//*****************************************************
//
// �v���C���[����Ȃ��y���M��[npcpenguin.cpp]
// Author:�Ό��D�n
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "npcpenguin.h"
#include "collision.h"
#include "debugproc.h"
#include "motion.h"
#include "shadow.h"
#include "player.h"
#include "iceManager.h"
#include "ice.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	namespace Skin
	{
		const vector<string> PATH_MODEL =
		{
			"data\\MOTION\\motionPenguin.txt",	// ���R��
			"data\\MOTION\\motionPenguin_Pilot.txt",	// �p�C���b�g
			"data\\MOTION\\motionPenguin_HeadBang.txt",	// �n�`�}�L
			"data\\MOTION\\motionPenguin_Pirate.txt",	// �C��
			"data\\MOTION\\motionPenguin_SwimSuit.txt",	// ����
		};
	}
	const string DEFAULT_PATH_MODEL = "data\\MOTION\\motionPenguin.txt";
	const float SCALE_BODY = 1.8f;	// �̂̃X�P�[��
	
	const float FACT_DECREASE_MOVE = 0.9f;	// �ړ��ʂ̌����W��
	const float ADD_MOVE = 4.0f;	// �ړ��̒ǉ���
	
	const float RADIUS_COLLISION = 200.0f;	// ���̔���̔��a
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CNPCPenguin::CNPCPenguin(int nPriority) : CMotion(nPriority)
{
	m_pCollisionSphere = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CNPCPenguin::~CNPCPenguin()
{

}

//=====================================================
// ��������
//=====================================================
CNPCPenguin* CNPCPenguin::Create(INPCPenguinState* pState, SKIN skin)
{
	CNPCPenguin *pNPCPenguin = nullptr;

	pNPCPenguin = new CNPCPenguin;

	if (pNPCPenguin != nullptr)
	{
		// �������O�ɃX�L���ݒ�
		if (skin == SKIN::SKIN_NONE)
		{
			pNPCPenguin->Load((char*)&DEFAULT_PATH_MODEL[0]);
		}
		else
		{
			pNPCPenguin->Load((char*)&player::PATH_BODY[skin][0]);
		}

		// ������
		pNPCPenguin->Init();
		if (pState != nullptr)
		{
			pNPCPenguin->SetState(pState);
		}
	}

	return pNPCPenguin;
}

//=====================================================
// �X�e�[�g�ݒ菈��
//=====================================================
void CNPCPenguin::SetState(INPCPenguinState* pState)
{
	if (m_pState != nullptr)
	{
		m_pState->Uninit();
		m_pState = nullptr;
	}
	
	m_pState = pState;
	if (m_pState != nullptr)
	{
		m_pState->Init(this);
	}
}

//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguin::Init(void)
{
	// �p���N���X�̏�����
	CMotion::Init();

	InitPose(0);

	// �X�P�[���̐ݒ�
	SetScale(SCALE_BODY);

	// ���̔��萶��
	m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG::TAG_PLAYER, CCollision::TYPE::TYPE_SPHERE, this);

	if (m_pCollisionSphere != nullptr)
	{
		m_pCollisionSphere->SetRadius(RADIUS_COLLISION);
		m_pCollisionSphere->SetPosition(GetPosition());
	}

	// �e�̐���
	m_pShadow = CShadow::Create(3);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguin::Uninit(void)
{
	// �e�E�����蔻��폜
	Object::DeleteObject((CObject**)&m_pShadow);
	Object::DeleteObject((CObject**)&m_pCollisionSphere);

	if (m_pState != nullptr)
	{
		m_pState->Uninit();
		m_pState = nullptr;
	}

	// �p���N���X�̏I��
	CMotion::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguin::Update(void)
{
	// ���[�V�����X�V
	CMotion::Update();

	// �X�ɏ���Ă���Ƃ���鏈��
	FollowIce();

	D3DXVECTOR3 pos = GetPosition();

	if (m_pCollisionSphere != nullptr)
	{// ���̔���̒Ǐ]
		m_pCollisionSphere->SetPosition(pos);

		// �u���b�N����
		m_pCollisionSphere->PushCollision(&pos, CCollision::TAG::TAG_BLOCK);

		// �L�����̈ʒu���f
		SetPosition(pos);
	}

	// �e�̒Ǐ]
	if (m_pShadow != nullptr)
		m_pShadow->SetPosition(pos);

	if (m_pState != nullptr)
	{
		m_pState->Update(this);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CNPCPenguin::Draw(void)
{
	// �p���N���X�̕`��
	CMotion::Draw();
}

//=====================================================
// �X�̒Ǐ]
//=====================================================
void CNPCPenguin::FollowIce(void)
{
	CIceManager* pIceMgr = CIceManager::GetInstance();

	if (pIceMgr == nullptr)
		return;

	int nGridV, nGridH;
	if (pIceMgr->GetIdxGridFromPosition(GetPosition(), &nGridV, &nGridH))
	{
		CIce* pIceStand = pIceMgr->GetGridIce(&nGridV, &nGridH);

		if (pIceStand != nullptr)
		{
			D3DXVECTOR3 pos = GetPosition();
			pos.y = pIceStand->GetPosition().y;
			SetPosition(pos);
		}
	}
}