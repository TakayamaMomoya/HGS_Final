//*****************************************************
//
// �`���[�g���A������[tutorial.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "tutorial.h"
#include "camera.h"
#include "cameraState.h"

#include "UI.h"
#include "texture.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "inputManager.h"
#include "sound.h"
#include "fade.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{

}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CTutorial *CTutorial::s_pTutorial = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CTutorial::CTutorial(): 
m_bFade(false)
{
	s_pTutorial = this;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTutorial::~CTutorial()
{
	s_pTutorial = nullptr;
}

//=====================================================
// ����������
//=====================================================
HRESULT CTutorial::Init(void)
{
	// �V�[���̏�����
	if (FAILED(CScene::Init()))
	{ // �������Ɏ��s�����ꍇ

		return E_FAIL;
	}

	// �`���[�g���A���摜��\��
	CUI* ui = CUI::Create();
	ui->SetIdxTexture(Texture::GetIdx("data\\TEXTURE\\tutorial.png"));
	ui->SetSize(0.5f, 0.5f);
	ui->SetPosition({ 0.5f, 0.5f, 0.0f });

	// �J�����̐ݒ�
	Camera::ChangeState(new CFollowPlayer);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTutorial::Uninit(void)
{
	// �V�[���̏I��
	CScene::Uninit();

	// �I�u�W�F�N�g�S�j��
	CObject::ReleaseAll();
}

//=====================================================
// �X�V����
//=====================================================
void CTutorial::Update(void)
{
	// ���͏��̎擾
	CInputKeyboard* pInputKeyboard = CInputKeyboard::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	// �{�^�����͂��Ȃ��ꍇ�֐��𔲂���
	if (!pInputKeyboard->GetTrigger(DIK_SPACE) &&
		!pInputKeyboard->GetTrigger(DIK_RETURN) &&
		!pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
	{ return; }

	// �t�F�[�h��ݒ�
	CFade::GetInstance()->SetFade(CScene::MODE_GAME);
}

//=====================================================
// �`�揈��
//=====================================================
void CTutorial::Draw(void)
{
	// �V�[���̕`��
	CScene::Draw();
}