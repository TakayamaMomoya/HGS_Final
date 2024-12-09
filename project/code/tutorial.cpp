//*****************************************************
//
// �`���[�g���A������[tutorial.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "tutorial.h"
#include "camera.h"
#include "cameraState.h"
#include "inputManager.h"
#include "game.h"
#include "gameManager.h"
#include "playerTutorial.h"
#include "debugproc.h"
#include "manager.h"
#include "fade.h"
#include "fade2D.h"
#include "texture.h"
#include "gauge.h"
#include "UI.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
//------------------------------
// �X�e�[�W�̒萔
//------------------------------
namespace stage
{
const string PATH_MAP = "data\\TEXT\\ice_stage_tutorial.txt";	// �}�b�v�̃p�X
const int SIZE_MAP = 15;										// �}�b�v�̃T�C�Y
}

//------------------------------
// ��Ԃ̒萔
//------------------------------
namespace state
{
const float TIME_END = 1.0f;	// �I���̗P�\
}

//------------------------------
// �`�F�b�N�}�[�N�̒萔
//------------------------------
namespace check
{
const string PATH_TEX = "data\\TEXTURE\\UI\\CheckMark.png";		// �e�N�X�`���p�X
const float WIDTH = 0.05f;										// ��
const float HEIGHT = 0.086f;									// ����
const D3DXVECTOR3 OFFSET = { WIDTH,-HEIGHT,0.0f };	// �I�t�Z�b�g
}

//------------------------------
// �L���v�V�����̒萔
//------------------------------
namespace caption
{
const float WIDTH = 0.3f;								// ��
const float HEIGHT = 0.1f;								// ����
const D3DXVECTOR3 POS_INIT = { 0.5f,0.114f,0.0f };		// �ʒu
const float TIME_FADE = 2.0f;							// �t�F�[�h�ɂ����鎞��
const string PATH_TEX[CTutorial::E_State::STATE_MAX] =	// �e�N�X�`���p�X
{
	"",												// ���ł��Ȃ����
	"data\\TEXTURE\\UI\\tutorial_move.png",			// �ړ����
	"data\\TEXTURE\\UI\\tutorial_piston.png",		// �˂������
	"data\\TEXTURE\\UI\\tutorial_pistonice.png",	// �X����
	"data\\TEXTURE\\UI\\tutorial_separate.png",		// �j�����
	"data\\TEXTURE\\UI\\tutorial_jump.png",			// �W�����v
	"data\\TEXTURE\\UI\\tutorial_enemy.png",		// �G����
	"data\\TEXTURE\\UI\\tutorial_albatross.png",	// �A�z�E�h��
	"",												// �I�����
};
const string PATH_TEX_ENEMY = "data\\TEXTURE\\UI\\tutorial_rival.png";	// �}���`�p�̓G�����p�X
const D3DXVECTOR2 SIZE[CTutorial::E_State::STATE_MAX] =	// �T�C�Y
{
	{ 0.0f,0.0f },	// ���ł��Ȃ����
	{ 0.2f,0.1f },	// �ړ����
	{ 0.2f,0.1f },	// �˂������
	{ 0.2f,0.1f },	// �X����
	{ 0.2f,0.1f },	// �j�����
	{ 0.15f,0.1f },	// �W�����v
	{ 0.17f,0.1f },	// �G����
	{ 0.15f,0.1f },	// �A�z�E�h��
	{ 0.0f,0.0f },	// �I�����
};
}

//------------------------------
// �Q�[�W�̒萔
//------------------------------
namespace gauge
{
const float TIME_SKIP = 3.0f;				// �X�L�b�v�ɂ����鎞��
const D3DXVECTOR3 POS = { 0.85f,0.9f,0.0f };	// �ʒu
}

//------------------------------
// �q���g�̒萔
//------------------------------
namespace hint
{
const float WIDTH = 0.1f;											// ��
const float HEIGTH = 0.05f;											// ����
const string PATH_TRYIT = "data\\TEXTURE\\UI\\tutorialtryit.png";	// ����Ă݂悤�̃e�N�X�`���p�X
const string PATH_SKIP = "data\\TEXTURE\\UI\\tutorialskip.png";		// �X�L�b�v�̃e�N�X�`���p�X
D3DXVECTOR3 POS = { 0.85f,0.15f,0.0f };								// �ʒu
const bool FRAG_TRY[CTutorial::E_State::STATE_MAX] =				// ����Ă݂悤�t���O
{
	false,	// ���ł��Ȃ����
	true,	// �ړ����
	true,	// �˂������
	false,	// �X����
	false,	// �j�����
	true,	// �W�����v
	false,	// �G����
	false,	// �A�z�E�h��
	false,	// �I�����
};
}

const string PATH_TEMP_FRAG = "data\\TEMP\\tutorialfrag.bin";	// �`���[�g���A���t���O�̕ۑ��p�X
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CTutorial::FuncUpdateState CTutorial::s_aFuncUpdateState[] =	// ��ԍX�V�֐�
{
	nullptr,					// ���ł��Ȃ����
	nullptr,					// �ړ����
	nullptr,					// �˂������
	nullptr,					// �X����
	nullptr,					// �j�����
	nullptr,					// �W�����v
	nullptr,					// �G����
	nullptr,					// �A�z�E�h������
	&CTutorial::UpdateEnd,		// �I�����
};

