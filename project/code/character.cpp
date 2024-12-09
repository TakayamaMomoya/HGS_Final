//*****************************************************
//
// キャラクターの処理[character.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "character.h"
#include "shadow.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
namespace init
{
const float DEC_MOVE = 0.5f;		// 移動減衰係数
const float FACT_ROTATION = 0.1f;	// 回転係数
}
}

//=====================================================
// コンストラクタ
//=====================================================
CCharacter::CCharacter(int nPriority) : CMotion(nPriority), m_move(), m_fDecMove(0.0f), m_fFactRot(0.0f), m_fRotDest(0.0f), m_pShadow(nullptr)
{

}

//=====================================================
// デストラクタ
//=====================================================
CCharacter::~CCharacter()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CCharacter::Init(void)
{
	// 継承クラスの初期化
	CMotion::Init();

	// 影の生成
	m_pShadow = CShadow::Create();

	// パラメーターのデフォルト設定
	m_fDecMove = init::DEC_MOVE;
	m_fFactRot = init::FACT_ROTATION;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CCharacter::Uninit(void)
{
	Object::DeleteObject((CObject**)&m_pShadow);

	// 継承クラスの終了
	CMotion::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CCharacter::Update(void)
{
	// 移動量の反映
	Translate(GetMove());

	// 影の追従
	if (m_pShadow != nullptr)
		m_pShadow->SetPosition(GetPosition());

	// モーション更新
	CMotion::Update();

	// 移動量の減衰
	DecreaseMove();

	// 向きの補正
	FactingRot();
}

//=====================================================
// 移動量減衰
//=====================================================
void CCharacter::DecreaseMove(void)
{
	D3DXVECTOR3 move = GetMove();

	// 移動量の減衰
	move.x *= m_fDecMove;
	move.z *= m_fDecMove;

	SetMove(move);
}

//=====================================================
// 向きの補正
//=====================================================
void CCharacter::FactingRot(void)
{
	D3DXVECTOR3 rot = GetRotation();
	universal::FactingRot(&rot.y, m_fRotDest, m_fFactRot);
	SetRotation(rot);
}

//=====================================================
// 描画処理
//=====================================================
void CCharacter::Draw(void)
{
	// 継承クラスの描画
	CMotion::Draw();
}

//=====================================================
// 影の位置設定
//=====================================================
void CCharacter::SetShadowPos(D3DXVECTOR3 pos)
{
	if (m_pShadow != nullptr)
		m_pShadow->SetJustPosition(pos);
}