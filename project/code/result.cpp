//*****************************************************
//
// Q[[game.cpp]
// Author:ûüRç
//
//*****************************************************

//*****************************************************
// CN[h
//*****************************************************
#include "manager.h"
#include "result.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputManager.h"
#include "fade.h"
#include "camera.h"
#include "sound.h"
#include "scene.h"
#include "debugproc.h"
#include "UIManager.h"
#include "polygon3D.h"
#include "texture.h"
#include "renderer.h"
#include "animEffect3D.h"
#include "pause.h"
#include "meshfield.h"
#include "CameraState.h"
#include "particle.h"
#include "timer.h"
#include "blur.h"
#include "resultSingle.h"
#include "player.h"
#include "score.h"
#include "fishshadow.h"
#include "house.h"

//*****************************************************
// èè`
//*****************************************************
namespace
{
	const int TRANS_TIME = 100;	// I¹ÜÅÌ]CÌt[
	const int SPEED_TIME = 60;	// ^C}[ª¸ÁÄ¢­¬x
	const char* PATH_GAME_ROAD = "data\\MAP\\road00.bin";	// Q[bV[hÌpX
	const char* PATH_SAMPLE_ICESTAGE = "data\\TEXT\\ice_stage_00.txt";	// TvÌúzu
	const float SPEED_CHANGE_LIGHTCOL = 0.1f;	// CgÌFªÏíé¬x
	const D3DXVECTOR3 SET_POS = D3DXVECTOR3(-900.0f, 0.0f, 0.0f);
	const float ADD_X = 200.0f;
	const float CHARA_Z = (-100.0f);
	char* CHARA_PATH = "data\\TEXT\\motion_kidsboy.txt";
	const float CNT = 0.3f;
	const int MAX_WIDTH_NUM = 10;
	const float ADD_Z = 500.0f;
	const D3DXVECTOR3 END_CAMERAROT = D3DXVECTOR3(D3DX_PI * 0.25f, 0.0f, 0.0f);
	const float END_CAMERADIS = 2000.0f;
	const float END_CAMERAINER = 0.02f;
}

//*****************************************************
// ÃIoÏé¾
//*****************************************************
CResult* CResult::m_pResult = nullptr;	// ©gÌ|C^

//=====================================================
// RXgN^
//=====================================================
CResult::CResult()
{
	m_ClearList.clear();
	m_CharacterList.clear();
	m_CharacterIt = m_CharacterList.end();
	m_fCnt = 0.0f;
	m_nKeyOld = 0;
	m_bEnd = false;
	m_camerastart = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=====================================================
// ú»
//=====================================================
HRESULT CResult::Init(void)
{
	// eNXÌú»
	CScene::Init();

	m_pResult = this;

	// Xgðæ¾·éæ
	//m_ClearList = CHouse::GetLabelResult();
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);
	m_ClearList.push_back(CPresent::E_Label::LABEL_PUPLE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_YELLOW);
	m_ClearList.push_back(CPresent::E_Label::LABEL_BLUE);
	m_ClearList.push_back(CPresent::E_Label::LABEL_GREEN);

	// v[gðÀ×é
	InitCharacter();

	// Ce[^[ú»
	m_CharacterIt = m_CharacterList.begin();

	CCamera* pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->ChangeState(new CCameraStateResult);
		pCamera->SetDist(600.0f);
		m_camerastart = pCamera->GetPosR();

		if (m_CharacterIt != m_CharacterList.end())
		{
			m_camerastart = (*m_CharacterIt)->pCharacter->GetPosition();
		}

		pCamera->SetPosR(m_camerastart);
	}

	// Q[BGMÌÄ¶
	Sound::Play(CSound::LABEL_BGM_GAME01);

	return S_OK;
}

//=====================================================
// I¹
//=====================================================
void CResult::Uninit(void)
{
	// îñpü
	for (auto& it : m_CharacterList)
	{

		if (it->pCharacter == m_LastInfo.pCharacter) {
			continue;
		}

		delete it;
	}

	m_CharacterList.clear();

	// IuWFNgSü
	CObject::ReleaseAll();

	CScene::Uninit();

	m_pResult = nullptr;
}

//=====================================================
// XV
//=====================================================
void CResult::Update(void)
{
	CFade* pFade = CFade::GetInstance();
	CInputManager* pInputManager = CInputManager::GetInstance();
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CSound* pSound = CSound::GetInstance();

	// [VÝè
	MotionSet();

	// JÇ]
	PursueCamera();

	// JXV
	UpdateCamera();

	// V[ÌXV
	CScene::Update();
}

