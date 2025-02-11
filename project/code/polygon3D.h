//*****************************************************
//
// 3Dポリゴンの処理[polygon3D.h]
// Author:��山桃也
//
//*****************************************************
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object3D.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CPolygon3D : public CObject3D
{
public:
	enum MODE
	{
		MODE_NORMAL = 0,	// 通常モード
		MODE_BILLBOARD,	// ビルボード
		MODE_STRETCHBILLBOARD,	// ストレッチビルボード
		MODE_MAX
	};

	CPolygon3D(int nPriority = 4);	// コンストラクタ
	~CPolygon3D();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPolygon3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f });
	float GetWidth(void) { return m_width; }	// サイズ取得
	float GetHeight(void) { return m_heigth; }	// サイズ取得
	void SetSize(float width, float height);
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }
	int GetIdxTexture(void) { return m_nIdxTexture; }
	D3DXCOLOR GetColor(void) { return m_col; }
	void SetColor(D3DXCOLOR col);
	void SetAlpha(float fValue) { m_col.a = fValue; SetColor(m_col); }
	void SetTex(D3DXVECTOR2 rd, D3DXVECTOR2 lu);
	void SetFactSB(float fFact) { m_fFactSB = fFact; }
	void SetVtx(void);
	void SetMode(MODE mode);
	MODE GetMode(void) { return m_mode; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	LPDIRECT3DVERTEXBUFFER9 CreateVtxBuff(int nNumVtx = 4);

private:
	void SetVtxNormal(void);
	void SetVtxStretchBillboard(void);
	void SetMtx(void);
	void SetMtxBillboard(void);

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	D3DXVECTOR3 m_posOld;				// 前回の位置
	D3DXCOLOR m_col;					// 色
	float m_width;						// 幅
	float m_heigth;						// 高さ
	float m_fFactSB;					// ストレッチビルボードのときの見やすさの補正
	int m_nIdxTexture;					// テクスチャの番号
	int m_nNumVtx;						// 頂点数
	MODE m_mode;						// モード
};

#endif