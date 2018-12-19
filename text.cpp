///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//text.cpp
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########

#include <Windows.h>

#pragma comment(lib, "msimg32.lib")

#include "text.h"
#include "fps.h"
#include "game.h"	

///########## グローバル変数の宣言と初期化 ##########

//テキスト構造体の変数
MY_TEXT MyText_name;		//名前
MY_TEXT MyText_title;		//タイトル
MY_TEXT MyText_title_st;	//スタート

///########## プロトタイプ宣言 ##########

VOID InitTextParam(VOID);							//テキストを初期化する
VOID MY_TextOut(HDC, MY_TEXT *);					//テキストを表示する関数
BOOL OnceFont_Read(HWND);							//フォントを一時的に読み込む
HFONT MY_CreateFont(HDC , MY_TEXT *);				//フォントを作成する
VOID OnceFont_Remove(HWND);							//一時的に読み込んだフォントを削除する
VOID MY_TextOut_Gra(HDC , MY_TEXT *);				//テキストを表示する（グラデーション）
VOID MY_TextOut_Align(HDC , MY_TEXT *, POINT *, SIZE);	//テキストを表示するパターンを判断する
BOOL MY_TextOut_Blink(HDC , MY_TEXT *);				//テキストを点滅させる

VOID MY_TextOut_Two_Gra(
	HDC ,
	RECT *,
	COLORREF ,
	COLORREF ,
	BOOL );

///########## テキストを初期化する関数 ##########
VOID InitTextParam(VOID)
{
	//+++++ 名前の文字 ++++++++++++++++++++

	wsprintf(MyText_name.string, TEXT(GAME_MY_NAME));
	wsprintf(MyText_name.fontname, FNT_GOD_NAME);
	MyText_name.charset = ANSI_CHARSET;

	//場所
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

	MyText_name.bkcolor = RGB(0, 0, 0);	//背景色
	MyText_name.color = RGB(255, 255, 255);//文字色
	MyText_name.bkmode = MOJI_BKMD_TRAN;	//背景モード

	MyText_name.blk = FALSE;

	//+++++ タイトルの文字 ++++++++++++++++++++

	wsprintf(MyText_title.string, TEXT(GAME_TITLE));
	wsprintf(MyText_title.fontname, FNT_GOD_NAME);
	MyText_title.charset = ANSI_CHARSET;

	//場所
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

	MyText_title.bkcolor = RGB(0, 0, 0);	//背景色
	MyText_title.color = RGB(255, 255, 255);//文字色
	MyText_title.bkmode = MOJI_BKMD_TRAN;	//背景モード

	MyText_title.blk = FALSE;

	//+++++ タイトルのスタート文字 ++++++++++++++++++++

	wsprintf(MyText_title_st.string, TEXT(GAME_TITLE_START));
	wsprintf(MyText_title_st.fontname, FNT_GOD_NAME);
	MyText_title_st.charset = ANSI_CHARSET;

	//場所
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

	MyText_title_st.bkcolor = RGB(0, 0, 255);		//背景色
	MyText_title_st.color = RGB(255, 0, 0);	//文字色
	MyText_title_st.bkmode = MOJI_BKMD_TRAN;	//背景モード

	MyText_title_st.blk = TRUE;
	MyText_title_st.blk_cnt = 0;
	MyText_title_st.blk_on_spd = FPS_DISP * 2;
	MyText_title_st.blk_off_spd = FPS_DISP / 2;
	MyText_title_st.blk_state = TRUE;

	return;
}

