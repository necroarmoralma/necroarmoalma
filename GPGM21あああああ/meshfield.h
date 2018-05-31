//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.h]
//  Author : HAL�Q�[���w�ȓ�N���ے�1�N�@�R�{�s��//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAPLIMIT_X	(SCREEN_WIDTH)//(SCREEN_WIDTH/2)			//�悱
#define MAPLIMIT_Z	(SCREEN_HEIGHT)//(SCREEN_HEIGHT/2)			// ����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
							int nNumBlockX, int nNumBlockZ, float nBlockSizeX, float nBlockSizeZ);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif
