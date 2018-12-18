//����������������������������������������
//sound.h
//����������������������������������������

//########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <windows.h>

//########## �}�N����` ##########

//+++++ �ǂݍ��݃G���[ ++++++++++++++++++++

#define ERR_MSG_SND_TITLE		TEXT("SOUND_ERROR")

#define ERR_MSG_NO_READ_WAVE	TEXT("WAVE�t�@�C����\
�ǂݍ��߂܂���ł���\n�v���O�������I�����܂�")

#define ERR_MSG_NO_READ_MP3		TEXT("MP3�t�@�C����\
�ǂݍ��߂܂���ł���\n�v���O�������I�����܂�")

//+++++ ���ʉ� ++++++++++++++++++++
#define SOUND_KOUKA_1		TEXT(".\\MY_SOUND\\don.wav")
#define SOUND_KOUKA_2		TEXT(".\\MY_SOUND\\chime.wav")

#define SOUND_KOUKA_MP3_1	TEXT(".\\MY_SOUND\\magical_1.mp3")
#define SOUND_KOUKA_MP3_2	TEXT(".\\MY_SOUND\\magical_2.mp3")

//+++++ BGM ++++++++++++++++++++
#define SOUND_BGM_MP3_1		".\\MY_SOUND\\magical_1.mp3"

//+++++ ���y�t�@�C���̎�� ++++++++++++++++++++
#define SOUND_KIND_BEEP		0	//Beep�֐�
#define SOUND_KIND_WAVE		1	//wave�t�@�C��
#define SOUND_KIND_MP3		2	//mp3�t�@�C��

//+++++ ���̑� ++++++++++++++++++++
#define MAX_STRING_NUM	512	//�ő啶����

//########## �\���� ##########

struct MY_STRUCT_SOUND {
	TCHAR			filepass;	//���y�t�@�C���̃p�X�Ɩ��O
	MCI_OPEN_PARMS	open;		//���y�t�@�C���̐ݒ���
	MCI_PLAY_PARMS	play;		//���y�t�@�C���̍Đ����
	int				fileKind;	//���y�t�@�C���̎��
	int				beepFreq;	//Beep�֐��F���g��
	int				beepMill;	//Beep�֐��F�Đ��~���b
};

//########## ���O�̍Ē�` ##########

typedef MY_STRUCT_SOUND	MY_SND;

//##########  �֐� �Q�Ƃ̐錾 ##########

//���������� �{�̂�sound.cpp ����������

extern BOOL MY_SOUND_Read(HWND, MY_SND);	//���y��ǂݍ��ފ֐�
extern VOID MY_SOUND_Remove(MY_SND);		//�ǂݍ��񂾉��y���폜����֐�

//���������� �{�̂�sound.cpp ����������