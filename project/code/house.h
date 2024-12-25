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
#include "present.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CUI;

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
	bool CheckCover(D3DXVECTOR3 pos);					// 被りチェック
	CPresent* GetPresent(void) { return m_pPresent; }	// プレゼント
	void SetPresent(CPresent* pPresent);
	CPresent::E_Label GetLabelWant(void) { return m_labelWant; }	// 欲しているラベル
	void SetLabelWant(CPresent::E_Label label) { m_labelWant = label; }

	// 静的メンバ関数
	static void SetHouseRandom(void);			// ランダムに家を配置する処理
	static void BindPresent(void);				// プレゼントの割り振り
	static CHouse *Create(void);				// 生成処理
	static CListManager<CHouse>* GetList(void); // リスト取得

private:
	// 静的メンバ変数
	static CListManager<CHouse>* m_pList;		// オブジェクトリスト

	// メンバ変数
	CListManager<CHouse>::AIterator m_iterator; // イテレーター
	CPresent* m_pPresent;						// プレゼント
	CPresent::E_Label m_labelWant;				// 欲しているラベル
	CUI* m_pUI;									// 欲しているラベルの画像
};

namespace house
{
void GetTwoLabel(CPresent::E_Label &labelFirst, CPresent::E_Label &labelSecond);
}

#endif