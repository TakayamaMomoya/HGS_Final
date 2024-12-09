//*****************************************************
//
// �Q�[���X�^�[�g���mUI����[UI_ready.h]
// Author:����F�M
//
//*****************************************************
#ifndef _UI_READY_H_
#define _UI_READY_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "gameObject.h"
#include "number.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CUIready : public CGameObject
{
public:
	// �񋓌^��`
	enum E_Number
	{// �����̎��
		NUMBER_SECOND = 0,	// �b
		NUMBER_MAX
	};

	// �񋓌^��`
	enum STATE
	{// �e�N�X�`���̎��
		STATE_NUMBER = 0,	//�������
		STATE_GO,			//GO�w��
		STATE_MAX
	};

	CUIready();	// �R���X�g���N�^
	~CUIready();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CUIready* Create();	// ����

	// �ϐ��擾�E�ݒ�֐�
	int GetSecond() { return m_nSecond; }	// �b
	void SetSecond(int nSecond) { m_nSecond = nSecond; }
	void AddSecond(int nSecond) { m_nSecond += nSecond; }
	void SetPosition(D3DXVECTOR3 pos) override;	// �ʒu

private:
	// �����o�֐�
	void UpdateNumber(void);		// �����̍X�V
	void TransformNumber(void);		// �����̃g�����X�t�H�[���ݒ�
	void StartGame(void);			// �Q�[���̊J�n

	// �����o�ϐ�
	int m_nSecond;					// ���݂̎���(�b)
	vector<CNumber*> m_aNumber;		// �����̔z��
	int m_nFrame;					// �t���[���v�Z
	STATE m_state;					// ��ԕϐ�
	CUI* m_Go;						// GO�̕ϐ�
	int m_nStateCnt;				// ��ԑJ�ڃJ�E���g
	float m_fsize;					// �T�C�Y�ϐ�
	float m_fmove;					// �ړ���
};

#endif
