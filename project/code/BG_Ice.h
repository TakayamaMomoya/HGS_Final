//*****************************************************
//
// �w�i�X�̏���[BG_Ice.h]
// Author:����F�M
//
//*****************************************************
#ifndef _BGICE_H_
#define _BGICE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �N���X��`
//*****************************************************
class CBgIce : public CObjectX
{
public:
	CBgIce();	// �R���X�g���N�^
	~CBgIce();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CBgIce* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type);
	static void Load(char* pPath);

private:
	// �񋓌^��`
	enum E_State
	{//�w�i�X�̏��
		STATE_FLOW = 0,
		STATE_SINK,
		STATE_MAX
	};

	// �����o�֐�
	void Move(void);		// �ړ�����
	void Flow(void);		// �C�ʂɉ��킹�鏈��
	void RippleCheck(void);	// �g����o�����̃`�F�b�N
	void CollideIce(void);	// ����X�Ƃ̔���
	void StartSink(void);	// ���ݎn�߂鏈��

	// �����o�ϐ�
	E_State m_state;		// ��ԕ����ϐ�
	float fSpeedGravity;	// ����ł������x
	float m_fSpeed;			// �ړ����x
	int m_nRippleCount;		// �g��o���J�E���^
	bool m_bInscreen;		// ��ʓ��ɓ��������`�F�b�N����ϐ�
	int m_nOutScreen;		//�X�N���[���O�ɂ��鎞��
};

//*****************************************************
// �萔��`
//*****************************************************
namespace bgice
{
	const int BGICE_MODEL = 3;	// �w�i�̕X����
	const int RIPPLE_DEFAULT = 150;	// �g��o���̊�{����
	const int RIPPLE_DEGREE = 90;	// �g��o�����Ԃ̂Ԃꕝ
}

#endif
