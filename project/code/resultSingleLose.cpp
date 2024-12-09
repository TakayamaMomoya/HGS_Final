//*****************************************************
//
// �V���O���������U���g�̏���[resultSingleLose.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "resultSingleLose.h"
#include "UI.h"
#include "camera.h"
#include "cameraState.h"
#include "number.h"
#include "texture.h"
#include "manager.h"
#include "inputManager.h"
#include "fade.h"
#include "sound.h"

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
const string PATH_TEX[CResultSingleLose::E_Select::SELECT_MAX] =
{// ���j���[�e�N�X�`���̃p�X
	"data\\TEXTURE\\UI\\Restart.png",
	"data\\TEXTURE\\UI\\Quit.png",
};
const float TIME_APPER = 2.0f;		// �o���ɂ����鎞��
const float WIDTH = 0.16f;			// ��
const float HEIGHT = 0.22f;			// ����
const float HEIGHT_INIT = -HEIGHT;
const D3DXVECTOR3 POS_INIT[CResultSingleLose::E_Select::SELECT_MAX] =
{// �����ʒu
	{ 0.3f,HEIGHT_INIT,0.0f },
	{ 0.7f,HEIGHT_INIT,0.0f },
};
const float HEIGHT_DEST = 0.7f;							// �ڕW�̍���
const float DIFF_HEIGHT = HEIGHT_DEST - HEIGHT_INIT;	// �����̍���
}
}

//*****************************************************
// �ÓI�����o�ϐ�
//*****************************************************
CResultSingleLose::FuncUpdateState CResultSingleLose::s_aFuncUpdateState[] =	// ��ԍX�V�֐�
{
	nullptr,								// �������Ȃ��X�V
	&CResultSingleLose::UpdateApperMenu,	// ���j���o����ԍX�V
	&CResultSingleLose::UpdateSelect,		// �I����ԍX�V
	nullptr,								// �I����Ԃ̍X�V
};

//====================================================
// �R���X�g���N�^
//====================================================
CResultSingleLose::CResultSingleLose() : m_fTimer(0.0f), m_apMenu(), m_state(E_State::STATE_NONE)
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CResultSingleLose::~CResultSingleLose()
{

}

//====================================================
// ����������
//====================================================
HRESULT CResultSingleLose::Init(void)
{
	// �e�N���X�̏�����
	CResultSingle::Init();

	// 2D�I�u�W�F�N�g�̐���
	Create2D();

	// �e�̏�Ԑݒ�
	CResultSingle::SetState(CResultSingle::E_State::STATE_FADE);

	m_select = SELECT_CONTINUE;
	m_apMenu[SELECT_QUIT]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	return S_OK;
}

//====================================================
// 2D�I�u�W�F�N�g�̐���
//====================================================
void CResultSingleLose::Create2D(void)
{
	// ���j���[�̐���
	CreateMenu();
}

//====================================================
// ���j���[�̐���
//====================================================
void CResultSingleLose::CreateMenu(void)
{
	for (int i = 0; i < E_Select::SELECT_MAX; i++)
	{
		// �L���v�V�����̐���
		m_apMenu[i] = CUI::Create();
		if (m_apMenu[i] == nullptr)
			continue;

		m_apMenu[i]->SetSize(menu::WIDTH, menu::HEIGHT);
		m_apMenu[i]->SetPosition(menu::POS_INIT[i]);
		int nIdxTexture = Texture::GetIdx(&menu::PATH_TEX[i][0]);
		m_apMenu[i]->SetIdxTexture(nIdxTexture);
		m_apMenu[i]->SetAlpha(0.0f);
		m_apMenu[i]->SetVtx();
	}
}

//====================================================
// �I������
//====================================================
void CResultSingleLose::Uninit(void)
{
	CResultSingle::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CResultSingleLose::Update(void)
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
void CResultSingleLose::UpdateApperMenu(void)
{
	m_fTimer += CManager::GetDeltaTime();

	float fTime = m_fTimer / menu::TIME_APPER;
	float fRate = easing::EaseOutExpo(fTime);
	universal::LimitValuefloat(&fRate, 1.0f, 0.0f);

	for (int i = 0; i < E_Select::SELECT_MAX; i++)
	{
		//-----------------------------------------
		// �L���v�V�����̈ړ�
		//-----------------------------------------
		if (m_apMenu[i] == nullptr)
			continue;

		D3DXVECTOR3 posCaption = m_apMenu[i]->GetPosition();
		posCaption.y = menu::HEIGHT_INIT + menu::DIFF_HEIGHT * fRate;

		m_apMenu[i]->SetPosition(posCaption);
		m_apMenu[i]->SetVtx();
		m_apMenu[i]->SetAlpha(fRate);
	}

	if (m_fTimer > menu::TIME_APPER)
	{// ��莞�Ԍo�߂Ŏ��̏�ԂɈڂ�
		m_state = E_State::STATE_SELECT;
		m_fTimer = 0.0f;
	}
}

//=====================================================
// �I����ԍX�V
//=====================================================
void CResultSingleLose::UpdateSelect(void)
{
	CInputManager *pInputManager = CInputManager::GetInstance();
	CSound* pSound = CSound::GetInstance();
	CFade *pFade = CFade::GetInstance();

	if (pFade == nullptr)
	{
		return;
	}
	else
	{
		if (pFade->GetState() != CFade::FADE_NONE)
			return;
	}

	if (pInputManager == nullptr)
	{
		return;
	}

	if (m_apMenu[m_select] != nullptr)
	{// �ȑO�ɑI�����Ă����ڂ��I��F�ɂ���
		m_apMenu[m_select]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	}

	// ���ڐ؂�ւ�
	if (pInputManager->GetTrigger(CInputManager::BUTTON_AXIS_RIGHT))
	{
		m_select = (E_Select)((m_select + 1) % E_Select::SELECT_MAX);
		pSound->Play(CSound::LABEL_SE_SELECT);
	}

	if (pInputManager->GetTrigger(CInputManager::BUTTON_AXIS_LEFT))
	{
		m_select = (E_Select)((m_select + E_Select::SELECT_MAX - 1) % E_Select::SELECT_MAX);
		pSound->Play(CSound::LABEL_SE_SELECT);
	}

	if (m_apMenu[m_select] != nullptr)
	{// �I�����Ă��鍀�ڂ̐F�ύX
		m_apMenu[m_select]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
	{// �I�����ڂɃt�F�[�h����
		if (pSound != nullptr)
		{
			pSound->Play(CSound::LABEL_SE_DECISION);
		}

		Fade(m_select);
	}
}

//====================================================
// �`�揈��
//====================================================
void CResultSingleLose::Draw(void)
{
	// �e�N���X�̕`��
	CResultSingle::Draw();
}

//====================================================
// �t�F�[�h���鏈��
//====================================================
void CResultSingleLose::Fade(E_Select select)
{
	CFade *pFade = CFade::GetInstance();

	if (pFade == nullptr)
		return;

	switch (select)
	{
	case CResultSingleLose::E_Select::SELECT_CONTINUE:	// �R���e�B�j���[
		pFade->SetFade(CScene::MODE::MODE_GAME);
		break;
	case CResultSingleLose::E_Select::SELECT_QUIT:		// �^�C�g���ɖ߂�
		pFade->SetFade(CScene::MODE::MODE_TITLE);
		break;
	default:
		break;
	}
}