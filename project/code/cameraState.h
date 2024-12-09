//*****************************************************
//
// �J�����X�e�C�g[cameraState.h]
// Author:���R����
//
//*****************************************************

#ifndef _CAMERASTATE_H_
#define _CAMERASTATE_H_

//****************************************************
// �O���錾
//****************************************************
class CCamera;
class CSelectStagePenguin;

//****************************************************
// �N���X�̒�`
//****************************************************
// ���N���X
class CCameraState
{
public:
	CCameraState() {};
	virtual void Init(CCamera *pCamera) = 0;
	virtual void Update(CCamera *pCamera) = 0;

private:
};

// �v���C���[�Ǐ]
class CFollowPlayer : public CCameraState
{
public:
	CFollowPlayer();
	void Init(CCamera *pCamera) {};
	void Update(CCamera *pCamera) override;

private:
	float m_fTimerPosR;
	float m_fLengthPosR;
	D3DXVECTOR3 m_rotROld;
	bool m_bDebug;
};

// �}���`���[�h
class CMultiGame : public CCameraState
{
public:
	CMultiGame();
	void Init(CCamera* pCamera) {};
	void Update(CCamera* pCamera) override;

private:

};

// ����
class CMoveControl : public CCameraState
{
public:
	CMoveControl() {};
	void Init(CCamera *pCamera) {};
	void Update(CCamera *pCamera) override;

private:
	bool m_bAbove = false;	// ��󎋓_���ǂ���
};

// �^�C�g��
class CCameraStateTitle : public CCameraState
{
public:
	CCameraStateTitle() {};
	void Init(CCamera *pCamera) {};
	void Update(CCamera* pCamera) override;

private:

};

// �X�e�[�W�Z���N�g��
class CCameraStateSelectStage : public CCameraState
{
public:
	CCameraStateSelectStage(CSelectStagePenguin *pPenguin) { m_pPenguin = pPenguin; }
	void Init(CCamera *pCamera);
	void Update(CCamera* pCamera) override;

private:
	CSelectStagePenguin *m_pPenguin;
};

// �V���O�����U���g��
class CResultSingle;
class CCameraResultSingle : public CCameraState
{
public:
	CCameraResultSingle(CResultSingle *pResult);
	void Init(CCamera *pCamera);
	void Update(CCamera* pCamera) override;

private:
	// �萔��`
	static constexpr float TIME_MOVE = 5.0f;	// �ړ��ɂ����鎞��

	// �����o�֐�
	void DecidePosDest(CCamera* pCamera);	// �ڕW�ʒu�̌���
	void MoveToPlayerFront(CCamera* pCamera);	// �v���C���[�̑O�܂ňړ����鏈��

	// �����o�ϐ�
	D3DXVECTOR3 m_posDest;	// �ڕW�ʒu
	D3DXVECTOR3 m_posInitiial;	// �����ʒu�ʒu
	D3DXVECTOR3 m_vecDiffInitial;	// ���������x�N�g��
	float m_fTimerMove;	// �ړ��^�C�}�[
	CResultSingle *m_pResult;	// ���U���g�̃|�C���^
};

// �}���`���[�h�̃��U���g
class CCameraStateResultMulti : public CCameraState
{
public:
	CCameraStateResultMulti() {}
	void Init(CCamera* pCamera);
	void Update(CCamera* pCamera) override;
private:

};

// ���[�h�I�����
class CCameraStateSelectMode : public CCameraState
{
public:
	CCameraStateSelectMode(){}
	void Init(CCamera* pCamera);
	void Update(CCamera* pCamera) override;
private:

};

#endif