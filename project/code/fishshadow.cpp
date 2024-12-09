//*****************************************************
//
// ���e�̏���[fishshadow.cpp]
// Author:��؈�^�@���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "fishshadow.h"
#include "texture.h"
#include "manager.h"
#include "iceManager.h"
#include "enemy.h"
#include "particle.h"

//*****************************************************
// �}�N����`
//*****************************************************
namespace
{
const char* PATH_TEX = "data\\TEXTURE\\enemy\\FishShadow.png";	// �e�N�X�`���p�X
const float TIME_FADEIN = 1.0f;									// �t�F�[�h�C���ɂ����鎞��
const float TIME_FADEOUT = 1.0f;								// �t�F�[�h�A�E�g�ɂ����鎞��
const D3DXCOLOR COL_INIT = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);	// �����F
const float WIDTH = 70.0f;										// ��
const float HEIGHT = 140.0f;									// ����
const float DIST_APPER = 500.0f;								// �o�����鋗��
const float RATE_DEST = 0.7f;									// �ڕW�ʒu�̊���

const int FRAME_BUBBLE = 5;										// �A���o���p�x

//-----------------------------------
// �A�j���[�V�����̒萔��`
//-----------------------------------
namespace anim
{
const int PATERN_ANIM = 5;	// �A�j���[�V�����p�^�[��
const int FRAME_ANIM = 5;	// �A�j���[�V�������؂�ւ��t���[����
}
}

//====================================================
// �R���X�g���N�^
//====================================================
CFishShadow::CFishShadow(int nPriority) : CAnim3D(nPriority), m_fTimerVanish(0.0f), m_nCntBubble(0)
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CFishShadow::~CFishShadow()
{

}

//====================================================
// ��������
//====================================================
CFishShadow* CFishShadow::Create(int nPatern)
{
	CFishShadow* pFishShadow = nullptr;

	pFishShadow = new CFishShadow;

	if (pFishShadow != nullptr)
	{
		pFishShadow->Init();
		pFishShadow->InitSpawn(nPatern);
	}

	return pFishShadow;
}

//====================================================
// ����������
//====================================================
HRESULT CFishShadow::Init(void)
{
	// �p���N���X�̏�����
	CAnim3D::Init();

	// �e�N�X�`���ݒ�
	int nIdxTexture = Texture::GetIdx(&PATH_TEX[0]);
	SetIdxTexture(nIdxTexture);

	// �O�ʂɏo��
	EnableZtest(true);

	// �F�����ݒ�
	SetColor(COL_INIT);

	// �T�C�Y�ݒ�
	SetSize(0.0f, 0.0f);

	// �A�j���[�V�����ݒ�
	SetNumAnim(anim::PATERN_ANIM);
	SetSpeedAnim(anim::FRAME_ANIM);
	EnableLoop(true);

	return S_OK;
}

//====================================================
// �X�|�[���̏�����
//====================================================
void CFishShadow::InitSpawn(int nPatern)
{
	CIceManager *pIceMgr = CIceManager::GetInstance();
	if (pIceMgr == nullptr)
		return;

	//--------------------------------
	// �ڕW�ʒu�̐ݒ�
	//--------------------------------
	D3DXVECTOR3 posDest = { 0.0f,0.0f,0.0f };

	switch (nPatern)	// �p�^�[�����Ƃ̃O���b�h�ʒu���擾
	{
	case CEnemy::E_Spawn::SPAWN_RU:
		posDest = pIceMgr->GetRightUpGrid().pos;
		break;
	case CEnemy::E_Spawn::SPAWN_LU:
		posDest = pIceMgr->GetLeftUpGrid().pos;
		break;
	case CEnemy::E_Spawn::SPAWN_RD:
		posDest = pIceMgr->GetRightDownGrid().pos;
		break;
	case CEnemy::E_Spawn::SPAWN_LD:
		posDest = pIceMgr->GetLeftDownGrid().pos;
		break;
	default:
		break;
	}

	m_posDest = posDest * RATE_DEST;

	//--------------------------------
	// �����ʒu�̐ݒ�
	//--------------------------------
	D3DXVECTOR3 posInit = m_posDest;
	D3DXVECTOR3 vecAdd;

	// �ڕW�ʒu���炳��ɉ�������
	D3DXVec3Normalize(&vecAdd, &m_posDest);
	vecAdd *= DIST_APPER;

	posInit += vecAdd;

	m_posInit = posInit;

	SetPosition(posInit);

	//--------------------------------
	// �����̐ݒ�
	//--------------------------------
	float fAngle = atan2f(-vecAdd.x, -vecAdd.z);

	SetRotation(D3DXVECTOR3(0.0f, fAngle, 0.0f));
}

//====================================================
// �I������
//====================================================
void CFishShadow::Uninit(void)
{
	// �p���N���X�̏I��
	CAnim3D::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CFishShadow::Update(void)
{
	// �p���N���X�̍X�V
	CAnim3D::Update();

	if (m_fTimerVanish >= fishshadow::TIME_VANISH)
	{
		Uninit();
		return;
	}

	// �^�C�}�[���Z
	m_fTimerVanish += CManager::GetDeltaTime();

	if (m_fTimerVanish <= TIME_FADEIN)	// �t�F�[�h�C�����
		UpdateFadeIn();
	else if (m_fTimerVanish >= fishshadow::TIME_VANISH - TIME_FADEOUT)	// �t�F�[�h�A�E�g���
		UpdateFadeOut();

	// �ړ�����
	Move();

	m_nCntBubble++;

	if (m_nCntBubble == FRAME_BUBBLE)
	{
		// �p�[�e�B�N�����o��
		CParticle::Create(GetPosition(), CParticle::TYPE::TYPE_BUBBLE_SINK);

		m_nCntBubble = 0;
	}
}

//====================================================
// �t�F�[�h�C�����
//====================================================
void CFishShadow::UpdateFadeIn(void)
{
	// �^�C�}�[�̃C�[�W���O
	float fTime = m_fTimerVanish / TIME_FADEIN;
	float fRate = easing::EaseOutExpo(fTime);

	SetAlpha(fRate);
	SetVtx();
}

//====================================================
// �t�F�[�h�A�E�g���
//====================================================
void CFishShadow::UpdateFadeOut(void)
{
	// �^�C�}�[�̃C�[�W���O
	float fTimer = TIME_FADEOUT - (fishshadow::TIME_VANISH - m_fTimerVanish);

	float fTime = fTimer / TIME_FADEIN;
	float fRate = easing::EaseOutExpo(fTime);

	SetAlpha(1.0f - fRate);
	SetVtx();
}

//====================================================
// �ړ����
//====================================================
void CFishShadow::Move(void)
{
	D3DXVECTOR3 vecDiff = m_posDest - m_posInit;

	// �^�C�}�[�̃C�[�W���O
	float fTime = m_fTimerVanish / fishshadow::TIME_VANISH;
	float fRate = easing::EaseOutExpo(fTime);

	D3DXVECTOR3 pos = m_posInit + vecDiff * fRate;

	SetPosition(pos);

	// �T�C�Y�ݒ�
	SetSize(WIDTH * fRate,HEIGHT * fRate);
}

//====================================================
// �`�揈��
//====================================================
void CFishShadow::Draw(void)
{
	// �p���N���X�̕`��
	CAnim3D::Draw();
}