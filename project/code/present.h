//*****************************************************
//
// �v���[���g�̏���[present.cpp]
// Author:���R����
//
//*****************************************************
#ifndef _PRESENT_H_
#define _PRESENT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPresent : public CMotion
{
public:
	// �\���̒�`
	struct S_InfoPresent
	{// �v���[���g���
		string pathThumnail;	// �T���l�C��
		string pathModel;		// ���f��
		int nID;				// ID
	};
	// �񋓌^��`
	enum E_Label
	{// ���x���̎��
		LABEL_BLUE = 0,		// ��
		LABEL_GREEN,		// ��
		LABEL_PUPLE,		// ��
		LABEL_YELLOW,		// ��
		LABEL_MAX,
	};

	CPresent(int nPriority = 5);	// �R���X�g���N�^
	~CPresent();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	E_Label GetLabel(void) { return m_label; }	// ���x��

	// �ÓI�����o�֐�
	static void Load(void);																	// �Ǎ�
	static void CPresent::LoadInfo(std::ifstream& file, string str, S_InfoPresent *pInfo);
	static void Unload(void);																// �j��
	static CPresent *Create(E_Label label = LABEL_BLUE);									// ��������
	static vector<S_InfoPresent*> GetInfoPresent(void) { return s_aInfoPresnt; }			// �v���[���g���̎擾

private:
	// �����o�ϐ�
	E_Label m_label;	// ���x��

	// �ÓI�����o�ϐ�
	static vector<S_InfoPresent*> s_aInfoPresnt;	// �v���[���g���̔z��
};

#endif