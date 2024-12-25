//*****************************************************
//
// �`���[�g���A������[tutorial.h]
// Author:���R����
//
//*****************************************************
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "scene.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CTutorial : public CScene
{
public:
	CTutorial();	// �R���X�g���N�^
	~CTutorial();	// �f�X�g���N�^

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	
	// �ÓI�����o�֐�
	static CTutorial *GetInstance(void) { return s_pTutorial; }	// �C���X�^���X�擾

private:
	// �ÓI�����o�ϐ�
	static CTutorial *s_pTutorial;					// ���g�̃|�C���^
	
	// �����o�ϐ�
	bool m_bFade;
};

#endif