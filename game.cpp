///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//game.cpp
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include <windows.h>
#include <Math.h>

#include "text.h"
#include "game.h"	
#include "sound.h"
#include "keyboad.h"

///########## プロトタイプ宣言 ##########

VOID InitGameParam(HWND);			//ゲームを初期化する
VOID selectSceneDraw(HDC, RECT);	//シーンごとに描画を変える
VOID DrawTitle(HDC, RECT);			//タイトル画面の背景を描画する
VOID DrawGame(HDC, RECT);			//ゲームの背景を描画する
VOID MoveBar(VOID);					//バーを移動する
VOID BarTamaCollision(VOID);		//バーと玉の衝突判定をする
VOID CalcTamaMove(VOID);			//玉の移動量を計算する
VOID WallTamaCollision(VOID);		//壁と玉の衝突判定をする

///########## グローバル変数の宣言と初期化 ##########

int GAME_scene;		//ゲームのシーン

int block[GAME_BLOCK_Y_MAX][GAME_BLOCK_X_MAX]	//ブロックの表示状態
= { {0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
};

int block_col[GAME_BLOCK_Y_MAX][GAME_BLOCK_X_MAX]	//ブロックの色
= { {COL_R,COL_R,COL_R,COL_R,COL_R,COL_R,COL_R,COL_R,COL_R,COL_R},
	{COL_G,COL_G,COL_G,COL_G,COL_G,COL_G,COL_G,COL_G,COL_G,COL_G},
	{COL_B,COL_B,COL_B,COL_B,COL_B,COL_B,COL_B,COL_B,COL_B,COL_B},
	{COL_Y,COL_Y,COL_Y,COL_Y,COL_Y,COL_Y,COL_Y,COL_Y,COL_Y,COL_Y},
	{COL_P,COL_P,COL_P,COL_P,COL_P,COL_P,COL_P,COL_P,COL_P,COL_P},
	{COL_W,COL_W,COL_W,COL_W,COL_W,COL_W,COL_W,COL_W,COL_W,COL_W}
};

RECT bar;			//バーの位置・大きさ
RECT tama;			//玉の位置・大きさ
RECT play;			//ゲーム画面の位置・大きさ
int barSpeed;		//バーの移動速度
int tamaSpeed;		//玉の移動速度

int angle;			//玉の角度
double radian;		//ラジアン

int tamaCosX;
int tamaSinY;

///########## ゲームを初期化する関数 ##########
VOID InitGameParam(HWND hWnd)
{
	GAME_scene = (int)SCENE_TITLE;	//ゲームのシーン設定

	GAME_scene = (int)SCENE_PLAY;	//ゲームのシーン設定

	//ブロックの初期化
	for (int tate = 0; tate < GAME_BLOCK_Y_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_BLOCK_X_MAX; yoko++)
		{
			block[tate][yoko] = 0;
		}
	}

	//ゲーム画面の位置と大きさを初期化
	play.top = GAME_PLAY_TOP;
	play.left = GAME_PLAY_LEFT;
	play.right = GAME_PLAY_RIGHT;
	play.bottom = GAME_PLAY_BOTTOM;

	//バーの位置と大きさを初期化
	bar.top = BAR_Y;
	bar.left = BAR_X;
	bar.bottom = BAR_Y + BAR_HEIGHT;
	bar.right = BAR_X + BAR_WIDHT;

	barSpeed = SPD_NOMAL;	//バーの速さを初期化

	//ボールの位置と大きさを初期化
	tama.top = BALL_Y;
	tama.left = BALL_X;
	tama.bottom = BALL_Y + BALL_HEIGHT;
	tama.right = BALL_X + BALL_WIDHT;

	tamaSpeed = SPD_NOMAL;	//玉の速さを初期化

	angle = 45;			//玉の角度を初期化

	CalcTamaMove();		//玉の向きを初期化

	return;
}

///########## ゲームを終了する関数 ##########
VOID RemoveGameParam(VOID)
{

}

///########## シーンごとに描画を変える関数 ##########
VOID selectSceneDraw(HDC hdc, RECT rect_cli)
{
	switch (GAME_scene)
	{

	case SCENE_TITLE:	//タイトル画面

		DrawTitle(hdc, rect_cli);		//タイトル画面の描画
		MY_SOUND_PLAY(MySnd_BGM_title);	//タイトルのBGMを鳴らす

		if (MyKey.IsDownSPACE == TRUE)		//スペースキーが押されたとき
		{
			GAME_scene = (int)SCENE_PLAY;	//ゲーム中に移動
			MY_SOUND_STOP(MySnd_BGM_title);	//BGMを止める
		}

		break;
	case SCENE_PLAY:	//ゲーム中

		MoveBar();		//バーを移動



		//玉の移動
		tama.top += tamaSinY;
		tama.bottom += tamaSinY;

		tama.left += tamaCosX;
		tama.right += tamaCosX;


		WallTamaCollision();		//壁と玉の衝突判定
		//BarTamaCollision();			//バーと玉の当たり判定

		CalcTamaMove();				//玉の角度を反転する

		DrawGame(hdc, rect_cli);	//ゲーム画面の描画

		break;

	case SCENE_END:		//ゲーム終了


		break;

	default:

		break;
	}

	return;
}

