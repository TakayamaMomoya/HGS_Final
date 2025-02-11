//*****************************************************
//
// ÆÌ[house.cpp]
// Author:ûüRç
//
//*****************************************************

//*****************************************************
// CN[h
//*****************************************************
#include "house.h"
#include "model.h"
#include "UI.h"
#include "texture.h"
#include "collision.h"
#include "manager.h"

//*****************************************************
// èè`
//*****************************************************
//-------------------------
// fÌè
//-------------------------
namespace model
{
const string PATH_DEFAULT = "data\\MODEL\\object\\Snowdome.x";	// ftHgfÌpX
const float RADIUS_COLLISION = 400.0f;							// »èÌ¼a
}

//-------------------------
// zuÌè
//-------------------------
namespace set
{
const int NUM_SET = 40;				// Ýu
const float DIST_HOUSE = 2300.0f;	// Æ¯mÌ£
const int NUM_GRID = 7;			// ObhÌ
const float RANGE_SET = DIST_HOUSE * NUM_GRID;	// zuÍÍ
const D3DXVECTOR3 OFFSET_PRESENT = { 0.0f,0.0f,-800.0f };	// v[gÌItZbg
}

//-------------------------
// UIÌè
//-------------------------
namespace UI
{
const float WIDTH = 0.05f;							// 
const float HEIGHT = 0.08f;							// ³
const D3DXVECTOR3 OFFSET = { 0.1f,-0.2f,0.0f };		// ItZbg
const string PATH[CPresent::E_Label::LABEL_MAX] =	// eNX`pX
{
	"data\\TEXTURE\\UI\\boxb.png",
	"data\\TEXTURE\\UI\\boxg.png",
	"data\\TEXTURE\\UI\\boxp.png",
	"data\\TEXTURE\\UI\\boxy.png",
};
const float TIME_FADE = 1.0f;	// tF[hÉ©©éÔ
}

//==========================================
// ÃIoÏé¾
//==========================================
CListManager<CHouse>* CHouse::m_pList = nullptr;	// IuWFNgXg
vector<CPresent::E_Label> CHouse::s_aLabelResult;	// UgxÌxN^[

//=====================================================
// RXgN^
//=====================================================
CHouse::CHouse(int nPriority) : CObjectX(nPriority), m_labelWant(CPresent::E_Label::LABEL_BLUE), m_pPresent(nullptr), m_pUI(nullptr),
m_bClear(false), m_fTimerFade(0.0f)
{

}

//=====================================================
// fXgN^
//=====================================================
CHouse::~CHouse()
{

}

//=====================================================
// _ÉÆðzu·é
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
			// zuÊuÌÝè
			pos.x = universal::RandRange(set::NUM_GRID, 0) * set::DIST_HOUSE - set::RANGE_SET * 0.5f;
			pos.z = universal::RandRange(set::NUM_GRID, 0) * set::DIST_HOUSE - set::RANGE_SET * 0.5f;

			// zuªíÁÄé©Ì`FbN
			bResult = !pHouse->CheckCover(pos);
		}

		pHouse->SetPosition(pos);
	}

	// v[gÌèUè
	BindPresent();
}

//=====================================================
// v[gÌèUè
//=====================================================
void CHouse::BindPresent(void)
{
	if (CHouse::GetList()->GetNumAll() % 2 != 0)
		assert(false);	// ôÂ¶áÈ¢Æ«ÌAT[g

	// xN^[ÉÏ·
	std::list<CHouse*> list = CHouse::GetList()->GetList();
	std::vector<CHouse*> vector;

	for (CHouse* house : list)
	{
		vector.push_back(house);
	}

	// ñÂ¸ÂèUé
	for (int i = 0; i < (int)vector.size(); i += 2)
	{
		// ñíÞAÊXÌxðpÓ·é
		CPresent::E_Label labelFirst;
		CPresent::E_Label labelSecond;

		house::GetTwoLabel(labelFirst, labelSecond);

		// èUé
		vector[i]->SetPresent(CPresent::Create(labelFirst));
		vector[i]->SetLabelWant(labelSecond);
		vector[i + 1]->SetPresent(CPresent::Create(labelSecond));
		vector[i + 1]->SetLabelWant(labelFirst);
	}
}

