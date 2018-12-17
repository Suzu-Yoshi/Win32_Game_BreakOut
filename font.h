//����������������������������������������
//############ �u���b�N���� ##############
//font.h
//����������������������������������������

#pragma once

//########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <windows.h>

//########## �G���[���b�Z�[�W ##########

#define ERR_MSG_FONT_TITLE		TEXT("FONT_ERROR")

#define ERR_MSG_NO_READ_FONT	TEXT("�t�H���g��\
�ǂݍ��߂܂���ł���\n�v���O�������I�����܂�")

#define ERR_MSG_NO_REM_FONT	TEXT("�t�H���g��\
�폜�ł��܂���ł���\n�v���O�������I�����܂�")

//���ł�PC�ɃC���X�g�[������Ă���t�H���g
#define FNT_MS_GOTHIC TEXT("�l�r �S�V�b�N")

#define FNT_MS_MINCHO TEXT("�l�r ����")

//########## �ꎞ�I�ɓǂݍ��ރt�H���g ##########

#define FNT_JUD_PASS	TEXT(".\\MY_FONT\\JUDGE2.TTF")
#define FNT_JUD_NAME	TEXT("Judge Hard")

#define FNT_TANU_PASS	TEXT(".\\MY_FONT\\TanukiMagic.ttf")
#define FNT_TANU_NAME	TEXT("���ʂ������}�W�b�N")

//########## �v���g�^�C�v�錾 ##########

//�t�H���g���ꎞ�I�ɓǂݍ���
extern BOOL OnceFont_Read(HWND);

//�t�H���g���쐬����
extern HFONT MY_CreateFont(HDC, LPCTSTR, int, int, int);

//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜����
extern VOID OnceFont_Remove(HWND);