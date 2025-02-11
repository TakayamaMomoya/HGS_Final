//*****************************************************
//
// Q[[game.cpp]
// Author:ûüRç
//
//*****************************************************

//*****************************************************
// CN[h
//*****************************************************
#include "manager.h"
#include "result.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputManager.h"
#include "fade.h"
#include "camera.h"
#include "sound.h"
#include "scene.h"
#include "debugproc.h"
#include "UIManager.h"
#include "polygon3D.h"
#include "texture.h"
#include "renderer.h"
#include "animEffect3D.h"
#include "pause.h"
#include "meshfield.h"
#include "CameraState.h"
#include "particle.h"
#include "timer.h"
#include "blur.h"
#include "resultSingle.h"
#include "player.h"
#include "score.h"
#include "fishshadow.h"
#include "house.h"
#include "number.h"
#include "UI.h"
#include "MyEffekseer.h"
#include "objectX.h"

//*****************************************************
// èè`
//*****************************************************
namespace
{
	const int TRANS_TIME = 100;	// I¹ÜÅÌ]CÌt[
	const int SPEED_TIME = 60;	// ^C}[ª¸ÁÄ¢­¬x
	const char* PATH_GAME_ROAD = "data\\MAP\\road00.bin";	// Q[bV[hÌpX
	const char* PATH_SAMPLE_ICESTAGE = "data\\TEXT\\ice_stage_00.txt";	// TvÌúzu
	const float SPEED_CHANGE_LIGHTCOL = 0.1f;	// CgÌFªÏíé¬x
	const D3DXVECTOR3 SET_POS = D3DXVECTOR3(-900.0f, 0.0f, 0.0f);
	const float ADD_X = 200.0f;
	const float CHARA_Z = (-100.0f);
	char* CHARA_PATH = "data\\TEXT\\motion_kidsboy.txt";
	const std::string FILE_PATH = "data\\FILE\\ranking.bin";
	const float CNT = 0.325f;
	const int MAX_WIDTH_NUM = 10;
	const float ADD_Z = 500.0f;
	const D3DXVECTOR3 END_CAMERAROT = D3DXVECTOR3(D3DX_PI * 0.25f, 0.0f, 0.0f);
	const float END_CAMERADIS = 2000.0f;
	const float END_CAMERAINER = 0.02f;
	const float AUTO_FADE_TIMER = 7.0f;
}

namespace
{
	namespace bg
	{
		const float WIDTH = 0.5f;	// 
		const float HEIGHT = 0.5f;	// ³
		const D3DXCOLOR INIT_COL = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// úÌF
		const float DEST_ALPHA = 0.5f;	// ÚWF
		const float DIFF_ALPHA = DEST_ALPHA - INIT_COL.a;			// ·ªAt@l
		const D3DXVECTOR3 POS = D3DXVECTOR3(0.5f, 0.5f, 0.0f);	// Êu
		const float TIME_FADE = 2.0f;	// tF[hÉ©©éÔ
	}

