//*****************************************************
//
// �w�i�X�̏���[BG_Ice.cpp]
// Author:����F�M
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "BG_Ice.h"
#include "ice.h"
#include "ocean.h"
#include "iceManager.h"
#include "MyEffekseer.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const char* MODEL[bgice::BGICE_MODEL] = { "data\\MODEL\\block\\ice_small001.x","data\\MODEL\\block\\ice_small002.x","data\\MODEL\\block\\ice_small003.x" };
const float MAX_HEIGHT = -300.0f;	// �X�����ލ���
const int MAX_FLOWTIMING = 12;		// �X�����ލő�^�C�~���O
const int MIN_FLOWTIMING = 1;		// �X�����ލŏ��^�C�~���O
const float RATE_SPEED_MOVE = 1.2f;	// �ړ����x�̊���
const int SCREEN_OUT_SINK = 180;	// ��ʊO�ɍs�����Ƃ��ɏ�����J�E���g
}

//====================================================
// �R���X�g���N�^
//====================================================
CBgIce::CBgIce() : CObjectX(), m_state(STATE_FLOW), m_fSpeed(0.0f), m_bInscreen(false), m_nRippleCount(0)
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CBgIce::~CBgIce()
{

}

//====================================================
// ��������
//====================================================
CBgIce* CBgIce::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int type)
{
	CBgIce* pBgIce = new CBgIce;

	pBgIce->SetPosition(pos);
	pBgIce->SetRotation(rot);

	pBgIce->Init();
	
	pBgIce->BindModel(CModel::Load(MODEL[type]));

	return pBgIce;
}

//====================================================
// ����������
//====================================================
HRESULT CBgIce::Init(void)
{
	// �ŏ��̔g��o�����Ԑݒ�
	m_nRippleCount = bgice::RIPPLE_DEFAULT + universal::RandRange(bgice::RIPPLE_DEGREE, -bgice::RIPPLE_DEGREE);

	// ���x�̐ݒ�
	m_fSpeed = (float)universal::RandRange(MAX_FLOWTIMING, MIN_FLOWTIMING) * 0.01f;

	// �p���N���X�̏�����
	CObjectX::Init();

	// �X�N���[���O�ɂ��鎞�Ԃ𐔂���ϐ�������
	m_nOutScreen = 0;

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CBgIce::Uninit(void)
{
	CObjectX::Uninit();
}

//====================================================
// �X�V����
//====================================================
void CBgIce::Update(void)
{
	//�ړ�����
	Move();

	// �g��o���m�F
	RippleCheck();

	CObjectX::Update();
}

//====================================================
// �`�揈��
//====================================================
void CBgIce::Draw(void)
{
	CObjectX::Draw();
}

//=====================================================
// �Ǎ�����
//=====================================================
void CBgIce::Load(char* pPath)
{
	//�ϐ��錾
	char cTemp[MAX_STRING];

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	//�t�@�C������ǂݍ���
	FILE* pFile = fopen(pPath, "r");

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ
		while (true)
		{
			//�����ǂݍ���
			(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "SET") == 0)
			{//�L�[�X�^�[�g
				while (strcmp(cTemp, "END_SET") != 0)
				{//�I���܂ŃL�[�ݒ�

					(void)fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "POS") == 0)
					{//�ʒu�擾
						(void)fscanf(pFile, "%s", &cTemp[0]);

						for (int nCntPos = 0; nCntPos < 3; nCntPos++)
						{
							(void)fscanf(pFile, "%f", &pos[nCntPos]);
						}
					}

					if (strcmp(cTemp, "ROT") == 0)
					{//�����擾
						(void)fscanf(pFile, "%s", &cTemp[0]);

						for (int nCntRot = 0; nCntRot < 3; nCntRot++)
						{
							(void)fscanf(pFile, "%f", &rot[nCntRot]);
						}
					}
				}

				Create(pos, rot, 0);
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
				break;
		}//while
	}//file
	else
	{
		assert(("BgIce�ǂݍ��݂Ɏ��s", false));
	}

	fclose(pFile);
}

//====================================================
// �ړ�����
//====================================================
void CBgIce::Move(void)
{
	CIceManager* pIceManager = CIceManager::GetInstance();

	if (pIceManager == nullptr)
		return;

	// �C���̃x�N�g���擾
	COcean::E_Stream dir = pIceManager->GetDirStream();
	D3DXVECTOR3 vecStream = stream::VECTOR_STREAM[dir];

	D3DXVECTOR3 pos = GetPosition();

	if (universal::IsInScreen(pos))
	{// ��x��ʂɓ������t���O�𗧂Ă�
		m_bInscreen = true;
	}
	else if (m_bInscreen || m_nOutScreen >= SCREEN_OUT_SINK)
	{
		StartSink();

		m_nOutScreen = 0;
	}
	
	m_nOutScreen++;

	// ����鑬�x�ɐ��K�����Ĉʒu�����Z
	float fSpeedFlow = pIceManager->GetOceanLevel();

	switch (m_state)
	{
	case STATE_FLOW:
		// �C���ɂ��ړ�
		D3DXVec3Normalize(&vecStream, &vecStream);
		vecStream *= fSpeedFlow * RATE_SPEED_MOVE;
		Translate(vecStream);

		//�C�ʂɉ��킹��
		Flow();

		// ����̕X�Ƃ̔���
		CollideIce();

		break;

	case STATE_SINK:

		m_bInscreen = false;

		fSpeedGravity += m_fSpeed;

		pos.y -= fSpeedGravity;

		if (pos.y <= MAX_HEIGHT)
			Uninit();

		SetPosition(pos);

		break;
	}
}

//====================================================
// �C�ʂɉ��킹�鏈��
//====================================================
void CBgIce::Flow(void)
{
	COcean* pOcean = COcean::GetInstance();

	if (pOcean == nullptr)
	{
		return;
	}

	// �C�ƈꏏ�ɕX�𓮂�������
	D3DXVECTOR3 pos = GetPosition();

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pos.y = pOcean->GetHeight(pos, &move);

	SetPosition(pos);
}

//====================================================
// �g��o���m�F����
//====================================================
void CBgIce::RippleCheck(void)
{
	m_nRippleCount--;	// �J�E���g���炷

	if (m_nRippleCount <= 0)
	{
		// �C�̏�����
		D3DXVECTOR3 pos = GetPosition();
		MyEffekseer::CreateEffect(CMyEffekseer::TYPE::TYPE_RIPPLE, D3DXVECTOR3(pos.x, 30.0f, pos.z),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(80.0f, 80.0f, 80.0f));	// �g��o��
		m_nRippleCount = bgice::RIPPLE_DEFAULT + universal::RandRange(bgice::RIPPLE_DEGREE, -bgice::RIPPLE_DEGREE);	// �g��o�����Ԑݒ�
	}
}

//====================================================
// ����X�Ƃ̔���
//====================================================
void CBgIce::CollideIce(void)
{
	vector<CIce*> apIce = CIce::GetInstance();

	for (CIce *pIce : apIce)
	{
		if (pIce == nullptr)
			continue;

		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 posIce = pIce->GetPosition();

		if (universal::DistCmpFlat(pos, posIce, Grid::SIZE, nullptr))
		{// �X�Ɠ������Ă��璾�ݎn�߂�
			StartSink();
			return;
		}
	}
}

//====================================================
// ���ݎn�߂鏈��
//====================================================
void CBgIce::StartSink(void)
{
	m_state = STATE_SINK;
	MyEffekseer::CreateEffect(CMyEffekseer::TYPE::TYPE_RIPPLE, GetPosition());
}