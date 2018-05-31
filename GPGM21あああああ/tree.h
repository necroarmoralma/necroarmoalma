//=============================================================================
//
// 木処理 [tree.h]
//  Author : HALゲーム学科二年生課程1年　山本壮将
//
//=============================================================================
#ifndef _TREE_H_
#define _TREE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TREE			(256)	// 木最大数
#define	TREE_WIDTH			(15.0f)							// 木の半径幅
#define	TREE_HEIGHT			(80.0f)							// 木の半径高さ
#define	VALUE_MOVE_TREE		(3.00f)							// 移動速度

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 scl;		// スケール
	float fWidth;			// 幅
	float fHeight;			// 高さ
	int nIdxShadow;			// 影ID
	bool bUse;				// 使用しているかどうか
} TREE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTree(void);
void UninitTree(void);
void UpdateTree(void);
void DrawTree(void);

int SetTree(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col);

TREE *GetTree(int no);

#endif
