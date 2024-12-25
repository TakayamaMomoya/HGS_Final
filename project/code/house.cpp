//*****************************************************
//
// �Ƃ̏���[house.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "house.h"
#include "model.h"
#include "UI.h"
#include "texture.h"
#include "collision.h"
#include "manager.h"

//*****************************************************
// �萔��`
//*****************************************************
//-------------------------
// ���f���̒萔
//-------------------------
namespace model
{
const string PATH_DEFAULT = "data\\MODEL\\object\\Snowdome.x";	// �f�t�H���g���f���̃p�X
const float RADIUS_COLLISION = 400.0f;							// ����̔��a
}

//-------------------------
// �z�u�̒萔
//-------------------------
namespace set
{
const int NUM_SET = 16;				// �ݒu��
const float DIST_HOUSE = 3000.0f;	// �Ɠ��m�̋���
const int NUM_GRID = 7;			// �O���b�h�̐�
const float RANGE_SET = DIST_HOUSE * NUM_GRID;	// �z�u�͈�
const D3DXVECTOR3 OFFSET_PRESENT = { 0.0f,0.0f,-800.0f };	// �v���[���g�̃I�t�Z�b�g
}

//-------------------------
// UI�̒萔
//-------------------------
namespace UI
{
const float WIDTH = 0.05f;							// ��
const float HEIGHT = 0.08f;							// ����
const D3DXVECTOR3 OFFSET = { 0.1f,-0.2f,0.0f };		// �I�t�Z�b�g
const string PATH[CPresent::E_Label::LABEL_MAX] =	// �e�N�X�`���p�X
{
	"data\\TEXTURE\\UI\\boxb.png",
	"data\\TEXTURE\\UI\\boxg.png",
	"data\\TEXTURE\\UI\\boxp.png",
	"data\\TEXTURE\\UI\\boxy.png",
};
const float TIME_FADE = 1.0f;	// �t�F�[�h�ɂ����鎞��
}

//==========================================
// �ÓI�����o�ϐ��錾
//==========================================
CListManager<CHouse>* CHouse::m_pList = nullptr;	// �I�u�W�F�N�g���X�g
vector<CPresent::E_Label> CHouse::s_aLabelResult;	// ���U���g���x���̃x�N�^�[

//=====================================================
// �R���X�g���N�^
//=====================================================
CHouse::CHouse(int nPriority) : CObjectX(nPriority), m_labelWant(CPresent::E_Label::LABEL_BLUE), m_pPresent(nullptr), m_pUI(nullptr),
m_bClear(false), m_fTimerFade(0.0f)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CHouse::~CHouse()
{

}

//=====================================================
// �����_���ɉƂ�z�u���鏈��
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
			// �z�u�ʒu�̐ݒ�
			pos.x = universal::RandRange(set::NUM_GRID, 0) * set::DIST_HOUSE - set::RANGE_SET * 0.5f;
			pos.z = universal::RandRange(set::NUM_GRID, 0) * set::DIST_HOUSE - set::RANGE_SET * 0.5f;

			// �z�u������Ă邩�̃`�F�b�N
			bResult = !pHouse->CheckCover(pos);
		}

		pHouse->SetPosition(pos);
	}

	// �v���[���g�̊���U��
	BindPresent();
}

//=====================================================
// �v���[���g�̊���U��
//=====================================================
void CHouse::BindPresent(void)
{
	if (CHouse::GetList()->GetNumAll() % 2 != 0)
		assert(false);	// ��������Ȃ��Ƃ��̃A�T�[�g

	// �x�N�^�[�ɕϊ�
	std::list<CHouse*> list = CHouse::GetList()->GetList();
	std::vector<CHouse*> vector;

	for (CHouse* house : list)
	{
		vector.push_back(house);
	}

	// �������U��
	for (int i = 0; i < (int)vector.size(); i += 2)
	{
		// ���ށA�ʁX�̃��x����p�ӂ���
		CPresent::E_Label labelFirst;
		CPresent::E_Label labelSecond;

		house::GetTwoLabel(labelFirst, labelSecond);

		// ����U��
		vector[i]->SetPresent(CPresent::Create(labelFirst));
		vector[i]->SetLabelWant(labelSecond);
		vector[i + 1]->SetPresent(CPresent::Create(labelSecond));
		vector[i + 1]->SetLabelWant(labelFirst);
	}
}

