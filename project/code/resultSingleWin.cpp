//*****************************************************
//
// �V���O���������U���g�̏���[resultSingleWin.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "resultSingleWin.h"
#include "UI.h"
#include "camera.h"
#include "cameraState.h"
#include "number.h"
#include "texture.h"
#include "manager.h"
#include "inputManager.h"
#include "fade.h"
#include "score.h"
#include "game.h"
#include "player.h"
#include "rankingSingle.h"
#include "gameManager.h"
#include "sound.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
//----------------------------
// �X�R�A���o���萔
//----------------------------
namespace scoreCaption
{
const string PATH_TEX[CResultSingleWin::E_ScoreCaption::CAPTION_MAX] =
{// �L���v�V�����̃p�X
	"data\\TEXTURE\\UI\\result_score.png",
	"data\\TEXTURE\\UI\\result_peck.png",
};
const float TIME_APPER = 2.0f;		// �o���ɂ����鎞��
const float WIDTH = 0.2f;			// ��
const float HEIGHT = 0.15f;			// ����
const float HEIGHT_INIT = -HEIGHT;
const D3DXVECTOR3 POS_INIT[CResultSingleWin::E_ScoreCaption::CAPTION_MAX] =
{// �����ʒu
	{ 0.3f,HEIGHT_INIT,0.0f },
	{ 0.7f,HEIGHT_INIT,0.0f },
};
const float HEIGHT_DEST = 0.37f;						// �ڕW�̍���
const float DIFF_HEIGHT = HEIGHT_DEST - HEIGHT_INIT;	// �����̍���
}

//----------------------------
// �X�R�A�����萔
//----------------------------
namespace scoreNumber
{
const float WIDTH_NUMBER = 0.03f;	// �����̕�
const float HEIGHT_NUMBER = 0.06f;	// �����̍���

const float HEIGHT_INIT = -0.1f;
const D3DXVECTOR3 POS_INIT[CResultSingleWin::E_ScoreCaption::CAPTION_MAX] =
{// �����ʒu
	{ 0.2f,HEIGHT_INIT,0.0f },
	{ 0.73f,HEIGHT_INIT,0.0f },
};
const float HEIGHT_DEST = 0.43f;	// �ڕW�̍���
const float DIFF_HEIGHT = HEIGHT_DEST - HEIGHT_INIT;	// �����̍���
}

//----------------------------
// �X�R�A�萔
//----------------------------
namespace score
{
const int NUM_PLACE[CResultSingleWin::E_ScoreCaption::CAPTION_MAX] = { 5, 2 };	// �X�R�A�̌���
}

//----------------------------
// �����L���O�萔
//----------------------------
namespace ranking
{
const string PATH_SAVE[] =
{// �X�e�[�W�̐����̃p�X
	"data\\BYNARY\\ranking00.bin",
	"data\\BYNARY\\ranking01.bin",
	"data\\BYNARY\\ranking02.bin",
	"data\\BYNARY\\ranking03.bin",
	"data\\BYNARY\\ranking04.bin",
	"data\\BYNARY\\ranking05.bin",
};
const D3DXVECTOR3 POS_NUMBER_DEFAULT = { 0.3f, 0.68f,0.0f };		// �����̃f�t�H���g�ʒu
const float DIST_NUMBER = 0.12f;								// �����Ԃ̋���
const float WIDTH_NUMBER = 0.025f;								// �����̕�
const float HEIGHT_NUMBER = 0.05f;								// �����̍���
const float OFFSET_TIMEPECK = 0.35f;								// �˂������񐔕\���̃I�t�Z�b�g

const float TIME_APPER = 2.0f;						// �o���ɂ����鎞��
const float ALPHA_INIT = 0.0f;						// �����A���t�@�l
const float ALPHA_DEST = 1.0f;						// �ڕW�̃A���t�@�l
const float ALPHA_DIFF = ALPHA_DEST - ALPHA_INIT;	// �����A���t�@�l
}

