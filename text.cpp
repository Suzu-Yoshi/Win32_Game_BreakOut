//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//text.cpp
//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

//########## ヘッダファイル読み込み ##########

#include <Windows.h>

#include "text.h"
#include "game.h"	

//テキスト構造体の変数
MY_TEXT MyText_title;		//タイトル
MY_TEXT MyText_title_st;	//スタート

//########## テキストを初期化する ##########
VOID InitTextParam(VOID)
{
	//+++++ タイトルの文字 ++++++++++++++++++++
	
	wsprintf(MyText_title.string, TEXT(GAME_TITLE));
	wsprintf(MyText_title.fontname, FNT_JUD_NAME);
	MyText_title.charset = ANSI_CHARSET;

	//場所
	MyText_title.rect.left = GAME_POS_X;
	MyText_title.rect.top = GAME_POS_Y;
	MyText_title.rect.right = GAME_RIGHT;
	MyText_title.rect.bottom = GAME_BOTTOM / 2;

	MyText_title.size = 70;	
	MyText_title.bold = MOJI_REGU;
	MyText_title.ita = FALSE;
	MyText_title.ul = FALSE;
	MyText_title.st = FALSE;
	MyText_title.align = TEXT_ALIGN_D_CENTER;
	
	MyText_title.bkcolor = RGB(0, 0, 0);	//背景色
	MyText_title.color = RGB(255, 255, 255);//文字色
	MyText_title.bkmode = MOJI_BKMD_TRAN;	//背景モード

	//+++++ タイトルのスタート文字 ++++++++++++++++++++

	wsprintf(MyText_title_st.string, TEXT(GAME_TITLE_START));
	wsprintf(MyText_title_st.fontname, FNT_JUD_NAME);
	MyText_title_st.charset = ANSI_CHARSET;

	//場所
	MyText_title_st.rect.left = GAME_POS_X;
	MyText_title_st.rect.top = GAME_BOTTOM / 2;
	MyText_title_st.rect.right = GAME_RIGHT;
	MyText_title_st.rect.bottom = GAME_BOTTOM / 2;

	MyText_title_st.size = 45;
	MyText_title_st.bold = MOJI_REGU;
	MyText_title_st.ita = FALSE;
	MyText_title_st.ul = TRUE;
	MyText_title_st.st = FALSE;
	MyText_title_st.align = TEXT_ALIGN_U_CENTER;

	MyText_title_st.bkcolor = RGB(0, 0, 0);		//背景色
	MyText_title_st.color = RGB(255, 255, 255);	//文字色
	MyText_title_st.bkmode = MOJI_BKMD_TRAN;	//背景モード

	return;
}

//########## テキストを表示する関数 ##########
VOID MY_TextOut(HDC hdc, MY_TEXT MyText)
{
	//フォントの詳細情報
	TEXTMETRIC tm;

	//文字の大きさ情報
	SIZE sz;
	int text_left;	//文字のX座標
	int text_top;	//文字のY座標

	//フォントを作成
	MyText.hfont = MY_CreateFont(hdc, MyText);

	//フォントを設定する
	SelectObject(hdc, MyText.hfont);

	//フォントの詳細情報を取得
	GetTextMetrics(hdc, &tm);

	SetTextColor(hdc, MyText.bkcolor);	//背景色
	SetTextColor(hdc, MyText.color);	//文字色
	SetBkMode(hdc, MyText.bkmode);		//背景モード

	//文字の大きさを取得
	GetTextExtentPoint32(
		hdc,
		MyText.string,
		lstrlen(MyText.string),
		&sz);

	//表示方法
	switch (MyText.align)
	{

	case TEXT_ALIGN_U_LEFT:
		//縦：上揃え　/横：左揃え

		text_left = MyText.rect.left;
		text_top = MyText.rect.top;

		break;

	case TEXT_ALIGN_U_CENTER:
		//縦：上揃え　/横：中央揃え

		text_left = MyText.rect.left + MyText.rect.right / 2 - sz.cx / 2;
		text_top = MyText.rect.top;

		break;

	case TEXT_ALIGN_U_RIGHT:
		//縦：上揃え　/横：右揃え

		text_left = MyText.rect.left + MyText.rect.right - sz.cx;
		text_top = MyText.rect.top;

		break;

	case TEXT_ALIGN_C_LEFT:
		//縦：中央揃え/横：左揃え

		text_left = MyText.rect.left;
		text_top = MyText.rect.top + MyText.rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_CENTER:
		//縦：中央揃え/横：中央揃え

		text_left = MyText.rect.left + MyText.rect.right / 2 - sz.cx / 2;
		text_top = MyText.rect.top + MyText.rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_RIGHT:
		//縦：中央揃え/横：右揃え

		text_left = MyText.rect.left + MyText.rect.right - sz.cx;
		text_top = MyText.rect.top + MyText.rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_D_LEFT:
		//縦：下揃え　/横：左揃え

		text_left = MyText.rect.left;
		text_top = MyText.rect.top + MyText.rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_CENTER:
		//縦：下揃え　/横：中央揃え

		text_left = MyText.rect.left + MyText.rect.right / 2 - sz.cx / 2;
		text_top = MyText.rect.top + MyText.rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_RIGHT:
		//縦：下揃え　/横：右揃え

		text_left = MyText.rect.left + MyText.rect.right - sz.cx;
		text_top = MyText.rect.top + MyText.rect.bottom - sz.cy;

		break;
	}


	//文字を表示
	TextOut(
		hdc,
		text_left,
		text_top,
		MyText.string,
		lstrlen(MyText.string));

	//不要なフォントを削除
	DeleteObject(MyText.hfont);

	return;
}

//########## 一時的にフォントを読み込む関数 ##########
BOOL OnceFont_Read(HWND hWnd)
{
	//judge hardフォントを一時的に読み込み
	if (AddFontResourceEx(FNT_JUD_PASS, FR_PRIVATE, NULL) == 0)
	{
		//フォントが読み込めなかったとき
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	//たぬき油性マジックフォントを一時的に読み込み
	if (AddFontResourceEx(FNT_TANU_PASS, FR_PRIVATE, NULL) == 0)
	{
		//フォントが読み込めなかったとき
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

//########## フォントを設定する関数 ##########
HFONT MY_CreateFont(HDC hdc, MY_TEXT MyText)
{
	HFONT hFont;
	hFont = CreateFont(
		MyText.size,			//フォントの高さ / 0ならデフォルト(大きさ)
		0,						//文字幅		 / 0なら自動計算
		MyText.angle,			//テキストの角度
		0,						//ベースラインとX軸との角度
		MyText.bold,			//フォントの重さ（太さ）
		MyText.ita,				//イタリック体
		MyText.ul,				//アンダーライン
		MyText.st,				//打ち消し線
		MyText.charset,			//文字セット
		OUT_DEFAULT_PRECIS,		//出力精度
		CLIP_DEFAULT_PRECIS,	//クリッピング精度
		PROOF_QUALITY,			//出力品質
		FIXED_PITCH | FF_MODERN,//ピッチとファミリー
		MyText.fontname);		//フォントの書体名

	return hFont;
}

//########## 一時的なフォントを削除する関数 ##########
VOID OnceFont_Remove(HWND hWnd)
{
	//一時的に読み込んだ judge hardフォントを削除
	RemoveFontResourceEx(FNT_JUD_PASS, FR_PRIVATE, NULL);

	//一時的に読み込んだ たぬき油性マジックフォントを削除
	RemoveFontResourceEx(FNT_TANU_PASS, FR_PRIVATE, NULL);

	return;
}
