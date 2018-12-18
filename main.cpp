//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//main.cpp
//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

//########## ヘッダファイル読み込み ##########
#include <Windows.h>

#include "text.h"
#include "fps.h"
#include "game.h"	
#include "keyboad.h"	
#include "sound.h"

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

//ウィンドウのサイズを変更できなくする
#define WS_STATIC_WINDOW	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

//ウィンドウのタイトルをなくす
#define WS_NOT_TITLE WS_POPUP | WS_BORDER

//########## 列挙型 ##########

//ウィンドウの表示を変更
enum WIN_MODE {
	WIN_RESZ_OK,	//0：ウィンドウサイズの変更ができる
	WIN_RESZ_NG,	//1：ウィンドウサイズの変更ができない
	WIN_NO_TITLE	//2：ウィンドウのタイトルをなくす
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
};

//########## 名前の再定義 ##########
typedef MY_STRUCT_GAME_WINDOW	MY_WIN;

//########## グローバル変数の宣言と初期化 ##########

//自作ウィンドウ構造体の変数
MY_WIN MyWin;

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

//シーンごとに描画を変える
VOID selectSceneDraw(VOID);

//タイトル画面の背景を描画する
VOID DrawTitle(HDC, RECT);

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
	InitGameParam(MyWin.hwnd);

	//メッセージを受け取り続ける
	while (GetMessage(&MyWin.msg, NULL, 0, 0))
	{
		//仮想キーコードを文字に変換する
		TranslateMessage(&MyWin.msg);

		//ウィンドウプロシージャに送る
		DispatchMessage(&MyWin.msg);
	}

	return (int)MyWin.msg.wParam;
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
			TEXT(GAME_TITLE),
			WS_OVERLAPPEDWINDOW,
			GAME_LEFT,
			GAME_TOP,
			GAME_RIGHT,
			GAME_BOTTOM,
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
			TEXT(GAME_TITLE),
			WS_STATIC_WINDOW,
			GAME_LEFT,
			GAME_TOP,
			GAME_RIGHT,
			GAME_BOTTOM,
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
			TEXT(GAME_TITLE),
			WS_NOT_TITLE,
			GAME_LEFT,
			GAME_TOP,
			GAME_RIGHT,
			GAME_BOTTOM,
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
//引　数：なし
//戻り値：なし
VOID MY_SetClientSize(VOID)
{
	//領域を管理する構造体
	RECT rect_set;

	//最初のクライアントの領域を設定
	rect_set.top = GAME_TOP;
	rect_set.left = GAME_LEFT;
	rect_set.bottom = GAME_BOTTOM;
	rect_set.right = GAME_RIGHT;

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
//引　数：なし
//戻り値：なし
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

		//▼▼▼▼▼ ゲーム固有の設定ここから ▼▼▼▼▼

		//テキストの初期化
		InitTextParam();

		//フォントを一時的に読み込めなかったら終了
		if (OnceFont_Read(hwnd) == FALSE) { return -1; }

		//サウンドの初期化
		InitSoundParam(hwnd);

		//サウンドを読み込めなかったら終了
		if (MY_SOUND_Read(hwnd) == FALSE) { return -1; }

		//▲▲▲▲▲ ゲーム固有の設定ここまで ▲▲▲▲▲

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
		selectSceneDraw(MyWin.hdc_double, MyWin.win_rect_cli);

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

		//▼▼▼▼▼ ゲーム固有の設定ここから ▼▼▼▼▼

		//一時的に読み込んだフォントを削除する
		OnceFont_Remove(hwnd);

		//読み込んだサウンドをを削除する
		MY_SOUND_Remove();

		//▲▲▲▲▲ ゲーム固有の設定ここまで ▲▲▲▲▲

		//メッセージキューに WM_QUIT を送る
		PostQuitMessage(0);

		return 0;
	}

	//デフォルトのウィンドウプロシージャ関数を呼び出す
	return DefWindowProc(hwnd, msg, wp, lp);
}