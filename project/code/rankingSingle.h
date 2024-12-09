//*****************************************************
//
// �V���O���̃����L���O����[rankingSingle.h]
// Author:���R����
//
//*****************************************************
#ifndef _RESULTSINGLELOSE_H_
#define _RESULTSINGLELOSE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "resultSingle.h"

//*****************************************************
// �O���錾
//*****************************************************

//*****************************************************
// �N���X��`
//*****************************************************
class CRankingSingle : public CObject
{
public:
	// �\���̒�`
	struct S_InfoRank
	{// �����N���
		int nScore;		// �X�R�A
		int nTimePeck;	// �˂�����
	};

	CRankingSingle();	// �R���X�g���N�^
	~CRankingSingle();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);
	void Save(void);
	void Reset(void);
	void ReleaseArray(void);

	// �ϐ��擾�E�ݒ�֐�
	vector<S_InfoRank*> GetRank(void) { return m_apRank; }	// �����N���z��

	// �ÓI�����o�֐�
	static CRankingSingle *Create(string pathSave = "data\\BYNARY\\ranking00.bin");	// ��������

private:
	string m_pathSave;	// �ۑ��p�X
	vector<S_InfoRank*> m_apRank;	// �����N���z��
};

#endif