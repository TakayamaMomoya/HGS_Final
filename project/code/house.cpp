//*****************************************************
//
// 家の処理[house.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "house.h"
#include "model.h"

//*****************************************************
// 定数定義
//*****************************************************
//-------------------------
// モデルの定数
//-------------------------
namespace model
{
const string PATH_DEFAULT = "data\\MODEL\\object\\Snowdome.x";	// デフォルトモデルのパス
}

//-------------------------
// 配置の定数
//-------------------------
namespace set
{
const int NUM_SET = 15;									// 設置数
const float DIST_HOUSE = 300.0f;						// 家同士の距離
const float RANGE_SET = 5000.0f;						// 配置範囲
const int NUM_GRID = (int)RANGE_SET / (int)DIST_HOUSE;	// グリッドの数
}

//==========================================
// 静的メンバ変数宣言
//==========================================
CListManager<CHouse>* CHouse::m_pList = nullptr; // オブジェクトリスト

//=====================================================
// コンストラクタ
//=====================================================
CHouse::CHouse(int nPriority) : CObjectX(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CHouse::~CHouse()
{

}

//=====================================================
// ランダムに家を配置する処理
//=====================================================
void CHouse::SetHouseRandom(void)
{
	for (int i = 0; i < set::NUM_SET; i++)
	{
		CHouse *pHouse = CHouse::Create();

		if (pHouse == nullptr)
			assert(false);

		bool bResult = false;

		D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

		while (!bResult)
		{
			// 配置位置の設定
			pos.x = universal::RandRange(set::NUM_GRID, 0) * set::DIST_HOUSE;
			pos.z = universal::RandRange(set::NUM_GRID, 0) * set::DIST_HOUSE;

			// 配置が被ってるかのチェック
			bResult = CheckCover(pos);
		}

		pHouse->SetPosition(pos);
	}
}

//=====================================================
// 被りチェック
//=====================================================
bool CHouse::CheckCover(D3DXVECTOR3 pos)
{
	

	return false;
}

//=====================================================
// 生成処理
//=====================================================
CHouse* CHouse::Create(void)
{
	CHouse *pHouse = nullptr;

	pHouse = new CHouse;

	if (pHouse != nullptr)
		pHouse->Init();

	return pHouse;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CHouse::Init(void)
{
	// 継承クラスの初期化
	CObjectX::Init();

	// モデル読込
	int nIdx = CModel::Load(&model::PATH_DEFAULT[0]);
	BindModel(nIdx);

	// リストマネージャーの生成
	if (m_pList == nullptr)
	{
		m_pList = CListManager<CHouse>::Create();
		if (m_pList == nullptr) { assert(false); return E_FAIL; }
	}

	// リストに自身のオブジェクトを追加・イテレーターを取得
	m_iterator = m_pList->AddList(this);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CHouse::Uninit(void)
{
	// リストから自身のオブジェクトを削除
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // オブジェクトが一つもない場合

		// リストマネージャーの破棄
		m_pList->Release(m_pList);
	}

	// 継承クラスの終了
	CObjectX::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CHouse::Update(void)
{
	// 継承クラスの更新
	CObjectX::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CHouse::Draw(void)
{
	// 継承クラスの描画
	CObjectX::Draw();
}

//==========================================
//  リストの取得
//==========================================
CListManager<CHouse>* CHouse::GetList(void)
{
	return m_pList;
}