	namespace caption
	{
		const char* PATH[CResultSingle::RESULT_MAX] =
		{																		// pX
			"data\\TEXTURE\\UI\\stage_clear.png",	// ¿
			"data\\TEXTURE\\UI\\gameover.png",		// S
			"data\\TEXTURE\\UI\\timeover.png",		// ^CI[o[
		};
		const float	MOVE_TIME = 1.5f;											// Ú®Ô
		const D3DXCOLOR DEST_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// ÚWF
		const D3DXCOLOR INIT_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);			// úF
		const D3DXCOLOR DIFF_COL = DEST_COL - INIT_COL;							// ·ªF
		const D3DXVECTOR3 DEST_POS = D3DXVECTOR3(0.5f, 0.1f, 0.0f);			// ÚWÊu
		const D3DXVECTOR3 INIT_POS = DEST_POS + D3DXVECTOR3(0.0f, 0.2f, 0.0f);	// úÊu
		const D3DXVECTOR3 DIFF_POS = DEST_POS - INIT_POS;						// ·ªÊu
		const float WIDTH = 0.27f;	// 
		const float HEIGHT = 0.11f;	// ³
	}

	namespace MyResult
	{
		const char* PATH =
		{																		// pX
			"data\\TEXTURE\\UI\\result_my.png",	// ¡ñÌXRA
		};
		const float	MOVE_TIME = 1.5f;											// Ú®Ô
		const D3DXCOLOR DEST_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// ÚWF
		const D3DXCOLOR INIT_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);			// úF
		const D3DXCOLOR DIFF_COL = DEST_COL - INIT_COL;							// ·ªF
		const D3DXVECTOR3 DEST_POS = D3DXVECTOR3(0.25f, 0.35f, 0.0f);				// ÚWÊu
		const D3DXVECTOR3 INIT_POS = DEST_POS + D3DXVECTOR3(0.0f, 0.2f, 0.0f);	// úÊu
		const D3DXVECTOR3 DIFF_POS = DEST_POS - INIT_POS;						// ·ªÊu
		const D3DXVECTOR3 SCORE_POS = D3DXVECTOR3(-0.09f, 0.3f, 0.0f);				// ÚWÊu
		const float WIDTH = 0.2f;	// 
		const float HEIGHT = 0.1f;	// ³
		const float SCORE_WIDTH = 0.05f;	// 
		const float SCORE_HEIGHT = 0.09f;	// ³
	}

	namespace Rank
	{
		const char* PATH =
		{																		// pX
			"data\\TEXTURE\\UI\\result_rank.png",	// ¡ñÌXRA
		};

		const char* SCORE_UIPATH[Result_Rank::NUM] =
		{																		// pX
			"data\\TEXTURE\\UI\\1st.png",	// 1
			"data\\TEXTURE\\UI\\2nd.png",	// 2
			"data\\TEXTURE\\UI\\3rd.png",	// 3
		};

		const float	MOVE_TIME = 1.5f;											// Ú®Ô
		const D3DXCOLOR DEST_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// ÚWF
		const D3DXCOLOR INIT_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);			// úF
		const D3DXCOLOR DIFF_COL = DEST_COL - INIT_COL;							// ·ªF
		const D3DXVECTOR3 DEST_POS = D3DXVECTOR3(0.75f, 0.35f, 0.0f);				// ÚWÊu
		const D3DXVECTOR3 INIT_POS = DEST_POS + D3DXVECTOR3(0.0f, 0.2f, 0.0f);	// úÊu
		const D3DXVECTOR3 DIFF_POS = DEST_POS - INIT_POS;						// ·ªÊu
		const D3DXVECTOR3 SCORE_POS = D3DXVECTOR3(-0.05f, 0.3f, 0.0f);			// ÚWÊu
		const D3DXVECTOR3 RANK_UI_POS = D3DXVECTOR3(-0.12f, 0.2f, 0.0f);		// ÚWÊu
		const D3DXVECTOR3 RANK_UI_SPACE = D3DXVECTOR3(0.0f, 0.15f, 0.0f);		// ÚWÊu
		const D3DXVECTOR3 RANK_SCORE_POS = D3DXVECTOR3(0.0f, 0.2f, 0.0f);		// ÚWÊu
		const D3DXVECTOR3 RANK_SCORE_SPACE = D3DXVECTOR3(0.0f, 0.15f, 0.0f);	// ÚWÊu
		const float WIDTH = 0.2f;				// 
		const float HEIGHT = 0.1f;			// ³
		const float SCORE_UI_WIDTH = 0.075f;		// 
		const float SCORE_UI_HEIGHT = 0.05f;	// ³
		const float SCORE_WIDTH = 0.03f;		// 
		const float SCORE_HEIGHT = 0.06f;		// ³
	}
}

//*****************************************************
// ÃIoÏé¾
//*****************************************************
CResult* CResult::m_pResult = nullptr;	// ©gÌ|C^

//*****************************************************
// ÃIoÏ
//*****************************************************
CResult::FuncUpdateState CResult::s_aFuncUpdateState[] =	// óÔXVÖ
{
	nullptr,							// ½àµÈ¢XV
	& CResult::UpdateFade,			// tF[hóÔÌXV
	& CResult::UpdateApperCaption,	// LvVo»óÔÌXV
	nullptr,							// LvVo»I¹óÔÌXV
	nullptr,							// I¹óÔÌXV
};

