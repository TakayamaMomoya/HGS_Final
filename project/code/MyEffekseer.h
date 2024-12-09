//===========================================================
//
// �}�C�G�t�F�N�V�A[MyEffekseer.h]
// Author : ���R����
//
//===========================================================
#ifndef _EFFEKSEER_H_
#define _EFFEKSEER_H_

//***********************************************************
// �C���N���[�h
//***********************************************************
#include "object.h"

//***********************************************************
// �O���錾
//***********************************************************
class CEffekseerEffect;

//***********************************************************
// �N���X�̒�`
//***********************************************************
class CMyEffekseer
{// �G�t�F�N�V�A�̃}�l�[�W���[
public:
	CMyEffekseer();
	~CMyEffekseer();

	enum TYPE
	{// ���
		TYPE_NONE = 0,		// �Ȃ���Ȃ�
		TYPE_PECKWAVE,		// �����g��
		TYPE_RIPPLESTRINGS,	// �����g
		TYPE_RIPPLE,		// �g��
		TYPE_BEARSTEP,		// �V���N�}�̕�����
		TYPE_BLIZZARD,		// ����
		TYPE_ICEBREAK,		// �X������Ƃ�
		TYPE_JUMP,			// �W�����v
		TYPE_DROP,			// �����Ԃ�
		TYPE_MAX
	};

	// �����o�֐�
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CEffekseerEffect *CreateEffect(const char* FileName, ::Effekseer::Vector3D pos, ::Effekseer::Vector3D rot, ::Effekseer::Vector3D scale);
	::EffekseerRendererDX9::RendererRef GetEffekseerRenderer(void) { return m_efkRenderer; }
	::Effekseer::ManagerRef GetEfkManager(void) { return m_efkManager; }
	void SetupEffekseerModules(::Effekseer::ManagerRef efkManager);
	void Release(int idx);
	void ReleaseEffect(CEffekseerEffect *pEffect);	// �G�t�F�N�g�̉��
	void StopAllEffect(void) { m_efkManager->StopAllEffects(); };					// �S�G�t�F�N�g�̒�~
	const char* GetPathEffect(CMyEffekseer::TYPE type);
	std::list<CEffekseerEffect*> *GetList(void) { return &m_listEffect; };	// ���X�g�̎擾

	Effekseer::Matrix44 GetMtxCamera(void) { return m_cameraMatrix; }
	Effekseer::Matrix44 GetMtxProj(void) { return m_projectionMatrix; }
	Effekseer::Vector3D GetPosView(void) { return m_viewerPosition; }

	// �ÓI�����o�֐�
	static CMyEffekseer *Create(void);
	static CMyEffekseer *GetInstance(void) { return s_pMyEffekseer; }	// �C���X�^���X�擾

private:
	// �����o�ϐ�
	EffekseerRendererDX9::RendererRef m_efkRenderer;
	Effekseer::Matrix44 m_cameraMatrix;
	Effekseer::Matrix44 m_projectionMatrix;
	Effekseer::ManagerRef m_efkManager;
	Effekseer::Vector3D m_viewerPosition;
	int m_nNum;
	std::list<CEffekseerEffect*> m_listEffect;	// �G�t�F�N�g�N���X�̃��X�g

	// �ÓI�����o�ϐ�
	static const char* m_apEfkName[CMyEffekseer::TYPE_MAX];
	static CMyEffekseer *s_pMyEffekseer;		// ���g�̃|�C���^
};

class CEffekseerEffect
{
public:
	CEffekseerEffect(int nPriority = 5);	// �R���X�g���N�^
	~CEffekseerEffect();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void) { return S_OK; }
	HRESULT Init(::Effekseer::Vector3D pos, ::Effekseer::Vector3D rot, ::Effekseer::Vector3D scale);	// ������
	void Update(void);	// �X�V����
	void Draw(void);	// �`��
	void Uninit(void);	// �I������
	CEffekseerEffect *FollowPosition(D3DXVECTOR3 pos);	// �ʒu�̒Ǐ]

	// �ϐ��擾�E�ݒ�֐�
	void SetEffect(Effekseer::EffectRef effect) { m_effect = effect; }	// �G�t�F�N�g�Q��
	Effekseer::EffectRef GetEffect(void) { return m_effect; }
	void SetHandle(Effekseer::Handle handle) { m_efkHandle = handle; }	// �n���h��
	Effekseer::Handle GetHandle(void) { return m_efkHandle; }
	void SetTime(int32_t time) { m_time = time; }	// ����
	int32_t GetTime(void) { return m_time; }
	Effekseer::Vector3D GetPositionVector3(void) { return m_pos; }	// �ʒu
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(m_pos.X, m_pos.Y, m_pos.Z); }
	void SetPosition(Effekseer::Vector3D pos) { m_pos = pos; }
	Effekseer::Vector3D GetRotation(void) { return m_rot; }	// ����
	D3DXVECTOR3 GetRotationD3D(void) { return D3DXVECTOR3(m_rot.X, m_rot.Y, m_rot.Z); }
	void SetRotation(Effekseer::Vector3D rot) { m_rot = rot; }
	Effekseer::Vector3D GetScale(void) { return m_scale; }	// �X�P�[��
	void SetScale(Effekseer::Vector3D scale) { m_scale = scale; }

private:
	// �����o�ϐ�
	Effekseer::Vector3D m_pos;       // �ʒu
	Effekseer::Vector3D m_rot;       // ����
	Effekseer::Vector3D m_scale;     // �傫��
	Effekseer::EffectRef m_effect;   // �G�t�F�N�g
	Effekseer::Handle m_efkHandle;   // �n���h��
	const char* m_EfkName;           // ���O
	int32_t m_time;                  // ����
};

namespace MyEffekseer
{
CEffekseerEffect *CreateEffect(CMyEffekseer::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f }, D3DXVECTOR3 scale = { 100.0f,100.0f,100.0f });
}
#endif