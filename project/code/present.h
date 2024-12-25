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
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPresent : public CObject
{
public:
	// �\���̒�`
	struct S_InfoPresent
	{// �v���[���g���
		string pathThumnail;	// �T���l�C��
		string pathModel;		// ���f��
		int nID;				// ID
	};

	CPresent(int nPriority = 5);	// �R���X�g���N�^
	~CPresent();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static void Load(void);			// �Ǎ�
	static void Unload(void);		// �j��
	static CPresent *Create(void);	// ��������

private:
	// �ÓI�����o�ϐ�
	static vector<S_InfoPresent*> s_aInfoPresnt;	// �v���[���g���̔z��
};

#endif