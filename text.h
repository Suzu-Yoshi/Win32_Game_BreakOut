///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//text.h
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include <windows.h>

///########## マクロ定義 ##########

//+++++ エラーメッセージ ++++++++++++++++++++

#define ERR_MSG_FONT_TITLE		TEXT("FONT_ERROR")

#define ERR_MSG_NO_READ_FONT	TEXT("フォントが\
読み込めませんでした\nプログラムを終了します")

#define ERR_MSG_NO_REM_FONT	TEXT("フォントが\
削除できませんでした\nプログラムを終了します")

//+++++ 文字コード ++++++++++++++++++++

#define MOJICD_ANSI ANSI_CHARSET		//ANSI
#define MOJICD_SJIS SHIFTJIS_CHARSET	//SHIFT-JIS
#define MOJICD_DEFL	DEFAULT_CHARSET		//デフォルト

//+++++ 文字の表示方向 ++++++++++++++++++++

#define MOJI_LEFT_RIGHT    0	//  0度	//左から右
#define MOJI_DONW_UP	 900	// 90度	//下から上
#define MOJI_RIGHT_LEFT	1800	//180度	//右から左
#define MOJI_UP_DOWN	2700	//270度	//上から下

//+++++ 文字の太さ ++++++++++++++++++++
#define MOJI_REGU	FW_REGULAR	//標準の太さ
#define MOJI_BOLD	FW_BOLD 	//標準の太さ

//+++++ 文字の背景モード ++++++++++++++++++++
#define MOJI_BKMD_TRAN	TRANSPARENT	//背景を残す
#define MOJI_BKMD_OPAQ	OPAQUE		//背景を塗りつぶす

//+++++ すでにPCにインストールされているフォント ++++++++++++++++++++

#define FNT_MS_GOTHIC TEXT("ＭＳ ゴシック")	//ＭＳは大文字、半角空白
#define FNT_MS_MINCHO TEXT("ＭＳ 明朝")		//ＭＳは大文字、半角空白

//+++++ 一時的に読み込むフォント ++++++++++++++++++++

//FNT_XXX_PASS：フォントの相対パス

//FNT_XXX_NAME：フォントの名称

#define FNT_JUD_PASS	TEXT(".\\MY_FONT\\JUDGE2.TTF")
#define FNT_JUD_NAME	TEXT("Judge Hard")

#define FNT_TANU_PASS	TEXT(".\\MY_FONT\\TanukiMagic.ttf")
#define FNT_TANU_NAME	TEXT("たぬき油性マジック")

#define FNT_GOD_PASS	TEXT(".\\MY_FONT\\GodEaterRegular.ttf")
#define FNT_GOD_NAME	TEXT("GodEater")

//+++++ 文字の揃え方 ++++++++++++++++++++

#define TEXT_ALIGN_U_LEFT	1	//縦：上揃え　/横：左揃え
#define TEXT_ALIGN_U_CENTER	2	//縦：上揃え　/横：中央揃え
#define TEXT_ALIGN_U_RIGHT	3	//縦：上揃え　/横：右揃え

#define TEXT_ALIGN_C_LEFT	4	//縦：中央揃え/横：左揃え
#define TEXT_ALIGN_C_CENTER	5	//縦：中央揃え/横：中央揃え
#define TEXT_ALIGN_C_RIGHT	6	//縦：中央揃え/横：右揃え

#define TEXT_ALIGN_D_LEFT	7	//縦：下揃え　/横：左揃え
#define TEXT_ALIGN_D_CENTER	8	//縦：下揃え　/横：中央揃え
#define TEXT_ALIGN_D_RIGHT	9	//縦：下揃え　/横：右揃え

//+++++ その他 ++++++++++++++++++++

#define MAX_STRING_NUM	512	//最大文字数

///########## 構造体 ##########

//テキスト構造体
struct MY_STRUCT_TEXT
{
	HFONT	hfont;
	TCHAR	string[MAX_STRING_NUM] = TEXT("");		//文字の内容
	TCHAR	fontname[MAX_STRING_NUM] = TEXT("");	//フォントの名前
	int		size;		//文字の大きさ
	int		angle;		//文字の表示角度
	int		bold;		//太字
	BOOL	ita;		//斜体
	BOOL	ul;			//下線
	BOOL	st;			//打ち消し線
	int		charset;	//文字コード
	RECT	rect;		//文字の表示位置
	int		align;		//文字の揃え方
	COLORREF bkcolor;	//文字の背景色
	COLORREF color;		//文字の色
	BOOL	 bkmode;	//背景色の設定
	BOOL	 blk = FALSE;		//文字の点滅
	int		blk_cnt;			//文字の点滅カウンタ(ポインタ)
	int		blk_on_spd = 0;		//文字の点滅速度(表示)(FPS)
	int		blk_off_spd = 0;	//文字の点滅速度(非表示)(FPS)
	BOOL	blk_state = FALSE;	//文字の点滅状態
};

///########## 名前の再定義 ##########

typedef MY_STRUCT_TEXT	MY_TEXT;

///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
#pragma once	//二重インクルードの防止
///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

///########## グローバル変数 参照の宣言 ##########

///▼▼▼▼▼ 本体はtext.cpp ▼▼▼▼▼

//テキスト構造体の変数
extern MY_TEXT MyText_name;		//名前
extern MY_TEXT MyText_title;	//タイトル
extern MY_TEXT MyText_title_st;	//スタート

///▲▲▲▲▲ 本体はtext.cpp ▲▲▲▲▲

///##########  関数 参照の宣言 ##########

///▼▼▼▼▼ 本体はtext.cpp ▼▼▼▼▼

extern VOID InitTextParam(VOID);						//テキストを初期化する
extern VOID MY_TextOut(HDC, MY_TEXT *);					//テキストを表示する関数
extern BOOL OnceFont_Read(HWND);						//フォントを一時的に読み込む
extern HFONT MY_CreateFont(HDC, MY_TEXT *);				//フォントを作成する
extern VOID OnceFont_Remove(HWND);						//一時的に読み込んだフォントを削除する
extern VOID MY_TextOut_Gra(HDC, MY_TEXT *);				//テキストを表示する（グラデーション）
extern VOID MY_TextOut_Align(HDC, MY_TEXT *, POINT *, SIZE);	//テキストを表示するパターンを判断する
extern BOOL MY_TextOut_Blink(HDC, MY_TEXT *);			//テキストを点滅させる

extern VOID MY_TextOut_Two_Gra(
	HDC,
	RECT *,
	COLORREF,
	COLORREF,
	BOOL);

///▲▲▲▲▲ 本体はtext.cpp ▲▲▲▲▲