//*****************************************************
//
// �}���`�^�C���A�b�v���U���g[resultMultiTimeUp.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "resultMultiTimeUp.h"
#include "UI.h"
#include "camera.h"
#include "cameraState.h"
#include "number.h"
#include "texture.h"
#include "manager.h"
#include "inputManager.h"
#include "fade.h"
#include "sound.h"
#include "gameManager.h"
#include "player.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
//----------------------------
// ���j���[�萔
//----------------------------
namespace menu
{
const string PATH_TEX = "data\\TEXTURE\\UI\\tutorialskip.png";	// �e�N�X�`���p�X
const float TIME_APPER = 2.0f;									// �o���ɂ����鎞��
const float WIDTH = 0.16f;										// ��
const float HEIGHT = 0.10f;										// ����
const float HEIGHT_INIT = -HEIGHT;
const D3DXVECTOR3 POS_INIT = { 0.5f,HEIGHT_INIT,0.0f };			// �����ʒu
const float HEIGHT_DEST = 0.7f;									// �ڕW�̍���
const float DIFF_HEIGHT = HEIGHT_DEST - HEIGHT_INIT;			// �����̍���
}
}

//*****************************************************
// �ÓI�����o�ϐ�
//*****************************************************
CResultMultiTimeUp::FuncUpdateState CResultMultiTimeUp::s_aFuncUpdateState[] =	// ��ԍX�V�֐�
{
	nullptr,								// �������Ȃ��X�V
	&CResultMultiTimeUp::UpdateApperMenu,	// ���j���o����ԍX�V
	&CResultMultiTimeUp::UpdateWait,		// �I����ԍX�V
	nullptr,								// �I����Ԃ̍X�V
};

//====================================================
// �R���X�g���N�^
//====================================================
CResultMultiTimeUp::CResultMultiTimeUp() : m_fTimer(0.0f), m_state(E_State::STATE_NONE)
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CResultMultiTimeUp::~CResultMultiTimeUp()
{

}

//====================================================
// ����������
//====================================================
HRESULT CResultMultiTimeUp::Init(void)
{
	// �e�N���X�̏�����
	CResultSingle::Init();

	// 2D�I�u�W�F�N�g�̐���
	Create2D();

	// �e�̏�Ԑݒ�
	CResultSingle::SetState(CResultSingle::E_State::STATE_FADE);

	return S_OK;
}

//====================================================
// 2D�I�u�W�F�N�g�̐���
//====================================================
void CResultMultiTimeUp::Create2D(void)
{
	// ���j���[�̐���
	CreateMenu();
}

//====================================================
// ���j���[�̐���
//====================================================
void CResultMultiTimeUp::CreateMenu(void)
{
	// �L���v�V�����̐���
	m_pMenu = CUI::Create();
	if (m_pMenu == nullptr)
		return;

	m_pMenu->SetSize(menu::WIDTH, menu::HEIGHT);
	m_pMenu->SetPosition(menu::POS_INIT);
	int nIdxTexture = Texture::GetIdx(&menu::PATH_TEX[0]);
	m_pMenu->SetIdxTexture(nIdxTexture);
	m_pMenu->SetAlpha(0.0f);
	m_pMenu->SetVtx();
}

//====================================================
// �I������
//====================================================
void CResultMultiTimeUp::Uninit(void)
{
	CResultSingle::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CResultMultiTimeUp::Update(void)
{
	assert(m_state > -1 && m_state < STATE_MAX);
	if (s_aFuncUpdateState[m_state] != nullptr)
	{ // �X�V�֐����w�肳��Ă���ꍇ

		// �e��Ԃ��Ƃ̍X�V
		(this->*(s_aFuncUpdateState[m_state]))();
	}

	// �e�N���X�̍X�V
	CResultSingle::Update();

	if (GetState() == CResultSingle::E_State::STATE_ENDAPPERCAPTION && m_state == E_State::STATE_NONE)
		m_state = E_State::STATE_APPER_MENU;	// �t�F�[�h���I�������牉�o�n�܂�
}

//=====================================================
// ���j���[�o����ԍX�V
//=====================================================
void CResultMultiTimeUp::UpdateApperMenu(void)
{
	m_fTimer += CManager::GetDeltaTime();

	float fTime = m_fTimer / menu::TIME_APPER;
	float fRate = easing::EaseOutExpo(fTime);
	universal::LimitValuefloat(&fRate, 1.0f, 0.0f);

	//-----------------------------------------
	// �L���v�V�����̈ړ�
	//-----------------------------------------
	if (m_pMenu == nullptr)
		return;

	D3DXVECTOR3 posCaption = m_pMenu->GetPosition();
	posCaption.y = menu::HEIGHT_INIT + menu::DIFF_HEIGHT * fRate;

	m_pMenu->SetPosition(posCaption);
	m_pMenu->SetVtx();
	m_pMenu->SetAlpha(fRate);

	if (m_fTimer > menu::TIME_APPER)
	{// ��莞�Ԍo�߂Ŏ��̏�ԂɈڂ�
		m_state = E_State::STATE_WAIT;
		m_fTimer = 0.0f;
	}
}

//=====================================================
// �I����ԍX�V
//=====================================================
void CResultMultiTimeUp::UpdateWait(void)
{
	CInputManager *pInputManager = CInputManager::GetInstance();
	CSound* pSound = CSound::GetInstance();
	CFade *pFade = CFade::GetInstance();

	if (pFade == nullptr)
		return;

	if (pInputManager == nullptr)
		return;

	if (pInputManager->GetTrigger(CInputManager::E_Button::BUTTON_ENTER))
	{
		// ���������ݒ�ɂ��ă}���`���U���g�ֈڍs
		gameManager::SaveWinner(CPlayer::GetNumPlayer(), -1);

		CFade *pFade = CFade::GetInstance();

		if (pFade != nullptr)
			pFade->SetFade(CScene::MODE_RESULTMULTI);
	}
}

//====================================================
// �`�揈��
//====================================================
void CResultMultiTimeUp::Draw(void)
{
	// �e�N���X�̕`��
	CResultSingle::Draw();
}