//=============================================================================
//
// e [shadow.h]
//  Author : HALQ[wΘρNΆΫφ1N@R{s«
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//*****************************************************************************
// vg^CvιΎ
//*****************************************************************************
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int CreateShadow(D3DXVECTOR3 pos, float fSizeX, float fSizeZ);
void ReleaseShadow(int nIdxShadow);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void SetVertexShadow(int nIdxShadow, float fSizeX, float fSizeZ);
void SetColorShadow(int nIdxShadow, D3DXCOLOR col);

#endif
