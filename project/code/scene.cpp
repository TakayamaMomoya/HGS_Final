//*****************************************************
//
// �V�[������[scene.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "scene.h"
#include "game.h"
#include "logo.h"
#include "title.h"
#include "tutorial.h"
#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "skybox.h"
#include "sound.h"
#include "inputManager.h"
#include "slow.h"
#include "texture.h"
#include "objectX.h"
#include "meshcylinder.h"
#include "polygon3D.h"
#include "MyEffekseer.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int NUM_LIGHT = 3;	// ���C�g�̐�
const D3DXCOLOR COL_LIGHT_DEFAULT = { 0.9f,0.9f,0.9f,1.0f };	// ���C�g�̃f�t�H���g�F
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CScene::CScene()
{
	m_nTimerTrans = 0;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CScene::~CScene()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CScene::Init(void)
{
	// �R�V�����_�[�̐���
	CMeshCylinder* pCylinder = CMeshCylinder::Create();

	if (pCylinder)
	{
		int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\BG\\mountain000.png");
		pCylinder->SetIdxTexture(nIdx);
		pCylinder->SetRadius(6000.0f);
		pCylinder->SetHeight(5000.0f);
		pCylinder->SetVtx();
		pCylinder->EnableLighting(false);
	}

	// �X���[�Ǘ��̐���
	CSlow::Create();

	// ���C�g�̐���
	CreateLight();

	// �X�J�C�{�b�N�X�̐���
	CSkybox::Create();

	return S_OK;
}

//=====================================================
// ���C�g�̐���
//=====================================================
void CScene::CreateLight(void)
{
	D3DXVECTOR3 aDir[NUM_LIGHT] =
	{
		{ -1.4f, 0.24f, -2.21f, },
		{ 1.42f, -0.8f, 0.08f },
		{ -0.29f, -0.8f, 0.55f }
	};

	for (int i = 0; i < NUM_LIGHT; i++)
	{
		CLight *pLight = CLight::Create();

		if (pLight == nullptr)
			continue;

		D3DLIGHT9 infoLight = pLight->GetLightInfo();

		infoLight.Type = D3DLIGHT_DIRECTIONAL;
		infoLight.Diffuse = COL_LIGHT_DEFAULT;

		D3DXVECTOR3 vecDir = aDir[i];
		D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g�����K��
		infoLight.Direction = vecDir;

		pLight->SetLightInfo(infoLight);
	}
}

//=====================================================
// �I������
//=====================================================
void CScene::Uninit(void)
{
	CSound* pSound = CSound::GetInstance();

	if (pSound != nullptr)
		pSound->Stop();

	CLight::ReleaseAll();

	CInputManager::ReleaseAll();

	// �S�G�t�F�N�g�̉��
	CMyEffekseer *pMyEffekseer = CMyEffekseer::GetInstance();

	if (pMyEffekseer != nullptr)
		pMyEffekseer->StopAllEffect();
}

//=====================================================
// �X�V����
//=====================================================
void CScene::Update(void)
{
	// �����_���[�̎擾
	CRenderer *pRenderer = CRenderer::GetInstance();
	if (pRenderer != nullptr)
	{
		// �����_���[�̍X�V
		pRenderer->Update();
	}

	// �J�����̎擾
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera != nullptr)
	{
		// �J�����̍X�V
		pCamera->Update();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CScene::Draw(void)
{

}

//=====================================================
// �V�[���̐�������
//=====================================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = nullptr;

	switch (mode)
	{
	case CScene::MODE_LOGO:

		pScene = new CLogo;

		break;
	case CScene::MODE_TITLE:

		pScene = new CTitle;

		break;
	case CScene::MODE_TUTORIAL:

		pScene = new CTutorial;

		break;
	case CScene::MODE_GAME:

		pScene = new CGame;

		break;
	default:

		pScene = new CGame;

		break;
	}

	if (pScene != nullptr)
	{// �V�[������
		pScene->Init();
	}

	return pScene;
}