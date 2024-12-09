//*****************************************************
//
// ���e�̏���[fishshadow.h]
// Author:��؈�^�@���R����
//
//*****************************************************
#ifndef _FISHSHADOW_H_
#define _FISHSHADOW_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "anim3D.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace fishshadow
{
const float TIME_VANISH = 3.0f;								// ���ł܂ł̎���
const float DELAY_AFTER_VANISH = 0.6f;						// �e����������̃f�B���C
const float TIME_APPER = DELAY_AFTER_VANISH + TIME_VANISH;	// ���e���o�鎞��
}

//*****************************************************
// �N���X��`
//*****************************************************
class CFishShadow : public CAnim3D
{
public:
	CFishShadow(int nPriority = 3);	// �R���X�g���N�^
	~CFishShadow();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CFishShadow* Create(int nPatern);

private:
	// �����o�֐�
	void InitSpawn(int nPatern);	// �X�|�[���̏�����
	void UpdateFadeIn(void);		// �t�F�[�h�C�����
	void UpdateFadeOut(void);		// �t�F�[�h�A�E�g���
	void Move(void);				// �ړ�����

	// �����o�ϐ�
	float m_fTimerVanish;	// ������܂ł̃^�C�}�[
	int m_nCntBubble;		// �A�J�E���^�[
	D3DXVECTOR3 m_posInit;	// �����ʒu
	D3DXVECTOR3 m_posDest;	// �ڕW�ʒu
};

#endif