//=====================================================
// ���`�F�b�N
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
// ��������
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
// ����������
//=====================================================
HRESULT CHouse::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	EnableShadow(true);

	// ���f���Ǎ�
	int nIdx = CModel::Load(&model::PATH_DEFAULT[0]);
	BindModel(nIdx);

	// ���X�g�}�l�[�W���[�̐���
	if (m_pList == nullptr)
	{
		m_pList = CListManager<CHouse>::Create();
		if (m_pList == nullptr) { assert(false); return E_FAIL; }
	}

	// ���X�g�Ɏ��g�̃I�u�W�F�N�g��ǉ��E�C�e���[�^�[���擾
	m_iterator = m_pList->AddList(this);

	// UI�̐���
	m_pUI = CUI::Create();

	if (m_pUI != nullptr)
	{
		m_pUI->SetSize(UI::WIDTH, UI::HEIGHT);
	}

	// ����̐���
	m_pCollision = CCollisionSphere::Create(CCollision::TAG_BLOCK, CCollision::TYPE::TYPE_SPHERE, this);

	if (m_pCollision != nullptr)
	{
		m_pCollision->SetRadius(model::RADIUS_COLLISION);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CHouse::Uninit(void)
{
	// ���X�g���玩�g�̃I�u�W�F�N�g���폜
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // �I�u�W�F�N�g������Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̔j��
		m_pList->Release(m_pList);
	}

	if (m_pCollision != nullptr)
	{
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}

	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CHouse::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();

	// UI�̒Ǐ]
	if (m_pUI != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		D3DXVECTOR3 posScreen;
		universal::IsInScreen(pos, &posScreen);
		universal::ConvertScreenRate(posScreen);
		posScreen += UI::OFFSET;

		m_pUI->SetPosition(posScreen);
		m_pUI->SetVtx();

		// �e�N�X�`���ݒ�
		int nIdxTexture = Texture::GetIdx(&UI::PATH[m_labelWant][0]);
		m_pUI->SetIdxTexture(nIdxTexture);
	}

	// ����̒Ǐ]
	if (m_pCollision != nullptr)
		m_pCollision->SetPosition(GetPosition());

	// �N���A�t���O�̊Ǘ�
	if (!m_bClear)
	{
		// �������Ă���v���[���g�Ƃق����v���[���g����v������t���O�𗧂Ă�
		if (m_pPresent->GetLabel() == m_labelWant)
		{
			m_bClear = true;
		}
	}
	else
	{
		m_fTimerFade += CManager::GetDeltaTime();
		universal::LimitValuefloat(&m_fTimerFade, UI::TIME_FADE, 0.0f);

		// �^�C�}�[�̃C�[�W���O
		float fTime = m_fTimerFade / UI::TIME_FADE;
		float fRate = easing::EaseOutExpo(fTime);

		// �F�̐ݒ�
		m_pUI->SetAlpha(1.0f - fRate);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CHouse::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//=====================================================
// �v���[���g�ݒ�
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
//  ���X�g�̎擾
//==========================================
CListManager<CHouse>* CHouse::GetList(void)
{
	return m_pList;
}

//==========================================
// ���U���g�̃��x���ݒ�
//==========================================
void CHouse::SetResultLabel(void)
{
	s_aLabelResult.clear();

	// �����̏����擾����
	if (CHouse::GetList() == nullptr) { return; }
	std::list<CHouse*> list = CHouse::GetList()->GetList();    // ���X�g���擾

	for (CHouse* house : list)
	{
		if (house->GetPresent()->GetLabel() == house->GetLabelWant())
		{
			s_aLabelResult.push_back(house->GetLabelWant());
		}
	}
}

//==========================================
// �ʒu�̐���
//==========================================
void CHouse::LimitPos(D3DXVECTOR3 &rPos)
{
	float width = set::NUM_GRID * set::DIST_HOUSE * 0.5f + set::DIST_HOUSE;
	float height = set::NUM_GRID * set::DIST_HOUSE * 0.5f + set::DIST_HOUSE;

	universal::LimitPosInSq(width, height, &rPos);
}

//==========================================
// �ʒu�̊�����Ԃ�
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
	// �ŏ��̃��x���̌���
	labelFirst = (CPresent::E_Label)universal::RandRange(CPresent::E_Label::LABEL_MAX, 0);

	// ���̃��x���̌���
	while (true)
	{
		labelSecond = (CPresent::E_Label)universal::RandRange(CPresent::E_Label::LABEL_MAX, 0);

		if (labelFirst != labelSecond)
			break;
	}
}
}