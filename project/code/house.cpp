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
#include "UI.h"
#include "texture.h"
#include "collision.h"
#include "manager.h"

//*****************************************************
// 定数定義
//*****************************************************
//-------------------------
// モデルの定数
//-------------------------
namespace model
{
const string PATH_DEFAULT = "data\\MODEL\\object\\Snowdome.x";	// デフォルトモデルのパス
const float RADIUS_COLLISION = 400.0f;							// 判定の半径
}

//-------------------------
// 配置の定数
//-------------------------
namespace set
{
const int NUM_SET = 16;				// 設置数
const float DIST_HOUSE = 3000.0f;	// 家同士の距離
const int NUM_GRID = 7;			// グリッドの数
const float RANGE_SET = DIST_HOUSE * NUM_GRID;	// 配置範囲
const D3DXVECTOR3 OFFSET_PRESENT = { 0.0f,0.0f,-800.0f };	// プレゼントのオフセット
}

//-------------------------
// UIの定数
//-------------------------
namespace UI
{
const float WIDTH = 0.05f;							// 幅
const float HEIGHT = 0.08f;							// 高さ
const D3DXVECTOR3 OFFSET = { 0.1f,-0.2f,0.0f };		// オフセット
const string PATH[CPresent::E_Label::LABEL_MAX] =	// テクスチャパス
{
	"data\\TEXTURE\\UI\\boxb.png",
	"data\\TEXTURE\\UI\\boxg.png",
	"data\\TEXTURE\\UI\\boxp.png",
	"data\\TEXTURE\\UI\\boxy.png",
};
const float TIME_FADE = 1.0f;	// フェードにかかる時間
}

//==========================================
// 静的メンバ変数宣言
//==========================================
CListManager<CHouse>* CHouse::m_pList = nullptr;	// オブジェクトリスト
vector<CPresent::E_Label> CHouse::s_aLabelResult;	// リザルトラベルのベクター

//=====================================================
// コンストラクタ
//=====================================================
CHouse::CHouse(int nPriority) : CObjectX(nPriority), m_labelWant(CPresent::E_Label::LABEL_BLUE), m_pPresent(nullptr), m_pUI(nullptr),
m_bClear(false), m_fTimerFade(0.0f)
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
			pos.x = universal::RandRange(set::NUM_GRID, 0) * set::DIST_HOUSE - set::RANGE_SET * 0.5f;
			pos.z = universal::RandRange(set::NUM_GRID, 0) * set::DIST_HOUSE - set::RANGE_SET * 0.5f;

			// 配置が被ってるかのチェック
			bResult = !pHouse->CheckCover(pos);
		}

		pHouse->SetPosition(pos);
	}

	// プレゼントの割り振り
	BindPresent();
}

//=====================================================
// プレゼントの割り振り
//=====================================================
void CHouse::BindPresent(void)
{
	if (CHouse::GetList()->GetNumAll() % 2 != 0)
		assert(false);	// 偶数個じゃないときのアサート

	// ベクターに変換
	std::list<CHouse*> list = CHouse::GetList()->GetList();
	std::vector<CHouse*> vector;

	for (CHouse* house : list)
	{
		vector.push_back(house);
	}

	// 二つずつ割り振る
	for (int i = 0; i < (int)vector.size(); i += 2)
	{
		// 二種類、別々のラベルを用意する
		CPresent::E_Label labelFirst;
		CPresent::E_Label labelSecond;

		house::GetTwoLabel(labelFirst, labelSecond);

		// 割り振る
		vector[i]->SetPresent(CPresent::Create(labelFirst));
		vector[i]->SetLabelWant(labelSecond);
		vector[i + 1]->SetPresent(CPresent::Create(labelSecond));
		vector[i + 1]->SetLabelWant(labelFirst);
	}
}

