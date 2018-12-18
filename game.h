//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//game_text.h
//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

//########## マクロ定義 ##########

//ゲームウィンドウの場所を大きさを設定
#define GAME_LEFT		100		//横の位置
#define GAME_TOP		100		//縦の位置
#define GAME_RIGHT		500		//幅
#define GAME_BOTTOM		500		//高さ
#define GAME_POS_X		  0		//左上のX座標
#define GAME_POS_Y		  0		//左上のY座標

//ゲームのタイトル
#define GAME_TITLE			"SUZUKI BREAK OUT"

//ゲームのタイトルの下
#define GAME_TITLE_START	"SPACE PUSH START"

//########## 列挙型 ##########

//ゲームのシーン設定
enum GAME_SCENE
{
	SCENE_TITLE,	//ゲーム開始
	SCENE_PLAY,		//ゲーム中
	SCENE_END		//ゲーム終了
};

//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//2回目以降のヘッダファイル読み込みで
//プロトタイプ宣言が二回定義されることになり
//コンパイルエラーになるのを防ぐ
#pragma once	//二重インクルードの防止
//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