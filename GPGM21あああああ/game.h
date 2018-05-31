//=============================================================================
//
// ゲーム画面処理 [game.h]
//  Author : HALゲーム学科二年生課程1年　山本壮将
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
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
