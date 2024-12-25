//*****************************************************
//
// ゲーム処理[game.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
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
// 定数定義
//*****************************************************
namespace
{
	const int TRANS_TIME = 100;	// 終了までの余韻のフレーム数
	const int SPEED_TIME = 60;	// タイマーが減っていく速度
	const char* PATH_GAME_ROAD = "data\\MAP\\road00.bin";	// ゲームメッシュロードのパス
	const char* PATH_SAMPLE_ICESTAGE = "data\\TEXT\\ice_stage_00.txt";	// サンプルの初期配置
	const float SPEED_CHANGE_LIGHTCOL = 0.1f;	// ライトの色が変わる速度
	const D3DXVECTOR3 SET_POS = D3DXVECTOR3(-900.0f, 0.0f, 0.0f);
	const float ADD_X = 200.0f;
	const float CHARA_Z = (-100.0f);
	char* CHARA_PATH = "data\\TEXT\\motion_kidsboy.txt";
	const float CNT = 0.35f;
	const int MAX_WIDTH_NUM = 10;
	const float ADD_Z = 500.0f;
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CResult* CResult::m_pResult = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
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
// 初期化処理
//=====================================================
HRESULT CResult::Init(void)
{
	// 親クラスの初期化
	CScene::Init();

	m_pResult = this;

	// リストを取得するよ
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

	// プレゼントを並べる
	InitCharacter();

	// イテレーター初期化
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

	// ゲームBGMの再生
	Sound::Play(CSound::LABEL_BGM_GAME01);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CResult::Uninit(void)
{
	// 情報廃棄
	for (auto& it : m_CharacterList)
	{

		if (it->pCharacter == m_LastInfo.pCharacter) {
			continue;
		}

		delete it;
	}

	m_CharacterList.clear();

	// オブジェクト全棄
	CObject::ReleaseAll();

	CScene::Uninit();

	m_pResult = nullptr;
}

//=====================================================
// 更新処理
//=====================================================
void CResult::Update(void)
{
	CFade* pFade = CFade::GetInstance();
	CInputManager* pInputManager = CInputManager::GetInstance();
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CSound* pSound = CSound::GetInstance();

	// モーション設定
	MotionSet();

	// カメラ追従
	PursueCamera();

	// カメラ更新
	UpdateCamera();

	// シーンの更新
	CScene::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CResult::Draw(void)
{
#ifndef _DEBUG

	return;

#endif
}

//=====================================================
// カメラの更新
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
// モーション設定
//=====================================================
void CResult::MotionSet(void)
{
	m_fCnt += CManager::GetDeltaTime();

	if (m_fCnt >= CNT)
	{
		m_fCnt = 0.0f;
		// キャラクター次あるよ
		if (m_CharacterIt != m_CharacterList.end())
		{
			(*m_CharacterIt)->pCharacter->SetMotion(1);
			(*m_CharacterIt)->pPresent->SetMotion(1);
			m_camerastart = (*m_CharacterIt)->pCharacter->GetPosition();
			m_CharacterIt++;
		}
	}

	// モーション確認
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

	// 終了確認
	if (m_nKeyOld > m_LastInfo.pCharacter->GetKey() && m_LastInfo.pCharacter->GetMotion() == 3)
	{
		m_bEnd = true;
	}
}

//=====================================================
// カメラ追従
//=====================================================
void CResult::PursueCamera(void)
{
	if (m_bEnd) { return; }

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
// 初期化
//=====================================================
void CResult::InitCharacter(void)
{
	int i = 0;
	for (const auto& it : m_ClearList)
	{
		SCharaInfo* info = new SCharaInfo();
		// プレゼントの生成
		info->pPresent = CPresent::Create(it);
		D3DXVECTOR3 pos = SET_POS;
	
		pos.x += ADD_X * (i % MAX_WIDTH_NUM);

		// 次の列に移動
		int temp = (i / MAX_WIDTH_NUM);
		pos.z += ADD_Z * temp;

		if (temp % 2 != 0)
		{
			pos.x *= -1.0f;
		}
		
		// 値設定
		info->pPresent->SetPosition(pos);
		info->pPresent->SetScale(0.75f);

		// キャラクター生成
		info->pCharacter = CMotion::Create(CHARA_PATH);
		pos.z += CHARA_Z;
		info->pCharacter->SetPosition(pos);
		info->pCharacter->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		info->pCharacter->SetScale(1.3f);
		m_CharacterList.push_back(info);

		i++;
	}


	// 最後の失敗キャラを作成
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