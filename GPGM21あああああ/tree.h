//=============================================================================
//
// �؏��� [tree.h]
//  Author : HAL�Q�[���w�ȓ�N���ے�1�N�@�R�{�s��
//
//=============================================================================
#ifndef _TREE_H_
#define _TREE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TREE			(256)	// �؍ő吔
#define	TREE_WIDTH			(15.0f)							// �؂̔��a��
#define	TREE_HEIGHT			(80.0f)							// �؂̔��a����
#define	VALUE_MOVE_TREE		(3.00f)							// �ړ����x

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 scl;		// �X�P�[��
	float fWidth;			// ��
	float fHeight;			// ����
	int nIdxShadow;			// �eID
	bool bUse;				// �g�p���Ă��邩�ǂ���
} TREE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTree(void);
void UninitTree(void);
void UpdateTree(void);
void DrawTree(void);

int SetTree(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col);

TREE *GetTree(int no);

#endif
