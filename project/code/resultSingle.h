//*****************************************************
//
// �V���O�����U���g�̏���[resultSingle.h]
// Author:���R����
//
//*****************************************************
#ifndef _RESULTSINGLE_H_
#define _RESULTSINGLE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;
class CNumber;

//*****************************************************
// �N���X��`
//*****************************************************
class CResultSingle : public CObject
{
public:
	enum E_State
	{
		STATE_NONE = 0,			// �������ĂȂ����
		STATE_FADE,				// �t�F�[�h���
		STATE_APPERCAPTION,		// ���o���o�����
		STATE_ENDAPPERCAPTION,	// ���o���o���I�����
		STATE_END,				// �I�����
		STATE_MAX
	};

	// ���U���g�̎��
	enum E_Result
	{
		RESULT_WIN = 0,			// ����
		RESULT_DEAD,			// ���S
		RESULT_TIMEOVER,		// �^�C���I�[�o�[
		RESULT_MAX
	};

	CResultSingle();	// �R���X�g���N�^
	~CResultSingle();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ϐ��擾�E�ݒ�֐�
	void SetState(CResultSingle::E_State state) { m_state = state; }	// ���
	CResultSingle::E_State GetState(void) { return m_state; }

	// �ÓI�����o�֐�
	static CResultSingle* Create(E_Result result);

private:
	// �����o�֐�
	void Create2D(void);		// 2DUI�̐���
	void CreateCaption(void);	// ���o���̐���
	void CreateBg(void);		// �w�i�̐���
	
	void UpdateFade(void);			// �t�F�[�h��Ԃ̍X�V
	void UpdateApperCaption(void);	// �L���v�V�����o����Ԃ̍X�V
	void Input(void);				// ����

	// �����o�ϐ�
	E_Result m_result;	// �����t���O
	CUI *m_pBg;			// �w�i�̃|�C���^
	CUI *m_pCaption;	// ���o���̃|�C���^

	E_State m_state;		// ���
	float m_fTimer;	// �^�C�}�[

	// ��ԍX�V�̊֐��|�C���^�^�G�C���A�X��`
	typedef void (CResultSingle::*FuncUpdateState)(void);

	// �ÓI�����o�ϐ�
	static FuncUpdateState s_aFuncUpdateState[];	// ��ԍX�V�֐�
};

#endif