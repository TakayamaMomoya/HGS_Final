//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:髙山桃也
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
#include "shadow.h"
#include "MyEffekseer.h"
#include "gameManager.h"

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
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
vector<CPlayer*> CPlayer::s_apPlayer;	// 格納用の配列

//=====================================================
// コンストラクタ
//=====================================================
CPlayer::CPlayer(int nPriority) : m_state(STATE_NONE), m_bEnableInput(false), m_fragMotion(), m_nID(0), m_pShadow(nullptr)
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
	CMotion::Init();

	InitPose(0);

	// 入力可能フラグを設定
	m_bEnableInput = true;

	// 状態設定
	m_state = STATE_NORMAL;

	// 影の生成
	m_pShadow = CShadow::Create();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CPlayer::Uninit(void)
{
	Object::DeleteObject((CObject**)&m_pShadow);

	for (auto itr = s_apPlayer.begin(); itr < s_apPlayer.end(); itr++)
	{
		//削除対象じゃない場合
		if (*itr != this)
			continue;

		//Vectorから削除
		s_apPlayer.erase(itr);

		break;
	}

	// 継承クラスの終了
	CMotion::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CPlayer::Update(void)
{
	// 入力処理
	Input();

	// モーションの管理
	ManageMotion();

	// 影の追従
	if (m_pShadow != nullptr)
		m_pShadow->SetPosition(GetPosition());

	// モーション更新
	CMotion::Update();

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

	// 向きの補正
	FactingRot();

	// 移動量の減衰
	DecreaseMove();
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

	// 移動量の反映
	Translate(move);
}

//=====================================================
// 移動量減衰
//=====================================================
void CPlayer::DecreaseMove(void)
{
	D3DXVECTOR3 move = GetMove();

	// 移動量の減衰
	move.x *= RATE_DECREASE_MOVE;
	move.z *= RATE_DECREASE_MOVE;

	SetMove(move);
}

//=====================================================
// 向きの補正
//=====================================================
void CPlayer::FactingRot(void)
{
	if (m_pInputMgr == nullptr)
		return;

	// 突っつきモーション中は行わない
	int nMotion = GetMotion();
	if (nMotion == MOTION_PECK || nMotion == MOTION_CANNOTPECK)
		return;

	// 目標方向の設定
	CInputManager::S_Axis axis = m_pInputMgr->GetAxis();
	D3DXVECTOR3 axisMove = axis.axisMove;

	// 軸を正規化
	float fLengthAxis = D3DXVec3Length(&axisMove);

	if (fLengthAxis >= LINE_FACT_ROT)
	{// 入力がしきい値を越えていたら補正
		// 目標の向きに補正する
		float fRotDest = atan2f(-axisMove.x, -axisMove.z);

		D3DXVECTOR3 rot = GetRotation();
		universal::FactingRot(&rot.y, fRotDest, FACT_ROTATION);
		SetRotation(rot);
	}
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

	if (pDebugProc == nullptr || pInputKeyboard == nullptr || pJoypad == nullptr || pInputMgr == nullptr || m_pShadow == nullptr)
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
	CMotion::Draw();
}

//=====================================================
// 影の位置設定
//=====================================================
void CPlayer::SetShadowPos(D3DXVECTOR3 pos)
{
	if (m_pShadow != nullptr)
		m_pShadow->SetJustPosition(pos);
}

//=====================================================
// 全プレイヤーの入力フラグ設定
//=====================================================
void CPlayer::EnableInputAll(bool bValue)
{
	for (CPlayer *pPlayer : s_apPlayer)
		pPlayer->EnableInput(bValue);
}