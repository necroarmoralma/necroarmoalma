//*****************************************************************************************************
// �t�@�C����:	setting.h
// �쐬��:		12��16��
// ����:		�Q�[�����Ŏg�����̓ǂݍ��ݐݒ�
//*****************************************************************************************************

#ifndef _SETTING_H_
#define _SETTING_H_

//*****************************************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************************************

#include "main.h"
#include "xinput.h"
//*****************************************************************************************************
// �}�N����`
//*****************************************************************************************************
#define DROWMAX_X		(360.0f)			//�@x�����̕`��͈�
#define DROWMAX_Z		(400.0f)			// �x�����̕`��͈�
#define PODREFRECT		(2.8)				// �ǂɓ����������ǂꂾ���̑傫���Œ��˕Ԃ�̂�
#define STICKBASE		(1000)				// �X�e�B�b�N���͂��󂯕t�����l(���Ȃ�����Ə���ɓ�������듮�삵����c)
#define TRIGGERBASE			(10)			// �g���K�[�̓��͂��󂯕t�����l(0�`255)
#define EVOLVEPOINT_BOSS	(10.0f)			// �{�X���j�ŖႦ��i���|�C���g

#define SHOTKANKAKU		(0.5*60*0.5)		// �ʏ�V���b�g�̊��o
//*****************************************************************************************************
// �\���̒�`
//*****************************************************************************************************


typedef enum
{
	RAY_FRONT,
	RAY_RIGHT,
	RAY_LEFT,
	RAY_BACK,
	RAY_UP,
	RAY_DOWN,
	RAY_MAX
} RAYS;



// �S�Ẵ��f���ŕK�v�ɂȂ����
// STATUS status�\����
typedef struct
{
	bool				roton;			// ����]���Ă��邩
	D3DXVECTOR3			pos;
	D3DXVECTOR3			oldpos;
	D3DXVECTOR3			move;
	D3DXVECTOR3		puremove;		// ����������O�̏����Ȉړ���
	D3DXVECTOR3			scl;
	D3DXVECTOR3			rot;
	D3DXVECTOR3			rotDest;
	D3DXMATRIX			World;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3		oldrotDest;		// 1�O�̖ړI�̌���
	float				hp;
	float				sabunRotY;
	LPD3DXBUFFER		BuffMatModel;	// LPD3DXBUFFER,�}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^D3DXMATERIAL�\���̂̔z�񂪊i�[
	DWORD				NumMatModel;			// DWORD,D3DXMATERIAL�\���̂ւ̃|�C���^
	LPD3DXMESH			MeshModel;		// LPD3DXMESH,���[�h���ꂽ���b�V����\��ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	LPDIRECT3DTEXTURE9	TextureModel;			// �e�N�X�`���ǂݍ��ݏꏊ

	// �e��\������ꍇ
	int					IdxShadow;				// �eID
	int					modelmovetype;				// ���f���̓��샂�[�h
	float				SizeShadow;				// �e�̃T�C�Y
	D3DXCOLOR			colShadow;				// �e�̐F

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

}STATUS;


typedef struct
{
	float	enemycenter;			// �G�̔��a
	float	map_zmax;				// ���_����e�}�b�v�̕ǂւ̋���
	float	map_zlow;
	float	map_xmax;
	float	map_xlow;
}ENEMYLENGTH;


// xinput�p�L�[���
typedef struct
{
	// �Q�[���p�b�h�̏��
	XINPUT_STATE	state;
	bool			use;

}GAMEPADX;

typedef enum
{
	firstwave
}WAVE;


//*****************************************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************************************

GAMEPADX *GetPADX(int no);			// xinput�̓���
ENEMYLENGTH *GetEnemylength(int no);


#endif