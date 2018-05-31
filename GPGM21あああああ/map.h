//=============================================================================
//
// ���f������ [map.h]
// Author : GP11B243 33 �R�{ �s��
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAP_MAX			(1)	// ���ł�̂���

// ����rotDest.y�̒l
#define ue				(3.14f)
#define migiue			(-2.36f)
#define migi			(-1.57f)
#define migishita		(-0.79f)
#define shita			(0.00f)
#define hidarishita	(0.79f)
#define hidari			(1.57f)
#define hidariue		(2.36f)
#define MAPACTTIME		(0.5f)					// 1.0��1�b��1�x
#define MAPACT			(MAPACTTIME*60)		// 60FPS�Ȃ̂�60�{
#define MAPLIFE		(1000)	// �{�X(�T���f�B�E�X16��)��HP
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
	float			map_maxlife;	// �{�X�̗̑͂̍ő�l
	float			map_life;		// �{�X�̌��݂̗̑�

	// ��������̓e�X�g
	LPD3DXMESH		MeshMap;		// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXBUFFER	BuffMatMap;		//���b�V���̃}�e���A�������i�[/
	DWORD			NumMatMap;		// �������̑���
} MAP;

//typedef enum
//{	//�s���p�^�[��
//
//	// �U������
//	ssshot = 0,
//} MAPMODE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);

D3DXVECTOR3 GetPositionMap(void);
D3DXVECTOR3 GetRotationMap(void);
D3DXVECTOR3 GetRotationDestMap(void);
MAP *GetMap(int no);

#endif
