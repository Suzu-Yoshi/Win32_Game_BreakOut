///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//keyboad.cpp
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include <windows.h>

#include "keyboad.h"

///########## グローバル変数の宣言と初期化 ##########

//キーボード構造体の変数
MY_KEY MyKey;

///########## プロトタイプ宣言 ##########

//どのキーを押しているか判定
VOID MY_CHECK_KEYDOWN(VOID);

///########## どのキーを押しているか判定する関数 ##########
VOID MY_CHECK_KEYDOWN(VOID)
{
	//すべての仮想キーの現在の状態を一気に取得する
	GetKeyboardState(MyKey.KeyBoard);

	//仮想キーコードで、A～Z、0～9は、ASCIIコードを指定
	BYTE IskeyDown_UP = MyKey.KeyBoard[VK_UP] & 0x80;
	BYTE IskeyDown_DOWN = MyKey.KeyBoard[VK_DOWN] & 0x80;
	BYTE IskeyDown_RIGHT = MyKey.KeyBoard[VK_RIGHT] & 0x80;
	BYTE IskeyDown_LEFT = MyKey.KeyBoard[VK_LEFT] & 0x80;
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