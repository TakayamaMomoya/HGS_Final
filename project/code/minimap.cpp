//*****************************************************
//
// �~�j�}�b�v�̏���[minimap.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "minimap.h"
#include "player.h"
#include "UI.h"
#include "texture.h"
#include "house.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace bg
{
const float WIDTH = 0.16f;		// ��
const float HEIGHT = 0.2f;	// ����
const string PATH = "data\\TEXTURE\\UI\\minimap.png";	// �p�X
const D3DXVECTOR3 POS = { WIDTH + 0.05f,1.0f - HEIGHT - 0.05f,0.0f };	// �ʒu
}
namespace icon
{
const float WIDTH = 0.01f;		// ��
const float HEIGHT = 0.03f;	// ����
const string PATH = "data\\TEXTURE\\UI\\dirPeck.png";	// �p�X
}


//=====================================================
// �R���X�g���N�^
//=====================================================
CMinimap::CMinimap(int nPriority) : CObject(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CMinimap::~CMinimap()
{

}

//=====================================================
// ��������
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
// ����������
//=====================================================
HRESULT CMinimap::Init(void)
{
	CreatePolygon();

	return S_OK;
}

//=====================================================
// �|���S���̐���
//=====================================================
void CMinimap::CreatePolygon(void)
{
	// �w�i===========================
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

	// �A�C�R��===========================
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
// �I������
//=====================================================
void CMinimap::Uninit(void)
{
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CMinimap::Update(void)
{
	// �Ǐ]
	FollowPlayer();
}

//=====================================================
// �Ǐ]
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
// �`�揈��
//=====================================================
void CMinimap::Draw(void)
{

}