///########## テキストを表示する関数 ##########
VOID MY_TextOut(HDC hdc, MY_TEXT *MyText)
{
	//フォントの詳細情報
	TEXTMETRIC tm;

	SIZE sz;		//文字の大きさ情報
	POINT text_pt;	//文字のXY座標

	//フォントを作成
	MyText->hfont = MY_CreateFont(hdc, MyText);

	//フォントを設定する
	SelectObject(hdc, MyText->hfont);

	//フォントの詳細情報を取得
	GetTextMetrics(hdc, &tm);

	SetTextColor(hdc, MyText->bkcolor);	//背景色
	SetTextColor(hdc, MyText->color);	//文字色
	SetBkMode(hdc, MyText->bkmode);		//背景モード

	//文字の大きさを取得
	GetTextExtentPoint32(
		hdc,
		MyText->string,
		lstrlen(MyText->string),
		&sz);

	//文字の表示場所を設定する
	MY_TextOut_Align(hdc, MyText, &text_pt,sz);

	//文字の点滅をさせる
	if (MY_TextOut_Blink(hdc, MyText) == FALSE)
	{
		return;
	}

	//文字を表示
	TextOut(
		hdc,
		text_pt.x,
		text_pt.y,
		MyText->string,
		lstrlen(MyText->string));

	//不要なフォントを削除
	DeleteObject(MyText->hfont);

	return;
}

///########## テキストを表示する（グラデーション）関数 ##########
VOID MY_TextOut_Gra(HDC hdc, MY_TEXT *MyText)
{
	//フォントの詳細情報
	TEXTMETRIC tm;

	SIZE sz;		//文字の大きさ情報
	POINT text_pt;	//文字のXY座標

	//文字のパス(輪郭)取得ここから
	BeginPath(hdc);

	//フォントを作成
	MyText->hfont = MY_CreateFont(hdc, MyText);

	//フォントを設定する
	SelectObject(hdc, MyText->hfont);

	//フォントの詳細情報を取得
	GetTextMetrics(hdc, &tm);

	SetTextColor(hdc, MyText->bkcolor);	//背景色
	SetTextColor(hdc, MyText->color);	//文字色
	SetBkMode(hdc, MyText->bkmode);		//背景モード

	//文字の大きさを取得
	GetTextExtentPoint32(
		hdc,
		MyText->string,
		lstrlen(MyText->string),
		&sz);

	//文字の表示場所を設定する
	MY_TextOut_Align(hdc, MyText, &text_pt,sz);

	//文字の点滅をさせる
	if (MY_TextOut_Blink(hdc, MyText) == FALSE)
	{
		return;
	}

	//最終的な文字の輪郭を取得
	TextOut(
		hdc,
		text_pt.x,
		text_pt.y,
		MyText->string,
		lstrlen(MyText->string));

	//文字のパス(輪郭)取得ここまで
	EndPath(hdc);

	//パスをクリップ領域(選択状態)に変換
	SelectClipPath(hdc, RGN_COPY);
	
	//クリップ領域を取得
	RECT clipRect;
	GetClipBox(hdc, &clipRect);

	//ブラシを作成
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 255));

	//ブラシを設定
	SelectObject(hdc, hbrush);

	//クリップ領域に２色のグラデーションで矩形を描画

	MY_TextOut_Two_Gra(hdc,
		&clipRect,
		MyText->color,
		MyText->bkcolor,
		FALSE
	);

	////四角を描画
	//Rectangle(
	//	hdc,				//デバイスコンテキストのハンドル
	//	clipRect.left,		//四角の左上のX座標
	//	clipRect.top,		//四角の左上のY座標
	//	clipRect.right,		//四角の右下のX座標
	//	clipRect.bottom);	//四角の右下のY座標

	//ブラシを削除
	DeleteObject(hbrush);


	//HPEN hpen;
	//hpen = CreatePen(PS_SOLID, 1, MyText->bkcolor);
	//SelectObject(hdc, hpen);

	//HBRUSH hbrush;
	//hbrush = CreateSolidBrush(MyText->color);
	//SelectObject(hdc, hbrush);

	////文字のパス(輪郭)と内部を描画
	//StrokeAndFillPath(hdc);

	//DeleteObject(hbrush);
	//DeleteObject(hpen);

	//不要なフォントを削除
	DeleteObject(MyText->hfont);

	return;
}

