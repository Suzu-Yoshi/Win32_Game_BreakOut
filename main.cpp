//����������������������������������������
//main.cpp
//����������������������������������������

//########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <Windows.h>

#include "text.h"
#include "fps.h"
#include "game.h"	
#include "keyboad.h"	
#include "sound.h"

//########## ���C�u�����ǂݍ��� ##########

//########## �}�N����` ##########

//�G���[���b�Z�[�W
#define ERR_MSG_TITLE			TEXT("WINDOW_ERROR")

#define ERR_MSG_NO_WIN_CLASS	TEXT("�E�B���h�E�N���X��\
�o�^�ł��܂���ł���\n�v���O�������I�����܂�")

#define ERR_MSG_NO_WIN_CREATE	TEXT("�E�B���h�E\
���쐬�ł��܂���ł���\n�v���O�������I�����܂�")

//�����ō쐬����E�B���h�E�N���X�̖��O
#define MY_WIN_CLASS	"MY_WIN_CLASS"

//�E�B���h�E�̃T�C�Y��ύX�ł��Ȃ�����
#define WS_STATIC_WINDOW	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

//�E�B���h�E�̃^�C�g�����Ȃ���
#define WS_NOT_TITLE WS_POPUP | WS_BORDER

//########## �񋓌^ ##########

//�E�B���h�E�̕\����ύX
enum WIN_MODE {
	WIN_RESZ_OK,	//0�F�E�B���h�E�T�C�Y�̕ύX���ł���
	WIN_RESZ_NG,	//1�F�E�B���h�E�T�C�Y�̕ύX���ł��Ȃ�
	WIN_NO_TITLE	//2�F�E�B���h�E�̃^�C�g�����Ȃ���
};

//########## �\���� ##########

//����E�B���h�E�\����
struct MY_STRUCT_GAME_WINDOW
{
	HWND		hwnd;			//�E�B���h�E�n���h��(�X�̃E�B���h�E������)
	WNDCLASS	winc;			//�E�B���h�E�N���X���Ǘ�
	MSG			msg;			//���b�Z�[�W��ێ�
	RECT		win_size;		//�E�B���h�E�̑S�̂̏ꏊ�Ƒ傫����
	RECT		win_rect_win;	//�E�C���h�E�̈�	
	RECT		win_rect_cli;	//�N���C�A���g�̈�
	int			win_mode;		//�E�B���h�E�̕\����ݒ�
	HBITMAP		hbmp_double;	//������ޯ̧�ݸޗp
	HDC			hdc_double;		//������ޯ̧�ݸޗp
	POINT		point_Mouse;	//�}�E�X�̍��W
};

//########## ���O�̍Ē�` ##########
typedef MY_STRUCT_GAME_WINDOW	MY_WIN;

//########## �O���[�o���ϐ��̐錾�Ə����� ##########

//����E�B���h�E�\���̂̕ϐ�
MY_WIN MyWin;

//########## �v���g�^�C�v�錾 ##########

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK MY_WndProc(HWND, UINT, WPARAM, LPARAM);

//�E�B���h�E�𐶐�����
BOOL MY_CreateWindowClass(HINSTANCE);

//�����̃E�B���h�E�N���X���쐬�A�o�^����֐�
BOOL MY_CreateWindow(HINSTANCE);

//�N���C�A���g�̈��ݒ肷��
VOID MY_SetClientSize(VOID);

//�_�u���o�b�t�@�����O�̐ݒ������
VOID MY_SetDoubleBufferring(VOID);

//�V�[�����Ƃɕ`���ς���
VOID selectSceneDraw(VOID);

//�^�C�g����ʂ̔w�i��`�悷��
VOID DrawTitle(HDC, RECT);

//########## ���C���֐� ##########
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdShow)
{

	//�I���`�F�b�N
	BOOL CheckError;

	//�����̃E�B���h�E�N���X���쐬�A�o�^����֐�
	CheckError = FALSE;		//�`�F�b�N������
	CheckError = MY_CreateWindowClass(hInstance);

	//�o�^���ł��Ȃ�������v���O�������I������
	if (CheckError == FALSE) { return -1; }

	//�E�B���h�E�𐶐�����(�T�C�Y�ύX�Ȃ�)
	MyWin.win_mode = (int)WIN_RESZ_NG;	//�E�B���h�E�\�����[�h��ݒ�
	CheckError = FALSE;					//�`�F�b�N������
	CheckError = MY_CreateWindow(hInstance);

	//�E�B���h�E����������Ȃ�������v���O�������I������
	if (MyWin.hwnd == NULL) { return -1; }

	//�N���C�A���g�̈���Đݒ肷��
	MY_SetClientSize();

	//�_�u���o�b�t�@�����O�̐ݒ������
	MY_SetDoubleBufferring();

	//�E�B���h�E��\��
	ShowWindow(MyWin.hwnd, SW_SHOW);

	//�Q�[��������������
	InitGameParam(MyWin.hwnd);

	//���b�Z�[�W���󂯎�葱����
	while (GetMessage(&MyWin.msg, NULL, 0, 0))
	{
		//���z�L�[�R�[�h�𕶎��ɕϊ�����
		TranslateMessage(&MyWin.msg);

		//�E�B���h�E�v���V�[�W���ɑ���
		DispatchMessage(&MyWin.msg);
	}

	return (int)MyWin.msg.wParam;
}

