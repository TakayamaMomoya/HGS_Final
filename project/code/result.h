//*****************************************************
//
// リザルト処理[result.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************
// インクルード
//*****************************************************
#include "scene.h"
#include "present.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CMotion;
class CUI;
class CNumber;

namespace Result_Rank
{
	const int NUM = 3;
}

//*****************************************************
// クラスの定義
//*****************************************************
class CResult : public CScene
{
private:

	// 一人ごとの情報
	struct SCharaInfo
	{
		CMotion* pCharacter;
		CPresent* pPresent;

		// コンストラクタ
		SCharaInfo() : pCharacter(nullptr), pPresent(nullptr) {}
	};

	enum E_State
	{
		STATE_NONE = 0,			// 何もしてない状態
		STATE_FADE,				// フェード状態
		STATE_APPERCAPTION,		// 見出し出現状態
		STATE_ENDAPPERCAPTION,	// 見出し出現終了状態
		STATE_END,				// 終了状態
		STATE_MAX
	};

public:
	static constexpr int MAX_TIME = 120;	// 最大時間

	CResult();	// コンストラクタ
	~CResult() {};	// デストラクタ

	static CResult* GetInstance(void) { return m_pResult; }
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update();
	virtual void Draw();

private:

	// メンバ変数
	void UpdateCamera(void);
	void MotionSet(void);
	void PursueCamera(void);
	void EndCamera(void);
	void InitCharacter(void);
	void Ui_Init(void);

	void Create2D(void);		// 2DUIの生成
	void CreateCaption(void);	// 見出しの生成
	void CreateBg(void);		// 背景の生成
	void CreateMyResult(void);	// 自身のリザルトの生成
	void CreateRank(void);		// ランキングの生成

	void UpdateFade(void);			// フェード状態の更新
	void UpdateApperCaption(void);	// キャプション出現状態の更新
	void Input(void);

	// 状態更新の関数ポインタ型エイリアス定義
	typedef void (CResult::* FuncUpdateState)(void);

	// 静的メンバ変数
	static FuncUpdateState s_aFuncUpdateState[];	// 状態更新関数

	// 静的メンバ変数
	static CResult* m_pResult;	// 自身のポインタ

	// メンバ変数
	std::vector<SCharaInfo*>::iterator m_CharacterIt;	// キャラクター系情報iterator
	std::vector<SCharaInfo*> m_CharacterList;			// キャラクター系情報リスト
	std::vector<CPresent::E_Label> m_ClearList;			// クリアラベルリスト
	SCharaInfo m_LastInfo;								// 失敗キャラ用
	float m_fCnt;			// キャラクター遷移用カウント
	bool m_bEnd;			// 終了フラグ
	int m_nKeyOld;			// 最後のキャラの前回のキー
	D3DXVECTOR3 m_camerastart;	// カメラの開始地点
	float m_fTimer;	// タイマー
	E_State m_state;		// 状態

	// UI用変数
	CUI* m_pBg;			// 背景のポインタ
	CUI* m_pCaption;	// 見出しのポインタ
	CUI* m_pMyResult;	// 見出しのポインタ
	CUI* m_pRank;		// 見出しのポインタ
	CNumber* m_pMyScore;
	CUI* m_apRank[Result_Rank::NUM];	// 見出しのポインタ
	CNumber* m_apRankScore[Result_Rank::NUM];
	std::vector<int> m_aRankScore;
};

#endif
