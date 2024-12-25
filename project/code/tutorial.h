//*****************************************************
//
// チュートリアル処理[tutorial.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************
// インクルード
//*****************************************************
#include "scene.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CTutorial : public CScene
{
public:
	CTutorial();	// コンストラクタ
	~CTutorial();	// デストラクタ

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	
	// 静的メンバ関数
	static CTutorial *GetInstance(void) { return s_pTutorial; }	// インスタンス取得

private:
	// 静的メンバ変数
	static CTutorial *s_pTutorial;					// 自身のポインタ
	
	// メンバ変数
	bool m_bFade;
};

#endif