//=============================================================================
//
// モデル処理 [unit.h]
// Author : GP11B243 33 山本 壮将
//
//=============================================================================

//****************************************************************************
// 使いまわしようメモ
// MODEL
// Model
// model
//
//
//*****************************************************************************


#ifndef _UNIT_H_
#define _UNIT_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// 構造体定義
//*****************************************************************************

// モデル構造体
typedef struct
{
	bool				use = false;			// true 使用　false 未使用
	D3DXVECTOR3			pos;			// モデルの現在位置
	D3DXVECTOR3			rot;			// モデルの向き(回転)
	D3DXVECTOR3			scl;			// モデルの大きさ(スケール)
	D3DXMATRIX			World;			// ワールドマトリックス
	D3DXVECTOR3			oldpos;			// 移動する前の座標
	D3DXVECTOR3			move;			// 移動量
	D3DXVECTOR3			rotDest;		// 目的の向き
	int					ShadowID;				// 影ID
	float				ShadowSize;				// 影のサイズ
	D3DXCOLOR			Shadowcol;				// 影の色
	D3DXVECTOR3			Billboardkidsrot;					// ビルボードの角度
	float				kaiten;									// test 回転
	float				baselen;				// 自機との距離
	LPDIRECT3DTEXTURE9	Texture3D;			// テクスチャ読み込み場所
	LPD3DXMESH			Mesh;			// ID3DXMeshインターフェイスへのポインタ
	LPD3DXBUFFER		BuffMat;		// メッシュのマテリアル情報を格納
} UNIT;



// 子機の隊長名
typedef enum
{
	ICHI = 0,
	NI,
	SAN,
	SHI,

	BUTAI_MAX

} KOKI;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitUnit(void);
void UninitUnit(void);
void UpdateUnit(void);
void DrawUnit(void);
int SetUnit(void);
UNIT *GetUnit(int no);

#endif
