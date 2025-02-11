//*****************************************************
//
// シングルゲームマネージャー[gameManagerSingle.h]
// Author:��山桃也
//
//*****************************************************
#ifndef _GAMEMANAGERSINGLE_H_
#define _GAMEMANAGERSINGLE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "gameManager.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CPlayer;

//*****************************************************
// クラスの定義
//*****************************************************
class CGameManagerSingle : public CGameManager
{
public:
	CGameManagerSingle();	// コンストラクタ
	~CGameManagerSingle() {};	// デストラクタ

	// メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void EndGame(void) override;	// ゲームの終了

	//プレイヤーの取得
	CPlayer* GetPlayer() { return m_pPlayer; }

private:
	// メンバ関数
	void UpdateStart(void) override;	// 開始状態の更新
	void UpdateNormal(void) override;	// 通常状態の更新
	void ManagePlayer(void);			// プレイヤーの管理
	void DeathPlayer(void);				// プレイヤーの死亡

	void UpdateResult(void) override;	// リザルト状態の更新
	void UpdateEnd(void) override;		// 終了状態の更新

	// メンバ変数
	CPlayer *m_pPlayer;		// プレイヤーのポインタ
};

#endif