//*****************************************************
//
// �~�j�}�b�v�̏���[minimap.h]
// Author:���R����
//
//*****************************************************
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CMinimap : public CObject
{
public:
	CMinimap(int nPriority = 3);	// �R���X�g���N�^
	~CMinimap();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CMinimap *Create(void);	// ��������

private:
	// �����o�֐�
	void CreatePolygon(void);	// �|���S���̐���
	void FollowPlayer(void);	// �Ǐ]

	// �����o�ϐ�
	CUI* m_pBg;		// �w�i�̃|�C���^
	CUI* m_pPlayer;	// �v���C���[�A�C�R���̃|�C���^
};

#endif