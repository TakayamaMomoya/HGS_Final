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
#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************
class CInputManager;
class CShadow;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayer : public CMotion
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
		MOTION_STOMACH,		// ���x�^
		MOTION_FALL,
		MOTION_BLOW,		// �������
		MOTION_STANDUP,		// �����オ��
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
	void SetMove(D3DXVECTOR3 move) { m_move = move; }				// �ړ���
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void EnableInput(bool bEnable) { m_bEnableInput = bEnable; }	// ���͉\�t���O
	bool IsEnableInput(void) { return m_bEnableInput; }
	void SetState(E_State state) { m_state = state; }				// ���
	E_State GetState(void) { return m_state; }
	void BindInputMgr(CInputManager *pInputMgr) { m_pInputMgr = pInputMgr; }	// ���̓}�l�[�W���[
	CInputManager *GetInpuManager(void) { return m_pInputMgr; }
	void SetID(int nID) { m_nID = nID; }	// �ԍ�
	int GetID(void) { return m_nID; }
	void SetShadowPos(D3DXVECTOR3 pos);

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
	void DecreaseMove(void);	// �ړ��ʂ̌���
	void FactingRot(void);		// �����̕␳
	
	void Event(EVENT_INFO* pEventInfo) override;	// ���[�V�����C�x���g
	void ManageMotion(void);						// ���[�V�����̊Ǘ�

	void Debug(void);	// �f�o�b�O����

	// �����o�ϐ�
	int m_nID;					// �ԍ�
	bool m_bEnableInput;		// ���͉\�t���O
	D3DXVECTOR3 m_move;			// �ړ���
	E_State m_state;			// �v���C���[���
	CShadow *m_pShadow;			// �e�̃|�C���^
	S_FragMotion m_fragMotion;	// ���[�V�����t���O
	CInputManager *m_pInputMgr;	// ���̓}�l�[�W���[

	// �ÓI�����o�ϐ�
	static vector<CPlayer*> s_apPlayer;	// �i�[�p�̔z��
};

#endif