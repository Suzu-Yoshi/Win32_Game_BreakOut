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

VOID InitSoundParam(HWND hWnd);					//サウンドを初期化する関数
BOOL MY_SOUND_Read(HWND);						//サウンドを読み込む関数
BOOL MY_SOUND_KIND_Read(HWND, MY_SND *);		//サウンドを種類ごとに読み込む関数
VOID MY_SOUND_Remove(VOID);						//読み込んだサウンドを削除する関数
VOID MY_SOUND_PLAY(MY_SND);						//音を鳴らす関数
VOID MY_SOUND_STOP(MY_SND);						//音を止める関数
VOID MY_SOUND_PLAY_END(WPARAM, LPARAM, MY_SND);	//音を鳴らした後の関数

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

	case SOUND_KIND_WAVE:	//waveのとき

		MySnd->open.lpstrDeviceType = (LPCWSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
		MySnd->open.lpstrElementName = MySnd->filepass;

		res_sound = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_ELEMENT, (DWORD_PTR)&MySnd->open);	//waveを取得

		if (res_sound)		//waveが読み込めなかったとき
		{
			MessageBox(hWnd, ERR_MSG_NO_READ_WAVE, ERR_MSG_SND_TITLE, MB_OK);
			return FALSE;
		}

		MySnd->play.dwCallback = (DWORD)hWnd;	//ウィンドウプロシージャのウィンドウハンドルを設定

		break;

	case SOUND_KIND_MP3:	//MP3のとき

		MySnd->open.lpstrDeviceType = TEXT("MPEGVideo");
		MySnd->open.lpstrElementName = MySnd->filepass;

		res_sound = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&MySnd->open);	//MP3を取得

		if (res_sound)		//MP3が読み込めなかったとき
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
	case SOUND_TYPE_BGM:	//BGMのとき
		MCI_STATUS_PARMS mciStatus;					//再生情報を管理

		mciStatus.dwItem = MCI_STATUS_MODE;			//再生情報を取得
		mciSendCommand(MySnd.open.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&mciStatus);

		if (mciStatus.dwReturn != MCI_MODE_PLAY)	//音を再生していないとき
		{
			mciSendCommand(MySnd.open.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&MySnd.play);	//再生する
		}

		break;

	case SOUND_TYPE_SE:		//効果音
		mciSendCommand(MySnd.open.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&MySnd.play);		//再生する

		break;
	}

	return;
}

///########## 音を止める関数 ##########
VOID MY_SOUND_STOP(MY_SND MySnd)
{
	switch (MySnd.soundType)
	{
	case SOUND_TYPE_BGM:	//BGMのとき
		MCI_STATUS_PARMS mciStatus;					//再生情報を管理

		mciStatus.dwItem = MCI_STATUS_MODE;			//再生情報を取得
		mciSendCommand(MySnd.open.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&mciStatus);

		if (mciStatus.dwReturn == MCI_MODE_PLAY)	//音を再生しているとき
		{
			mciSendCommand(MySnd.open.wDeviceID, MCI_STOP, MCI_NOTIFY, (DWORD_PTR)&MySnd.play);	//再生する
		}

		break;

	case SOUND_TYPE_SE:		//効果音
		mciSendCommand(MySnd.open.wDeviceID, MCI_STOP, MCI_NOTIFY, (DWORD_PTR)&MySnd.play);		//再生する

		break;
	}

	return;
}

///########## 音を鳴らした後の関数 ##########
VOID MY_SOUND_PLAY_LOOP(WPARAM wp, LPARAM lp)
{
	if (lp == MySnd_BGM_title.open.wDeviceID)	//タイトル画面のBGMが終了したとき
	{
		if (wp == MCI_NOTIFY_SUCCESSFUL)		//再生が終了したとき
		{
			mciSendCommand(MySnd_BGM_title.open.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);	//シークバーを先頭に戻す
		}
	}

	return;
}