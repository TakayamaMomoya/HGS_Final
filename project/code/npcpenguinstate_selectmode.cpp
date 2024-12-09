//*****************************************************
//
// ���[�h�I���y���M��[selectmodepenguin.cpp]
// Author:�Ό��D�n
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "npcpenguinstate_selectmode.h"
#include "collision.h"
#include "debugproc.h"
#include "motion.h"
#include "sound.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	namespace Stand
	{
		const int MOTION_COUNT = 60 * 3;	// ���[�V���������鎞��
		const vector<CNPCPenguin::MOTION> NEXT_MOTION_PATTERN =
		{
			CNPCPenguin::MOTION_WALK,		// �ړ�
			CNPCPenguin::MOTION_WALK,		// �ړ�
			CNPCPenguin::MOTION_WALK,		// �ړ�
			CNPCPenguin::MOTION_NECKSHAKE,	// ��U��
			CNPCPenguin::MOTION_STOMACH,		// ���x�^�@
			CNPCPenguin::MOTION_UNYO,		// �񂤂ɂ��
			CNPCPenguin::MOTION_WINGPTPT		// �H�p�^
		};
	}
	namespace Move
	{
		const int MOTION_COUNT = 60 * 5 + 20;	// ���[�V���������鎞��
		const int FALL_CHANCE = 18;			// �R�P�m���i�l�F���j
		const float MOVE_SPEED = 2.5f;		// �ړ����x
	}
	namespace ShakeHead
	{
		const int MOTION_COUNT = 60 * 2;	// ���[�V���������鎞��
	}
	namespace Stomach
	{
		const int MOTION_COUNT = 60 * 3;	// ���[�V���������鎞��
	}
}

//*****************************************************
// �����Ă邾���X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_Stand::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_NEUTRAL);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_Stand::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_Stand::Update(CNPCPenguin* pPenguin)
{
	m_nCounter++;
	if (m_nCounter >= Stand::MOTION_COUNT)
	{// �X�e�[�g���ԏI��
		// �ǂ̃X�e�[�g�ɑJ�ڂ��邩���I
		CNPCPenguin::MOTION rnd = Stand::NEXT_MOTION_PATTERN[(rand() % (int)Stand::NEXT_MOTION_PATTERN.size())];
		switch (rnd)
		{
		case CNPCPenguin::MOTION_WALK:
			pPenguin->SetState(new CNPCPenguinState_Move);
			break;
		case CNPCPenguin::MOTION_NECKSHAKE:
			pPenguin->SetState(new CNPCPenguinState_ShakeHead);
			break;
		case CNPCPenguin::MOTION_STOMACH:
			pPenguin->SetState(new CNPCPenguinState_Stomach);
			break;
		case CNPCPenguin::MOTION_UNYO:
			pPenguin->SetState(new CNPCPenguinState_UNYO);
			break;
		case CNPCPenguin::MOTION_WINGPTPT:
			pPenguin->SetState(new CNPCPenguinState_WingPTPT);
			break;
		default:
			m_nCounter = 0;
			break;
		}
	}
}

//*****************************************************
// �ړ��X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_Move::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_WALK);

	CSound::GetInstance()->Play(CSound::LABEL_SE_PENGUIN_VOICE01);	// �y���M���̉H�΂�����
	CSound::GetInstance()->Play(CSound::LABEL_SE_PENGUIN_WALKING);  // �y���M���̕�����

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_Move::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_Move::Update(CNPCPenguin* pPenguin)
{
	// �ړ�
	D3DXVECTOR3 rot = pPenguin->GetRotation();
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	move.x = -sinf(rot.y) * Move::MOVE_SPEED;
	move.z = -cosf(rot.y) * Move::MOVE_SPEED;

	pPenguin->Translate(move);

	// ���
	rot.y += 0.005f * D3DX_PI;
	pPenguin->SetRotation(rot);

	// �X�e�[�g�I���J�E���g
	m_nCounter++;
	if (m_nCounter >= Move::MOTION_COUNT)
	{// �X�e�[�g���ԏI��
		// �R�P�`�����X
		int rnd = rand() % 100;
		if (rnd < Move::FALL_CHANCE)
		{// �R�P
			pPenguin->SetState(new CNPCPenguinState_Fall);
		}
		else
		{// ���ʂɗ���
			pPenguin->SetState(new CNPCPenguinState_Stand);
		}
	}
}

//*****************************************************
// �]�уX�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_Fall::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_FALL);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_Fall::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_Fall::Update(CNPCPenguin* pPenguin)
{
	if (pPenguin->IsFinish())
	{// �R�P�I�����
		pPenguin->SetState(new CNPCPenguinState_Stand);
	}
}

//*****************************************************
// ��U��X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_ShakeHead::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_NECKSHAKE);

	// �y���M���̉H�΂�����
	CSound::GetInstance()->Play(CSound::LABEL_SE_FLAPPING_WING);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_ShakeHead::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_ShakeHead::Update(CNPCPenguin* pPenguin)
{
	m_nCounter++;
	if (m_nCounter >= ShakeHead::MOTION_COUNT)
	{// �X�e�[�g���ԏI��
		pPenguin->SetState(new CNPCPenguinState_Stand);
	}
}

//*****************************************************
// ���x�^�X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_Stomach::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_STOMACH);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_Stomach::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_Stomach::Update(CNPCPenguin* pPenguin)
{
	m_nCounter++;
	if (m_nCounter >= Stomach::MOTION_COUNT)
	{// �X�e�[�g���ԏI��
		pPenguin->SetState(new CNPCPenguinState_Stand);
	}
}

//*****************************************************
// �񂤂˃X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_UNYO::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_UNYO);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_UNYO::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_UNYO::Update(CNPCPenguin* pPenguin)
{
	if (pPenguin->IsFinish())
	{// �񂤂ɂ��I�����
		pPenguin->SetState(new CNPCPenguinState_Stand);
	}
}

//*****************************************************
// �H�p�^�p�^�X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_WingPTPT::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_WINGPTPT);

	// �y���M���̉H�΂�����
	CSound::GetInstance()->Play(CSound::LABEL_SE_FLAPPING_WING);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_WingPTPT::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_WingPTPT::Update(CNPCPenguin* pPenguin)
{
	if (pPenguin->IsFinish())
	{// �H�p�^�I�����
		pPenguin->SetState(new CNPCPenguinState_Stand);
	}
}