///########## ２色のグラデーションで矩形を描画する関数 ##########
//引　数：描画先のデバイスコンテキストのハンドル
//引　数：描画する範囲の矩形
//引　数：描画する一つ目の色
//引　数：描画する二つ目の色
//引　数：グラデーションの向き：水平:TRUE/垂直:FALSE
//戻り値：なし
VOID MY_TextOut_Two_Gra(
	HDC hdc,
	RECT *rect,
	COLORREF color1,
	COLORREF color2,
	BOOL IsHorizon)
{

	TRIVERTEX vert[2];	//描画範囲と色を指定

	GRADIENT_RECT gra_rect = { 0, 1 };

	//COLORREF型(4バイト)のデータ構造
	//0000 0000 * 1111 1111 * 1111 1111 * 1111 1111  
	// 0に設定  *     青     *    緑    *     赤
	//上記を10進数表記で表すと、16,777,215
	//上記を16進数表記で表すと、0x00FFFFFF
	//
	//GetRValueでは、データから、下位8ビットを取得する
	//0000 0000 * 1111 1111 * 1111 1111 * 1111 1111
	//　　　　　　　　　　　　　　↓下位8ビット↓
	//                        0000 0000 * 1111 1111	(WORD型(2バイト)に変換)
	//　　　　　　　　　　　　　　↓           ↓
	//GetRValueで取得したデータを、8バイト左シフトする
	//                        0000 0000 * 1111 1111
	//　　　　　　　　　　　　　　↓   << 8    ↓
	//                        1111 1111 * 0000 0000←空いたところは0埋め
	//上記を10進数表記で表すと、65,280
	//上記を16進数表記で表すと、0xFF00
	//→BYTE型(1バイト)からCOLOR16(2バイト)に変換していた
	//******************************************************************************************
	//GetGValueでは、データをWORD型(2バイト)に変換し、8ビット右シフトし、下位8ビットを取得する
	//0000 0000 * 1111 1111 * 1111 1111 * 1111 1111
	//　　　　　　　　　　　　　　↓  2バイト  ↓
	//                        1111 1111 * 1111 1111
	//　　　　　　　　　　　　　　↓   >> 8    ↓
	//   空いたところは0埋め→0000 0000 * 1111 1111
	//　　　　　　　　　　　　　　↓下位8ビット↓
	//                        0000 0000 * 1111 1111
	//　　　　　　　　　　　　　　↓           ↓
	//GetGValueで取得したデータを、8バイト左シフトする
	//                                    1111 1111
	//　　　　　　　　　　　　　　↓   << 8    ↓
	//                        1111 1111 * 0000 0000←空いたところは0埋め
	//******************************************************************************************
	//GetBValueでは、16ビット右シフトし、下位8ビットを取得する
	//0000 0000 * 1111 1111 * 1111 1111 * 1111 1111
	//　　　　　　　　　　　　　　↓   >> 16    ↓
	//   空いたところは0埋め→0000 0000 * 1111 1111(WORD型(2バイト)に変換)
	//　　　　　　　　　　　　　　↓下位8ビット↓
	//                        0000 0000 * 1111 1111
	//　　　　　　　　　　　　　　↓           ↓
	//GetBValueで取得したデータを、8バイト左シフトする
	//                        0000 0000 * 1111 1111
	//　　　　　　　　　　　　　　↓   << 8    ↓
	//                        1111 1111 * 0000 0000←空いたところは0埋め

	//１つ目の色
	vert[0].x = rect->left;
	vert[0].y = rect->top;
	vert[0].Red = GetRValue(color1) <<8;	//赤の情報を取得＆８ビット左シフト
	vert[0].Green = GetGValue(color1) << 8;	//青の情報を取得＆８ビット左シフト
	vert[0].Blue = GetBValue(color1) << 8;	//緑の情報を取得＆８ビット左シフト
	vert[0].Alpha = 0;

	//２つ目の色
	vert[1].x = rect->right;
	vert[1].y = rect->bottom;
	vert[1].Red = GetRValue(color2) << 8;	//赤の情報を取得＆８ビット左シフト
	vert[1].Green = GetGValue(color2) << 8;	//青の情報を取得＆８ビット左シフト
	vert[1].Blue = GetBValue(color2) << 8;	//緑の情報を取得＆８ビット左シフト
	vert[1].Alpha = 0;
	
	//グラデーションの向き
	ULONG rect_h_v;
	if (IsHorizon == TRUE)
	{
		rect_h_v = GRADIENT_FILL_RECT_H;
	}
	else if (IsHorizon == FALSE)
	{
		rect_h_v = GRADIENT_FILL_RECT_V;
	}

	//矩形を描画
	GradientFill(hdc, vert, 2, &gra_rect, 1, rect_h_v);
}

