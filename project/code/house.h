//*****************************************************
//
// 家の処理[house.cpp]
// Author:髙山桃也
//
//*****************************************************
#ifndef _HOUSE_H_
#define _HOUSE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "objectX.h"

//*****************************************************
// 前方宣言
//*****************************************************

//*****************************************************
// クラスの定義
//*****************************************************
class CHouse : public CObjectX
{
public:
	CHouse(int nPriority = 5);	// コンストラクタ
	~CHouse();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static void SetHouseRandom(void);			// ランダムに家を配置する処理
	static bool CheckCover(D3DXVECTOR3 pos);				// 被りチェック
	static CHouse *Create(void);				// 生成処理
	static CListManager<CHouse>* GetList(void); // リスト取得

private:

	// 静的メンバ変数
	static CListManager<CHouse>* m_pList; // オブジェクトリスト

	// メンバ変数
	CListManager<CHouse>::AIterator m_iterator; // イテレーター

};

#endif