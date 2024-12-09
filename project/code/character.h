//*****************************************************
//
// �L�����N�^�[�̏���[character.h]
// Author:���R����
//
//*****************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************
class CShadow;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CCharacter : public CMotion
{
public:
	CCharacter(int nPriority = 5);	// �R���X�g���N�^
	~CCharacter();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ϐ��擾�E�ݒ�֐�
	void SetMove(D3DXVECTOR3 move) { m_move = move; }		// �ړ���
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetDecMove(float fDec) { m_fDecMove = fDec; }		// �ړ������W��
	float GetDecMove(void) { return m_fDecMove; }
	void SetRotDest(float fRot) { m_fRotDest = fRot; }		// �ڕW�̌���
	float GetRotDest(void) { return m_fRotDest; }
	void SetFactRot(float fFact) { m_fFactRot = fFact; }	// ��]�W��
	float GetFactRot(void) { return m_fFactRot; }
	void SetShadowPos(D3DXVECTOR3 pos);						// �e�̈ʒu
	
private:
	// �����o�֐�
	void DecreaseMove(void);	// �ړ��ʂ̌���
	void FactingRot(void);		// �����̕␳

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���
	float m_fDecMove;			// �ړ��ʂ̌����W��
	float m_fRotDest;			// �ڕW�̌���
	float m_fFactRot;			// ��]�W��
	CShadow *m_pShadow;			// �e�̃|�C���^
};

#endif