//*****************************************************
//
// �Q�[�W�̏���[gauge.h]
// Author:���R����
//
//*****************************************************
#ifndef _GAUGE_H_
#define _GAUGE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "gameObject.h"

//*****************************************************
// �O���錾
//*****************************************************
class CUI;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGauge : public CGameObject
{
public:
	CGauge();	// �R���X�g���N�^
	~CGauge();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������	
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void AddParam(float fValue);	// �p�����[�^�[���Z����

	// �ϐ��擾�E�ݒ�֐�
	void SetParam(float fParam) { m_fParam = fParam; }	// �p�����[�^�[
	float GetParam(void) { return m_fParam; }
	void SetPosition(D3DXVECTOR3 pos) override;	// �ʒu

	CUI* GetGauge(void) { return m_aPolygon[E_Polygon::POLYGON_GAUGE]; }	// �Q�[�W�|���S��
	void SetGauge(CUI* pUI) { m_aPolygon[E_Polygon::POLYGON_GAUGE] = pUI; }

	D3DXVECTOR2 GetGaugeSize(void) { return m_sizeGauge; }	// �Q�[�W�T�C�Y
	void SetGaugeSize(const float fWidth, const float fHeight) { m_sizeGauge.x = fWidth; m_sizeGauge.y = fHeight; }

	// �ÓI�����o�֐�
	static CGauge *Create(float fParamMax, const D3DXVECTOR2& size);	// ��������

private:
	// �񋓌^��`
	enum E_Polygon
	{// �|���S���̎��
		POLYGON_FRAME = 0,	// �t���[��
		POLYGON_GAUGE,	// �Q�[�W
		POLYGON_MAX
	};

	// �����o�֐�
	void CreatePolygon(void);	// �|���S���̐���
	void ManageGaugePolygon(void);	// �Q�[�W�|���S���̊Ǘ�

	// �����o�ϐ�
	vector<CUI*> m_aPolygon;	// 2D�|���S���̔z��
	float m_fParam;	// �p�����[�^�[�̌��݂̒l
	float m_fParamMax;	// �p�����[�^�[�̍ő�l
	float m_fTimerTransGauge;	// �Q�[�W�ϓ��̃^�C�}�[
	float m_fTimeLimitTransGauge;	// �Q�[�W�ϓ��̃^�C�����~�b�g
	float m_fWidthOld;	// �O��̕�
	D3DXVECTOR2 m_sizeGauge;	// �Q�[�W�̃T�C�Y
};

#endif