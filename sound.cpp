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

VOID InitSoundParam(HWND hWnd);				//�T�E���h������������֐�
BOOL MY_SOUND_Read(HWND);					//�T�E���h��ǂݍ��ފ֐�
BOOL MY_SOUND_KIND_Read(HWND , MY_SND *);	//�T�E���h����ނ��Ƃɓǂݍ��ފ֐�
VOID MY_SOUND_Remove(VOID);					//�ǂݍ��񂾃T�E���h���폜����֐�
VOID MY_SOUND_PLAY(MY_SND MySnd);			//����炷�֐�
//########## �T�E���h������������֐� ##########
VOID InitSoundParam(HWND hWnd)
{

	//+++++ �^�C�g����ʂ�BGM ++++++++++++++++++++

	MySnd_BGM_title.filepass = TEXT(SOUND_BGM_MP3_1);
	MySnd_BGM_title.fileKind = SOUND_KIND_MP3;


}

//########## �T�E���h��ǂݍ��ފ֐� ##########
BOOL MY_SOUND_Read(HWND hWnd)
{
	//�^�C�g����ʂ�BGM
	if (MY_SOUND_KIND_Read(hWnd, &MySnd_BGM_title) == FALSE)
	{	return FALSE;	}
	
	return TRUE;
}

//########## �T�E���h����ނ��Ƃɓǂݍ��ފ֐� ##########
BOOL MY_SOUND_KIND_Read(HWND hWnd, MY_SND *MySnd)
{
	int res_sound;	//�ǂݍ��݂̌��ʂ�ۑ�

	switch (MySnd->fileKind)
	{

	case SOUND_KIND_BEEP:

		break;

	case SOUND_KIND_WAVE:

		//wave�̏���ݒ�
		MySnd->open.lpstrDeviceType = (LPCWSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
		MySnd->open.lpstrElementName = MySnd->filepass;

		//wave���擾
		res_sound = mciSendCommand(
			0,
			MCI_OPEN,			//�f�o�C�X���I�[�v��
			MCI_OPEN_TYPE		//wave�t�@�C���̏ꍇ
			| MCI_OPEN_TYPE_ID	//wave�t�@�C���̏ꍇ
			| MCI_OPEN_ELEMENT,	//wave�t�@�C���̏ꍇ
			(DWORD_PTR)&MySnd->open);

		//wave���ǂݍ��߂Ȃ������Ƃ�
		if (res_sound)
		{
			MessageBox(hWnd, ERR_MSG_NO_READ_WAVE, ERR_MSG_SND_TITLE, MB_OK);
			return FALSE;
		}

		//�E�B���h�E�v���V�[�W���̃E�B���h�E�n���h����ݒ�
		MySnd->play.dwCallback = (DWORD)hWnd;

		break;

	case SOUND_KIND_MP3:

		//MP3�̏���ݒ�
		MySnd->open.lpstrDeviceType = TEXT("MPEGVideo");
		MySnd->open.lpstrElementName = MySnd->filepass;

		//MP3���擾
		res_sound = mciSendCommand(
			0,
			MCI_OPEN, 			//�f�o�C�X���I�[�v��
			MCI_OPEN_TYPE		//MP3�t�@�C���̏ꍇ
			| MCI_OPEN_ELEMENT,	//MP3�t�@�C���̏ꍇ
			(DWORD_PTR)&MySnd->open);

		//MP3���ǂݍ��߂Ȃ������Ƃ�
		if (res_sound)
		{
			MessageBox(hWnd, ERR_MSG_NO_READ_MP3, ERR_MSG_SND_TITLE, MB_OK);
			return FALSE;
		}

		//�E�B���h�E�v���V�[�W���̃E�B���h�E�n���h����ݒ�
		MySnd->play.dwCallback = (DWORD)hWnd;

		break;
	}

	return TRUE;
}

//########## �ǂݍ��񂾃T�E���h���폜����֐� ##########
VOID MY_SOUND_Remove(VOID)
{
	//�^�C�g����ʂ�BGM
	mciSendCommand(MySnd_BGM_title.open.wDeviceID, MCI_CLOSE, 0, 0);

}

//########## ����炷�֐� ##########
VOID MY_SOUND_PLAY(MY_SND MySnd)
{
	//�Đ������Ǘ�
	MCI_STATUS_PARMS mciStatus;

	//�Đ������擾
	mciStatus.dwItem = MCI_STATUS_MODE;
	mciSendCommand(MySnd.open.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&mciStatus);

	//�Đ����Ă��Ȃ��Ƃ�
	if (mciStatus.dwReturn != MCI_MODE_PLAY)
	{
		//�Đ�����
		mciSendCommand(
			MySnd.open.wDeviceID,
			MCI_PLAY,
			MCI_NOTIFY,
			(DWORD_PTR)&MySnd.play
		);
	}

	return;
}