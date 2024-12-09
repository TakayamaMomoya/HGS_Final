//*****************************************************
//
// �V���O���������U���g�̏���[resultSingleLose.h]
// Author:���R����
//
//*****************************************************
#ifndef _RESULTSINGLELOSE_H_
#define _RESULTSINGLELOSE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "resultSingle.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;

//*****************************************************
// �N���X��`
//*****************************************************
class CResultSingleLose : public CResultSingle
{
public:
	enum E_State
	{
		STATE_NONE = 0,			// �������ĂȂ����
		STATE_APPER_MENU,		// ���j���[�I�����
		STATE_SELECT,			// �I�����
		STATE_END,				// �I�����
		STATE_MAX
	};
	// �񋓌^��`
	enum E_Select
	{
		SELECT_CONTINUE = 0,	// ������
		SELECT_QUIT,		// �͂�
		SELECT_MAX
	};

	CResultSingleLose();	// �R���X�g���N�^
	~CResultSingleLose();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ϐ��擾�E�ݒ�֐�

private:
	// �����o�֐�
	void Create2D(void);			// 2DUI�̐���
	void CreateMenu(void);			// ���j���[�̐���
	void UpdateApperMenu(void);		// ���j���[�̏o��
	void UpdateSelect(void);		// �I�����
	void Fade(E_Select select);			// �t�F�[�h���鏈��

	// �����o�ϐ�
	E_State m_state;						// ���
	float m_fTimer;							// �^�C�}�[
	CUI *m_apMenu[E_Select::SELECT_MAX];	// ���j���[���ڂ̃|���S��
	E_Select m_select;						// �I������

	// ��ԍX�V�̊֐��|�C���^�^�G�C���A�X��`
	typedef void (CResultSingleLose::*FuncUpdateState)(void);

	// �ÓI�����o�ϐ�
	static FuncUpdateState s_aFuncUpdateState[];	// ��ԍX�V�֐�
};

#endif