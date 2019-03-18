///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//sound.cpp
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include <windows.h>

#include <mmsystem.h>
#include<digitalv.h>
#pragma comment (lib, "winmm.lib")

#include "sound.h"

///########## グローバル変数の宣言と初期化 ##########
MY_SND MySnd_BGM_title;

///########## プロトタイプ宣言 ##########

VOID InitSoundParam(HWND hWnd);				//サウンドを初期化する関数
BOOL MY_SOUND_Read(HWND);					//サウンドを読み込む関数
BOOL MY_SOUND_KIND_Read(HWND, MY_SND *);	//サウンドを種類ごとに読み込む関数
VOID MY_SOUND_Remove(VOID);					//読み込んだサウンドを削除する関数
VOID MY_SOUND_PLAY(MY_SND );				//音を鳴らす関数
VOID MY_SOUND_PLAY_END(WPARAM , LPARAM);	//音を鳴らした後の関数
VOID MY_SOUND_PLAY_END_FUNC(WPARAM, LPARAM, MY_SND);	//音を鳴らした後の処理関数

///########## サウンドを初期化する関数 ##########
VOID InitSoundParam(HWND hWnd)
{

	//タイトル画面のBGM
	MySnd_BGM_title.filepass = TEXT(SOUND_BGM_MP3_1);
	MySnd_BGM_title.fileKind = SOUND_KIND_MP3;
	MySnd_BGM_title.soundType = SOUND_TYPE_BGM;

	return;
}

///########## サウンドを読み込む関数 ##########
BOOL MY_SOUND_Read(HWND hWnd)
{
	//タイトル画面のBGM
	if (MY_SOUND_KIND_Read(hWnd, &MySnd_BGM_title) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

///########## サウンドを種類ごとに読み込む関数 ##########
BOOL MY_SOUND_KIND_Read(HWND hWnd, MY_SND *MySnd)
{
	int res_sound;	//読み込みの結果を保存

	switch (MySnd->fileKind)
	{

	case SOUND_KIND_BEEP:

		break;

	case SOUND_KIND_WAVE:

		//waveの情報を設定
		MySnd->open.lpstrDeviceType = (LPCWSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
		MySnd->open.lpstrElementName = MySnd->filepass;

		//waveを取得
		res_sound = mciSendCommand(
			0,
			MCI_OPEN,			//デバイスをオープン
			MCI_OPEN_TYPE		//waveファイルの場合
			| MCI_OPEN_TYPE_ID	//waveファイルの場合
			| MCI_OPEN_ELEMENT,	//waveファイルの場合
			(DWORD_PTR)&MySnd->open);

		//waveが読み込めなかったとき
		if (res_sound)
		{
			MessageBox(hWnd, ERR_MSG_NO_READ_WAVE, ERR_MSG_SND_TITLE, MB_OK);
			return FALSE;
		}

		//ウィンドウプロシージャのウィンドウハンドルを設定
		MySnd->play.dwCallback = (DWORD)hWnd;

		break;

	case SOUND_KIND_MP3:

		//MP3の情報を設定
		MySnd->open.lpstrDeviceType = TEXT("MPEGVideo");
		MySnd->open.lpstrElementName = MySnd->filepass;

		//MP3を取得
		res_sound = mciSendCommand(
			0,
			MCI_OPEN, 			//デバイスをオープン
			MCI_OPEN_TYPE		//MP3ファイルの場合
			| MCI_OPEN_ELEMENT,	//MP3ファイルの場合
			(DWORD_PTR)&MySnd->open);

		//MP3が読み込めなかったとき
		if (res_sound)
		{
			MessageBox(hWnd, ERR_MSG_NO_READ_MP3, ERR_MSG_SND_TITLE, MB_OK);
			return FALSE;
		}

		//ウィンドウプロシージャのウィンドウハンドルを設定
		MySnd->play.dwCallback = (DWORD)hWnd;

		break;
	}

	return TRUE;
}

///########## 読み込んだサウンドを削除する関数 ##########
VOID MY_SOUND_Remove(VOID)
{
	//タイトル画面のBGM
	mciSendCommand(MySnd_BGM_title.open.wDeviceID, MCI_CLOSE, 0, 0);

}

///########## 音を鳴らす関数 ##########
VOID MY_SOUND_PLAY(MY_SND MySnd)
{

	//サウンドのタイプを判定
	switch (MySnd.soundType)
	{
	case SOUND_TYPE_BGM:
		//再生情報を管理
		MCI_STATUS_PARMS mciStatus;

		//再生情報を取得
		mciStatus.dwItem = MCI_STATUS_MODE;
		mciSendCommand(MySnd.open.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&mciStatus);

		//再生していないとき
		if (mciStatus.dwReturn != MCI_MODE_PLAY)
		{
			//再生する
			mciSendCommand(
				MySnd.open.wDeviceID,
				MCI_PLAY,
				MCI_NOTIFY,
				(DWORD_PTR)&MySnd.play
			);
		}

		break;

	case SOUND_TYPE_SE:

		//再生する
		mciSendCommand(
			MySnd.open.wDeviceID,
			MCI_PLAY,
			MCI_NOTIFY,
			(DWORD_PTR)&MySnd.play
		);

		break;
	}

	return;
}

///########## 音を鳴らした後の関数 ##########
VOID MY_SOUND_PLAY_END(WPARAM wp, LPARAM lp)
{
	//音を鳴らしたあとの処理
	MY_SOUND_PLAY_END_FUNC(wp, lp, MySnd_BGM_title);

	return;
}

///########## 音を鳴らした後の処理関数 ##########
VOID MY_SOUND_PLAY_END_FUNC(WPARAM wp,LPARAM lp,MY_SND MySnd)
{
	if (lp == MySnd.open.wDeviceID)
	{
		//再生が終了したとき
		if (wp == MCI_NOTIFY_SUCCESSFUL)
		{
			//シークバーを先頭に戻す
			mciSendCommand(
				MySnd.open.wDeviceID,
				MCI_SEEK,
				MCI_SEEK_TO_START,
				0);
		}
	}

	return;
}