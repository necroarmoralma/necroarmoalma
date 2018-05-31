//=============================================================================
//
// モデル処理 [skydoom.h]
// Author : GP11B243 33 山本 壮将
//
//=============================================================================
#ifndef _SKYDOOM_H_
#define _SKYDOOM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	SKYDOOM_MAX			(1)	// もでるのかず

// 方向rotDest.yの値
#define ue				(3.14f)
#define migiue			(-2.36f)
#define migi			(-1.57f)
#define migishita		(-0.79f)
#define shita			(0.00f)
#define hidarishita	(0.79f)
#define hidari			(1.57f)
#define hidariue		(2.36f)
#define SKYDOOMACTTIME		(0.5f)					// 1.0で1秒に1度
#define SKYDOOMACT			(SKYDOOMACTTIME*60)		// 60FPSなので60倍
#define SKYDOOMLIFE		(1000)	// ボス(サメディウス16世)のHP
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
	float			skydoom_maxlife;	// ボスの体力の最大値
	float			skydoom_life;		// ボスの現在の体力

									// ここからはテスト
	LPD3DXMESH		MeshSkydoom;		// ID3DXMeshインターフェイスへのポインタ
	LPD3DXBUFFER	BuffMatSkydoom;		//メッシュのマテリアル情報を格納/
	DWORD			NumMatSkydoom;		// 属性情報の総数
} SKYDOOM;

//typedef enum
//{	//行動パターン
//
//	// 攻撃動作
//	ssshot = 0,
//} SKYDOOMMODE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSkydoom(void);
void UninitSkydoom(void);
void UpdateSkydoom(void);
void DrawSkydoom(void);

D3DXVECTOR3 GetPositionSkydoom(void);
D3DXVECTOR3 GetRotationSkydoom(void);
D3DXVECTOR3 GetRotationDestSkydoom(void);
SKYDOOM *GetSkydoom(int no);

#endif