CTutorial *CTutorial::s_pTutorial = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CTutorial::CTutorial() : m_state(E_State::STATE_NONE), m_fTimeEnd(0.0f) , m_nCntProgress(0), m_pUIPlayer(nullptr), m_abComplete(),
m_pCaption(nullptr), m_pFadeCaption(nullptr), m_pGaugeSkip(nullptr), m_fTimerSkip(0.0f), m_pHint(nullptr),m_pFadeHint(nullptr)
{
	s_pTutorial = this;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTutorial::~CTutorial()
{
	s_pTutorial = nullptr;
}

//=====================================================
// ����������
//=====================================================
HRESULT CTutorial::Init(void)
{
	// �V�[���̏�����
	if (FAILED(CScene::Init()))
	{ // �������Ɏ��s�����ꍇ

		return E_FAIL;
	}

	// �J�����̐ݒ�
	Camera::ChangeState(new CFollowPlayer);

	// ��Ԃ̏�����
	m_state = E_State::STATE_MOVE;

	//--------------------------------
	// �v���C���[�̐���
	//--------------------------------
	CPlayerTutorial *pPlayer = CPlayerTutorial::Create();

	//--------------------------------
	// �L���v�V�����̐���
	//--------------------------------
	m_pCaption = CUI::Create();
	
	if (m_pCaption == nullptr)
		return E_FAIL;

	m_pCaption->SetSize(caption::SIZE[E_State::STATE_MOVE].x, caption::SIZE[E_State::STATE_MOVE].y);
	m_pCaption->SetPosition(caption::POS_INIT);
	m_pCaption->SetVtx();

	int nIdxTexture = Texture::GetIdx(&caption::PATH_TEX[E_State::STATE_MOVE][0]);
	m_pCaption->SetIdxTexture(nIdxTexture);

	m_pFadeCaption = CFade2D::Create(m_pCaption, caption::TIME_FADE);

	if (m_pFadeCaption != nullptr)
	{
		m_pFadeCaption->EnableBouceOut(true);
		m_pFadeCaption->SetState(CFade2D::E_State::STATE_IN);
	}

	//--------------------------------
	// �q���g�̐���
	//--------------------------------
	m_pHint = CUI::Create();

	if (m_pHint == nullptr)
		return E_FAIL;

	m_pHint->SetSize(hint::WIDTH, hint::HEIGTH);
	m_pHint->SetPosition(hint::POS);
	m_pHint->SetVtx();

	nIdxTexture = Texture::GetIdx(&hint::PATH_TRYIT[0]);
	m_pHint->SetIdxTexture(nIdxTexture);

	m_pFadeHint = CFade2D::Create(m_pHint, caption::TIME_FADE);

	if (m_pFadeHint != nullptr)
	{
		m_pFadeHint->EnableBouceOut(true);
		m_pFadeHint->SetState(CFade2D::E_State::STATE_IN);
	}

	// �Q�[�W�̐���
	m_pGaugeSkip = CGauge::Create(gauge::TIME_SKIP);

	if (m_pGaugeSkip == nullptr)
		return E_FAIL;

	m_pGaugeSkip->SetPosition(gauge::POS);

	// �`���[�g���A���t���O�����Z�b�g
	tutorial::SaveFrag(false);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTutorial::Uninit(void)
{
	Object::DeleteObject((CObject**)&m_pUIPlayer);
	Object::DeleteObject((CObject**)&m_pCaption);
	Object::DeleteObject((CObject**)&m_pFadeCaption);

	// �V�[���̏I��
	CScene::Uninit();

	// �I�u�W�F�N�g�S�j��
	CObject::ReleaseAll();
}

//=====================================================
// �X�V����
//=====================================================
void CTutorial::Update(void)
{
	assert(m_state > -1 && m_state < STATE_MAX);
	if (s_aFuncUpdateState[m_state] != nullptr)
	{ // �X�V�֐����w�肳��Ă���ꍇ

		// �e��Ԃ��Ƃ̍X�V
		(this->*(s_aFuncUpdateState[m_state]))();
	}

	// ��Ԃ��i�ނ��̊m�F�����鏈��
	CheckProgress();

	// �X�L�b�v�̓���
	InputSkip();

	// �V�[���̍X�V
	CScene::Update();

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// �I����Ԃ̍X�V
//=====================================================
void CTutorial::UpdateEnd(void)
{
	m_fTimeEnd += CManager::GetDeltaTime();

	if (m_fTimeEnd > state::TIME_END)
	{
		// ��莞�Ԍo�߂Ńt�F�[�h����
		CFade *pFade = CFade::GetInstance();
		if (pFade == nullptr)
			return;

		pFade->SetFade(CScene::MODE::MODE_GAME);
	}
}

//=====================================================
// �i�s����
//=====================================================
void CTutorial::CheckProgress(void)
{
	int nNumPlayer = CPlayer::GetNumPlayer();

	if (m_nCntProgress == nNumPlayer)
	{// �v���C���[�Ɛi�s�J�E���^�[����v������i�s
		ProgressState();
	}
}

//=====================================================
// �i�s�J�E���^�[���Z
//=====================================================
void CTutorial::AddCntProgress(CPlayer *pPlayer)
{
	if (m_pFadeCaption != nullptr)
	{
		if (m_pFadeCaption->GetState() != CFade2D::E_State::STATE_NONE)
			return;
	}

	// �Ή�����ID�̃A�C�R�����擾
	int nID = pPlayer->GetID();

	if (m_abComplete[nID])
		return;	// ���Ɋ������Ă�����ʂ�Ȃ�

	m_abComplete[nID] = true;

	// �i�s�J�E���^�[���Z
	m_nCntProgress++;
}

//=====================================================
// �X�L�b�v�̓���
//=====================================================
void CTutorial::InputSkip(void)
{
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager == nullptr)
		return;

	if (pInputManager->GetPress(CInputManager::BUTTON_SKIP))
	{
		float fDeltaTime = CManager::GetDeltaTime();

		m_fTimerSkip += fDeltaTime;

		if (m_fTimerSkip >= gauge::TIME_SKIP)
		{// ��莞�Ԓ������Ń^�C�g���ɑJ��
			m_fTimerSkip = gauge::TIME_SKIP;

			CFade *pFade = CFade::GetInstance();

			if (pFade != nullptr)
				pFade->SetFade(CScene::MODE_GAME);
		}
	}
	else
	{
		if (m_fTimerSkip < gauge::TIME_SKIP)
		{
			m_fTimerSkip = 0;
		}
	}

	if (m_pGaugeSkip != nullptr)
		m_pGaugeSkip->SetParam(m_fTimerSkip);
}

//=====================================================
// ��Ԃ�i�߂鏈��
//=====================================================
void CTutorial::ProgressState(void)
{
	// ��Ԃ�i�߂�
	m_state = (E_State)(m_state + 1);

	if (m_state == E_State::STATE_ALBATROSS)
		int n = 0;

	// �J�E���^�[�̃��Z�b�g
	m_nCntProgress = 0;

	if (m_pFadeCaption != nullptr)
	{// �L���v�V�����̃t�F�[�h�ݒ�
		// �t�F�[�h�A�E�g�ɂ��āA���̏���ݒ�
		m_pFadeCaption->SetState(CFade2D::E_State::STATE_OUT);
		m_pFadeCaption->SetPathNext(caption::PATH_TEX[m_state]);
		m_pFadeCaption->SetSizeNext(caption::SIZE[m_state]);

		if (m_state == E_State::STATE_EXPLAIN_ENEMY)
		{// �}���`�v���C�p�̃e�N�X�`������
			if (CPlayer::GetNumPlayer() > 1)
				m_pFadeCaption->SetPathNext(caption::PATH_TEX_ENEMY);
		}
	}

	if (m_pFadeHint != nullptr)
	{// �L���v�V�����̃t�F�[�h�ݒ�
		// �t�F�[�h�A�E�g�ɂ��āA���̏���ݒ�
		m_pFadeHint->SetState(CFade2D::E_State::STATE_OUT);

		if(hint::FRAG_TRY[m_state])
			m_pFadeHint->SetPathNext(hint::PATH_TRYIT);
		else
			m_pFadeHint->SetPathNext(hint::PATH_SKIP);
	}

	// �����t���O���Z�b�g
	for (int i = 0; i < NUM_PLAYER; i++)
		m_abComplete[i] = false;
}

//=====================================================
// �`�揈��
//=====================================================
void CTutorial::Draw(void)
{
	// �V�[���̕`��
	CScene::Draw();
}

//=====================================================
// �f�o�b�O����
//=====================================================
void CTutorial::Debug(void)
{
	CDebugProc *pDebugProc = CDebugProc::GetInstance();
	CInputManager *pInputMgr = CInputManager::GetInstance();

	if (pDebugProc == nullptr || pInputMgr == nullptr)
		return;

	pDebugProc->Print("\n�`���[�g���A�����========================================");
	pDebugProc->Print("\n���[%d]", m_state);
	pDebugProc->Print("\n�J�E���^�[[%d]", m_nCntProgress);
}

namespace tutorial
{
// �t���O�̃Z�[�u
void SaveFrag(bool bValue)
{
	// �t�@�C�����J��
	std::ofstream outputFile(PATH_TEMP_FRAG, std::ios::binary);

	if (!outputFile.is_open())
		assert(false);

	// �f�[�^�̕ۑ�
	outputFile.write(reinterpret_cast<char*>(&bValue), sizeof(bool));

	outputFile.close();
}

// �t���O�̃��[�h
bool LoadFrag(void)
{
	// �t�@�C�����J��
	std::ifstream inputFile(PATH_TEMP_FRAG, std::ios::binary);

	if (!inputFile.is_open())
		assert(false);

	bool bFrag;

	inputFile.read(reinterpret_cast<char*>(&bFrag), sizeof(bool));

	inputFile.close();

	return bFrag;
}
}