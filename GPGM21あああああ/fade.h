//=============================================================================
//
// フェード処理 [fade.h]
//  Author : HALゲーム学科二年生課程1年　山本壮将
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

//*************************************
// フェードの状態
//*************************************
typedef enum
{
	FADE_NONE = 0,		// 何もない状態
	FADE_IN,			// フェードイン処理
	FADE_OUT,			// フェードアウト処理
	FADE_MAX
} FADE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(FADE fade);
FADE GetFade(void);

#endif
