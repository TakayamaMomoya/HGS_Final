//*****************************************************
//
// �`���[�g���A���v���C���[�̏���[PlayerTutorial.h]
// Author:���R����
//
//*****************************************************
#ifndef _PlayerTutorial_H_
#define _PlayerTutorial_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "player.h"

//*****************************************************
// �O���錾
//*****************************************************s

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayerTutorial : public CPlayer
{
public:
	CPlayerTutorial(int nPriority = 5);	// �R���X�g���N�^
	~CPlayerTutorial();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CPlayerTutorial *Create(void);	// ��������

private:
	// �����o�֐�

	// �����o�ϐ�
};

#endif