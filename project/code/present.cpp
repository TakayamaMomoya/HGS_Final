//*****************************************************
//
// プレゼントの処理[present.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "present.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const string PATH_INFO = "data\\TEXT\\present.txt";	// プレゼント情報のパス
const string PATH_LABEL[CPresent::E_Label::LABEL_MAX] =	// ラベルのモデルパス
{
	"data\\TEXT\\box\\motion_box_b.txt",
	"data\\TEXT\\box\\motion_box_g.txt",
	"data\\TEXT\\box\\motion_box_p.txt",
	"data\\TEXT\\box\\motion_box_y.txt",
};
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
vector<CPresent::S_InfoPresent*> CPresent::s_aInfoPresnt;	// プレゼント情報

//=====================================================
// コンストラクタ
//=====================================================
CPresent::CPresent(int nPriority) : CMotion(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CPresent::~CPresent()
{

}

//=====================================================
// 読込処理
//=====================================================
void CPresent::Load(void)
{
	std::ifstream file(PATH_INFO);

	if (file.is_open())
	{
		std::string temp;

		while (std::getline(file, temp))
		{// 読み込むものがなくなるまで読込
			std::istringstream iss(temp);
			std::string key;
			iss >> key;

			if (key == "SET")
			{// ステージ情報読込開始
				// ステージ情報の生成
				S_InfoPresent *pInfo = new S_InfoPresent;

				if (pInfo == nullptr)
					continue;

				LoadInfo(file, temp, pInfo);

				pInfo->nID = s_aInfoPresnt.size();
				s_aInfoPresnt.push_back(pInfo);
			}

			if (file.eof())
			{// 読み込み終了
				break;
			}
		}

		file.close();
	}
	else
	{
		assert(("ファイルが開けませんでした", false));
	}
}


//=====================================================
// 情報の読込
//=====================================================
void CPresent::LoadInfo(std::ifstream& file, string str, S_InfoPresent *pInfo)
{
	if (pInfo == nullptr)
		return;

	while (std::getline(file, str))
	{// 読込開始
		std::istringstream iss(str);
		std::string key;
		iss >> key;

		if (key == "END_SET")
		{// 終了
			break;
		}

		if (key == "PATH_THUMNAIL")
		{// サムネイルのパス
			iss >> str >> pInfo->pathThumnail;
		}

		if (key == "PATH_MODEL")
		{// モデルのパス
			iss >> str >> pInfo->pathThumnail;
		}
	}
}

//=====================================================
// 破棄処理
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
// 生成処理
//=====================================================
CPresent* CPresent::Create(E_Label label)
{
	CPresent *pPresent = nullptr;

	pPresent = new CPresent;

	if (pPresent != nullptr)
	{
		pPresent->m_label = label;
		pPresent->Init();
	}

	return pPresent;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CPresent::Init(void)
{
	// 読込
	CMotion::Load((char*)&PATH_LABEL[m_label][0]);

	CMotion::Init();

	InitPose(0);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CPresent::Uninit(void)
{
	CMotion::Uninit();

	// 自身の解放
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CPresent::Update(void)
{
	CMotion::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CPresent::Draw(void)
{
	CMotion::Draw();
}