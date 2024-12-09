//*****************************************************
//
// 2D�t�F�[�h�̏���[fade2D.h]
// Author:���R����
//
//*****************************************************
#ifndef _FADE2D_H_
#define _FADE2D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CPolygon2D;

//*****************************************************
// �N���X��`
//*****************************************************
class CFade2D : public CObject
{
public:
	// �񋓌^��`
	enum E_State
	{// ���
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_IN,		// �C�����
		STATE_OUT,		// �A�E�g���
		STATE_MAX
	};

	CFade2D();	// �R���X�g���N�^
	~CFade2D();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void InitByState(E_State state);	// ��Ԃł̏�����

	// �ϐ��擾�E�ݒ�֐�
	void SetTimeMax(float fTime) { m_fTimeMax = fTime; }	// �ő厞��
	float GetTime(void) { return m_fTimeMax; }
	void SetState(E_State state) { m_state = state; }	// ���
	E_State GetState(void) { return m_state; }
	void EnableBouceIn(bool bValue) { m_bBouceIn = bValue; }
	void EnableBouceOut(bool bValue) { m_bBouceOut = bValue; }
	void SetPathNext(string sValue) { m_pathNext = sValue; }	// ���̃e�N�X�`���p�X
	void SetSizeNext(D3DXVECTOR2 size) { m_sizeNext = size; }	// ���̃T�C�Y

	// �ÓI�����o�֐�
	static CFade2D *Create(CPolygon2D *pPolygon,float fTimeMax = 4.0f);
private:
	// �����o�ϐ�
	E_State m_state;		// ���
	float m_fTimer;			// �^�C�}�[
	float m_fTimeMax;		// �ő厞��
	CPolygon2D *m_pPoygon;	// �|���S���̃|�C���^
	bool m_bBouceIn;		// �C����Ԃ̃o�E���X
	bool m_bBouceOut;		// �A�E�g��Ԃ̃o�E���X
	string m_pathNext;		// ���̃e�N�X�`���p�X
	D3DXVECTOR2 m_sizeNext;	// ���̃T�C�Y

	// ��ԍX�V�̊֐��|�C���^�^�G�C���A�X��`
	typedef void (CFade2D::*FuncUpdateState)(void);

	// �ÓI�����o�ϐ�
	static FuncUpdateState s_aFuncUpdateState[];	// ��ԍX�V�֐�
};

#endif