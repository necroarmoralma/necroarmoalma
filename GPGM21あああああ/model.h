	//=============================================================================
//
// ���f������ [model.h]
// Author : GP11B243 33 �R�{ �s��
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "setting.h"
#include "xinput.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_MAX			(1)	// ���ł�̂���

// ����rotDest.y�̒l
#define ue				(3.14f)
#define migiue			(-2.36f)
#define migi			(-1.57f)
#define migishita		(-0.79f)
#define shita			(0.00f)
#define hidarishita	(0.79f)
#define hidari			(1.57f)
#define hidariue		(2.36f)
#define rolluptime		(1.0f)
#define ROLLLIMIT		(rolluptime * 60)		// 60FPS�������
#define rollcooltime	(3.0f)					// 1.0��1�b
#define COOLTIME		(rolluptime * 60)		// 60FPS�������
// �ő�HP
#define PLAYER_HP_MAX	(1000.0f)

#define	PITCH_MODEL		"data/MODEL/player.x"

#define	VALUE_MOVE_MODEL	(0.80f)						// �ړ����x
#define	RATE_MOVE_MODEL		(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_MODEL	(0.20f)						// ��]�����W��
#define	BULLET_SIZEX		(20.0f)						// �e�̑傫����lX
#define BULLET_SIZEY		(20.0f)						// �e�̑傫����lY
#define MODEL_MOVEROLL		(0.2f)						// �ړ����̉�]�p
#define MODEL_MOVEROLlX		(0.2f)						// �ړ����̉�](�O��)
#define MODEL_DISTANCE_CL	(8.0f)						// ���f���̒��S���瑫���܂ł̋���
#define MODEL_BAUNCE		(1.5f)						// ���]�ړ���



#define NOCONTROL			(0.2 * 60)	// 60fps
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

// ���f���\����
typedef struct
{

	// ���f���̒���
	float center;			// ���S�_�܂ł̋���
	float higher;			// ����

	bool			use;			// true �g�p�@false ���g�p
	D3DXVECTOR3		pos;			// ���f���̌��݈ʒu
	D3DXVECTOR3		oldpos;			// ���f����1�t���[���O�̍��W��ۑ�
	D3DXVECTOR3		rot;			// ���f���̌���(��])
	D3DXVECTOR3		scl;			// ���f���̑傫��(�X�P�[��)
	D3DXMATRIX		World;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3		move;			// �ړ���
	D3DXVECTOR3		puremove;		// ����������O�̏����Ȉړ���
	D3DXVECTOR3		rotDest;		// �ړI�̌���
	D3DXVECTOR3		oldrotDest;		// 1�O�̖ړI�̌���


	float			Maxlife;			// ������傭
	float			Nowlife;		// ���̗̑�
	bool			rollon;			// �����Ђ��Ă�?
	float			cooltime;		// �N�[���^�C��
	bool			control;		// �L�[�{�[�h���͉\���ǂ���
	bool			escapemode;		// �ǂɂ߂荞�܂Ȃ��悤�ɂ��Ă��邩�ǂ���(���false)

	// �}�b�v�Ƃ̊e�����̓����蔻��
	BOOL			tomapDown;			// �}�b�v�Ƃ̓����蔻��(������)
	BOOL			tomapUp;			// �}�b�v�Ƃ̓����蔻��(�����)
	BOOL			tomapFront;			// �}�b�v�Ƃ̓����蔻��(�O����)
	BOOL			tomapBack;			// �}�b�v�Ƃ̓����蔻��(������)
	BOOL			tomapRight;			// �}�b�v�Ƃ̓����蔻��(�E����)
	BOOL			tomapLeft;			// �}�b�v�Ƃ̓����蔻��(������)
	// ���C�ƃ}�b�v�̋���
	float			R_RtoMdistance;	// �E
	float			L_RtoMdistance;	// ��
	float			U_RtoMdistance;	// ��
	float			D_RtoMdistance;	// ��
	float			F_RtoMdistance;	// �O��
	float			B_RtoMdistance;	// ���
	// �^�C��
	STATUS			status;
	STATUS			taiya_status;
	// ��
	float			shot;					// ���̔��ˊԊu
	float			nowshot_evolve;			// ���̃|�C���g
	float			shot_evolve;			// ���x���A�b�v�ɕK�v�Ȑ��l
	int				shotlv;
	bool			shot_on;				// �e���łĂ邩�ǂ����̔���
	// �u�[�X�g
	float			boostgage;
	// �Q�[���{�҂ł̃��f��
	DWORD				NumMatModelgame;			// DWORD,D3DXMATERIAL�\���̂ւ̃|�C���^
	LPD3DXMESH			MeshModelgame;		// LPD3DXMESH,���[�h���ꂽ���b�V����\��ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	LPDIRECT3DTEXTURE9	TextureModelgame;			// �e�N�X�`���ǂݍ��ݏꏊ

} MODEL;



 // ���f����x�t�@�C���֘A�̍\����
typedef struct
{
	LPD3DXBUFFER	g_pD3DXBuffMatModel;	// LPD3DXBUFFER,�}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^D3DXMATERIAL�\���̂̔z�񂪊i�[
	DWORD			g_nNumMatModel;			// DWORD,D3DXMATERIAL�\���̂ւ̃|�C���^
	LPD3DXMESH		g_pD3DXMeshModel;		// LPD3DXMESH,���[�h���ꂽ���b�V����\��ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
} MODEL_XFILE;

// ���f���̓���
typedef enum
{
	model_game,
	model_title,
	MODELMOVETYPEMAX
} MODELMOVETYPE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitModel(int gametypeno);
void UninitModel(void);
void UpdateModel(int movetypeno);
void DrawModel(int gametypeno);

D3DXVECTOR3 GetPositionModel(void);
D3DXVECTOR3 GetRotationModel(void);
D3DXVECTOR3 GetRotationDestModel(void);
void model_RaypickTomap(void);
MODEL *GetModel(int no);

#endif
