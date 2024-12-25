//*****************************************************
//
// プレゼントの処理[present.cpp]
// Author:髙山桃也
//
//*****************************************************
#ifndef _PRESENT_H_
#define _PRESENT_H_

//*****************************************************
// インクルード
//*****************************************************
#include "motion.h"

//*****************************************************
// 前方宣言
//*****************************************************

//*****************************************************
// クラスの定義
//*****************************************************
class CPresent : public CMotion
{
public:
	// 構造体定義
	struct S_InfoPresent
	{// プレゼント情報
		string pathThumnail;	// サムネイル
		string pathModel;		// モデル
		int nID;				// ID
	};
	// 列挙型定義
	enum E_Label
	{// ラベルの種類
		LABEL_BLUE = 0,		// 青
		LABEL_GREEN,		// 緑
		LABEL_PUPLE,		// 紫
		LABEL_YELLOW,		// 黄
		LABEL_MAX,
	};

	CPresent(int nPriority = 5);	// コンストラクタ
	~CPresent();					// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	E_Label GetLabel(void) { return m_label; }	// ラベル

	// 静的メンバ関数
	static void Load(void);																	// 読込
	static void CPresent::LoadInfo(std::ifstream& file, string str, S_InfoPresent *pInfo);
	static void Unload(void);																// 破棄
	static CPresent *Create(E_Label label = LABEL_BLUE);									// 生成処理
	static vector<S_InfoPresent*> GetInfoPresent(void) { return s_aInfoPresnt; }			// プレゼント情報の取得

private:
	// メンバ変数
	E_Label m_label;	// ラベル

	// 静的メンバ変数
	static vector<S_InfoPresent*> s_aInfoPresnt;	// プレゼント情報の配列
};

#endif