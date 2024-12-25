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
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************

//*****************************************************
// クラスの定義
//*****************************************************
class CPresent : public CObject
{
public:
	// 構造体定義
	struct S_InfoPresent
	{// プレゼント情報
		string pathThumnail;	// サムネイル
		string pathModel;		// モデル
		int nID;				// ID
	};

	CPresent(int nPriority = 5);	// コンストラクタ
	~CPresent();					// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static void Load(void);			// 読込
	static void Unload(void);		// 破棄
	static CPresent *Create(void);	// 生成処理

private:
	// 静的メンバ変数
	static vector<S_InfoPresent*> s_aInfoPresnt;	// プレゼント情報の配列
};

#endif