//=============================================================================
//
// モデル処理 [boss.h]
// Author : GP11B243 33 山本 壮将
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BOSS_MAX			(1)	// もでるのかず

// 方向rotDest.yの値
#define ue				(3.14f)
#define migiue			(-2.36f)
#define migi			(-1.57f)
#define migishita		(-0.79f)
#define shita			(0.00f)
#define hidarishita	(0.79f)
#define hidari			(1.57f)
#define hidariue		(2.36f)

// 攻撃等行動時間
#define BOSSACTTIME		(0.8f)					// 1.0で1秒に1度
#define BOSSACT			(BOSSACTTIME*60)		// 60FPSなので60倍

// 次のモードへの移行を開始するまでの時間

#define BOSSLIFE		(4500)	// ボス()のHP
#define BOSSKAITENSPEED	(D3DX_PI * 0.0002f)
#define BOSSKAITENHANKEI	(450.0f)
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
	float			boss_maxlife;	// ボスの体力の最大値
	float			boss_life;		// ボスの現在の体力
	float			kaiten;			// 回転移動に必要なもの
	float			rockon;			// 自機に向かう方向
	float			movesetting;	// 制御用現在の回転値
	int				movemode;		// 動作制御
	bool			bossmoveok;		// 移動してもよいかどうか
	bool			moveon;			// 移動中？


	//float
} BOSS;

typedef enum
{	//行動パターン

	DEBIRU,
	AHIRU,
	HENANO,
	MEKA,
	BOSSMOVEMAX,
	// 攻撃動作
	shot = 0,
} BOSSMODE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);

D3DXVECTOR3 GetPositionBoss(void);
D3DXVECTOR3 GetRotationBoss(void);
D3DXVECTOR3 GetRotationDestBoss(void);
BOSS *GetBoss(int no);

#endif
