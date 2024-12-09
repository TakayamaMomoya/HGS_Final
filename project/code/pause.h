//*****************************************************
//
// �|�[�Y�̏���[pause.h]
// Author:���R����
//
//*****************************************************

#ifndef _PAUSE_H_
#define _PAUSE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;

//*****************************************************
// �N���X��`
//*****************************************************
class CPause : CObject
{
public:
	enum STATE
	{
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_IN,	// �t�F�[�h�C�����
		STATE_OUT,	// �t�F�[�h�A�E�g���
		STATE_MAX
	};

	CPause();	// �R���X�g���N�^
	~CPause();	// �f�X�g���N�^

	static CPause *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	enum MENU
	{// ���ڂ̎��
		MENU_RESUME = 0,	// ����
		MENU_RESTART,	// ���X�^�[�g
		MENU_QUIT,	// �^�C�g���ɖ߂�
		MENU_PAUSE,	// �|�[�Y
		MENU_MAX
	};

	void ManageState(void);
	void ManageBg(void);
	void Input(void);
	void Fade(MENU menu);
	void OffPosition(void);
	void SelectMove(void);

	MENU m_menu;						// �I������
	CUI *m_apMenu[MENU_MAX];			// ���j���[���ڂ̂QD�I�u�W�F�N�g
	CUI *m_pBg;							// �w�i�QD�I�u�W�F�N�g
	D3DXVECTOR3 m_aPosDest[MENU_MAX];	// �ڕW�̈ʒu
	STATE m_state;						// ���
	bool m_bSound;
	int nCountMove;
};

#endif