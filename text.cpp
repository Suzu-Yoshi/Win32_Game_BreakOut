///����������������������������������������
//text.cpp
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########

#include <Windows.h>

#pragma comment(lib, "msimg32.lib")

#include "text.h"
#include "fps.h"
#include "game.h"	

///########## �O���[�o���ϐ��̐錾�Ə����� ##########

//�e�L�X�g�\���̂̕ϐ�
MY_TEXT MyText_name;		//���O
MY_TEXT MyText_title;		//�^�C�g��
MY_TEXT MyText_title_st;	//�X�^�[�g

///########## �v���g�^�C�v�錾 ##########

VOID InitTextParam(VOID);							//�e�L�X�g������������
VOID MY_TextOut(HDC, MY_TEXT *);					//�e�L�X�g��\������֐�
BOOL OnceFont_Read(HWND);							//�t�H���g���ꎞ�I�ɓǂݍ���
HFONT MY_CreateFont(HDC , MY_TEXT *);				//�t�H���g���쐬����
VOID OnceFont_Remove(HWND);							//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜����
VOID MY_TextOut_Gra(HDC , MY_TEXT *);				//�e�L�X�g��\������i�O���f�[�V�����j
VOID MY_TextOut_Align(HDC , MY_TEXT *, POINT *, SIZE);	//�e�L�X�g��\������p�^�[���𔻒f����
BOOL MY_TextOut_Blink(HDC , MY_TEXT *);				//�e�L�X�g��_�ł�����

VOID MY_TextOut_Two_Gra(
	HDC ,
	RECT *,
	COLORREF ,
	COLORREF ,
	BOOL );

///########## �e�L�X�g������������֐� ##########
VOID InitTextParam(VOID)
{
	//+++++ ���O�̕��� ++++++++++++++++++++

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

	MyText_title_st.bkcolor = RGB(0, 0, 255);		//�w�i�F
	MyText_title_st.color = RGB(255, 0, 0);	//�����F
	MyText_title_st.bkmode = MOJI_BKMD_TRAN;	//�w�i���[�h

	MyText_title_st.blk = TRUE;
	MyText_title_st.blk_cnt = 0;
	MyText_title_st.blk_on_spd = FPS_DISP * 2;
	MyText_title_st.blk_off_spd = FPS_DISP / 2;
	MyText_title_st.blk_state = TRUE;

	return;
}

///########## �e�L�X�g��\������֐� ##########
VOID MY_TextOut(HDC hdc, MY_TEXT *MyText)
{
	//�t�H���g�̏ڍ׏��
	TEXTMETRIC tm;

	SIZE sz;		//�����̑傫�����
	POINT text_pt;	//������XY���W

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

	//�����̕\���ꏊ��ݒ肷��
	MY_TextOut_Align(hdc, MyText, &text_pt,sz);

	//�����̓_�ł�������
	if (MY_TextOut_Blink(hdc, MyText) == FALSE)
	{
		return;
	}

	//������\��
	TextOut(
		hdc,
		text_pt.x,
		text_pt.y,
		MyText->string,
		lstrlen(MyText->string));

	//�s�v�ȃt�H���g���폜
	DeleteObject(MyText->hfont);

	return;
}

