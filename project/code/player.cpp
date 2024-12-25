//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "player.h"
#include "inputManager.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "debugproc.h"
#include "particle.h"
#include "camera.h"
#include "manager.h"
#include "flowIce.h"
#include "effect3D.h"
#include "collision.h"
#include "texture.h"
#include "sound.h"
#include "MyEffekseer.h"
#include "gameManager.h"

#include "house.h"
#include "UI.h"
#include "present.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const std::string PATH_BODY = "data\\MOTION\\motionPenguin.txt";	// ボディのパス

const float RATE_DECREASE_MOVE = 0.5f;	// 移動減衰の割合
const float LINE_FACT_ROT = 0.3f;		// 向きを補正するまでの入力しきい値
const float FACT_ROTATION = 0.1f;		// 回転係数
const float SPEED_MOVE = 5.0f;			// 移動速度

const float INTERACT_LENGTH = 500.0f; // インタラクト表示が出る範囲
const D3DXVECTOR3 UI_SIZE = { 0.03f, 0.06f, 0.0f }; // インタラクトUIのサイズ
const D3DXVECTOR3 UI_OFFSET = { 0.0f, 300.0f, 0.0f }; // インタラクトUIのオフセット

const D3DXVECTOR3 PRESENT_OFFSET = { 0.0f, 300.0f, 0.0f }; // プレゼントのオフセット
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
vector<CPlayer*> CPlayer::s_apPlayer;	// 格納用の配列

//=====================================================
// コンストラクタ
//=====================================================
CPlayer::CPlayer(int nPriority) : m_state(STATE_NONE), m_bEnableInput(false), m_fragMotion(), m_nID(0),
m_pInteract(nullptr),
m_pPresent(nullptr),
m_pNearHouse(nullptr)
{
	// デフォルトは入った順の番号
	m_nID = (int)s_apPlayer.size();

	s_apPlayer.push_back(this);
}

//=====================================================
// デストラクタ
//=====================================================
CPlayer::~CPlayer()
{

}

