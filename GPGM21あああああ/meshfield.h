//=============================================================================
//
// メッシュ地面の処理 [meshfield.h]
//  Author : HALゲーム学科二年生課程1年　山本壮将//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAPLIMIT_X	(SCREEN_WIDTH)//(SCREEN_WIDTH/2)			//よこ
#define MAPLIMIT_Z	(SCREEN_HEIGHT)//(SCREEN_HEIGHT/2)			// おく

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
							int nNumBlockX, int nNumBlockZ, float nBlockSizeX, float nBlockSizeZ);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif
