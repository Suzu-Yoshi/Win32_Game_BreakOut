///����������������������������������������
//game.cpp
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <windows.h>
#include <Math.h>

#include "text.h"
#include "game.h"	
#include "sound.h"
#include "keyboad.h"

///########## �v���g�^�C�v�錾 ##########

VOID InitGameParam(HWND);			//�Q�[��������������
VOID selectSceneDraw(HDC, RECT);	//�V�[�����Ƃɕ`���ς���
VOID DrawTitle(HDC, RECT);			//�^�C�g����ʂ̔w�i��`�悷��
VOID DrawGame(HDC, RECT);			//�Q�[���̔w�i��`�悷��
VOID MoveBar(VOID);					//�o�[���ړ�����
VOID BarTamaCollision(VOID);		//�o�[�Ƌʂ̏Փ˔��������
VOID CalcTamaMove(VOID);			//�ʂ̈ړ��ʂ��v�Z����
VOID WallTamaCollision(VOID);		//�ǂƋʂ̏Փ˔��������

///########## �O���[�o���ϐ��̐錾�Ə����� ##########

int GAME_scene;		//�Q�[���̃V�[��

int block[GAME_BLOCK_Y_MAX][GAME_BLOCK_X_MAX]	//�u���b�N�̕\�����
= { {0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
};

int block_col[GAME_BLOCK_Y_MAX][GAME_BLOCK_X_MAX]	//�u���b�N�̐F
= { {COL_R,COL_R,COL_R,COL_R,COL_R,COL_R,COL_R,COL_R,COL_R,COL_R},
	{COL_G,COL_G,COL_G,COL_G,COL_G,COL_G,COL_G,COL_G,COL_G,COL_G},
	{COL_B,COL_B,COL_B,COL_B,COL_B,COL_B,COL_B,COL_B,COL_B,COL_B},
	{COL_Y,COL_Y,COL_Y,COL_Y,COL_Y,COL_Y,COL_Y,COL_Y,COL_Y,COL_Y},
	{COL_P,COL_P,COL_P,COL_P,COL_P,COL_P,COL_P,COL_P,COL_P,COL_P},
	{COL_W,COL_W,COL_W,COL_W,COL_W,COL_W,COL_W,COL_W,COL_W,COL_W}
};

RECT bar;			//�o�[�̈ʒu�E�傫��
RECT tama;			//�ʂ̈ʒu�E�傫��
RECT play;			//�Q�[����ʂ̈ʒu�E�傫��
int barSpeed;		//�o�[�̈ړ����x
int tamaSpeed;		//�ʂ̈ړ����x

int angle;			//�ʂ̊p�x
double radian;		//���W�A��

int tamaCosX;
int tamaSinY;

///########## �Q�[��������������֐� ##########
VOID InitGameParam(HWND hWnd)
{
	GAME_scene = (int)SCENE_TITLE;	//�Q�[���̃V�[���ݒ�

	GAME_scene = (int)SCENE_PLAY;	//�Q�[���̃V�[���ݒ�

	//�u���b�N�̏�����
	for (int tate = 0; tate < GAME_BLOCK_Y_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_BLOCK_X_MAX; yoko++)
		{
			block[tate][yoko] = 0;
		}
	}

	//�Q�[����ʂ̈ʒu�Ƒ傫����������
	play.top = GAME_PLAY_TOP;
	play.left = GAME_PLAY_LEFT;
	play.right = GAME_PLAY_RIGHT;
	play.bottom = GAME_PLAY_BOTTOM;

	//�o�[�̈ʒu�Ƒ傫����������
	bar.top = BAR_Y;
	bar.left = BAR_X;
	bar.bottom = BAR_Y + BAR_HEIGHT;
	bar.right = BAR_X + BAR_WIDHT;

	barSpeed = SPD_NOMAL;	//�o�[�̑�����������

	//�{�[���̈ʒu�Ƒ傫����������
	tama.top = BALL_Y;
	tama.left = BALL_X;
	tama.bottom = BALL_Y + BALL_HEIGHT;
	tama.right = BALL_X + BALL_WIDHT;

	tamaSpeed = SPD_NOMAL;	//�ʂ̑�����������

	angle = 45;			//�ʂ̊p�x��������

	CalcTamaMove();		//�ʂ̌�����������

	return;
}

///########## �Q�[�����I������֐� ##########
VOID RemoveGameParam(VOID)
{

}

///########## �V�[�����Ƃɕ`���ς���֐� ##########
VOID selectSceneDraw(HDC hdc, RECT rect_cli)
{
	switch (GAME_scene)
	{

	case SCENE_TITLE:	//�^�C�g�����

		DrawTitle(hdc, rect_cli);		//�^�C�g����ʂ̕`��
		MY_SOUND_PLAY(MySnd_BGM_title);	//�^�C�g����BGM��炷

		if (MyKey.IsDownSPACE == TRUE)		//�X�y�[�X�L�[�������ꂽ�Ƃ�
		{
			GAME_scene = (int)SCENE_PLAY;	//�Q�[�����Ɉړ�
			MY_SOUND_STOP(MySnd_BGM_title);	//BGM���~�߂�
		}

		break;
	case SCENE_PLAY:	//�Q�[����

		MoveBar();		//�o�[���ړ�



		//�ʂ̈ړ�
		tama.top += tamaSinY;
		tama.bottom += tamaSinY;

		tama.left += tamaCosX;
		tama.right += tamaCosX;


		WallTamaCollision();		//�ǂƋʂ̏Փ˔���
		//BarTamaCollision();			//�o�[�Ƌʂ̓����蔻��

		CalcTamaMove();				//�ʂ̊p�x�𔽓]����

		DrawGame(hdc, rect_cli);	//�Q�[����ʂ̕`��

		break;

	case SCENE_END:		//�Q�[���I��


		break;

	default:

		break;
	}

	return;
}

