//*****************************************************
//
// ���̓}�l�[�W���[[inputManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "inputManager.h"
#include "manager.h"
#include "inputjoypad.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float DEADZONE_DEFAULT = 0.2f;	// �X�e�B�b�N�̃f�b�h�]�[��
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
vector<CInputManager*> CInputManager::s_aInputMgr;	// �i�[�p�̔z��

//=====================================================
// �R���X�g���N�^
//=====================================================
CInputManager::CInputManager()
{
	ZeroMemory(&m_info, sizeof(S_Info));
	ZeroMemory(&m_axis, sizeof(S_Axis));
	m_nID = -1;
	m_fDeadZone = 0.0f;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CInputManager::~CInputManager()
{

}

//=====================================================
// �f�o�C�X�̑�������
//=====================================================
void CInputManager::InitDevice(HINSTANCE hInstance, HWND hWnd)
{
	// �W���C�p�b�h����
	CInputJoypad::Create();

	// �L�[�{�[�h����
	CInputKeyboard::Create(hInstance, hWnd);

	// �}�E�X����
	CInputMouse::Create(hInstance, hWnd);
}

//=====================================================
// ��������
//=====================================================
CInputManager *CInputManager::Create(void)
{
	CInputManager *pInputMgr = new CInputManager;

	if (pInputMgr != nullptr)
	{
		pInputMgr->Init();
	}

	return pInputMgr;
}

//=====================================================
// �C���X�^���X�̎擾
//=====================================================
CInputManager *CInputManager::GetInstance(int nIdx)
{
	if (nIdx < 0 || nIdx > (int)s_aInputMgr.size() - 1)
		return nullptr;

	return s_aInputMgr[nIdx];
}

//=====================================================
// ����������
//=====================================================
HRESULT CInputManager::Init(void)
{
	// �ԍ��̕ۑ�
	m_nID = s_aInputMgr.size();

	// �z��Ɋi�[
	s_aInputMgr.push_back(this);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CInputManager::Uninit(void)
{
	// ���g�̃|�C���^�j��
	delete this;
}

//=====================================================
// �f�o�C�X�̑�������
//=====================================================
void CInputManager::UninitDevice(void)
{
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();

	if (pJoypad != nullptr)
	{
		pJoypad->Uninit();
	}

	if (pKeyboard != nullptr)
	{
		pKeyboard->Uninit();
	}

	if (pMouse != nullptr)
	{
		pMouse->Uninit();
	}
}

//=====================================================
// �S�C���X�^���X�̉��
//=====================================================
void CInputManager::ReleaseAll(void)
{
	for (auto it : s_aInputMgr)
	{
		if (it != nullptr)
			it->Uninit();
	}

	s_aInputMgr.clear();
}

//=====================================================
// �S�C���X�^���X�̍X�V
//=====================================================
void CInputManager::UpdateAll(void)
{
	// �e���̓f�o�C�X�̍X�V
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();

	if (pJoypad != nullptr)
	{
		pJoypad->Update();
	}

	if (pKeyboard != nullptr)
	{
		pKeyboard->Update();
	}

	if (pMouse != nullptr)
	{
		pMouse->Update();
	}

	for (auto it : s_aInputMgr)
	{
		if (it != nullptr)
			it->Update();
	}
}

//=====================================================
// �X�V����
//=====================================================
void CInputManager::Update(void)
{
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();

	// �G���^�[
	m_info.abTrigger[BUTTON_ENTER] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, m_nID) ||
		pKeyboard->GetTrigger(DIK_RETURN)
	);

	// �����{�^��
	m_info.abTrigger[BUTTON_READY] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, m_nID) ||
		pKeyboard->GetTrigger(DIK_O)
	);

	// �߂�{�^��
	m_info.abTrigger[BUTTON_BACK] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_B, m_nID) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_BACK, m_nID) ||
		pKeyboard->GetTrigger(DIK_BACK)
	);

	// �X�L�b�v�{�^��
	m_info.abPress[BUTTON_SKIP] =
	(
		pJoypad->GetPress(CInputJoypad::PADBUTTONS_BACK, m_nID) ||
		pKeyboard->GetPress(DIK_TAB)
	);

	// �|�[�Y
	m_info.abTrigger[BUTTON_PAUSE] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, m_nID) ||
		pKeyboard->GetTrigger(DIK_P)
	);

	// ������L�[
	m_info.abTrigger[BUTTON_AXIS_UP] =
	(
		pJoypad->GetLStickTrigger(CInputJoypad::DIRECTION_UP, m_nID) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_UP, m_nID) ||
		pKeyboard->GetTrigger(DIK_W)
	);

	// �������L�[
	m_info.abTrigger[BUTTON_AXIS_DOWN] =
	(
		pJoypad->GetLStickTrigger(CInputJoypad::DIRECTION_DOWN, m_nID) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_DOWN, m_nID) ||
		pKeyboard->GetTrigger(DIK_S)
	);

	// �������L�[
	m_info.abTrigger[BUTTON_AXIS_LEFT] =
		(
			pJoypad->GetLStickTrigger(CInputJoypad::DIRECTION_LEFT, m_nID) ||
			pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_LEFT, m_nID) ||
			pKeyboard->GetTrigger(DIK_A)
		);

	// �E�����L�[
	m_info.abTrigger[BUTTON_AXIS_RIGHT] =
		(
			pJoypad->GetLStickTrigger(CInputJoypad::DIRECTION_RIGHT, m_nID) ||
			pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_RIGHT, m_nID) ||
			pKeyboard->GetTrigger(DIK_D)
		);

	// ������e��
	m_info.abTrigger[BUTTON_TRIGGER_UP] =
	(
		pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION_UP, m_nID) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_UP, m_nID)
	);

	// �������e��
	m_info.abTrigger[BUTTON_TRIGGER_DOWN] =
	(
		pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION_DOWN, m_nID) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_DOWN, m_nID)
	);

	// �E�����e��
	m_info.abTrigger[BUTTON_TRIGGER_RIGHT] =
	(
		pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION_RIGHT, m_nID) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_RIGHT, m_nID)
	);

	// �������e��
	m_info.abTrigger[BUTTON_TRIGGER_LEFT] =
	(
		pJoypad->GetRStickTrigger(CInputJoypad::DIRECTION_LEFT, m_nID) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_LEFT, m_nID)
	);

	// ��
	m_info.abTrigger[BUTTON_PECK] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_B, m_nID) ||
		pKeyboard->GetTrigger(DIK_RETURN)
	);

	// �W�����v
	m_info.abTrigger[BUTTON_JUMP] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, m_nID) ||
		pKeyboard->GetTrigger(DIK_SPACE)
	);

	// �X�R�A���Z
	m_info.abTrigger[BUTTON_SCORE] =
	(
		pKeyboard->GetPress(DIK_L)
	);

	// ���U���g���o
	m_info.abTrigger[BUTTON_RESULT] =
	(
		pKeyboard->GetTrigger(DIK_R)
	);

	// �X�ݒu
	m_info.abTrigger[BUTTON_SETICE] =
	(
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_RB, m_nID) ||
		pKeyboard->GetTrigger(DIK_RSHIFT)
	);

	// �����̃��Z�b�g
	ZeroMemory(&m_axis, sizeof(S_Axis));

	// �ړ������̐ݒ�=============
	// �W���C�p�b�h
	D3DXVECTOR3 vecInput = D3DXVECTOR3(pJoypad->GetJoyStickLX(m_nID), 0.0f, pJoypad->GetJoyStickLY(m_nID));
	float fLengthInput = sqrtf(vecInput.x * vecInput.x + vecInput.z * vecInput.z);

	if (fLengthInput < DEADZONE_DEFAULT)
		vecInput = { 0.0f,0.0f,0.0f };

	m_axis.axisMove = vecInput;

	// �L�[�{�[�h
	if (pKeyboard->GetPress(DIK_W))
	{
		m_axis.axisMove.z += 1.0f;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		m_axis.axisMove.z -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		m_axis.axisMove.x -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		m_axis.axisMove.x += 1.0f;
	}

	if (D3DXVec3Length(&m_axis.axisMove) > 1.0f)
		D3DXVec3Normalize(&m_axis.axisMove, &m_axis.axisMove);

	// �J�����̌��������ݒ�=============
	m_axis.axisCamera += D3DXVECTOR3(pJoypad->GetJoyStickRX(m_nID), -pJoypad->GetJoyStickRY(m_nID), 0.0f);
	m_axis.axisCamera += D3DXVECTOR3(pMouse->GetMoveIX(), pMouse->GetMoveIY(), 0.0f);

	D3DXVec3Normalize(&m_axis.axisCamera, &m_axis.axisCamera);
}

void CInputManager::UpdateDevice(void)
{
	// �e���̓f�o�C�X�̍X�V
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();

	if (pJoypad != nullptr)
	{
		pJoypad->UpdateDevice();
	}

	if (pKeyboard != nullptr)
	{
		pKeyboard->UpdateDevice();
	}

	if (pMouse != nullptr)
	{
		pMouse->UpdateDevice();
	}
}