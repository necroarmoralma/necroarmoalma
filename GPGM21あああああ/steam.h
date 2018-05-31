//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : GP11B243 33 �R�{ �s��
// �r���{�[�h�̃w�b�_�[������
//=============================================================================
#ifndef _STEAM_H_
#define _STEAM_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	STEAM_MAX				(300)
#define	STEAM_WIDTH				(20.0f)							// �e�̔��a��
#define	STEAM_HEIGHT			(20.0f)							// �e�̔��a��
#define	STEAMSPEED				(0.8f)
#define	STEAM_RELEASECOUNT		(1.0 * 60)						// �b���~FPS

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct {		// �o���b�g�\����
	D3DXMATRIX				mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3				pos;							// �ʒu
	D3DXVECTOR3				scl;							// �X�P�[��
	D3DXVECTOR3				move;							// �ړ���
	D3DXVECTOR3				rot;							// ��]
	D3DXVECTOR3				rotTarget;						// �^�[�Q�b�g�ւ̌���
	float					wide;							// ��
	float					height;							// ����
	int						g_nIdxShadow;					// �eID
	bool					gravity;						// �d�͂�L���ɂ��邩�ǂ���
	bool					use;							// �g�p���Ă��邩�ǂ���
	bool					moveon;							// �ړ��ʂ͊m�肵�Ă��邩?
	float					size_X;
	float					count;							// ���ł܂ł̎���
} STEAM;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSteam(void);
void UninitSteam(void);
void UpdateSteam(void);
void DrawSteam(void);
int SetSteam(D3DXVECTOR3 pos,float fx, float fy, D3DXCOLOR col);
STEAM *GetSteam(int no);

#endif
