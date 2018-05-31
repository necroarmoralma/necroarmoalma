//=============================================================================
//
// バレット処理 [bullet.h]
// Author : GP11B243 33 山本 壮将
// ビルボードのヘッダーがもと
//=============================================================================
#ifndef _BULLETMK2_H_
#define _BULLETMK2_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BULLET_MAX	(3300)
//#define	VALUE_MOVE_MODEL	(0.80f)						// 移動速度
#define	RATE_MOVE_MODEL		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_MODEL	(0.20f)						// 回転慣性係数
#define	BULLETMK2_WIDTH		(20.0f)						// 弾の半径幅
#define	BULLETMK2_HEIGHT	(20.0f)						// 弾の半径幅
#define BULLETMK2LIMIT				(11000)				// 仮　弾が移動する領域


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
	float					hoseix;
	float					hoseiz;
	float					life;							//			生存時間
} BULLETMK2;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBulletmk2(void);
void UninitBulletmk2(void);
void UpdateBulletmk2(void);
void DrawBulletmk2(void);
int SetBulletmk2(D3DXVECTOR3 pos,float fx, float fy,float SIDE,float UP, D3DXCOLOR col);
BULLETMK2 *GetBulletmk2(int no);


#endif
