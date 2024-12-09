//*****************************************************
//
// �^�C�g������[title.h]
// Author:��؈�^
//
//*****************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "scene.h"

//*****************************************************
// �O���錾
//*****************************************************
class CMenu;
class CUI;
class CTitleBehavior;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CTitle : public CScene
{
public:
	enum STATE
	{
		STATE_NONE = 0,	// �������ĂȂ����
		STATE_OUT,		// �t�F�[�h�A�E�g���
		START_MAX
	};
	
	enum TITLESTATE
	{
		TITLESTATE_ICEFLOW = 0,	// �X������Ă�����
		TITLESTATE_LOGO,		// ���S���������
		TITLESTATE_PICKAXE,		// ��͂����
		TITLESTATE_MAX
	};

	enum TITLE_UI
	{
		TITLE_UI_LEFT = 0,	// ����
		TITLE_UI_RIGHT,	// �E��
		TITLE_UI_ICEBLOCK,	// �X�u���b�N����
		TITLE_UI_ICE,	// �X
		TITLE_UI_PENGUIN,	// �y���M��
		TITLE_UI_LOGO,	// ���S
		TITLE_UI_PICKAXE,	// ��͂�
		TITLE_UI_FLASH,	// �t���b�V��
		TITLE_UI_MAX
	};

	CTitle();	// �R���X�g���N�^
	~CTitle();	// �f�X�g���N�^

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	STATE GetState(void) { return m_State; }

private:
	void Input(void);
	void Fade(void);
	void IceFlowState(void);
	void IceConnect(D3DXVECTOR3 *left, D3DXVECTOR3 *right);
	void LogoState(void);
	void PickaxeState(void);

	int m_nCntState;	// �J�E���g�̏��
	int m_nCntMove;	// UI�̈ړ��J�E���g
	int m_nCntFade;	// �J�E���g�̏��
	int m_nStateLogo;	// �X�^�[�g���S�J�E���g
	bool m_bFade; // �t�F�C�h
	bool m_bMove; // �ړ�
	STATE m_State;				// ���
	TITLESTATE m_TitleState;	// �^�C�g����ԊǗ�
	TITLE_UI m_Title_UI;	// �^�C�g��UI
	CUI* m_apMenu_UI;	// ���j���[UI
	CUI *m_apTitle_UI[TITLE_UI_MAX];	// �^�C�g��UI
	D3DXVECTOR3 m_aPosDest[TITLE_UI_MAX];	// �ڕW�̈ʒu
};

#endif