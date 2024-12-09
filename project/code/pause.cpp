//*****************************************************
//
// �|�[�Y�̏���[pause.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "pause.h"
#include "manager.h"
#include "polygon2D.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "inputManager.h"
#include "texture.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "UI.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MENU_WIDTH	(0.11f)	// ���ڂ̕�
#define MENU_HEIGHT	(0.18f)	// ���ڂ̍���
#define MOVE_FACT	(0.08f)	// �ړ����x
#define LINE_ARRIVAL	(0.05f)	// ���������Ƃ���邵�����l
#define LINE_UNINIT	(0.2f)	// �I������܂ł̂������l
#define SPEED_FADE	(0.03f)	// �w�i�̃t�F�[�h���x
#define ALPHA_BG	(0.5f)	// �w�i�̕s�����x

//====================================================
// �R���X�g���N�^
//====================================================
CPause::CPause()
{
	m_menu = MENU_RESUME;
	m_state = STATE_NONE;
	ZeroMemory(&m_apMenu[MENU_RESUME], sizeof(m_apMenu));
	ZeroMemory(&m_aPosDest[MENU_RESUME], sizeof(D3DXVECTOR3) * MENU_MAX);
	m_bSound = false;
	nCountMove = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CPause::~CPause()
{

}

//====================================================
// ��������
//====================================================
CPause *CPause::Create(void)
{
	CPause *pPause = nullptr;

	pPause = new CPause;

	if (pPause != nullptr)
	{
		pPause->Init();
	}

	return pPause;
}

//====================================================
// ����������
//====================================================
HRESULT CPause::Init(void)
{
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		// �Q�[�����~����
		pGame->EnableStop(true);

		CSound* pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(pSound->LABEL_SE_PAUSE_MENU);
		}
	}

	// �w�i�̐���
	m_pBg = CUI::Create();

	if (m_pBg != nullptr)
	{
		m_pBg->SetPosition(D3DXVECTOR3(0.5f, 0.5f, 0.0f));

		m_pBg->SetSize(0.5f, 0.5f);

		m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

		m_pBg->SetVtx();
	}

	char *pPath[MENU_MAX] = 
	{// ���j���[���ڂ̃p�X
		"data\\TEXTURE\\UI\\Resume.png",
		"data\\TEXTURE\\UI\\Restart.png",
		"data\\TEXTURE\\UI\\Quit.png",
		"data\\TEXTURE\\UI\\pause.png",
	};

	int nIdxTexture;

	for (int nCntMenu = 0; nCntMenu < MENU_MAX; nCntMenu++)
	{// ���j���[���ڂ̃|���S���𐶐�
		if (m_apMenu[nCntMenu] == nullptr)
		{
			m_apMenu[nCntMenu] = CUI::Create();

			if (m_apMenu[nCntMenu] != nullptr)
			{
				if (nCntMenu == MENU_RESUME)
				{//	�Q�[���ɖ߂�
					// �|���S���̐ݒ�
					m_apMenu[nCntMenu]->SetPosition(D3DXVECTOR3(-2.5f, 0.45f + MENU_HEIGHT * nCntMenu, 0.0f));
					m_apMenu[nCntMenu]->SetSize(MENU_WIDTH, MENU_HEIGHT);
					m_apMenu[nCntMenu]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
					m_aPosDest[nCntMenu] = m_apMenu[nCntMenu]->GetPosition();
					m_aPosDest[nCntMenu].x = 0.35f;
				}

				else if (nCntMenu == MENU_RESTART)
				{//	�Q�[���̃��X�^�[�g
					// �|���S���̐ݒ�
					m_apMenu[nCntMenu]->SetPosition(D3DXVECTOR3(2.5f, 0.45f + MENU_HEIGHT * nCntMenu, 0.0f));
					m_apMenu[nCntMenu]->SetSize(MENU_WIDTH, MENU_HEIGHT);
					m_apMenu[nCntMenu]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
					m_aPosDest[nCntMenu] = m_apMenu[nCntMenu]->GetPosition();
					m_aPosDest[nCntMenu].x = 0.65f;
				}

				else if (nCntMenu == MENU_QUIT)
				{//	�^�C�g���ɖ߂�
					// �|���S���̐ݒ�
					m_apMenu[nCntMenu]->SetPosition(D3DXVECTOR3(-2.5f, 0.45f + MENU_HEIGHT * nCntMenu, 0.0f));
					m_apMenu[nCntMenu]->SetSize(MENU_WIDTH, MENU_HEIGHT);
					m_apMenu[nCntMenu]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
					m_aPosDest[nCntMenu] = m_apMenu[nCntMenu]->GetPosition();
					m_aPosDest[nCntMenu].x = 0.35f;
				}

				else if (nCntMenu == MENU_PAUSE)
				{//	�|�[�Y
					// �|���S���̐ݒ�
					m_apMenu[nCntMenu]->SetPosition(D3DXVECTOR3(2.5f, 0.12f, 0.0f));
					m_apMenu[nCntMenu]->SetSize(MENU_WIDTH + 0.1f, MENU_HEIGHT - 0.05f);
					m_apMenu[nCntMenu]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					m_aPosDest[nCntMenu] = m_apMenu[nCntMenu]->GetPosition();
					m_aPosDest[nCntMenu].x = 0.5f;
				}

				// �e�N�X�`���̐ݒ�
				nIdxTexture = CTexture::GetInstance()->Regist(pPath[nCntMenu]);

				m_apMenu[nCntMenu]->SetIdxTexture(nIdxTexture);
				m_apMenu[nCntMenu]->SetVtx();
			}
		}
	}

	m_state = STATE_IN;

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CPause::Uninit(void)
{
	if (m_pBg != nullptr)
	{// �w�i�|���S���̔j��
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{// ���j���[���ڂ̔j��
		if (m_apMenu[nCnt] != nullptr)
		{
			m_apMenu[nCnt]->Uninit();

			m_apMenu[nCnt] = nullptr;
		}
	}

	// �Q�[�����ĊJ����
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		pGame->EnableStop(false);
		pGame->ReleasePause();
	}

	// ���g�̔j��
	Release();
}

