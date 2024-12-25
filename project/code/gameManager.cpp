//*****************************************************
//
// ゲームマネージャー[gameManager.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "gameManager.h"
#include "gameManagerSingle.h"
#include "UIManager.h"
#include "timer.h"
#include "BG_Ice.h"
#include "UI_ready.h"
#include "sound.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const string PATH_TEX = "data\\TEMP\\mode.txt";	// モードのパス
const string PATH_IDXMAP = "data\\TEMP\\mapIdx.bin";	// マップ番号のパス
const string PATH_WINNER = "data\\TEMP\\winner.bin";	// 勝者のパス
const string PATH_IDXINPUT = "data\\TEMP\\idxInput.txt";	// 入力番号のパス
const int PLAY_SOUND_SEA_COUNT = 60 * 24;	// 静かな海サウンド再生時間（右側変更で秒数変更）
}

//=====================================================
// コンストラクタ
//=====================================================
CGameManager::CGameManager()
{
	m_nCounterSoundSea = 0;
}

//=====================================================
// 生成処理
//=====================================================
CGameManager *CGameManager::Create(CGame::E_GameMode mode)
{
	CGameManager* pGameManager = nullptr;

	pGameManager = new CGameManagerSingle;

	if (pGameManager == nullptr)
		return nullptr;

	pGameManager->Init();

	return pGameManager;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CGameManager::Init(void)
{
	// UIマネージャーの追加
	CUIManager::Create();

#if 0
	//ゲームスタート告知UI
	CUIready::Create();
#endif

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CGameManager::Uninit(void)
{
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CGameManager::Update(void)
{
	// ゲームの状態管理
	ManageGameState();
}

//=====================================================
// ゲームの状態管理
//=====================================================
void CGameManager::ManageGameState(void)
{
	CGame::E_State state = CGame::GetState();

	switch (state)
	{
	case CGame::STATE_READY:

		break;
	case CGame::STATE_START:
		UpdateStart();
		break;
	case CGame::STATE_NORMAL:
		UpdateNormal();
		break;
	case CGame::STATE_RESULT:
		UpdateResult();
		break;
	case CGame::STATE_END:
		UpdateEnd();
		break;
	default:
		assert(false);
		break;
	}
}

//=====================================================
// 開始状態の更新
//=====================================================
void CGameManager::UpdateStart(void)
{

}

//=====================================================
// 通常状態の更新
//=====================================================
void CGameManager::UpdateNormal(void)
{
	m_nCounterSoundSea++;
	if (m_nCounterSoundSea >= PLAY_SOUND_SEA_COUNT)
	{// 音を流す
		m_nCounterSoundSea = 0;
		CSound::GetInstance()->Play(CSound::LABEL_SE_SEA);
	}
}

//=====================================================
// リザルト状態の更新
//=====================================================
void CGameManager::UpdateResult(void)
{

}

//=====================================================
// 終了状態の更新
//=====================================================
void CGameManager::UpdateEnd(void)
{

}

//=====================================================
// 描画処理
//=====================================================
void CGameManager::Draw(void)
{

}