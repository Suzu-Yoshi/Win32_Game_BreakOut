//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//############ ブロック崩し ##############
//main.cpp
//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

//########## ヘッダファイル読み込み ##########
#include <Windows.h>

#include "font.h"

//########## ライブラリ読み込み ##########

//########## マクロ定義 ##########

//エラーメッセージ
#define ERR_MSG_TITLE			TEXT("WINDOW_ERROR")

#define ERR_MSG_NO_WIN_CLASS	TEXT("ウィンドウクラスが\
登録できませんでした\nプログラムを終了します")

#define ERR_MSG_NO_WIN_CREATE	TEXT("ウィンドウ\
が作成できませんでした\nプログラムを終了します")

//自分で作成するウィンドウクラスの名前
#define MY_WIN_CLASS	"MY_WIN_CLASS"

//ウィンドウのタイトル
#define MY_WIN_TITLE	"SUZUKI BREAK OUT"

//ウィンドウのタイトル
#define MY_WIN_TITLE_START	"SPACE PUSH START"

//ウィンドウの場所を大きさを設定
#define WIN_X		100		//横の位置
#define WIN_Y		100		//縦の位置
#define WIN_WIDTH	500		//幅
#define WIN_HEIGHT	500		//高さ

//ウィンドウのサイズを変更できなくする
#define WS_STATIC_WINDOW	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

//ウィンドウのタイトルをなくす
#define WS_NOT_TITLE WS_POPUP | WS_BORDER

//FPS用のタイマーID
#define TIMER_ID_FPS	100	

//########## 列挙型 ##########

//ウィンドウの表示を変更
enum WIN_MODE {
	WIN_RESZ_OK,	//0：ウィンドウサイズの変更ができる
	WIN_RESZ_NG,	//1：ウィンドウサイズの変更ができない
	WIN_NO_TITLE	//2：ウィンドウのタイトルをなくす
};

//ゲームのシーン設定
enum GAME_SCENE
{
	GAME_TITLE,		//ゲーム開始
	GAME_PLAY,		//ゲーム中
	GAME_END		//ゲーム終了
};

//########## 構造体 ##########

//自作ウィンドウ構造体
struct MY_STRUCT_GAME_WINDOW
{
	HWND		hwnd;			//ウィンドウハンドル(個々のウィンドウを識別)
	WNDCLASS	winc;			//ウィンドウクラスを管理
	MSG			msg;			//メッセージを保持
	RECT		win_size;		//ウィンドウの全体の場所と大きさを
	RECT		win_rect_win;	//ウインドウ領域	
	RECT		win_rect_cli;	//クライアント領域
	int			win_mode;		//ウィンドウの表示を設定
	HBITMAP		hbmp_double;	//ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用
	HDC			hdc_double;		//ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用
	POINT		point_Mouse;	//マウスの座標
	int			scene;			//ゲームのシーン

};

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

//フォントの構造体
struct MY_STRUCT_FONT
{
	HFONT hfnt;
	int x;
	int y;
	TCHAR string[512] = TEXT("");

};

//########## 名前の再定義 ##########
typedef MY_STRUCT_GAME_WINDOW	MY_WIN;

typedef MY_STRUCT_FPS	MY_FPS;

typedef MY_STRUCT_KEY_STATE	MY_KEY;

typedef MY_STRUCT_FONT	MY_FONT;

//########## グローバル変数の宣言と初期化 ##########

//自作ウィンドウ構造体の変数
MY_WIN MyWin;

//FPS構造体の変数
MY_FPS MyFPS;

//キー構造体の変数
MY_KEY MyKey;

//フォント構造体の変数
MY_FONT MyFont_title;

//########## プロトタイプ宣言 ##########

//ウィンドウプロシージャ
LRESULT CALLBACK MY_WndProc(HWND, UINT, WPARAM, LPARAM);

//ウィンドウを生成する
BOOL MY_CreateWindowClass(HINSTANCE);

//自分のウィンドウクラスを作成、登録する関数
BOOL MY_CreateWindow(HINSTANCE);

