//*****************************************************
//
// ゲーム処理[game.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
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

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const int TRANS_TIME = 100;	// 終了までの余韻のフレーム数
	const int SPEED_TIME = 60;	// タイマーが減っていく速度
	const char* PATH_GAME_ROAD = "data\\MAP\\road00.bin";	// ゲームメッシュロードのパス
	const char* PATH_SAMPLE_ICESTAGE = "data\\TEXT\\ice_stage_00.txt";	// サンプルの初期配置
	const float SPEED_CHANGE_LIGHTCOL = 0.1f;	// ライトの色が変わる速度
	const D3DXVECTOR3 SET_POS = D3DXVECTOR3(-900.0f, 0.0f, 0.0f);
	const float ADD_X = 200.0f;
	const float CHARA_Z = (-100.0f);
	char* CHARA_PATH = "data\\TEXT\\motion_kidsboy.txt";
	const std::string FILE_PATH = "data\\FILE\\ranking.bin";
	const float CNT = 0.3f;
	const int MAX_WIDTH_NUM = 10;
	const float ADD_Z = 500.0f;
	const D3DXVECTOR3 END_CAMERAROT = D3DXVECTOR3(D3DX_PI * 0.25f, 0.0f, 0.0f);
	const float END_CAMERADIS = 2000.0f;
	const float END_CAMERAINER = 0.02f;
}

namespace
{
	namespace bg
	{
		const float WIDTH = 0.5f;	// 幅
		const float HEIGHT = 0.5f;	// 高さ
		const D3DXCOLOR INIT_COL = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 初期の色
		const float DEST_ALPHA = 0.5f;	// 目標色
		const float DIFF_ALPHA = DEST_ALPHA - INIT_COL.a;			// 差分アルファ値
		const D3DXVECTOR3 POS = D3DXVECTOR3(0.5f, 0.5f, 0.0f);	// 位置
		const float TIME_FADE = 2.0f;	// フェードにかかる時間
	}

