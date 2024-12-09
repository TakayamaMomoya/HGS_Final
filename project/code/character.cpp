//*****************************************************
//
// �L�����N�^�[�̏���[character.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "character.h"
#include "shadow.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
namespace init
{
const float DEC_MOVE = 0.5f;		// �ړ������W��
const float FACT_ROTATION = 0.1f;	// ��]�W��
}
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CCharacter::CCharacter(int nPriority) : CMotion(nPriority), m_move(), m_fDecMove(0.0f), m_fFactRot(0.0f), m_fRotDest(0.0f), m_pShadow(nullptr)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CCharacter::~CCharacter()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CCharacter::Init(void)
{
	// �p���N���X�̏�����
	CMotion::Init();

	// �e�̐���
	m_pShadow = CShadow::Create();

	// �p�����[�^�[�̃f�t�H���g�ݒ�
	m_fDecMove = init::DEC_MOVE;
	m_fFactRot = init::FACT_ROTATION;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CCharacter::Uninit(void)
{
	Object::DeleteObject((CObject**)&m_pShadow);

	// �p���N���X�̏I��
	CMotion::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CCharacter::Update(void)
{
	// �ړ��ʂ̔��f
	Translate(GetMove());

	// �e�̒Ǐ]
	if (m_pShadow != nullptr)
		m_pShadow->SetPosition(GetPosition());

	// ���[�V�����X�V
	CMotion::Update();

	// �ړ��ʂ̌���
	DecreaseMove();

	// �����̕␳
	FactingRot();
}

//=====================================================
// �ړ��ʌ���
//=====================================================
void CCharacter::DecreaseMove(void)
{
	D3DXVECTOR3 move = GetMove();

	// �ړ��ʂ̌���
	move.x *= m_fDecMove;
	move.z *= m_fDecMove;

	SetMove(move);
}

//=====================================================
// �����̕␳
//=====================================================
void CCharacter::FactingRot(void)
{
	D3DXVECTOR3 rot = GetRotation();
	universal::FactingRot(&rot.y, m_fRotDest, m_fFactRot);
	SetRotation(rot);
}

//=====================================================
// �`�揈��
//=====================================================
void CCharacter::Draw(void)
{
	// �p���N���X�̕`��
	CMotion::Draw();
}

//=====================================================
// �e�̈ʒu�ݒ�
//=====================================================
void CCharacter::SetShadowPos(D3DXVECTOR3 pos)
{
	if (m_pShadow != nullptr)
		m_pShadow->SetJustPosition(pos);
}