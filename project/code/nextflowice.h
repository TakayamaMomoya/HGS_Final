////*****************************************************
////
//// �X�������UI�̏���[nextflowice.h]
//// Author:��؈�^
////
////*****************************************************
//#ifndef _NEXTFLOWICE_H_
//#define _NEXTFLOWICE_H_
//
////*****************************************************
//// �C���N���[�h
////*****************************************************
//#include "gameObject.h"
//
////*****************************************************
//// �O���錾
////*****************************************************
//class CPolygon2D;
//
////*****************************************************
//// �N���X��`
////*****************************************************
//class CNextFlowIce : public CObject
//{
//public:
//	CNextFlowIce();	// �R���X�g���N�^
//	~CNextFlowIce();	// �f�X�g���N�^
//
//	static CNextFlowIce* Create(void);
//	HRESULT Init(void);
//	void Uninit(void);
//	void Update(void);
//	void Draw(void);
//	static CNextFlowIce* GetInstance(void) { return m_pStageResultUI; }
//
//private:
//
//	// ���U���g�̎��
//	enum RESULT
//	{
//		RESULT_CLEAR = 0,	// �N���A
//		RESULT_FAIL,	// ���s
//		RESULT_MAX
//	};
//
//	enum STATE
//	{
//		STATE_NONE = 0,	// ���ł��Ȃ����
//		STATE_IN,	// �t�F�[�h�C�����
//		STATE_OUT,	// �t�F�[�h�A�E�g���
//		STATE_MAX
//	};
//
//	void ResultState(void); // ���U���gUI�̏��
//	void ResultClear(void); // ���U���g���N���A�̎�
//	void ResultFail(void); // ���U���g�����s�̎�
//	void Fade(RESULT RESULT);
//
//	RESULT m_Result;	// �I������
//	CPolygon2D* m_apResult[RESULT_MAX];	// �X�e�[�W���U���g��2D�I�u�W�F�N�g
//	D3DXVECTOR3 m_aPosDest[RESULT_MAX];	// �ڕW�̈ʒu
//	STATE m_state;	// ���
//	static CNextFlowIce* m_pStageResultUI;	// ���g�̃|�C���^
//	bool m_bSound;
//	int nCountMove;
//};
//
//#endif