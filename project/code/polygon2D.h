//*****************************************************
//
// 2D�|���S���̏���[polygon2D.h]
// Author:���R����
//
//*****************************************************
#ifndef _POLYGON2D_H_
#define _POLYGON2D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object2D.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPolygon2D	: public CObject2D
{
public:
	CPolygon2D(int nPriority = 5);	// �R���X�g���N
	~CPolygon2D();	//	�f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void AddMove(D3DXVECTOR3 move);	// �ړ��ʉ��Z����
	void DicMove(float fDicrease);	// �ړ��ʌ�������

	// �ϐ��擾�E�ݒ�֐�
	virtual void SetSize(float width, float height);	// �T�C�Y
	virtual D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2(m_width, m_heigth); }
	virtual void SetWidth(float width);
	virtual void SetHeight(float height);
	virtual float GetWidth(void) { return m_width; }	// ��
	virtual float GetHeight(void) { return m_heigth; }	// ����
	void SetAnim(int nAnim, int nNumAnim, int nNumV);	// �A�j���[�V����
	void SetTex(D3DXVECTOR2 texLeftUp, D3DXVECTOR2 texRightDown);	// �e�N�X�`�����W
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }	// ���_�o�b�t�@
	void SetMove(D3DXVECTOR3 move);	// �ړ��ʐݒ菈��
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }	// �O��̈ʒu
	D3DXVECTOR3 GetMove(void) { return m_move; }	// �ړ��ʎ擾����
	D3DXCOLOR GetCol(void) { return m_col; }	// �F
	float GetAlpha(void) { return m_col.a; }	// �����x
	void SetCol(D3DXCOLOR col);
	void SetAlpha(float fAlpha);
	void SetVtx(void);	// ���_���ݒ�
	void SetCenterHeight(float fHeight);	// ���S�̍���
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }	// �e�N�X�`���ԍ�
	int GetIdxTexture(void) { return m_nIdxTexture; }

	// �ÓI�����o�֐�
	static CPolygon2D *Create(int nPriority = 3, float fCenterHeight = 0.5f);	// ��������

private:
	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXCOLOR m_col;	// �F
	float m_width;	// ��
	float m_heigth;	// ����
	float m_fCenterHeight;	// ���S�̍���
	int m_nIdxTexture;	// �e�N�X�`���̔ԍ�
};

#endif