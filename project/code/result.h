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

	// 静的メンバ変数
	std::vector<SCharaInfo*>::iterator m_CharacterIt;	// キャラクター系情報iterator
	std::vector<SCharaInfo*> m_CharacterList;			// キャラクター系情報リスト
	std::vector<CPresent::E_Label> m_ClearList;			// クリアラベルリスト
	SCharaInfo m_LastInfo;								// 失敗キャラ用
	float m_fCnt;			// キャラクター遷移用カウント
	bool m_bEnd;			// 終了フラグ
	int m_nKeyOld;			// 最後のキャラの前回のキー
	D3DXVECTOR3 m_camerastart;	// カメラの開始地点
	static CResult* m_pResult;	// 自身のポインタ
};

#endif
