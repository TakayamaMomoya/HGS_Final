//*****************************************************
//
// 3D�t�F�[�h�̏���[fade3D.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "fade3D.h"
#include "polygon3D.h"
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
CFade3D::FuncUpdateState CFade3D::s_aFuncUpdateState[] =
{
	nullptr,			// �������Ă��Ȃ���Ԃ̍X�V
};

//====================================================
// �R���X�g���N�^
//====================================================
CFade3D::CFade3D() : m_state(E_State::STATE_NONE), m_fTimer(0.0f), m_bBouceIn(false), m_bBouceOut(false), m_pathNext("")
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CFade3D::~CFade3D()
{

}

//====================================================
// ��������
//====================================================
CFade3D *CFade3D::Create(CPolygon3D *pPolygon, float fTimeMax)
{
	CFade3D *pFade3D = nullptr;

	pFade3D = new CFade3D;

	if (pFade3D != nullptr)
	{
		pFade3D->m_pPoygon = pPolygon;
		pFade3D->m_fTimeMax = fTimeMax;
		pFade3D->Init();
	}

	return pFade3D;
}

//====================================================
// ����������
//====================================================
HRESULT CFade3D::Init(void)
{
	return S_OK;
}

//====================================================
// �I������
//====================================================
void CFade3D::Uninit(void)
{
	Release();
}

//====================================================
// �X�V����
//====================================================
void CFade3D::Update(void)
{
	switch (m_state)
	{
	case CFade3D::STATE_IN:
		m_fTimer += CManager::GetDeltaTime();

		if (m_fTimer > m_fTimeMax)
		{
			if (m_bBouceIn)
				m_state = CFade3D::STATE_OUT;
			else
				m_state = CFade3D::STATE_NONE;
		}

		
		break;
	case CFade3D::STATE_OUT:
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

				m_state = CFade3D::STATE_IN;
			}
			else
				m_state = CFade3D::STATE_NONE;
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
void CFade3D::InitByState(E_State state)
{
	switch (state)
	{
	case CFade3D::STATE_IN:
		m_fTimer = 0.0f;
		break;
	case CFade3D::STATE_OUT:
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
void CFade3D::Draw(void)
{

}