//=====================================================
// íè`FbN
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
// ¶¬
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
// ú»
//=====================================================
HRESULT CHouse::Init(void)
{
	// p³NXÌú»
	CObjectX::Init();

	EnableShadow(true);

	// fÇ
	int nIdx = CModel::Load(&model::PATH_DEFAULT[0]);
	BindModel(nIdx);

	// Xg}l[W[Ì¶¬
	if (m_pList == nullptr)
	{
		m_pList = CListManager<CHouse>::Create();
		if (m_pList == nullptr) { assert(false); return E_FAIL; }
	}

	// XgÉ©gÌIuWFNgðÇÁECe[^[ðæ¾
	m_iterator = m_pList->AddList(this);

	// UIÌ¶¬
	m_pUI = CUI::Create();

	if (m_pUI != nullptr)
	{
		m_pUI->SetSize(UI::WIDTH, UI::HEIGHT);
	}

	// »èÌ¶¬
	m_pCollision = CCollisionSphere::Create(CCollision::TAG_BLOCK, CCollision::TYPE::TYPE_SPHERE, this);

	if (m_pCollision != nullptr)
	{
		m_pCollision->SetRadius(model::RADIUS_COLLISION);
	}

	return S_OK;
}

//=====================================================
// I¹
//=====================================================
void CHouse::Uninit(void)
{
	// Xg©ç©gÌIuWFNgðí
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // IuWFNgªêÂàÈ¢ê

		// Xg}l[W[Ìjü
		m_pList->Release(m_pList);
	}

	if (m_pCollision != nullptr)
	{
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}

	// p³NXÌI¹
	CObjectX::Uninit();
}

//=====================================================
// XV
//=====================================================
void CHouse::Update(void)
{
	// p³NXÌXV
	CObjectX::Update();

	// UIÌÇ]
	if (m_pUI != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		D3DXVECTOR3 posScreen;
		universal::IsInScreen(pos, &posScreen);
		universal::ConvertScreenRate(posScreen);
		posScreen += UI::OFFSET;

		m_pUI->SetPosition(posScreen);
		m_pUI->SetVtx();

		// eNX`Ýè
		int nIdxTexture = Texture::GetIdx(&UI::PATH[m_labelWant][0]);
		m_pUI->SetIdxTexture(nIdxTexture);
	}

	// »èÌÇ]
	if (m_pCollision != nullptr)
		m_pCollision->SetPosition(GetPosition());

	// NAtOÌÇ
	if (!m_bClear)
	{
		// µÄ¢év[gÆÙµ¢v[gªêvµ½çtOð§Äé
		if (m_pPresent->GetLabel() == m_labelWant)
		{
			m_bClear = true;
		}
	}
	else
	{
		m_fTimerFade += CManager::GetDeltaTime();
		universal::LimitValuefloat(&m_fTimerFade, UI::TIME_FADE, 0.0f);

		// ^C}[ÌC[WO
		float fTime = m_fTimerFade / UI::TIME_FADE;
		float fRate = easing::EaseOutExpo(fTime);

		// FÌÝè
		m_pUI->SetAlpha(1.0f - fRate);
	}
}

//=====================================================
// `æ
//=====================================================
void CHouse::Draw(void)
{
	// p³NXÌ`æ
	CObjectX::Draw();
}

//=====================================================
// v[gÝè
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
//  XgÌæ¾
//==========================================
CListManager<CHouse>* CHouse::GetList(void)
{
	return m_pList;
}

//==========================================
// UgÌxÝè
//==========================================
void CHouse::SetResultLabel(void)
{
	s_aLabelResult.clear();

	// ¨Ìîñðæ¾·é
	if (CHouse::GetList() == nullptr) { return; }
	std::list<CHouse*> list = CHouse::GetList()->GetList();    // Xgðæ¾

	for (CHouse* house : list)
	{
		if (house->GetPresent()->GetLabel() == house->GetLabelWant())
		{
			s_aLabelResult.push_back(house->GetLabelWant());
		}
	}
}

//==========================================
// ÊuÌ§À
//==========================================
void CHouse::LimitPos(D3DXVECTOR3 &rPos)
{
	float width = set::NUM_GRID * set::DIST_HOUSE * 0.5f + set::DIST_HOUSE;
	float height = set::NUM_GRID * set::DIST_HOUSE * 0.5f + set::DIST_HOUSE;

	universal::LimitPosInSq(width, height, &rPos);
}

//==========================================
// ÊuÌðÔ·
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
	// ÅÌxÌè
	labelFirst = (CPresent::E_Label)universal::RandRange(CPresent::E_Label::LABEL_MAX, 0);

	// ÌxÌè
	while (true)
	{
		labelSecond = (CPresent::E_Label)universal::RandRange(CPresent::E_Label::LABEL_MAX, 0);

		if (labelFirst != labelSecond)
			break;
	}
}
}