///########## テキストを表示するパターンを判断する関数 ##########
VOID MY_TextOut_Align(HDC hdc, MY_TEXT *MyText, POINT *pt, SIZE sz)
{
	//表示方法
	switch (MyText->align)
	{

	case TEXT_ALIGN_U_LEFT:
		//縦：上揃え　/横：左揃え

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_U_CENTER:
		//縦：上揃え　/横：中央揃え

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_U_RIGHT:
		//縦：上揃え　/横：右揃え

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top;

		break;

	case TEXT_ALIGN_C_LEFT:
		//縦：中央揃え/横：左揃え

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_CENTER:
		//縦：中央揃え/横：中央揃え

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_C_RIGHT:
		//縦：中央揃え/横：右揃え

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top + MyText->rect.bottom / 2 - sz.cy / 2;

		break;

	case TEXT_ALIGN_D_LEFT:
		//縦：下揃え　/横：左揃え

		pt->x = MyText->rect.left;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_CENTER:
		//縦：下揃え　/横：中央揃え

		pt->x = MyText->rect.left + MyText->rect.right / 2 - sz.cx / 2;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;

	case TEXT_ALIGN_D_RIGHT:
		//縦：下揃え　/横：右揃え

		pt->x = MyText->rect.left + MyText->rect.right - sz.cx;
		pt->y = MyText->rect.top + MyText->rect.bottom - sz.cy;

		break;
	}

	return;
}

///########## テキストを点滅させる関数 ##########
BOOL MY_TextOut_Blink(HDC hdc, MY_TEXT *MyText)
{
	//文字を点滅させるとき
	if (MyText->blk == TRUE)
	{
		if (MyText->blk_state == FALSE)
		{
			//文字を表示しないときは関数から抜ける
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
			//文字を表示するとき
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

///########## 一時的にフォントを読み込む関数 ##########
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

	//ゴッドイーター風フォントを一時的に読み込み
	if (AddFontResourceEx(FNT_GOD_PASS, FR_PRIVATE, NULL) == 0)
	{
		//フォントが読み込めなかったとき
		MessageBox(hWnd, ERR_MSG_NO_READ_FONT, ERR_MSG_FONT_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

///########## フォントを設定する関数 ##########
HFONT MY_CreateFont(HDC hdc, MY_TEXT *MyText)
{
	HFONT hFont;
	hFont = CreateFont(
		MyText->size,			//フォントの高さ / 0ならデフォルト(大きさ)
		0,						//文字幅		 / 0なら自動計算
		MyText->angle,			//テキストの角度
		0,						//ベースラインとX軸との角度
		MyText->bold,			//フォントの重さ（太さ）
		MyText->ita,			//イタリック体
		MyText->ul,				//アンダーライン
		MyText->st,				//打ち消し線
		MyText->charset,		//文字セット
		OUT_DEFAULT_PRECIS,		//出力精度
		CLIP_DEFAULT_PRECIS,	//クリッピング精度
		PROOF_QUALITY,			//出力品質
		FIXED_PITCH | FF_MODERN,//ピッチとファミリー
		MyText->fontname);		//フォントの書体名

	return hFont;
}

///########## 一時的なフォントを削除する関数 ##########
VOID OnceFont_Remove(HWND hWnd)
{
	//一時的に読み込んだ judge hardフォントを削除
	RemoveFontResourceEx(FNT_JUD_PASS, FR_PRIVATE, NULL);

	//一時的に読み込んだ たぬき油性マジックフォントを削除
	RemoveFontResourceEx(FNT_TANU_PASS, FR_PRIVATE, NULL);

	//一時的に読み込んだ ゴッドイーター風マジックフォントを削除
	RemoveFontResourceEx(FNT_GOD_PASS, FR_PRIVATE, NULL);

	return;
}
