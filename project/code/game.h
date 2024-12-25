//*****************************************************
//
// �Q�[������[game.h]
// Author:���R����
//
//*****************************************************
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "scene.h"
#include "timer.h"
#include "score.h"
#include "pause.h"

//*****************************************************
// �O���錾
//*****************************************************
class CGame;
class CPause;
class CGameManager;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGame : public CScene
{
public:
	static constexpr int MAX_TIME = 40;	// �ő厞��

	enum E_State
	{// ���
		STATE_NONE,		// �������Ă��Ȃ����
		STATE_READY,	// �������
		STATE_START,	// �J�n���
		STATE_NORMAL,	// �ʏ��� 
		STATE_RESULT,	// ���U���g���
		STATE_END,		// �I�����
		STATE_MAX
	};
	enum E_GameMode
	{// �Q�[���̃��[�h
		MODE_NONE = 0,	// ���ł��Ȃ����[�h
		MODE_SINGLE,	// �V���O�����[�h
		MODE_MULTI,		// �}���`
		MODE_MAX
	};

	CGame();	// �R���X�g���N�^
	~CGame() {};	// �f�X�g���N�^

	static CGame *GetInstance(void) { return m_pGame; }
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update();
	virtual void Draw();
	static void SetState(E_State state) { m_state = state; }
	static E_State GetState(void) { return m_state; }
	void EnableStop(bool bStop) { m_bStop = bStop; }
	bool GetStop(void) { return m_bStop; }
	void ReleasePause(void) { m_pPause = nullptr; };	// �|�[�Y�̉��
	void CreateScore(void);	// �X�R�A�̐���
	void StartGame(void);	// �Q�[���̊J�n

	// �ϐ��擾�E�ݒ�֐�
	int GetTimeSecond(void) { if (m_pTimer != nullptr) { return m_pTimer->GetSecond(); } return 0; }
	CScore *GetScore(void) { return m_pScore; };	// �X�R�A

private:
	// �����o�֐�
	void UpdateCamera(void);
	void ManageState(void);
	void ToggleStop(void);
	void Debug(void);
	void UpdatePause(void);	// �|�[�Y�̍X�V

	// �����o�ϐ�
	int m_nCntState;					// ��ԑJ�ڃJ�E���^�[
	int m_nTimerCnt;					// �^�C�}�[�p�̃J�E���g
	bool m_bStop;						// ��~���
	CTimer* m_pTimer;					// �^�C�}�[
	CScore* m_pScore;					// �X�R�A
	CPause *m_pPause;					// �|�[�Y�̃|�C���^
	E_GameMode m_GameMode;				// �Q�[�����[�h
	CGameManager *m_pGameManager;		// �Q�[���}�l�[�W���[

	// �ÓI�����o�ϐ�
	static E_State m_state;	// ���
	static CGame *m_pGame;	// ���g�̃|�C���^
};

namespace game
{
void AddScore(int nScore);	// �X�R�A���Z
}

#endif