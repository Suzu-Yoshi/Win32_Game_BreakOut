///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//game.h
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## マクロ定義 ##########

#define PI 3.14159

//ゲームウィンドウの場所を大きさを設定
#define GAME_LEFT		100		//横の位置
#define GAME_TOP		100		//縦の位置
#define GAME_RIGHT		700		//幅
#define GAME_BOTTOM		700		//高さ
#define GAME_POS_X		  0		//左上のX座標
#define GAME_POS_Y		  0		//左上のY座標

#define GAME_PLAY_TOP		100	//ゲーム画面の上位置
#define GAME_PLAY_LEFT		0	//ゲーム画面の左位置
#define GAME_PLAY_RIGHT		700	//ゲーム画面の右位置
#define GAME_PLAY_BOTTOM	700	//ゲーム画面の下位置

#define GAME_MY_NAME		"HAMAJO"				//自分の名前
#define GAME_TITLE			"BREAK OUT"				//ゲームのタイトル
#define GAME_TITLE_START	"PUSH SPACE >> START"	//ゲームのタイトルの下

#define GAME_BLOCK_WIDTH	70	//ブロックの幅
#define GAME_BLOCK_HEIGHT	35	//ブロックの高さ

#define GAME_BLOCK_X_MAX	10	//ブロックの横の最大値
#define GAME_BLOCK_Y_MAX	6	//ブロックの縦の最大値

#define BAR_X		250		//バーの横の位置 
#define BAR_Y		600		//バーの縦の位置
#define BAR_WIDHT	200		//バーの幅
#define BAR_HEIGHT	25		//バーの高さ

#define BALL_X		335		//ボールの横の位置 
#define BALL_Y		500		//ボールの縦の位置
#define BALL_WIDHT	30		//ボールの幅
#define BALL_HEIGHT	30		//ボールの高さ


#define COL_R		1		//ブロックの色(赤)
#define COL_G		2		//ブロックの色(緑)
#define COL_B		3		//ブロックの色(青)
#define COL_Y		4		//ブロックの色(黄)
#define COL_P		5		//ブロックの色(紫)
#define COL_W		6		//ブロックの色(白)

#define SPD_NOMAL	3	//バーの速さ(通常)
#define SPD_FAST	6	//バーの速さ(早い)
#define SPD_STAR	9	//バーの速さ(超早)

///########## 列挙型 ##########

//ゲームのシーン設定
enum GAME_SCENE
{
	SCENE_TITLE,	//ゲーム開始
	SCENE_PLAY,		//ゲーム中
	SCENE_END		//ゲーム終了
};

///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
#pragma once	//二重インクルードの防止
///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

///########## グローバル変数 参照の宣言 ##########

///▼▼▼▼▼ 本体はgame.cpp ▼▼▼▼▼

extern int GAME_scene;		//ゲームのシーン

///▲▲▲▲▲ 本体はgame.cpp ▲▲▲▲▲

///##########  関数 参照の宣言 ##########

///▼▼▼▼▼ 本体はgame.cpp ▼▼▼▼▼

extern VOID InitGameParam(HWND);			//ゲームを初期化する
extern VOID selectSceneDraw(HDC, RECT);		//シーンごとに描画を変える
extern VOID DrawTitle(HDC, RECT);			//タイトル画面の背景を描画する
extern VOID DrawGame(HDC, RECT);			//ゲームの背景を描画する
extern VOID CalcTamaMove(VOID);				//玉の移動量を計算する
extern VOID BarTamaCollision(VOID);			//バーと玉の衝突判定をする

///▲▲▲▲▲ 本体はgame.cpp ▲▲▲▲▲