//=====================================================
// RXgN^
//=====================================================
CResult::CResult() : m_fTimer(0.0f), m_pCaption(nullptr)
{
	m_ClearList.clear();
	m_CharacterList.clear();
	m_CharacterIt = m_CharacterList.end();
	m_aRankScore.clear();
	m_fCnt = 0.0f;
	m_nKeyOld = 0;
	m_bEnd = false;
	m_state = E_State::STATE_NONE;
	m_camerastart = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMyScore = nullptr;
	m_pRank = nullptr;
	m_fFadeTimer = 0.0f;

	for (int i = 0; i < Result_Rank::NUM; i++)
	{
		m_apRank[i] = nullptr;
		m_apRankScore[i] = nullptr;
	}
}

//=====================================================
// ú»
//=====================================================
HRESULT CResult::Init(void)
{
	CInputManager::Create();

	m_aRankScore.resize(Result_Rank::NUM);

	// eNXÌú»
	CScene::Init();

	m_pResult = this;

	// Xgðæ¾·éæ
	m_ClearList = CHouse::GetLabelResult();

	// v[gðÀ×é
	InitCharacter();

	// Ce[^[ú»
	m_CharacterIt = m_CharacterList.begin();

	CCamera* pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->ChangeState(new CCameraStateResult);
		pCamera->SetDist(600.0f);
		m_camerastart = pCamera->GetPosR();

		if (m_CharacterIt != m_CharacterList.end())
		{
			m_camerastart = (*m_CharacterIt)->pCharacter->GetPosition();
		}

		pCamera->SetPosR(m_camerastart);
	}

	// ÇÝÝ
	Load();

	// \[g
	Sort();

	// Û¶
	Save();

	// 2DIuWFNgÌ¶¬
	Create2D();

	// Q[BGMÌÄ¶
	Sound::Play(CSound::LABEL_BGM_GAME01);

	return S_OK;
}

//=====================================================
// I¹
//=====================================================
void CResult::Uninit(void)
{
	// îñpü
	for (auto& it : m_CharacterList)
	{

		if (it->pCharacter == m_LastInfo.pCharacter) {
			continue;
		}

		delete it;
	}

	Object::DeleteObject((CObject**)&m_pBg);
	Object::DeleteObject((CObject**)&m_pCaption);
	Object::DeleteObject((CObject**)&m_pMyResult);
	Object::DeleteObject((CObject**)&m_pRank);

	for (int i = 0; i < Result_Rank::NUM; i++)
	{
		if (m_apRank[i] != nullptr)
		{
			Object::DeleteObject((CObject**)&m_apRank[i]);
		}
	}

	m_CharacterList.clear();
	m_aRankScore.clear();
	m_ClearList.clear();

	// IuWFNgSü
	CObject::ReleaseAll();

	CScene::Uninit();

	m_pResult = nullptr;
}

//=====================================================
// XV
//=====================================================
void CResult::Update(void)
{
	CFade* pFade = CFade::GetInstance();
	CInputManager* pInputManager = CInputManager::GetInstance();
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CSound* pSound = CSound::GetInstance();

	// [VÝè
	MotionSet();

	// JÇ]
	PursueCamera();

	// JXV
	UpdateCamera();

	assert(m_state > -1 && m_state < STATE_MAX);
	if (s_aFuncUpdateState[m_state] != nullptr)
	{ // XVÖªwè³êÄ¢éê

		// eóÔ²ÆÌXV
		(this->*(s_aFuncUpdateState[m_state]))();
	}

	Input();

	// V[ÌXV
	CScene::Update();
}

//=====================================================
// `æ
//=====================================================
void CResult::Draw(void)
{
#ifndef _DEBUG

	return;

#endif
}

//=====================================================
// JÌXV
//=====================================================
void CResult::UpdateCamera(void)
{
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	pCamera->Update();
}