	namespace caption
	{
		const char* PATH[CResultSingle::RESULT_MAX] =
		{																		// パス
			"data\\TEXTURE\\UI\\stage_clear.png",	// 勝ち
			"data\\TEXTURE\\UI\\gameover.png",		// 死亡
			"data\\TEXTURE\\UI\\timeover.png",		// タイムオーバー
		};
		const float	MOVE_TIME = 1.5f;											// 移動時間
		const D3DXCOLOR DEST_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// 目標色
		const D3DXCOLOR INIT_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);			// 初期色
		const D3DXCOLOR DIFF_COL = DEST_COL - INIT_COL;							// 差分色
		const D3DXVECTOR3 DEST_POS = D3DXVECTOR3(0.5f, 0.1f, 0.0f);			// 目標位置
		const D3DXVECTOR3 INIT_POS = DEST_POS + D3DXVECTOR3(0.0f, 0.2f, 0.0f);	// 初期位置
		const D3DXVECTOR3 DIFF_POS = DEST_POS - INIT_POS;						// 差分位置
		const float WIDTH = 0.27f;	// 幅
		const float HEIGHT = 0.14f;	// 高さ
	}

	namespace MyResult
	{
		const char* PATH =
		{																		// パス
			"data\\TEXTURE\\UI\\stage_clear.png",	// 今回のスコア
		};
		const float	MOVE_TIME = 1.5f;											// 移動時間
		const D3DXCOLOR DEST_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// 目標色
		const D3DXCOLOR INIT_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);			// 初期色
		const D3DXCOLOR DIFF_COL = DEST_COL - INIT_COL;							// 差分色
		const D3DXVECTOR3 DEST_POS = D3DXVECTOR3(0.25f, 0.35f, 0.0f);				// 目標位置
		const D3DXVECTOR3 INIT_POS = DEST_POS + D3DXVECTOR3(0.0f, 0.2f, 0.0f);	// 初期位置
		const D3DXVECTOR3 DIFF_POS = DEST_POS - INIT_POS;						// 差分位置
		const D3DXVECTOR3 SCORE_POS = D3DXVECTOR3(-0.09f, 0.3f, 0.0f);				// 目標位置
		const float WIDTH = 0.2f;	// 幅
		const float HEIGHT = 0.125f;	// 高さ
		const float SCORE_WIDTH = 0.05f;	// 幅
		const float SCORE_HEIGHT = 0.09f;	// 高さ
	}

	namespace Rank
	{
		const char* PATH =
		{																		// パス
			"data\\TEXTURE\\UI\\stage_clear.png",	// 今回のスコア
		};

		const char* SCORE_UIPATH[Result_Rank::NUM] =
		{																		// パス
			"data\\TEXTURE\\UI\\1st.png",	// 1
			"data\\TEXTURE\\UI\\2nd.png",	// 2
			"data\\TEXTURE\\UI\\3rd.png",	// 3
		};

		const float	MOVE_TIME = 1.5f;											// 移動時間
		const D3DXCOLOR DEST_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// 目標色
		const D3DXCOLOR INIT_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);			// 初期色
		const D3DXCOLOR DIFF_COL = DEST_COL - INIT_COL;							// 差分色
		const D3DXVECTOR3 DEST_POS = D3DXVECTOR3(0.75f, 0.35f, 0.0f);				// 目標位置
		const D3DXVECTOR3 INIT_POS = DEST_POS + D3DXVECTOR3(0.0f, 0.2f, 0.0f);	// 初期位置
		const D3DXVECTOR3 DIFF_POS = DEST_POS - INIT_POS;						// 差分位置
		const D3DXVECTOR3 SCORE_POS = D3DXVECTOR3(-0.05f, 0.3f, 0.0f);			// 目標位置
		const D3DXVECTOR3 RANK_UI_POS = D3DXVECTOR3(-0.12f, 0.15f, 0.0f);		// 目標位置
		const D3DXVECTOR3 RANK_UI_SPACE = D3DXVECTOR3(0.0f, 0.15f, 0.0f);		// 目標位置
		const D3DXVECTOR3 RANK_SCORE_POS = D3DXVECTOR3(0.0f, 0.15f, 0.0f);		// 目標位置
		const D3DXVECTOR3 RANK_SCORE_SPACE = D3DXVECTOR3(0.0f, 0.15f, 0.0f);	// 目標位置
		const float WIDTH = 0.2f;				// 幅
		const float HEIGHT = 0.125f;			// 高さ
		const float SCORE_UI_WIDTH = 0.075f;		// 幅
		const float SCORE_UI_HEIGHT = 0.05f;	// 高さ
		const float SCORE_WIDTH = 0.03f;		// 幅
		const float SCORE_HEIGHT = 0.06f;		// 高さ
	}
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CResult* CResult::m_pResult = nullptr;	// 自身のポインタ

//*****************************************************
// 静的メンバ変数
//*****************************************************
CResult::FuncUpdateState CResult::s_aFuncUpdateState[] =	// 状態更新関数
{
	nullptr,							// 何もしない更新
	& CResult::UpdateFade,			// フェード状態の更新
	& CResult::UpdateApperCaption,	// キャプション出現状態の更新
	nullptr,							// キャプション出現終了状態の更新
	nullptr,							// 終了状態の更新
};

