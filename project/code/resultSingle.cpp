//*****************************************************
//
// �V���O�����U���g�̏���[resultSingle.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "resultSingle.h"
#include "resultSingleWin.h"
#include "resultSingleLose.h"
#include "manager.h"
#include "ui.h"
#include "inputManager.h"
#include "texture.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "timer.h"
#include "ranking.h"
#include "camera.h"
#include "cameraState.h"
#include "debugproc.h"
#include "player.h"
#include "gameManager.h"
#include "resultMultiTimeUp.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
namespace bg
{
const float WIDTH = 0.5f;	// ��
const float HEIGHT = 0.5f;	// ����
const D3DXCOLOR INIT_COL = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �����̐F
const float DEST_ALPHA = 0.5f;	// �ڕW�F
const float DIFF_ALPHA = DEST_ALPHA - INIT_COL.a;			// �����A���t�@�l
const D3DXVECTOR3 POS = D3DXVECTOR3(0.5f, 0.5f, 0.0f);	// �ʒu
const float TIME_FADE = 0.9f;	// �t�F�[�h�ɂ����鎞��
}

namespace caption
{
const char* PATH[CResultSingle::RESULT_MAX] =
{																		// �p�X
	"data\\TEXTURE\\UI\\stage_clear.png",	// ����
	"data\\TEXTURE\\UI\\gameover.png",		// ���S
	"data\\TEXTURE\\UI\\timeover.png",		// �^�C���I�[�o�[
};
const float	MOVE_TIME = 0.6f;											// �ړ�����
const D3DXCOLOR DEST_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// �ڕW�F
const D3DXCOLOR INIT_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);			// �����F
const D3DXCOLOR DIFF_COL = DEST_COL - INIT_COL;							// �����F
const D3DXVECTOR3 DEST_POS = D3DXVECTOR3(0.5f, 0.5f, 0.0f);			// �ڕW�ʒu
const D3DXVECTOR3 INIT_POS = DEST_POS + D3DXVECTOR3(0.0f, 0.2f, 0.0f);	// �����ʒu
const D3DXVECTOR3 DIFF_POS = DEST_POS - INIT_POS;						// �����ʒu
const float WIDTH = 0.27f;	// ��
const float HEIGHT = 0.12f;	// ����
}
}

//*****************************************************
// �ÓI�����o�ϐ�
//*****************************************************
CResultSingle::FuncUpdateState CResultSingle::s_aFuncUpdateState[] =	// ��ԍX�V�֐�
{
	nullptr,							// �������Ȃ��X�V
	&CResultSingle::UpdateFade,			// �t�F�[�h��Ԃ̍X�V
	&CResultSingle::UpdateApperCaption,	// �L���v�V�����o����Ԃ̍X�V
	nullptr,							// �L���v�V�����o���I����Ԃ̍X�V
	nullptr,							// �I����Ԃ̍X�V
};

//====================================================
// �R���X�g���N�^
//====================================================
CResultSingle::CResultSingle() : m_fTimer(0.0f),m_pCaption(nullptr), m_result(RESULT_WIN)
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CResultSingle::~CResultSingle()
{

}

//====================================================
// ��������
//====================================================
CResultSingle *CResultSingle::Create(E_Result result)
{
	if (CGame::GetState() != CGame::E_State::STATE_NORMAL)
		return nullptr;

	CResultSingle *pResult = nullptr;
	
	if(result == RESULT_WIN)
		pResult = new CResultSingleWin;		// �����̃��U���g
	else 
		pResult = new CResultSingleLose;	// �s�k�̃��U���g

	if (pResult != nullptr)
	{
		pResult->m_result = result;
		pResult->Init();
	}

	return pResult;
}

//====================================================
// ����������
//====================================================
HRESULT CResultSingle::Init(void)
{
	// �Q�[����ʂ����U���g��Ԃɂ���
	CGame::SetState(CGame::E_State::STATE_RESULT);

	CSound* pSound = CSound::GetInstance();	// �T�E���h���
	assert(pSound != nullptr);

	// �T�E���h�̍Đ�
	pSound->Stop();
	pSound->Play(CSound::LABEL_BGM_RESULT);

	// 2D�I�u�W�F�N�g�̐���
	Create2D();

	// �v���C���[�𑀍�s�\�ɂ���
	CPlayer::EnableInputAll(false);

	return S_OK;
}

//====================================================
// 2D�I�u�W�F�N�g�̐���
//====================================================
void CResultSingle::Create2D(void)
{
	// �w�i�̐���
	CreateBg();

	// ���o���̐���
	CreateCaption();
}

