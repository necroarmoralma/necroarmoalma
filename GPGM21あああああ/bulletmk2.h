//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : GP11B243 33 �R�{ �s��
// �r���{�[�h�̃w�b�_�[������
//=============================================================================
#ifndef _BULLETMK2_H_
#define _BULLETMK2_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BULLET_MAX	(3300)
//#define	VALUE_MOVE_MODEL	(0.80f)						// �ړ����x
#define	RATE_MOVE_MODEL		(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_MODEL	(0.20f)						// ��]�����W��
#define	BULLETMK2_WIDTH		(20.0f)						// �e�̔��a��
#define	BULLETMK2_HEIGHT	(20.0f)						// �e�̔��a��
#define BULLETMK2LIMIT				(11000)				// ���@�e���ړ�����̈�


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
	float					hoseix;
	float					hoseiz;
	float					life;							//			��������
} BULLETMK2;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBulletmk2(void);
void UninitBulletmk2(void);
void UpdateBulletmk2(void);
void DrawBulletmk2(void);
int SetBulletmk2(D3DXVECTOR3 pos,float fx, float fy,float SIDE,float UP, D3DXCOLOR col);
BULLETMK2 *GetBulletmk2(int no);


#endif