//=====================================================
// 生成処理
//=====================================================
CPlayer* CPlayer::Create(void)
{
	CPlayer *pPlayer = nullptr;

	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		pPlayer->Init();
	}

	return pPlayer;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CPlayer::Init(void)
{
	// 読込
	Load((char*)&PATH_BODY[0]);

	// 継承クラスの初期化
	CCharacter::Init();

	InitPose(0);

	// プレゼントを生成
	m_pPresent = CPresent::Create();

	// 入力可能フラグを設定
	m_bEnableInput = true;

	// 状態設定
	m_state = STATE_NORMAL;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CPlayer::Uninit(void)
{
	for (auto itr = s_apPlayer.begin(); itr < s_apPlayer.end(); itr++)
	{
		//削除対象じゃない場合
		if (*itr != this)
			continue;

		//Vectorから削除
		s_apPlayer.erase(itr);

		break;
	}

	// UIを削除する
	if (m_pInteract != nullptr)
	{
		m_pInteract->Uninit();
		delete m_pInteract;
		m_pInteract = nullptr;
	}

	// 継承クラスの終了
	CCharacter::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CPlayer::Update(void)
{
	// インタラクト表示処理
	Interact();

	// UIを移動する
	if (m_pInteract != nullptr)
	{
		D3DXVECTOR3 posScreen = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 pos = GetPosition() + UI_OFFSET;
		universal::IsInScreen(pos, &posScreen);
		universal::ConvertScreenRate(posScreen);
		m_pInteract->SetPosition(posScreen);
	}

	// プレゼントを入れ替える処理
	SwapPresent();

	// プレゼントを移動する
	if (m_pPresent != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition() + PRESENT_OFFSET;
		m_pPresent->SetPosition(pos);
	}

	// 入力処理
	Input();

	// モーションの管理
	ManageMotion();

	// モーション更新
	CCharacter::Update();

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// 入力
//=====================================================
void CPlayer::Input(void)
{
	if (m_bEnableInput)
	{
		// アナログ移動
		MoveAnalog();
	}
}

//=====================================================
// アナログ移動
//=====================================================
void CPlayer::MoveAnalog(void)
{
	// アナログ移動入力
	InputMoveAnalog();
}

//=====================================================
// アナログ移動入力
//=====================================================
void CPlayer::InputMoveAnalog(void)
{
	// 前進処理
	Forward();
}

//=====================================================
// 前進処理
//=====================================================
void CPlayer::Forward(void)
{
	if (m_pInputMgr == nullptr)
		return;

	// 目標方向の設定
	CInputManager::S_Axis axis = m_pInputMgr->GetAxis();
	D3DXVECTOR3 axisMove = axis.axisMove;

	// 軸を正規化
	float fLengthAxis = D3DXVec3Length(&axisMove);

	D3DXVECTOR3 vecMove = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 rot = GetRotation();

	float fSpeed = 0.0f;

	if (LINE_FACT_ROT < fLengthAxis)
	{// 移動軸操作がしきい値を越えていたら移動
		fSpeed = SPEED_MOVE;
	}

	// 移動速度の設定
	D3DXVECTOR3 move = GetMove();

	// 向いている方向にベクトルを伸ばす
	vecMove -= {sinf(rot.y) * fSpeed, 0.0f, cosf(rot.y) * fSpeed};
	move += vecMove;

	SetMove(move);

	// 目標向きの設定
	float fRotDest = atan2f(axisMove.x, axisMove.z) + D3DX_PI;
	SetRotDest(fRotDest);
}

//==========================================
//  インタラクト表示
//==========================================
void CPlayer::Interact()
{
	// 建物の情報を取得する
	if (CHouse::GetList() == nullptr) { return; }
	std::list<CHouse*> list = CHouse::GetList()->GetList();    // リストを取得

	// 自身の座標を取得する
	D3DXVECTOR3 pos = GetPosition();

	// プレイヤーリストの中身を確認する
	for (CHouse* house : list)
	{
		// 建物の座標を取得する
		D3DXVECTOR3 posHouse = house->GetPosition();

		// 一定距離内に建物が存在しない場合次に進む
		if (!universal::DistCmp(pos, posHouse, INTERACT_LENGTH, nullptr)) continue;

		// 一定距離内に建物が存在したらポリゴンを表示する
		if (m_pInteract == nullptr)
		{
			m_pInteract = CUI::Create();
			m_pInteract->Init();
			m_pInteract->SetSize(UI_SIZE.x, UI_SIZE.y);
			D3DXVECTOR3 posScreen = { 0.0f, 0.0f, 0.0f };
			D3DXVECTOR3 pos = GetPosition() + UI_OFFSET;
			universal::IsInScreen(pos, &posScreen);
			universal::ConvertScreenRate(posScreen);
			m_pInteract->SetPosition(posScreen);
			m_pInteract->SetIdxTexture(Texture::GetIdx("data\\TEXTURE\\UI\\swap.png"));
		}

		// 近かった建物を記録する
		m_pNearHouse = house;

		return;
	}

	// 建物を最後までチェックしても存在していない場合ポリゴンを削除する
	if (m_pInteract != nullptr)
	{
		m_pInteract->Uninit();
		delete m_pInteract;
		m_pInteract = nullptr;
	}
}

//==========================================
//  プレゼントを交換する処理
//==========================================
void CPlayer::SwapPresent()
{
	CDebugProc::GetInstance()->Print("所持プレゼント : %d\n", m_pPresent);

	// インタラクト表示が存在していない場合関数を抜ける
	if (m_pInteract == nullptr) { return; }

	// 入力情報の取得
	CInputKeyboard* pInputKeyboard = CInputKeyboard::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	// ボタン入力がない場合関数を抜ける
	if (!pInputKeyboard->GetTrigger(DIK_SPACE) && !pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0)){ return; }

	// 最も近い建物のプレゼントを受け取る
	CPresent* pTemp = m_pNearHouse->GetPresent();

	// 最も近い建物にプレゼントを与える
	m_pNearHouse->SetPresent(m_pPresent);

	// 自身の所持しているプレゼントを上書きする
	m_pPresent = pTemp;
}

//=====================================================
// ジョイパッドを振動させる
//=====================================================
void CPlayer::VibJoypad(float fPow, int nFrame)
{
	CInputJoypad* pInputJoypad = CInputJoypad::GetInstance();

	if (pInputJoypad == nullptr)
		return;

	// joypad振動させる
	pInputJoypad->Vibration(m_nID, fPow, nFrame);
}

//=====================================================
// モーションの管理
//=====================================================
void CPlayer::ManageMotion(void)
{
	int nMotion = GetMotion();
	bool bFinish = IsFinish();
	
	if (m_fragMotion.bWalk)
	{// 歩きモーションフラグ有効
		if (nMotion != MOTION::MOTION_WALK)
			SetMotion(MOTION::MOTION_WALK);
	}
	else
	{// 何もフラグが立っていない状態
		if(nMotion != MOTION::MOTION_NEUTRAL)
			SetMotion(MOTION::MOTION_NEUTRAL);
	}
}

//=====================================================
// モーションイベント
//=====================================================
void CPlayer::Event(EVENT_INFO* pEventInfo)
{
	int nMotion = GetMotion();
}

//=====================================================
// ヒット処理
//=====================================================
void CPlayer::Hit(float fDamage)
{
	if (m_state == E_State::STATE_DEATH)
		return;	// 条件によってHit処理を無効化
}

//=====================================================
// デバッグ処理
//=====================================================
void CPlayer::Debug(void)
{
	CDebugProc *pDebugProc = CDebugProc::GetInstance();
	CInputKeyboard *pInputKeyboard = CInputKeyboard::GetInstance();
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();
	CInputManager *pInputMgr = CInputManager::GetInstance();

	if (pDebugProc == nullptr || pInputKeyboard == nullptr || pJoypad == nullptr || pInputMgr == nullptr)
		return;

#if 1
	pDebugProc->Print("\nプレイヤー情報==========================");
	pDebugProc->Print("\n位置[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	pDebugProc->Print("\n移動量[%f,%f,%f]", GetMove().x, GetMove().y, GetMove().z);
	pDebugProc->Print("\n状態[%d]", GetState());
#endif

}

//=====================================================
// 描画処理
//=====================================================
void CPlayer::Draw(void)
{
	// 継承クラスの描画
	CCharacter::Draw();
}

//=====================================================
// 全プレイヤーの入力フラグ設定
//=====================================================
void CPlayer::EnableInputAll(bool bValue)
{
	for (CPlayer *pPlayer : s_apPlayer)
		pPlayer->EnableInput(bValue);
}