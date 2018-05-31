//=============================================================================
//
// ���f������ [boss.h]
// Author : GP11B243 33 �R�{ �s��
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BOSS_MAX			(1)	// ���ł�̂���

// ����rotDest.y�̒l
#define ue				(3.14f)
#define migiue			(-2.36f)
#define migi			(-1.57f)
#define migishita		(-0.79f)
#define shita			(0.00f)
#define hidarishita	(0.79f)
#define hidari			(1.57f)
#define hidariue		(2.36f)

// �U�����s������
#define BOSSACTTIME		(0.8f)					// 1.0��1�b��1�x
#define BOSSACT			(BOSSACTTIME*60)		// 60FPS�Ȃ̂�60�{

// ���̃��[�h�ւ̈ڍs���J�n����܂ł̎���

#define BOSSLIFE		(4500)	// �{�X()��HP
#define BOSSKAITENSPEED	(D3DX_PI * 0.0002f)
#define BOSSKAITENHANKEI	(450.0f)
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
	float			acttime;		// ���슴�o
	float			boss_maxlife;	// �{�X�̗̑͂̍ő�l
	float			boss_life;		// �{�X�̌��݂̗̑�
	float			kaiten;			// ��]�ړ��ɕK�v�Ȃ���
	float			rockon;			// ���@�Ɍ���������
	float			movesetting;	// ����p���݂̉�]�l
	int				movemode;		// ���쐧��
	bool			bossmoveok;		// �ړ����Ă��悢���ǂ���
	bool			moveon;			// �ړ����H


	//float
} BOSS;

typedef enum
{	//�s���p�^�[��

	DEBIRU,
	AHIRU,
	HENANO,
	MEKA,
	BOSSMOVEMAX,
	// �U������
	shot = 0,
} BOSSMODE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);

D3DXVECTOR3 GetPositionBoss(void);
D3DXVECTOR3 GetRotationBoss(void);
D3DXVECTOR3 GetRotationDestBoss(void);
BOSS *GetBoss(int no);

#endif