//=====================================================
// [VÝè
//=====================================================
void CResult::MotionSet(void)
{
	m_fCnt += CManager::GetDeltaTime();

	if (m_fCnt >= CNT)
	{
		m_fCnt = 0.0f;
		// LN^[ éæ
		if (m_CharacterIt != m_CharacterList.end())
		{
			// [VðÝè
			(*m_CharacterIt)->pCharacter->SetMotion(1);
			(*m_CharacterIt)->pPresent->SetMotion(1);

			//=====================================================
			// v[gð¶¬
			//=====================================================
			 vector<CPresent::S_InfoPresent*> aInfo = CPresent::GetInfoPresent();

			 Sound::Play(CSound::LABEL::LABEL_SE_SUCCESS);

			 CPresent::S_InfoPresent* pInfo = universal::RandomFromVector(aInfo);
			 (*m_CharacterIt)->pModel = CObjectX::Create();
			 int nIdxModel = CModel::Load(&pInfo->pathModel[0]);
			 (*m_CharacterIt)->pModel->BindModel(nIdxModel);
			 (*m_CharacterIt)->pModel->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
			 (*m_CharacterIt)->pModel->SetScale(pInfo->fScale);

			// v[g ©çGtFNgð¶¬
			MyEffekseer::CreateEffect(CMyEffekseer::TYPE::TYPE_PRESENT, (*m_CharacterIt)->pPresent->GetPosition());

			m_camerastart = (*m_CharacterIt)->pCharacter->GetPosition();
			m_CharacterIt++;
		}
	}

	// [VmF
	for (const auto& it : m_CharacterList)
	{
		//=====================================================
		// v[gðèÌæÉt¯é (6ÅEè 10Å¶è)
		//=====================================================
		D3DXMATRIX mtxHand = it->pCharacter->GetParts(6)->pParts->GetMatrix();

		if (it->pModel != nullptr)
		{
			it->pModel->SetPosition(D3DXVECTOR3(mtxHand._41, mtxHand._42, mtxHand._43));
		}

		if (it->pCharacter->IsFinish())
		{
			if (it->pCharacter == m_LastInfo.pCharacter)
			{
				it->pCharacter->SetMotion(3);
			}
			else
			{
				it->pCharacter->SetMotion(2);
			}
		}
	}

	// I¹mF
	if (m_nKeyOld > m_LastInfo.pCharacter->GetKey() && m_LastInfo.pCharacter->GetMotion() == 3)
	{
		m_bEnd = true;

		if (m_state == E_State::STATE_NONE)
		{
			m_state = E_State::STATE_FADE;
		}
	}
}

//=====================================================
// JÇ]
//=====================================================
void CResult::PursueCamera(void)
{
	if (m_bEnd) { EndCamera(); return; }

	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr){ return; }

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_CharacterIt != m_CharacterList.end())
	{
		pos = (*m_CharacterIt)->pCharacter->GetPosition();
	}
	else
	{
		pos = m_LastInfo.pCharacter->GetPosition();
	}

	D3DXVECTOR3 diff = pos - m_camerastart;
	D3DXVECTOR3 setpos = m_camerastart + (diff * (m_fCnt / CNT));

	pCamera->SetPosR(setpos);
}

//=====================================================
// ú»
//=====================================================
void CResult::InitCharacter(void)
{
	int i = 0;
	for (const auto& it : m_ClearList)
	{
		SCharaInfo* info = new SCharaInfo();
		// v[gÌ¶¬
		info->pPresent = CPresent::Create(it);
		D3DXVECTOR3 pos = SET_POS;
	
		pos.x += ADD_X * (i % MAX_WIDTH_NUM);

		// ÌñÉÚ®
		int temp = (i / MAX_WIDTH_NUM);
		pos.z += ADD_Z * temp;

		if (temp % 2 != 0)
		{
			pos.x *= -1.0f;
		}
		
		// lÝè
		info->pPresent->SetPosition(pos);
		info->pPresent->SetScale(0.75f);

		// LN^[¶¬
		info->pCharacter = CMotion::Create(CHARA_PATH);
		pos.z += CHARA_Z;
		info->pCharacter->SetPosition(pos);
		info->pCharacter->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		info->pCharacter->SetScale(1.3f);
		m_CharacterList.push_back(info);

		i++;
	}


	// ÅãÌ¸sLðì¬
	m_LastInfo.pPresent = CPresent::Create(CPresent::E_Label::LABEL_YELLOW);
	D3DXVECTOR3 pos = SET_POS;
	int temp = (i / MAX_WIDTH_NUM);
	pos.x += (ADD_X * (i % MAX_WIDTH_NUM));
	pos.z += ADD_Z * temp;


	if (temp % 2 != 0)
	{
		pos.x *= -1.0f;
	}

	m_LastInfo.pPresent->SetPosition(pos);
	m_LastInfo.pPresent->SetScale(0.75f);

	m_LastInfo.pCharacter = CMotion::Create(CHARA_PATH);
	pos.z += CHARA_Z;
	m_LastInfo.pCharacter->SetPosition(pos);
	m_LastInfo.pCharacter->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	m_LastInfo.pCharacter->SetScale(1.1f);
	m_CharacterList.push_back(&m_LastInfo);
}

