//*****************************************************
//
// �v���C���[����Ȃ��y���M��[npcpenguin.h]
// Author:�Ό��D�n
//
//*****************************************************
#ifndef _SELECTMODEPENGUIN_H_
#define _SELECTMODEPENGUIN_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;
class CShadow;
__interface INPCPenguinState;

//*****************************************************
// �N���X�̒�`
//*****************************************************
//****************************************
// ���[�h�I����ʂ̗V�ԃy���M���I�u�W�F�N�g�N���X
//****************************************
class CNPCPenguin : public CMotion
{
public:
	// ���[�V������
	enum MOTION
	{
		MOTION_NEUTRAL = 0,
		MOTION_WALK,
		MOTION_STARTJUMP,
		MOTION_STAYJUMP,
		MOTION_LANDING,
		MOTION_PECK,
		MOTION_FLOW,
		MOTION_VICTORY,
		MOTION_FAIL,
		MOTION_GUTS,
		MOTION_NECKSHAKE,	
		MOTION_UNYO,	// �񂤂�
		MOTION_CANNOTPECK,
		MOTION_MULTIAPPEAR,
		MOTION_WINGPTPT,	// �H���p�^�p�^
		MOTION_STOMACH,	// ���x�^
		MOTION_FALL,
		MOTION_MAX
	};
	// �y���M���X�L����
	enum SKIN
	{
		SKIN_PILOT = 0,		// �p�C���b�g
		SKIN_HEADBANG,		// �n�`�}�L�y���M��
		SKIN_PIRATE,		// �C��
		SKIN_SWIMSUIT,		// �����i�����H�j
		SKIN_NONE,			// ���R��
		SKIN_MAX
	};

	CNPCPenguin(int nPriority = 4);	// �R���X�g���N�^
	~CNPCPenguin();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CNPCPenguin* Create(INPCPenguinState* pState = nullptr, SKIN skin = SKIN_NONE);	// ��������

	// �ݒ�
	void SetState(INPCPenguinState* pState);

private:
	// �����o�֐�
	void FollowIce(void);

	// �����o�ϐ�
	CCollisionSphere *m_pCollisionSphere;	// ���̔���
	INPCPenguinState *m_pState;				// �����X�e�[�g
	CShadow *m_pShadow;						// �e�̃|�C���^
};

//****************************************
// �����X�e�[�g
//****************************************
//----------------------------------------
// �y���M���̓����X�e�[�g���C���^�[�t�F�[�X
//----------------------------------------
__interface INPCPenguinState
{
	HRESULT Init(CNPCPenguin *pPenguin) = 0;
	void Uninit(void) = 0;
	void Update(CNPCPenguin* pPenguin) = 0;
};

#endif