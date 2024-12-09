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
#include "shadow.h"
#include "MyEffekseer.h"
#include "gameManager.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const std::string PATH_BODY = "data\\MOTION\\motionPenguin.txt";	// �{�f�B�̃p�X

const float RATE_DECREASE_MOVE = 0.5f;	// �ړ������̊���
const float LINE_FACT_ROT = 0.3f;		// ������␳����܂ł̓��͂������l
const float FACT_ROTATION = 0.1f;		// ��]�W��
const float SPEED_MOVE = 5.0f;			// �ړ����x
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
vector<CPlayer*> CPlayer::s_apPlayer;	// �i�[�p�̔z��

//=====================================================
// �R���X�g���N�^
//=====================================================
CPlayer::CPlayer(int nPriority) : m_state(STATE_NONE), m_bEnableInput(false), m_fragMotion(), m_nID(0), m_pShadow(nullptr)
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
	CMotion::Init();

	InitPose(0);

	// ���͉\�t���O��ݒ�
	m_bEnableInput = true;

	// ��Ԑݒ�
	m_state = STATE_NORMAL;

	// �e�̐���
	m_pShadow = CShadow::Create();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CPlayer::Uninit(void)
{
	Object::DeleteObject((CObject**)&m_pShadow);

	for (auto itr = s_apPlayer.begin(); itr < s_apPlayer.end(); itr++)
	{
		//�폜�Ώۂ���Ȃ��ꍇ
		if (*itr != this)
			continue;

		//Vector����폜
		s_apPlayer.erase(itr);

		break;
	}

	// �p���N���X�̏I��
	CMotion::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CPlayer::Update(void)
{
	// ���͏���
	Input();

	// ���[�V�����̊Ǘ�
	ManageMotion();

	// �e�̒Ǐ]
	if (m_pShadow != nullptr)
		m_pShadow->SetPosition(GetPosition());

	// ���[�V�����X�V
	CMotion::Update();

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

	// �����̕␳
	FactingRot();

	// �ړ��ʂ̌���
	DecreaseMove();
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
	}

	// �ړ����x�̐ݒ�
	D3DXVECTOR3 move = GetMove();

	// �����Ă�������Ƀx�N�g����L�΂�
	vecMove -= {sinf(rot.y) * fSpeed, 0.0f, cosf(rot.y) * fSpeed};
	move += vecMove;

	SetMove(move);

	// �ړ��ʂ̔��f
	Translate(move);
}

//=====================================================
// �ړ��ʌ���
//=====================================================
void CPlayer::DecreaseMove(void)
{
	D3DXVECTOR3 move = GetMove();

	// �ړ��ʂ̌���
	move.x *= RATE_DECREASE_MOVE;
	move.z *= RATE_DECREASE_MOVE;

	SetMove(move);
}

//=====================================================
// �����̕␳
//=====================================================
void CPlayer::FactingRot(void)
{
	if (m_pInputMgr == nullptr)
		return;

	// �˂������[�V�������͍s��Ȃ�
	int nMotion = GetMotion();
	if (nMotion == MOTION_PECK || nMotion == MOTION_CANNOTPECK)
		return;

	// �ڕW�����̐ݒ�
	CInputManager::S_Axis axis = m_pInputMgr->GetAxis();
	D3DXVECTOR3 axisMove = axis.axisMove;

	// ���𐳋K��
	float fLengthAxis = D3DXVec3Length(&axisMove);

	if (fLengthAxis >= LINE_FACT_ROT)
	{// ���͂��������l���z���Ă�����␳
		// �ڕW�̌����ɕ␳����
		float fRotDest = atan2f(-axisMove.x, -axisMove.z);

		D3DXVECTOR3 rot = GetRotation();
		universal::FactingRot(&rot.y, fRotDest, FACT_ROTATION);
		SetRotation(rot);
	}
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
		if (nMotion != MOTION::MOTION_WALK)
			SetMotion(MOTION::MOTION_WALK);
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

	if (pDebugProc == nullptr || pInputKeyboard == nullptr || pJoypad == nullptr || pInputMgr == nullptr || m_pShadow == nullptr)
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
	CMotion::Draw();
}

//=====================================================
// �e�̈ʒu�ݒ�
//=====================================================
void CPlayer::SetShadowPos(D3DXVECTOR3 pos)
{
	if (m_pShadow != nullptr)
		m_pShadow->SetJustPosition(pos);
}

//=====================================================
// �S�v���C���[�̓��̓t���O�ݒ�
//=====================================================
void CPlayer::EnableInputAll(bool bValue)
{
	for (CPlayer *pPlayer : s_apPlayer)
		pPlayer->EnableInput(bValue);
}