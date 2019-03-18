///����������������������������������������
//keyboad.cpp
///����������������������������������������

///########## �w�b�_�t�@�C���ǂݍ��� ##########
#include <windows.h>

#include "keyboad.h"

///########## �O���[�o���ϐ��̐錾�Ə����� ##########

//�L�[�{�[�h�\���̂̕ϐ�
MY_KEY MyKey;

///########## �v���g�^�C�v�錾 ##########

//�ǂ̃L�[�������Ă��邩����
VOID MY_CHECK_KEYDOWN(VOID);

///########## �ǂ̃L�[�������Ă��邩���肷��֐� ##########
VOID MY_CHECK_KEYDOWN(VOID)
{
	//���ׂẲ��z�L�[�̌��݂̏�Ԃ���C�Ɏ擾����
	GetKeyboardState(MyKey.KeyBoard);

	//���z�L�[�R�[�h�ŁAA�`Z�A0�`9�́AASCII�R�[�h���w��
	BYTE IskeyDown_UP = MyKey.KeyBoard[VK_UP] & 0x80;
	BYTE IskeyDown_DOWN = MyKey.KeyBoard[VK_DOWN] & 0x80;
	BYTE IskeyDown_RIGHT = MyKey.KeyBoard[VK_RIGHT] & 0x80;
	BYTE IskeyDown_LEFT = MyKey.KeyBoard[VK_LEFT] & 0x80;
	BYTE IskeyDown_SPACE = MyKey.KeyBoard[VK_SPACE] & 0x80;

	//��L�[��������Ă��邩���肷��
	if (IskeyDown_UP != 0)
	{
		MyKey.IsDownUP = TRUE;
	}
	else
	{
		MyKey.IsDownUP = FALSE;
	}

	//���L�[��������Ă��邩���肷��
	if (IskeyDown_DOWN != 0)
	{
		MyKey.IsDownDOWN = TRUE;
	}
	else
	{
		MyKey.IsDownDOWN = FALSE;
	}

	//�E�L�[��������Ă��邩���肷��
	if (IskeyDown_RIGHT != 0)
	{
		MyKey.IsDownRIGHT = TRUE;
	}
	else
	{
		MyKey.IsDownRIGHT = FALSE;
	}

	//���L�[��������Ă��邩���肷��
	if (IskeyDown_LEFT != 0)
	{
		MyKey.IsDownLEFT = TRUE;
	}
	else
	{
		MyKey.IsDownLEFT = FALSE;
	}

	//�X�y�[�X�L�[��������Ă��邩���肷��
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