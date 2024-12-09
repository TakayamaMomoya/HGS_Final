//*****************************************************
//
// 3D�~�̏���[fan3D.h]
// Author:���R����
//
//*****************************************************

#ifndef _FAN3D_H_
#define _FAN3D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "fan.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CFan3D : public CFan
{
public:
	CFan3D(int nPriority = 5);
	~CFan3D();	//	�f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) override;	// ����������
	void Uninit(void) override;		// �I������
	void Update(void) override;		// �X�V����
	void Draw(void) override;		// �`�揈��
	void DrawNormal(void);			// �ʏ�`��
	void DrawBillboard(void);		// �r���{�[�h�`��
	void SetVtx(void) override;		// ���_�ݒ�
	void SetTex(float fScrollX, float fScrollY);      // �e�N�X�`�����W�ݒ菈��
	void SetCol(D3DXCOLOR col) override;
	void SetIdxTextureOverRay(int nIdx) { m_nIdxTextureOverRay = nIdx; }	// �I�[�o�[���C�e�N�X�`���ԍ��ݒ�
	void ResetMtxParent(void);		// �e�}�g���b�N�X�̃��Z�b�g

	// �ϐ��擾�E�ݒ�֐�
	D3DXMATRIX GetMatrixParent(void) { return m_mtxParent; }	// �e�}�g���b�N�X
	void SetMatrixParent(D3DXMATRIX mtx) { m_mtxParent = mtx; }

	// �ÓI�����o�֐�
	static CFan3D *Create(int nPriority = 3, int nNumVtx = 16);	// ��������

private:
	// �����o�ϐ�
	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxParent;	// �e�}�g���b�N�X
	bool m_bBillboard;				// �r���{�[�h���ǂ���
	int m_nStartOffsetCount;		// �g�p����g�`�̊J�n�ʒu�����炷�J�E���g
	int m_nIdxTextureOverRay;		// �I�[�o�[���C�e�N�X�`���̐ݒ�
};

#endif