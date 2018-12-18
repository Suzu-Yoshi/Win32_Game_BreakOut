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

//+++++ �T�E���h�t�@�C���̎�� ++++++++++++++++++++
#define SOUND_KIND_BEEP		0	//Beep�֐�
#define SOUND_KIND_WAVE		1	//wave�t�@�C��
#define SOUND_KIND_MP3		2	//mp3�t�@�C��

//+++++ ���̑� ++++++++++++++++++++
#define MAX_STRING_NUM	512	//�ő啶����

//########## �\���� ##########

struct MY_STRUCT_SOUND {
	LPCWSTR			filepass;	//�T�E���h�t�@�C���̃p�X�Ɩ��O
	MCI_OPEN_PARMS	open;		//�T�E���h�t�@�C���̐ݒ���
	MCI_PLAY_PARMS	play;		//�T�E���h�t�@�C���̍Đ����
	int				fileKind;	//�T�E���h�t�@�C���̎��
	int				beepFreq;	//Beep�֐��F���g��
	int				beepMill;	//Beep�֐��F�Đ��~���b
};

//########## ���O�̍Ē�` ##########

typedef MY_STRUCT_SOUND	MY_SND;

//########## �O���[�o���ϐ� �Q�Ƃ̐錾 ##########

//���������� �{�̂�sound.cpp ����������

extern MY_SND MySnd_BGM_title;

//���������� �{�̂�sound.cpp ����������

//##########  �֐� �Q�Ƃ̐錾 ##########

//���������� �{�̂�sound.cpp ����������

extern VOID InitSoundParam(HWND hWnd);			//�T�E���h������������֐�
extern BOOL MY_SOUND_Read(HWND);				//�T�E���h��ǂݍ��ފ֐�
extern BOOL MY_SOUND_KIND_Read(HWND, MY_SND *);	//�T�E���h����ނ��Ƃɓǂݍ��ފ֐�
extern VOID MY_SOUND_Remove(VOID);				//�ǂݍ��񂾃T�E���h���폜����֐�
extern VOID MY_SOUND_PLAY(MY_SND MySnd);		//����炷�֐�

//���������� �{�̂�sound.cpp ����������