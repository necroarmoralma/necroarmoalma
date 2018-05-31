//=============================================================================
//
// モデル処理 [modelarm.h]
// Author : GP11B243 33 山本 壮将
//
//=============================================================================
#ifndef _MODELARM_H_
#define _MODELARM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODELARM_MAX	(1)	// もでるのかず
//*****************************************************************************
// 構造体定義
//*****************************************************************************

// モデル構造体
typedef struct
{
	bool			use;			// true 使用　false 未使用
	D3DXVECTOR3		pos;			// モデルの現在位置
	D3DXVECTOR3		rot;			// モデルの向き(回転)
	D3DXVECTOR3		scl;			// モデルの大きさ(スケール)
	D3DXMATRIX		World;			// ワールドマトリックス
	D3DXVECTOR3		oldpos;			// 移動する前の座標
	D3DXVECTOR3		move;			// 移動量
	D3DXVECTOR3		puremove;		// 慣性かかる前の純粋な移動量
	D3DXVECTOR3		rotDest;		// 目的の向き
	D3DXVECTOR3		oldrotDest;		// 1つ前の目的の向き
	float			Maxlife;			// たいりょく
	float			Nowlife;		// 今の体力
	float			rollup;			// 緊急避難
	bool			rolluse;		// 緊急避難使った？
	bool			rollon;			// かいひなう？
	float			cooltime;		// クールタイム
	int				g_nIdxShadow;				// 影ID
	float			g_fSizeShadow;				// 影のサイズ
	D3DXCOLOR		g_colShadow;				// 影の色
	bool			roton;						// 今物体は回転
} MODELARM;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitModelArm(void);
void UninitModelArm(void);
void UpdateModelArm(void);
void DrawModelArm(void);

D3DXVECTOR3 GetPositionModelArm(void);
D3DXVECTOR3 GetRotationModelArm(void);
D3DXVECTOR3 GetRotationDestModelArm(void);
MODELARM *GetModelArm(int no);

#endif