//=====================================================
// `æ
//=====================================================
void CResult::Draw(void)
{
#ifndef _DEBUG

	return;

#endif
}

//=====================================================
// JÌXV
//=====================================================
void CResult::UpdateCamera(void)
{
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	pCamera->Update();
}

//=====================================================
// [VÝè
//=====================================================
void CResult::MotionSet(void)
{
	m_fCnt += CManager::GetDeltaTime();

	if (m_fCnt >= CNT)
	{
		m_fCnt = 0.0f;
		// LN^[ éæ
		if (m_CharacterIt != m_CharacterList.end())
		{
			(*m_CharacterIt)->pCharacter->SetMotion(1);
			(*m_CharacterIt)->pPresent->SetMotion(1);
			m_camerastart = (*m_CharacterIt)->pCharacter->GetPosition();
			m_CharacterIt++;
		}
	}

	// [VmF
	for (const auto& it : m_CharacterList)
	{
		if (it->pCharacter->IsFinish())
		{
			if (it->pCharacter == m_LastInfo.pCharacter)
			{
				it->pCharacter->SetMotion(3);
			}
			else
			{
				it->pCharacter->SetMotion(2);
			}
		}
	}

	// I¹mF
	if (m_nKeyOld > m_LastInfo.pCharacter->GetKey() && m_LastInfo.pCharacter->GetMotion() == 3)
	{
		m_bEnd = true;
	}
}

//=====================================================
// JÇ]
//=====================================================
void CResult::PursueCamera(void)
{
	if (m_bEnd) { EndCamera(); return; }

	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr){ return; }

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_CharacterIt != m_CharacterList.end())
	{
		pos = (*m_CharacterIt)->pCharacter->GetPosition();
	}
	else
	{
		pos = m_LastInfo.pCharacter->GetPosition();
	}

	D3DXVECTOR3 diff = pos - m_camerastart;
	D3DXVECTOR3 setpos = m_camerastart + (diff * (m_fCnt / CNT));

	pCamera->SetPosR(setpos);
}

//=====================================================
// ú»
//=====================================================
void CResult::InitCharacter(void)
{
	int i = 0;
	for (const auto& it : m_ClearList)
	{
		SCharaInfo* info = new SCharaInfo();
		// v[gÌ¶¬
		info->pPresent = CPresent::Create(it);
		D3DXVECTOR3 pos = SET_POS;
	
		pos.x += ADD_X * (i % MAX_WIDTH_NUM);

		// ÌñÉÚ®
		int temp = (i / MAX_WIDTH_NUM);
		pos.z += ADD_Z * temp;

		if (temp % 2 != 0)
		{
			pos.x *= -1.0f;
		}
		
		// lÝè
		info->pPresent->SetPosition(pos);
		info->pPresent->SetScale(0.75f);

		// LN^[¶¬
		info->pCharacter = CMotion::Create(CHARA_PATH);
		pos.z += CHARA_Z;
		info->pCharacter->SetPosition(pos);
		info->pCharacter->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		info->pCharacter->SetScale(1.3f);
		m_CharacterList.push_back(info);

		i++;
	}


	// ÅãÌ¸sLðì¬
	m_LastInfo.pPresent = CPresent::Create(CPresent::E_Label::LABEL_YELLOW);
	D3DXVECTOR3 pos = SET_POS;
	int temp = (i / MAX_WIDTH_NUM);
	pos.x += (ADD_X * (i % MAX_WIDTH_NUM));
	pos.z += ADD_Z * temp;


	if (temp % 2 != 0)
	{
		pos.x *= -1.0f;
	}

	m_LastInfo.pPresent->SetPosition(pos);
	m_LastInfo.pPresent->SetScale(0.75f);

	m_LastInfo.pCharacter = CMotion::Create(CHARA_PATH);
	pos.z += CHARA_Z;
	m_LastInfo.pCharacter->SetPosition(pos);
	m_LastInfo.pCharacter->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	m_LastInfo.pCharacter->SetScale(1.1f);
	m_CharacterList.push_back(&m_LastInfo);
}

void CResult::EndCamera(void)
{
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr) { return; }

	float dis = pCamera->GetDist() + ((END_CAMERADIS - pCamera->GetDist()) * END_CAMERAINER);
	pCamera->SetDist(dis);

	D3DXVECTOR3 rot = pCamera->GetRot() + ((END_CAMERAROT - pCamera->GetRot()) * END_CAMERAINER);
	pCamera->SetRot(rot);
}