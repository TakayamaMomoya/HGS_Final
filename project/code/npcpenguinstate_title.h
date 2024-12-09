//*****************************************************
//
// �^�C�g���pNPC�y���M���X�e�[�g[npcpenguinstate_title.h]
// Author:�Ό��D�n
//
//*****************************************************
#ifndef _NPCPENGUINSTATE_TITLE_H_
#define _NPCPENGUINSTATE_TITLE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "npcpenguin.h"

//*****************************************************
// �O���錾
//*****************************************************
__interface INPCPenguinState;

//*****************************************************
// �N���X�̒�`
//*****************************************************
//****************************************
// �ҋ@�X�e�[�g
//****************************************
class CNPCPenguinState_StandTitle : public INPCPenguinState
{
public:
	CNPCPenguinState_StandTitle(){ m_nCounter = 0; }
	~CNPCPenguinState_StandTitle(){}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
private:
	int m_nCounter;	// �X�e�[�g���s�J�E���^
};

//****************************************
// ��U��X�e�[�g
//****************************************
class CNPCPenguinState_ShakeHeadTitle : public INPCPenguinState
{
public:
	CNPCPenguinState_ShakeHeadTitle() { m_nCounter = 0; }
	~CNPCPenguinState_ShakeHeadTitle() {}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
private:
	int m_nCounter;	// �X�e�[�g���s�J�E���^
};

//****************************************
// ���x�^�X�e�[�g
//****************************************
class CNPCPenguinState_StomachTitle : public INPCPenguinState
{
public:
	CNPCPenguinState_StomachTitle() { m_nCounter = 0; }
	~CNPCPenguinState_StomachTitle() {}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
private:
	int m_nCounter;	// �X�e�[�g���s�J�E���^
};

//****************************************
// ���ɂ��X�e�[�g
//****************************************
class CNPCPenguinState_UNYOTitle : public INPCPenguinState
{
public:
	CNPCPenguinState_UNYOTitle() {}
	~CNPCPenguinState_UNYOTitle() {}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
};

//****************************************
// �H�p�^�p�^�X�e�[�g
//****************************************
class CNPCPenguinState_WingPTPTTitle : public INPCPenguinState
{
public:
	CNPCPenguinState_WingPTPTTitle() {}
	~CNPCPenguinState_WingPTPTTitle() {}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
};

#endif