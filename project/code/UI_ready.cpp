//*****************************************************
//
// �Q�[���X�^�[�g���mUI����[UI_ready.cpp]
// Author:����F�M
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "UI_ready.h"
#include "UI.h"
#include "texture.h"
#include "game.h"
#include "player.h"
#include "sound.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const int TIME_DIGIT = 1;	// ���ꂼ��̌���
	const int TIME_SECOND = 3;	// �b��
	const int STATE_COUNT_MAX = 60;	// �X�e�[�g�̃J�E���g�ő�l
	const float DIST_NUMBER = 0.03f;	// �����Ԃ̋���
	const D3DXVECTOR2 SIZE_NORMAL_NUM = { 0.05f, 0.09f };	// �ʏ퐔���̃T�C�Y
	const float SIZE_NUM = 0.2f;	// Go�����̃T�C�Y
	const D3DXVECTOR3 POS_INITIAL = { 0.6f,0.5f,0.0f };	// �����ʒu
	const D3DXVECTOR3 POS_GO = { 0.5f,0.5f,0.0f };	// �����ʒu
	const string PATH_TEX_OK = "data\\TEXTURE\\UI\\start.png";	// �R�����̃e�N�X�`���p�X
	const D3DXCOLOR NORMAL_COL = { 1.0f,1.0f,1.0f,1.0f };		//��F
	const int FRAME_CNT = 60;		// �t���[���b��
	const int SECOND_ELAPSED = 1;		// �b���o��
	const float SIZE_WIDTH = 0.5f;		// �T�C�Y�̕�
	const float SIZE_HEIGHT = 0.9f;		// �T�C�Y�̕�
	const float SIZE_READY_INIT = 0.9f;		// READY�̏����T�C�Y
	const float SIZE_READY_MOVE = -0.04f;		// READY�̏����T�C�Y
	const float SIZE_READY_LIMIT = 0.3f;		// READY�̃T�C�Y����
	const D3DXCOLOR READY_COLOR = { 1.0f, 0.8f, 0.0f, 1.0f };		// READY�̐F
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CUIready::CUIready()
{
	m_nSecond = 0;
	m_nFrame = 0;
	m_state = STATE_NUMBER;
	m_nStateCnt = 0;
	m_fsize = 0.0f;
	m_fmove = 0.0f;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CUIready::~CUIready()
{

}

//=====================================================
// ��������
//=====================================================
CUIready* CUIready::Create(void)
{
	CUIready* pUI_ready = nullptr;

	pUI_ready = new CUIready;

	if (pUI_ready != nullptr)
	{// ������
		pUI_ready->Init();
	}

	return pUI_ready;
}

//=====================================================
// ����������
//=====================================================
HRESULT CUIready::Init(void)
{
	m_nSecond = 0;		// �b�̏�����
	m_nFrame = 0;		// �t���[����������
	m_nStateCnt = 0;	// ��ԑJ�ڃJ�E���g�̏�����
	m_fsize = 0.0f;		// �T�C�Y�̏�����	
	m_fmove = 0;		// �ړ��ʏ�����

	// �����ʒu�̐ݒ�
	SetPosition(POS_INITIAL);
	SetSecond(TIME_SECOND);

	// �����̔z��̃��T�C�Y
	m_aNumber.resize(E_Number::NUMBER_MAX);

	int aDigit[E_Number::NUMBER_MAX] =
	{// ����
		TIME_DIGIT,
	};

	// �����̐���
	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		m_aNumber[i] = CNumber::Create(aDigit[i], 0);
	}

	// �����̃g�����X�t�H�[���̐ݒ�
	TransformNumber();

	// �S�v���C���[������s�\�ɂȂ�
	CPlayer::EnableInputAll(false);

	// �Q�[����������Ԃɂ���
	CGame::SetState(CGame::E_State::STATE_READY);

	// �T�E���h�Đ�
	CSound* pSound = CSound::GetInstance();
	if (pSound != nullptr)
	{
		pSound->Play(CSound::LABEL_SE_COUNTDOWN);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CUIready::Uninit(void)
{
	for (auto it : m_aNumber)
	{
		it->Uninit();
	}

	m_aNumber.clear();

	if (m_Go != nullptr)
	{
		m_Go->Uninit();
	}

	CGameObject::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CUIready::Update(void)
{
	// �b�������炤
	m_nSecond = GetSecond();

	switch (m_state)
	{
	case STATE_NUMBER:

		for (int i = 0; i < E_Number::NUMBER_MAX; i++)
		{
			m_aNumber[i]->SetSizeAll(m_fsize, m_fsize);
		}

		// �T�C�Y�ړ���
		m_fmove = 0.002f;

		// �T�C�Y���g��
		m_fsize += m_fmove;

		if (m_nSecond <= 0)
		{
			m_state = STATE_GO;

			for (int i = 0; i < E_Number::NUMBER_MAX; i++)
			{
				m_aNumber[i]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			}

			// GOUI�𐶐�
			m_Go = CUI::Create();

			m_Go->SetPosition(POS_GO);
			int nIdxTexture = Texture::GetIdx(&PATH_TEX_OK[0]);
			m_Go->SetIdxTexture(nIdxTexture);

			// �T�C�Y���Z�b�g
			m_fsize = SIZE_READY_INIT;

			// �T�E���h�Đ�
			CSound* pSound = CSound::GetInstance();
			if (pSound != nullptr)
			{
				pSound->Play(CSound::LABEL_SE_COUNTSTART);
			}
		}

		break;

	case STATE_GO:

		if (m_Go == nullptr)
		{
			return;
		}

		// �T�C�Y�k���̐���
		if (m_fsize <= SIZE_READY_LIMIT)
		{
			m_fsize = SIZE_READY_LIMIT;
		}

		// �T�C�Y�ړ���
		m_fmove = SIZE_READY_MOVE;

		// �T�C�Y���k��
		m_fsize += m_fmove;

		//�X�e�[�g�J�E���g���Z
		m_nStateCnt++;

		// �F�w��
		m_Go->SetCol(READY_COLOR);

		// �T�C�Y�w��
		m_Go->SetSize(m_fsize, m_fsize);

		m_Go->SetVtx();

		if (m_nStateCnt >= STATE_COUNT_MAX)
		{
			// �Q�[���̊J�n
			StartGame();
			return;
		}

		break;
	}

	UpdateNumber();

}

//=====================================================
// �����̍X�V
//=====================================================
void CUIready::UpdateNumber()
{
	if (m_aNumber.empty())
		return;

	if (m_nSecond < 0)
	{
		m_nSecond = 0;
	}

	//�t���[�����Z
	m_nFrame++;

	if (m_nFrame >= FRAME_CNT)
	{
		m_nSecond = m_nSecond - SECOND_ELAPSED;

		m_nFrame = 0;
		
		m_fsize = 0.0f;
		
		//�����T�C�Y������
		for (int i = 0; i < E_Number::NUMBER_MAX; i++)
		{
			m_aNumber[i]->SetSizeAll(m_fsize, m_fsize);
		}

		// �T�E���h�Đ�
		CSound* pSound = CSound::GetInstance();
		if (pSound != nullptr && m_nSecond > 0)
		{
			pSound->Play(CSound::LABEL_SE_COUNTDOWN);
		}
	}

	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		m_aNumber[i]->SetValue(m_nSecond);
	}
}

//=====================================================
// �����̃g�����X�t�H�[���ݒ�
//=====================================================
void CUIready::TransformNumber()
{
	if (m_aNumber.empty())
		return;

	int aDigit[E_Number::NUMBER_MAX] =
	{// ����
		TIME_DIGIT,
	};

	D3DXVECTOR2 aSize[E_Number::NUMBER_MAX] =
	{// �����̃T�C�Y
		SIZE_NORMAL_NUM,
	};

	D3DXVECTOR3 posBase = GetPosition();

	// �������A�������Đݒ�
	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		if (m_aNumber[i] == nullptr)
			continue;

		// �Q�Ƃ���T�C�Y�̔ԍ�
		int nIdx = i;

		if (nIdx > 0)
			nIdx--;	// 0�ԖڂłȂ���ΑO��̃T�C�Y���Q�Ƃ���

		// �p�����[�^�[�ݒ�
		float fWidth = aSize[nIdx].x * aDigit[nIdx] * 2 + DIST_NUMBER;	// �T�C�Y�ɉ����Đ����Ԃ̃X�y�[�X��������
		D3DXVECTOR3 pos = { posBase.x + fWidth * (i - 1), posBase.y, 0.0f };
		m_aNumber[i]->SetPosition(pos);
		m_aNumber[i]->SetSizeAll(aSize[i].x, aSize[i].y);

		if (i == 0)	// 0�ȏ�̂Ƃ���������Ȃ�����
			continue;
	}
}

//=====================================================
// �Q�[���̊J�n
//=====================================================
void CUIready::StartGame(void)
{
	CGame *pGame = CGame::GetInstance();

	if (pGame == nullptr)
		return;

	pGame->StartGame();

	// ���g��j��
	Uninit();
}

//=====================================================
// �ʒu�̐ݒ�
//=====================================================
void CUIready::SetPosition(D3DXVECTOR3 pos)
{
	CGameObject::SetPosition(pos);

	// �����̃g�����X�t�H�[���̐ݒ�
	TransformNumber();
}

//=====================================================
// �`�揈��
//=====================================================
void CUIready::Draw()
{

}