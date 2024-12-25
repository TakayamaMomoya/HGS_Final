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
class CUI;

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
	bool CheckCover(D3DXVECTOR3 pos);					// ���`�F�b�N
	CPresent* GetPresent(void) { return m_pPresent; }	// �v���[���g
	void SetPresent(CPresent* pPresent);
	CPresent::E_Label GetLabelWant(void) { return m_labelWant; }	// �~���Ă��郉�x��
	void SetLabelWant(CPresent::E_Label label) { m_labelWant = label; }

	bool IsClear() { return m_bClear; }	// �N���A�t���O

	// �ÓI�����o�֐�
	static void SetHouseRandom(void);			// �����_���ɉƂ�z�u���鏈��
	static void BindPresent(void);				// �v���[���g�̊���U��
	static CHouse *Create(void);				// ��������
	static CListManager<CHouse>* GetList(void); // ���X�g�擾
	static void SetResultLabel(void);			// ���U���g�̃��x���ݒ�
	static vector<CPresent::E_Label> GetLabelResult(void) { return s_aLabelResult; }

private:
	// �ÓI�����o�ϐ�
	static CListManager<CHouse>* m_pList;				// �I�u�W�F�N�g���X�g
	static vector<CPresent::E_Label> s_aLabelResult;	// ���U���g�̃��x��

	// �����o�ϐ�
	CListManager<CHouse>::AIterator m_iterator; // �C�e���[�^�[
	CPresent* m_pPresent;						// �v���[���g
	CPresent::E_Label m_labelWant;				// �~���Ă��郉�x��
	CUI* m_pUI;									// �~���Ă��郉�x���̉摜
	bool m_bClear;								// �v���[���g�̈�v�t���O
};

namespace house
{
void GetTwoLabel(CPresent::E_Label &labelFirst, CPresent::E_Label &labelSecond);
}

#endif