//########## �����̃E�B���h�E�N���X���쐬�A�o�^����֐� ##########
//���@���F���C���֐��̃C���X�^���X�n���h��
//�߂�l�FTRUE �F����I��
//�߂�l�FFALSE�F�ُ�I��
BOOL MY_CreateWindowClass(HINSTANCE hInstance)
{
	//�u���V���쐬
	HBRUSH brush;

	//�u���V�̐F��ݒ�
	brush = CreateSolidBrush(RGB(255, 255, 255));

	//�E�B���h�E�N���X�̐ݒ�͂�������
	MyWin.winc.style = CS_HREDRAW | CS_VREDRAW;
	MyWin.winc.lpfnWndProc = MY_WndProc;			//����̃E�B���h�E�v���V�[�W��
	MyWin.winc.cbClsExtra = 0;
	MyWin.winc.cbWndExtra = 0;
	MyWin.winc.hInstance = hInstance;				//���C���֐��̃C���X�^���X�n���h��
	MyWin.winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	MyWin.winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	MyWin.winc.hbrBackground = brush;				//�u���V�̐F��ݒ�
	MyWin.winc.lpszMenuName = NULL;
	MyWin.winc.lpszClassName = TEXT(MY_WIN_CLASS);	//����̃E�B���h�E�N���X�̖��O

	//�u���V���폜
	DeleteObject(brush);

	//�E�B���h�E�N���X��o�^�ł��Ȃ������Ƃ�
	if (!RegisterClass(&MyWin.winc))
	{
		//���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, ERR_MSG_NO_WIN_CLASS, ERR_MSG_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

//########## �E�B���h�E�𐶐�����֐� ##########
//���@���F���C���֐��̃C���X�^���X�n���h��
//�߂�l�FTRUE �F����I��
//�߂�l�FFALSE�F�ُ�I��
BOOL MY_CreateWindow(HINSTANCE hInstance)
{
	switch (MyWin.win_mode)
	{
	case WIN_RESZ_OK:
		//�E�B���h�E�̃T�C�Y�ύX���ł���

		//�E�B���h�E���쐬����
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
		//�E�B���h�E�̃T�C�Y�ύX���ł��Ȃ�

		//�E�B���h�E���쐬����
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
		//�E�B���h�E�̃^�C�g����\�����Ȃ�

		//�E�B���h�E���쐬����
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

	//�E�B���h�E����������Ȃ������Ƃ�
	if (MyWin.hwnd == NULL)
	{
		//���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, ERR_MSG_NO_WIN_CREATE, ERR_MSG_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

//########## �N���C�A���g�̈�̐ݒ������֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_SetClientSize(VOID)
{
	//�̈���Ǘ�����\����
	RECT rect_set;

	//�ŏ��̃N���C�A���g�̗̈��ݒ�
	rect_set.top = GAME_TOP;
	rect_set.left = GAME_LEFT;
	rect_set.bottom = GAME_BOTTOM;
	rect_set.right = GAME_RIGHT;

	//�E�B���h�E�̈���擾
	GetWindowRect(MyWin.hwnd, &MyWin.win_rect_win);

	//�N���C�A���g�̈���擾
	GetClientRect(MyWin.hwnd, &MyWin.win_rect_cli);

	//�N���C�A���g�̈�̕����C��
	rect_set.right += (
		(MyWin.win_rect_win.right - MyWin.win_rect_win.left)	// (�E�C���h�E  �̉��T�C�Y) 
		- (MyWin.win_rect_cli.right - MyWin.win_rect_cli.left)	//-(�N���C�A���g�̉��T�C�Y)
		);

	//�N���C�A���g�̈�̍������C��
	rect_set.bottom += (
		(MyWin.win_rect_win.bottom - MyWin.win_rect_win.top)	// (�E�C���h�E  �̏c�T�C�Y)
		- (MyWin.win_rect_cli.bottom - MyWin.win_rect_cli.top)	//-(�N���C�A���g�̏c�T�C�Y)
		);

	//�N���C�A���g�̈�̏ꏊ�ƃT�C�Y���Đݒ�
	SetWindowPos(
		MyWin.hwnd,				//�E�B���h�E�n���h��
		HWND_TOP,				//�E�B���h�E��O�̖ʂɂ���
		rect_set.left,			//�E�B���h�E��X���W
		rect_set.top,			//�E�B���h�E��Y���W
		rect_set.right,			//�E�B���h�E�̕�
		rect_set.bottom,		//�E�B���h�E�̍���
		SWP_SHOWWINDOW);		//�E�B���h�E��\��

	//���������E�B���h�E�̈���擾
	GetWindowRect(MyWin.hwnd, &MyWin.win_rect_win);

	//���������N���C�A���g�̈���擾
	GetClientRect(MyWin.hwnd, &MyWin.win_rect_cli);

	return;
}

//########## �_�u���o�b�t�@�����O�̐ݒ������֐� ##########
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
VOID MY_SetDoubleBufferring(VOID)
{
	// �E�C���h�E�̃f�o�C�X�R���e�L�X�g�̃n���h�����擾
	HDC hdc = GetDC(MyWin.hwnd);

	//�������̒��Ƀf�o�C�X�R���e�L�X�g�̃n���h�����쐬
	MyWin.hdc_double = CreateCompatibleDC(hdc);

	//�������̒��ɉ摜���쐬
	MyWin.hbmp_double = CreateCompatibleBitmap(
		hdc,
		MyWin.win_rect_cli.right,
		MyWin.win_rect_cli.bottom);

	//�f�o�C�X�R���e�L�X�g�ɉ摜��ݒ�
	SelectObject(MyWin.hdc_double, MyWin.hbmp_double);

	return;
}

//########## �E�B���h�E�v���V�[�W���֐� ##########
LRESULT CALLBACK MY_WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	//HDC�F�f�o�C�X�R���e�L�X�g�̃n���h��
	HDC hdc;

	//PAINTSTRUCT�F�E�B���h�E���Ƃ̕`������Ǘ�����\����
	PAINTSTRUCT ps;

	switch (msg)
	{

	case WM_CREATE:
		//�E�B���h�E�̐�����������

		//���������� �Q�[���ŗL�̐ݒ肱������ ����������

		//�e�L�X�g�̏�����
		InitTextParam();

		//�t�H���g���ꎞ�I�ɓǂݍ��߂Ȃ�������I��
		if (OnceFont_Read(hwnd) == FALSE) { return -1; }

		//�T�E���h�̏�����
		InitSoundParam(hwnd);

		//�T�E���h��ǂݍ��߂Ȃ�������I��
		if (MY_SOUND_Read(hwnd) == FALSE) { return -1; }

		//���������� �Q�[���ŗL�̐ݒ肱���܂� ����������

		//�^�C�}�[��10�~���Ԋu�ɃZ�b�g(�J�n)
		SetTimer(hwnd, TIMER_ID_FPS, 10, NULL);

		//�E�B���h�E�𐶐�����Ƃ��́A0��Ԃ�
		return 0;
	case WM_TIMER:

		switch (wp)
		{
		case TIMER_ID_FPS:

			//��ʍX�V�̎������擾����
			MY_FPS_UPDATE();

			//���L�[�������Ă��邩���肷��
			MY_CHECK_KEYDOWN();

			//���������� �Q�[���ŗL�̐ݒ肱������ ����������

			//���������� �Q�[���ŗL�̐ݒ肱���܂� ����������

			//�������[�W�����𔭐�
			InvalidateRect(hwnd, NULL, FALSE);
			//��ʂ��A�����ɍĕ`�悷��
			UpdateWindow(hwnd);

			//�w�肵��FPS�ɂȂ�悤�ɑ҂�
			MY_FPS_WAIT();

			break;
		}

		return 0;
	case WM_PAINT:
		//�E�B���h�E�����ĕ`�悷��Ƃ�

		//�f�o�C�X�R���e�L�X�g�̃n���h�����擾
		hdc = BeginPaint(hwnd, &ps);

		//���݂̃f�o�C�X�R���e�L�X�g��ۑ�����
		SaveDC(hdc);

		//���������� �Q�[���ŗL�̐ݒ肱������ ����������

		//�V�[�����Ƃɕ`�悷����̂�ς���
		selectSceneDraw(MyWin.hdc_double, MyWin.win_rect_cli);

		//���������� �Q�[���ŗL�̐ݒ肱���܂� ����������

		//���������̉摜��`��
		BitBlt(hdc,
			0, 0, MyWin.win_rect_cli.right, MyWin.win_rect_cli.bottom,
			MyWin.hdc_double, 0, 0, SRCCOPY);

		//�ۑ������f�o�C�X�R���e�L�X�𕜌�����
		RestoreDC(hdc, -1);

		//�f�o�C�X�R���e�L�X�g�̃n���h�����J������
		EndPaint(hwnd, &ps);

		return 0;
	case WM_LBUTTONDOWN:
		//�}�E�X�̍��{�^���������Ă���Ƃ�

		//�^�C�g���o�[���Ȃ��Ƃ�
		if (MyWin.win_mode == WIN_NO_TITLE)
		{
			//���b�Z�[�W��������
			PostMessage(
				hwnd,				//�E�B���h�E�n���h��
				WM_NCLBUTTONDOWN,	//��N���C�A���g�̈�����N���b�N����
				HTCAPTION,			//�^�C�g���o�[���N���b�N����
				MAKELPARAM(0, 0));	//�}�E�X�̍��W�F0,0

			return 0;
		}

		//�N���C�A���g�̈�O�ł��}�E�X�̓����̊Ď����J�n
		SetCapture(hwnd);

		break;

	case WM_LBUTTONUP:
		//�}�E�X�̍��{�^�����グ���Ƃ�

		//�^�C�g���o�[���Ȃ��Ƃ�
		if (MyWin.win_mode == WIN_NO_TITLE)
		{
			return 0;
		}

		//�N���C�A���g�̈�O�ł��}�E�X�̓����̊Ď����I��
		ReleaseCapture();

		break;
	case WM_RBUTTONDOWN:
		//�}�E�X�̉E�{�^�����������Ƃ�

		break;
	case WM_RBUTTONUP:
		//�}�E�X�̉E�{�^�����グ���Ƃ�

		break;
	case WM_MOUSEMOVE:
		//�}�E�X�J�[�\�����ړ������Ƃ�

		//DWORD�^(32�r�b�g)�̉���WORD(16�r�b�g)�����o��
		MyWin.point_Mouse.x = LOWORD(lp);

		//DWORD�^(32�r�b�g)�̏��WORD(16�r�b�g)�����o��
		MyWin.point_Mouse.y = HIWORD(lp);

		//�N���C�A���g�̈�O�̑Ώ�
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
		//��ʂ̃T�C�Y���ς�����Ƃ�

		//DWORD�^(32�r�b�g)�̏��WORD(16�r�b�g)�����o��
		MyWin.win_size.bottom = HIWORD(lp);

		//DWORD�^(32�r�b�g)�̉���WORD(16�r�b�g)�����o��
		MyWin.win_size.right = LOWORD(lp);

		break;
	case WM_KEYDOWN:
		//�L�[�{�[�h�ŃL�[���������Ƃ�

		return 0;
	case WM_KEYUP:
		//�L�[�{�[�h�ŃL�[���������Ƃ�

		return 0;
	case WM_CHAR:
		//���z�L�[�R�[�h�𕶎��ɕϊ������Ƃ�

		return 0;
	case WM_SYSKEYDOWN:
		//�V�X�e�����̃L�[(Alt�L�[)���������Ƃ�

		return 0;
	case WM_SYSKEYUP:
		//�V�X�e�����̃L�[(Alt�L�[)���グ���Ƃ�

		return 0;
	case WM_SYSCHAR:
		//���z�V�X�e���L�[�R�[�h�𕶎��ɕϊ������Ƃ�

		return 0;
	case MM_MCINOTIFY:
		//MP3���Đ�

		break;
	case WM_CLOSE:
		//����{�^�����������Ƃ�

		break;
	case WM_DESTROY:
		//�E�B���h�E���j�����ꂽ(�Ȃ��Ȃ���)�Ƃ�

		//���������� �Q�[���ŗL�̐ݒ肱������ ����������

		//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜����
		OnceFont_Remove(hwnd);

		//�ǂݍ��񂾃T�E���h�����폜����
		MY_SOUND_Remove();

		//���������� �Q�[���ŗL�̐ݒ肱���܂� ����������

		//���b�Z�[�W�L���[�� WM_QUIT �𑗂�
		PostQuitMessage(0);

		return 0;
	}

	//�f�t�H���g�̃E�B���h�E�v���V�[�W���֐����Ăяo��
	return DefWindowProc(hwnd, msg, wp, lp);
}