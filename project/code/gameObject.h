//*****************************************************
//
// �Q�[���I�u�W�F�N�g[gameObject.cpp]
// Author:���R����
//
//*****************************************************
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X��`
//*****************************************************
class CGameObject : public CObject
{
public:
	CGameObject(int nPriority = 4) : CObject(nPriority), m_pos(), m_rot() {};	// �R���X�g���N�^
	~CGameObject() {};	// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void) { return S_OK; }	// ������
	virtual void Uninit(void) { CObject::Release(); }	// �I��
	virtual void Update(void) {};	// �X�V
	virtual void Draw(void) {};	// �`��

	// �ϐ��擾�E�ݒ�֐�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �ʒu
	virtual void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void Translate(D3DXVECTOR3 pos) { m_pos += pos; }
	void Rotate(D3DXVECTOR3 rot) { m_rot += rot; universal::LimitRot(&m_rot.x); universal::LimitRot(&m_rot.y);universal::LimitRot(&m_rot.z);}
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	// ����
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

private:
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
};

#endif