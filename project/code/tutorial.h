//*****************************************************
//
// �`���[�g���A������[tutorial.h]
// Author:���R����
//
//*****************************************************
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "scene.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;
class CUIPlayer;
class CFade2D;
class CGauge;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CTutorial : public CScene
{
public:
	// �񋓌^��`
	enum E_State
	{// ���
		STATE_NONE = 0,			// ���ł��Ȃ����
		STATE_MOVE,				// �ړ����
		STATE_PECK,				// �˂������
		STATE_EXPLAIN_ICE,		// �X����
		STATE_EXPLAIN_BREAK,	// �j�����
		STATE_JUMP,				// �W�����v
		STATE_EXPLAIN_ENEMY,	// �G����
		STATE_ALBATROSS,		// �A�z�E�h��
		STATE_END,				// �I�����
		STATE_MAX
	};
	CTutorial();	// �R���X�g���N�^
	~CTutorial();	// �f�X�g���N�^

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	
	void ProgressState(void);	// �`���[�g���A����i�߂�

	// �ϐ��擾�E�ݒ�֐�
	void SetState(E_State state) { m_state = state; }	// ���
	E_State GetState(void) { return m_state; }
	int GetCntProgress(void) { return m_nCntProgress; }	// ��Ԑi�s�J�E���^�[
	void AddCntProgress(CPlayer *pPlayer);

	// �ÓI�����o�֐�
	static CTutorial *GetInstance(void) { return s_pTutorial; }	// �C���X�^���X�擾

private:
	// �����o�֐�
	void UpdateEnd(void);		// �I�����
	void CheckProgress(void);	// �i�s���f
	void InputSkip(void);		// �X�L�b�v����
	void Debug(void);			// �f�o�b�O

	// �����o�ϐ�
	E_State m_state;				// ���
	CUIPlayer *m_pUIPlayer;			// �v���C���[UI�̃|�C���^
	float m_fTimeEnd;				// �I���^�C�}�[
	int m_nCntProgress;				// �i�s�J�E���^�[
	CUI *m_pCaption;				// �L���v�V����
	CFade2D *m_pFadeCaption;		// �L���v�V�����̃t�F�[�h
	bool m_abComplete[NUM_PLAYER];	// �����t���O
	CGauge *m_pGaugeSkip;			// �X�L�b�v�Q�[�W
	float m_fTimerSkip;				// �X�L�b�v�^�C�}�[
	CUI *m_pHint;					// �q���g�̃|���S��
	CFade2D *m_pFadeHint;			// �q���g�̃t�F�[�h

	// �֐��|�C���^�^���`
	typedef void (CTutorial::*FuncUpdateState)(void);

	// �ÓI�����o�ϐ�
	static FuncUpdateState s_aFuncUpdateState[];	// ��ԍX�V�֐�
	static CTutorial *s_pTutorial;					// ���g�̃|�C���^
};

namespace tutorial
{
void SaveFrag(bool bValue);
bool LoadFrag(void);
}

#endif