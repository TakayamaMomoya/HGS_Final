//*****************************************************
//
// �i�r�Q�[�V�����̏���[navigation.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "navigation.h"
#include "polygon3D.h"
#include "player.h"
#include "house.h"
#include "texture.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float WIDTH = 200.0f;		// ��
const float HEIGHT = 300.0f;	// ����
const float SPEED_ROTATE = 0.1f;	// ��]���x
const string PATH = "data\\TEXTURE\\UI\\dirPeck.png";	// �p�X
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CNavigation::CNavigation(int nPriority) : CObject(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CNavigation::~CNavigation()
{

}

//=====================================================
// ��������
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
// ����������
//=====================================================
HRESULT CNavigation::Init(void)
{
	CreatePolygon();

	return S_OK;
}

//=====================================================
// �|���S���̐���
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
// �|���S���̔j��
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
// �I������
//=====================================================
void CNavigation::Uninit(void)
{
	DeletePolygon();

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CNavigation::Update(void)
{
	// �Ǐ]
	FollowPlayer();
}

//=====================================================
// �Ǐ]
//=====================================================
void CNavigation::FollowPlayer(void)
{
	if (CPlayer::GetInstance().empty())
		return;

	CPlayer* pPlayer = *CPlayer::GetInstance().begin();

	if (pPlayer == nullptr)
		return;

	// �����̐ݒ�
	float fRotDest = CulcRotDest();

	if (m_pPolygon == nullptr)
		return;

	// �ʒu�̐ݒ�
	m_pPolygon->SetPosition(pPlayer->GetPosition());

	D3DXVECTOR3 rot = m_pPolygon->GetRotation();

	universal::FactingRot(&rot.y, fRotDest, SPEED_ROTATE);

	m_pPolygon->SetRotation(rot);
}

//=====================================================
// �ڕW�̌����̌v�Z
//=====================================================
float CNavigation::CulcRotDest(void)
{
	if (CPlayer::GetInstance().empty())
		return 0.0f;

	CPlayer* pPlayer = *CPlayer::GetInstance().begin();

	if (pPlayer == nullptr)
		return 0.0f;

	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

	// �S�ƂƂ̃`�F�b�N
	if (CHouse::GetList() == nullptr) { return 0.0f; }
	std::list<CHouse*> list = CHouse::GetList()->GetList();    // ���X�g���擾

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
// �`�揈��
//=====================================================
void CNavigation::Draw(void)
{

}