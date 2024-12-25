//*****************************************************
//
// �v���[���g�̏���[present.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "present.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const string PATH_INFO = "data\\TEXT\\present.txt";	// �v���[���g���̃p�X
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
vector<CPresent::S_InfoPresent*> CPresent::s_aInfoPresnt;	// �v���[���g���

//=====================================================
// �R���X�g���N�^
//=====================================================
CPresent::CPresent(int nPriority) : CObject(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CPresent::~CPresent()
{

}

//=====================================================
// �Ǎ�����
//=====================================================
void CPresent::Load(void)
{
	std::ifstream file(PATH_INFO);

	if (file.is_open())
	{
		std::string temp;

		while (std::getline(file, temp))
		{// �ǂݍ��ނ��̂��Ȃ��Ȃ�܂œǍ�
			std::istringstream iss(temp);
			std::string key;
			iss >> key;

			if (key == "SET")
			{// �X�e�[�W���Ǎ��J�n
				// �X�e�[�W���̐���
				S_InfoPresent *pInfo = new S_InfoPresent;

				if (pInfo == nullptr)
					continue;

				LoadInfo(file, temp, pInfo);

				pInfo->nID = s_aInfoPresnt.size();
				s_aInfoPresnt.push_back(pInfo);
			}

			if (file.eof())
			{// �ǂݍ��ݏI��
				break;
			}
		}

		file.close();
	}
	else
	{
		assert(("�t�@�C�����J���܂���ł���", false));
	}
}


//=====================================================
// ���̓Ǎ�
//=====================================================
void CPresent::LoadInfo(std::ifstream& file, string str, S_InfoPresent *pInfo)
{
	if (pInfo == nullptr)
		return;

	while (std::getline(file, str))
	{// �Ǎ��J�n
		std::istringstream iss(str);
		std::string key;
		iss >> key;

		if (key == "END_SET")
		{// �I��
			break;
		}

		if (key == "PATH_THUMNAIL")
		{// �T���l�C���̃p�X
			iss >> str >> pInfo->pathThumnail;
		}

		if (key == "PATH_MODEL")
		{// ���f���̃p�X
			iss >> str >> pInfo->pathThumnail;
		}
	}
}

//=====================================================
// �j������
//=====================================================
void CPresent::Unload(void)
{
	for (int i = 0; i < (int)s_aInfoPresnt.size() - 1; i++)
	{
		if (s_aInfoPresnt[i] != nullptr)
		{
			delete s_aInfoPresnt[i];
			s_aInfoPresnt[i] = nullptr;
		}
	}

	s_aInfoPresnt.clear();
}

//=====================================================
// ��������
//=====================================================
CPresent* CPresent::Create(void)
{
	CPresent *pPresent = nullptr;

	pPresent = new CPresent;

	if (pPresent != nullptr)
		pPresent->Init();

	return pPresent;
}

//=====================================================
// ����������
//=====================================================
HRESULT CPresent::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CPresent::Uninit(void)
{
	// ���g�̉��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CPresent::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CPresent::Draw(void)
{

}