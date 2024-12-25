//*****************************************************
//
// �Q�[���}�l�[�W���[[gameManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "gameManager.h"
#include "gameManagerSingle.h"
#include "UIManager.h"
#include "timer.h"
#include "BG_Ice.h"
#include "UI_ready.h"
#include "sound.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const string PATH_TEX = "data\\TEMP\\mode.txt";	// ���[�h�̃p�X
const string PATH_IDXMAP = "data\\TEMP\\mapIdx.bin";	// �}�b�v�ԍ��̃p�X
const string PATH_WINNER = "data\\TEMP\\winner.bin";	// ���҂̃p�X
const string PATH_IDXINPUT = "data\\TEMP\\idxInput.txt";	// ���͔ԍ��̃p�X
const int PLAY_SOUND_SEA_COUNT = 60 * 24;	// �Â��ȊC�T�E���h�Đ����ԁi�E���ύX�ŕb���ύX�j
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CGameManager::CGameManager()
{
	m_nCounterSoundSea = 0;
}

//=====================================================
// ��������
//=====================================================
CGameManager *CGameManager::Create(CGame::E_GameMode mode)
{
	CGameManager* pGameManager = nullptr;

	pGameManager = new CGameManagerSingle;

	if (pGameManager == nullptr)
		return nullptr;

	pGameManager->Init();

	return pGameManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CGameManager::Init(void)
{
	// UI�}�l�[�W���[�̒ǉ�
	CUIManager::Create();

#if 0
	//�Q�[���X�^�[�g���mUI
	CUIready::Create();
#endif

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CGameManager::Uninit(void)
{
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CGameManager::Update(void)
{
	// �Q�[���̏�ԊǗ�
	ManageGameState();
}

//=====================================================
// �Q�[���̏�ԊǗ�
//=====================================================
void CGameManager::ManageGameState(void)
{
	CGame::E_State state = CGame::GetState();

	switch (state)
	{
	case CGame::STATE_READY:

		break;
	case CGame::STATE_START:
		UpdateStart();
		break;
	case CGame::STATE_NORMAL:
		UpdateNormal();
		break;
	case CGame::STATE_RESULT:
		UpdateResult();
		break;
	case CGame::STATE_END:
		UpdateEnd();
		break;
	default:
		assert(false);
		break;
	}
}

//=====================================================
// �J�n��Ԃ̍X�V
//=====================================================
void CGameManager::UpdateStart(void)
{

}

//=====================================================
// �ʏ��Ԃ̍X�V
//=====================================================
void CGameManager::UpdateNormal(void)
{
	m_nCounterSoundSea++;
	if (m_nCounterSoundSea >= PLAY_SOUND_SEA_COUNT)
	{// ���𗬂�
		m_nCounterSoundSea = 0;
		CSound::GetInstance()->Play(CSound::LABEL_SE_SEA);
	}
}

//=====================================================
// ���U���g��Ԃ̍X�V
//=====================================================
void CGameManager::UpdateResult(void)
{

}

//=====================================================
// �I����Ԃ̍X�V
//=====================================================
void CGameManager::UpdateEnd(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CGameManager::Draw(void)
{

}