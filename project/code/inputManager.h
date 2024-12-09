//*****************************************************
//
// ���̓}�l�[�W���[[inputManager.h]
// Author:���R����
//
//*****************************************************
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CInputManager
{
public:
	enum E_Button
	{// �{�^���̎��
		BUTTON_ENTER = 0,	// �G���^�[�{�^��
		BUTTON_READY,	// �����{�^��
		BUTTON_BACK,	// �߂�{�^��
		BUTTON_SKIP,	// �X�L�b�v�{�^��
		BUTTON_PAUSE,	// �|�[�Y
		BUTTON_AXIS_UP,	// ������L�[ �X�e�B�b�N��
		BUTTON_AXIS_DOWN,	// �������L�[
		BUTTON_AXIS_RIGHT,	// �E�����L�[
		BUTTON_AXIS_LEFT,	// �������L�[
		BUTTON_TRIGGER_UP,	// ������e��
		BUTTON_TRIGGER_DOWN,	// �������e�� �X�e�B�b�N�E
		BUTTON_TRIGGER_RIGHT,	// �E�����e��
		BUTTON_TRIGGER_LEFT,	// �������e��
		BUTTON_PECK,	// ��
		BUTTON_JUMP,	// �W�����v
		BUTTON_SCORE,	// �X�R�A
		BUTTON_RESULT,	// ���U���g���o
		BUTTON_SETICE,	// �X�ݒu
		BUTTON_MAX
	};
	struct S_Axis
	{// �����̂܂Ƃ�
		D3DXVECTOR3 axisMove;	// �ړ�����
		D3DXVECTOR3 axisCamera;	// �J�����𓮂�������
	};

	CInputManager();	// �R���X�g���N�^
	~CInputManager();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateDevice(void);
	bool GetTrigger(E_Button button) { return m_info.abTrigger[button]; }
	bool GetPress(E_Button button) { return m_info.abPress[button]; }
	bool GetRelease(E_Button button) { return m_info.abRelease[button]; }
	S_Axis GetAxis(void) { return m_axis; }

	float GetAngleMove(void) { return atan2f(-m_axis.axisMove.x, -m_axis.axisMove.z); }	// �ړ����͊p�x�̎擾

	// �ÓI�����o�֐�
	static CInputManager *Create(void);
	static CInputManager *GetInstance(int nIdx = 0);
	static void InitDevice(HINSTANCE hInstance, HWND hWnd);	// �f�o�C�X�̑�������
	static void UninitDevice(void);	// �f�o�C�X�̑��I��
	static void ReleaseAll(void);	// �S�C���X�^���X���
	static void UpdateAll(void);	// �S�C���X�^���X�X�V
	static vector<CInputManager*> GetArray(void) { return s_aInputMgr; }	// �z��̎擾

private:
	struct S_Info
	{// ���̍\����
		bool abTrigger[BUTTON_MAX];	// �g���K�[���
		bool abPress[BUTTON_MAX];	// �v���X���
		bool abRelease[BUTTON_MAX];	// �����[�X���
	};

	S_Info m_info;		// ���
	S_Axis m_axis;		// �����̏��
	int m_nID;			// �ԍ�
	float m_fDeadZone;	// �f�b�h�]�[��

	static vector<CInputManager*> s_aInputMgr;	// �i�[�p�z��
};

#endif