//=====================================================
// I¹ÌJ
//=====================================================
void CResult::EndCamera(void)
{
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr) { return; }

	float dis = pCamera->GetDist() + ((END_CAMERADIS - pCamera->GetDist()) * END_CAMERAINER);
	pCamera->SetDist(dis);

	D3DXVECTOR3 rot = pCamera->GetRot() + ((END_CAMERAROT - pCamera->GetRot()) * END_CAMERAINER);
	pCamera->SetRot(rot);

	if (m_CharacterIt != m_CharacterList.end())
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (m_CharacterIt != m_CharacterList.end())
		{
			pos = (*m_CharacterIt)->pCharacter->GetPosition();
		}
		else
		{
			pos = m_LastInfo.pCharacter->GetPosition();
		}

		D3DXVECTOR3 diff = pos - m_camerastart;
		D3DXVECTOR3 setpos = m_camerastart + (diff * (m_fCnt / CNT));

		pCamera->SetPosR(setpos);
	}
}

//=====================================================
// UIÌú»
//=====================================================
void CResult::Ui_Init(void)
{

}

//====================================================
// 2DIuWFNgÌ¶¬
//====================================================
void CResult::Create2D(void)
{
	// wiÌ¶¬
	CreateBg();

	// ©oµÌ¶¬
	CreateCaption();

	// ÂlUgì¬
	CreateMyResult();

	// LOì¬
	CreateRank();
}

//====================================================
// ©oµÌ¶¬
//====================================================
void CResult::CreateCaption(void)
{
	m_pCaption = CUI::Create();

	if (m_pCaption == nullptr)
		return;

	m_pCaption->SetSize(caption::WIDTH, caption::HEIGHT);
	m_pCaption->SetPosition(caption::INIT_POS);
	m_pCaption->SetCol(caption::INIT_COL);
	m_pCaption->SetVtx();

	int nIdxTexture = Texture::GetIdx(caption::PATH[0]);
	m_pCaption->SetIdxTexture(nIdxTexture);
}

//====================================================
// wiÌ¶¬
//====================================================
void CResult::CreateBg(void)
{
	m_pBg = CUI::Create();

	if (m_pBg == nullptr)
		return;

	m_pBg->SetSize(bg::WIDTH, bg::HEIGHT);
	m_pBg->SetPosition(bg::POS);
	m_pBg->SetCol(bg::INIT_COL);
	m_pBg->SetVtx();
}

//=====================================================
// tF[hóÔÌXV
//=====================================================
void CResult::UpdateFade(void)
{
	if (m_pBg == nullptr)
		return;

	m_fTimer += CManager::GetDeltaTime();

	// ^C}[ÌC[WO
	float fTime = m_fTimer / bg::TIME_FADE;
	float fRate = easing::EaseOutExpo(fTime);

	// FÌÝè
	m_pBg->SetAlpha(bg::INIT_COL.a + bg::DIFF_ALPHA * fRate);

	if (bg::TIME_FADE < m_fTimer)
	{// tF[hóÔÌI¹
		m_state = E_State::STATE_APPERCAPTION;
		m_fTimer = 0.0f;
		return;
	}
}