//====================================================
// ���o���̐���
//====================================================
void CResultSingle::CreateCaption(void)
{
	m_pCaption = CUI::Create();

	if (m_pCaption == nullptr)
		return;

	m_pCaption->SetSize(caption::WIDTH, caption::HEIGHT);
	m_pCaption->SetPosition(caption::INIT_POS);
	m_pCaption->SetCol(caption::INIT_COL);
	m_pCaption->SetVtx();

	int nIdxTexture = Texture::GetIdx(caption::PATH[m_result]);
	m_pCaption->SetIdxTexture(nIdxTexture);
}

//====================================================
// �w�i�̐���
//====================================================
void CResultSingle::CreateBg(void)
{
	m_pBg = CUI::Create();

	if (m_pBg == nullptr)
		return;

	m_pBg->SetSize(bg::WIDTH, bg::HEIGHT);
	m_pBg->SetPosition(bg::POS);
	m_pBg->SetCol(bg::INIT_COL);
	m_pBg->SetVtx();
}

//====================================================
// �I������
//====================================================
void CResultSingle::Uninit(void)
{
	Object::DeleteObject((CObject**)&m_pBg);
	Object::DeleteObject((CObject**)&m_pCaption);

	Release();
}

//====================================================
// �X�V����
//====================================================
void CResultSingle::Update(void)
{
	assert(m_state > -1 && m_state < STATE_MAX);
	if (s_aFuncUpdateState[m_state] != nullptr)
	{ // �X�V�֐����w�肳��Ă���ꍇ

		// �e��Ԃ��Ƃ̍X�V
		(this->*(s_aFuncUpdateState[m_state]))();
	}

	// ����
	Input();
}

//=====================================================
// �t�F�[�h��Ԃ̍X�V����
//=====================================================
void CResultSingle::UpdateFade(void)
{
	if (m_pBg == nullptr)
		return;

	m_fTimer += CManager::GetDeltaTime();

	// �^�C�}�[�̃C�[�W���O
	float fTime = m_fTimer / bg::TIME_FADE;
	float fRate = easing::EaseOutExpo(fTime);

	// �F�̐ݒ�
	m_pBg->SetAlpha(bg::INIT_COL.a + bg::DIFF_ALPHA * fRate);

	if (bg::TIME_FADE < m_fTimer)
	{// �t�F�[�h��Ԃ̏I��
		m_state = E_State::STATE_APPERCAPTION;
		m_fTimer = 0.0f;
		Camera::ChangeState(nullptr);

		return;
	}
}

//=====================================================
// �L���v�V�����o����Ԃ̍X�V
//=====================================================
void CResultSingle::UpdateApperCaption(void)
{
	if (m_pCaption == nullptr)
		return;

	m_fTimer += CManager::GetDeltaTime();

	float fTime = m_fTimer / caption::MOVE_TIME;
	float fRate = easing::EaseOutExpo(fTime);
	universal::LimitValuefloat(&fRate, 1.0f, 0.0f);

	//-----------------------------------------
	// �L���v�V�����̈ړ�
	//-----------------------------------------
	D3DXVECTOR3 posCaption = caption::INIT_POS + caption::DIFF_POS * fRate;

	m_pCaption->SetPosition(posCaption);
	m_pCaption->SetVtx();
	m_pCaption->SetAlpha(fRate);

	if (m_fTimer > caption::MOVE_TIME)
	{// ��莞�Ԍo�߂Ŏ��̏�ԂɈڂ�
		m_state = E_State::STATE_ENDAPPERCAPTION;
		m_fTimer = 0.0f;
		CGame::SetState(CGame::E_State::STATE_END);
	}
}

//=====================================================
// ���͏���
//=====================================================
void CResultSingle::Input(void)
{
	CInputManager *pInputMgr = CInputManager::GetInstance();

	if (pInputMgr == nullptr)
		return;

	float aTimer[E_State::STATE_MAX] = { 0.0f, bg::TIME_FADE, caption::MOVE_TIME, 0.0f, 0.0f, };

	if (pInputMgr->GetTrigger(CInputManager::E_Button::BUTTON_ENTER))
		m_fTimer = aTimer[m_state];
}

//====================================================
// �`�揈��
//====================================================
void CResultSingle::Draw(void)
{
#ifdef _DEBUG
	CDebugProc::GetInstance()->Print("\n���U���g�f�o�b�O���===============================");
	CDebugProc::GetInstance()->Print("\n���[%d]",m_state);
#endif
}