///########## �e�L�X�g��\������i�O���f�[�V�����j�֐� ##########
VOID MY_TextOut_Gra(HDC hdc, MY_TEXT *MyText)
{
	//�t�H���g�̏ڍ׏��
	TEXTMETRIC tm;

	SIZE sz;		//�����̑傫�����
	POINT text_pt;	//������XY���W

	//�����̃p�X(�֊s)�擾��������
	BeginPath(hdc);

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

	//�����̕\���ꏊ��ݒ肷��
	MY_TextOut_Align(hdc, MyText, &text_pt,sz);

	//�����̓_�ł�������
	if (MY_TextOut_Blink(hdc, MyText) == FALSE)
	{
		return;
	}

	//�ŏI�I�ȕ����̗֊s���擾
	TextOut(
		hdc,
		text_pt.x,
		text_pt.y,
		MyText->string,
		lstrlen(MyText->string));

	//�����̃p�X(�֊s)�擾�����܂�
	EndPath(hdc);

	//�p�X���N���b�v�̈�(�I�����)�ɕϊ�
	SelectClipPath(hdc, RGN_COPY);
	
	//�N���b�v�̈���擾
	RECT clipRect;
	GetClipBox(hdc, &clipRect);

	//�u���V���쐬
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 255));

	//�u���V��ݒ�
	SelectObject(hdc, hbrush);

	//�N���b�v�̈�ɂQ�F�̃O���f�[�V�����ŋ�`��`��

	MY_TextOut_Two_Gra(hdc,
		&clipRect,
		MyText->color,
		MyText->bkcolor,
		FALSE
	);

	////�l�p��`��
	//Rectangle(
	//	hdc,				//�f�o�C�X�R���e�L�X�g�̃n���h��
	//	clipRect.left,		//�l�p�̍����X���W
	//	clipRect.top,		//�l�p�̍����Y���W
	//	clipRect.right,		//�l�p�̉E����X���W
	//	clipRect.bottom);	//�l�p�̉E����Y���W

	//�u���V���폜
	DeleteObject(hbrush);


	//HPEN hpen;
	//hpen = CreatePen(PS_SOLID, 1, MyText->bkcolor);
	//SelectObject(hdc, hpen);

	//HBRUSH hbrush;
	//hbrush = CreateSolidBrush(MyText->color);
	//SelectObject(hdc, hbrush);

	////�����̃p�X(�֊s)�Ɠ�����`��
	//StrokeAndFillPath(hdc);

	//DeleteObject(hbrush);
	//DeleteObject(hpen);

	//�s�v�ȃt�H���g���폜
	DeleteObject(MyText->hfont);

	return;
}

///########## �Q�F�̃O���f�[�V�����ŋ�`��`�悷��֐� ##########
//���@���F�`���̃f�o�C�X�R���e�L�X�g�̃n���h��
//���@���F�`�悷��͈͂̋�`
//���@���F�`�悷���ڂ̐F
//���@���F�`�悷���ڂ̐F
//���@���F�O���f�[�V�����̌����F����:TRUE/����:FALSE
//�߂�l�F�Ȃ�
VOID MY_TextOut_Two_Gra(
	HDC hdc,
	RECT *rect,
	COLORREF color1,
	COLORREF color2,
	BOOL IsHorizon)
{

	TRIVERTEX vert[2];	//�`��͈͂ƐF���w��

	GRADIENT_RECT gra_rect = { 0, 1 };

	//COLORREF�^(4�o�C�g)�̃f�[�^�\��
	//0000 0000 * 1111 1111 * 1111 1111 * 1111 1111  
	// 0�ɐݒ�  *     ��     *    ��    *     ��
	//��L��10�i���\�L�ŕ\���ƁA16,777,215
	//��L��16�i���\�L�ŕ\���ƁA0x00FFFFFF
	//
	//GetRValue�ł́A�f�[�^����A����8�r�b�g���擾����
	//0000 0000 * 1111 1111 * 1111 1111 * 1111 1111
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@������8�r�b�g��
	//                        0000 0000 * 1111 1111	(WORD�^(2�o�C�g)�ɕϊ�)
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@��           ��
	//GetRValue�Ŏ擾�����f�[�^���A8�o�C�g���V�t�g����
	//                        0000 0000 * 1111 1111
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@��   << 8    ��
	//                        1111 1111 * 0000 0000���󂢂��Ƃ����0����
	//��L��10�i���\�L�ŕ\���ƁA65,280
	//��L��16�i���\�L�ŕ\���ƁA0xFF00
	//��BYTE�^(1�o�C�g)����COLOR16(2�o�C�g)�ɕϊ����Ă���
	//******************************************************************************************
	//GetGValue�ł́A�f�[�^��WORD�^(2�o�C�g)�ɕϊ����A8�r�b�g�E�V�t�g���A����8�r�b�g���擾����
	//0000 0000 * 1111 1111 * 1111 1111 * 1111 1111
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@��  2�o�C�g  ��
	//                        1111 1111 * 1111 1111
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@��   >> 8    ��
	//   �󂢂��Ƃ����0���߁�0000 0000 * 1111 1111
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@������8�r�b�g��
	//                        0000 0000 * 1111 1111
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@��           ��
	//GetGValue�Ŏ擾�����f�[�^���A8�o�C�g���V�t�g����
	//                                    1111 1111
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@��   << 8    ��
	//                        1111 1111 * 0000 0000���󂢂��Ƃ����0����
	//******************************************************************************************
	//GetBValue�ł́A16�r�b�g�E�V�t�g���A����8�r�b�g���擾����
	//0000 0000 * 1111 1111 * 1111 1111 * 1111 1111
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@��   >> 16    ��
	//   �󂢂��Ƃ����0���߁�0000 0000 * 1111 1111(WORD�^(2�o�C�g)�ɕϊ�)
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@������8�r�b�g��
	//                        0000 0000 * 1111 1111
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@��           ��
	//GetBValue�Ŏ擾�����f�[�^���A8�o�C�g���V�t�g����
	//                        0000 0000 * 1111 1111
	//�@�@�@�@�@�@�@�@�@�@�@�@�@�@��   << 8    ��
	//                        1111 1111 * 0000 0000���󂢂��Ƃ����0����

	//�P�ڂ̐F
	vert[0].x = rect->left;
	vert[0].y = rect->top;
	vert[0].Red = GetRValue(color1) <<8;	//�Ԃ̏����擾���W�r�b�g���V�t�g
	vert[0].Green = GetGValue(color1) << 8;	//�̏����擾���W�r�b�g���V�t�g
	vert[0].Blue = GetBValue(color1) << 8;	//�΂̏����擾���W�r�b�g���V�t�g
	vert[0].Alpha = 0;

	//�Q�ڂ̐F
	vert[1].x = rect->right;
	vert[1].y = rect->bottom;
	vert[1].Red = GetRValue(color2) << 8;	//�Ԃ̏����擾���W�r�b�g���V�t�g
	vert[1].Green = GetGValue(color2) << 8;	//�̏����擾���W�r�b�g���V�t�g
	vert[1].Blue = GetBValue(color2) << 8;	//�΂̏����擾���W�r�b�g���V�t�g
	vert[1].Alpha = 0;
	
	//�O���f�[�V�����̌���
	ULONG rect_h_v;
	if (IsHorizon == TRUE)
	{
		rect_h_v = GRADIENT_FILL_RECT_H;
	}
	else if (IsHorizon == FALSE)
	{
		rect_h_v = GRADIENT_FILL_RECT_V;
	}

	//��`��`��
	GradientFill(hdc, vert, 2, &gra_rect, 1, rect_h_v);
}

