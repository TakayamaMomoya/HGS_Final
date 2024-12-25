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
#include "present.h"

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
	bool CheckCover(D3DXVECTOR3 pos);	// ���`�F�b�N
	CPresent* GetPresent(void) { return m_pPresent; }	// �v���[���g
	void SetPresent(CPresent* pPresent);

	// �ÓI�����o�֐�
	static void SetHouseRandom(void);			// �����_���ɉƂ�z�u���鏈��
	static void BindPresent(void);				// �v���[���g�̊���U��
	static CHouse *Create(void);				// ��������
	static CListManager<CHouse>* GetList(void); // ���X�g�擾

private:
	// �ÓI�����o�ϐ�
	static CListManager<CHouse>* m_pList;		// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CHouse>::AIterator m_iterator; // �C�e���[�^�[
	CPresent* m_pPresent;						// �v���[���g
};

namespace house
{
void GetTwoLabel(CPresent::E_Label &labelFirst, CPresent::E_Label &labelSecond);
}

#endif