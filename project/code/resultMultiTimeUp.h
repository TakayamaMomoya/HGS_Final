//*****************************************************
//
// �}���`�^�C���A�b�v���U���g[resultMultiTimeUp.h]
// Author:���R����
//
//*****************************************************
#ifndef _RESULTMULTITIMEUP_H_
#define _RESULTMULTITIMEUP_H_

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
class CResultMultiTimeUp : public CResultSingle
{
public:
	// �񋓌^��`
	enum E_State
	{// ���
		STATE_NONE = 0,		// �������ĂȂ����
		STATE_APPER_MENU,	// ���j���[�I�����
		STATE_WAIT,			// �ҋ@���
		STATE_END,			// �I�����
		STATE_MAX
	};

	CResultMultiTimeUp();	// �R���X�g���N�^
	~CResultMultiTimeUp();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�֐�
	void Create2D(void);			// 2DUI�̐���
	void CreateMenu(void);			// ���j���[�̐���
	void UpdateApperMenu(void);		// ���j���[�̏o��
	void UpdateWait(void);			// �ҋ@���̍X�V

	// �����o�ϐ�
	E_State m_state;	// ���
	float m_fTimer;		// �^�C�}�[
	CUI *m_pMenu;		// ���j���[

	// ��ԍX�V�̊֐��|�C���^�^�G�C���A�X��`
	typedef void (CResultMultiTimeUp::*FuncUpdateState)(void);

	// �ÓI�����o�ϐ�
	static FuncUpdateState s_aFuncUpdateState[];	// ��ԍX�V�֐�
};

#endif