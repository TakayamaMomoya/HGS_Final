//*****************************************************
//
// 2D�I�u�W�F�N�g[object2D.h]
// Author:���R����
//
//*****************************************************
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "gameObject.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CObject2D	: public CGameObject
{
public:
	CObject2D(int nPriority = 6);	// �R���X�g���N�^
	~CObject2D();	//	�f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void);	// ������
	virtual void Uninit(void);	// �I��
	virtual void Update(void);	// �X�V
	virtual void Draw(void);	// �`��
private:
};

#endif