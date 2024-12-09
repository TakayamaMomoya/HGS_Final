//===========================================================
//
// �}�C�G�t�F�N�V�A[MyEffekseer.cpp]
// Author : ���R����
//
//===========================================================

//***********************************************************
// �C���N���[�h
//***********************************************************
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>
#include <locale>
#include <string>

#include "manager.h"
#include "renderer.h"
#include "MyEffekseer.h"
#include "camera.h"
#include "debugproc.h"
#include "game.h"

//***********************************************************
// �ÓI�����o�ϐ��錾
//***********************************************************
const char* CMyEffekseer::m_apEfkName[CMyEffekseer::TYPE_MAX] =		// �G�t�F�N�g�̃p�X
{
	"",												// �Ȃ���Ȃ�
	"data\\EFFEKSEER\\Effect\\peckWave.efkefc",		// �����̔g��
	"data\\EFFEKSEER\\Effect\\splashwater.efkefc",	// �����g
	"data\\EFFEKSEER\\Effect\\ripplesring.efkefc",	// �g��
	"data\\EFFEKSEER\\Effect\\bearstep.efkefc",		// �V���N�}�̑���
	"data\\EFFEKSEER\\Effect\\blizzard.efkefc",		// ����
	"data\\EFFEKSEER\\Effect\\icebreak.efkefc",		// �X�̔j��
	"data\\EFFEKSEER\\Effect\\jump.efkefc",			// �W�����v
	"data\\EFFEKSEER\\Effect\\drop.efkefc",			// �����Ԃ�
};
CMyEffekseer *CMyEffekseer::s_pMyEffekseer = nullptr;	// ���g�̃|�C���^

//===========================================================
// �R���X�g���N�^
//===========================================================
CMyEffekseer::CMyEffekseer()
{
	m_nNum = 0;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CMyEffekseer::~CMyEffekseer()
{

}

//===========================================================
// ��������
//===========================================================
CMyEffekseer *CMyEffekseer::Create(void)
{
	if (s_pMyEffekseer == nullptr)
	{
		s_pMyEffekseer = new CMyEffekseer;

		if (s_pMyEffekseer != nullptr)
			s_pMyEffekseer->Init();
	}

	return s_pMyEffekseer;
}

//===========================================================
// ����������
//===========================================================
void CMyEffekseer::Init(void)
{
	// �G�t�F�N�g�̃}�l�[�W���[�̍쐬
	m_efkManager = ::Effekseer::Manager::Create(8000);

	// ���_�ʒu���m��
	m_viewerPosition = ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f);

	// ���W�n��ݒ肷��B�A�v���P�[�V�����ƈ�v������K�v������B
	m_efkManager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

	// Effekseer�̃��W���[�����Z�b�g�A�b�v����
	SetupEffekseerModules(m_efkManager);

	// ���e�s���ݒ�
	m_projectionMatrix.PerspectiveFovLH(90.0f / 180.0f * 3.14f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 500.0f);

	// �J�����s���ݒ�
	m_cameraMatrix.LookAtLH(m_viewerPosition, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f));
}

//===========================================================
// �I������
//===========================================================
void CMyEffekseer::Uninit(void)
{
	for (auto it = m_listEffect.begin(); it != m_listEffect.end();)
	{
		auto itNext = std::next(it);

		if (itNext == m_listEffect.end())
			break;

		ReleaseEffect((*it));

		it = itNext;
	}

	m_nNum = 0;

	delete this;
}