//クライアント領域を設定する
VOID MY_SetClientSize(VOID);

//ダブルバッファリングの設定をする
VOID MY_SetDoubleBufferring(VOID);

//画面更新の時刻を取得する関数
BOOL MY_FPS_UPDATE(VOID);

//指定したFPSになるように待つ関数
VOID MY_FPS_WAIT(VOID);

//どのキーを押しているか判定
VOID MY_CHECK_KEYDOWN(VOID);

//シーンごとに描画を変える
VOID selectSceneDraw(VOID);

//タイトル画面の背景を描画する
VOID DrawTitle(HDC, RECT);

//ゲームを初期化する
VOID InitGameParam(VOID);

//########## メイン関数 ##########
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdShow)
{

	//終了チェック
	BOOL CheckError;

	//自分のウィンドウクラスを作成、登録する関数
	CheckError = FALSE;		//チェック初期化
	CheckError = MY_CreateWindowClass(hInstance);

	//登録ができなかったらプログラムを終了する
	if (CheckError == FALSE) { return -1; }

	//ウィンドウを生成する(サイズ変更なし)
	MyWin.win_mode = (int)WIN_RESZ_NG;	//ウィンドウ表示モードを設定
	CheckError = FALSE;					//チェック初期化
	CheckError = MY_CreateWindow(hInstance);

	//ウィンドウが生成されなかったらプログラムを終了する
	if (MyWin.hwnd == NULL) { return -1; }

	//クライアント領域を再設定する
	MY_SetClientSize();

	//ダブルバッファリングの設定をする
	MY_SetDoubleBufferring();

	//ウィンドウを表示
	ShowWindow(MyWin.hwnd, SW_SHOW);

	//ゲームを初期化する
	InitGameParam();

	//メッセージを受け取り続ける
	while (GetMessage(&MyWin.msg, NULL, 0, 0))
	{
		//仮想キーコードを文字に変換する
		TranslateMessage(&MyWin.msg);

		//ウィンドウプロシージャに送る
		DispatchMessage(&MyWin.msg);
	}

	return MyWin.msg.wParam;
}

//########## ゲームを初期化する ##########
VOID InitGameParam(VOID)
{
	//ゲームのシーン設定
	MyWin.scene = (int)GAME_TITLE;

	//タイトルの文字を設定
	wsprintf(MyFont_title.string, TEXT(MY_WIN_TITLE));
	
	//タイトルの文字の場所を設定
	MyFont_title.x = 0;
	MyFont_title.y = 100;
}


