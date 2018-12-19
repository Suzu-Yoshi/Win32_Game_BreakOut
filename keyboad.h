///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//keyboad.h
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include <windows.h>

///########## マクロ定義 ##########

///########## 構造体 ##########

//キー状態の構造体
struct MY_STRUCT_KEY_STATE
{
	BYTE KeyBoard[256];			//全てのキー状態を入れる変数
	BOOL IsDownUP = FALSE;		//上キーを押しているか
	BOOL IsDownDOWN = FALSE;	//下キーを押しているか
	BOOL IsDownRIGHT = FALSE;	//右キーを押しているか
	BOOL IsDownLEFT = FALSE;	//左キーを押しているか
	BOOL IsDownSPACE = FALSE;	//スペースキーを押しているか
};

///########## 名前の再定義 ##########

typedef MY_STRUCT_KEY_STATE		MY_KEY;

///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
#pragma once	//二重インクルードの防止
///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

///########## グローバル変数 参照の宣言 ##########

///▼▼▼▼▼ 本体はkeyboad.cpp ▼▼▼▼▼

//キー構造体の変数
extern MY_KEY MyKey;

///▲▲▲▲▲ 本体はkeyboad.cpp ▲▲▲▲▲

///########## グローバル変数 参照の宣言 ##########

///▼▼▼▼▼ 本体はkeyboad.cpp ▼▼▼▼▼

//どのキーを押しているか判定
extern VOID MY_CHECK_KEYDOWN(VOID);

///▲▲▲▲▲ 本体はkeyboad.cpp ▲▲▲▲▲
