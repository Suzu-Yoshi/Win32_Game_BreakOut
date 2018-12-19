///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//game.cpp
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include <windows.h>

#include "text.h"
#include "game.h"	
#include "sound.h"

///########## プロトタイプ宣言 ##########

VOID InitGameParam(HWND);			//ゲームを初期化する
VOID selectSceneDraw(HDC, RECT);	//シーンごとに描画を変える
VOID DrawTitle(HDC, RECT);			//タイトル画面の背景を描画する

///########## グローバル変数の宣言と初期化 ##########

int GAME_scene;		//ゲームのシーン

///########## ゲームを初期化する関数 ##########
//引　数：なし
//戻り値：なし
VOID InitGameParam(HWND hWnd)
{
	//ゲームのシーン設定
	GAME_scene = (int)SCENE_TITLE;
}

///########## ゲームを終了する関数 ##########
//引　数：なし
//戻り値：なし
VOID RemoveGameParam(VOID)
{


}


///########## シーンごとに描画を変える関数 ##########
//引　数：なし
//戻り値：なし
VOID selectSceneDraw(HDC hdc , RECT rect_cli)
{
	switch (GAME_scene)
	{

	case SCENE_TITLE:
		//タイトル画面

		//タイトル画面の描画
		DrawTitle(hdc, rect_cli);

		//タイトルのBGMを鳴らす
		MY_SOUND_PLAY(MySnd_BGM_title);

		break;
	case SCENE_PLAY:
		//ゲーム中


		break;

	case SCENE_END:
		//ゲーム終了


		break;
	}

	return;
}

///########## タイトル画面の背景を描画する関数 ##########
//引　数：デバイスコンテキストのハンドル
//引　数：クライアント領域
//戻り値：なし
VOID DrawTitle(HDC hdc, RECT rect_c)
{
	//+++++ 背景の描画 ++++++++++++++++++++

	//ブラシを作成
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));

	//ブラシを設定
	SelectObject(hdc, hbrush);

	//四角を描画
	Rectangle(
		hdc,			//デバイスコンテキストのハンドル
		rect_c.left,	//四角の左上のX座標
		rect_c.top,		//四角の左上のY座標
		rect_c.right,	//四角の右下のX座標
		rect_c.bottom);	//四角の右下のY座標

	//ブラシを削除
	DeleteObject(hbrush);

	//+++++ 背景の文字を描画 ++++++++++++++++++++
	//MY_TextOut(hdc, &MyText_name);		//名前
	//MY_TextOut(hdc, &MyText_title);		//タイトル
	//MY_TextOut(hdc, &MyText_title_st);	//スタート

	MY_TextOut_Gra(hdc, &MyText_name);		//名前
	MY_TextOut_Gra(hdc, &MyText_title);		//タイトル
	MY_TextOut_Gra(hdc, &MyText_title_st);	//スタート

	return;
}