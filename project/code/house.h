//*****************************************************
//
// �Ƃ̏���[house.cpp]
// Author:���R����
//
//*****************************************************
#ifndef _HOUSE_H_
#define _HOUSE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �O���錾
//*****************************************************

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CHouse : public CObjectX
{
public:
	CHouse(int nPriority = 5);	// �R���X�g���N�^
	~CHouse();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CHouse *Create(void);	// ��������
	static CListManager<CHouse>* GetList(void); // ���X�g�擾

private:

	// �ÓI�����o�ϐ�
	static CListManager<CHouse>* m_pList; // �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CHouse>::AIterator m_iterator; // �C�e���[�^�[

};

#endif