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
#include "MyEffekseer.h"
#include "gameManager.h"
#include "navigation.h"

#include "house.h"
#include "UI.h"
#include "present.h"
#include "gauge.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const std::string PATH_BODY = "data\\MOTION\\motionTonakai.txt";	// ボディのパス
const float MODEL_SCALE = 10.0f; // 拡大率

const float RATE_DECREASE_MOVE = 0.5f;	// 移動減衰の割合
const float LINE_FACT_ROT = 0.3f;		// 向きを補正するまでの入力しきい値
const float FACT_ROTATION = 0.1f;		// 回転係数
const float SPEED_MOVE = 20.0f;			// 移動速度

const float INTERACT_LENGTH = 1000.0f; // インタラクト表示が出る範囲
const D3DXVECTOR3 UI_SIZE = { 0.025f, 0.05f, 0.0f }; // インタラクトUIのサイズ
const D3DXVECTOR3 UI_OFFSET = { 0.0f, 600.0f, 0.0f }; // インタラクトUIのオフセット

const D3DXVECTOR3 PRESENT_OFFSET = { 0.0f, 300.0f, 0.0f }; // プレゼントのオフセット

const int POWERUP_NUM = 5; // 加速に必要な連続正解数
const float POWER_RATE = 2.0f; // 加速倍率

const float POWER_GAUGE = 5.0f;							// 連続正解ゲージの最大値
const float POWER_ADD = 1.0f;		// １正解で加算されるゲージの量
const D3DXVECTOR3 GAUGE_POS = { 0.8f, 0.93f, 0.0f };	// ゲージの位置
const D3DXVECTOR2 GAUGE_SIZE = { 0.2f, 0.07f };		// ゲージのサイズ
const float RADIUS_COLLISION = 200.0f;					// 判定の半径

const float SAB_TIME = 10.0f; // ゲージが減少するまでの時間

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
m_pNearHouse(nullptr),
m_nAnswerCount(0),
m_pGauge(nullptr),
m_pCollision(nullptr),
m_fSabTime(0.0f)
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

	// 大きくする
	SetScale(MODEL_SCALE);

	// ゲージを生成
	m_pGauge = CGauge::Create(POWER_GAUGE, GAUGE_SIZE);
	m_pGauge->SetPosition(GAUGE_POS);

	// プレゼントを生成
	m_pPresent = CPresent::Create();

	// 入力可能フラグを設定
	m_bEnableInput = true;

	// 状態設定
	m_state = STATE_NORMAL;

	// 判定の生成
	m_pCollision = CCollisionSphere::Create(CCollision::TAG_PLAYER, CCollision::TYPE::TYPE_SPHERE, this);

	if (m_pCollision != nullptr)
	{
		m_pCollision->SetRadius(RADIUS_COLLISION);
	}

	// ナビゲーション生成
	CNavigation::Create();

	EnableShadow(true);

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

	if (m_pCollision != nullptr)
	{
		m_pCollision->Uninit();
		m_pCollision = nullptr;
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

	// ゲージの操作
	ControlGauge();

	CDebugProc::GetInstance()->Print("\n\n\n\n\n\n\nゲージの数字 : %f\n\n\n\n\n\n", m_pGauge->GetParam());

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

	// 判定の追従
	if (m_pCollision != nullptr)
	{// 球の判定の追従
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 posInit = pos;

		m_pCollision->SetPosition(pos);

		// ブロック判定
		m_pCollision->PushCollision(&pos, CCollision::TAG::TAG_BLOCK);

		pos.y = posInit.y;

		// 位置制限
		CHouse::LimitPos(pos);

		// キャラの位置反映
		SetPosition(pos);
	}

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

		// 移動速度の設定
		D3DXVECTOR3 move = GetMove();

		// 向いている方向にベクトルを伸ばす
		vecMove -= {sinf(rot.y) * fSpeed, 0.0f, cosf(rot.y) * fSpeed};
		move += vecMove;

		SetMove(move);

		// 目標向きの設定
		float fRotDest = atan2f(axisMove.x, axisMove.z) + D3DX_PI;
		SetRotDest(fRotDest);

		m_fragMotion.bWalk = true;
	}
	else
		m_fragMotion.bWalk = false;

	if (m_pGauge->GetParam() >= POWER_GAUGE)
	{
		fSpeed *= POWER_RATE;
	}
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
		// クリアフラグがたっていた場合次に進む
		if(house->IsClear()) continue;

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
	CDebugProc::GetInstance()->Print("連続正解カウンター : %d\n", m_nAnswerCount);

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

	// 正解のプレゼントだった場合カウンターを加算する
	if (m_pNearHouse->GetLabelWant() == m_pPresent->GetLabel())
	{
		m_fSabTime = 0.0f;
		++m_nAnswerCount;
		m_pGauge->AddParam(POWER_ADD);
	}
	else
	{
		// 間違えていた場合カウンターを初期化
		m_fSabTime = 0.0f;
		m_nAnswerCount = 0;
		m_pGauge->SetParam(0.0f);
	}

	// 自身の所持しているプレゼントを上書きする
	m_pPresent = pTemp;
}

//==========================================
//  ゲージの操作
//==========================================
void CPlayer::ControlGauge()
{
	// ゲージが最大の場合関数を抜ける
	if (m_pGauge->GetParam() >= POWER_GAUGE) { return; }

	// ゲージ減少時間を加算する
	m_fSabTime += CManager::GetDeltaTime();

	// 一定時間経過していない場合関数を抜ける
	if (m_fSabTime < SAB_TIME) { return; }

	// ゲージを減らす
	m_pGauge->AddParam(-0.01f);
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
		if (m_pGauge->GetParam() >= POWER_GAUGE)
		{
			if (nMotion != MOTION::MOTION_WALKTWOLEG)
				SetMotion(MOTION::MOTION_WALKTWOLEG);
		}
		else
		{
			if (nMotion != MOTION::MOTION_WALKFOURLEG)
				SetMotion(MOTION::MOTION_WALKFOURLEG);
		}
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