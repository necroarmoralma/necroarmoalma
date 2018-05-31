//=============================================================================
//
// バレット処理 [bullet.h]
// Author : GP11B243 33 山本 壮将
// ビルボードのヘッダーがもと
//=============================================================================
#ifndef _HIT_H_
#define _HIT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BULLET_MAX	(300)
#define	VALUE_MOVE_MODEL	(0.80f)						// 移動速度
#define	RATE_MOVE_MODEL		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_MODEL	(0.20f)						// 回転慣性係数
#define	HIT_WIDTH		(20.0f)							// 弾の半径幅
#define	HIT_HEIGHT	(20.0f)							// 弾の半径幅
#define HITON		(0.5*60.0f)					// 再生時間
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct {		// バレット構造体



	D3DXMATRIX				mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3				pos;							// 位置
	D3DXVECTOR3				scl;							// スケール
	D3DXVECTOR3				move;							// 移動量
	D3DXVECTOR3				rot;							// 回転
	D3DXVECTOR3				rotTarget;						// ターゲットへの向き
	float					wide;							// 幅
	float					height;							// 高さ
	int						g_nIdxShadow;					// 影ID
	bool					gravity;						// 重力を有効にするかどうか
	bool					use;							// 使用しているかどうか
	bool					moveon;							// 移動量は確定しているか?
	float					size_X;
	float					life;
} HIT;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitHit(void);
void UninitHit(void);
void UpdateHit(void);
void DrawHit(void);
int SetHit(D3DXVECTOR3 pos, float fx, float fy, D3DXCOLOR col);
HIT *GetHit(int no);

#endif
