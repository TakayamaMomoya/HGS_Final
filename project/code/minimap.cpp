//*****************************************************
//
// ミニマップの処理[minimap.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "minimap.h"
#include "player.h"
#include "UI.h"
#include "texture.h"
#include "house.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace bg
{
const float WIDTH = 0.16f;		// 幅
const float HEIGHT = 0.2f;	// 高さ
const string PATH = "data\\TEXTURE\\UI\\minimap.png";	// パス
const D3DXVECTOR3 POS = { WIDTH + 0.05f,1.0f - HEIGHT - 0.05f,0.0f };	// 位置
}
namespace icon
{
const float WIDTH = 0.01f;		// 幅
const float HEIGHT = 0.03f;	// 高さ
const string PATH = "data\\TEXTURE\\UI\\dirPeck.png";	// パス
}


//=====================================================
// コンストラクタ
//=====================================================
CMinimap::CMinimap(int nPriority) : CObject(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CMinimap::~CMinimap()
{

}

//=====================================================
// 生成処理
//=====================================================
CMinimap* CMinimap::Create(void)
{
	CMinimap *pMinimap = nullptr;

	pMinimap = new CMinimap;

	if (pMinimap != nullptr)
		pMinimap->Init();

	return pMinimap;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CMinimap::Init(void)
{
	CreatePolygon();

	return S_OK;
}

//=====================================================
// ポリゴンの生成
//=====================================================
void CMinimap::CreatePolygon(void)
{
	// 背景===========================
	if (m_pBg != nullptr)
		return;

	m_pBg = CUI::Create();

	if (m_pBg == nullptr)
		return;

	m_pBg->SetSize(bg::WIDTH, bg::HEIGHT);
	int nIdx = Texture::GetIdx(&bg::PATH[0]);
	m_pBg->SetIdxTexture(nIdx);
	m_pBg->SetPosition(bg::POS);
	m_pBg->SetVtx();

	// アイコン===========================
	if (m_pPlayer != nullptr)
		return;

	m_pPlayer = CUI::Create();

	if (m_pPlayer == nullptr)
		return;

	m_pPlayer->SetSize(icon::WIDTH, icon::HEIGHT);
	nIdx = Texture::GetIdx(&icon::PATH[0]);
	m_pPlayer->SetIdxTexture(nIdx);
	m_pPlayer->SetVtx();
}

//=====================================================
// 終了処理
//=====================================================
void CMinimap::Uninit(void)
{
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CMinimap::Update(void)
{
	// 追従
	FollowPlayer();
}

//=====================================================
// 追従
//=====================================================
void CMinimap::FollowPlayer(void)
{
	if (CPlayer::GetInstance().empty())
		return;

	CPlayer* pPlayer = *CPlayer::GetInstance().begin();

	if (pPlayer == nullptr)
		return;

	D3DXVECTOR3 pos = pPlayer->GetPosition();
	D3DXVECTOR3 rot = pPlayer->GetRotation();

	float fRateX;
	float fRateZ;
	CHouse::PosRate(pos, &fRateX, &fRateZ);

	if (m_pPlayer == nullptr)
		return;

	D3DXVECTOR3 posIcon = bg::POS;
	posIcon.x += bg::WIDTH * fRateX * 2;
	posIcon.y -= bg::WIDTH * fRateZ * 2;

	rot.z = -pPlayer->GetRotation().y + D3DX_PI;

	m_pPlayer->SetPosition(posIcon);
	m_pPlayer->SetRotation(rot);
}

//=====================================================
// 描画処理
//=====================================================
void CMinimap::Draw(void)
{

}