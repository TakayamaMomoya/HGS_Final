//*****************************************************
//
// �V���O���������U���g�̏���[resultSingleWin.h]
// Author:���R����
//
//*****************************************************
#ifndef _RESULTSINGLEWIN_H_
#define _RESULTSINGLEWIN_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "resultSingle.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;
class CNumber;
class CRankingSingle;

//*****************************************************
// �N���X��`
//*****************************************************
class CResultSingleWin : public CResultSingle
{
public:
	enum E_State
	{
		STATE_NONE = 0,		// �������ĂȂ����
		STATE_MOVECAMERA,	// �J�����ړ����
		STATE_APPERSCORE,	// �X�R�A�o��
		STATE_APPERRANKING,	// �����L���O�o��
		STATE_WAIT,			// �ҋ@���
		STATE_END,			// �I�����
		STATE_MAX
	};
	enum E_ScoreCaption
	{
		CAPTION_SCORE = 0,	// �X�R�A
		CAPTION_TIMEPECK,	// ��������
		CAPTION_MAX
	};

	CResultSingleWin();	// �R���X�g���N�^
	~CResultSingleWin();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ϐ��擾�E�ݒ�֐�

private:
	// �萔��`
	static constexpr int NUM_RANKING = 3;	// �����L���O�̐�

	// �����o�֐�
	void Create2D(void);			// 2DUI�̐���
	void CreateOwnScore(void);		// ���g�̃X�R�A�̐���
	void CreateRankingNumber(void);	// �����L���O�����̐���

	void UpdateMoveCamera(void);	// �J�����ړ���Ԃ̍X�V
	void UpdateApperScore(void);	// �X�R�A�o����Ԃ̍X�V
	void UpdateApperRanking(void);	// �����L���O�o����Ԃ̍X�V
	void UpdateWait(void);			// �ҋ@��Ԃ̍X�V

	void Input(void);				// ���͏���

	// �����o�ϐ�
	CUI *m_apCaptionScore[CAPTION_MAX];		// ���g�̃L���v�V�����̃|�C���^
	CNumber *m_apNumberOwn[CAPTION_MAX];	// ���g�̐��т̐����|�C���^

	CNumber *m_apRankingNumber[NUM_RANKING][CAPTION_MAX];	// �����L���O�̐����̔z��
	CRankingSingle *m_pRanking;								// �����L���O����
	CUI *m_pFrame;											// �t���[���̃|���S��

	E_State m_state;		// ���
	float m_fTimer;			// �^�C�}�[

	// ��ԍX�V�̊֐��|�C���^�^�G�C���A�X��`
	typedef void (CResultSingleWin::*FuncUpdateState)(void);

	// �ÓI�����o�ϐ�
	static FuncUpdateState s_aFuncUpdateState[];	// ��ԍX�V�֐�
};

#endif