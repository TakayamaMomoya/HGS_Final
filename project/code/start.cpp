//*****************************************************
//
// �X�^�[�g�\���̏���[start.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "start.h"
#include "UI.h"
#include "game.h"
#include "texture.h"
#include "sound.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define CAPTION_WIDTH	(0.3f)	// ���o���̕�
#define CAPTION_HEIGHT	(0.2f)	// ���o���̍���
#define CAPTION_PATH_HAKKEYOI "data\\TEXTURE\\UI\\start00.png"	// �͂����悢�̃p�X
#define CAPTION_PATH_NOKOTTA "data\\TEXTURE\\UI\\start01.png"	// �̂������̃p�X
#define SPEED_HAKKEYOI (0.005f)	// �͂����悢�̃X�s�[�h
#define SPEED_NOKOTTA (0.05f)	// �̂������̃X�s�[�h

#define TIME_HAKKEYOI (1.02f)	// �͂����悢�̎���
#define TIME_NOKOTTA  (0.3f)	// �̂������̎���

#define SPEED_EXTEND_NOKOTTA (1.1f)	// �̂������̂ł����Ȃ銄��

//*****************************************************
// �ÓI�����o�ϐ�
//*****************************************************
CStart *CStart::s_pStart = nullptr;	// ���g�̃|�C���^

//====================================================
// �R���X�g���N�^
//====================================================
CStart::CStart()
{
	m_state = STATE_NONE;
	m_fTimer = 0.0f;
}

//====================================================
// �f�X�g���N�^
//====================================================
CStart::~CStart()
{

}

//====================================================
// ��������
//====================================================
CStart *CStart::Create(void)
{
	if (s_pStart == nullptr)
	{
		s_pStart = new CStart;

		if (s_pStart != nullptr)
		{
			s_pStart->Init();
		}
	}

	return s_pStart;
}

//====================================================
// ����������
//====================================================
HRESULT CStart::Init(void)
{
	m_state = STATE_HAKKEYOI;

	CGame::SetState(CGame::STATE::STATE_START);

	// ���o���̐���
	m_pCaption = CUI::Create();

	if (m_pCaption != nullptr)
	{
		m_pCaption->SetPosition(D3DXVECTOR3(0.5f, 0.4f, 0.0f));

		m_pCaption->SetSize(CAPTION_WIDTH, CAPTION_HEIGHT);

		m_pCaption->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		int nIdxTexture = CTexture::GetInstance()->Regist(CAPTION_PATH_HAKKEYOI);

		m_pCaption->SetIdxTexture(nIdxTexture);

		m_pCaption->SetVtx();
	}

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CStart::Uninit(void)
{
	s_pStart = nullptr;

	if (m_pCaption != nullptr)
	{
		m_pCaption->Uninit();
		m_pCaption = nullptr;
	}

	Release();
}

//====================================================
// �X�V����
//====================================================
void CStart::Update(void)
{
	m_fTimer += SPEED_HAKKEYOI;

	switch (m_state)
	{
	case CStart::STATE_HAKKEYOI:
	{// �s�����x���グ�Ă���
		float fAlpha = easing::OutQuint(m_fTimer);

		universal::LimitValuefloat(&fAlpha, 1.0f, 0.0f);

		if (m_pCaption != nullptr)
		{
			m_pCaption->SetAlpha(fAlpha);

			if (m_fTimer > TIME_HAKKEYOI)
			{// �̂������Ɉڍs
				m_state = STATE::STATE_NOKOTTA;

				// �e�N�X�`���؂�ւ�
				int nIdxTexture = CTexture::GetInstance()->Regist(CAPTION_PATH_NOKOTTA);
				m_pCaption->SetIdxTexture(nIdxTexture);
				m_fTimer = 0.0f;
			}
		}
	}
		break;
	case CStart::STATE_NOKOTTA:
	{// �g�傷��
		if (m_pCaption == nullptr)
			return;

		D3DXVECTOR2 size = m_pCaption->GetSize();

		size *= SPEED_EXTEND_NOKOTTA;

		m_pCaption->SetSize(size.x, size.y);
		m_pCaption->SetVtx();

		float fAlpha = 1.0f - easing::OutQuint(m_fTimer);

		universal::LimitValuefloat(&fAlpha, 1.0f, 0.0f);

		m_pCaption->SetAlpha(fAlpha);

		if (m_fTimer > TIME_NOKOTTA)
		{// �̂������Ɉڍs
			CGame::SetState(CGame::STATE::STATE_NORMAL);

			// BGM�Đ�
			CSound* pSound = CSound::GetInstance();

			if (pSound != nullptr)
			{
				pSound->Play(pSound->LABEL_BGM_GAME01);
				pSound->Play(pSound->LABEL_SE_PAUSE_ENTER01);
			}


			Uninit();
		}
	}
		break;
	default:
		break;
	}
}

//====================================================
// �`�揈��
//====================================================
void CStart::Draw(void)
{

}