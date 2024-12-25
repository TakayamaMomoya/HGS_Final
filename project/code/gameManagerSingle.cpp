//*****************************************************
//
// �V���O���Q�[���}�l�[�W���[[gameManagerSingle.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "gameManagerSingle.h"
#include "player.h"
#include "inputManager.h"
#include "resultSingle.h"
#include "game.h"
#include "fade.h"
#include "camera.h"
#include "cameraState.h"
#include "house.h"
#include "present.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int NUM_ENEMY_DEFAULT = 5;								// �G�̐��̃f�t�H���g�l
const string PATH_ENEMY_DEFAULT = "data\\TEXT\\enemy00.txt";	// �G�z�u���̃e�L�X�g
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CGameManagerSingle::CGameManagerSingle() : m_pPlayer(nullptr)
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CGameManagerSingle::Init(void)
{
	// �v���C���[����
	m_pPlayer = CPlayer::Create();

	if (m_pPlayer != nullptr)
	{
		// ���̓}�l�[�W���[�̊��蓖��
		CInputManager *pInpuMgr = CInputManager::Create();
		m_pPlayer->BindInputMgr(pInpuMgr);
	}

	// �J�����̃X�e�C�g�ݒ�
	Camera::ChangeState(new CFollowPlayer);

	// �Ƃ̐���
	CHouse::SetHouseRandom();
	
	// ���N���X�̏�����
	CGameManager::Init();

	// �X�R�A�̐���
	//CGame *pGame = CGame::GetInstance();

	//if (pGame != nullptr)
	//	pGame->CreateScore();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CGameManagerSingle::Uninit(void)
{
	// ���N���X�̏I��
	CGameManager::Uninit();

	m_pPlayer = nullptr;
}

//=====================================================
// �X�V����
//=====================================================
void CGameManagerSingle::Update(void)
{
	// ���N���X�̍X�V
	CGameManager::Update();
}

//=====================================================
// �J�n��Ԃ̍X�V
//=====================================================
void CGameManagerSingle::UpdateStart(void)
{
	// ���N���X�̍X�V
	CGameManager::UpdateStart();
}

//=====================================================
// �ʏ��Ԃ̍X�V
//=====================================================
void CGameManagerSingle::UpdateNormal(void)
{
	// ���N���X�̍X�V
	CGameManager::UpdateNormal();

	// �v���C���[�Ǘ�
	ManagePlayer();
}

//=====================================================
// �v���C���[�̊Ǘ�
//=====================================================
void CGameManagerSingle::ManagePlayer(void)
{
	if (m_pPlayer == nullptr)
		return;

	CPlayer::E_State state = m_pPlayer->GetState();

	if (state == CPlayer::E_State::STATE_DEATH)
		DeathPlayer();	// �v���C���[�̎��S
}

//=====================================================
// �v���C���[�̎��S
//=====================================================
void CGameManagerSingle::DeathPlayer(void)
{
	if (m_pPlayer == nullptr)
		return;

	m_pPlayer->Uninit();
	m_pPlayer = nullptr;

	// �v���C���[���S�Ŕs�k
	CResultSingle::Create(CResultSingle::RESULT_DEAD);
}

//=====================================================
// ���U���g��Ԃ̍X�V
//=====================================================
void CGameManagerSingle::UpdateResult(void)
{
	// ���N���X�̍X�V
	CGameManager::UpdateResult();
}

//=====================================================
// �I����Ԃ̍X�V
//=====================================================
void CGameManagerSingle::UpdateEnd(void)
{
	// ���N���X�̍X�V
	CGameManager::UpdateEnd();
}

//=====================================================
// �`�揈��
//=====================================================
void CGameManagerSingle::Draw(void)
{
	// ���N���X�̕`��
	CGameManager::Draw();
}

//=====================================================
// �Q�[���̏I��
//=====================================================
void CGameManagerSingle::EndGame(void)
{
	CFade *pFade = CFade::GetInstance();

	if (pFade != nullptr)
		pFade->SetFade(CScene::MODE_TITLE);
}