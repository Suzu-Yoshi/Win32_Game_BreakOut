//����������������������������������������
//text.cpp
//����������������������������������������

//########## �w�b�_�t�@�C���ǂݍ��� ##########

#include <Windows.h>

#include "text.h"
#include "fps.h"
#include "game.h"	

//########## �O���[�o���ϐ��̐錾�Ə����� ##########

//�e�L�X�g�\���̂̕ϐ�
MY_TEXT MyText_name;		//���O
MY_TEXT MyText_title;		//�^�C�g��
MY_TEXT MyText_title_st;	//�X�^�[�g

//########## �e�L�X�g������������֐� ##########
VOID InitTextParam(VOID)
{
	//+++++ �^�C�g���̕��� ++++++++++++++++++++

	wsprintf(MyText_name.string, TEXT(GAME_MY_NAME));
	wsprintf(MyText_name.fontname, FNT_GOD_NAME);
	MyText_name.charset = ANSI_CHARSET;

	//�ꏊ
	MyText_name.rect.left = GAME_POS_X;
	MyText_name.rect.top = GAME_POS_Y;
	MyText_name.rect.right = GAME_RIGHT;
	MyText_name.rect.bottom = GAME_BOTTOM / 2;

	MyText_name.size = 70;
	MyText_name.bold = MOJI_REGU;
	MyText_name.ita = FALSE;
	MyText_name.ul = FALSE;
	MyText_name.st = FALSE;
	MyText_name.align = TEXT_ALIGN_C_CENTER;

	MyText_name.bkcolor = RGB(0, 0, 0);	//�w�i�F
	MyText_name.color = RGB(255, 255, 255);//�����F
	MyText_name.bkmode = MOJI_BKMD_TRAN;	//�w�i���[�h

	MyText_name.blk = FALSE;

	//+++++ �^�C�g���̕��� ++++++++++++++++++++

	wsprintf(MyText_title.string, TEXT(GAME_TITLE));
	wsprintf(MyText_title.fontname, FNT_GOD_NAME);
	MyText_title.charset = ANSI_CHARSET;

	//�ꏊ
	MyText_title.rect.left = GAME_POS_X;
	MyText_title.rect.top = GAME_POS_Y;
	MyText_title.rect.right = GAME_RIGHT;
	MyText_title.rect.bottom = GAME_BOTTOM / 2;

	MyText_title.size = 80;
	MyText_title.bold = MOJI_REGU;
	MyText_title.ita = FALSE;
	MyText_title.ul = FALSE;
	MyText_title.st = FALSE;
	MyText_title.align = TEXT_ALIGN_D_CENTER;

	MyText_title.bkcolor = RGB(0, 0, 0);	//�w�i�F
	MyText_title.color = RGB(255, 255, 255);//�����F
	MyText_title.bkmode = MOJI_BKMD_TRAN;	//�w�i���[�h

	MyText_title.blk = FALSE;

	//+++++ �^�C�g���̃X�^�[�g���� ++++++++++++++++++++

	wsprintf(MyText_title_st.string, TEXT(GAME_TITLE_START));
	wsprintf(MyText_title_st.fontname, FNT_GOD_NAME);
	MyText_title_st.charset = ANSI_CHARSET;

	//�ꏊ
	MyText_title_st.rect.left = GAME_POS_X;
	MyText_title_st.rect.top = GAME_BOTTOM / 2;
	MyText_title_st.rect.right = GAME_RIGHT;
	MyText_title_st.rect.bottom = GAME_BOTTOM / 2;

	MyText_title_st.size = 50;
	MyText_title_st.bold = MOJI_REGU;
	MyText_title_st.ita = FALSE;
	MyText_title_st.ul = TRUE;
	MyText_title_st.st = FALSE;
	MyText_title_st.align = TEXT_ALIGN_C_CENTER;

	MyText_title_st.bkcolor = RGB(0, 0, 0);		//�w�i�F
	MyText_title_st.color = RGB(255, 255, 255);	//�����F
	MyText_title_st.bkmode = MOJI_BKMD_TRAN;	//�w�i���[�h

	MyText_title_st.blk = TRUE;
	MyText_title_st.blk_cnt = 0;
	MyText_title_st.blk_on_spd = FPS_DISP * 2;
	MyText_title_st.blk_off_spd = FPS_DISP / 2;
	MyText_title_st.blk_state = TRUE;

	return;
}