//=====================================================
// コンストラクタ
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

	for (int i = 0; i < Result_Rank::NUM; i++)
	{
		m_apRank[i] = nullptr;
		m_apRankScore[i] = nullptr;
	}
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CResult::Init(void)
{
	CInputManager::Create();

	m_aRankScore.resize(Result_Rank::NUM);

	// 親クラスの初期化
	CScene::Init();

	m_pResult = this;

	// リストを取得するよ
	m_ClearList = CHouse::GetLabelResult();

	// プレゼントを並べる
	InitCharacter();

	// イテレーター初期化
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

	// 読み込み
	Load();

	// ソート
	Sort();

	// 保存
	Save();

	// 2Dオブジェクトの生成
	Create2D();

	// ゲームBGMの再生
	Sound::Play(CSound::LABEL_BGM_GAME01);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CResult::Uninit(void)
{
	// 情報廃棄
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

	// オブジェクト全棄
	CObject::ReleaseAll();

	CScene::Uninit();

	m_pResult = nullptr;
}

//=====================================================
// 更新処理
//=====================================================
void CResult::Update(void)
{
	CFade* pFade = CFade::GetInstance();
	CInputManager* pInputManager = CInputManager::GetInstance();
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CSound* pSound = CSound::GetInstance();

	// モーション設定
	MotionSet();

	// カメラ追従
	PursueCamera();

	// カメラ更新
	UpdateCamera();

	assert(m_state > -1 && m_state < STATE_MAX);
	if (s_aFuncUpdateState[m_state] != nullptr)
	{ // 更新関数が指定されている場合

		// 各状態ごとの更新
		(this->*(s_aFuncUpdateState[m_state]))();
	}

	Input();

	// シーンの更新
	CScene::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CResult::Draw(void)
{
#ifndef _DEBUG

	return;

#endif
}

//=====================================================
// カメラの更新
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
// モーション設定
//=====================================================
void CResult::MotionSet(void)
{
	m_fCnt += CManager::GetDeltaTime();

	if (m_fCnt >= CNT)
	{
		m_fCnt = 0.0f;
		// キャラクター次あるよ
		if (m_CharacterIt != m_CharacterList.end())
		{
			(*m_CharacterIt)->pCharacter->SetMotion(1);
			(*m_CharacterIt)->pPresent->SetMotion(1);
			m_camerastart = (*m_CharacterIt)->pCharacter->GetPosition();
			m_CharacterIt++;
		}
	}

	// モーション確認
	for (const auto& it : m_CharacterList)
	{
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

	// 終了確認
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
// カメラ追従
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
// 初期化
//=====================================================
void CResult::InitCharacter(void)
{
	int i = 0;
	for (const auto& it : m_ClearList)
	{
		SCharaInfo* info = new SCharaInfo();
		// プレゼントの生成
		info->pPresent = CPresent::Create(it);
		D3DXVECTOR3 pos = SET_POS;
	
		pos.x += ADD_X * (i % MAX_WIDTH_NUM);

		// 次の列に移動
		int temp = (i / MAX_WIDTH_NUM);
		pos.z += ADD_Z * temp;

		if (temp % 2 != 0)
		{
			pos.x *= -1.0f;
		}
		
		// 値設定
		info->pPresent->SetPosition(pos);
		info->pPresent->SetScale(0.75f);

		// キャラクター生成
		info->pCharacter = CMotion::Create(CHARA_PATH);
		pos.z += CHARA_Z;
		info->pCharacter->SetPosition(pos);
		info->pCharacter->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		info->pCharacter->SetScale(1.3f);
		m_CharacterList.push_back(info);

		i++;
	}


	// 最後の失敗キャラを作成
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
// 終了時のカメラ
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
// UIの初期化
//=====================================================
void CResult::Ui_Init(void)
{

}

//====================================================
// 2Dオブジェクトの生成
//====================================================
void CResult::Create2D(void)
{
	// 背景の生成
	CreateBg();

	// 見出しの生成
	CreateCaption();

	// 個人リザルト作成
	CreateMyResult();

	// ランキング作成
	CreateRank();
}

//====================================================
// 見出しの生成
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
// 背景の生成
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
// フェード状態の更新処理
//=====================================================
void CResult::UpdateFade(void)
{
	if (m_pBg == nullptr)
		return;

	m_fTimer += CManager::GetDeltaTime();

	// タイマーのイージング
	float fTime = m_fTimer / bg::TIME_FADE;
	float fRate = easing::EaseOutExpo(fTime);

	// 色の設定
	m_pBg->SetAlpha(bg::INIT_COL.a + bg::DIFF_ALPHA * fRate);

	if (bg::TIME_FADE < m_fTimer)
	{// フェード状態の終了
		m_state = E_State::STATE_APPERCAPTION;
		m_fTimer = 0.0f;
		return;
	}
}

//=====================================================
// キャプション出現状態の更新
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
			// キャプションの移動
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
			// キャプションの移動
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
		// キャプションの移動
		//-----------------------------------------
		D3DXVECTOR3 posCaption = caption::INIT_POS + caption::DIFF_POS * fRate;

		m_pCaption->SetPosition(posCaption);
		m_pCaption->SetVtx();
		m_pCaption->SetAlpha(fRate);

		if (m_fTimer > caption::MOVE_TIME)
		{// 一定時間経過で次の状態に移る
			m_state = E_State::STATE_ENDAPPERCAPTION;
			m_fTimer = 0.0f;
		}
	}
}

//=====================================================
// 入力処理
//=====================================================
void CResult::Input(void)
{
	CInputManager* pInputMgr = CInputManager::GetInstance();

	if (pInputMgr == nullptr)
		return;

	if (!pInputMgr->GetTrigger(CInputManager::E_Button::BUTTON_ENTER)) { return; }

	if (m_state == E_State::STATE_NONE)
	{
		m_state = E_State::STATE_FADE;
	}
	else if (m_state == E_State::STATE_ENDAPPERCAPTION)
	{
		m_state = E_State::STATE_END;
		CFade::GetInstance()->SetFade(CScene::MODE::MODE_TITLE);
	}
}

//=====================================================
// リザルト用UI生成
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
// ランキング用UI作成
//=====================================================
void CResult::CreateRank(void)
{
	// 見出し
	m_pRank = CUI::Create();

	if (m_pRank == nullptr)
		return;

	m_pRank->SetSize(Rank::WIDTH, Rank::HEIGHT);
	m_pRank->SetPosition(Rank::INIT_POS);
	m_pRank->SetCol(Rank::INIT_COL);
	m_pRank->SetVtx();

	int nIdxTexture = Texture::GetIdx(Rank::PATH);
	m_pRank->SetIdxTexture(nIdxTexture);

	// 順位
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
// 保存
//=====================================================
void CResult::Save(void)
{
	// ファイルを開く
	std::ofstream File(FILE_PATH, std::ios::binary);
	if (!File.is_open()) {
		return;
	}

	int size = m_aRankScore.size();

	// ベクトルのサイズをセーブ
	File.write(reinterpret_cast<const char*>(&size), sizeof(size));

	// データをバイナリファイルに書き出す
	File.write(reinterpret_cast<char*>(m_aRankScore.data()), size * sizeof(int));

	// ファイルを閉じる
	File.close();
}

//=====================================================
// 読み込み
//=====================================================
void CResult::Load(void)
{
	m_aRankScore.clear();
	m_aRankScore.resize(Result_Rank::NUM);

	// ファイルを開く
	std::ifstream File(FILE_PATH, std::ios::binary);
	if (!File.is_open()) {
		// 例外処理

		for (int i = 0; i < m_aRankScore.size(); i++)
		{
			m_aRankScore[i] = i;
		}

		return;
	}

	// サイズ読み込み
	int size = 0;
	File.read(reinterpret_cast<char*>(&size), sizeof(size));
	File.read(reinterpret_cast<char*>(m_aRankScore.data()), size * sizeof(int));

	// ファイルを閉じる
	File.close();
}

//=====================================================
// ソート
//=====================================================
void CResult::Sort(void)
{
	if (m_aRankScore.size() <= 1) { return; }

	// ランクインを確認
	if (m_ClearList.size() >= m_aRankScore[m_aRankScore.size() - 1])
	{
		m_aRankScore[m_aRankScore.size() - 1] = m_ClearList.size();
	}

	// ソート
	for (int i = 0; i < Result_Rank::NUM; i++)
	{
		int temp = i;

		for (int j = i + 1; j < Result_Rank::NUM; j++)
		{
			// 昇順ソート
			if (m_aRankScore[j] >= m_aRankScore[temp])
			{
				// 記憶
				temp = j;
			}
		}

		// 変更された
		if (i != temp)
		{
			int score = m_aRankScore[temp];
			m_aRankScore[temp] = m_aRankScore[i];
			m_aRankScore[i] = score;
		}
	}
}