//====================================================
// �X�V����
//====================================================
void CPause::Update(void)
{
	// ��ԊǗ�
	ManageState();
}

//====================================================
// ��ԊǗ�
//====================================================
void CPause::ManageState(void)
{
	if (m_state != STATE_OUT)
	{
		Input();
	}
	
	// �w�i�̊Ǘ�
	ManageBg();

	// �I���t���O�p
	int nEnd = 0;

	// �|���S����ڕW�ʒu�Ɍ����킹��
	for (int nCntMenu = 0; nCntMenu < MENU_MAX; nCntMenu++)
	{
		if (m_apMenu[nCntMenu] != nullptr)
		{
			D3DXVECTOR3 pos = m_apMenu[nCntMenu]->GetPosition();
			D3DXVECTOR3 posOld = pos;
			D3DXVECTOR3 vecDiff = m_aPosDest[nCntMenu] - pos;
			float fDiffOld = vecDiff.x;

			vecDiff *= MOVE_FACT;
			vecDiff += pos;

			m_apMenu[nCntMenu]->SetPosition(vecDiff);
			m_apMenu[nCntMenu]->SetVtx();

			float fDiff = m_aPosDest[nCntMenu].x - vecDiff.x;

			if (fDiff * fDiff < LINE_UNINIT * LINE_UNINIT &&
				m_state == STATE_OUT)
			{// �I���̃��C��
				nEnd++;
			}
		}
	}

	if (nEnd == MENU_MAX &&
		m_state == STATE_OUT)
	{
		Uninit();
		return;
	}
}

//====================================================
// �w�i�̊Ǘ�
//====================================================
void CPause::ManageBg(void)
{
	if (m_pBg == nullptr)
		return;

	D3DXCOLOR col = m_pBg->GetCol();

	switch (m_state)
	{
	case CPause::STATE_IN:

		col.a += SPEED_FADE;

		if (col.a >= ALPHA_BG)
		{
			col.a = ALPHA_BG;

			m_state = STATE_NONE;
		}

		break;
	case CPause::STATE_OUT:

		col.a -= SPEED_FADE;

		if (col.a <= 0.0f)
		{
			col.a = 0.0f;
		}

		break;
	default:
		break;
	}

	m_pBg->SetCol(col);
}

//====================================================
// ���쏈��
//====================================================
void CPause::Input(void)
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
		{
			return;
		}
	}

	if (pInputManager == nullptr)
	{
		return;
	}
	
	if ((pInputManager->GetTrigger(CInputManager::BUTTON_PAUSE) || 
		pInputManager->GetTrigger(CInputManager::BUTTON_BACK)) && 
		m_state == STATE::STATE_NONE)
	{
		m_state = STATE_OUT;

		//	��ʊO�ڕW��ݒ�
		OffPosition();
		return;
	}

	if (m_apMenu[m_menu] != nullptr)
	{// �ȑO�ɑI�����Ă����ڂ��I��F�ɂ���
		m_apMenu[m_menu]->SetCol(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f));
	}

	// ���ڐ؂�ւ�
	if (pInputManager->GetTrigger(CInputManager::BUTTON_AXIS_DOWN))
	{
		nCountMove = 0;
		m_menu = (MENU)((m_menu + 1) % 3);

		if (pSound != nullptr && m_bSound == false)
		{
			pSound->Play(CSound::LABEL_SE_SELECT);

			m_bSound = true;
		}
	}

	if (pInputManager->GetTrigger(CInputManager::BUTTON_AXIS_UP))
	{
		nCountMove = 0;
		m_menu = (MENU)((m_menu + 3 - 1) % 3);
		
		if (pSound != nullptr && m_bSound == false)
		{
			pSound->Play(CSound::LABEL_SE_SELECT);

			m_bSound = true;
		}
	}

	if (m_apMenu[m_menu] != nullptr)
	{// �I�����Ă��鍀�ڂ̐F�ύX
		m_apMenu[m_menu]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
	{// �I�����ڂɃt�F�[�h����
		if (pSound != nullptr)
		{
			pSound->Play(CSound::LABEL_SE_DECISION);
		}

		Fade(m_menu);
	}

	//	�I����������UI����������
	SelectMove();
}

