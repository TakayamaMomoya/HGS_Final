//*****************************************************
//
// �V���O���Q�[���}�l�[�W���[[gameManagerSingle.h]
// Author:���R����
//
//*****************************************************
#ifndef _GAMEMANAGERSINGLE_H_
#define _GAMEMANAGERSINGLE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "gameManager.h"

//*****************************************************
// �O���錾
//*****************************************************
class CPlayer;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGameManagerSingle : public CGameManager
{
public:
	CGameManagerSingle();	// �R���X�g���N�^
	~CGameManagerSingle() {};	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void EndGame(void) override;	// �Q�[���̏I��

	//�v���C���[�̎擾
	CPlayer* GetPlayer() { return m_pPlayer; }

private:
	// �����o�֐�
	void UpdateStart(void) override;	// �J�n��Ԃ̍X�V
	void UpdateNormal(void) override;	// �ʏ��Ԃ̍X�V
	void ManagePlayer(void);			// �v���C���[�̊Ǘ�
	void DeathPlayer(void);				// �v���C���[�̎��S

	void UpdateResult(void) override;	// ���U���g��Ԃ̍X�V
	void UpdateEnd(void) override;		// �I����Ԃ̍X�V

	// �����o�ϐ�
	CPlayer *m_pPlayer;		// �v���C���[�̃|�C���^
};

#endif