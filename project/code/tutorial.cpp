//*****************************************************
//
// チュートリアル処理[tutorial.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "tutorial.h"
#include "camera.h"
#include "cameraState.h"

#include "UI.h"
#include "texture.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "inputManager.h"
#include "sound.h"
#include "fade.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{

}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CTutorial *CTutorial::s_pTutorial = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CTutorial::CTutorial(): 
m_bFade(false)
{
	s_pTutorial = this;
}

//=====================================================
// デストラクタ
//=====================================================
CTutorial::~CTutorial()
{
	s_pTutorial = nullptr;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CTutorial::Init(void)
{
	// シーンの初期化
	if (FAILED(CScene::Init()))
	{ // 初期化に失敗した場合

		return E_FAIL;
	}

	// チュートリアル画像を表示
	CUI* ui = CUI::Create();
	ui->SetIdxTexture(Texture::GetIdx("data\\TEXTURE\\tutorial.png"));
	ui->SetSize(0.5f, 0.5f);
	ui->SetPosition({ 0.5f, 0.5f, 0.0f });

	// カメラの設定
	Camera::ChangeState(new CFollowPlayer);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CTutorial::Uninit(void)
{
	// シーンの終了
	CScene::Uninit();

	// オブジェクト全破棄
	CObject::ReleaseAll();
}

//=====================================================
// 更新処理
//=====================================================
void CTutorial::Update(void)
{
	// 入力情報の取得
	CInputKeyboard* pInputKeyboard = CInputKeyboard::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	// ボタン入力がない場合関数を抜ける
	if (!pInputKeyboard->GetTrigger(DIK_SPACE) &&
		!pInputKeyboard->GetTrigger(DIK_RETURN) &&
		!pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
	{ return; }

	// フェードを設定
	CFade::GetInstance()->SetFade(CScene::MODE_GAME);
}

//=====================================================
// 描画処理
//=====================================================
void CTutorial::Draw(void)
{
	// シーンの描画
	CScene::Draw();
}