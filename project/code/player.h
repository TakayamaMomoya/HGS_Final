//*****************************************************
//
// �v���C���[�̏���[player.cpp]
// Author:���R����
//
//*****************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "character.h"

//*****************************************************
// �O���錾
//*****************************************************
class CInputManager;
class CShadow;
class CUI;
class CPresent;
class CHouse;
class CGauge;
class CCollisionSphere;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayer : public CCharacter
{
public:
	// ���[�V������
	enum MOTION
	{
		MOTION_NEUTRAL = 0,
		MOTION_WALK,
		MOTION_WALKFOURLEG,
		MOTION_WALKTWOLEG,
		MOTION_MAX
	};
	// �v���C���[���
	enum E_State
	{
		STATE_NONE = 0,		// ���ł��Ȃ����
		STATE_NORMAL,		// �ʏ�
		STATE_DEATH,		// ��
		STATE_MAX
	};

	CPlayer(int nPriority = 5);	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	virtual void Hit(float fDamage) override;	// �q�b�g����
	void VibJoypad(float fPow, int nFrame);		// �W���C�p�b�h��U��������

	// �擾�E�ݒ�
	void EnableInput(bool bEnable) { m_bEnableInput = bEnable; }	// ���͉\�t���O
	bool IsEnableInput(void) { return m_bEnableInput; }
	void SetState(E_State state) { m_state = state; }				// ���
	E_State GetState(void) { return m_state; }
	void BindInputMgr(CInputManager *pInputMgr) { m_pInputMgr = pInputMgr; }	// ���̓}�l�[�W���[
	CInputManager *GetInpuManager(void) { return m_pInputMgr; }
	CPresent* GetPresent(void) { return m_pPresent; }	// �v���[���g
	void SetID(int nID) { m_nID = nID; }	// �ԍ�
	int GetID(void) { return m_nID; }

	// �ÓI�����o�֐�
	static CPlayer* Create(void);										// ��������
	static vector<CPlayer*> GetInstance(void) { return s_apPlayer; }	// �C���X�^���X�̎擾
	static void EnableInputAll(bool bValue);							// �S�v���C���[�̓��̓t���O�ݒ�
	static int GetNumPlayer(void) { return (int)s_apPlayer.size(); }	// �v���C���[���̎擾

private:
	// �\���̒�`
	struct S_FragMotion
	{// ���[�V�����t���O�̍\����
		bool bWalk;		// ���s
		bool bPeck;		// �˂���
		bool bJump;		// �W�����v
	};

	// �����o�֐�
	void Input(void);		// ����
	
	void MoveAnalog(void);		// �A�i���O�ړ�
	void InputMoveAnalog(void);	// �A�i���O�ړ�����
	void Forward(void);			// �O�i����

	void Interact(); // �C���^���N�g�\��

	void SwapPresent(); // �v���[���g���������鏈��

	void ControlGauge(); // �Q�[�W�̑���

	void Event(EVENT_INFO* pEventInfo) override;	// ���[�V�����C�x���g
	void ManageMotion(void);						// ���[�V�����̊Ǘ�

	void Debug(void);	// �f�o�b�O����

	// �����o�ϐ�
	int m_nID;					// �ԍ�
	bool m_bEnableInput;		// ���͉\�t���O
	E_State m_state;			// �v���C���[���
	S_FragMotion m_fragMotion;	// ���[�V�����t���O
	CInputManager *m_pInputMgr;	// ���̓}�l�[�W���[
	CUI* m_pInteract;			// �C���^���N�gUI
	CPresent* m_pPresent;		// �v���[���g�̃|�C���^
	CHouse* m_pNearHouse;			// �߂������̃|�C���^
	CCollisionSphere *m_pCollision;	// �����蔻��
	
	unsigned int m_nAnswerCount; // �A�������J�E���^�[
	CGauge* m_pGauge; // �A�������Q�[�W
	float m_fSabTime; // �Q�[�W����������܂ł̎���

	// �ÓI�����o�ϐ�
	static vector<CPlayer*> s_apPlayer;	// �i�[�p�̔z��
};

#endif