//*****************************************************
//
// �v���C���[�̏���[player.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "player.h"
#include "inputManager.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "debugproc.h"
#include "particle.h"
#include "camera.h"
#include "manager.h"
#include "flowIce.h"
#include "effect3D.h"
#include "collision.h"
#include "texture.h"
#include "sound.h"
#include "MyEffekseer.h"
#include "gameManager.h"
#include "navigation.h"

#include "house.h"
#include "UI.h"
#include "present.h"
#include "gauge.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const std::string PATH_BODY = "data\\MOTION\\motionTonakai.txt";	// �{�f�B�̃p�X
const float MODEL_SCALE = 10.0f; // �g�嗦

const float RATE_DECREASE_MOVE = 0.5f;	// �ړ������̊���
const float LINE_FACT_ROT = 0.3f;		// ������␳����܂ł̓��͂������l
const float FACT_ROTATION = 0.1f;		// ��]�W��
const float SPEED_MOVE = 20.0f;			// �ړ����x

const float INTERACT_LENGTH = 1000.0f; // �C���^���N�g�\�����o��͈�
const D3DXVECTOR3 UI_SIZE = { 0.025f, 0.05f, 0.0f }; // �C���^���N�gUI�̃T�C�Y
const D3DXVECTOR3 UI_OFFSET = { 0.0f, 600.0f, 0.0f }; // �C���^���N�gUI�̃I�t�Z�b�g

const D3DXVECTOR3 PRESENT_OFFSET = { 0.0f, 300.0f, 0.0f }; // �v���[���g�̃I�t�Z�b�g

const int POWERUP_NUM = 5; // �����ɕK�v�ȘA������
const float POWER_RATE = 2.0f; // �����{��

const float POWER_GAUGE = 5.0f;							// �A�������Q�[�W�̍ő�l
const float POWER_ADD = 1.0f;		// �P�����ŉ��Z�����Q�[�W�̗�
const D3DXVECTOR3 GAUGE_POS = { 0.8f, 0.93f, 0.0f };	// �Q�[�W�̈ʒu
const D3DXVECTOR2 GAUGE_SIZE = { 0.2f, 0.07f };		// �Q�[�W�̃T�C�Y
const float RADIUS_COLLISION = 200.0f;					// ����̔��a

const float SAB_TIME = 10.0f; // �Q�[�W����������܂ł̎���

}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
vector<CPlayer*> CPlayer::s_apPlayer;	// �i�[�p�̔z��

//=====================================================
// �R���X�g���N�^
//=====================================================
CPlayer::CPlayer(int nPriority) : m_state(STATE_NONE), m_bEnableInput(false), m_fragMotion(), m_nID(0),
m_pInteract(nullptr),
m_pPresent(nullptr),
m_pNearHouse(nullptr),
m_nAnswerCount(0),
m_pGauge(nullptr),
m_pCollision(nullptr),
m_fSabTime(0.0f)
{
	// �f�t�H���g�͓��������̔ԍ�
	m_nID = (int)s_apPlayer.size();

	s_apPlayer.push_back(this);
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CPlayer::~CPlayer()
{

}

//=====================================================
// ��������
//=====================================================
CPlayer* CPlayer::Create(void)
{
	CPlayer *pPlayer = nullptr;

	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		pPlayer->Init();
	}

	return pPlayer;
}

