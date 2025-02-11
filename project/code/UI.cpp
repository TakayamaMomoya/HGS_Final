//*****************************************************
//
// UIÌ[UI.cpp]
// Author:ûüRç
//
//*****************************************************

//*****************************************************
// CN[h
//*****************************************************
#include "UI.h"
#include "UIManager.h"
#include "blur.h"

//=====================================================
// DæÊðßéRXgN^
//=====================================================
CUI::CUI(int nPriority) : CPolygon2D(nPriority)
{

}

//=====================================================
// fXgN^
//=====================================================
CUI::~CUI()
{

}

//=====================================================
// ¶¬
//=====================================================
CUI *CUI::Create(void)
{
	CUI *pUI = nullptr;

	if (pUI == nullptr)
	{
		// CX^X¶¬
		pUI = new CUI;

		if (pUI != nullptr)
		{
			// ú»
			pUI->Init();
		}
	}

	return pUI;
}

//=====================================================
// ú»
//=====================================================
HRESULT CUI::Init(void)
{
	CPolygon2D::Init();
	
	return S_OK;
}

//=====================================================
// I¹
//=====================================================
void CUI::Uninit(void)
{
	CPolygon2D::Uninit();
}

//=====================================================
// XV
//=====================================================
void CUI::Update(void)
{
	CPolygon2D::Update();
}

//=====================================================
// `æ
//=====================================================
void CUI::Draw(void)
{
	bool bDisp = true;

	CUIManager *pUIManager = CUIManager::GetInstance();

	if (pUIManager != nullptr)
	{// `æ·é©Ìæ¾
		bDisp = pUIManager->IsDisp();
	}

	if (bDisp)
	{
		CPolygon2D::Draw();
	}
}

//=====================================================
// TCYÌÝè
//=====================================================
void CUI::SetSize(float width, float height)
{
	float fWidth;
	float fHeigth;

	fWidth = SCREEN_WIDTH * width;
	fHeigth = SCREEN_HEIGHT * height;

	CPolygon2D::SetSize(fWidth, fHeigth);
}

//=====================================================
// TCYÌæ¾
//=====================================================
D3DXVECTOR2 CUI::GetSize(void)
{
	D3DXVECTOR2 size = CPolygon2D::GetSize();

	size.x /= SCREEN_WIDTH;
	size.y /= SCREEN_HEIGHT;

	return size;
}

//=====================================================
// ÌÝè
//=====================================================
void CUI::SetWidth(float width)
{
	float fWidth = SCREEN_WIDTH * width;
	CPolygon2D::SetSize(fWidth, CPolygon2D::GetHeight());
}

//=====================================================
// ³ÌÝè
//=====================================================
void CUI::SetHeight(float height)
{
	float fHeigth = SCREEN_HEIGHT * height;
	CPolygon2D::SetSize(CPolygon2D::GetWidth(), fHeigth);
}

//=====================================================
// Ìæ¾
//=====================================================
float CUI::GetWidth(void)
{
	return GetSize().x;
}

//=====================================================
// ³Ìæ¾
//=====================================================
float CUI::GetHeight(void)
{
	return GetSize().y;
}

//=====================================================
// ÊuÝè
//=====================================================
void CUI::SetPosition(D3DXVECTOR3 pos)
{
	pos.x *= SCREEN_WIDTH;
	pos.y *= SCREEN_HEIGHT;

	CGameObject::SetPosition(pos);
	SetVtx();
}

//=====================================================
// Êuæ¾
//=====================================================
D3DXVECTOR3 CUI::GetPosition(void)
{
	D3DXVECTOR3 pos = CPolygon2D::GetPosition();

	pos.x /= SCREEN_WIDTH;
	pos.y /= SCREEN_HEIGHT;

	return pos;
}