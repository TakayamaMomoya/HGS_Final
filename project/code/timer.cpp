//*****************************************************
//
// �^�C���̏���[timer.cpp]
// Author:�X��x��
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "timer.h"
#include "UI.h"
#include "texture.h"
#include "game.h"
#include "gameManager.h"
#include "resultSingle.h"
#include "player.h"
#include "fade.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int MINUTES_DIGIT = 2;	// ���\���̌���
const int TIME_DIGIT = 2;	// ���ꂼ��̌���
const float DIST_NUMBER = 0.03f;	// �����Ԃ̋���
D3DXVECTOR2 SIZE_NORMAL_NUM = { 0.02f, 0.06f };	// �ʏ퐔���̃T�C�Y
D3DXVECTOR2 SIZE_MINI_NUM = { 0.014f, 0.028f };	// �~�j�����̃T�C�Y
D3DXVECTOR3 POS_INITIAL = { 0.5f,0.08f,0.0f };	// �����ʒu
const string PATH_TEX_COLON = "data\\TEXTURE\\UI\\colon.png";	// �R�����̃e�N�X�`���p�X
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CTimer::CTimer()
{
	m_nSecond = 0;
	m_fScaleNumber = 0;
	m_bStop = false;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTimer::~CTimer()
{

}

//=====================================================
// ��������
//=====================================================
CTimer* CTimer::Create(void)
{
	CTimer *pTimer = nullptr;

	pTimer = new CTimer;

	if (pTimer != nullptr)
	{// ������
		pTimer->Init();
	}

	return pTimer;
}

//=====================================================
// ���ԕۑ�����
//=====================================================
void CTimer::SaveSecond(int fSecond)
{
	// �t�@�C�����J��
	std::ofstream file("data\\TEMP\\time.bin", std::ios_base::binary);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "���Ԃ̏����o���Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return;
	}

	// �����̎��Ԃ������o��
	file.write((char*)&fSecond, sizeof(float));

	// �t�@�C�������
	file.close();
}

//=====================================================
// ���ԓǍ�����
//=====================================================
int CTimer::LoadSecond(void)
{
	// �t�@�C�����J��
	std::ifstream file("data\\TEMP\\time.bin", std::ios_base::binary);	// �t�@�C���X�g���[��
	if (file.fail())
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "���Ԃ̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return 0;
	}

	// �����̎��Ԃ�ǂݍ���
	int nTime = 0;
	file.read((char*)&nTime, sizeof(float));

	// �t�@�C�������
	file.close();

	// �ǂݍ��񂾎��Ԃ�Ԃ�
	return nTime;
}

