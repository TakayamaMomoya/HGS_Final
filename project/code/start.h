//*****************************************************
//
// �X�^�[�g�\���̏���[start.h]
// Author:���R����
//
//*****************************************************
#ifndef _START_H_
#define _START_H_

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
class CStart : CObject
{
public:
	CStart();	// �R���X�g���N�^
	~CStart();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CStart *Create(void);
	static CStart *GetInstance(void) { return s_pStart; }

private:
	enum STATE
	{// ���
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_HAKKEYOI,	// �͂����悢
		STATE_NOKOTTA,	// �̂�����
		STATE_MAX
	};

	// �����o�֐�
	STATE m_state;	// ���

	// �����o�ϐ�
	CUI *m_pCaption;	// ���o���̃|�C���^
	float m_fTimer;	// �^�C�}�[

	// �ÓI�����o�֐�
	static CStart *s_pStart;	// ���g�̃|�C���^
};

#endif