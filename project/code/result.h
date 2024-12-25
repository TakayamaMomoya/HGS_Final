//*****************************************************
//
// ���U���g����[result.h]
// Author:���R����
//
//*****************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "scene.h"
#include "present.h"

//*****************************************************
// �O���錾
//*****************************************************
class CMotion;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CResult : public CScene
{
private:

	// ��l���Ƃ̏��
	struct SCharaInfo
	{
		CMotion* pCharacter;
		CPresent* pPresent;

		// �R���X�g���N�^
		SCharaInfo() : pCharacter(nullptr), pPresent(nullptr) {}
	};

public:
	static constexpr int MAX_TIME = 120;	// �ő厞��

	CResult();	// �R���X�g���N�^
	~CResult() {};	// �f�X�g���N�^

	static CResult* GetInstance(void) { return m_pResult; }
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update();
	virtual void Draw();

private:

	// �����o�ϐ�
	void UpdateCamera(void);
	void MotionSet(void);
	void PursueCamera(void);
	void EndCamera(void);
	void InitCharacter(void);

	// �ÓI�����o�ϐ�
	std::vector<SCharaInfo*>::iterator m_CharacterIt;	// �L�����N�^�[�n���iterator
	std::vector<SCharaInfo*> m_CharacterList;			// �L�����N�^�[�n��񃊃X�g
	std::vector<CPresent::E_Label> m_ClearList;			// �N���A���x�����X�g
	SCharaInfo m_LastInfo;								// ���s�L�����p
	float m_fCnt;			// �L�����N�^�[�J�ڗp�J�E���g
	bool m_bEnd;			// �I���t���O
	int m_nKeyOld;			// �Ō�̃L�����̑O��̃L�[
	D3DXVECTOR3 m_camerastart;	// �J�����̊J�n�n�_
	static CResult* m_pResult;	// ���g�̃|�C���^
};

#endif
