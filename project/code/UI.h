//*****************************************************
//
// UIÌ[UI.h]
// Author:ûüRç
//
//*****************************************************
#ifndef _UI_H_
#define _UI_H_

//*****************************************************
// CN[h
//*****************************************************
#include "polygon2D.h"

//*****************************************************
// NXÌè`
//*****************************************************
class CUI	: public CPolygon2D
{
public:
	CUI(int nPriority = 6);	// RXgN^
	~CUI() override;		//	fXgN^

	// oÖ
	static CUI *Create(void);	// ¶¬
	HRESULT Init(void);			// ú»
	void Uninit(void);			// I¹
	void Update(void);			// XV
	void Draw(void);			// `æ

	// Ïæ¾EÝèÖ
	void SetSize(float width, float height) override;	// TCY
	D3DXVECTOR2 GetSize(void) override;
	void SetWidth(float width) override;	// 
	void SetHeight(float height) override;	// ³
	float GetWidth(void) override;
	float GetHeight(void) override;
	virtual void SetPosition(D3DXVECTOR3 pos);	// Êu
	virtual D3DXVECTOR3 GetPosition(void);

private:
};

#endif