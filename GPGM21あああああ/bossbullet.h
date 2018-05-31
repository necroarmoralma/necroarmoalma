//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : GP11B243 33 �R�{ �s��
// �r���{�[�h�̃w�b�_�[������
//=============================================================================
#ifndef _BOSSBULLET_H_
#define _BOSSBULLET_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BOSSBULLET_MAX	(2300)
#define	RATE_MOVE_MODEL		(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_MODEL	(0.20f)						// ��]�����W��
#define	BOSSBULLET_WIDTH		(30.0f)							// �e�̔��a��
#define	BOSSBULLET_HEIGHT	(30.0f)							// �e�̔��a��
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct {		// �o���b�g�\����


	int						count;							// �o���b�g�̐�������
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
	float					bossbullet_rot;					// ��]�p
	float					live;							// �{�X�̒e�����݂ł��鎞��
} BOSSBULLET;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBossbullet(void);
void UninitBossbullet(void);
void UpdateBossbullet(void);
void DrawBossbullet(void);
int SetBossbullet(D3DXVECTOR3 pos, float fx, float fy, D3DXCOLOR col,float bossbulletrot);
int SetEnemybullet(D3DXVECTOR3 pos, float fx, float fy, D3DXCOLOR col, float enemytargetrot);
BOSSBULLET *GetBossbullet(int no);

#endif
