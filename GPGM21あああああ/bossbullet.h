//=============================================================================
//
// バレット処理 [bullet.h]
// Author : GP11B243 33 山本 壮将
// ビルボードのヘッダーがもと
//=============================================================================
#ifndef _BOSSBULLET_H_
#define _BOSSBULLET_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BOSSBULLET_MAX	(2300)
#define	RATE_MOVE_MODEL		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_MODEL	(0.20f)						// 回転慣性係数
#define	BOSSBULLET_WIDTH		(30.0f)							// 弾の半径幅
#define	BOSSBULLET_HEIGHT	(30.0f)							// 弾の半径幅
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct {		// バレット構造体


	int						count;							// バレットの生存時間
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
	float					bossbullet_rot;					// 回転角
	float					live;							// ボスの弾が存在できる時間
} BOSSBULLET;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBossbullet(void);
void UninitBossbullet(void);
void UpdateBossbullet(void);
void DrawBossbullet(void);
int SetBossbullet(D3DXVECTOR3 pos, float fx, float fy, D3DXCOLOR col,float bossbulletrot);
int SetEnemybullet(D3DXVECTOR3 pos, float fx, float fy, D3DXCOLOR col, float enemytargetrot);
BOSSBULLET *GetBossbullet(int no);

#endif