///########## タイトル画面の背景を描画する関数 ##########
VOID DrawTitle(HDC hdc, RECT rect_c)
{
	//背景を描画
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));					//ブラシを作成	
	SelectObject(hdc, hbrush);												//ブラシを設定
	Rectangle(hdc, rect_c.left, rect_c.top, rect_c.right, rect_c.bottom);	//四角を描画
	DeleteObject(hbrush);													//ブラシを削除

	//文字を描画
	MY_TextOut(hdc, &MyText_name_OL);		//名前(輪郭)
	MY_TextOut_Gra(hdc, &MyText_name);		//名前
	MY_TextOut(hdc, &MyText_title_OL);		//タイトル(輪郭)
	MY_TextOut_Gra(hdc, &MyText_title);		//タイトル
	MY_TextOut(hdc, &MyText_title_st_OL);	//スタート(輪郭)
	MY_TextOut_Gra(hdc, &MyText_title_st);	//スタート

	return;
}

///########## ゲームの背景を描画する関数 ##########
VOID DrawGame(HDC hdc, RECT rect_c)
{
	//背景を描画
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));							//ブラシを作成	
	SelectObject(hdc, hbrush);												//ブラシを設定
	Rectangle(hdc, rect_c.left, rect_c.top, rect_c.right, rect_c.bottom);	//四角を描画
	DeleteObject(hbrush);													//ブラシを削除

	//ブロックを描画
	HBRUSH hbrush_block_col;
	for (int tate = 0; tate < GAME_BLOCK_Y_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_BLOCK_X_MAX; yoko++)
		{
			switch (block_col[tate][yoko])
			{
			case COL_R:
				hbrush_block_col = CreateSolidBrush(RGB(240, 0, 0));
				break;
			case COL_G:
				hbrush_block_col = CreateSolidBrush(RGB(0, 240, 0));
				break;
			case COL_B:
				hbrush_block_col = CreateSolidBrush(RGB(0, 0, 240));
				break;
			case COL_Y:
				hbrush_block_col = CreateSolidBrush(RGB(240, 240, 0));
				break;
			case COL_P:
				hbrush_block_col = CreateSolidBrush(RGB(240, 0, 240));
				break;
			case COL_W:
				hbrush_block_col = CreateSolidBrush(RGB(240, 240, 240));
				break;
			default:
				hbrush_block_col = CreateSolidBrush(RGB(100, 100, 100));
				break;
			}

			SelectObject(hdc, hbrush_block_col);

			Rectangle(
				hdc,
				(yoko + 0) * GAME_BLOCK_WIDTH,
				(tate + 0) * GAME_BLOCK_HEIGHT + play.top,	//ゲーム画面用に位置をずらす
				(yoko + 1) * GAME_BLOCK_WIDTH,
				(tate + 1) * GAME_BLOCK_HEIGHT + play.top);	//ゲーム画面用に位置をずらす

			DeleteObject(hbrush_block_col);
		}
	}

	//バーを描画
	HBRUSH hbrush_bar = CreateSolidBrush(RGB(0, 161, 233));
	SelectObject(hdc, hbrush_bar);
	Rectangle(hdc, bar.left, bar.top, bar.right, bar.bottom);
	DeleteObject(hbrush_bar);

	//ボールを描画
	HBRUSH hbrush_tama = CreateSolidBrush(RGB(255, 215, 0));
	SelectObject(hdc, hbrush_tama);
	Ellipse(hdc, tama.left, tama.top, tama.right, tama.bottom);
	DeleteObject(hbrush_tama);

	return;
}

///########## バーを移動する関数 ##########
VOID MoveBar(VOID)
{
	if (MyKey.IsDownRIGHT == TRUE)	//右を押したとき
	{
		if (bar.right + barSpeed < GAME_PLAY_RIGHT)	//右側
		{
			bar.right += barSpeed;
			bar.left += barSpeed;
		}
	}

	if (MyKey.IsDownLEFT == TRUE)	//左を押したとき
	{
		if (bar.left - barSpeed > GAME_PLAY_LEFT)	//左側
		{
			bar.right -= barSpeed;
			bar.left -= barSpeed;
		}
	}
}

///########## バーと玉の衝突判定をする関数 ##########
VOID BarTamaCollision(VOID)
{

	if (bar.top < tama.bottom		//バー(上)と玉(下)の判定
		&& bar.bottom > tama.top)	//バー(下)と玉(上)の判定
	{
		angle = 360 - angle;		//角度を反転させる
	}

	//if (bar.left < tama.right 		//バー(左)と玉(右)の判定
	//	&& bar.right > tama.left)	//バー(右)と玉(左)の判定
	//{
	//	angle = 180 - angle;		//角度を反転させる
	//}	

	return;
}

///########## 壁と玉の衝突判定をする関数 ##########
VOID WallTamaCollision(VOID)
{

	if (tama.top < GAME_PLAY_TOP			//玉(上)と壁(上)の判定
		|| tama.bottom > GAME_PLAY_BOTTOM)	//玉(下)と壁(下)の判定
	{
		angle = 360 - angle;		//角度を反転させる
	}

	if (tama.left < GAME_PLAY_LEFT 			//玉(左)と壁(左)の判定
		|| tama.right > GAME_PLAY_RIGHT)	//玉(右)と壁(右)の判定
	{
		angle = 180 - angle;		//角度を反転させる
	}

	return;
}

///########## 玉の移動量を計算する関数 ##########
VOID CalcTamaMove(VOID)
{
	radian = angle * PI / 180;				//角度をラジアンに変更
	tamaSinY = sin(radian) * tamaSpeed;		//玉の向きを計算(縦)
	if (tamaSinY > 0) { tamaSinY -= 1; }	//微調整

	tamaCosX = cos(radian) * tamaSpeed;		//玉の向きを計算(横)
	if (tamaCosX > 0) { tamaCosX -= 1; }	//微調整

	//tama.left += cos(radian) * tamaSpeed;
	//tama.top += sin(radian) * tamaSpeed;
	//tama.right += cos(radian) * tamaSpeed;
	//tama.bottom += sin(radian) * tamaSpeed;

	return;
}