///########## �e�L�X�g��\������p�^�[���𔻒f����֐� ##########
VOID MY_TextOut_Align(HDC hdc, MY_TEXT *MyText, POINT *pt, SIZE sz)
{
	//�\�����@
	switch (MyText->align)
	{

	case TEXT_ALIGN_U_LEFT:
		//�c�F�㑵���@/���F������

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_U_CENTER:
		//�c�F�㑵���@/���F��������

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_U_RIGHT:
		//�c�F�㑵���@/���F�E����

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_C_LEFT:
		//�c�F��������/���F������

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_CENTER:
		//�c�F��������/���F��������

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_RIGHT:
		//�c�F��������/���F�E����

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_D_LEFT:
		//�c�F�������@/���F������

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_CENTER:
		//�c�F�������@/���F��������

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_RIGHT:
		//�c�F�������@/���F�E����

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;
	}

	return;
}

///########## �e�L�X�g��_�ł�����֐� ##########
BOOL MY_TextOut_Blink(HDC hdc, MY_TEXT *MyText)
{
	//������_�ł�����Ƃ�
	if (MyText->blk == TRUE)
	{
		if (MyText->blk_state == FALSE)
		{
			//������\�����Ȃ��Ƃ��͊֐����甲����
			if (MyText->blk_off_spd > MyText->blk_cnt)
			{
				MyText->blk_cnt++;
				return FALSE;
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

	return TRUE;
}

///########## �ꎞ�I�Ƀt�H���g��ǂݍ��ފ֐� ##########
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

///########## �t�H���g��ݒ肷��֐� ##########
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

///########## �ꎞ�I�ȃt�H���g���폜����֐� ##########
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
