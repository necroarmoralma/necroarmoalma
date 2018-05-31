//=============================================================================
//
// バレット処理 [bullet.h]
// Author : GP11B243 33 山本 壮将
// ビルボードのヘッダーがもと
//=============================================================================
#ifndef _STEAM_H_
#define _STEAM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	STEAM_MAX				(300)
#define	STEAM_WIDTH				(20.0f)							// 弾の半径幅
#define	STEAM_HEIGHT			(20.0f)							// 弾の半径幅
#define	STEAMSPEED				(0.8f)
#define	STEAM_RELEASECOUNT		(1.0 * 60)						// 秒数×FPS

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
	float					count;							// 消滅までの時間
} STEAM;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSteam(void);
void UninitSteam(void);
void UpdateSteam(void);
void DrawSteam(void);
int SetSteam(D3DXVECTOR3 pos,float fx, float fy, D3DXCOLOR col);
STEAM *GetSteam(int no);

#endif
