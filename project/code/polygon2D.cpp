//*****************************************************
//
// 2Dオブジェクトの処理[object2D.h]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "polygon2D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CPolygon2D::CPolygon2D(int nPriority) : CObject2D(nPriority)
{
	// 変数のクリア
	m_pVtxBuff = nullptr;
	m_heigth = 0;
	m_width = 0;
	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_fCenterHeight = 0.5f;
	m_nIdxTexture = -1;
}

//=====================================================
// デストラクタ
//=====================================================
CPolygon2D::~CPolygon2D()
{

}

//=====================================================
// 初期化
//=====================================================
HRESULT CPolygon2D::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	if (pDevice != nullptr)
	{
		if (m_pVtxBuff == nullptr)
		{
			// 頂点バッファの生成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&m_pVtxBuff,
				nullptr);
		}
	}

	// 頂点情報のポインタ
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].pos = { 0.0f,0.0f,0.0f };
			pVtx[nCnt].rhw = 1.0;
			pVtx[nCnt].col = m_col;
			pVtx[nCnt].tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		m_width = 50.0f;
		m_heigth = 50.0f;

		// 対角線の角度取得
		float fAngleUp = atan2f(m_width, m_heigth);
		// 長さの取得
		float fLengthUp = sqrtf(m_width * m_width + m_heigth * m_heigth);

		D3DXVECTOR3 pos = CObject2D::GetPosition();
		D3DXVECTOR3 rot = CObject2D::GetRotation();

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3
		(
			pos.x + sinf(rot.z - D3DX_PI + fAngleUp) * fLengthUp,
			pos.y + cosf(rot.z - D3DX_PI + fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[1].pos = D3DXVECTOR3
		(
			pos.x + sinf(rot.z + D3DX_PI - fAngleUp) * fLengthUp,
			pos.y + cosf(rot.z + D3DX_PI - fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[2].pos = D3DXVECTOR3
		(
			pos.x + sinf(rot.z - fAngleUp) * fLengthUp,
			pos.y + cosf(rot.z - fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[3].pos = D3DXVECTOR3
		(
			pos.x + sinf(rot.z + fAngleUp) * fLengthUp,
			pos.y + cosf(rot.z + fAngleUp) * fLengthUp,
			0.0f
		);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}

	CObject2D::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CPolygon2D::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	CObject2D::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CPolygon2D::Update(void)
{
	CObject2D::Update();
}

//=====================================================
// 頂点位置設定
//=====================================================
void CPolygon2D::SetVtx(void)
{
	// 頂点情報のポインタ
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 対角線の角度取得
		float fAngleUp = atan2f(m_width, m_heigth);
		// 長さの取得
		float fLengthUp = sqrtf(m_width * m_width + m_heigth * m_heigth);

		D3DXVECTOR3 pos = CObject2D::GetPosition();
		D3DXVECTOR3 rot = CObject2D::GetRotation();

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3
		(
			pos.x + sinf(rot.z - D3DX_PI + fAngleUp) * fLengthUp,
			pos.y + cosf(rot.z - D3DX_PI + fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[1].pos = D3DXVECTOR3
		(
			pos.x + sinf(rot.z + D3DX_PI - fAngleUp) * fLengthUp,
			pos.y + cosf(rot.z + D3DX_PI - fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[2].pos = D3DXVECTOR3
		(
			pos.x + sinf(rot.z - fAngleUp) * fLengthUp,
			pos.y + cosf(rot.z - fAngleUp) * fLengthUp,
			0.0f
		);
		pVtx[3].pos = D3DXVECTOR3
		(
			pos.x + sinf(rot.z + fAngleUp) * fLengthUp,
			pos.y + cosf(rot.z + fAngleUp) * fLengthUp,
			0.0f
		);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].col = m_col;
		}

		// 頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}

}

//=====================================================
// 描画
//=====================================================
void CPolygon2D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	if (pDevice != nullptr)
	{
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		LPDIRECT3DTEXTURE9 pTexture = CTexture::GetInstance()->GetAddress(m_nIdxTexture);

		// テクスチャ設定
		pDevice->SetTexture(0, pTexture);

		// 背景の描画
 		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	CObject2D::Draw();
}

//=====================================================
// 中心の高さ
//=====================================================
void CPolygon2D::SetCenterHeight(float fHeight)
{
	m_fCenterHeight = fHeight;
}

//=====================================================
// 生成処理
//=====================================================
CPolygon2D *CPolygon2D::Create(int nPriority, float fCenterHeight)
{
	CPolygon2D *pObject2D = nullptr;

	if (pObject2D == nullptr)
	{
		// インスタンス生成
		pObject2D = new CPolygon2D(nPriority);

		if (pObject2D != nullptr)
		{
			pObject2D->m_fCenterHeight = fCenterHeight;

			// 初期化処理
			pObject2D->Init();
		}
	}

	return pObject2D;
}

//=====================================================
// サイズ設定処理
//=====================================================
void CPolygon2D::SetSize(float width, float height)
{
	m_width = width;
	m_heigth = height;

	SetVtx();
}

//=====================================================
// 幅設定処理
//=====================================================
void CPolygon2D::SetWidth(float width)
{
	m_width = width;

	SetVtx();
}

//=====================================================
// 高さ設定処理
//=====================================================
void CPolygon2D::SetHeight(float height)
{
	m_heigth = height;

	SetVtx();
}

//=====================================================
// テクスチャ座標設定処理
//=====================================================
void CPolygon2D::SetTex(D3DXVECTOR2 texLeftUp, D3DXVECTOR2 texRightDown)
{
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	// 頂点情報のポインタ
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標
	pVtx[0].tex = texLeftUp;
	pVtx[1].tex = D3DXVECTOR2(texRightDown.x, texLeftUp.y);
	pVtx[2].tex = D3DXVECTOR2(texLeftUp.x, texRightDown.y);
	pVtx[3].tex = texRightDown;

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=====================================================
// アニメーション設定処理
//=====================================================
void CPolygon2D::SetAnim(int nAnim,int nNumAnim,int nNumV)
{
	// 頂点情報のポインタ
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2
		(
			(1.0f / nNumAnim) * nAnim,
			0.0f
		);
		pVtx[1].tex = D3DXVECTOR2
		(
			1.0f / nNumAnim + 1.0f / nNumAnim * nAnim,
			0.0f
		);
		pVtx[2].tex = D3DXVECTOR2
		(
			1.0f / nNumAnim * nAnim,
			1.0f
		);
		pVtx[3].tex = D3DXVECTOR2
		(
			1.0f / nNumAnim + 1.0f / nNumAnim * nAnim,
			1.0f
		);

		// 頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}
}

//=====================================================
// 色設定処理
//=====================================================
void CPolygon2D::SetCol(D3DXCOLOR col)
{
	m_col = col;

	// 頂点情報のポインタ
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].col = m_col;
		}

		// 頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}
}

//=====================================================
// 透明度設定処理
//=====================================================
void CPolygon2D::SetAlpha(float fAlpha)
{
	// 透明度を設定
	m_col.a = fAlpha;

	// 色の反映
	SetCol(m_col);
}