//=====================================================
// ����������
//=====================================================
HRESULT CPlayer::Init(void)
{
	// �Ǎ�
	Load((char*)&PATH_BODY[0]);

	// �p���N���X�̏�����
	CCharacter::Init();

	// �傫������
	SetScale(MODEL_SCALE);

	// �Q�[�W�𐶐�
	m_pGauge = CGauge::Create(POWER_GAUGE, GAUGE_SIZE);
	m_pGauge->SetPosition(GAUGE_POS);

	// �v���[���g�𐶐�
	m_pPresent = CPresent::Create();

	// ���͉\�t���O��ݒ�
	m_bEnableInput = true;

	// ��Ԑݒ�
	m_state = STATE_NORMAL;

	// ����̐���
	m_pCollision = CCollisionSphere::Create(CCollision::TAG_PLAYER, CCollision::TYPE::TYPE_SPHERE, this);

	if (m_pCollision != nullptr)
	{
		m_pCollision->SetRadius(RADIUS_COLLISION);
	}

	// �i�r�Q�[�V��������
	CNavigation::Create();

	EnableShadow(true);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CPlayer::Uninit(void)
{
	for (auto itr = s_apPlayer.begin(); itr < s_apPlayer.end(); itr++)
	{
		//�폜�Ώۂ���Ȃ��ꍇ
		if (*itr != this)
			continue;

		//Vector����폜
		s_apPlayer.erase(itr);

		break;
	}

	// UI���폜����
	if (m_pInteract != nullptr)
	{
		m_pInteract->Uninit();
		delete m_pInteract;
		m_pInteract = nullptr;
	}

	if (m_pCollision != nullptr)
	{
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}

	// �p���N���X�̏I��
	CCharacter::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CPlayer::Update(void)
{
	// �C���^���N�g�\������
	Interact();

	// UI���ړ�����
	if (m_pInteract != nullptr)
	{
		D3DXVECTOR3 posScreen = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 pos = GetPosition() + UI_OFFSET;
		universal::IsInScreen(pos, &posScreen);
		universal::ConvertScreenRate(posScreen);
		m_pInteract->SetPosition(posScreen);
	}

	// �Q�[�W�̑���
	ControlGauge();

	CDebugProc::GetInstance()->Print("\n\n\n\n\n\n\n�Q�[�W�̐��� : %f\n\n\n\n\n\n", m_pGauge->GetParam());

	// �v���[���g�����ւ��鏈��
	SwapPresent();

	// �v���[���g���ړ�����
	if (m_pPresent != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition() + PRESENT_OFFSET;
		m_pPresent->SetPosition(pos);
	}

	// ���͏���
	Input();

	// ���[�V�����̊Ǘ�
	ManageMotion();

	// ���[�V�����X�V
	CCharacter::Update();

	// ����̒Ǐ]
	if (m_pCollision != nullptr)
	{// ���̔���̒Ǐ]
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 posInit = pos;

		m_pCollision->SetPosition(pos);

		// �u���b�N����
		m_pCollision->PushCollision(&pos, CCollision::TAG::TAG_BLOCK);

		pos.y = posInit.y;

		// �ʒu����
		CHouse::LimitPos(pos);

		// �L�����̈ʒu���f
		SetPosition(pos);
	}

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// ����
//=====================================================
void CPlayer::Input(void)
{
	if (m_bEnableInput)
	{
		// �A�i���O�ړ�
		MoveAnalog();
	}
}

//=====================================================
// �A�i���O�ړ�
//=====================================================
void CPlayer::MoveAnalog(void)
{
	// �A�i���O�ړ�����
	InputMoveAnalog();
}

//=====================================================
// �A�i���O�ړ�����
//=====================================================
void CPlayer::InputMoveAnalog(void)
{
	// �O�i����
	Forward();
}

//=====================================================
// �O�i����
//=====================================================
void CPlayer::Forward(void)
{
	if (m_pInputMgr == nullptr)
		return;

	// �ڕW�����̐ݒ�
	CInputManager::S_Axis axis = m_pInputMgr->GetAxis();
	D3DXVECTOR3 axisMove = axis.axisMove;

	// ���𐳋K��
	float fLengthAxis = D3DXVec3Length(&axisMove);

	D3DXVECTOR3 vecMove = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 rot = GetRotation();

	float fSpeed = 0.0f;

	if (LINE_FACT_ROT < fLengthAxis)
	{// �ړ������삪�������l���z���Ă�����ړ�
		fSpeed = SPEED_MOVE;

		// �ړ����x�̐ݒ�
		D3DXVECTOR3 move = GetMove();

		// �����Ă�������Ƀx�N�g����L�΂�
		vecMove -= {sinf(rot.y) * fSpeed, 0.0f, cosf(rot.y) * fSpeed};
		move += vecMove;

		SetMove(move);

		// �ڕW�����̐ݒ�
		float fRotDest = atan2f(axisMove.x, axisMove.z) + D3DX_PI;
		SetRotDest(fRotDest);

		m_fragMotion.bWalk = true;
	}
	else
		m_fragMotion.bWalk = false;

	if (m_pGauge->GetParam() >= POWER_GAUGE)
	{
		fSpeed *= POWER_RATE;
	}
}

//==========================================
//  �C���^���N�g�\��
//==========================================
void CPlayer::Interact()
{
	// �����̏����擾����
	if (CHouse::GetList() == nullptr) { return; }
	std::list<CHouse*> list = CHouse::GetList()->GetList();    // ���X�g���擾

	// ���g�̍��W���擾����
	D3DXVECTOR3 pos = GetPosition();

	// �v���C���[���X�g�̒��g���m�F����
	for (CHouse* house : list)
	{
		// �N���A�t���O�������Ă����ꍇ���ɐi��
		if(house->IsClear()) continue;

		// �����̍��W���擾����
		D3DXVECTOR3 posHouse = house->GetPosition();

		// ��苗�����Ɍ��������݂��Ȃ��ꍇ���ɐi��
		if (!universal::DistCmp(pos, posHouse, INTERACT_LENGTH, nullptr)) continue;

		// ��苗�����Ɍ��������݂�����|���S����\������
		if (m_pInteract == nullptr)
		{
			m_pInteract = CUI::Create();
			m_pInteract->Init();
			m_pInteract->SetSize(UI_SIZE.x, UI_SIZE.y);
			D3DXVECTOR3 posScreen = { 0.0f, 0.0f, 0.0f };
			D3DXVECTOR3 pos = GetPosition() + UI_OFFSET;
			universal::IsInScreen(pos, &posScreen);
			universal::ConvertScreenRate(posScreen);
			m_pInteract->SetPosition(posScreen);
			m_pInteract->SetIdxTexture(Texture::GetIdx("data\\TEXTURE\\UI\\swap.png"));
		}

		// �߂������������L�^����
		m_pNearHouse = house;

		return;
	}

	// �������Ō�܂Ń`�F�b�N���Ă����݂��Ă��Ȃ��ꍇ�|���S�����폜����
	if (m_pInteract != nullptr)
	{
		m_pInteract->Uninit();
		delete m_pInteract;
		m_pInteract = nullptr;
	}
}

//==========================================
//  �v���[���g���������鏈��
//==========================================
void CPlayer::SwapPresent()
{
	CDebugProc::GetInstance()->Print("�����v���[���g : %d\n", m_pPresent);
	CDebugProc::GetInstance()->Print("�A�������J�E���^�[ : %d\n", m_nAnswerCount);

	// �C���^���N�g�\�������݂��Ă��Ȃ��ꍇ�֐��𔲂���
	if (m_pInteract == nullptr) { return; }

	// ���͏��̎擾
	CInputKeyboard* pInputKeyboard = CInputKeyboard::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	// �{�^�����͂��Ȃ��ꍇ�֐��𔲂���
	if (!pInputKeyboard->GetTrigger(DIK_SPACE) && !pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0)){ return; }

	// �ł��߂������̃v���[���g���󂯎��
	CPresent* pTemp = m_pNearHouse->GetPresent();

	// �ł��߂������Ƀv���[���g��^����
	m_pNearHouse->SetPresent(m_pPresent);

	// �����̃v���[���g�������ꍇ�J�E���^�[�����Z����
	if (m_pNearHouse->GetLabelWant() == m_pPresent->GetLabel())
	{
		m_fSabTime = 0.0f;
		++m_nAnswerCount;
		m_pGauge->AddParam(POWER_ADD);
	}
	else
	{
		// �ԈႦ�Ă����ꍇ�J�E���^�[��������
		m_fSabTime = 0.0f;
		m_nAnswerCount = 0;
		m_pGauge->SetParam(0.0f);
	}

	// ���g�̏������Ă���v���[���g���㏑������
	m_pPresent = pTemp;
}

//==========================================
//  �Q�[�W�̑���
//==========================================
void CPlayer::ControlGauge()
{
	// �Q�[�W���ő�̏ꍇ�֐��𔲂���
	if (m_pGauge->GetParam() >= POWER_GAUGE) { return; }

	// �Q�[�W�������Ԃ����Z����
	m_fSabTime += CManager::GetDeltaTime();

	// ��莞�Ԍo�߂��Ă��Ȃ��ꍇ�֐��𔲂���
	if (m_fSabTime < SAB_TIME) { return; }

	// �Q�[�W�����炷
	m_pGauge->AddParam(-0.01f);
}

//=====================================================
// �W���C�p�b�h��U��������
//=====================================================
void CPlayer::VibJoypad(float fPow, int nFrame)
{
	CInputJoypad* pInputJoypad = CInputJoypad::GetInstance();

	if (pInputJoypad == nullptr)
		return;

	// joypad�U��������
	pInputJoypad->Vibration(m_nID, fPow, nFrame);
}

//=====================================================
// ���[�V�����̊Ǘ�
//=====================================================
void CPlayer::ManageMotion(void)
{
	int nMotion = GetMotion();
	bool bFinish = IsFinish();
	
	if (m_fragMotion.bWalk)
	{// �������[�V�����t���O�L��
		if (m_pGauge->GetParam() >= POWER_GAUGE)
		{
			if (nMotion != MOTION::MOTION_WALKTWOLEG)
				SetMotion(MOTION::MOTION_WALKTWOLEG);
		}
		else
		{
			if (nMotion != MOTION::MOTION_WALKFOURLEG)
				SetMotion(MOTION::MOTION_WALKFOURLEG);
		}
	}
	else
	{// �����t���O�������Ă��Ȃ����
		if(nMotion != MOTION::MOTION_NEUTRAL)
			SetMotion(MOTION::MOTION_NEUTRAL);
	}
}

//=====================================================
// ���[�V�����C�x���g
//=====================================================
void CPlayer::Event(EVENT_INFO* pEventInfo)
{
	int nMotion = GetMotion();
}

//=====================================================
// �q�b�g����
//=====================================================
void CPlayer::Hit(float fDamage)
{
	if (m_state == E_State::STATE_DEATH)
		return;	// �����ɂ����Hit�����𖳌���
}

//=====================================================
// �f�o�b�O����
//=====================================================
void CPlayer::Debug(void)
{
	CDebugProc *pDebugProc = CDebugProc::GetInstance();
	CInputKeyboard *pInputKeyboard = CInputKeyboard::GetInstance();
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();
	CInputManager *pInputMgr = CInputManager::GetInstance();

	if (pDebugProc == nullptr || pInputKeyboard == nullptr || pJoypad == nullptr || pInputMgr == nullptr)
		return;

#if 1
	pDebugProc->Print("\n�v���C���[���==========================");
	pDebugProc->Print("\n�ʒu[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	pDebugProc->Print("\n�ړ���[%f,%f,%f]", GetMove().x, GetMove().y, GetMove().z);
	pDebugProc->Print("\n���[%d]", GetState());
#endif

}

//=====================================================
// �`�揈��
//=====================================================
void CPlayer::Draw(void)
{
	// �p���N���X�̕`��
	CCharacter::Draw();
}

//=====================================================
// �S�v���C���[�̓��̓t���O�ݒ�
//=====================================================
void CPlayer::EnableInputAll(bool bValue)
{
	for (CPlayer *pPlayer : s_apPlayer)
		pPlayer->EnableInput(bValue);
}