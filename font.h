//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//############ ブロック崩し ##############
//font.h
//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

#pragma once

//########## ヘッダファイル読み込み ##########
#include <windows.h>

//########## エラーメッセージ ##########

#define ERR_MSG_FONT_TITLE		TEXT("FONT_ERROR")

#define ERR_MSG_NO_READ_FONT	TEXT("フォントが\
読み込めませんでした\nプログラムを終了します")

#define ERR_MSG_NO_REM_FONT	TEXT("フォントが\
削除できませんでした\nプログラムを終了します")

//すでにPCにインストールされているフォント
#define FNT_MS_GOTHIC TEXT("ＭＳ ゴシック")

#define FNT_MS_MINCHO TEXT("ＭＳ 明朝")

//########## 一時的に読み込むフォント ##########

#define FNT_JUD_PASS	TEXT(".\\MY_FONT\\JUDGE2.TTF")
#define FNT_JUD_NAME	TEXT("Judge Hard")

#define FNT_TANU_PASS	TEXT(".\\MY_FONT\\TanukiMagic.ttf")
#define FNT_TANU_NAME	TEXT("たぬき油性マジック")

//########## プロトタイプ宣言 ##########

//フォントを一時的に読み込む
extern BOOL OnceFont_Read(HWND);

//フォントを作成する
extern HFONT MY_CreateFont(HDC, LPCTSTR, int, int, int);

//一時的に読み込んだフォントを削除する
extern VOID OnceFont_Remove(HWND);