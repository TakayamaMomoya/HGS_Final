//*****************************************************
//
// �t�F�[�h����[fade.h]
// Author:���R����
//
//*****************************************************

#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "polygon2D.h"
#include "scene.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CFade
{
public:
	typedef enum
	{//�t�F�[�h�̏��
		FADE_NONE = 0,				//�������Ă��Ȃ����
		FADE_IN,					//�t�F�[�h�C�����
		FADE_OUT,					//�t�F�[�h�A�E�g���
		FADE_MAX
	}FADE;
	typedef enum
	{// ���[�h
		MODE_NORMAL = 0,	// �ʏ�
		MODE_WHITEOUT,	// �z���C�g�A�E�g
		MODE_MAX
	}MODE;

	CFade();	// �R���X�g���N�^
	~CFade();	// �f�X�g���N�^
	
	static CFade *Create(void);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void SetFade(CScene::MODE modeNext,bool bTrans = true);
	FADE GetState(void);
	void SetState(FADE state) { m_fade = state; }
	bool IsTrans(void) { return m_bTrans; }
	void SetIsTrans(bool trans) { m_bTrans = trans; }
	CScene::MODE GetModeNext(void) { return m_modeNext; }
	void SetModeNext(CScene::MODE modeNext) { m_modeNext = modeNext; }
	void SetColor(D3DXCOLOR col) { m_col = col; }
	static CFade *GetInstance(void) { return m_pFade; }

private:
	bool m_bTrans;	// �J�ڂ��邩�ǂ���
	FADE m_fade;	//�t�F�[�h�̏��
	CScene::MODE m_modeNext;	//���̉��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	D3DXCOLOR m_col;	// �F
	static CFade *m_pFade;	// ���g�̃|�C���^
};

#endif
