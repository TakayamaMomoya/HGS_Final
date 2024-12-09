//*****************************************************
//
// ���[�h�I���X�e�[�g[npcpenguinstate_selectmode.h]
// Author:�Ό��D�n
//
//*****************************************************
#ifndef _NPCPENGUINSTATE_SELECTMODE_H_
#define _NPCPENGUINSTATE_SELECTMODE_H_

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
class CNPCPenguinState_Stand : public INPCPenguinState
{
public:
	CNPCPenguinState_Stand(){ m_nCounter = 0; }
	~CNPCPenguinState_Stand(){}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
private:
	int m_nCounter;	// �X�e�[�g���s�J�E���^
};

//****************************************
// �����X�e�[�g
//****************************************
class CNPCPenguinState_Move : public INPCPenguinState
{
public:
	CNPCPenguinState_Move() { m_nCounter = 0; }
	~CNPCPenguinState_Move() {}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
private:
	int m_nCounter;	// �X�e�[�g���s�J�E���^
};

//****************************************
// �]�уX�e�[�g
//****************************************
class CNPCPenguinState_Fall : public INPCPenguinState
{
public:
	CNPCPenguinState_Fall() {}
	~CNPCPenguinState_Fall() {}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
};

//****************************************
// ��U��X�e�[�g
//****************************************
class CNPCPenguinState_ShakeHead : public INPCPenguinState
{
public:
	CNPCPenguinState_ShakeHead() { m_nCounter = 0; }
	~CNPCPenguinState_ShakeHead() {}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
private:
	int m_nCounter;	// �X�e�[�g���s�J�E���^
};

//****************************************
// ���x�^�X�e�[�g
//****************************************
class CNPCPenguinState_Stomach : public INPCPenguinState
{
public:
	CNPCPenguinState_Stomach() { m_nCounter = 0; }
	~CNPCPenguinState_Stomach() {}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
private:
	int m_nCounter;	// �X�e�[�g���s�J�E���^
};

//****************************************
// ���ɂ��X�e�[�g
//****************************************
class CNPCPenguinState_UNYO : public INPCPenguinState
{
public:
	CNPCPenguinState_UNYO() {}
	~CNPCPenguinState_UNYO() {}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
};

//****************************************
// �H�p�^�p�^�X�e�[�g
//****************************************
class CNPCPenguinState_WingPTPT : public INPCPenguinState
{
public:
	CNPCPenguinState_WingPTPT() {}
	~CNPCPenguinState_WingPTPT() {}
	HRESULT Init(CNPCPenguin* pPenguin);
	void Uninit(void);
	void Update(CNPCPenguin* pPenguin);
};

#endif