//=====================================================
// LvVo»óÔÌXV
//=====================================================
void CResult::UpdateApperCaption(void)
{
	m_fTimer += CManager::GetDeltaTime();
	
	if (m_pMyResult != nullptr)
	{
		if (m_pMyResult != nullptr)
		{

			float fTime = m_fTimer / MyResult::MOVE_TIME;
			float fRate = easing::EaseOutExpo(fTime);
			universal::LimitValuefloat(&fRate, 1.0f, 0.0f);

			//-----------------------------------------
			// LvVÌÚ®
			//-----------------------------------------
			D3DXVECTOR3 posCaption = MyResult::INIT_POS + MyResult::DIFF_POS * fRate;

			m_pMyResult->SetPosition(posCaption);
			m_pMyResult->SetVtx();
			m_pMyResult->SetAlpha(fRate);
			m_pMyScore->SetAlpha(fRate);
			m_pMyScore->SetPosition(posCaption + MyResult::SCORE_POS);
		}
	}

	if (m_pRank != nullptr)
	{
		if (m_pRank != nullptr)
		{

			float fTime = m_fTimer / Rank::MOVE_TIME;
			float fRate = easing::EaseOutExpo(fTime);
			universal::LimitValuefloat(&fRate, 1.0f, 0.0f);

			//-----------------------------------------
			// LvVÌÚ®
			//-----------------------------------------
			D3DXVECTOR3 posCaption = Rank::INIT_POS + Rank::DIFF_POS * fRate;

			m_pRank->SetPosition(posCaption);
			m_pRank->SetVtx();
			m_pRank->SetAlpha(fRate);

			for (int i = 0; i < Result_Rank::NUM; i++)
			{

				if (m_apRank[i] == nullptr)
					continue;

				m_apRank[i]->SetPosition(posCaption + Rank::RANK_UI_POS + Rank::RANK_UI_SPACE * i);
				m_apRank[i]->SetVtx();
				m_apRank[i]->SetAlpha(fRate);

				if (m_apRankScore[i] == nullptr)
					continue;

				m_apRankScore[i]->SetPosition(posCaption + Rank::RANK_SCORE_POS + Rank::RANK_SCORE_SPACE * i);
				m_apRankScore[i]->SetAlpha(fRate);
			}
		}
	}

	if (m_pCaption != nullptr)
	{

		float fTime = m_fTimer / caption::MOVE_TIME;
		float fRate = easing::EaseOutExpo(fTime);
		universal::LimitValuefloat(&fRate, 1.0f, 0.0f);

		//-----------------------------------------
		// LvVÌÚ®
		//-----------------------------------------
		D3DXVECTOR3 posCaption = caption::INIT_POS + caption::DIFF_POS * fRate;

		m_pCaption->SetPosition(posCaption);
		m_pCaption->SetVtx();
		m_pCaption->SetAlpha(fRate);

		if (m_fTimer > caption::MOVE_TIME)
		{// êèÔoßÅÌóÔÉÚé
			m_state = E_State::STATE_ENDAPPERCAPTION;
			m_fTimer = 0.0f;
		}
	}
}

//=====================================================
// üÍ
//=====================================================
void CResult::Input(void)
{
	CInputManager* pInputMgr = CInputManager::GetInstance();

	if (pInputMgr == nullptr)
		return;

	if (m_state == E_State::STATE_NONE)
	{
		if (!pInputMgr->GetTrigger(CInputManager::E_Button::BUTTON_ENTER)) { return; }
		m_state = E_State::STATE_FADE;
	}
	else if (m_state == E_State::STATE_ENDAPPERCAPTION)
	{
		m_fFadeTimer += CManager::GetDeltaTime();
		if (!pInputMgr->GetTrigger(CInputManager::E_Button::BUTTON_ENTER) && m_fFadeTimer <= AUTO_FADE_TIMER) { return; }
		m_state = E_State::STATE_END;
		CFade::GetInstance()->SetFade(CScene::MODE::MODE_TITLE);
	}
}

//=====================================================
// UgpUI¶¬
//=====================================================
void CResult::CreateMyResult(void)
{
	m_pMyResult = CUI::Create();

	if (m_pMyResult == nullptr)
		return;

	m_pMyResult->SetSize(MyResult::WIDTH, MyResult::HEIGHT);
	m_pMyResult->SetPosition(MyResult::INIT_POS);
	m_pMyResult->SetCol(MyResult::INIT_COL);
	m_pMyResult->SetVtx();

	int nIdxTexture = Texture::GetIdx(MyResult::PATH);
	m_pMyResult->SetIdxTexture(nIdxTexture);

	m_pMyScore = CNumber::Create(3, m_ClearList.size());
	m_pMyScore->SetPosition(MyResult::INIT_POS + MyResult::SCORE_POS);
	m_pMyScore->SetAlpha(0.0f);
	m_pMyScore->SetSizeAll(MyResult::SCORE_WIDTH, MyResult::SCORE_HEIGHT);
}

