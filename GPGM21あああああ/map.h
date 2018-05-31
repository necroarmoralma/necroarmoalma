//=============================================================================
//
// モデル処理 [map.h]
// Author : GP11B243 33 山本 壮将
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAP_MAX			(1)	// もでるのかず

// 方向rotDest.yの値
#define ue				(3.14f)
#define migiue			(-2.36f)
#define migi			(-1.57f)
#define migishita		(-0.79f)
#define shita			(0.00f)
#define hidarishita	(0.79f)
#define hidari			(1.57f)
#define hidariue		(2.36f)
#define MAPACTTIME		(0.5f)					// 1.0で1秒に1度
#define MAPACT			(MAPACTTIME*60)		// 60FPSなので60倍
#define MAPLIFE		(1000)	// ボス(サメディウス16世)のHP
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
	float			acttime;		// 動作感覚
	float			map_maxlife;	// ボスの体力の最大値
	float			map_life;		// ボスの現在の体力

	// ここからはテスト
	LPD3DXMESH		MeshMap;		// ID3DXMeshインターフェイスへのポインタ
	LPD3DXBUFFER	BuffMatMap;		//メッシュのマテリアル情報を格納/
	DWORD			NumMatMap;		// 属性情報の総数
} MAP;

//typedef enum
//{	//行動パターン
//
//	// 攻撃動作
//	ssshot = 0,
//} MAPMODE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);

D3DXVECTOR3 GetPositionMap(void);
D3DXVECTOR3 GetRotationMap(void);
D3DXVECTOR3 GetRotationDestMap(void);
MAP *GetMap(int no);

#endif
