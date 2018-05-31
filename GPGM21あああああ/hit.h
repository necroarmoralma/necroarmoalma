//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : GP11B243 33 �R�{ �s��
// �r���{�[�h�̃w�b�_�[������
//=============================================================================
#ifndef _HIT_H_
#define _HIT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BULLET_MAX	(300)
#define	VALUE_MOVE_MODEL	(0.80f)						// �ړ����x
#define	RATE_MOVE_MODEL		(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_MODEL	(0.20f)						// ��]�����W��
#define	HIT_WIDTH		(20.0f)							// �e�̔��a��
#define	HIT_HEIGHT	(20.0f)							// �e�̔��a��
#define HITON		(0.5*60.0f)					// �Đ�����
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
	float					life;
} HIT;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitHit(void);
void UninitHit(void);
void UpdateHit(void);
void DrawHit(void);
int SetHit(D3DXVECTOR3 pos, float fx, float fy, D3DXCOLOR col);
HIT *GetHit(int no);

#endif
