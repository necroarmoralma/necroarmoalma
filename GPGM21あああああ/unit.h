//=============================================================================
//
// ���f������ [unit.h]
// Author : GP11B243 33 �R�{ �s��
//
//=============================================================================

//****************************************************************************
// �g���܂킵�悤����
// MODEL
// Model
// model
//
//
//*****************************************************************************


#ifndef _UNIT_H_
#define _UNIT_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �\���̒�`
//*****************************************************************************

// ���f���\����
typedef struct
{
	bool				use = false;			// true �g�p�@false ���g�p
	D3DXVECTOR3			pos;			// ���f���̌��݈ʒu
	D3DXVECTOR3			rot;			// ���f���̌���(��])
	D3DXVECTOR3			scl;			// ���f���̑傫��(�X�P�[��)
	D3DXMATRIX			World;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3			oldpos;			// �ړ�����O�̍��W
	D3DXVECTOR3			move;			// �ړ���
	D3DXVECTOR3			rotDest;		// �ړI�̌���
	int					ShadowID;				// �eID
	float				ShadowSize;				// �e�̃T�C�Y
	D3DXCOLOR			Shadowcol;				// �e�̐F
	D3DXVECTOR3			Billboardkidsrot;					// �r���{�[�h�̊p�x
	float				kaiten;									// test ��]
	float				baselen;				// ���@�Ƃ̋���
	LPDIRECT3DTEXTURE9	Texture3D;			// �e�N�X�`���ǂݍ��ݏꏊ
	LPD3DXMESH			Mesh;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXBUFFER		BuffMat;		// ���b�V���̃}�e���A�������i�[
} UNIT;



// �q�@�̑�����
typedef enum
{
	ICHI = 0,
	NI,
	SAN,
	SHI,

	BUTAI_MAX

} KOKI;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUnit(void);
void UninitUnit(void);
void UpdateUnit(void);
void DrawUnit(void);
int SetUnit(void);
UNIT *GetUnit(int no);

#endif
