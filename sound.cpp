//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//sound.cpp
//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

//########## ヘッダファイル読み込み ##########
#include <windows.h>

#include <mmsystem.h>
#include<digitalv.h>
#pragma comment (lib, "winmm.lib")

#include "sound.h"

//########## グローバル変数の宣言と初期化 ##########
MY_SND MySnd_BGM_title;

//########## プロトタイプ宣言 ##########

BOOL MY_SOUND_Read(HWND , MY_SND );	//音楽を読み込む関数
VOID MY_SOUND_Remove(MY_SND );		//読み込んだ音楽を削除する関数

//########## 音楽を読み込む関数 ##########
VOID InitSoundParam(HWND hWnd)
{

	//+++++ タイトル画面のBGM ++++++++++++++++++++

	wsprintf(MySnd_BGM_title.filepass,TEXT(SOUND_BGM_MP3_1));


	MY_SOUND_Read(hWnd, MySnd_BGM_title)

}

//########## 音楽を読み込む関数 ##########
BOOL MY_SOUND_Read(HWND hWnd, MY_SND MySnd)
{
	int res_sound;	//読み込みの結果を保存

	switch (MySnd.fileKind)
	{

	case SOUND_KIND_BEEP:

		break;

	case SOUND_KIND_WAVE:

		//waveの情報を設定
		MySnd.open.lpstrDeviceType = (LPCWSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
		MySnd.open.lpstrElementName = MySnd.filepass;

		//waveを取得
		mciSendCommand(
			0,
			MCI_OPEN,			//デバイスをオープン
			MCI_OPEN_TYPE		//waveファイルの場合
			| MCI_OPEN_TYPE_ID	//waveファイルの場合
			| MCI_OPEN_ELEMENT,	//waveファイルの場合
			(DWORD_PTR)&MySnd.open);

		//waveが読み込めなかったとき
		if (res_sound)
		{
			MessageBox(hWnd, ERR_MSG_NO_READ_WAVE, ERR_MSG_SND_TITLE, MB_OK);
			return FALSE;
		}

		//ウィンドウプロシージャのウィンドウハンドルを設定
		MySnd.play.dwCallback = (DWORD)hWnd;

		break;

	case SOUND_KIND_MP3:

		//MP3の情報を設定
		MySnd.open.lpstrDeviceType = TEXT("MPEGVideo");
		MySnd.open.lpstrElementName = MySnd.filepass;

		//MP3を取得
		res_sound = mciSendCommand(
			0,
			MCI_OPEN, 			//デバイスをオープン
			MCI_OPEN_TYPE		//MP3ファイルの場合
			| MCI_OPEN_ELEMENT,	//MP3ファイルの場合
			(DWORD_PTR)&MySnd.open);

		//MP3が読み込めなかったとき
		if (res_sound)
		{
			MessageBox(hWnd, ERR_MSG_NO_READ_MP3, ERR_MSG_SND_TITLE, MB_OK);
			return FALSE;
		}

		//ウィンドウプロシージャのウィンドウハンドルを設定
		MySnd.play.dwCallback = (DWORD)hWnd;

		break;
	}

	return TRUE;
}


//########## 読み込んだ音楽を削除する関数 ##########
VOID MY_SOUND_Remove(MY_SND MySnd)
{
	//音楽ファイルを閉じる
	mciSendCommand(MySnd.open.wDeviceID, MCI_CLOSE, 0, 0);
}