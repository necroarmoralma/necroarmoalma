//=============================================================================
//
// モデル処理 [lockcircle.h]
// Author : GP11B243 33 山本 壮将
//
//=============================================================================
#ifndef _LOCKCIRCLE_H_
#define _LOCKCIRCLE_H_

#include "main.h"
#include "setting.h"
#include "xinput.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LOCK_LIMITMOVE_X			(SCREEN_CENTER_X)		// かりおき
#define LOCK_LIMITMOVE_Y			(SCREEN_CENTER_Y)		// かりおき

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	STATUS status;
}LOCKCIRCLE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitLockcircle(void);
void UninitLockcircle(void);
void UpdateLockcircle(int movetypeno);
void DrawLockcircle(void);


#endif
