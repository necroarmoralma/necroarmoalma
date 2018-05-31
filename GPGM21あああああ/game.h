//=============================================================================
//
// �Q�[����ʏ��� [game.h]
//  Author : HAL�Q�[���w�ȓ�N���ے�1�N�@�R�{�s��
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void CheckHitBB_M(void);
bool CheckHitBC3D(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
void CheckHitBMk2_Boss(void);
void CheckHitBMk2_Bossarmr(void);

#endif
