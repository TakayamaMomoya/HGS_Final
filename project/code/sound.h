//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���R����
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	typedef enum
	{
		LABEL_BGM_TITLE,				// �^�C�g��BGM
		LABEL_BGM_TUTORIAL,				// �`���[�g���A��BGM
		LABEL_BGM_GAME01,				// �Q�[��BGM01
		LABEL_BGM_RESULT,				// ���U���gBGM
		LABEL_BGM_OPTION,				// �I�v�V����BGM

		LABEL_SE_COUNTDOWN,				// �J�E���g�_�E��
		LABEL_SE_COUNTSTART,			// �J�n���X�^�[�g
		LABEL_SE_PENGUIN_JUMP,			// �y���M���W�����v
		LABEL_SE_SEA,					// �Â��ȊC�i���j
		LABEL_SE_BREAK_ICE,				// �X�j��
		LABEL_SE_SEAL_CRY,				// �A�U���V����
		LABEL_SE_SEA_SPLASH_01,			// �G���C����オ���Ă����i�d�˂���1�j
		LABEL_SE_SEA_SPLASH_02,			// �G���C����オ���Ă����i�d�˂���2�j
		LABEL_SE_ICE_CHAIN,				// �X���m�Ԃ�����
		LABEL_SE_DECISION,				// ���艹
		LABEL_SE_SELECT,				// �I����
		LABEL_SE_PENGUIN_VOICE00,		// �y���M���̖���1
		LABEL_SE_PENGUIN_VOICE01,		// �y���M���̖���2
		LABEL_SE_FLAPPING_WING,			// �y���M���̉H�΂�����
		LABEL_SE_PENGUIN_WALKING,		// �y���M���̕�����
		LABEL_SE_POLARBEAR_VOICE,		// �V���N�}����
		LABEL_SE_POLARBEAR_ASSALT,		// �V���N�}�ˌ�
		LABEL_SE_ALBATROSS,				// �A�z�E�h������

		LABEL_SE_PAUSE_MENU,			// �|�[�Y
		LABEL_SE_PAUSE_ARROW,			// �ړ�
		LABEL_SE_PAUSE_ENTER00,			// ����
		LABEL_SE_PAUSE_ENTER01,			// ����

		LABEL_SE_GAME_START,			// �Q�[���X�^�[�g

		LABEL_SE_TITLE_FADE,			// �^�C�g���t�F�[�h
		LABEL_SE_STAGE_ENTRY,			// �X�e�[�W�ɓ����Ă�����

		LABEL_MAX
	} LABEL;
	typedef enum
	{
		FADESTATE_NONE = 0,	//�������Ă��Ȃ����
		FADESTATE_IN,	//�t�F�[�h�C�����
		FADESTATE_OUT,	//�t�F�[�h�A�E�g���
		FADESTATE_MAX
	}FADESTATE;

	CSound();	// �R���X�g���N�^
	~CSound();	// �f�X�g���N�^

	static CSound *Create(HWND hWnd);
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);

	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void Stop(void);

	void SetVolume(LABEL label, float fVolume);
	void SetFade(LABEL LabelNow, LABEL LabelNext, float fSpeed);

	static CSound *GetInstance(void) { return m_pSound; }

private:
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX];	// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];	// �I�[�f�B�I�f�[�^�T�C�Y
	FADESTATE m_fadeSound;	// �t�F�[�h���
	LABEL m_SoundLabelNow;	// ���݂̃T�E���h���x��
	LABEL m_SoundLabelNext;	// ���̃T�E���h���x��
	float m_fSpeedFadeSound;	// �T�E���h���t�F�[�h����X�s�[�h
	float m_fVolumeSound;	// �T�E���h�̃{�����[��

	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[LABEL_MAX] =
	{
		{ "data/SOUND/BGM/BGM_Title.wav",-1 },			// �^�C�g�����BGM
		{ "data/SOUND/BGM/BGM_Result.wav",-1 },			// �`���[�g���A�����BGM�i���j
		{ "data/SOUND/BGM/BGM_Game00.wav",-1 },			// �Q�[�����BGM
		{ "data/SOUND/BGM/BGM_Result.wav",-1 },			// ���U���g���BGM
		{ "data/SOUND/BGM/BGM_Option.wav",-1 },			// �I�v�V�������BGM

		{ "data/SOUND/SE/SE_Count.wav",0 },				// �J�E���g�_�E��
		{ "data/SOUND/SE/SE_Start.wav",0 },				// �J�n���X�^�[�g
		{ "data/SOUND/SE/SE_Penguin_Jump.wav",0 },		// �y���M���W�����v
		{ "data/SOUND/SE/SE_Sea.wav",0 },				// �Â��ȊC
		{ "data/SOUND/SE/SE_Break_Ice.wav",0 },			// �X�j��
		{ "data/SOUND/SE/SE_Seal_Cry.wav",0 },			// �A�U���V����
		{ "data/SOUND/SE/SE_SeaSplash_01.wav",0 },		// �G���C����オ���Ă����i�d�˂���1�j
		{ "data/SOUND/SE/SE_SeaSplash_02.wav",0 },		// �G���C����オ���Ă����i�d�˂���2�j
		{ "data/SOUND/SE/SE_Ice_Union.wav",0 },			// �X���m�Ԃ�����
		{ "data/SOUND/SE/SE_Decision.wav",0 },			// ���艹
		{ "data/SOUND/SE/SE_Select.wav",0 },			// �I����
		{ "data/SOUND/SE/SE_Penguin_Voice00.wav",0 },	// �y���M������1
		{ "data/SOUND/SE/SE_Penguin_Voice01.wav",0 },	// �y���M������2
		{ "data/SOUND/SE/SE_flapping_wing.wav",0 },		// �y���M���̉H�΂�����
		{ "data/SOUND/SE/SE_Walking_Sound.wav",0 },		// �y���M���̕�����
		{ "data/SOUND/SE/SE_Polarbear_Voice.wav",0 },	// �V���N�}����
		{ "data/SOUND/SE/SE_Polarbear_Assault.wav",0 },	// �V���N�}�ˌ�
		{ "data/SOUND/SE/SE_Albatross.wav",0 },			// �A�z�E�h������

		{ "data/SOUND/SE/pause.wav",0 },				// �|�[�Y
		{ "data/SOUND/SE/SE_ENTER00.wav",0 },			// �I��
		{ "data/SOUND/SE/SE_Enter01.wav",0 },			// ����
		{ "data/SOUND/SE/SE_Enter02.wav",0 },			// ����

		{ "data/SOUND/SE/SE_GameStart.wav",0 },			// �Q�[���X�^�[�g

		{ "data/SOUND/SE/SE_Fade.wav",0 },				// �^�C�g���t�F�[�h��
		{ "data/SOUND/SE/SE_StageEntry.wav",-1 },				// �^�C�g���t�F�[�h��
	};

	static CSound *m_pSound;	// ���g�̃|�C���^
};

namespace Sound
{
void Play(CSound::LABEL label);
}

#endif