//=====================================================
// ����������
//=====================================================
HRESULT CTimer::Init(void)
{
	m_nSecond = 0;	// �b�̏�����
	m_fScaleNumber = 1.0f;	// �����X�P�[���ݒ�
	m_bStop = false;	// �^�C�}�[��~�̃t���O

	// �����ʒu�̐ݒ�
	SetPosition(POS_INITIAL);

	// �����̔z��̃��T�C�Y
	m_aNumber.resize(E_Number::NUMBER_MAX);

	int aDigit[E_Number::NUMBER_MAX] =
	{// ����
		MINUTES_DIGIT,
		TIME_DIGIT,
	};

	// �����̐���
	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		m_aNumber[i] = CNumber::Create(aDigit[i], 0);	// �����̐���
	}

	// �R�����̐���
	m_aColon.resize(E_Number::NUMBER_MAX - 1);

	for (int i = 0; i < E_Number::NUMBER_MAX - 1; i++)
	{
		m_aColon[i] = CUI::Create();

		if (m_aColon[i] == nullptr)
			continue;

		int nIdxTexture = Texture::GetIdx(&PATH_TEX_COLON[0]);
		m_aColon[i]->SetIdxTexture(nIdxTexture);
	}

	// �����̃g�����X�t�H�[���̐ݒ�
	TransformNumber();

	SetPosition(D3DXVECTOR3(0.48f, 0.07f, 0.0f));
	SetSecond(CGame::MAX_TIME);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTimer::Uninit(void)
{
	for (auto it : m_aNumber)
	{
		it->Uninit();
	}

	m_aNumber.clear();

	for (auto it : m_aColon)
	{
		it->Uninit();
	}

	m_aColon.clear();

	CGameObject::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CTimer::Update(void)
{
	UpdateNumber();
}

//=====================================================
// �����̍X�V
//=====================================================
void CTimer::UpdateNumber()
{
	if (m_aNumber.empty())
		return;

	if (m_nSecond < 0)
	{
		m_nSecond = 0;

		// ���Ԑ؂ꃊ�U���g
		CResultSingle::Create(CResultSingle::RESULT_TIMEOVER);
	}

	// �l�̗p��
	int aValue[E_Number::NUMBER_MAX] =
	{
#if 1
		(int)m_nSecond / 60,
		(int)m_nSecond % 60,
#else
		(int)((DWORD)(m_nSecond * 1000) / 60000),
		(int)((DWORD)(m_nSecond * 1000) / 1000 % 60),
#endif
	};

	for (int i = 0; i < E_Number::NUMBER_MAX; i++)
	{
		m_aNumber[i]->SetValue(aValue[i]);
	}
}

//=====================================================
// �����̃g�����X�t�H�[���ݒ�
//=====================================================
void CTimer::TransformNumber()
{
	if (m_aNumber.empty())
		return;

	int aDigit[E_Number::NUMBER_MAX] =
	{// ����
		MINUTES_DIGIT,
		TIME_DIGIT,
	};

	D3DXVECTOR2 aSize[E_Number::NUMBER_MAX] =
	{// �����̃T�C�Y
		SIZE_NORMAL_NUM * m_fScaleNumber,
		SIZE_NORMAL_NUM * m_fScaleNumber,
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
		float fWidth = aSize[nIdx].x * aDigit[nIdx] * 2 + DIST_NUMBER * m_fScaleNumber;	// �T�C�Y�ɉ����Đ����Ԃ̃X�y�[�X��������
		D3DXVECTOR3 pos = { posBase.x + fWidth * (i - 1), posBase.y, 0.0f };
		m_aNumber[i]->SetPosition(pos);
		m_aNumber[i]->SetSizeAll(aSize[i].x, aSize[i].y);

		if (i == 0)	// 0�ȏ�̂Ƃ���������Ȃ�����
			continue;
		
		// �R�����̈ʒu��ݒ�
		int nIdxColon = i - 1;

		if (m_aColon[nIdxColon] != nullptr)
		{
			float fPosXLast = m_aNumber[i - 1]->GetPosition().x + aDigit[i - 1] * aSize[i - 1].x;
			D3DXVECTOR3 posColon = { (pos.x + fPosXLast) / 2, pos.y, 0.0f };
			m_aColon[nIdxColon]->SetPosition(posColon);	// �ʒu
			m_aColon[nIdxColon]->SetSize(aSize[i].x, aSize[i].y);	// �T�C�Y
			m_aColon[nIdxColon]->SetVtx();
		}
	}
}

//=====================================================
// �ʒu�̐ݒ�
//=====================================================
void CTimer::SetPosition(D3DXVECTOR3 pos)
{
	CGameObject::SetPosition(pos);

	// �����̃g�����X�t�H�[���̐ݒ�
	TransformNumber();
}

//=====================================================
// �����̃X�P�[���̐ݒ�
//=====================================================
void CTimer::SetScaleNumber(float fScale)
{
	m_fScaleNumber = fScale;

	// �����̃g�����X�t�H�[���̐ݒ�
	TransformNumber();
}

//=====================================================
// �F�̐ݒ�
//=====================================================
void CTimer::SetColor(E_Number number, D3DXCOLOR col)
{
	if (number < 0 || number > E_Number::NUMBER_MAX)
		return;

	if (number == E_Number::NUMBER_MAX)
	{// �S�����̐F�ݒ�
		for (auto it : m_aNumber)	// ����
			it->SetColor(col);

		for (auto it : m_aColon)	// �R����
			it->SetCol(col);
	}
	else
	{// �e�����̐F�ݒ�
		m_aNumber[number]->SetColor(col);
	}
}

//=====================================================
// �F�̎擾
//=====================================================
D3DXCOLOR CTimer::GetColor(E_Number number)
{
	if (number < 0 || number >= E_Number::NUMBER_MAX)
		return D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	return m_aNumber[number]->GetColor();
}

//=====================================================
// �`�揈��
//=====================================================
void CTimer::Draw()
{

}