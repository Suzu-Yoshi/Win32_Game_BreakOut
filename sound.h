//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//sound.h
//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

//########## ヘッダファイル読み込み ##########
#include <windows.h>

//########## マクロ定義 ##########

//+++++ 読み込みエラー ++++++++++++++++++++

#define ERR_MSG_SND_TITLE		TEXT("SOUND_ERROR")

#define ERR_MSG_NO_READ_WAVE	TEXT("WAVEファイルが\
読み込めませんでした\nプログラムを終了します")

#define ERR_MSG_NO_READ_MP3		TEXT("MP3ファイルが\
読み込めませんでした\nプログラムを終了します")

//+++++ 効果音 ++++++++++++++++++++
#define SOUND_KOUKA_1		TEXT(".\\MY_SOUND\\don.wav")
#define SOUND_KOUKA_2		TEXT(".\\MY_SOUND\\chime.wav")

#define SOUND_KOUKA_MP3_1	TEXT(".\\MY_SOUND\\magical_1.mp3")
#define SOUND_KOUKA_MP3_2	TEXT(".\\MY_SOUND\\magical_2.mp3")

//+++++ BGM ++++++++++++++++++++
#define SOUND_BGM_MP3_1		".\\MY_SOUND\\magical_1.mp3"

//+++++ サウンドファイルの種類 ++++++++++++++++++++
#define SOUND_KIND_BEEP		0	//Beep関数
#define SOUND_KIND_WAVE		1	//waveファイル
#define SOUND_KIND_MP3		2	//mp3ファイル

//+++++ その他 ++++++++++++++++++++
#define MAX_STRING_NUM	512	//最大文字数

//########## 構造体 ##########

struct MY_STRUCT_SOUND {
	LPCWSTR			filepass;	//サウンドファイルのパスと名前
	MCI_OPEN_PARMS	open;		//サウンドファイルの設定情報
	MCI_PLAY_PARMS	play;		//サウンドファイルの再生情報
	int				fileKind;	//サウンドファイルの種類
	int				beepFreq;	//Beep関数：周波数
	int				beepMill;	//Beep関数：再生ミリ秒
};

//########## 名前の再定義 ##########

typedef MY_STRUCT_SOUND	MY_SND;

//########## グローバル変数 参照の宣言 ##########

//▼▼▼▼▼ 本体はsound.cpp ▼▼▼▼▼

extern MY_SND MySnd_BGM_title;

//▲▲▲▲▲ 本体はsound.cpp ▲▲▲▲▲

//##########  関数 参照の宣言 ##########

//▼▼▼▼▼ 本体はsound.cpp ▼▼▼▼▼

extern VOID InitSoundParam(HWND hWnd);			//サウンドを初期化する関数
extern BOOL MY_SOUND_Read(HWND);				//サウンドを読み込む関数
extern BOOL MY_SOUND_KIND_Read(HWND, MY_SND *);	//サウンドを種類ごとに読み込む関数
extern VOID MY_SOUND_Remove(VOID);				//読み込んだサウンドを削除する関数
extern VOID MY_SOUND_PLAY(MY_SND MySnd);		//音を鳴らす関数

//▲▲▲▲▲ 本体はsound.cpp ▲▲▲▲▲