//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//fps.h
//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

//########## ヘッダファイル読み込み ##########
#include <windows.h>

//########## マクロ定義 ##########

//FPS用のタイマーID
#define TIMER_ID_FPS	100

//FPSのパラメータ構造体
struct MY_STRUCT_FPS
{
	float		fps_Show;		//表示するFPS
	DWORD		fps_sta_tm;		//0フレーム目の開始時刻
	DWORD		fps_end_tm;		//設定したフレームの終了時刻
	DWORD		fps_count;		//フレームのカウント
	float		fps_ave = 60.0;	//FPSを計算するための平均サンプル数
	int			fps_disp = 60;	//FPSの値
};

//########## 名前の再定義 ##########

typedef MY_STRUCT_FPS	MY_FPS;

//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//2回目以降のヘッダファイル読み込みで
//プロトタイプ宣言が二回定義されることになり
//コンパイルエラーになるのを防ぐ
#pragma once	//二重インクルードの防止
//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

//########## 外部 変数 参照の宣言 ##########

//▼▼▼▼▼ 本体はfps.cpp ▼▼▼▼▼

//FPS構造体の変数
extern MY_FPS MyFPS;

//▲▲▲▲▲ 本体はfps.cpp ▲▲▲▲▲

//########## 外部 関数 参照の宣言 ##########

//▼▼▼▼▼ 本体はfps.cpp ▼▼▼▼▼

//画面更新の時刻を取得する関数
extern BOOL MY_FPS_UPDATE(VOID);

//指定したFPSになるように待つ関数
extern VOID MY_FPS_WAIT(VOID);

//▲▲▲▲▲ 本体はfps.cpp ▲▲▲▲▲