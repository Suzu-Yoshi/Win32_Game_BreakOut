///����������������������������������������
//game.cpp
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <windows.h>

#include "text.h"
#include "game.h"	
#include "sound.h"
#include "keyboad.h"

///########## �v���g�^�C�v�錾 ##########

VOID InitGameParam(HWND);			//�Q�[��������������
VOID selectSceneDraw(HDC, RECT);	//�V�[�����Ƃɕ`���ς���
VOID DrawTitle(HDC, RECT);			//�^�C�g����ʂ̔w�i��`�悷��

///########## �O���[�o���ϐ��̐錾�Ə����� ##########

int GAME_scene;		//�Q�[���̃V�[��

///########## �Q�[��������������֐� ##########
VOID InitGameParam(HWND hWnd)
{
	//�Q�[���̃V�[���ݒ�
	GAME_scene = (int)SCENE_TITLE;
}

///########## �Q�[�����I������֐� ##########
VOID RemoveGameParam(VOID)
{


}


///########## �V�[�����Ƃɕ`���ς���֐� ##########
VOID selectSceneDraw(HDC hdc , RECT rect_cli)
{
	switch (GAME_scene)
	{

	case SCENE_TITLE:
		//�^�C�g�����

		//�^�C�g����ʂ̕`��
		DrawTitle(hdc, rect_cli);

		//�^�C�g����BGM��炷
		MY_SOUND_PLAY(MySnd_BGM_title);

		//�X�y�[�X�L�[�������ꂽ�Ƃ�
		if()

		break;
	case SCENE_PLAY:
		//�Q�[����


		break;

	case SCENE_END:
		//�Q�[���I��


		break;
	}

	return;
}

///########## �^�C�g����ʂ̔w�i��`�悷��֐� ##########
VOID DrawTitle(HDC hdc, RECT rect_c)
{
	//+++++ �w�i�̕`�� ++++++++++++++++++++

	//�u���V���쐬
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));

	//�u���V��ݒ�
	SelectObject(hdc, hbrush);

	//�l�p��`��
	Rectangle(
		hdc,			//�f�o�C�X�R���e�L�X�g�̃n���h��
		rect_c.left,	//�l�p�̍����X���W
		rect_c.top,		//�l�p�̍����Y���W
		rect_c.right,	//�l�p�̉E����X���W
		rect_c.bottom);	//�l�p�̉E����Y���W

	//�u���V���폜
	DeleteObject(hbrush);

	//+++++ ������`�� ++++++++++++++++++++

	MY_TextOut(hdc, &MyText_name_OL);		//���O(�֊s)
	MY_TextOut_Gra(hdc, &MyText_name);		//���O
	MY_TextOut(hdc, &MyText_title_OL);		//�^�C�g��(�֊s)
	MY_TextOut_Gra(hdc, &MyText_title);		//�^�C�g��
	MY_TextOut(hdc, &MyText_title_st_OL);	//�X�^�[�g(�֊s)
	MY_TextOut_Gra(hdc, &MyText_title_st);	//�X�^�[�g


	return;
}