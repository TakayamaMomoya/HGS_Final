//*****************************************************
//
// �V���O���̃����L���O����[rankingSingle.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "rankingSingle.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int NUM_DATA_DEFAULT = 3;	// �f�t�H���g�̃f�[�^��
}

//====================================================
// �R���X�g���N�^
//====================================================
CRankingSingle::CRankingSingle()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CRankingSingle::~CRankingSingle()
{

}

//====================================================
// ��������
//====================================================
CRankingSingle *CRankingSingle::Create(string pathSave)
{
	CRankingSingle *pRanking = nullptr;

	pRanking = new CRankingSingle;

	if (pRanking != nullptr)
	{
		pRanking->m_pathSave = pathSave;
		pRanking->Init();
	}

	return pRanking;
}

//====================================================
// ����������
//====================================================
HRESULT CRankingSingle::Init(void)
{
#if 1
	Reset();	// ���Z�b�g����

	Save();
#endif

	Load();

	return S_OK;
}

//====================================================
// ���Z�b�g
//====================================================
void CRankingSingle::Reset(void)
{
	int aScore[NUM_DATA_DEFAULT] = { 10000,6700,5000 };
	int nTimePeck[NUM_DATA_DEFAULT] = { 10, 15, 20 };

	for (int i = 0; i < NUM_DATA_DEFAULT; i++)
	{
		S_InfoRank *pInfoRank = new S_InfoRank;

		if (pInfoRank == nullptr)
			continue;
		
		pInfoRank->nScore = aScore[i];
		pInfoRank->nTimePeck = nTimePeck[i];

		m_apRank.push_back(pInfoRank);
	}
}

//====================================================
// �z��̉��
//====================================================
void CRankingSingle::ReleaseArray(void)
{
	for (int i = 0; i < (int)m_apRank.size(); i++)
	{
		if (m_apRank[i] == nullptr)
			continue;

		delete m_apRank[i];
		m_apRank[i] = nullptr;
	}

	m_apRank.clear();
}

//====================================================
// �I������
//====================================================
void CRankingSingle::Uninit(void)
{
	ReleaseArray();

	Release();
}

//====================================================
// �X�V����
//====================================================
void CRankingSingle::Update(void)
{

}

//====================================================
// �`�揈��
//====================================================
void CRankingSingle::Draw(void)
{

}

//====================================================
// �Ǎ�
//====================================================
void CRankingSingle::Load(void)
{
	// �z��̉��
	ReleaseArray();

	// �t�@�C�����J��
	std::ifstream inputFile(m_pathSave, std::ios::binary);

	if (!inputFile.is_open())
		assert(("�����L���O�t�@�C�����J���܂���ł���", false));

	while (true)
	{// �t�@�C���̏I���܂œǂݍ���
		S_InfoRank *pInfoRank = new S_InfoRank;

		inputFile.read(reinterpret_cast<char*>(pInfoRank), sizeof(S_InfoRank));

		if (inputFile.eof())
		{
			delete pInfoRank;
			break;
		}

		m_apRank.push_back(pInfoRank);
	}

	inputFile.close();
}

//====================================================
// �ۑ�
//====================================================
void CRankingSingle::Save(void)
{
	// �t�@�C�����J��
	std::ofstream outputFile(m_pathSave, std::ios::binary);

	if (!outputFile.is_open())
		assert(("�����L���O�t�@�C�����J���܂���ł���", false));

	// ���T�C�Y
	size_t size = m_apRank.size();

	for (S_InfoRank *pInfo : m_apRank)
	{
		// �f�[�^�̕ۑ�
		outputFile.write(reinterpret_cast<char*>(&pInfo->nScore), sizeof(int));
		outputFile.write(reinterpret_cast<char*>(&pInfo->nTimePeck), sizeof(int));
	}

	outputFile.close();
}