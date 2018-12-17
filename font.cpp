//����������������������������������������
//############ �u���b�N���� ##############
//font.cpp
//����������������������������������������

//########## �w�b�_�t�@�C���ǂݍ��� ##########
#include "font.h"

//########## �ꎞ�I�Ƀt�H���g��ǂݍ��ފ֐� ##########
BOOL OnceFont_Read(HWND hWnd)
{
	//judge hard�t�H���g���ꎞ�I�ɓǂݍ���
	if (AddFontResourceEx(FNT_JUD_PASS, FR_PRIVATE, NULL) == 0)
	{
		//�t�H���g���ǂݍ��߂Ȃ������Ƃ�
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	//���ʂ������}�W�b�N�t�H���g���ꎞ�I�ɓǂݍ���
	if (AddFontResourceEx(FNT_TANU_PASS, FR_PRIVATE, NULL) == 0)
	{
		//�t�H���g���ǂݍ��߂Ȃ������Ƃ�
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

//########## �t�H���g��ݒ肷��֐� ##########
HFONT MY_CreateFont(HDC hdc, LPCTSTR fontName, int size, int angle, int charset)
{

	HFONT hFont;
	hFont = CreateFont(
		size,					//�t�H���g�̍��� / 0�Ȃ�f�t�H���g(�傫��)
		0,						//������		 / 0�Ȃ玩���v�Z

		angle,					//�e�L�X�g�̊p�x
								//�������甽���v���� 1/10 �x�P�ʂŊp�x���w��
								//   0(  0�x) �Ȃ�� ������E�֕`��
								// 900( 90�x) �Ȃ�� �������֕`��
								//1800(180�x) �Ȃ�� �E���獶�֕`��
								//2700(270�x) �Ȃ�� �ォ�牺�֕`��

		0,						//�x�[�X���C���Ƃ����Ƃ̊p�x
		FW_REGULAR,				//�t�H���g�̏d���i�����j
		FALSE,					//�C�^���b�N��
		FALSE,					//�A���_�[���C��
		FALSE,					//�ł�������

		charset,				//�����Z�b�g
								//ANSI      ���g���Ȃ�� ANSI_CHARSET
								//Shift-JIS ���g���Ȃ�� SHIFTJIS_CHARSET
								//�f�t�H���g���g���Ȃ�� DEFAULT_CHARSET

		OUT_DEFAULT_PRECIS,	//�o�͐��x
		CLIP_DEFAULT_PRECIS,	//�N���b�s���O���x
		PROOF_QUALITY,			//�o�͕i��
		FIXED_PITCH | FF_MODERN,//�s�b�`�ƃt�@�~���[
		fontName);				//�t�H���g�̏��̖�

	return hFont;
}

//########## �ꎞ�I�ȃt�H���g���폜����֐� ##########
VOID OnceFont_Remove(HWND hWnd)
{
	//�ꎞ�I�ɓǂݍ��� judge hard�t�H���g���폜
	RemoveFontResourceEx(FNT_JUD_PASS, FR_PRIVATE, NULL);

	//�ꎞ�I�ɓǂݍ��� ���ʂ������}�W�b�N�t�H���g���폜
	RemoveFontResourceEx(FNT_TANU_PASS, FR_PRIVATE, NULL);

	return;
}