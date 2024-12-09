//*****************************************************
//
// �X�J�C�{�b�N�X�̏���[skybox.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "skybox.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float SPEED_ROT = 0.0003f;	// ��鑬�x
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CSkybox *CSkybox::s_pSkybox = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CSkybox::CSkybox(int nPriority) : CObjectX(nPriority), m_bFollowPlayer(false)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CSkybox::~CSkybox()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CSkybox::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	// ���f���̓Ǎ�
	int nIdx = CModel::Load("data\\MODEL\\skybox\\sky00.x");
	BindModel(nIdx);

	EnableLighting(true);
	EnableFog(false);

	m_bFollowPlayer = true;

	s_pSkybox = this;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CSkybox::Uninit(void)
{
	s_pSkybox = nullptr;

	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CSkybox::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();

	Rotate(D3DXVECTOR3(0.0f, SPEED_ROT, 0.0f));
}

//=====================================================
// �`�揈��
//=====================================================
void CSkybox::Draw(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CRenderer::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �p���N���X�̕`��
	CObjectX::Draw();

	// ���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=====================================================
// ��������
//=====================================================
CSkybox *CSkybox::Create()
{
	CSkybox *pSkybox = nullptr;

	if (pSkybox == nullptr)
	{
		pSkybox = new CSkybox;

		if (pSkybox != nullptr)
		{
			// ������
			pSkybox->Init();
		}
	}

	return pSkybox;
}