//====================================================
// �t�F�[�h���鏈��
//====================================================
void CPause::Fade(MENU menu)
{
	CFade *pFade = CFade::GetInstance();

	if (pFade == nullptr)
	{
		return;
	}

	switch (menu)
	{
	case CPause::MENU_RESUME:

		//	��ʊO�ڕW��ݒ�
		OffPosition();

		m_state = STATE_OUT;

		break;
	case CPause::MENU_RESTART:

		CGame::SetState(CGame::STATE_END);
		pFade->SetFade(CScene::MODE_GAME);

		break;
	case CPause::MENU_QUIT:
	{
		pFade->SetFade(CScene::MODE_TITLE);
	}
		break;
	default:
		break;
	}
}

//====================================================
// ��ʊO�ڕW�ݒ菈��
//====================================================
void CPause::OffPosition(void)
{
	for (int nCntMenu = 0; nCntMenu < MENU_MAX; nCntMenu++)
	{//	��ʊO�̖ڕW��ݒ�	
		if (m_apMenu[nCntMenu] != nullptr)
		{
			if (nCntMenu == MENU_RESUME)
			{
				m_aPosDest[nCntMenu].x = -0.25f;
			}

			else if (nCntMenu == MENU_RESTART)
			{
				m_aPosDest[nCntMenu].x = 1.25f;
			}

			else if (nCntMenu == MENU_QUIT)
			{
				m_aPosDest[nCntMenu].x = -0.25f;
			}

			else if (nCntMenu == MENU_PAUSE)
			{
				m_aPosDest[nCntMenu].y = -0.25f;
			}
		}
	}
}

//====================================================
// �I����������UI����������
//====================================================
void CPause::SelectMove(void)
{
	if (m_apMenu[m_menu] == nullptr)
		return;

	D3DXVECTOR3 pos = m_apMenu[m_menu]->GetPosition();
	nCountMove++;

	//	�Q�[���ɖ߂�
	if (m_menu == MENU_RESUME)
	{
		//	�ق��̍��ڂ������l�ɖ߂�
		if (m_aPosDest[MENU_RESTART].x < 0.65f)
		{
			m_aPosDest[MENU_RESTART].x += 0.001f;
		}

		else if (m_aPosDest[MENU_RESTART].x > 0.65f)
		{
			m_aPosDest[MENU_RESTART].x -= 0.001f;
		}

		if (m_aPosDest[MENU_QUIT].x < 0.35f)
		{
			m_aPosDest[MENU_QUIT].x += 0.001f;
		}

		else if (m_aPosDest[MENU_QUIT].x > 0.35f)
		{
			m_aPosDest[MENU_QUIT].x -= 0.001f;
		}
	}

	// ���X�^�[�g
	else if (m_menu == MENU_RESTART)
	{
		//	�ق��̍��ڂ������l�ɖ߂�
		if (m_aPosDest[MENU_RESUME].x < 0.35f)
		{
			m_aPosDest[MENU_RESUME].x += 0.001f;
		}

		else if (m_aPosDest[MENU_RESUME].x > 0.35f)
		{
			m_aPosDest[MENU_RESUME].x -= 0.001f;
		}

		if (m_aPosDest[MENU_QUIT].x < 0.35f)
		{
			m_aPosDest[MENU_QUIT].x += 0.001f;
		}

		else if (m_aPosDest[MENU_QUIT].x > 0.35f)
		{
			m_aPosDest[MENU_QUIT].x -= 0.001f;
		}
	}

	// �^�C�g���ɖ߂�
	else if (m_menu == MENU_QUIT)
	{
		//	�ق��̍��ڂ������l�ɖ߂�
		if (m_aPosDest[MENU_RESUME].x < 0.35f)
		{
			m_aPosDest[MENU_RESUME].x += 0.001f;
		}

		else if (m_aPosDest[MENU_RESUME].x > 0.35f)
		{
			m_aPosDest[MENU_RESUME].x -= 0.001f;
		}

		if (m_aPosDest[MENU_RESTART].x < 0.65f)
		{
			m_aPosDest[MENU_RESTART].x += 0.001f;
		}

		else if (m_aPosDest[MENU_RESTART].x > 0.65f)
		{
			m_aPosDest[MENU_RESTART].x -= 0.001f;
		}
	}

	// �|���S�����J�E���g���Ƃɓ�����
	if (nCountMove > 0 && nCountMove < 100)
	{
		m_aPosDest[m_menu].x += 0.001f;
	}

	else if (nCountMove > 100 && nCountMove < 300)
	{
		m_aPosDest[m_menu].x -= 0.001f;
	}

	else if (nCountMove > 300 && nCountMove < 500)
	{
		m_aPosDest[m_menu].x += 0.001f;
	}

	else if (nCountMove > 500)
	{
		nCountMove = 100;
	}

	m_apMenu[m_menu]->SetPosition(pos);
	m_apMenu[m_menu]->SetVtx();
}

//====================================================
// �`�揈��
//====================================================
void CPause::Draw(void)
{

}
