//*****************************************************
//
// ���X�̏���[flowIce.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "flowIce.h"
#include "ice.h"
#include "iceManager.h"
#include "effect3D.h"
#include "manager.h"
#include "sound.h"
#include "player.h"
#include "camera.h"
#include "inputjoypad.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float TIME_DELETE = 20.0f;	// �X��������܂ł̎���

const float POW_CAMERAQUAKE_DEFAULT = 0.1f;		// �J�����̗h��̃f�t�H���g�l
const int FRAME_CAMERAQUAKE_DEFAULT = 30;		// �J�����̗h��̃f�t�H���g�t���[����

const float POW_VIB_CHAIN = 0.6f;	// �A�����̃R���g���[���[�h�ꋭ��
const int TIME_VIB_CHAIN = 40;		// �A�����̃R���g���[���[�h�꒷��
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
vector<CFlowIce*> CFlowIce::s_vector;	// �i�[�p�̔z��

//=====================================================
// �R���X�g���N�^
//=====================================================
CFlowIce::CFlowIce(int nPriority) : CObject(nPriority), m_fTimerDelete(0.0f), m_bInScrnAllIce(false)
{
	s_vector.push_back(this);
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CFlowIce::~CFlowIce()
{

}

//=====================================================
// ��������
//=====================================================
CFlowIce *CFlowIce::Create(void)
{
	CFlowIce *pFlowice = nullptr;

	pFlowice = new CFlowIce;

	if (pFlowice != nullptr)
		pFlowice->Init();

	return pFlowice;
}

//=====================================================
// ����������
//=====================================================
HRESULT CFlowIce::Init(void)
{
	return S_OK;
}

//=====================================================
// �X��z��ɒǉ�
//=====================================================
void CFlowIce::AddIceToArray(CIce *pIce)
{
	m_apIce.push_back(pIce);
}

//=====================================================
// �I������
//=====================================================
void CFlowIce::Uninit(void)
{
	for (auto itr = s_vector.begin(); itr < s_vector.end(); itr++)
	{
		if (*itr == this)
		{
			s_vector.erase(itr);

			break;
		}
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CFlowIce::Update(void)
{
	// �ǂꂩ�̕X���~�܂��Ă��Ȃ����̃`�F�b�N
	CheckSomeIceStop();

	// ���̗��X�Ƃ̔���
	CollideOtherFlowIce();

	if (!m_bInScrnAllIce)
		CheckInAllIce();	// �S�Ă̕X���f�������̔���
	else
		CheckDelete();	// �폜�m�F

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// �S�Ă̕X����ʂɉf�������̃`�F�b�N
//=====================================================
void CFlowIce::CheckInAllIce(void)
{
	CIceManager *pIceMgr = CIceManager::GetInstance();

	if (pIceMgr == nullptr)
		return;

	for (int i = 0; i < (int)m_apIce.size(); i++)
	{
		if (m_apIce[i] == nullptr)
			continue;

		// ��ʓ�����
		D3DXVECTOR3 pos = m_apIce[i]->GetPosition();
		if (universal::IsInScreen(pos, nullptr))
		{// �ǂꂩ��ł���ʓ��ɂ���΃t���O�𗧂Ă�
			m_bInScrnAllIce = true;
		}
	}
}

//=====================================================
// �ǂꂩ�̕X���~�܂��Ă��Ȃ����̃`�F�b�N
//=====================================================
void CFlowIce::CheckSomeIceStop(void)
{
	for (auto it : m_apIce)
	{
		if (it->IsStop())
		{// �~�܂��Ă���Ȃ�S�Ă̕X���~�߂�
			StopAllIce();
			Uninit();	// ���g�̔j��
			break;
		}
	}
}

//=====================================================
// ���̗��X�Ƃ̔���
//=====================================================
void CFlowIce::CollideOtherFlowIce(void)
{
	
}

//=====================================================
// �S�Ă̕X���~�߂�
//=====================================================
void CFlowIce::StopAllIce(void)
{
	CIceManager *pIceManager = CIceManager::GetInstance();

	if (pIceManager == nullptr)
		return;

	for (auto it : m_apIce)
	{
		it->ChangeState(new CIceStaeteNormal);

		pIceManager->AddIce(it, it->GetPosition());
	}

	Sound::Play(CSound::LABEL_SE_ICE_CHAIN);

	// �J������h�炷
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
		pCamera->SetQuake(POW_CAMERAQUAKE_DEFAULT, POW_CAMERAQUAKE_DEFAULT, FRAME_CAMERAQUAKE_DEFAULT);

	// �R���g���[���[��U��������
	CInputJoypad* pInputJoypad = CInputJoypad::GetInstance();

	if (pInputJoypad == nullptr)
		return;

	pInputJoypad->Vibration(POW_VIB_CHAIN, TIME_VIB_CHAIN);
}

//=====================================================
// ��ɂ�����̂��~�߂�
//=====================================================
void CFlowIce::StopOnTopObject(void)
{

}

//=====================================================
// �S�X�̍폜
//=====================================================
void CFlowIce::DeleteAllIce(void)
{
	CIceManager *pIceManager = CIceManager::GetInstance();

	if (pIceManager == nullptr)
		return;

	// �v���C���[�̎擾
	vector<CPlayer*> apPlayer = CPlayer::GetInstance();

	for (int i = 0; i < (int)m_apIce.size(); i++)
	{
		if (m_apIce[i] == nullptr)
			continue;
		
		for (CPlayer *pPlayer : apPlayer)
		{// �v���C���[����ɏ���Ă���Hit����
			D3DXVECTOR3 pos = pPlayer->GetPosition();
			D3DXVECTOR3 posIce = m_apIce[i]->GetPosition();

			if (universal::DistCmpFlat(posIce, pos, Grid::SIZE, nullptr))
				pPlayer->Hit(0.0f);
		}

		pIceManager->DeleteIce(m_apIce[i]);
		m_apIce[i]->Uninit();
	}

	m_apIce.clear();
}

//=====================================================
// �X�폜�̊m�F
//=====================================================
void CFlowIce::CheckDelete(void)
{
	CIceManager *pIceMgr = CIceManager::GetInstance();

	if (pIceMgr == nullptr)
		return;

	for (int i = 0; i < (int)m_apIce.size(); i++)
	{
		if (m_apIce[i] == nullptr)
			continue;

		// ��ʓ�����
		D3DXVECTOR3 pos = m_apIce[i]->GetPosition();
		if (universal::IsInScreen(pos, nullptr))
			return;	// �ǂꂩ��ł���ʓ��ɂ���Ί֐����I��
	}

	// �����܂Œʂ�����X���폜
	DeleteAllIce();
	Uninit();
}

//=====================================================
// �f�o�b�O����
//=====================================================
void CFlowIce::Debug(void)
{
	for (auto it : m_apIce)
	{
		D3DXVECTOR3 posIce = it->GetPosition();

		//CEffect3D::Create(posIce, 50.0f, 5, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CFlowIce::Draw(void)
{

}