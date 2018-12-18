//����������������������������������������
//sound.cpp
//����������������������������������������

//########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <windows.h>

#include <mmsystem.h>
#include<digitalv.h>
#pragma comment (lib, "winmm.lib")

#include "sound.h"

//########## �O���[�o���ϐ��̐錾�Ə����� ##########
MY_SND MySnd_BGM_title;

//########## �v���g�^�C�v�錾 ##########

BOOL MY_SOUND_Read(HWND , MY_SND );	//���y��ǂݍ��ފ֐�
VOID MY_SOUND_Remove(MY_SND );		//�ǂݍ��񂾉��y���폜����֐�

//########## ���y��ǂݍ��ފ֐� ##########
VOID InitSoundParam(HWND hWnd)
{

	//+++++ �^�C�g����ʂ�BGM ++++++++++++++++++++

	wsprintf(MySnd_BGM_title.filepass,TEXT(SOUND_BGM_MP3_1));


	MY_SOUND_Read(hWnd, MySnd_BGM_title)

}

//########## ���y��ǂݍ��ފ֐� ##########
BOOL MY_SOUND_Read(HWND hWnd, MY_SND MySnd)
{
	int res_sound;	//�ǂݍ��݂̌��ʂ�ۑ�

	switch (MySnd.fileKind)
	{

	case SOUND_KIND_BEEP:

		break;

	case SOUND_KIND_WAVE:

		//wave�̏���ݒ�
		MySnd.open.lpstrDeviceType = (LPCWSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
		MySnd.open.lpstrElementName = MySnd.filepass;

		//wave���擾
		mciSendCommand(
			0,
			MCI_OPEN,			//�f�o�C�X���I�[�v��
			MCI_OPEN_TYPE		//wave�t�@�C���̏ꍇ
			| MCI_OPEN_TYPE_ID	//wave�t�@�C���̏ꍇ
			| MCI_OPEN_ELEMENT,	//wave�t�@�C���̏ꍇ
			(DWORD_PTR)&MySnd.open);

		//wave���ǂݍ��߂Ȃ������Ƃ�
		if (res_sound)
		{
			MessageBox(hWnd, ERR_MSG_NO_READ_WAVE, ERR_MSG_SND_TITLE, MB_OK);
			return FALSE;
		}

		//�E�B���h�E�v���V�[�W���̃E�B���h�E�n���h����ݒ�
		MySnd.play.dwCallback = (DWORD)hWnd;

		break;

	case SOUND_KIND_MP3:

		//MP3�̏���ݒ�
		MySnd.open.lpstrDeviceType = TEXT("MPEGVideo");
		MySnd.open.lpstrElementName = MySnd.filepass;

		//MP3���擾
		res_sound = mciSendCommand(
			0,
			MCI_OPEN, 			//�f�o�C�X���I�[�v��
			MCI_OPEN_TYPE		//MP3�t�@�C���̏ꍇ
			| MCI_OPEN_ELEMENT,	//MP3�t�@�C���̏ꍇ
			(DWORD_PTR)&MySnd.open);

		//MP3���ǂݍ��߂Ȃ������Ƃ�
		if (res_sound)
		{
			MessageBox(hWnd, ERR_MSG_NO_READ_MP3, ERR_MSG_SND_TITLE, MB_OK);
			return FALSE;
		}

		//�E�B���h�E�v���V�[�W���̃E�B���h�E�n���h����ݒ�
		MySnd.play.dwCallback = (DWORD)hWnd;

		break;
	}

	return TRUE;
}


//########## �ǂݍ��񂾉��y���폜����֐� ##########
VOID MY_SOUND_Remove(MY_SND MySnd)
{
	//���y�t�@�C�������
	mciSendCommand(MySnd.open.wDeviceID, MCI_CLOSE, 0, 0);
}