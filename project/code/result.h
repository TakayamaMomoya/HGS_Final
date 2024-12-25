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
class CUI;
class CNumber;

namespace Result_Rank
{
	const int NUM = 3;
}

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

	enum E_State
	{
		STATE_NONE = 0,			// �������ĂȂ����
		STATE_FADE,				// �t�F�[�h���
		STATE_APPERCAPTION,		// ���o���o�����
		STATE_ENDAPPERCAPTION,	// ���o���o���I�����
		STATE_END,				// �I�����
		STATE_MAX
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
	void Ui_Init(void);

	void Create2D(void);		// 2DUI�̐���
	void CreateCaption(void);	// ���o���̐���
	void CreateBg(void);		// �w�i�̐���
	void CreateMyResult(void);	// ���g�̃��U���g�̐���
	void CreateRank(void);		// �����L���O�̐���

	void UpdateFade(void);			// �t�F�[�h��Ԃ̍X�V
	void UpdateApperCaption(void);	// �L���v�V�����o����Ԃ̍X�V
	void Input(void);

	// ��ԍX�V�̊֐��|�C���^�^�G�C���A�X��`
	typedef void (CResult::* FuncUpdateState)(void);

	// �ÓI�����o�ϐ�
	static FuncUpdateState s_aFuncUpdateState[];	// ��ԍX�V�֐�

	// �ÓI�����o�ϐ�
	static CResult* m_pResult;	// ���g�̃|�C���^

	// �����o�ϐ�
	std::vector<SCharaInfo*>::iterator m_CharacterIt;	// �L�����N�^�[�n���iterator
	std::vector<SCharaInfo*> m_CharacterList;			// �L�����N�^�[�n��񃊃X�g
	std::vector<CPresent::E_Label> m_ClearList;			// �N���A���x�����X�g
	SCharaInfo m_LastInfo;								// ���s�L�����p
	float m_fCnt;			// �L�����N�^�[�J�ڗp�J�E���g
	bool m_bEnd;			// �I���t���O
	int m_nKeyOld;			// �Ō�̃L�����̑O��̃L�[
	D3DXVECTOR3 m_camerastart;	// �J�����̊J�n�n�_
	float m_fTimer;	// �^�C�}�[
	E_State m_state;		// ���

	// UI�p�ϐ�
	CUI* m_pBg;			// �w�i�̃|�C���^
	CUI* m_pCaption;	// ���o���̃|�C���^
	CUI* m_pMyResult;	// ���o���̃|�C���^
	CUI* m_pRank;		// ���o���̃|�C���^
	CNumber* m_pMyScore;
	CUI* m_apRank[Result_Rank::NUM];	// ���o���̃|�C���^
	CNumber* m_apRankScore[Result_Rank::NUM];
	std::vector<int> m_aRankScore;
};

#endif
