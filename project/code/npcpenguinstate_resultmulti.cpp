//*****************************************************
//
// �}���`���[�h�̃��U���g�X�e�[�g[npcpenguinstate_resultmulti.cpp]
// Author:�Ό��D�n
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "npcpenguinstate_resultmulti.h"
#include "collision.h"
#include "debugproc.h"
#include "motion.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	namespace Loser
	{
		const float ROTATE_SPEED = 0.005f;
	}
}

//*****************************************************
// ���҃o���U�C�X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_BANZAI::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_VICTORY);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_BANZAI::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_BANZAI::Update(CNPCPenguin* pPenguin)
{
	
}

//*****************************************************
// �s�ғ����X�e�[�g
//*****************************************************
//=====================================================
// ����������
//=====================================================
HRESULT CNPCPenguinState_Flee::Init(CNPCPenguin* pPenguin)
{
	pPenguin->SetMotion(CNPCPenguin::MOTION::MOTION_FAIL);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CNPCPenguinState_Flee::Uninit(void)
{
	delete this;
}

//=====================================================
// �X�V����
//=====================================================
void CNPCPenguinState_Flee::Update(CNPCPenguin* pPenguin)
{
	float length = D3DXVec3Length(&(c_centorPos - pPenguin->GetPosition()));
	D3DXVECTOR3 rot = pPenguin->GetRotation();

	// �ړ�������ς���
	rot.y += Loser::ROTATE_SPEED;
	rot.y = fmodf(rot.y + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI;

	// �ʒu�v�Z
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, pPenguin->GetPosition().y, 0.0f);
	pos.x = -sinf(rot.y - 0.5f * D3DX_PI) * length + c_centorPos.x;
	pos.z = -cosf(rot.y - 0.5f * D3DX_PI) * length + c_centorPos.z;

	// �ʒu�����ݒ�
	pPenguin->SetPosition(pos);
	pPenguin->SetRotation(rot);
}
