//=============================================================================
//
// スコア処理 [score.h]
// Author : GP11B243 34 吉田太智
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
int GetScore(void);
void ChangeScore(int value);

#endif
