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

//*****************************************************
// �萔��`
//*****************************************************
//-------------------------
// ���f���̒萔
//-------------------------
namespace model
{
const string PATH_DEFAULT = "data\\MODEL\\object\\Snowdome.x";	// �f�t�H���g���f���̃p�X
}

//-------------------------
// �z�u�̒萔
//-------------------------
namespace set
{
const int NUM_SET = 15;									// �ݒu��
const float DIST_HOUSE = 1000.0f;						// �Ɠ��m�̋���
const float RANGE_SET = 5000.0f;						// �z�u�͈�
const int NUM_GRID = 20;	// �O���b�h�̐�
}

//==========================================
// �ÓI�����o�ϐ��錾
//==========================================
CListManager<CHouse>* CHouse::m_pList = nullptr; // �I�u�W�F�N�g���X�g

//=====================================================
// �R���X�g���N�^
//=====================================================
CHouse::CHouse(int nPriority) : CObjectX(nPriority)
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
			pos.x = universal::RandRange(set::NUM_GRID, 0) * set::DIST_HOUSE - set::RANGE_SET;
			pos.z = universal::RandRange(set::NUM_GRID, 0) * set::DIST_HOUSE - set::RANGE_SET;

			// �z�u������Ă邩�̃`�F�b�N
			bResult = !pHouse->CheckCover(pos);
		}

		pHouse->SetPosition(pos);
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
}

//=====================================================
// �`�揈��
//=====================================================
void CHouse::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//==========================================
//  ���X�g�̎擾
//==========================================
CListManager<CHouse>* CHouse::GetList(void)
{
	return m_pList;
}
