//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:髙山桃也
//
//*****************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "motion.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CInputManager;
class CShadow;

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayer : public CMotion
{
public:
	// モーション列挙
	enum MOTION
	{
		MOTION_NEUTRAL = 0,
		MOTION_WALK,
		MOTION_STARTJUMP,
		MOTION_STAYJUMP,
		MOTION_LANDING,
		MOTION_PECK,
		MOTION_FLOW,
		MOTION_VICTORY,
		MOTION_FAIL,
		MOTION_GUTS,
		MOTION_NECKSHAKE,
		MOTION_UNYO,	// 首うね
		MOTION_CANNOTPECK,
		MOTION_MULTIAPPEAR,
		MOTION_WINGPTPT,	// 羽根パタパタ
		MOTION_STOMACH,		// 腹ベタ
		MOTION_FALL,
		MOTION_BLOW,		// 吹き飛び
		MOTION_STANDUP,		// 立ち上がり
		MOTION_MAX
	};
	// プレイヤー状態
	enum E_State
	{
		STATE_NONE = 0,		// 何でもない状態
		STATE_NORMAL,		// 通常
		STATE_DEATH,		// 死
		STATE_MAX
	};

	CPlayer(int nPriority = 5);	// コンストラクタ
	~CPlayer();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	virtual void Hit(float fDamage) override;	// ヒット処理
	void VibJoypad(float fPow, int nFrame);		// ジョイパッドを振動させる

	// 取得・設定
	void SetMove(D3DXVECTOR3 move) { m_move = move; }				// 移動量
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void EnableInput(bool bEnable) { m_bEnableInput = bEnable; }	// 入力可能フラグ
	bool IsEnableInput(void) { return m_bEnableInput; }
	void SetState(E_State state) { m_state = state; }				// 状態
	E_State GetState(void) { return m_state; }
	void BindInputMgr(CInputManager *pInputMgr) { m_pInputMgr = pInputMgr; }	// 入力マネージャー
	CInputManager *GetInpuManager(void) { return m_pInputMgr; }
	void SetID(int nID) { m_nID = nID; }	// 番号
	int GetID(void) { return m_nID; }
	void SetShadowPos(D3DXVECTOR3 pos);

	// 静的メンバ関数
	static CPlayer* Create(void);										// 生成処理
	static vector<CPlayer*> GetInstance(void) { return s_apPlayer; }	// インスタンスの取得
	static void EnableInputAll(bool bValue);							// 全プレイヤーの入力フラグ設定
	static int GetNumPlayer(void) { return (int)s_apPlayer.size(); }	// プレイヤー数の取得

private:
	// 構造体定義
	struct S_FragMotion
	{// モーションフラグの構造体
		bool bWalk;		// 歩行
		bool bPeck;		// 突っつき
		bool bJump;		// ジャンプ
	};

	// メンバ関数
	void Input(void);		// 入力
	
	void MoveAnalog(void);		// アナログ移動
	void InputMoveAnalog(void);	// アナログ移動入力
	void Forward(void);			// 前進処理
	void DecreaseMove(void);	// 移動量の減衰
	void FactingRot(void);		// 向きの補正
	
	void Event(EVENT_INFO* pEventInfo) override;	// モーションイベント
	void ManageMotion(void);						// モーションの管理

	void Debug(void);	// デバッグ処理

	// メンバ変数
	int m_nID;					// 番号
	bool m_bEnableInput;		// 入力可能フラグ
	D3DXVECTOR3 m_move;			// 移動量
	E_State m_state;			// プレイヤー状態
	CShadow *m_pShadow;			// 影のポインタ
	S_FragMotion m_fragMotion;	// モーションフラグ
	CInputManager *m_pInputMgr;	// 入力マネージャー

	// 静的メンバ変数
	static vector<CPlayer*> s_apPlayer;	// 格納用の配列
};

#endif