//=============================================================================
//
// モデル処理 [wheel.h]
// Author : GP11B243 33 山本 壮将
//
//=============================================================================
#ifndef _WHEEL_H_
#define _WHEEL_H_

#include "main.h"
#include "setting.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 方向rotDest.yの値
//#define ue				(3.14f)
//#define migiue			(-2.36f)
//#define migi			(-1.57f)
//#define migishita		(-0.79f)
//#define shita			(0.00f)
//#define hidarishita	(0.79f)
//#define hidari			(1.57f)
//#define hidariue		(2.36f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitWheel(void);
void UninitWheel(void);
void UpdateWheel(int movetypeno);
void DrawWheel(void);

D3DXVECTOR3 GetPositionWheel(void);
D3DXVECTOR3 GetRotationWheel(void);
D3DXVECTOR3 GetRotationDestWheel(void);

#endif
