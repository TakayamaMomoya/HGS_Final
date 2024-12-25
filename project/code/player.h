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
#include "character.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CInputManager;
class CShadow;
class CUI;
class CPresent;
class CHouse;
class CGauge;
class CCollisionSphere;

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayer : public CCharacter
{
public:
	// モーション列挙
	enum MOTION
	{
		MOTION_NEUTRAL = 0,
		MOTION_WALK,
		MOTION_WALKFOURLEG,
		MOTION_WALKTWOLEG,
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
	void EnableInput(bool bEnable) { m_bEnableInput = bEnable; }	// 入力可能フラグ
	bool IsEnableInput(void) { return m_bEnableInput; }
	void SetState(E_State state) { m_state = state; }				// 状態
	E_State GetState(void) { return m_state; }
	void BindInputMgr(CInputManager *pInputMgr) { m_pInputMgr = pInputMgr; }	// 入力マネージャー
	CInputManager *GetInpuManager(void) { return m_pInputMgr; }
	CPresent* GetPresent(void) { return m_pPresent; }	// プレゼント
	void SetID(int nID) { m_nID = nID; }	// 番号
	int GetID(void) { return m_nID; }

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

	void Interact(); // インタラクト表示

	void SwapPresent(); // プレゼントを交換する処理

	void ControlGauge(); // ゲージの操作

	void Event(EVENT_INFO* pEventInfo) override;	// モーションイベント
	void ManageMotion(void);						// モーションの管理

	void Debug(void);	// デバッグ処理

	// メンバ変数
	int m_nID;					// 番号
	bool m_bEnableInput;		// 入力可能フラグ
	E_State m_state;			// プレイヤー状態
	S_FragMotion m_fragMotion;	// モーションフラグ
	CInputManager *m_pInputMgr;	// 入力マネージャー
	CUI* m_pInteract;			// インタラクトUI
	CPresent* m_pPresent;		// プレゼントのポインタ
	CHouse* m_pNearHouse;			// 近い建物のポインタ
	CCollisionSphere *m_pCollision;	// 当たり判定
	
	unsigned int m_nAnswerCount; // 連続正解カウンター
	CGauge* m_pGauge; // 連続正解ゲージ
	float m_fSabTime; // ゲージが減少するまでの時間

	// 静的メンバ変数
	static vector<CPlayer*> s_apPlayer;	// 格納用の配列
};

#endif