//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//############ ブロック崩し ##############
//font.cpp
//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

//########## ヘッダファイル読み込み ##########
#include "font.h"

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
HFONT MY_CreateFont(HDC hdc, LPCTSTR fontName, int size, int angle, int charset)
{

	HFONT hFont;
	hFont = CreateFont(
		size,					//フォントの高さ / 0ならデフォルト(大きさ)
		0,						//文字幅		 / 0なら自動計算

		angle,					//テキストの角度
								//水平から反時計回りに 1/10 度単位で角度を指定
								//   0(  0度) ならば 左から右へ描画
								// 900( 90度) ならば 下から上へ描画
								//1800(180度) ならば 右から左へ描画
								//2700(270度) ならば 上から下へ描画

		0,						//ベースラインとｘ軸との角度
		FW_REGULAR,				//フォントの重さ（太さ）
		FALSE,					//イタリック体
		FALSE,					//アンダーライン
		FALSE,					//打ち消し線

		charset,				//文字セット
								//ANSI      を使うならば ANSI_CHARSET
								//Shift-JIS を使うならば SHIFTJIS_CHARSET
								//デフォルトを使うならば DEFAULT_CHARSET

		OUT_DEFAULT_PRECIS,	//出力精度
		CLIP_DEFAULT_PRECIS,	//クリッピング精度
		PROOF_QUALITY,			//出力品質
		FIXED_PITCH | FF_MODERN,//ピッチとファミリー
		fontName);				//フォントの書体名

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