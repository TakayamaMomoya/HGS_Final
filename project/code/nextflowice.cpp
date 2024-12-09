////*****************************************************
////
//// �X�������UI�̏���[nextflowice.cpp]
//// Author:��؈�^
////
////*****************************************************
//
////*****************************************************
//// �C���N���[�h
////*****************************************************
//#include "nextflowice.h"
//#include "manager.h"
//#include "polygon2D.h"
//#include "inputkeyboard.h"
//#include "inputjoypad.h"
//#include "inputManager.h"
//#include "texture.h"
//#include "fade.h"
//#include "game.h"
//#include "sound.h"
//#include "UI.h"
//#include "inputManager.h"
//
////*****************************************************
//// �}�N����`
////*****************************************************
//#define RESULT_WIDTH	(0.18f)	// ���ڂ̕�
//#define RESULT_HEIGHT	(0.05f)	// ���ڂ̍���
//#define MOVE_FACT	(0.15f)	// �ړ����x
//#define LINE_ARRIVAL	(0.05f)	// ���������Ƃ���邵�����l
//#define LINE_UNINIT	(3.0f)	// �I������܂ł̂������l
//
////*****************************************************
//// �萔��`
////*****************************************************
//namespace
//{
//	const char* CREAR_LOGO_PATH = "data\\TEXTURE\\UI\\stage_clear.png";	// �N���A���S�̃p�X
//	const char* FAIL_LOGO_PATH = "data\\TEXTURE\\UI\\gameover.png";	// ���s���S�̃p�X
//}
//
////*****************************************************
//// �ÓI�����o�ϐ��錾
////*****************************************************
//CNextFlowIce* CNextFlowIce::m_pStageResultUI = nullptr;	// ���g�̃|�C���^
//
////====================================================
//// �R���X�g���N�^
////====================================================
//CNextFlowIce::CNextFlowIce() :m_apResult(), m_aPosDest()
//{
//	m_Result = RESULT_CLEAR;
//	m_state = STATE_NONE;
//	m_bSound = false;
//	nCountMove = 0;
//}
//
////====================================================
//// �f�X�g���N�^
////====================================================
//CNextFlowIce::~CNextFlowIce()
//{
//
//}
//
////====================================================
//// ��������
////====================================================
//CNextFlowIce* CNextFlowIce::Create(void)
//{
//	if (m_pStageResultUI == nullptr)
//	{
//		m_pStageResultUI = new CNextFlowIce;
//
//		if (m_pStageResultUI != nullptr)
//		{
//			m_pStageResultUI->Init();
//		}
//	}
//
//	return m_pStageResultUI;
//}
//
////====================================================
//// ����������
////====================================================
//HRESULT CNextFlowIce::Init(void)
//{
//	//�N���A�̎�
//	if (m_Result == RESULT_CLEAR)
//	{
//		// �N���A���S�̐���
//		m_apResult[RESULT_CLEAR] = CPolygon2D::Create(7);
//
//		if (m_apResult[RESULT_CLEAR] != nullptr)
//		{
//			m_apResult[RESULT_CLEAR]->SetSize(300.0f, 100.0f);
//			m_apResult[RESULT_CLEAR]->SetPosition(D3DXVECTOR3(640.0f, 200.0f, 0.0f));
//			int nIdx = CTexture::GetInstance()->Regist(CREAR_LOGO_PATH);
//			m_apResult[RESULT_CLEAR]->SetIdxTexture(nIdx);
//			m_apResult[RESULT_CLEAR]->SetVtx();
//			m_apResult[RESULT_CLEAR]->SetAlpha(0.2f);
//		}
//	}
//
//	//���s�̎�
//	else if (m_Result == RESULT_FAIL)
//	{
//		// ���s���S�̐���
//		m_apResult[RESULT_FAIL] = CPolygon2D::Create(7);
//
//		if (m_apResult[RESULT_FAIL] != nullptr)
//		{
//			m_apResult[RESULT_FAIL]->SetSize(330.0f, 100.0f);
//			m_apResult[RESULT_FAIL]->SetPosition(D3DXVECTOR3(640.0f, 200.0f, 0.0f));
//			int nIdx = CTexture::GetInstance()->Regist(FAIL_LOGO_PATH);
//			m_apResult[RESULT_FAIL]->SetIdxTexture(nIdx);
//			m_apResult[RESULT_FAIL]->SetVtx();
//			m_apResult[RESULT_FAIL]->SetAlpha(0.2f);
//		}
//	}
//
//	m_state = STATE_IN;
//
//	m_aPosDest[0].x = RESULT_WIDTH;
//
//	EnableNotStop(true);
//
//	return S_OK;
//}
//
////====================================================
//// �I������
////====================================================
//void CNextFlowIce::Uninit(void)
//{
//	for (int nCnt = 0; nCnt < RESULT_MAX; nCnt++)
//	{// ���j���[���ڂ̔j��
//		if (m_apResult[nCnt] != nullptr)
//		{
//			m_apResult[nCnt]->Uninit();
//
//			m_apResult[nCnt] = nullptr;
//		}
//	}
//
//	m_pStageResultUI = nullptr;
//
//	Release();
//}
//
////====================================================
//// �X�V����
////====================================================
//void CNextFlowIce::Update(void)
//{
//	// ��ԊǗ�
//	ResultState();
//}
//
////====================================================
//// ��ԊǗ�
////====================================================
//void CNextFlowIce::ResultState(void)
//{
//	// ���U���g���N���A�̎��̏���
//	ResultClear();
//
//	// ���U���g�����s�̎��̏���
//	ResultFail();
//}
//
////====================================================
//// ���U���g���N���A�̎�
////====================================================
//void CNextFlowIce::ResultClear(void)
//{
//	CInputManager* pInputManager = CInputManager::GetInstance();
//
//	// �N���A�̎�
//	if (m_Result == RESULT_CLEAR)
//	{
//		if (m_apResult[RESULT_CLEAR] != nullptr)
//		{
//			D3DXVECTOR2 size = m_apResult[RESULT_CLEAR]->GetSize();
//			float fAlpha = m_apResult[RESULT_CLEAR]->GetAlpha();
//			nCountMove++;
//
//			if (nCountMove > 15 && nCountMove < 25)
//			{
//				fAlpha += 0.08f;
//			}
//
//			// �|���S�����J�E���g���Ƃɓ�����
//			if (nCountMove > 0 && nCountMove < 20 ||
//				nCountMove > 50 && nCountMove < 80 ||
//				nCountMove > 110 && nCountMove < 140)
//			{
//				size.x += 1.0f;
//				size.y += 0.6f;
//			}
//
//			else if (nCountMove > 20 && nCountMove < 50 ||
//				nCountMove > 80 && nCountMove < 110 ||
//				nCountMove > 140 && nCountMove < 170)
//			{
//				size.x -= 1.0f;
//				size.y -= 0.6f;
//			}
//
//			else if (nCountMove > 170)
//			{
//				// �J�E���g�Ɠ����x�����Z�b�g========================================
//				if (pInputManager->GetTrigger(CInputManager::BUTTON_RESULT))
//				{
//					nCountMove = 0;
//					fAlpha = 0.2f;
//				}
//			}
//
//			m_apResult[RESULT_CLEAR]->SetSize(size.x, size.y);
//			m_apResult[RESULT_CLEAR]->SetAlpha(fAlpha);
//			m_apResult[RESULT_CLEAR]->SetVtx();
//		}
//	}
//}
//
////====================================================
//// ���U���g�����s�̎�
////====================================================
//void CNextFlowIce::ResultFail(void)
//{
//	CInputManager* pInputManager = CInputManager::GetInstance();
//
//	// ���s�̎�
//	if (m_Result == RESULT_FAIL)
//	{
//		if (m_apResult[RESULT_FAIL] != nullptr)
//		{
//			D3DXVECTOR3 pos = m_apResult[RESULT_FAIL]->GetPosition();
//			D3DXVECTOR3 rot = m_apResult[RESULT_FAIL]->GetRotation();
//			float fAlpha = m_apResult[RESULT_FAIL]->GetAlpha();
//			nCountMove++;
//
//			if (nCountMove > 15 && nCountMove < 25)
//			{
//				fAlpha += 0.08f;
//			}
//
//			// �|���S�����J�E���g���Ƃɓ�����
//			if (nCountMove > 0 && nCountMove < 40 ||
//				nCountMove > 75 && nCountMove < 105 ||
//				nCountMove > 130 && nCountMove < 150 ||
//				nCountMove > 165 && nCountMove < 175)
//			{
//				pos.y += 1.0f;
//			}
//
//			else if (nCountMove > 40 && nCountMove < 75 ||
//				nCountMove > 105 && nCountMove < 130 ||
//				nCountMove > 150 && nCountMove < 165 ||
//				nCountMove > 175 && nCountMove < 180)
//			{
//				pos.y -= 1.0f;
//			}
//
//			else if (nCountMove > 185 && nCountMove < 205)
//			{
//				rot.z -= 0.008f;
//			}
//
//			else if (nCountMove > 205)
//			{
//				// �J�E���g�Ɠ����x�����Z�b�g========================================
//				if (pInputManager->GetTrigger(CInputManager::BUTTON_RESULT))
//				{
//					nCountMove = 0;
//					fAlpha = 0.2f;
//					rot.z = 0.0f;
//				}
//			}
//
//			m_apResult[RESULT_FAIL]->SetPosition(pos);
//			m_apResult[RESULT_FAIL]->SetRotation(rot);
//			m_apResult[RESULT_FAIL]->SetAlpha(fAlpha);
//			m_apResult[RESULT_FAIL]->SetVtx();
//		}
//	}
//}
//
////====================================================
//// �t�F�[�h���鏈��
////====================================================
//void CNextFlowIce::Fade(RESULT RESULT)
//{
//	CFade* pFade = CFade::GetInstance();
//
//	if (pFade == nullptr)
//	{
//		return;
//	}
//
//	switch (RESULT)
//	{
//	case CNextFlowIce::RESULT_CLEAR:
//
//		CGame::SetState(CGame::STATE_END);
//		pFade->SetFade(CScene::MODE_GAME);
//
//		break;
//	case CNextFlowIce::RESULT_FAIL:
//
//		m_state = STATE_OUT;
//		m_aPosDest[0].x = -RESULT_WIDTH;
//
//		break;
//	default:
//		break;
//	}
//}
//
////====================================================
//// �`�揈��
////====================================================
//void CNextFlowIce::Draw(void)
//{
//
//}