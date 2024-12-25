//*****************************************************
//
// �i�r�Q�[�V�����̏���[navigation.h]
// Author:���R����
//
//*****************************************************
#ifndef _NAVIGATION_H_
#define _NAVIGATION_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CPolygon3D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CNavigation : public CObject
{
public:
	CNavigation(int nPriority = 3);	// �R���X�g���N�^
	~CNavigation();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CreatePolygon(void);	// �|���S���̐���
	void DeletePolygon(void);	// �|���S���̔j��

	// �ÓI�����o�֐�
	static CNavigation *Create(void);	// ��������

private:
	// �����o�֐�
	void FollowPlayer(void);	// �Ǐ]
	float CulcRotDest(void);	// �ڕW�����̌v�Z

	// �����o�ϐ�
	CPolygon3D* m_pPolygon;	// �|���S���̃|�C���^
};

#endif