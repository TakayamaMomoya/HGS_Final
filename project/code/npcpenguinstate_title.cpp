//*****************************************************
//
// �^�C�g���pNPC�y���M���X�e�[�g[npcpenguinstate_title.cpp]
// Author:�Ό��D�n
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "npcpenguinstate_title.h"
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
		const int MOTION_COUNT = 150;	// ���[�V���������鎞��
		const vector<CNPCPenguin::MOTION> NEXT_MOTION_PATTERN =
		{
			CNPCPenguin::MOTION_NECKSHAKE,		// ��U��
			CNPCPenguin::MOTION_STOMACH,		// ���x�^�@
			CNPCPenguin::MOTION_UNYO,			// �񂤂ɂ��
			CNPCPenguin::MOTION_UNYO,			// �񂤂ɂ��
			CNPCPenguin::MOTION_WINGPTPT,		// �H�p�^
			CNPCPenguin::MOTION_WINGPTPT		// �H�p�^
		};
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
HRESULT CNPCPenguinState_StandTitle::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_NEUTRAL);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_StandTitle::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_StandTitle::Update(CNPCPenguin* pPenguin)
{
	m_nCounter++;
	if (m_nCounter >= Stand::MOTION_COUNT)
	{// �X�e�[�g���ԏI��
		// �ǂ̃X�e�[�g�ɑJ�ڂ��邩���I
		CNPCPenguin::MOTION rnd = Stand::NEXT_MOTION_PATTERN[(rand() % (int)Stand::NEXT_MOTION_PATTERN.size())];
		switch (rnd)
		{
		case CNPCPenguin::MOTION_NECKSHAKE:
			pPenguin->SetState(new CNPCPenguinState_ShakeHeadTitle);
			break;
		case CNPCPenguin::MOTION_STOMACH:
			pPenguin->SetState(new CNPCPenguinState_StomachTitle);
			break;
		case CNPCPenguin::MOTION_UNYO:
			pPenguin->SetState(new CNPCPenguinState_UNYOTitle);
			break;
		case CNPCPenguin::MOTION_WINGPTPT:
			pPenguin->SetState(new CNPCPenguinState_WingPTPTTitle);
			break;
		default:
			m_nCounter = 0;
			break;
		}
	}
}

//*****************************************************
// ��U��X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_ShakeHeadTitle::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_NECKSHAKE);

	// �y���M���̉H�΂�����
	CSound::GetInstance()->Play(CSound::LABEL_SE_FLAPPING_WING);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_ShakeHeadTitle::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_ShakeHeadTitle::Update(CNPCPenguin* pPenguin)
{
	m_nCounter++;
	if (m_nCounter >= ShakeHead::MOTION_COUNT)
	{// �X�e�[�g���ԏI��
		pPenguin->SetState(new CNPCPenguinState_StandTitle);
	}
}

//*****************************************************
// ���x�^�X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_StomachTitle::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_STOMACH);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_StomachTitle::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_StomachTitle::Update(CNPCPenguin* pPenguin)
{
	m_nCounter++;
	if (m_nCounter >= Stomach::MOTION_COUNT)
	{// �X�e�[�g���ԏI��
		pPenguin->SetState(new CNPCPenguinState_StandTitle);
	}
}

//*****************************************************
// �񂤂˃X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_UNYOTitle::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_UNYO);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_UNYOTitle::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_UNYOTitle::Update(CNPCPenguin* pPenguin)
{
	if (pPenguin->IsFinish())
	{// �񂤂ɂ��I�����
		pPenguin->SetState(new CNPCPenguinState_StandTitle);
	}
}

//*****************************************************
// �H�p�^�p�^�X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_WingPTPTTitle::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_WINGPTPT);

	// �y���M���̉H�΂�����
	CSound::GetInstance()->Play(CSound::LABEL_SE_FLAPPING_WING);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_WingPTPTTitle::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_WingPTPTTitle::Update(CNPCPenguin* pPenguin)
{
	if (pPenguin->IsFinish())
	{// �H�p�^�I�����
		pPenguin->SetState(new CNPCPenguinState_StandTitle);
	}
}
