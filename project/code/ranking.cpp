//*****************************************************
//
// �����L���O�̏���[Ranking.cpp]
//Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "ranking.h"
#include "fade.h"
#include "object.h"
#include "manager.h"
#include "texture.h"
#include "inputManager.h"
#include "skybox.h"
#include "universal.h"
#include "sound.h"
#include "meshcylinder.h"
#include "texture.h"
#include "camera.h"
#include "polygon2D.h"
#include "timer.h"
#include "cameraState.h"
#include "UI.h"
#include "light.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_PLACE					(6)										// �X�R�A�̌���
#define TIMER_TRANS					(360)									// �J�ڎ���
#define RANKING_WIDTH			(80)	// ����
#define RANKING_HEIGHT			(80)	// ����
#define FLASH_SPEED					(10)	// �_�ŃX�s�[�h
#define RANKING_BIN_FILE			"data\\BIN\\ranking"								// �����L���O�t�@�C����
#define RANKING_TEX_FILE			"data\\TEXTURE\\UI\\Number000.png"		// �����L���O�e�N�X�`����
#define BG_TEX_FILE					"data\\TEXTURE\\BG\\ResultBg000.png"	// �����L���O�w�i�e�N�X�`����
#define RANKING_PATH	"data\\TEXTURE\\UI\\ranking00.png"	// ���ڃe�N�X�`����

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float SPEED_ROTATION = 0.003f;	// ���X�s�[�h
const float HEIGHT_CYLINDER = 800.0f;	// �V�����_�[�̍���
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CRanking::s_nTime = 0;

//=====================================================
// �R���X�g���N�^
//=====================================================
CRanking::CRanking()
{
	ZeroMemory(&m_apTimer[0],sizeof(m_apTimer));
	m_nCntState = 0;
	m_nRankUpdate = -1;
	m_nScore = 0;
	m_nTimerTrans = 0;
	ZeroMemory(&m_aScore[0],sizeof(int) * NUM_RANK);
	m_state = STATE_NORMAL;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CRanking::~CRanking()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CRanking::Init(void)
{
	//s_fTime = 49.0f;

	// ���ڂ̐���
	CUI *pObject2D = CUI::Create();
	pObject2D->SetSize(0.3f,0.15f);
	pObject2D->SetPosition(D3DXVECTOR3(0.5f, 0.18f, 0.0f));

	int nIdx = CTexture::GetInstance()->Regist(RANKING_PATH);
	pObject2D->SetIdxTexture(nIdx);
	pObject2D->SetVtx();

	// �����̐���
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		m_apTimer[nCnt] = CTimer::Create();
	}

	// �����ݒ�
	Reset();
	Sort();

	// �X�R�A�̎擾
	//int nScore = Manager::GetScore();

	// �擾�����X�R�A�Ń����L���O�ݒ�
	Set(s_nTime);

	// �ۑ�
	Save();

	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		//pSound->Play(CSound::LABEL_BGM000);
	}

	Camera::ChangeState(new CFollowPlayer);

	CScene::Init();

	// �J�����C���X�^���X�擾
	CCamera *pCamera = CManager::GetCamera();
	assert(pCamera != nullptr);

	// �J�������̐ݒ�
	CCamera::Camera *pInfoCamera = pCamera->GetCamera();
	pInfoCamera->fLength = { 500.0f };			// ����
	pInfoCamera->rot = { 1.35f, 0.0f, 0.0f };	// ����
	pInfoCamera->posR = { 0.0f, 600.0f, 0.0f };	// �����_�ʒu
	pCamera->SetPosV();	// ���_���f

	D3DXVECTOR3 aDir[3] =
	{
		{ -1.4f, 0.24f, -2.21f, },
		{ 1.42f, -0.8f, 0.08f },
		{ -0.29f, -0.8f, 0.55f }
	};

	for (int i = 0; i < 3; i++)
	{
		CLight *pLight = CLight::Create();

		if (pLight == nullptr)
			continue;

		D3DLIGHT9 infoLight = pLight->GetLightInfo();

		infoLight.Type = D3DLIGHT_DIRECTIONAL;
		infoLight.Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);

		D3DXVECTOR3 vecDir = aDir[i];
		D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g�����K��
		infoLight.Direction = vecDir;

		pLight->SetLightInfo(infoLight);
	}
	return S_OK;

}

//=====================================================
// �I������
//=====================================================
void CRanking::Uninit(void)
{
	s_nTime = 0;

	CScene::Uninit();

	CObject::ReleaseAll();
}