//----------------------------
// �t���[���萔
//----------------------------
namespace frame
{
const string PATH_TEX = "data\\TEXTURE\\UI\\result_ranking.png";	// �e�N�X�`���p�X
const D3DXCOLOR DEST_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// �ڕW�F
const D3DXCOLOR INIT_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);			// �����F
const D3DXCOLOR DIFF_COL = DEST_COL - INIT_COL;							// �����F
const D3DXVECTOR3 INIT_POS = D3DXVECTOR3(0.5f, 0.76f, 0.0f);				// �����ʒu
const float WIDTH = 0.3f;	// ��
const float HEIGHT = 0.24f;	// ����
}
}

//*****************************************************
// �ÓI�����o�ϐ�
//*****************************************************
CResultSingleWin::FuncUpdateState CResultSingleWin::s_aFuncUpdateState[] =	// ��ԍX�V�֐�
{
	nullptr,									// �������Ȃ��X�V
	&CResultSingleWin::UpdateMoveCamera,		// �J�����ړ��̍X�V
	&CResultSingleWin::UpdateApperScore,		// �X�R�A�o����Ԃ̍X�V
	&CResultSingleWin::UpdateApperRanking,		// �����L���O�o����Ԃ̍X�V
	&CResultSingleWin::UpdateWait,				// �ҋ@��Ԃ̍X�V
	nullptr,									// �I����Ԃ̍X�V
};

//====================================================
// �R���X�g���N�^
//====================================================
CResultSingleWin::CResultSingleWin() : m_fTimer(0.0f), m_apCaptionScore(),m_apNumberOwn(), m_pRanking(nullptr), m_apRankingNumber(), m_pFrame(nullptr)
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CResultSingleWin::~CResultSingleWin()
{

}

//====================================================
// ����������
//====================================================
HRESULT CResultSingleWin::Init(void)
{
	// �e�N���X�̏�����
	CResultSingle::Init();

	// �����L���O�����̐���
	//int nIdxMap = gameManager::LoadIdxMap();
	//m_pRanking = CRankingSingle::Create(ranking::PATH_SAVE[nIdxMap]);

	// 2D�I�u�W�F�N�g�̐���
	Create2D();

	// ��Ԃ̏�����
	m_state = E_State::STATE_MOVECAMERA;

	// �J�����̐ݒ�
	Camera::ChangeState(new CCameraResultSingle(this));

	return S_OK;
}

//====================================================
// 2D�I�u�W�F�N�g�̐���
//====================================================
void CResultSingleWin::Create2D(void)
{
	// ���g�̃X�R�A�̐���
	CreateOwnScore();

	// �����L���O�����̐���
	CreateRankingNumber();
}

//====================================================
// ���g�̃X�R�A�̐���
//====================================================
void CResultSingleWin::CreateOwnScore(void)
{
	////----------------------------
	//// �X�R�A�̎擾
	////----------------------------
	//CGame *pGame = CGame::GetInstance();
	//if (pGame == nullptr)
	//	return;

	//CScore *pScore = pGame->GetScore();
	//if (pScore == nullptr)
	//	return;

	//int nScore = pScore->GetScore();

	////----------------------------
	//// �|���S���̐���
	////----------------------------
	//int aData[E_ScoreCaption::CAPTION_MAX] = { nScore,nTimePeck };	// �����̒l
	//for (int i = 0; i < E_ScoreCaption::CAPTION_MAX; i++)
	//{
	//	// �L���v�V�����̐���
	//	m_apCaptionScore[i] = CUI::Create();
	//	if (m_apCaptionScore[i] == nullptr)
	//		continue;

	//	m_apCaptionScore[i]->SetSize(scoreCaption::WIDTH, scoreCaption::HEIGHT);
	//	m_apCaptionScore[i]->SetPosition(scoreCaption::POS_INIT[i]);
	//	int nIdxTexture = Texture::GetIdx(&scoreCaption::PATH_TEX[i][0]);
	//	m_apCaptionScore[i]->SetIdxTexture(nIdxTexture);
	//	m_apCaptionScore[i]->SetAlpha(0.0f);
	//	m_apCaptionScore[i]->SetVtx();

	//	// �����̐���
	//	m_apNumberOwn[i] = CNumber::Create(score::NUM_PLACE[i], aData[i]);
	//	if (m_apNumberOwn[i] == nullptr)
	//		continue;

	//	m_apNumberOwn[i]->SetPosition(scoreNumber::POS_INIT[i]);
	//	m_apNumberOwn[i]->SetSizeAll(scoreNumber::WIDTH_NUMBER, scoreNumber::HEIGHT_NUMBER);
	//	m_apNumberOwn[i]->SetAlpha(0.0f);
	//}
}

