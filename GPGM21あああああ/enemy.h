//=============================================================================
//
// ���f������ [enemy.h]
// Author : GP11B243 33 �R�{ �s��
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "setting.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMYMAX			(15)					// �G�l�~�[�̍ő吔



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
#define ENEMYACTTIME		(0.8f)					// 1.0��1�b��1�x
#define ENEMYACT			(ENEMYACTTIME*60)		// 60FPS�Ȃ̂�60�{

// ���̃��[�h�ւ̈ڍs���J�n����܂ł̎���

#define ENEMYLIFE		(450)	// �Ă���HP
#define ENEMYKAITENSPEED	(D3DX_PI * 0.0002f)
#define ENEMYKAITENHANKEI	(450.0f)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

// ���f���\����
typedef struct
{
	bool			use;			// true �g�p�@false ���g�p
	bool			live;			// ��������
	D3DXVECTOR3		oldpos;			// �ړ�����O�̍��W
	float			acttime;		// ���슴�o
	float			enemy_maxlife;	// �{�X�̗̑͂̍ő�l
	float			enemy_life;		// �{�X�̌��݂̗̑�
	float			kaiten;			// ��]�ړ��ɕK�v�Ȃ���
	float			rockon;			// ���@�Ɍ���������
	float			movesetting;	// ����p���݂̉�]�l
	float			center;			// ���S�_�܂ł̋���
	int				movemode;		// ���쐧��
	bool			enemymoveok;		// �ړ����Ă��悢���ǂ���
	bool			moveon;			// �ړ���
	STATUS			status;
	
	//	�c�p
	bool			warning;		// �x�������ǂ���
	bool			muki;			// �������Ă����������
									//float
} ENEMY;

typedef enum
{	//�s���p�^�[��

	SHOT
} ENEMYMODE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void DeleatEnemy(int no);
void CreateEnemy(D3DXVECTOR3 pos);

D3DXVECTOR3 GetPositionEnemy(int no);
D3DXVECTOR3 GetRotationEnemy(int no);
D3DXVECTOR3 GetRotationDestEnemy(int no);
ENEMY *GetEnemy(int no);
void SetShikenkan(void);

#endif
