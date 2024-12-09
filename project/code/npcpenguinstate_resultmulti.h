//*****************************************************
//
// �}���`���[�h�̃��U���g�X�e�[�g[npcpenguinstate_resultmulti.h]
// Author:�Ό��D�n
//
//*****************************************************
#ifndef _NPCPENGUINSTATE_RESULTMULTI_H_
#define _NPCPENGUINSTATE_RESULTMULTI_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "npcpenguin.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;

//*****************************************************
// �N���X�̒�`
//*****************************************************
//****************************************
// ���҃o���U�C�X�e�[�g
//****************************************
class CNPCPenguinState_BANZAI : public INPCPenguinState
{
public:
	CNPCPenguinState_BANZAI(){ m_nCounter = 0; }
	~CNPCPenguinState_BANZAI(){}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
private:
	int m_nCounter;	// �X�e�[�g���s�J�E���^
};

//****************************************
// �s�ғ����X�e�[�g
//****************************************
class CNPCPenguinState_Flee : public INPCPenguinState
{
public:
	CNPCPenguinState_Flee(D3DXVECTOR3 centorPos) : c_centorPos(centorPos){}
	~CNPCPenguinState_Flee() {}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
private:
	const D3DXVECTOR3 c_centorPos;	// ��]�̒��S
};

#endif