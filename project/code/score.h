//*****************************************************
//
// �X�R�A�̏���[Score.h]
// Author:��؈�^
//
//*****************************************************
#ifndef _SCORE_H_
#define _SCORE_H_

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
class CScore : public CGameObject
{
public:
	CScore();	// �R���X�g���N�^
	~CScore();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void SetData(int nDigit = 6);

	// �ϐ��擾�E�ݒ�֐�
	int GetScore() { return m_nScore; }	// �X�R�A
	void SetScore(int nScore) { m_nScore = nScore; }
	void AddScore(int nScore) { m_nScore += nScore; }
	void SetPosition(D3DXVECTOR3 pos) override;	// �ʒu
	void SetScaleNumber(float fScale);	// �����̃X�P�[��
	float GetScaleNumber(void) { return m_fScaleNumber; }
	void SetColor(D3DXCOLOR col);	// �F

	// �ÓI�����o�֐�
	static CScore* Create();	// ����
	static void SaveScore(int nSecond);	// �X�R�A�ۑ�
	static int LoadScore(void);	// �X�R�A�Ǎ�

private:
	// �����o�֐�
	void UpdateNumber();	// �����̍X�V
	void TransformNumber();	// �����̃g�����X�t�H�[���ݒ�

	// �����o�ϐ�
	int m_nScore;			// ���݂̃X�R�A
	float m_fScaleNumber;	// �����̃X�P�[��
	vector<CNumber*> m_aNumber;	// �����̔z��
};

#endif