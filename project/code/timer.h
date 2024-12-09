//*****************************************************
//
// �^�C���̏���[timer.h]
// Author:�X��x��
//
//*****************************************************
#ifndef _TIMER_H_
#define _TIMER_H_

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
class CTimer : public CGameObject
{
public:
	// �񋓌^��`
	enum E_Number
	{// �����̎��
		NUMBER_MINUTE = 0,	// ��
		NUMBER_SECOND,	// �b
		NUMBER_MAX
	};

	CTimer();	// �R���X�g���N�^
	~CTimer();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// �ϐ��擾�E�ݒ�֐�
	int GetSecond() { return m_nSecond; }	// �b
	void SetSecond(int nSecond) { m_nSecond = nSecond; }
	void AddSecond(int nSecond) { m_nSecond += nSecond; }
	bool GetFlag() { return m_bStop; }	// ����t���O
	void SetFlag(bool bStop) { m_bStop = bStop; }
	void SetPosition(D3DXVECTOR3 pos) override;	// �ʒu
	void SetScaleNumber(float fScale);	// �����̃X�P�[��
	float GetScaleNumber(void) { return m_fScaleNumber; }
	void SetColor(E_Number number,D3DXCOLOR col);	// �F
	D3DXCOLOR GetColor(E_Number number);

	// �ÓI�����o�֐�
	static CTimer *Create();	// ����
	static void SaveSecond(int nSecond);	// ���ԕۑ�
	static int LoadSecond(void);	// ���ԓǍ�

private:
	// �����o�֐�
	void UpdateNumber();	// �����̍X�V
	void TransformNumber();	// �����̃g�����X�t�H�[���ݒ�

	// �����o�ϐ�
	int m_nSecond;			// ���݂̎���(�b)
	float m_fScaleNumber;	// �����̃X�P�[��
	bool m_bStop;				// �^�C�}�[��~�̃t���O
	vector<CNumber*> m_aNumber;	// �����̔z��
	vector<CUI*> m_aColon;	// �R�����̔z��
};

#endif
