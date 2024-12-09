//*****************************************************
//
// チュートリアルプレイヤーの処理[playerTutorial.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "playerTutorial.h"
#include "inputManager.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{

}

//=====================================================
// コンストラクタ
//=====================================================
CPlayerTutorial::CPlayerTutorial(int nPriority) : CPlayer(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CPlayerTutorial::~CPlayerTutorial()
{

}

//=====================================================
// 生成処理
//=====================================================
CPlayerTutorial* CPlayerTutorial::Create(void)
{
	CPlayerTutorial *pPlayerTutorial = nullptr;

	pPlayerTutorial = new CPlayerTutorial;

	if (pPlayerTutorial != nullptr)
		pPlayerTutorial->Init();

	return pPlayerTutorial;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CPlayerTutorial::Init(void)
{
	// 継承クラスの初期化
	CPlayer::Init();
	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CPlayerTutorial::Uninit(void)
{
	// 継承クラスの終了
	CPlayer::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CPlayerTutorial::Update(void)
{
	// 継承クラスの更新
	CPlayer::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CPlayerTutorial::Draw(void)
{
	// 継承クラスの描画
	CPlayer::Draw();
}