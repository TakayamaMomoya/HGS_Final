//*****************************************************
//
// ナビゲーションの処理[navigation.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _NAVIGATION_H_
#define _NAVIGATION_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CPolygon3D;

//*****************************************************
// クラスの定義
//*****************************************************
class CNavigation : public CObject
{
public:
	CNavigation(int nPriority = 3);	// コンストラクタ
	~CNavigation();					// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CreatePolygon(void);	// ポリゴンの生成
	void DeletePolygon(void);	// ポリゴンの破棄

	// 静的メンバ関数
	static CNavigation *Create(void);	// 生成処理

private:
	// メンバ関数
	void FollowPlayer(void);	// 追従
	float CulcRotDest(void);	// 目標向きの計算

	// メンバ変数
	CPolygon3D* m_pPolygon;	// ポリゴンのポインタ
};

#endif