//*****************************************************
//
// �^�C�g������[title.cpp]
// Author:��؈�^
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "title.h"
#include "fade.h"
#include "object.h"
#include "inputManager.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"
#include "cameraState.h"
#include "renderer.h"
#include "sound.h"
#include "polygon3D.h"
#include "objectX.h"
#include "skybox.h"
#include "polygon2D.h"
#include "UI.h"
#include "effect2D.h"
#include "inputjoypad.h"
#include "npcpenguin.h"
#include "npcpenguinstate_title.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MOVE_FACT	(0.01f)	// �ړ����x
#define LINE_UNINIT	(0.2f)	// �I������܂ł̂������l
#define EFFECTMAX	(15)	// ��͂��ŉ󂵂��Ƃ��̃G�t�F�N�g�̍ő吔

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const string PATH_TEX = "data\\TEXTURE\\EFFECT\\snow01.png";	// �e�N�X�`���p�X
	const string MAP_PATH = "data\\TEXT\\ice_stage_title.txt";		// �z�u�X�e�[�W�p�X
	const D3DXCOLOR COL_INITIAL_MENU = { 0.4f,0.4f,0.4f,1.0f };	// ���j���[���ڂ̏����F
	const D3DXCOLOR COL_CURRENT_MENU = { 1.0f,1.0f,1.0f,1.0f };	// ���j���[���ڂ̑I��F
	const D3DXVECTOR3 UI_POS[CTitle::TITLE_UI_MAX] =  // UI�̏����ʒu
	{
		D3DXVECTOR3(-0.2f, 0.4f,0.0f),
		D3DXVECTOR3(1.2f, 0.36f,0.0f),
		D3DXVECTOR3(0.5f, 0.28f,0.0f),
		D3DXVECTOR3(0.8f, 0.23f,0.0f),
		D3DXVECTOR3(0.25f, 0.18f,0.0f),
		D3DXVECTOR3(0.48f, 0.33f,0.0f),
		D3DXVECTOR3(0.72f, 0.68f,0.0f),
		D3DXVECTOR3(0.5f, 0.5f,0.0f),
	};
	const D3DXVECTOR2 UI_SIZE[CTitle::TITLE_UI_MAX] =  // UI�̏����T�C�Y
	{
		D3DXVECTOR2(0.2f,0.2f),
		D3DXVECTOR2(0.2f,0.2f),
		D3DXVECTOR2(0.3f,0.3f),
		D3DXVECTOR2(0.1f,0.1f),
		D3DXVECTOR2(0.1f,0.15f),
		D3DXVECTOR2(0.4f,0.1f),
		D3DXVECTOR2(0.08f,0.15f),
		D3DXVECTOR2(0.5f,0.5f),
	};
	const vector<D3DXVECTOR3> PENGUIN_POS =
	{
		D3DXVECTOR3(0.0f,0.0f,-350.0f),
		D3DXVECTOR3(-220.0f,0.0f,150.0f),
		D3DXVECTOR3(300.0f,0.0f,0.0f),
		D3DXVECTOR3(600.0f,0.0f,700.0f),
	};
	const vector<D3DXVECTOR3> PENGUIN_ROT =
	{
		D3DXVECTOR3(0.0f,0.0f,0.0f),
		D3DXVECTOR3(0.0f,D3DX_PI,0.0f),
		D3DXVECTOR3(0.0f,-0.8f * D3DX_PI,0.0f),
		D3DXVECTOR3(0.0f,0.2f * D3DX_PI,0.0f),
	};

	const float VIBRATION_POWER = 0.2f;	//�o�C�u�̋���
	const int VIBRATION_TIME = 20;	//�o�C�u�̎���
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CTitle::CTitle()
{
	m_nCntState = 0;
	m_nCntMove = 0;
	m_nStateLogo = 0;
	m_State = STATE_NONE;
	m_TitleState = TITLESTATE_ICEFLOW;
	m_Title_UI = TITLE_UI_LEFT;
	m_apMenu_UI = nullptr;
	m_bFade = false;
	m_bMove = false;

	for (int nCntUI = 0; nCntUI < TITLE_UI_MAX; nCntUI++)
	{
		m_apTitle_UI[nCntUI] = nullptr;
	}
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTitle::~CTitle()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CTitle::Init(void)
{
	const char* aPath =
	{// ���j���[�̃e�N�X�`���p�X
		"data\\TEXTURE\\TITLE\\Start.png",
	};

	const char* aTitle[TITLE_UI_MAX] =
	{// �^�C�g��UI�̃e�N�X�`���p�X
		"data\\TEXTURE\\TITLE\\ice_block_Left_2.png",
		"data\\TEXTURE\\TITLE\\ice_block_Right_2.png",
		"data\\TEXTURE\\TITLE\\ice_block.png",
		"data\\TEXTURE\\TITLE\\title_ice.png",
		"data\\TEXTURE\\TITLE\\penguin.png",
		"data\\TEXTURE\\TITLE\\title_full.png",
		"data\\TEXTURE\\TITLE\\turuhasi.png",
		"data\\TEXTURE\\TITLE\\pengui.png",
	};

	// �t�H�O�������Ȃ�
	CRenderer* pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->EnableFog(false);
	}

	// �T�E���h�C���X�^���X�̎擾
	CSound* pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		// BGM�̍Đ�
		pSound->Play(pSound->LABEL_BGM_TITLE);
	}
	else if (pSound == nullptr)
	{
		return E_FAIL;
	}

	// �J�����ʒu�̐ݒ�
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
		return E_FAIL;

	CCamera::Camera* pInfoCamera = pCamera->GetCamera();

	pInfoCamera->posV = { 45.38f,84.71f,270.10f };
	pInfoCamera->posR = { 0.0f,100.0f,0.0f };
	pInfoCamera->fLength = 1500.0f;

	// �Q�[���X�^�[�g�̃|���S���𐶐�
	if (m_apMenu_UI == nullptr)
	{
		m_apMenu_UI = CUI::Create();

		if (m_apMenu_UI != nullptr)
		{
			{//	�X�^�[�g���j���[
				// �|���S���̐ݒ�
				m_apMenu_UI->SetPosition(D3DXVECTOR3(0.5f, 0.75f, 0.0f));
				m_apMenu_UI->SetSize(0.2f, 0.15f);
				m_apMenu_UI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}

			// �e�N�X�`���̐ݒ�
			int nIdxTexture = CTexture::GetInstance()->Regist(aPath);

			m_apMenu_UI->SetIdxTexture(nIdxTexture);
			m_apMenu_UI->SetVtx();
		}
	}

	Camera::ChangeState(new CCameraStateTitle);

	for (int nCntUI = 0; nCntUI < TITLE_UI_MAX; nCntUI++)
	{// ���j���[���ڂ̃|���S���𐶐�
		if (m_apTitle_UI[nCntUI] == nullptr)
		{
			m_apTitle_UI[nCntUI] = CUI::Create();

			if (m_apTitle_UI[nCntUI] != nullptr)
			{
				m_apTitle_UI[nCntUI]->SetPosition(UI_POS[nCntUI]);

				if (nCntUI == TITLE_UI_LEFT)
				{//	�����炭��X
					m_apTitle_UI[nCntUI]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					m_aPosDest[nCntUI] = m_apTitle_UI[nCntUI]->GetPosition();
					m_aPosDest[nCntUI].x = 0.35f;
				}

				if (nCntUI == TITLE_UI_RIGHT)
				{//	�E���炭��X
					m_apTitle_UI[nCntUI]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					m_aPosDest[nCntUI] = m_apTitle_UI[nCntUI]->GetPosition();
					m_aPosDest[nCntUI].x = 0.6f;
				}

				if (nCntUI == TITLE_UI_ICEBLOCK)
				{//	�X�u���b�N����
					m_apTitle_UI[nCntUI]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
					m_aPosDest[nCntUI] = m_apTitle_UI[nCntUI]->GetPosition();
				}

				if (nCntUI == TITLE_UI_ICE)
				{//	�X
					m_apTitle_UI[nCntUI]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
					m_aPosDest[nCntUI] = m_apTitle_UI[nCntUI]->GetPosition();
				}

				if (nCntUI == TITLE_UI_PENGUIN)
				{//	�y���M��
					m_apTitle_UI[nCntUI]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
					m_aPosDest[nCntUI] = m_apTitle_UI[nCntUI]->GetPosition();
				}

				if (nCntUI == TITLE_UI_PICKAXE)
				{//	��͂�
					m_apTitle_UI[nCntUI]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					m_apTitle_UI[nCntUI]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
					m_aPosDest[nCntUI] = m_apTitle_UI[nCntUI]->GetPosition();
				}

				if (nCntUI == TITLE_UI_LOGO)
				{//	�^�C�g�����S
					m_apTitle_UI[nCntUI]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
					m_aPosDest[nCntUI] = m_apTitle_UI[nCntUI]->GetPosition();
				}

				if (nCntUI == TITLE_UI_FLASH)
				{//	�t���b�V��
					m_apTitle_UI[nCntUI]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
					m_aPosDest[nCntUI] = m_apTitle_UI[nCntUI]->GetPosition();
				}

				// �e�N�X�`���̐ݒ�
				int nIdxTexture = CTexture::GetInstance()->Regist(aTitle[nCntUI]);

				m_apTitle_UI[nCntUI]->SetSize(UI_SIZE[nCntUI].x, UI_SIZE[nCntUI].y);
				m_apTitle_UI[nCntUI]->SetIdxTexture(nIdxTexture);
				m_apTitle_UI[nCntUI]->SetVtx();
			}
		}
	}

	CInputManager::Create();
	CScene::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTitle::Uninit(void)
{
	// ���j���[���ڂ̔j��
	if (m_apMenu_UI != nullptr)
	{
		m_apMenu_UI->Uninit();

		m_apMenu_UI = nullptr;
	}

	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{// �^�C�g��UI�̔j��
		if (m_apTitle_UI[nCnt] != nullptr)
		{
			m_apTitle_UI[nCnt]->Uninit();

			m_apTitle_UI[nCnt] = nullptr;
		}
	}

	// �I�u�W�F�N�g�S�j��
	CObject::ReleaseAll();

	CScene::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CTitle::Update(void)
{
	switch (m_TitleState)
	{
	case CTitle::TITLESTATE_ICEFLOW:

		// �X������Ă����ԊǗ�
		IceFlowState();

		break;
	case CTitle::TITLESTATE_LOGO:

		// ���S���o���ē���������
		LogoState();

		// ����
		Input();

		break;
	case CTitle::TITLESTATE_PICKAXE:

		// ���S���o���ē���������
		LogoState();

		// �s�b�P���𓮂�������
		PickaxeState();

		break;
	default:
		break;
	}

	// �V�[���̍X�V
	CScene::Update();

	for (int nCntUI = 0; nCntUI < TITLE_UI_MAX; nCntUI++)
	{
		m_apTitle_UI[nCntUI]->SetVtx();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CTitle::Draw(void)
{
	CScene::Draw();
}

//=====================================================
// ���͏���
//=====================================================
void CTitle::Input(void)
{
	CInputManager* pInput = CInputManager::GetInstance();

	if (pInput == nullptr)
		return;

	CInputJoypad* pInputJoypad = CInputJoypad::GetInstance();

	if (pInputJoypad == nullptr)
		return;

	if (m_bFade == true)
	{
		if (pInput->GetTrigger(CInputManager::BUTTON_ENTER))	// ENTER�������Ƃ�
		{
			// joypad�U��������
			pInputJoypad->Vibration(0, VIBRATION_POWER, VIBRATION_TIME);

			// ���艹��炷
			CSound::GetInstance()->Play(CSound::LABEL_SE_DECISION);

			m_nCntState = 0;
			m_nStateLogo = 0;
			m_TitleState = TITLESTATE_PICKAXE;

			for (int nCntUI = 0; nCntUI < EFFECTMAX; nCntUI++)
			{
				float fmoveX = universal::RandRange(40, -40) * 0.1f;
				float fmoveY = universal::RandRange(40, -40) * 0.1f;
				CEffect2D* pEffect2D = CEffect2D::Create(D3DXVECTOR3(640.0f, 550.0f, 0.0f), 60.0f, 80, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(fmoveX, fmoveY, 0.0f));
				int nIdx = Texture::GetIdx(&PATH_TEX[0]);
				pEffect2D->SetIdxTexture(nIdx);
			}
		}
	}
}

//=====================================================
// �t�F�[�h����
//=====================================================
void CTitle::Fade(void)
{// �e��t�F�[�h
	CFade* pFade = CFade::GetInstance();

	if (pFade == nullptr)
		return;

	if (pFade->GetState() != CFade::FADE_NONE)
		return;

	pFade->SetFade(CScene::MODE_TUTORIAL);
}

//====================================================
// �X������Ă����ԏ���
//====================================================
void CTitle::IceFlowState(void)
{
	CInputManager* pInput = CInputManager::GetInstance();

	if (pInput == nullptr)
		return;

	// �X������Ă����Ԃ̎�
	D3DXVECTOR3 pos_left = m_apTitle_UI[TITLE_UI_LEFT]->GetPosition();
	D3DXVECTOR3 pos_right = m_apTitle_UI[TITLE_UI_RIGHT]->GetPosition();

	pos_left.x += 0.003f;
	pos_right.x -= 0.003f;

	// �ړI�̈ʒu�Ɍ��݂̈ʒu���߂���
	if (m_aPosDest[TITLE_UI_LEFT].x + 0.01f < pos_left.x)
	{
		// �X���������鏈��
		IceConnect(&pos_left, &pos_right);
	}
	if (pInput->GetTrigger(CInputManager::BUTTON_ENTER))
	{
		// ���艹��炷
		CSound::GetInstance()->Play(CSound::LABEL_SE_DECISION);

		// �X���������鏈��
		IceConnect(&pos_left, &pos_right);
	}

	m_apTitle_UI[TITLE_UI_LEFT]->SetPosition(pos_left);
	m_apTitle_UI[TITLE_UI_RIGHT]->SetPosition(pos_right);
}

//====================================================
// �X���������鏈��
//====================================================
void CTitle::IceConnect(D3DXVECTOR3* left, D3DXVECTOR3* right)
{
	*left = m_aPosDest[TITLE_UI_LEFT];	// ���݂̈ʒu�ɖڕW�̈ʒu������
	*right = m_aPosDest[TITLE_UI_RIGHT];

	m_apTitle_UI[TITLE_UI_LEFT]->SetAlpha(0.0f);	// �����x����
	m_apTitle_UI[TITLE_UI_RIGHT]->SetAlpha(0.0f);
	m_apTitle_UI[TITLE_UI_FLASH]->SetAlpha(1.0f);
	m_TitleState = TITLESTATE_LOGO;
}

//====================================================
// ���S���o���ē���������
//====================================================
void CTitle::LogoState(void)
{
	// ��ʂɃt���b�V���������ԂɂȂ�����
	m_nCntMove++;

	float fAlpha = m_apTitle_UI[TITLE_UI_FLASH]->GetAlpha();
	fAlpha -= 0.004f;
	m_bFade = true;

	for (int nCntUI = TITLE_UI_ICEBLOCK; nCntUI < TITLE_UI_PICKAXE; nCntUI++)
	{
		D3DXVECTOR3 pos = m_apTitle_UI[nCntUI]->GetPosition();

		// �|���S���𓮂���
		if (m_nCntMove > 0 && m_nCntMove < 40)
		{
			m_bMove = false;
		}

		if (m_nCntMove > 40 && m_nCntMove < 80)
		{
			m_bMove = true;
		}

		if (m_nCntMove > 79)
		{
			m_nCntMove = 0;
		}

		if (m_bMove == false)
		{
			pos.y += 0.0005f;
		}

		if (m_bMove == true)
		{
			pos.y -= 0.0005f;
		}

		m_apTitle_UI[nCntUI]->SetPosition(pos);
	}

	// �t���b�V���̈ʒu�Ɠ����x����
	m_apTitle_UI[TITLE_UI_FLASH]->SetPosition(D3DXVECTOR3(0.5f, 0.5f, 0.0f));
	m_apTitle_UI[TITLE_UI_FLASH]->SetAlpha(fAlpha);

	// UI�̓����x����
	m_apMenu_UI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apTitle_UI[TITLE_UI_ICEBLOCK]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apTitle_UI[TITLE_UI_ICE]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apTitle_UI[TITLE_UI_PENGUIN]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apTitle_UI[TITLE_UI_PICKAXE]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apTitle_UI[TITLE_UI_LOGO]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//====================================================
// �s�b�P������������
//====================================================
void CTitle::PickaxeState(void)
{
	D3DXVECTOR3 rot = m_apTitle_UI[TITLE_UI_PICKAXE]->GetRotation();

	m_apTitle_UI[TITLE_UI_FLASH]->SetAlpha(0.0f);	// �����x��0�ɂ���

	rot.z += 0.07f;	// ��͂��̌������X����

	m_nStateLogo++;

	if (rot.z > 0.5f)
	{
		rot.z = 0.5f;
	}

	m_apMenu_UI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �X�^�[�g���S�̓����x��0�ɂ���

	m_apTitle_UI[TITLE_UI_PICKAXE]->SetRotation(rot);

	if (m_bFade == true)
	{
		m_nCntState++;

		if (m_nCntState > 70)
		{
			// �t�F�[�h����
			Fade();
		}
	}
}