//===========================================================
// �X�V����
//===========================================================
void CMyEffekseer::Update(void)
{
	// ���C���[�p�����[�^�̐ݒ�
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = m_viewerPosition;
	m_efkManager->SetLayerParameter(0, layerParameter);

	// �}�l�[�W���[�̍X�V
	Effekseer::Manager::UpdateParameter updateParameter;
	m_efkManager->Update(updateParameter);

	for (auto it = m_listEffect.begin(); it != m_listEffect.end(); )
	{
		// �G�t�F�N�g�̈ړ�
		Effekseer::Handle handle = (*it)->GetHandle();
		Effekseer::Vector3D pos = (*it)->GetPositionVector3();
		m_efkManager->SetLocation(handle, pos);

		// �G�t�F�N�g�̌������f
		Effekseer::Vector3D rot = (*it)->GetRotation();
		m_efkManager->SetRotation(handle, rot.X, rot.Y, rot.Z);

		// �G�t�F�N�g�̃X�P�[�����f
		Effekseer::Vector3D scale = (*it)->GetScale();
		m_efkManager->SetScale(handle, scale.X, scale.Y, scale.Z);

		// ��~�t���O�̎擾
		bool bStop = false;
		CGame *pGame = CGame::GetInstance();
		if (pGame != nullptr)
			bStop = pGame->GetStop();

		if (bStop)
		{
			// �Đ����Ԃ��~����
			m_efkManager->SetPaused(handle, true);
		}
		else
		{
			if (it == m_listEffect.begin())
			{
				// �Đ����Ԃ�i�߂�
				int32_t time = (*it)->GetTime();
				time++;
				(*it)->SetTime(time);

				m_efkManager->SetPaused(handle, false); // �Đ����ĊJ
			}
		}

		// ���t���[���A�G�t�F�N�g���Đ��I�����Ă��邩�m�F����
		if (m_efkManager->Exists(handle) == false)
		{
			(*it)->Uninit();
			it = m_listEffect.erase(it);  // ���X�g����v�f���폜���A�C�e���[�^���X�V
		}
		else
		{
			++it;  // �G�t�F�N�g���܂����݂���ꍇ�͎��̗v�f�֐i��
		}
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CMyEffekseer::Draw(void)
{
	if (m_efkRenderer != nullptr)
	{
		// ���e�s���ݒ�
		m_efkRenderer->SetProjectionMatrix(m_projectionMatrix);

		// �J�����̏��擾
		CCamera* pCamera = CManager::GetCamera();

		// �r���[�}�g���b�N�X
		auto ViewMatrix = pCamera->GetCamera()->mtxView;

		// �v���W�F�N�V�����}�g���b�N�X
		auto Projection = pCamera->GetCamera()->mtxProjection;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_projectionMatrix.Values[i][j] = Projection.m[i][j];
				m_cameraMatrix.Values[i][j] = ViewMatrix.m[i][j];
			}
		}

		// �J�����s���ݒ�
		m_efkRenderer->SetCameraMatrix(m_cameraMatrix);

		// �G�t�F�N�g�̕`��J�n�������s���B
		m_efkRenderer->BeginRendering();

		// �G�t�F�N�g�̕`����s���B
		Effekseer::Manager::DrawParameter drawParameter;
		drawParameter.ZNear = 0.0f;
		drawParameter.ZFar = 1.0f;
		drawParameter.ViewProjectionMatrix = m_efkRenderer->GetCameraProjectionMatrix();
		m_efkManager->Draw(drawParameter);

		// �G�t�F�N�g�̕`��I���������s���B
		m_efkRenderer->EndRendering();
	}
}

//===========================================================
// �G�t�F�N�g�̐���
//===========================================================
CEffekseerEffect *CMyEffekseer::CreateEffect(const char* FileName, ::Effekseer::Vector3D pos, ::Effekseer::Vector3D rot, ::Effekseer::Vector3D scale)
{
	CEffekseerEffect *pEffect = nullptr;

	pEffect = new CEffekseerEffect;

	if (pEffect == nullptr)
		return nullptr;

	// �G�t�F�N�g�̓Ǎ�
	// char16_t�ɕϊ�
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
	std::u16string string16t = converter.from_bytes(FileName);

	Effekseer::EffectRef effect = Effekseer::Effect::Create(m_efkManager, string16t.c_str());

	pEffect->SetEffect(effect);
	
	// �G�t�F�N�g�̍Đ�
	Effekseer::Handle handle = m_efkManager->Play(effect, 0, 0, 0);

	pEffect->SetHandle(handle);

	pEffect->Init(pos, rot, scale);

	m_listEffect.push_back(pEffect);

	return pEffect;
}

//===========================================================
// ���W���[���ݒ�
//===========================================================
void CMyEffekseer::SetupEffekseerModules(::Effekseer::ManagerRef efkManager)
{
	// �`��f�o�C�X�̍쐬
	::Effekseer::Backend::GraphicsDeviceRef graphicsDevice;
	graphicsDevice = ::EffekseerRendererDX9::CreateGraphicsDevice(CRenderer::GetInstance()->GetDevice());

	// �G�t�F�N�g�̃����_���[�̍쐬
	m_efkRenderer = ::EffekseerRendererDX9::Renderer::Create(graphicsDevice, 8000);

	// �`�惂�W���[���̐ݒ�
	efkManager->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
	efkManager->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
	efkManager->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
	efkManager->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
	efkManager->SetModelRenderer(m_efkRenderer->CreateModelRenderer());

	// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
	// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
	efkManager->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
	efkManager->SetModelLoader(m_efkRenderer->CreateModelLoader());
	efkManager->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
	efkManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
}

//===========================================================
// �G�t�F�N�g�̃����[�X
//===========================================================
void CMyEffekseer::Release(int idx)
{

}

//===========================================================
// �G�t�F�N�g�̃����[�X
//===========================================================
void CMyEffekseer::ReleaseEffect(CEffekseerEffect *pEffect)
{
	if (pEffect == nullptr)
		return;

	// �G�t�F�N�g�̏I������
	pEffect->Uninit();

	// ���X�g���珜�O
	m_listEffect.remove(pEffect);
}

//===========================================================
// �G�t�F�N�g�t�@�C���̃p�X�擾
//===========================================================
const char* CMyEffekseer::GetPathEffect(CMyEffekseer::TYPE type)
{
	if (type <= TYPE::TYPE_NONE || type >= TYPE::TYPE_MAX)
		return nullptr;

	return m_apEfkName[type];
}

