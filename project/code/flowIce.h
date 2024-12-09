//*****************************************************
//
// ���X�̏���[flowIce.h]
// Author:���R����
//
//*****************************************************
#ifndef _FLOWICE_H_
#define _FLOWICE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CIce;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CFlowIce : public CObject
{
public:
	CFlowIce(int nPriority = 2);	// �R���X�g���N�^
	~CFlowIce();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	// �ϐ��ݒ�E�擾����
	void AddIceToArray(CIce *pIce);
	vector<CIce*> GetIce(void) { return m_apIce; }	// �X�̎擾
	
	// �ÓI�����o�֐�
	static CFlowIce *Create(void);	// ��������
	static vector<CFlowIce*> GetInstance(void) { return s_vector; }	// �C���X�^���X�擾

private:
	// �����o�֐�
	void CheckInAllIce(void);		// �S�Ă̕X����ʂɓ��������̃`�F�b�N
	void CheckSomeIceStop(void);	// �ǂꂩ�̕X���~�܂��Ă��Ȃ����̃`�F�b�N
	void CollideOtherFlowIce(void);	// ���̗��X�Ƃ̔���
	void StopAllIce(void);			// �S�Ă̕X���~�߂�
	void StopOnTopObject(void);		// ��ɂ���I�u�W�F�N�g���~�߂�
	void DeleteAllIce(void);		// �S�X�̍폜
	void CheckDelete(void);			// �폜�m�F
	void Debug(void);				// �f�o�b�O����

	// �����o�ϐ�
	vector<CIce*> m_apIce;	// �X�̔z��
	float m_fTimerDelete;	// �폜�^�C�}�[
	bool m_bInScrnAllIce;	// �S�Ă̕X���X�N���[���ɉf�����t���O

	// �ÓI�����o�ϐ�
	static vector<CFlowIce*> s_vector;	// �i�[�p�̔z��
};

#endif

