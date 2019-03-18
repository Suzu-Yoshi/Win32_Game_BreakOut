///����������������������������������������
//game.h
///����������������������������������������

///########## �}�N����` ##########

#define PI 3.14159

//�Q�[���E�B���h�E�̏ꏊ��傫����ݒ�
#define GAME_LEFT		100		//���̈ʒu
#define GAME_TOP		100		//�c�̈ʒu
#define GAME_RIGHT		700		//��
#define GAME_BOTTOM		700		//����
#define GAME_POS_X		  0		//�����X���W
#define GAME_POS_Y		  0		//�����Y���W

#define GAME_PLAY_TOP		100	//�Q�[����ʂ̏�ʒu
#define GAME_PLAY_LEFT		0	//�Q�[����ʂ̍��ʒu
#define GAME_PLAY_RIGHT		700	//�Q�[����ʂ̉E�ʒu
#define GAME_PLAY_BOTTOM	700	//�Q�[����ʂ̉��ʒu

#define GAME_MY_NAME		"HAMAJO"				//�����̖��O
#define GAME_TITLE			"BREAK OUT"				//�Q�[���̃^�C�g��
#define GAME_TITLE_START	"PUSH SPACE >> START"	//�Q�[���̃^�C�g���̉�

#define GAME_BLOCK_WIDTH	70	//�u���b�N�̕�
#define GAME_BLOCK_HEIGHT	35	//�u���b�N�̍���

#define GAME_BLOCK_X_MAX	10	//�u���b�N�̉��̍ő�l
#define GAME_BLOCK_Y_MAX	6	//�u���b�N�̏c�̍ő�l

#define BAR_X		250		//�o�[�̉��̈ʒu 
#define BAR_Y		600		//�o�[�̏c�̈ʒu
#define BAR_WIDHT	200		//�o�[�̕�
#define BAR_HEIGHT	25		//�o�[�̍���

#define BALL_X		335		//�{�[���̉��̈ʒu 
#define BALL_Y		500		//�{�[���̏c�̈ʒu
#define BALL_WIDHT	30		//�{�[���̕�
#define BALL_HEIGHT	30		//�{�[���̍���


#define COL_R		1		//�u���b�N�̐F(��)
#define COL_G		2		//�u���b�N�̐F(��)
#define COL_B		3		//�u���b�N�̐F(��)
#define COL_Y		4		//�u���b�N�̐F(��)
#define COL_P		5		//�u���b�N�̐F(��)
#define COL_W		6		//�u���b�N�̐F(��)

#define SPD_NOMAL	3	//�o�[�̑���(�ʏ�)
#define SPD_FAST	6	//�o�[�̑���(����)
#define SPD_STAR	9	//�o�[�̑���(����)

///########## �񋓌^ ##########

//�Q�[���̃V�[���ݒ�
enum GAME_SCENE
{
	SCENE_TITLE,	//�Q�[���J�n
	SCENE_PLAY,		//�Q�[����
	SCENE_END		//�Q�[���I��
};

///��������������������������������������������������������
#pragma once	//��d�C���N���[�h�̖h�~
///��������������������������������������������������������

///########## �O���[�o���ϐ� �Q�Ƃ̐錾 ##########

///���������� �{�̂�game.cpp ����������

extern int GAME_scene;		//�Q�[���̃V�[��

///���������� �{�̂�game.cpp ����������

///##########  �֐� �Q�Ƃ̐錾 ##########

///���������� �{�̂�game.cpp ����������

extern VOID InitGameParam(HWND);			//�Q�[��������������
extern VOID selectSceneDraw(HDC, RECT);		//�V�[�����Ƃɕ`���ς���
extern VOID DrawTitle(HDC, RECT);			//�^�C�g����ʂ̔w�i��`�悷��
extern VOID DrawGame(HDC, RECT);			//�Q�[���̔w�i��`�悷��
extern VOID CalcTamaMove(VOID);				//�ʂ̈ړ��ʂ��v�Z����
extern VOID BarTamaCollision(VOID);			//�o�[�Ƌʂ̏Փ˔��������

///���������� �{�̂�game.cpp ����������
