//=============================================================================
//
// ���f������ [modelbooster.h]
// Author : GP11B243 33 �R�{ �s��
//
//=============================================================================
#ifndef _MODELBOOSTER_H_
#define _MODELBOOSTER_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODELBOOSTER_MAX	(1)	// ���ł�̂���
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

// ���f���\����
typedef struct
{
	bool			use;			// true �g�p�@false ���g�p
	D3DXVECTOR3		pos;			// ���f���̌��݈ʒu
	D3DXVECTOR3		rot;			// ���f���̌���(��])
	D3DXVECTOR3		scl;			// ���f���̑傫��(�X�P�[��)
	D3DXMATRIX		World;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3		oldpos;			// �ړ�����O�̍��W
	D3DXVECTOR3		move;			// �ړ���
	D3DXVECTOR3		puremove;		// ����������O�̏����Ȉړ���
	D3DXVECTOR3		rotDest;		// �ړI�̌���
	D3DXVECTOR3		oldrotDest;		// 1�O�̖ړI�̌���
	float			Maxlife;			// ������傭
	float			Nowlife;		// ���̗̑�
	float			rollup;			// �ً}���
	bool			rolluse;		// �ً}���g�����H
	bool			rollon;			// �����ЂȂ��H
	float			cooltime;		// �N�[���^�C��
	int				g_nIdxShadow;				// �eID
	float			g_fSizeShadow;				// �e�̃T�C�Y
	D3DXCOLOR		g_colShadow;				// �e�̐F
	bool			roton;						// �����͉̂�]
} MODELBOOSTER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitModelBooster(void);
void UninitModelBooster(void);
void UpdateModelBooster(void);
void DrawModelBooster(void);

D3DXVECTOR3 GetPositionModelBooster(void);
D3DXVECTOR3 GetRotationModelBooster(void);
D3DXVECTOR3 GetRotationDestModelBooster(void);
MODELBOOSTER *GetModelBooster(int no);

#endif
