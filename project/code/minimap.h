//*****************************************************
//
// ミニマップの処理[minimap.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CUI;

//*****************************************************
// クラスの定義
//*****************************************************
class CMinimap : public CObject
{
public:
	CMinimap(int nPriority = 3);	// コンストラクタ
	~CMinimap();					// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CMinimap *Create(void);	// 生成処理

private:
	// メンバ関数
	void CreatePolygon(void);	// ポリゴンの生成
	void FollowPlayer(void);	// 追従

	// メンバ変数
	CUI* m_pBg;		// 背景のポインタ
	CUI* m_pPlayer;	// プレイヤーアイコンのポインタ
};

#endif