//########## �e�L�X�g��\������֐� ##########
VOID MY_TextOut(HDC hdc, MY_TEXT *MyText)
{
	//�t�H���g�̏ڍ׏��
	TEXTMETRIC tm;

	//�����̑傫�����
	SIZE sz;
	int text_left;	//������X���W
	int text_top;	//������Y���W

	//�t�H���g���쐬
	MyText->hfont = MY_CreateFont(hdc, MyText);

	//�t�H���g��ݒ肷��
	SelectObject(hdc, MyText->hfont);

	//�t�H���g�̏ڍ׏����擾
	GetTextMetrics(hdc, &tm);

	SetTextColor(hdc, MyText->bkcolor);	//�w�i�F
	SetTextColor(hdc, MyText->color);	//�����F
	SetBkMode(hdc, MyText->bkmode);		//�w�i���[�h

	//�����̑傫�����擾
	GetTextExtentPoint32(
		hdc,
		MyText->string,
		lstrlen(MyText->string),
		&sz);

	//�\�����@
	switch (MyText->align)
	{

	case TEXT_ALIGN_U_LEFT:
		//�c�F�㑵���@/���F������

		text_left = MyText->rect.left;
		text_top = MyText->rect.top;

		break;

	case TEXT_ALIGN_U_CENTER:
		//�c�F�㑵���@/���F��������

		text_left = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		text_top = MyText->rect.top;

		break;

	case TEXT_ALIGN_U_RIGHT:
		//�c�F�㑵���@/���F�E����

		text_left = MyText->rect.left + MyText->rect.right - sz.cx;
		text_top = MyText->rect.top;

		break;

	case TEXT_ALIGN_C_LEFT:
		//�c�F��������/���F������

		text_left = MyText->rect.left;
		text_top = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_CENTER:
		//�c�F��������/���F��������

		text_left = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		text_top = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_RIGHT:
		//�c�F��������/���F�E����

		text_left = MyText->rect.left + MyText->rect.right - sz.cx;
		text_top = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_D_LEFT:
		//�c�F�������@/���F������

		text_left = MyText->rect.left;
		text_top = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_CENTER:
		//�c�F�������@/���F��������

		text_left = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		text_top = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_RIGHT:
		//�c�F�������@/���F�E����

		text_left = MyText->rect.left + MyText->rect.right - sz.cx;
		text_top = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;
	}

	//������_�ł�����Ƃ�
	if (MyText->blk == TRUE)
	{
		if (MyText->blk_state == FALSE)
		{
			//������\�����Ȃ��Ƃ��͊֐����甲����
			if (MyText->blk_off_spd > MyText->blk_cnt)
			{
				MyText->blk_cnt++;
				return;
			}
			else
			{
				MyText->blk_cnt = 0;
				MyText->blk_state = TRUE;
			}
		}

		if (MyText->blk_state == TRUE)
		{
			//������\������Ƃ�
			if (MyText->blk_on_spd > MyText->blk_cnt)
			{
				MyText->blk_cnt++;
			}
			else
			{
				MyText->blk_cnt = 0;
				MyText->blk_state = FALSE;
			}
		}
	}

	//������\��
	TextOut(
		hdc,
		text_left,
		text_top,
		MyText->string,
		lstrlen(MyText->string));

	//�s�v�ȃt�H���g���폜
	DeleteObject(MyText->hfont);

	return;
}

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

	//�S�b�h�C�[�^�[���t�H���g���ꎞ�I�ɓǂݍ���
	if (AddFontResourceEx(FNT_GOD_PASS, FR_PRIVATE, NULL) == 0)
	{
		//�t�H���g���ǂݍ��߂Ȃ������Ƃ�
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

//########## �t�H���g��ݒ肷��֐� ##########
HFONT MY_CreateFont(HDC hdc, MY_TEXT *MyText)
{
	HFONT hFont;
	hFont = CreateFont(
		MyText->size,			//�t�H���g�̍��� / 0�Ȃ�f�t�H���g(�傫��)
		0,						//������		 / 0�Ȃ玩���v�Z
		MyText->angle,			//�e�L�X�g�̊p�x
		0,						//�x�[�X���C����X���Ƃ̊p�x
		MyText->bold,			//�t�H���g�̏d���i�����j
		MyText->ita,			//�C�^���b�N��
		MyText->ul,				//�A���_�[���C��
		MyText->st,				//�ł�������
		MyText->charset,		//�����Z�b�g
		OUT_DEFAULT_PRECIS,		//�o�͐��x
		CLIP_DEFAULT_PRECIS,	//�N���b�s���O���x
		PROOF_QUALITY,			//�o�͕i��
		FIXED_PITCH | FF_MODERN,//�s�b�`�ƃt�@�~���[
		MyText->fontname);		//�t�H���g�̏��̖�

	return hFont;
}

//########## �ꎞ�I�ȃt�H���g���폜����֐� ##########
VOID OnceFont_Remove(HWND hWnd)
{
	//�ꎞ�I�ɓǂݍ��� judge hard�t�H���g���폜
	RemoveFontResourceEx(FNT_JUD_PASS, FR_PRIVATE, NULL);

	//�ꎞ�I�ɓǂݍ��� ���ʂ������}�W�b�N�t�H���g���폜
	RemoveFontResourceEx(FNT_TANU_PASS, FR_PRIVATE, NULL);

	//�ꎞ�I�ɓǂݍ��� �S�b�h�C�[�^�[���}�W�b�N�t�H���g���폜
	RemoveFontResourceEx(FNT_GOD_PASS, FR_PRIVATE, NULL);

	return;
}