///########## �^�C�g����ʂ̔w�i��`�悷��֐� ##########
VOID DrawTitle(HDC hdc, RECT rect_c)
{
	//�w�i��`��
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));					//�u���V���쐬	
	SelectObject(hdc, hbrush);												//�u���V��ݒ�
	Rectangle(hdc, rect_c.left, rect_c.top, rect_c.right, rect_c.bottom);	//�l�p��`��
	DeleteObject(hbrush);													//�u���V���폜

	//������`��
	MY_TextOut(hdc, &MyText_name_OL);		//���O(�֊s)
	MY_TextOut_Gra(hdc, &MyText_name);		//���O
	MY_TextOut(hdc, &MyText_title_OL);		//�^�C�g��(�֊s)
	MY_TextOut_Gra(hdc, &MyText_title);		//�^�C�g��
	MY_TextOut(hdc, &MyText_title_st_OL);	//�X�^�[�g(�֊s)
	MY_TextOut_Gra(hdc, &MyText_title_st);	//�X�^�[�g

	return;
}

///########## �Q�[���̔w�i��`�悷��֐� ##########
VOID DrawGame(HDC hdc, RECT rect_c)
{
	//�w�i��`��
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));							//�u���V���쐬	
	SelectObject(hdc, hbrush);												//�u���V��ݒ�
	Rectangle(hdc, rect_c.left, rect_c.top, rect_c.right, rect_c.bottom);	//�l�p��`��
	DeleteObject(hbrush);													//�u���V���폜

	//�u���b�N��`��
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
				(tate + 0) * GAME_BLOCK_HEIGHT + play.top,	//�Q�[����ʗp�Ɉʒu�����炷
				(yoko + 1) * GAME_BLOCK_WIDTH,
				(tate + 1) * GAME_BLOCK_HEIGHT + play.top);	//�Q�[����ʗp�Ɉʒu�����炷

			DeleteObject(hbrush_block_col);
		}
	}

	//�o�[��`��
	HBRUSH hbrush_bar = CreateSolidBrush(RGB(0, 161, 233));
	SelectObject(hdc, hbrush_bar);
	Rectangle(hdc, bar.left, bar.top, bar.right, bar.bottom);
	DeleteObject(hbrush_bar);

	//�{�[����`��
	HBRUSH hbrush_tama = CreateSolidBrush(RGB(255, 215, 0));
	SelectObject(hdc, hbrush_tama);
	Ellipse(hdc, tama.left, tama.top, tama.right, tama.bottom);
	DeleteObject(hbrush_tama);

	return;
}

///########## �o�[���ړ�����֐� ##########
VOID MoveBar(VOID)
{
	if (MyKey.IsDownRIGHT == TRUE)	//�E���������Ƃ�
	{
		if (bar.right + barSpeed < GAME_PLAY_RIGHT)	//�E��
		{
			bar.right += barSpeed;
			bar.left += barSpeed;
		}
	}

	if (MyKey.IsDownLEFT == TRUE)	//�����������Ƃ�
	{
		if (bar.left - barSpeed > GAME_PLAY_LEFT)	//����
		{
			bar.right -= barSpeed;
			bar.left -= barSpeed;
		}
	}
}

///########## �o�[�Ƌʂ̏Փ˔��������֐� ##########
VOID BarTamaCollision(VOID)
{

	if (bar.top < tama.bottom		//�o�[(��)�Ƌ�(��)�̔���
		&& bar.bottom > tama.top)	//�o�[(��)�Ƌ�(��)�̔���
	{
		angle = 360 - angle;		//�p�x�𔽓]������
	}

	//if (bar.left < tama.right 		//�o�[(��)�Ƌ�(�E)�̔���
	//	&& bar.right > tama.left)	//�o�[(�E)�Ƌ�(��)�̔���
	//{
	//	angle = 180 - angle;		//�p�x�𔽓]������
	//}	

	return;
}

///########## �ǂƋʂ̏Փ˔��������֐� ##########
VOID WallTamaCollision(VOID)
{

	if (tama.top < GAME_PLAY_TOP			//��(��)�ƕ�(��)�̔���
		|| tama.bottom > GAME_PLAY_BOTTOM)	//��(��)�ƕ�(��)�̔���
	{
		angle = 360 - angle;		//�p�x�𔽓]������
	}

	if (tama.left < GAME_PLAY_LEFT 			//��(��)�ƕ�(��)�̔���
		|| tama.right > GAME_PLAY_RIGHT)	//��(�E)�ƕ�(�E)�̔���
	{
		angle = 180 - angle;		//�p�x�𔽓]������
	}

	return;
}

///########## �ʂ̈ړ��ʂ��v�Z����֐� ##########
VOID CalcTamaMove(VOID)
{
	radian = angle * PI / 180;				//�p�x�����W�A���ɕύX
	tamaSinY = sin(radian) * tamaSpeed;		//�ʂ̌������v�Z(�c)
	if (tamaSinY > 0) { tamaSinY -= 1; }	//������

	tamaCosX = cos(radian) * tamaSpeed;		//�ʂ̌������v�Z(��)
	if (tamaCosX > 0) { tamaCosX -= 1; }	//������

	//tama.left += cos(radian) * tamaSpeed;
	//tama.top += sin(radian) * tamaSpeed;
	//tama.right += cos(radian) * tamaSpeed;
	//tama.bottom += sin(radian) * tamaSpeed;

	return;
}