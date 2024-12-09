//*****************************************************
//
// �Q�[���}�l�[�W���[[gameManager.h]
// Author:���R����
//
//*****************************************************
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"
#include "game.h"

//*****************************************************
// �O���錾
//*****************************************************
class CTimer;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGameManager : public CObject
{
public:
	CGameManager();	// �R���X�g���N�^
	~CGameManager() {};	// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void UpdateStart(void);		// �J�n��Ԃ̍X�V
	virtual void UpdateNormal(void);	// �ʏ��Ԃ̍X�V
	virtual void UpdateResult(void);	// ���U���g��Ԃ̍X�V
	virtual void UpdateEnd(void);		// �I����Ԃ̍X�V
	virtual void EndGame(void) = 0;		// �Q�[���̏I��

	// �ϐ��擾�E�ݒ�֐�

	// �ÓI�����o�֐�
	static CGameManager *Create(CGame::E_GameMode mode);	// ��������

private:
	// �����o�֐�
	void ManageGameState(void);	// �Q�[���̏�ԊǗ�

	// �����o�ϐ�
	int m_nCounterSoundSea;	// �Â��ȊC�̉��𗬂��p�̃J�E���^

	// �ÓI�����o�ϐ�
};

#endif