//=====================================================
// LOpUIì¬
//=====================================================
void CResult::CreateRank(void)
{
	// ©oµ
	m_pRank = CUI::Create();

	if (m_pRank == nullptr)
		return;

	m_pRank->SetSize(Rank::WIDTH, Rank::HEIGHT);
	m_pRank->SetPosition(Rank::INIT_POS);
	m_pRank->SetCol(Rank::INIT_COL);
	m_pRank->SetVtx();

	int nIdxTexture = Texture::GetIdx(Rank::PATH);
	m_pRank->SetIdxTexture(nIdxTexture);

	// Ê
	for (int i = 0; i < Result_Rank::NUM; i++)
	{
		m_apRank[i] = CUI::Create();

		if (m_apRank[i] == nullptr)
			return;

		m_apRank[i]->SetSize(Rank::SCORE_UI_WIDTH, Rank::SCORE_UI_HEIGHT);
		m_apRank[i]->SetPosition(Rank::INIT_POS + Rank::RANK_UI_POS + Rank::RANK_UI_SPACE * i);
		m_apRank[i]->SetCol(Rank::INIT_COL);
		m_apRank[i]->SetVtx();

		int nIdxTexture = Texture::GetIdx(Rank::SCORE_UIPATH[i]);
		m_apRank[i]->SetIdxTexture(nIdxTexture);

		m_apRankScore[i] = CNumber::Create(3, m_aRankScore[i]);

		if (m_apRankScore[i] == nullptr)
			return;

		m_apRankScore[i]->SetPosition(Rank::INIT_POS + Rank::RANK_SCORE_POS + Rank::RANK_SCORE_SPACE * i);
		m_apRankScore[i]->SetAlpha(Rank::INIT_COL.a);
		m_apRankScore[i]->SetSizeAll(Rank::SCORE_WIDTH, Rank::SCORE_HEIGHT);
	}
}

//=====================================================
// Û¶
//=====================================================
void CResult::Save(void)
{
	// t@CðJ­
	std::ofstream File(FILE_PATH, std::ios::binary);
	if (!File.is_open()) {
		return;
	}

	int size = m_aRankScore.size();

	// xNgÌTCYðZ[u
	File.write(reinterpret_cast<const char*>(&size), sizeof(size));

	// f[^ðoCit@CÉ«o·
	File.write(reinterpret_cast<char*>(m_aRankScore.data()), size * sizeof(int));

	// t@CðÂ¶é
	File.close();
}

//=====================================================
// ÇÝÝ
//=====================================================
void CResult::Load(void)
{
	m_aRankScore.clear();
	m_aRankScore.resize(Result_Rank::NUM);

	// t@CðJ­
	std::ifstream File(FILE_PATH, std::ios::binary);
	if (!File.is_open()) {
		// áO

		for (int i = 0; i < m_aRankScore.size(); i++)
		{
			m_aRankScore[i] = i;
		}

		return;
	}

	// TCYÇÝÝ
	int size = 0;
	File.read(reinterpret_cast<char*>(&size), sizeof(size));
	File.read(reinterpret_cast<char*>(m_aRankScore.data()), size * sizeof(int));

	// t@CðÂ¶é
	File.close();
}

//=====================================================
// \[g
//=====================================================
void CResult::Sort(void)
{
	if (m_aRankScore.size() <= 1) { return; }

	// NCðmF
	bool flag = false;
	for (int i = 0; i < Result_Rank::NUM; i++)
	{
		if (m_ClearList.size() == m_aRankScore[i])
		{
			flag = true;
		}
	}
	if (m_ClearList.size() >= m_aRankScore[m_aRankScore.size() - 1] && !flag)
	{
		m_aRankScore[m_aRankScore.size() - 1] = m_ClearList.size();
	}

	// \[g
	for (int i = 0; i < Result_Rank::NUM; i++)
	{
		int temp = i;

		for (int j = i + 1; j < Result_Rank::NUM; j++)
		{
			// ¸\[g
			if (m_aRankScore[j] >= m_aRankScore[temp])
			{
				// L¯
				temp = j;
			}
		}

		// ÏX³ê½
		if (i != temp)
		{
			int score = m_aRankScore[temp];
			m_aRankScore[temp] = m_aRankScore[i];
			m_aRankScore[i] = score;
		}
	}
}