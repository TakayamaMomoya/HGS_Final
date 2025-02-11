//*****************************************************
//
// シーン処理[scene.h]
// Author:��山桃也
//
//*****************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"

//*****************************************************
// 前方宣言
//*****************************************************

//*****************************************************
// クラスの定義
//*****************************************************
class CScene
{
public:
	enum MODE
	{
		MODE_LOGO = 0,
		MODE_TITLE,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	};

	CScene();	// コンストラクタ
	~CScene();	// デストラクタ

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update();
	virtual void Draw();
	static CScene *Create(MODE mode);
	int GetTimer(void) { return m_nTimerTrans; }
	void SetTimer(int nTime) { m_nTimerTrans = nTime; }

private:
	void CreateLight(void);	// ライトの生成

	int m_nTimerTrans;	// 遷移タイマー
};

#endif