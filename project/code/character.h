//*****************************************************
//
// キャラクターの処理[character.h]
// Author:髙山桃也
//
//*****************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "motion.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CShadow;

//*****************************************************
// クラスの定義
//*****************************************************
class CCharacter : public CMotion
{
public:
	CCharacter(int nPriority = 5);	// コンストラクタ
	~CCharacter();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 変数取得・設定関数
	void SetMove(D3DXVECTOR3 move) { m_move = move; }		// 移動量
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetDecMove(float fDec) { m_fDecMove = fDec; }		// 移動減衰係数
	float GetDecMove(void) { return m_fDecMove; }
	void SetRotDest(float fRot) { m_fRotDest = fRot; }		// 目標の向き
	float GetRotDest(void) { return m_fRotDest; }
	void SetFactRot(float fFact) { m_fFactRot = fFact; }	// 回転係数
	float GetFactRot(void) { return m_fFactRot; }
	void SetShadowPos(D3DXVECTOR3 pos);						// 影の位置
	
private:
	// メンバ関数
	void DecreaseMove(void);	// 移動量の減衰
	void FactingRot(void);		// 向きの補正

	// メンバ変数
	D3DXVECTOR3 m_move;			// 移動量
	float m_fDecMove;			// 移動量の減衰係数
	float m_fRotDest;			// 目標の向き
	float m_fFactRot;			// 回転係数
	CShadow *m_pShadow;			// 影のポインタ
};

#endif