//**************************************************************************************
// �G�t�F�N�g�N���X
//**************************************************************************************
//===========================================================
// �R���X�g���N�^
//===========================================================
CEffekseerEffect::CEffekseerEffect(int nPriority)
{

}

//===========================================================
// �f�X�g���N�^
//===========================================================
CEffekseerEffect::~CEffekseerEffect()
{

}

//===========================================================
// ������
//===========================================================
HRESULT CEffekseerEffect::Init(::Effekseer::Vector3D pos, ::Effekseer::Vector3D rot, ::Effekseer::Vector3D scale)
{
	m_pos = pos;
	m_rot = rot;
	m_scale = scale;
	m_time = 0;

	CMyEffekseer *pEffekseer = CManager::GetMyEffekseer();

	if (pEffekseer == nullptr)
		return E_FAIL;

	Effekseer::ManagerRef manager = pEffekseer->GetEfkManager();

	// �ʒu�A�����A�傫���ݒ�
	manager->SetLocation(m_efkHandle, m_pos);
	manager->SetRotation(m_efkHandle, { 0.0f, 1.0f, 0.0f }, rot.Y);
	manager->SetScale(m_efkHandle, m_scale.X, m_scale.Y, m_scale.Z);

	return S_OK;
}

//===========================================================
// �I��
//===========================================================
void CEffekseerEffect::Uninit()
{
	CMyEffekseer *pEffekseer = CManager::GetMyEffekseer();

	if (pEffekseer == nullptr)
		return;

	Effekseer::ManagerRef efkManager = pEffekseer->GetEfkManager();

	// �G�t�F�N�g�̉��
	efkManager->StopEffect(m_efkHandle);
}

//===========================================================
// �X�V����
//===========================================================
void CEffekseerEffect::Update(void)
{

}

//===========================================================
// �`��
//===========================================================
void CEffekseerEffect::Draw(void)
{
	//CMyEffekseer *pEffekseer = CManager::GetMyEffekseer();

	//if (pEffekseer == nullptr)
	//	return;

	//EffekseerRendererDX9::RendererRef renderer = pEffekseer->GetEffekseerRenderer();
	//Effekseer::ManagerRef manager = pEffekseer->GetEfkManager();

	//LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	////-----------------------------------------
	//// �J�����̐ݒ�
	////-----------------------------------------
	//// ���e�s���ݒ�
	//renderer->SetProjectionMatrix(m_projectionMatrix);

	//// �J�����̏��擾
	//CCamera* pCamera = CManager::GetCamera();

	//// �r���[�}�g���b�N�X
	//auto ViewMatrix = pCamera->GetCamera()->mtxView;

	//// �v���W�F�N�V�����}�g���b�N�X
	//auto Projection = pCamera->GetCamera()->mtxProjection;

	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		m_projectionMatrix.Values[i][j] = Projection.m[i][j];
	//		m_cameraMatrix.Values[i][j] = ViewMatrix.m[i][j];
	//	}
	//}

	//// �J�����s���ݒ�
	//renderer->SetCameraMatrix(m_cameraMatrix);

	////-----------------------------------------
	//// �`��
	////-----------------------------------------
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//// �G�t�F�N�g�̕`��J�n�������s���B
	//renderer->BeginRendering();

	//// �G�t�F�N�g�̕`����s���B
	//Effekseer::Manager::DrawParameter drawParameter;
	//drawParameter.ZNear = 0.0f;
	//drawParameter.ZFar = 1.0f;
	//drawParameter.ViewProjectionMatrix = renderer->GetCameraProjectionMatrix();
	//manager->Draw(drawParameter);

	//// �G�t�F�N�g�̕`��I���������s���B
	//renderer->EndRendering();

	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//===========================================================
// �ʒu�̒Ǐ]
//===========================================================
CEffekseerEffect *CEffekseerEffect::FollowPosition(D3DXVECTOR3 pos)
{
	CMyEffekseer *pEffekseer = CManager::GetMyEffekseer();

	if (pEffekseer == nullptr)
		return nullptr;

	Effekseer::ManagerRef efkManager = pEffekseer->GetEfkManager();

	// ���t���[���A�G�t�F�N�g���Đ��I�����Ă��邩�m�F����
	if (efkManager->Exists(m_efkHandle) == false)
	{
		return nullptr;
	}

	SetPosition(Effekseer::Vector3D(pos.x, pos.y, pos.z));

	return this;
}

namespace MyEffekseer
{
CEffekseerEffect *CreateEffect(CMyEffekseer::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	CMyEffekseer *pEffekseer = CMyEffekseer::GetInstance();

	if (pEffekseer == nullptr)
		return nullptr;

	// �p�X�̎擾
	const char* pPath = pEffekseer->GetPathEffect(type);

	if (pPath == nullptr)
		return nullptr;

	CEffekseerEffect *pEffect = pEffekseer->CreateEffect(pPath, Effekseer::Vector3D(pos.x, pos.y, pos.z), Effekseer::Vector3D(rot.x, rot.y, rot.z), Effekseer::Vector3D(scale.x, scale.y, scale.z));

	return pEffect;
}
}