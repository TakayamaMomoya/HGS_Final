//*****************************************************
//
// 2D�t�F�[�h�̏���[fade2D.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "fade2D.h"
#include "polygon2D.h"
#include "manager.h"
#include "texture.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{

}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CFade2D::FuncUpdateState CFade2D::s_aFuncUpdateState[] =
{
	nullptr,			// �������Ă��Ȃ���Ԃ̍X�V
};

//====================================================
// �R���X�g���N�^
//====================================================
CFade2D::CFade2D() : m_state(E_State::STATE_NONE), m_fTimer(0.0f), m_bBouceIn(false), m_bBouceOut(false), m_pathNext(""), m_sizeNext()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CFade2D::~CFade2D()
{

}

//====================================================
// ��������
//====================================================
CFade2D *CFade2D::Create(CPolygon2D *pPolygon, float fTimeMax)
{
	CFade2D *pFade2D = nullptr;

	pFade2D = new CFade2D;

	if (pFade2D != nullptr)
	{
		pFade2D->m_pPoygon = pPolygon;
		pFade2D->m_fTimeMax = fTimeMax;
		pFade2D->Init();
	}

	return pFade2D;
}

//====================================================
// ����������
//====================================================
HRESULT CFade2D::Init(void)
{
	// ���̃T�C�Y�𓯂��ɂ���
	m_sizeNext = m_pPoygon->GetSize();

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CFade2D::Uninit(void)
{
	Release();
}

//====================================================
// �X�V����
//====================================================
void CFade2D::Update(void)
{
	switch (m_state)
	{
	case CFade2D::STATE_IN:
		m_fTimer += CManager::GetDeltaTime();

		if (m_fTimer > m_fTimeMax)
		{
			if (m_bBouceIn)
				m_state = CFade2D::STATE_OUT;
			else
				m_state = CFade2D::STATE_NONE;
		}

		
		break;
	case CFade2D::STATE_OUT:
		m_fTimer -= CManager::GetDeltaTime();
		
		if (m_fTimer < 0.0f)
		{
			if (m_bBouceOut)
			{
				if (m_pathNext != "")
				{// ���̃e�N�X�`����\��
					int nIdxTexture = Texture::GetIdx(&m_pathNext[0]);
					m_pPoygon->SetIdxTexture(nIdxTexture);
				}

				m_pPoygon->SetSize(m_sizeNext.x, m_sizeNext.y);
				m_pPoygon->SetVtx();

				m_state = CFade2D::STATE_IN;
			}
			else
				m_state = CFade2D::STATE_NONE;
		}
		break;
	default:
		break;
	}

	universal::LimitValuefloat(&m_fTimer, m_fTimeMax, 0.0f);

	float fRate = easing::EaseInOutExpo(m_fTimer);

	// �F��ݒ�
	if (m_pPoygon != nullptr)
		m_pPoygon->SetAlpha(fRate);
}

//====================================================
// ��Ԃɂ�鏉����
//====================================================
void CFade2D::InitByState(E_State state)
{
	switch (state)
	{
	case CFade2D::STATE_IN:
		m_fTimer = 0.0f;
		break;
	case CFade2D::STATE_OUT:
		m_fTimer = m_fTimeMax;
		break;
	default:
		break;
	}

	SetState(state);
}

//====================================================
// �`�揈��
//====================================================
void CFade2D::Draw(void)
{

}