//=====================================================
// 被りチェック
//=====================================================
bool CHouse::CheckCover(D3DXVECTOR3 pos)
{
	std::list<CHouse*> list = CHouse::GetList()->GetList(); 

	for (CHouse* house : list)
	{
		if (house == this)
			continue;

		D3DXVECTOR3 posHouse = house->GetPosition();

		if (!universal::DistCmp(pos, posHouse, 1.0f, nullptr))
			continue;

		return true;
	}

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

	EnableShadow(true);

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

	// UIの生成
	m_pUI = CUI::Create();

	if (m_pUI != nullptr)
	{
		m_pUI->SetSize(UI::WIDTH, UI::HEIGHT);
	}

	// 判定の生成
	m_pCollision = CCollisionSphere::Create(CCollision::TAG_BLOCK, CCollision::TYPE::TYPE_SPHERE, this);

	if (m_pCollision != nullptr)
	{
		m_pCollision->SetRadius(model::RADIUS_COLLISION);
	}

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

	if (m_pCollision != nullptr)
	{
		m_pCollision->Uninit();
		m_pCollision = nullptr;
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

	// UIの追従
	if (m_pUI != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		D3DXVECTOR3 posScreen;
		universal::IsInScreen(pos, &posScreen);
		universal::ConvertScreenRate(posScreen);
		posScreen += UI::OFFSET;

		m_pUI->SetPosition(posScreen);
		m_pUI->SetVtx();

		// テクスチャ設定
		int nIdxTexture = Texture::GetIdx(&UI::PATH[m_labelWant][0]);
		m_pUI->SetIdxTexture(nIdxTexture);
	}

	// 判定の追従
	if (m_pCollision != nullptr)
		m_pCollision->SetPosition(GetPosition());

	// クリアフラグの管理
	if (!m_bClear)
	{
		// 所持しているプレゼントとほしいプレゼントが一致したらフラグを立てる
		if (m_pPresent->GetLabel() == m_labelWant)
		{
			m_bClear = true;
		}
	}
	else
	{
		m_fTimerFade += CManager::GetDeltaTime();
		universal::LimitValuefloat(&m_fTimerFade, UI::TIME_FADE, 0.0f);

		// タイマーのイージング
		float fTime = m_fTimerFade / UI::TIME_FADE;
		float fRate = easing::EaseOutExpo(fTime);

		// 色の設定
		m_pUI->SetAlpha(1.0f - fRate);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CHouse::Draw(void)
{
	// 継承クラスの描画
	CObjectX::Draw();
}

//=====================================================
// プレゼント設定
//=====================================================
void CHouse::SetPresent(CPresent* pPresent)
{ 
	m_pPresent = pPresent;

	if (m_pPresent != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition() + set::OFFSET_PRESENT;

		m_pPresent->SetPosition(pos);
	}
}

//==========================================
//  リストの取得
//==========================================
CListManager<CHouse>* CHouse::GetList(void)
{
	return m_pList;
}

//==========================================
// リザルトのラベル設定
//==========================================
void CHouse::SetResultLabel(void)
{
	s_aLabelResult.clear();

	// 建物の情報を取得する
	if (CHouse::GetList() == nullptr) { return; }
	std::list<CHouse*> list = CHouse::GetList()->GetList();    // リストを取得

	for (CHouse* house : list)
	{
		if (house->GetPresent()->GetLabel() == house->GetLabelWant())
		{
			s_aLabelResult.push_back(house->GetLabelWant());
		}
	}
}

//==========================================
// 位置の制限
//==========================================
void CHouse::LimitPos(D3DXVECTOR3 &rPos)
{
	float width = set::NUM_GRID * set::DIST_HOUSE * 0.5f + set::DIST_HOUSE;
	float height = set::NUM_GRID * set::DIST_HOUSE * 0.5f + set::DIST_HOUSE;

	universal::LimitPosInSq(width, height, &rPos);
}

//==========================================
// 位置の割合を返す
//==========================================
void CHouse::PosRate(D3DXVECTOR3 pos, float* pRateX, float* pRateZ)
{
	*pRateX = pos.x / (set::NUM_GRID * set::DIST_HOUSE + set::DIST_HOUSE * 3.3f);
	*pRateZ = pos.z / (set::NUM_GRID * set::DIST_HOUSE + set::DIST_HOUSE * 2);
}

namespace house
{
void GetTwoLabel(CPresent::E_Label &labelFirst, CPresent::E_Label &labelSecond)
{
	// 最初のラベルの決定
	labelFirst = (CPresent::E_Label)universal::RandRange(CPresent::E_Label::LABEL_MAX, 0);

	// 次のラベルの決定
	while (true)
	{
		labelSecond = (CPresent::E_Label)universal::RandRange(CPresent::E_Label::LABEL_MAX, 0);

		if (labelFirst != labelSecond)
			break;
	}
}
}