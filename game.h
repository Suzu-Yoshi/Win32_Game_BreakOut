//����������������������������������������
//game.h
//����������������������������������������

//########## �}�N����` ##########

//�Q�[���E�B���h�E�̏ꏊ��傫����ݒ�
#define GAME_LEFT		100		//���̈ʒu
#define GAME_TOP		100		//�c�̈ʒu
#define GAME_RIGHT		700		//��
#define GAME_BOTTOM		700		//����
#define GAME_POS_X		  0		//�����X���W
#define GAME_POS_Y		  0		//�����Y���W

//�����̖��O
#define GAME_MY_NAME		"SUZUKI"

//�Q�[���̃^�C�g��
#define GAME_TITLE			"BREAK OUT"

//�Q�[���̃^�C�g���̉�
#define GAME_TITLE_START	"SPACE PUSH START"

//########## �񋓌^ ##########

//�Q�[���̃V�[���ݒ�
enum GAME_SCENE
{
	SCENE_TITLE,	//�Q�[���J�n
	SCENE_PLAY,		//�Q�[����
	SCENE_END		//�Q�[���I��
};

//��������������������������������������������������������
//2��ڈȍ~�̃w�b�_�t�@�C���ǂݍ��݂�
//�v���g�^�C�v�錾������`����邱�ƂɂȂ�
//�R���p�C���G���[�ɂȂ�̂�h��
#pragma once	//��d�C���N���[�h�̖h�~
//��������������������������������������������������������

//########## �O���[�o���ϐ� �Q�Ƃ̐錾 ##########

//���������� �{�̂�game.cpp ����������

extern int GAME_scene;		//�Q�[���̃V�[��

//���������� �{�̂�game.cpp ����������

//##########  �֐� �Q�Ƃ̐錾 ##########

//���������� �{�̂�game.cpp ����������

extern VOID InitGameParam(VOID);			//�Q�[��������������
extern VOID selectSceneDraw(HDC, RECT);		//�V�[�����Ƃɕ`���ς���
extern VOID DrawTitle(HDC, RECT);			//�^�C�g����ʂ̔w�i��`�悷��

//���������� �{�̂�game.cpp ����������