//====================================================
// �����L���O�����̐���
//====================================================
void CResultSingleWin::CreateRankingNumber(void)
{
	//--------------------------
	// �����L���O�̃t���[��
	//--------------------------
	m_pFrame = CUI::Create();

	if (m_pFrame == nullptr)
		return;

	int nIdxTexture = Texture::GetIdx(&frame::PATH_TEX[0]);
	m_pFrame->SetIdxTexture(nIdxTexture);

	m_pFrame->SetSize(frame::WIDTH, frame::HEIGHT);
	m_pFrame->SetPosition(frame::INIT_POS);
	m_pFrame->SetCol(frame::INIT_COL);
	m_pFrame->SetVtx();

	if (m_pRanking == nullptr)
		return;

	//--------------------------
	// �����L���O�̐���
	//--------------------------
	vector<CRankingSingle::S_InfoRank*> aInfoRank = m_pRanking->GetRank();

	if (aInfoRank.empty())
		return;

	for (int i = 0; i < CResultSingleWin::NUM_RANKING; i++)
	{
		int aData[E_ScoreCaption::CAPTION_MAX] = { aInfoRank[i]->nScore,aInfoRank[i]->nTimePeck };

		for (int j = 0; j < E_ScoreCaption::CAPTION_MAX; j++)
		{
			// �����̐���
			CNumber *pNumber = CNumber::Create(score::NUM_PLACE[j], aData[j]);
			if (pNumber == nullptr)
				continue;

			// �ʒu�̌v�Z
			D3DXVECTOR3 pos = ranking::POS_NUMBER_DEFAULT;
			pos.y += ranking::DIST_NUMBER * i;	// ���������ɂ��炷

			if (j == E_ScoreCaption::CAPTION_TIMEPECK)
				pos.x += ranking::OFFSET_TIMEPECK;	// �������񐔂̕\���͂��炷

			// �g�����X�t�H�[���̐ݒ�
			pNumber->SetPosition(pos);
			pNumber->SetSizeAll(ranking::WIDTH_NUMBER,ranking::HEIGHT_NUMBER);

			// �A���t�@�l�̏����ݒ�
			pNumber->SetAlpha(ranking::ALPHA_INIT);

			// �|�C���^��ۑ�
			m_apRankingNumber[i][j] = pNumber;
		}
	}
}

//====================================================
// �I������
//====================================================
void CResultSingleWin::Uninit(void)
{
	Object::DeleteObject((CObject**)&m_pRanking);

	CResultSingle::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CResultSingleWin::Update(void)
{
	assert(m_state > -1 && m_state < STATE_MAX);
	if (s_aFuncUpdateState[m_state] != nullptr)
	{ // �X�V�֐����w�肳��Ă���ꍇ

		// �e��Ԃ��Ƃ̍X�V
		(this->*(s_aFuncUpdateState[m_state]))();
	}

	// �e�N���X�̍X�V
	CResultSingle::Update();

	// ���͏���
	Input();
}

//=====================================================
// �J�����ړ���Ԃ̍X�V
//=====================================================
void CResultSingleWin::UpdateMoveCamera(void)
{
	if (GetState() == CResultSingle::E_State::STATE_ENDAPPERCAPTION)
		m_state = E_State::STATE_APPERSCORE;
}

//=====================================================
// �X�R�A�o����Ԃ̍X�V����
//=====================================================
void CResultSingleWin::UpdateApperScore(void)
{
	m_fTimer += CManager::GetDeltaTime();

	float fTime = m_fTimer / scoreCaption::TIME_APPER;
	float fRate = easing::EaseOutExpo(fTime);
	universal::LimitValuefloat(&fRate, 1.0f, 0.0f);

	for (int i = 0; i < E_ScoreCaption::CAPTION_MAX; i++)
	{
		//-----------------------------------------
		// �L���v�V�����̈ړ�
		//-----------------------------------------
		if (m_apCaptionScore[i] == nullptr)
			continue;

		D3DXVECTOR3 posCaption = m_apCaptionScore[i]->GetPosition();
		posCaption.y = scoreCaption::HEIGHT_INIT + scoreCaption::DIFF_HEIGHT * fRate;

		m_apCaptionScore[i]->SetPosition(posCaption);
		m_apCaptionScore[i]->SetVtx();
		m_apCaptionScore[i]->SetAlpha(fRate);

		//-----------------------------------------
		// �����̈ړ�
		//-----------------------------------------
		if (m_apNumberOwn[i] == nullptr)
			continue;

		D3DXVECTOR3 posNumber = m_apNumberOwn[i]->GetPosition();
		posNumber.y = scoreNumber::HEIGHT_INIT + scoreNumber::DIFF_HEIGHT * fRate;

		m_apNumberOwn[i]->SetPosition(posNumber);
		m_apNumberOwn[i]->SetAlpha(fRate);
	}

	if (m_fTimer > scoreCaption::TIME_APPER)
	{// ��莞�Ԍo�߂Ŏ��̏�ԂɈڂ�
		m_state = E_State::STATE_APPERRANKING;
		m_fTimer = 0.0f;
	}
}

//=====================================================
// �����L���O�o����Ԃ̍X�V����
//=====================================================
void CResultSingleWin::UpdateApperRanking(void)
{
	m_fTimer += CManager::GetDeltaTime();

	float fTime = m_fTimer / scoreCaption::TIME_APPER;
	float fRate = easing::EaseOutExpo(fTime);
	universal::LimitValuefloat(&fRate, 1.0f, 0.0f);

	// �����̐F�ݒ�
	for (int i = 0; i < CResultSingleWin::NUM_RANKING; i++)
	{
		for (int j = 0; j < E_ScoreCaption::CAPTION_MAX; j++)
		{
			if (m_apRankingNumber[i][j] == nullptr)
				continue;

			float fAlpha = ranking::ALPHA_INIT + ranking::ALPHA_DIFF * fRate;

			m_apRankingNumber[i][j]->SetAlpha(fAlpha);
		}
	}

	if (m_pFrame == nullptr)
		return;

	m_pFrame->SetAlpha(fRate);

	if (m_fTimer > ranking::TIME_APPER)
		m_state = E_State::STATE_WAIT;
}

//=====================================================
// �ҋ@��Ԃ̍X�V����
//=====================================================
void CResultSingleWin::UpdateWait(void)
{
	vector<CInputManager*> aInputMgr = CInputManager::GetArray();

	for (CInputManager *pInputMgr : aInputMgr)
	{
		if (pInputMgr == nullptr)
			continue;

		if (pInputMgr->GetTrigger(CInputManager::E_Button::BUTTON_ENTER))
		{// �t�F�[�h���ă^�C�g���ɖ߂�
			CFade *pFade = CFade::GetInstance();

			if (pFade != nullptr)
			{
				pFade->SetFade(CScene::MODE::MODE_TITLE);
				CSound::GetInstance()->Play(CSound::LABEL_SE_DECISION);
			}
		}
	}
}

//=====================================================
// ���͏���
//=====================================================
void CResultSingleWin::Input(void)
{
	CInputManager *pInputMgr = CInputManager::GetInstance();

	if (pInputMgr == nullptr)
		return;

	float aTimer[E_State::STATE_MAX] = { 0.0f, 0.0f, scoreCaption::TIME_APPER, ranking::TIME_APPER, 0.0f,0.0f };

	if (pInputMgr->GetTrigger(CInputManager::E_Button::BUTTON_ENTER))
		m_fTimer = aTimer[m_state];
}

//====================================================
// �`�揈��
//====================================================
void CResultSingleWin::Draw(void)
{
	// �e�N���X�̕`��
	CResultSingle::Draw();
}