//########## 自分のウィンドウクラスを作成、登録する関数 ##########
//引　数：メイン関数のインスタンスハンドル
//戻り値：TRUE ：正常終了
//戻り値：FALSE：異常終了
BOOL MY_CreateWindowClass(HINSTANCE hInstance)
{
	//ブラシを作成
	HBRUSH brush;

	//ブラシの色を設定
	brush = CreateSolidBrush(RGB(255, 255, 255));

	//ウィンドウクラスの設定はここから
	MyWin.winc.style = CS_HREDRAW | CS_VREDRAW;
	MyWin.winc.lpfnWndProc = MY_WndProc;			//自作のウィンドウプロシージャ
	MyWin.winc.cbClsExtra = 0;
	MyWin.winc.cbWndExtra = 0;
	MyWin.winc.hInstance = hInstance;				//メイン関数のインスタンスハンドル
	MyWin.winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	MyWin.winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	MyWin.winc.hbrBackground = brush;				//ブラシの色を設定
	MyWin.winc.lpszMenuName = NULL;
	MyWin.winc.lpszClassName = TEXT(MY_WIN_CLASS);	//自作のウィンドウクラスの名前

	//ブラシを削除
	DeleteObject(brush);

	//ウィンドウクラスを登録できなかったとき
	if (!RegisterClass(&MyWin.winc))
	{
		//メッセージボックスを表示
		MessageBox(NULL, ERR_MSG_NO_WIN_CLASS, ERR_MSG_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

//########## ウィンドウを生成する関数 ##########
//引　数：メイン関数のインスタンスハンドル
//戻り値：TRUE ：正常終了
//戻り値：FALSE：異常終了
BOOL MY_CreateWindow(HINSTANCE hInstance)
{
	switch (MyWin.win_mode)
	{
	case WIN_RESZ_OK:
		//ウィンドウのサイズ変更ができる

		//ウィンドウを作成する
		MyWin.hwnd = CreateWindow(
			TEXT(MY_WIN_CLASS),
			TEXT(MY_WIN_TITLE),
			WS_OVERLAPPEDWINDOW,
			WIN_X,
			WIN_Y,
			WIN_WIDTH,
			WIN_HEIGHT,
			NULL,
			NULL,
			hInstance,
			NULL);
		break;

	case WIN_RESZ_NG:
		//ウィンドウのサイズ変更ができない

		//ウィンドウを作成する
		MyWin.hwnd = CreateWindow(
			TEXT(MY_WIN_CLASS),
			TEXT(MY_WIN_TITLE),
			WS_STATIC_WINDOW,
			WIN_X,
			WIN_Y,
			WIN_WIDTH,
			WIN_HEIGHT,
			NULL,
			NULL,
			hInstance,
			NULL);
		break;

	case WIN_NO_TITLE:
		//ウィンドウのタイトルを表示しない

		//ウィンドウを作成する
		MyWin.hwnd = CreateWindow(
			TEXT(MY_WIN_CLASS),
			TEXT(MY_WIN_TITLE),
			WS_NOT_TITLE,
			WIN_X,
			WIN_Y,
			WIN_WIDTH,
			WIN_HEIGHT,
			NULL,
			NULL,
			hInstance,
			NULL);
		break;
	}

	//ウィンドウが生成されなかったとき
	if (MyWin.hwnd == NULL)
	{
		//メッセージボックスを表示
		MessageBox(NULL, ERR_MSG_NO_WIN_CREATE, ERR_MSG_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

//########## クライアント領域の設定をする関数 ##########
VOID MY_SetClientSize(VOID)
{
	//領域を管理する構造体
	RECT rect_set;

	//最初のクライアントの領域を設定
	rect_set.top = WIN_Y;
	rect_set.left = WIN_X;
	rect_set.bottom = WIN_HEIGHT;
	rect_set.right = WIN_WIDTH;

	//ウィンドウ領域を取得
	GetWindowRect(MyWin.hwnd, &MyWin.win_rect_win);

	//クライアント領域を取得
	GetClientRect(MyWin.hwnd, &MyWin.win_rect_cli);

	//クライアント領域の幅を修正
	rect_set.right += (
		(MyWin.win_rect_win.right - MyWin.win_rect_win.left)	// (ウインドウ  の横サイズ) 
		- (MyWin.win_rect_cli.right - MyWin.win_rect_cli.left)	//-(クライアントの横サイズ)
		);

	//クライアント領域の高さを修正
	rect_set.bottom += (
		(MyWin.win_rect_win.bottom - MyWin.win_rect_win.top)	// (ウインドウ  の縦サイズ)
		- (MyWin.win_rect_cli.bottom - MyWin.win_rect_cli.top)	//-(クライアントの縦サイズ)
		);

	//クライアント領域の場所とサイズを再設定
	SetWindowPos(
		MyWin.hwnd,				//ウィンドウハンドル
		HWND_TOP,				//ウィンドウを前の面にする
		rect_set.left,			//ウィンドウのX座標
		rect_set.top,			//ウィンドウのY座標
		rect_set.right,			//ウィンドウの幅
		rect_set.bottom,		//ウィンドウの高さ
		SWP_SHOWWINDOW);		//ウィンドウを表示

	//調整したウィンドウ領域を取得
	GetWindowRect(MyWin.hwnd, &MyWin.win_rect_win);

	//調整したクライアント領域を取得
	GetClientRect(MyWin.hwnd, &MyWin.win_rect_cli);

	return;
}

//########## ダブルバッファリングの設定をする関数 ##########
VOID MY_SetDoubleBufferring(VOID)
{
	// ウインドウのデバイスコンテキストのハンドルを取得
	HDC hdc = GetDC(MyWin.hwnd);

	//メモリの中にデバイスコンテキストのハンドルを作成
	MyWin.hdc_double = CreateCompatibleDC(hdc);

	//メモリの中に画像を作成
	MyWin.hbmp_double = CreateCompatibleBitmap(
		hdc,
		MyWin.win_rect_cli.right,
		MyWin.win_rect_cli.bottom);

	//デバイスコンテキストに画像を設定
	SelectObject(MyWin.hdc_double, MyWin.hbmp_double);

	return;
}

//########## 画面更新の時刻を取得する関数 ##########
BOOL MY_FPS_UPDATE(VOID)
{
	//1フレーム目なら時刻を記憶
	if (MyFPS.fps_count == 0)
	{
		//Windowsが起動してから現在までの時刻をミリ秒で取得
		MyFPS.fps_sta_tm = GetTickCount();
	}

	//60フレーム目なら平均を計算する
	if (MyFPS.fps_count == MyFPS.fps_ave)
	{
		//Windowsが起動してから現在までの時刻をミリ秒で取得
		MyFPS.fps_end_tm = GetTickCount();

		//平均的なFPS値を計算
		MyFPS.fps_Show
			= 1000.0f / ((MyFPS.fps_end_tm - MyFPS.fps_sta_tm) / MyFPS.fps_ave);

		//次のFPS計算の準備
		MyFPS.fps_sta_tm = MyFPS.fps_end_tm;

		//カウント初期化
		MyFPS.fps_count = 0;

	}

	MyFPS.fps_count++;

	return true;
}

//########## 指定したFPSになるように待つ関数 ##########
VOID MY_FPS_WAIT(VOID)
{
	//現在の時刻をミリ秒で取得
	DWORD now_tm = GetTickCount();

	//1フレーム目から実際にかかった時間を計算
	DWORD keika_tm = now_tm - MyFPS.fps_sta_tm;

	//待つべき時間 = かかるべき時間 - 実際にかかった時間;
	DWORD wait_tm = (MyFPS.fps_count * 1000 / MyFPS.fps_disp) - (keika_tm);

	//待つべき時間があった場合
	if (wait_tm > 0 && wait_tm < 2000)
	{
		//ミリ秒分、処理を中断する
		Sleep(wait_tm);
	}

	return;
}

//########## どのキーを押しているか判定する関数 ##########
VOID MY_CHECK_KEYDOWN(VOID)
{
	//すべての仮想キーの現在の状態を一気に取得する
	GetKeyboardState(MyKey.KeyBoard);

	//仮想キーコードで、A～Z、0～9は、ASCIIコードを指定
	BYTE IskeyDown_UP = MyKey.KeyBoard['W'] & 0x80;
	BYTE IskeyDown_DOWN = MyKey.KeyBoard['D'] & 0x80;
	BYTE IskeyDown_RIGHT = MyKey.KeyBoard['A'] & 0x80;
	BYTE IskeyDown_LEFT = MyKey.KeyBoard['S'] & 0x80;
	BYTE IskeyDown_SPACE = MyKey.KeyBoard[VK_SPACE] & 0x80;

	//上キーが押されているか判定する
	if (IskeyDown_UP != 0)
	{
		MyKey.IsDownUP = TRUE;
	}
	else
	{
		MyKey.IsDownUP = FALSE;
	}

	//下キーが押されているか判定する
	if (IskeyDown_DOWN != 0)
	{
		MyKey.IsDownDOWN = TRUE;
	}
	else
	{
		MyKey.IsDownDOWN = FALSE;
	}

	//右キーが押されているか判定する
	if (IskeyDown_RIGHT != 0)
	{
		MyKey.IsDownRIGHT = TRUE;
	}
	else
	{
		MyKey.IsDownRIGHT = FALSE;
	}

	//左キーが押されているか判定する
	if (IskeyDown_LEFT != 0)
	{
		MyKey.IsDownLEFT = TRUE;
	}
	else
	{
		MyKey.IsDownLEFT = FALSE;
	}

	//スペースキーが押されているか判定する
	if (IskeyDown_SPACE != 0)
	{
		MyKey.IsDownSPACE = TRUE;
	}
	else
	{
		MyKey.IsDownSPACE = FALSE;
	}

	return;
}

//########## シーンごとに描画を変える関数 ##########
VOID selectSceneDraw()
{
	switch (MyWin.scene)
	{

	case GAME_TITLE:
		//タイトル画面

		//タイトル画面の描画
		DrawTitle(MyWin.hdc_double, MyWin.win_rect_cli);

		break;
	case GAME_PLAY:
		//ゲーム中


		break;

	case GAME_END:
		//ゲーム終了


		break;
	}

	return;
}

//########## タイトル画面の背景を描画する関数 ##########
VOID DrawTitle(HDC hdc, RECT rect_c)
{
	//+++++ 背景の描画 ++++++++++++++++++++

	//ブラシを作成
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));

	//ブラシを設定
	SelectObject(MyWin.hdc_double, hbrush);

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

	//フォントの詳細情報
	TEXTMETRIC tm;

	//フォントの詳細情報を取得
	GetTextMetrics(hdc, &tm);

	//フォントを作成
	MyFont_title.hfnt = MY_CreateFont(hdc, FNT_JUD_NAME, 70, 0, ANSI_CHARSET);

	//フォントを設定する
	SelectObject(hdc, MyFont_title.hfnt);

	SIZE sz;



	//文字色を白にする
	SetTextColor(hdc, RGB(255, 255, 255));

	//背景を塗りつぶさない
	SetBkMode(hdc, TRANSPARENT);

	GetTextExtentPoint32(hdc, MyFont_title.string, lstrlen(MyFont_title.string), &sz);

	//文字を表示
	TextOut(
		hdc, 
		MyFont_title.x, 
		MyFont_title.y + (tm.tmHeight * 0), 
		MyFont_title.string, 
		lstrlen(MyFont_title.string));

	//フォントの詳細情報を取得
	GetTextMetrics(hdc, &tm);

	//不要なフォントを削除
	DeleteObject(MyFont_title.hfnt);

	return;
}




//########## ウィンドウプロシージャ関数 ##########
LRESULT CALLBACK MY_WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	//HDC：デバイスコンテキストのハンドル
	HDC hdc;

	//PAINTSTRUCT：ウィンドウごとの描画情報を管理する構造体
	PAINTSTRUCT ps;

	switch (msg)
	{

	case WM_CREATE:
		//ウィンドウの生成＆初期化

		//フォントを一時的に読み込めなかったら終了
		if (OnceFont_Read(hwnd) == FALSE) { return -1; }


		//タイマーを10ミリ間隔にセット(開始)
		SetTimer(hwnd, TIMER_ID_FPS, 10, NULL);

		//ウィンドウを生成するときは、0を返す
		return 0;
	case WM_TIMER:

		switch (wp)
		{
		case TIMER_ID_FPS:

			//画面更新の時刻を取得する
			MY_FPS_UPDATE();

			//矢印キーを押しているか判定する
			MY_CHECK_KEYDOWN();

			//▼▼▼▼▼ ゲーム固有の設定ここから ▼▼▼▼▼

			//▲▲▲▲▲ ゲーム固有の設定ここまで ▲▲▲▲▲

			//無効リージョンを発生
			InvalidateRect(hwnd, NULL, FALSE);
			//画面を、すぐに再描画する
			UpdateWindow(hwnd);

			//指定したFPSになるように待つ
			MY_FPS_WAIT();

			break;
		}

		return 0;
	case WM_PAINT:
		//ウィンドウ内を再描画するとき

		//デバイスコンテキストのハンドルを取得
		hdc = BeginPaint(hwnd, &ps);

		//現在のデバイスコンテキストを保存する
		SaveDC(hdc);

		//▼▼▼▼▼ ゲーム固有の設定ここから ▼▼▼▼▼

		//シーンごとに描画するものを変える
		selectSceneDraw();

		//▲▲▲▲▲ ゲーム固有の設定ここまで ▲▲▲▲▲

		//メモリ内の画像を描画
		BitBlt(hdc,
			0, 0, MyWin.win_rect_cli.right, MyWin.win_rect_cli.bottom,
			MyWin.hdc_double, 0, 0, SRCCOPY);

		//保存したデバイスコンテキスを復元する
		RestoreDC(hdc, -1);

		//デバイスコンテキストのハンドルを開放する
		EndPaint(hwnd, &ps);

		return 0;
	case WM_LBUTTONDOWN:
		//マウスの左ボタンを押しているとき

		//タイトルバーがないとき
		if (MyWin.win_mode == WIN_NO_TITLE)
		{
			//メッセージが送られる
			PostMessage(
				hwnd,				//ウィンドウハンドル
				WM_NCLBUTTONDOWN,	//非クライアント領域を左クリックする
				HTCAPTION,			//タイトルバーをクリックする
				MAKELPARAM(0, 0));	//マウスの座標：0,0

			return 0;
		}

		//クライアント領域外でもマウスの動きの監視を開始
		SetCapture(hwnd);

		break;

	case WM_LBUTTONUP:
		//マウスの左ボタンを上げたとき

		//タイトルバーがないとき
		if (MyWin.win_mode == WIN_NO_TITLE)
		{
			return 0;
		}

		//クライアント領域外でもマウスの動きの監視を終了
		ReleaseCapture();

		break;
	case WM_RBUTTONDOWN:
		//マウスの右ボタンを押したとき

		break;
	case WM_RBUTTONUP:
		//マウスの右ボタンを上げたとき

		break;
	case WM_MOUSEMOVE:
		//マウスカーソルが移動したとき

		//DWORD型(32ビット)の下位WORD(16ビット)を取り出す
		MyWin.point_Mouse.x = LOWORD(lp);

		//DWORD型(32ビット)の上位WORD(16ビット)を取り出す
		MyWin.point_Mouse.y = HIWORD(lp);

		//クライアント領域外の対処
		if (MyWin.point_Mouse.x < MyWin.win_size.left)
			MyWin.point_Mouse.x = MyWin.win_size.left;

		if (MyWin.point_Mouse.x >= MyWin.win_size.right)
			MyWin.point_Mouse.x = MyWin.win_size.right - 1;

		if (MyWin.point_Mouse.y < MyWin.win_size.top)
			MyWin.point_Mouse.y = MyWin.win_size.top;

		if (MyWin.point_Mouse.y >= MyWin.win_size.bottom)
			MyWin.point_Mouse.y = MyWin.win_size.bottom - 1;

		break;
	case WM_SIZE:
		//画面のサイズが変わったとき

		//DWORD型(32ビット)の上位WORD(16ビット)を取り出す
		MyWin.win_size.bottom = HIWORD(lp);

		//DWORD型(32ビット)の下位WORD(16ビット)を取り出す
		MyWin.win_size.right = LOWORD(lp);

		break;
	case WM_KEYDOWN:
		//キーボードでキーを押したとき

		return 0;
	case WM_KEYUP:
		//キーボードでキーを押したとき

		return 0;
	case WM_CHAR:
		//仮想キーコードを文字に変換したとき

		return 0;
	case WM_SYSKEYDOWN:
		//システム側のキー(Altキー)を押したとき

		return 0;
	case WM_SYSKEYUP:
		//システム側のキー(Altキー)を上げたとき

		return 0;
	case WM_SYSCHAR:
		//仮想システムキーコードを文字に変換したとき

		return 0;
	case MM_MCINOTIFY:
		//MP3を再生

		break;
	case WM_CLOSE:
		//閉じるボタンを押したとき

		break;
	case WM_DESTROY:
		//ウィンドウが破棄された(なくなった)とき

		//一時的に読み込んだフォントを削除する
		OnceFont_Remove(hwnd);

		//メッセージキューに WM_QUIT を送る
		PostQuitMessage(0);

		return 0;
	}

	//デフォルトのウィンドウプロシージャ関数を呼び出す
	return DefWindowProc(hwnd, msg, wp, lp);
}