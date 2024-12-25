//*****************************************************
//
// ナビゲーションの処理[navigation.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "navigation.h"
#include "polygon3D.h"
#include "player.h"
#include "house.h"
#include "texture.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float WIDTH = 200.0f;		// 幅
const float HEIGHT = 300.0f;	// 高さ
const float SPEED_ROTATE = 0.1f;	// 回転速度
const string PATH = "data\\TEXTURE\\UI\\dirPeck.png";	// パス
}

//=====================================================
// コンストラクタ
//=====================================================
CNavigation::CNavigation(int nPriority) : CObject(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CNavigation::~CNavigation()
{

}

//=====================================================
// 生成処理
//=====================================================
CNavigation* CNavigation::Create(void)
{
	CNavigation *pNavigation = nullptr;

	pNavigation = new CNavigation;

	if (pNavigation != nullptr)
		pNavigation->Init();

	return pNavigation;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CNavigation::Init(void)
{
	CreatePolygon();

	return S_OK;
}

//=====================================================
// ポリゴンの生成
//=====================================================
void CNavigation::CreatePolygon(void)
{
	if (m_pPolygon != nullptr)
		return;

	m_pPolygon = CPolygon3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (m_pPolygon == nullptr)
		return;

	m_pPolygon->SetSize(WIDTH, HEIGHT);
	int nIdx = Texture::GetIdx(&PATH[0]);
	m_pPolygon->SetIdxTexture(nIdx);
}

//=====================================================
// ポリゴンの破棄
//=====================================================
void CNavigation::DeletePolygon(void)
{
	if (m_pPolygon != nullptr)
	{
		m_pPolygon->Uninit();
		m_pPolygon = nullptr;
	}
}

//=====================================================
// 終了処理
//=====================================================
void CNavigation::Uninit(void)
{
	DeletePolygon();

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CNavigation::Update(void)
{
	// 追従
	FollowPlayer();
}

//=====================================================
// 追従
//=====================================================
void CNavigation::FollowPlayer(void)
{
	if (CPlayer::GetInstance().empty())
		return;

	CPlayer* pPlayer = *CPlayer::GetInstance().begin();

	if (pPlayer == nullptr)
		return;

	// 向きの設定
	float fRotDest = CulcRotDest();

	if (m_pPolygon == nullptr)
		return;

	// 位置の設定
	m_pPolygon->SetPosition(pPlayer->GetPosition());

	D3DXVECTOR3 rot = m_pPolygon->GetRotation();

	universal::FactingRot(&rot.y, fRotDest, SPEED_ROTATE);

	m_pPolygon->SetRotation(rot);
}

//=====================================================
// 目標の向きの計算
//=====================================================
float CNavigation::CulcRotDest(void)
{
	if (CPlayer::GetInstance().empty())
		return 0.0f;

	CPlayer* pPlayer = *CPlayer::GetInstance().begin();

	if (pPlayer == nullptr)
		return 0.0f;

	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// 全家とのチェック
	if (CHouse::GetList() == nullptr) { return 0.0f; }
	std::list<CHouse*> list = CHouse::GetList()->GetList();    // リストを取得

	float fDiffMin = FLT_MAX;
	CHouse* houseDest = nullptr;
	for (CHouse* house : list)
	{
		if (house->IsClear())
			continue;

		if (pPlayer->GetPresent()->GetLabel() != house->GetLabelWant())
			continue;

		float fDiff = 0.0f;
		if (universal::DistCmpFlat(posPlayer, house->GetPosition(), fDiffMin, &fDiff))
		{
			fDiffMin = fDiff;
			houseDest = house;
		}
	}

	if (houseDest != nullptr)
	{
		CreatePolygon();

		D3DXVECTOR3 vecDiff = houseDest->GetPosition() - posPlayer;

		float fRotDiff = atan2f(vecDiff.x, vecDiff.z);

		return fRotDiff;
	}
	else
		DeletePolygon();

	return 0.0f;
}

//=====================================================
// 描画処理
//=====================================================
void CNavigation::Draw(void)
{

}