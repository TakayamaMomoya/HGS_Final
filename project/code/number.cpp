//*****************************************************
//
// 数字の処理[number.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "UI.h"

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = nullptr;	// テクスチャのポインタ

//=====================================================
// コンストラクタ
//=====================================================
CNumber::CNumber(int nPriority) : CObject(nPriority)
{
	m_nValue = 0;
	m_nNumPlace = 0;
	m_pos = { 0.0f,0.0f,0.0f };
	m_nNumAll = 0;
	m_nIdxTexture = -1;
	ZeroMemory(&m_apObject[0],sizeof(m_apObject));
}

//=====================================================
//	デストラクタ
//=====================================================
CNumber::~CNumber()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CNumber::Init(void)
{
	for (int nCount = 0; nCount < m_nNumPlace; nCount++)
	{
		if (m_apObject[nCount] != nullptr)
		{
			m_apObject[nCount]->SetSize(0.1f, 0.3f);
			m_apObject[nCount]->SetPosition(D3DXVECTOR3(GetPosition().x + 80.0f * nCount, GetPosition().y, GetPosition().z));
		}
	}

	// テクスチャ番号取得
	m_nIdxTexture = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\number00.png");

	for (int nCnt = 0; nCnt < m_nNumPlace; nCnt++)
	{// テクスチャ番号取得
		if (m_apObject[nCnt] != nullptr)
		{
			m_apObject[nCnt]->SetIdxTexture(m_nIdxTexture);
		}
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CNumber::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_PLACE; nCount++)
	{
		if (m_apObject[nCount] != nullptr)
		{
			m_apObject[nCount]->Uninit();
			m_apObject[nCount] = nullptr;
		}
	}

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CNumber::Update(void)
{

}

//=====================================================
// 値設定処理
//=====================================================
void CNumber::SetValue(int nValue)
{
	// 変数宣言
	int aTexU[MAX_PLACE];
	int aData1, aData2;

	m_nValue = nValue;

	for (int nCount = 0; nCount < m_nNumPlace; nCount++)
	{
		if (m_apObject[nCount] != nullptr)
		{
			aData1 = (int)pow(10.0f, m_nNumPlace - nCount);
			aData2 = (int)pow(10.0f, m_nNumPlace - nCount - 1);

			aTexU[nCount] = m_nValue % aData1 / aData2;

			D3DXVECTOR2 leftUp = { 0.0f + 0.1f * aTexU[nCount], 0.0f };
			D3DXVECTOR2 rightDown = { 0.1f + 0.1f * aTexU[nCount], 1.0f };


			m_apObject[nCount]->SetVtx();

			m_apObject[nCount]->SetTex(leftUp, rightDown);
		}
	}
}

//=====================================================
// 位置設定処理
//=====================================================
void CNumber::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;

	for (int nCount = 0; nCount < m_nNumPlace; nCount++)
	{
		if (m_apObject[nCount] != nullptr)
		{
			m_apObject[nCount]->SetPosition(D3DXVECTOR3(pos.x + m_apObject[nCount]->GetWidth() * nCount * 2, pos.y, pos.z));
			m_apObject[nCount]->SetVtx();
		}
	}
}

//=====================================================
// サイズ設定処理
//=====================================================
void CNumber::SetSizeAll(float width, float height)
{
	for (int nCount = 0; nCount < m_nNumPlace; nCount++)
	{
		if (m_apObject[nCount] != nullptr)
		{
			D3DXVECTOR3 pos = D3DXVECTOR3(D3DXVECTOR3(GetPosition().x + width * nCount * 2, GetPosition().y, GetPosition().z));

			m_apObject[nCount]->SetSize(width,height);
			m_apObject[nCount]->SetPosition(pos);
			m_apObject[nCount]->SetVtx();
		}
	}
}

//=====================================================
// テクスチャ設定処理
//=====================================================
void CNumber::SetTex(const char* pFileName)
{
	for (int nCnt = 0; nCnt < m_nNumPlace; nCnt++)
	{// テクスチャ番号取得

		if (m_apObject[nCnt] != nullptr)
		{
			CTexture* pTexture = CTexture::GetInstance();

			if (pTexture != nullptr)
			{
				m_nIdxTexture = pTexture->Regist(pFileName);

				m_apObject[nCnt]->SetIdxTexture(m_nIdxTexture);
				m_apObject[nCnt]->SetVtx();
			}
		}
	}


}
//=====================================================
// 色設定処理
//=====================================================
void CNumber::SetColor(D3DXCOLOR col)
{
	for (int nCount = 0; nCount < m_nNumPlace; nCount++)
	{
		if (m_apObject[nCount] != nullptr)
		{
			m_apObject[nCount]->SetCol(col);
		}
	}
}

//=====================================================
// アルファ値設定処理
//=====================================================
void CNumber::SetAlpha(float fAlpha)
{
	for (int nCount = 0; nCount < m_nNumPlace; nCount++)
	{
		if (m_apObject[nCount] != nullptr)
		{
			m_apObject[nCount]->SetAlpha(fAlpha);
		}
	}
}

//=====================================================
// 色取得処理
//=====================================================
D3DXCOLOR CNumber::GetColor(void)
{
	if (m_apObject[0] != nullptr)
	{
		return m_apObject[0]->GetCol();
	}

	return D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//=====================================================
// 生成処理
//=====================================================
CNumber *CNumber::Create(int nNumPlace, int nValue)
{
	CNumber *pNumber = nullptr;

	pNumber = new CNumber;

	if (pNumber != nullptr)
	{
		pNumber->m_nNumPlace = nNumPlace;

		pNumber->m_nValue = nValue;

		for (int nCnt = 0; nCnt < nNumPlace; nCnt++)
		{// 数字用のインスタンスを生成
			pNumber->m_apObject[nCnt] = nullptr;

			if (pNumber->m_apObject[nCnt] == nullptr)
			{
				pNumber->m_apObject[nCnt] = CUI::Create();
			}
		}

		// 初期化処理
		pNumber->Init();

		pNumber->SetValue(nValue);
	}

	return pNumber;
}