//=====================================================
// �X�V����
//=====================================================
void CRanking::Update(void)
{
	CInputManager *pInputManager = CInputManager::GetInstance();
	CFade *pFade = CFade::GetInstance();

	// �V�[���̍X�V
	CScene::Update();

	// �J�E���g�A�b�v
	m_nCntState++;

	if (m_nRankUpdate != -1)
	{// �����L���O���X�V���ꂽ
		// �Y���̃����N��_��==================================
		
		if (m_nCntState >= FLASH_SPEED)
		{// �J�E���^�����̒l�ɒB������
			switch (m_state)
			{
			case STATE_NORMAL:
				m_state = STATE_DIFF;
				break;
			case STATE_DIFF:
				m_state = STATE_NORMAL;
				break;
			}

			m_nCntState = 0;
		}

		// �ϐ��錾
		D3DXCOLOR colRanking = {0.0f,0.0f,0.0f,0.0f};

		switch (m_state)
		{// ��Ԃɂ�镪��
		case STATE_NORMAL:
			colRanking = { 1.0f,1.0f,1.0f,1.0f};
			break;
		case STATE_DIFF:
			colRanking = { 0.5f,1.0f,0.5f,1.0f };
			break;
		}

		if (m_apTimer[m_nRankUpdate] != nullptr)
		{
			m_apTimer[m_nRankUpdate]->SetColor(CTimer::E_Number::NUMBER_MINUTE, colRanking);
			m_apTimer[m_nRankUpdate]->SetColor(CTimer::E_Number::NUMBER_SECOND, colRanking);
		}
	}

	// ��ʑJ��==========================================
	if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
	{//ENTER�L�[�������ꂽ��
		//�^�C�g���Ɉڍs
		if (pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_TITLE);
		}
	}

	// �J�ڃ^�C�}�[�i�s
	m_nTimerTrans++;
}

//=====================================================
// �`�揈��
//=====================================================
void CRanking::Draw(void)
{
	CScene::Draw();
}

//=====================================================
// �ݒ菈��
//=====================================================
void CRanking::Set(int nTime)
{
	// �ϐ��錾
	D3DXVECTOR3 pos;
	char *apPath[NUM_RANK] = 
	{
		"data\\TEXTURE\\UI\\1st.png",
		"data\\TEXTURE\\UI\\2nd.png",
		"data\\TEXTURE\\UI\\3rd.png",
		"data\\TEXTURE\\UI\\4th.png",
		"data\\TEXTURE\\UI\\5th.png",
	};

	// �\�[�g
	Sort();

	if (nTime < m_aScore[NUM_RANK - 1])
	{// �ŏ��l���z��������
		m_aScore[NUM_RANK - 1] = nTime;

		// �ă\�[�g
		Sort();

		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{// �������l�ƍ��v����L�^��T��
			if ((int)nTime == (int)m_aScore[nCnt])
			{// �j���[���R�[�h�ԍ����L�^
				m_nRankUpdate = nCnt;
			}
		}
	}

	if (m_aScore != nullptr)
	{
		// �����̐ݒ�
		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{
			if (m_apTimer[nCnt] != nullptr)
			{
				// �l�̐ݒ�
				m_apTimer[nCnt]->SetSecond(m_aScore[nCnt]);

				// �ʒu�̐ݒ�
				pos = D3DXVECTOR3{ 0.5f,0.4f + 0.1f * nCnt,0.0f };

				m_apTimer[nCnt]->SetPosition(pos);

				pos = m_apTimer[nCnt]->GetPosition();

				m_apTimer[nCnt]->SetScaleNumber(1.0f);

				// ���ʂ̐���
				CUI *pObject2D = CUI::Create();
				pObject2D->SetSize(0.05f, 0.05f);
				pos.x -= 0.19f;

				pObject2D->SetPosition(pos);

				int nIdx = CTexture::GetInstance()->Regist(apPath[nCnt]);
				pObject2D->SetIdxTexture(nIdx);
				pObject2D->SetVtx();
			}
		}
	}

	// �ۑ�����
#ifndef _DEBUG
	Save();
#endif
}

//=====================================================
// �����L���O�\�[�g
//=====================================================
void CRanking::Sort(void)
{
	for (int nCntRanking = 0; nCntRanking < NUM_RANK - 1; nCntRanking++)
	{//�����L���O���\�[�g
		//���[�̒l���ő�l�Ƃ���
		int nTop = nCntRanking;

		for (int nCount2 = nCntRanking + 1; nCount2 < NUM_RANK; nCount2++)
		{//���̒l�ƑΏۂ̒l���r
			if (m_aScore[nTop] > m_aScore[nCount2])
			{//������r����������������������
				nTop = nCount2;
			}
		}

		//�v�f�̓���ւ�
		int nTemp = m_aScore[nCntRanking];
		m_aScore[nCntRanking] = m_aScore[nTop];
		m_aScore[nTop] = nTemp;
	}
}

//=====================================================
// �����L���O��񃊃Z�b�g
//=====================================================
void CRanking::Reset(void)
{
	//�O���t�@�C���ǂݍ���
	Load();

#if 1
	//�����L���O�����ݒ�
	m_aScore[0] = 45;
	m_aScore[1] = 49;
	m_aScore[2] = 50;
	m_aScore[3] = 55;
	m_aScore[4] = 59;
#endif
}

//=====================================================
// �����L���O���ۑ�
//=====================================================
void CRanking::Save(void)
{
	//�|�C���^�錾
	FILE *pFile;

	//�t�@�C�����J��
	pFile = fopen(RANKING_BIN_FILE, "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	    //�o�C�i���t�@�C���ɏ�������
		fwrite(&m_aScore[0], sizeof(float), NUM_RANK, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ

	}
}

//=====================================================
//�����L���O���ǂݍ���
//=====================================================
void CRanking::Load(void)
{
	//�|�C���^�錾
	FILE *pFile;

	//�t�@�C�����J��
	pFile = fopen(RANKING_BIN_FILE, "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	    //�o�C�i���t�@�C������ǂݍ���
		fread(&m_aScore[0], sizeof(float), NUM_RANK, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
	}
}