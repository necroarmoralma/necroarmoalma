//=============================================================================
//
// モデル処理 [enemy.h]
// Author : GP11B243 33 山本 壮将
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "setting.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMYMAX			(15)					// エネミーの最大数



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
#define ENEMYACTTIME		(0.8f)					// 1.0で1秒に1度
#define ENEMYACT			(ENEMYACTTIME*60)		// 60FPSなので60倍

// 次のモードへの移行を開始するまでの時間

#define ENEMYLIFE		(450)	// てきのHP
#define ENEMYKAITENSPEED	(D3DX_PI * 0.0002f)
#define ENEMYKAITENHANKEI	(450.0f)
//*****************************************************************************
// 構造体定義
//*****************************************************************************

// モデル構造体
typedef struct
{
	bool			use;			// true 使用　false 未使用
	bool			live;			// 生存中か
	D3DXVECTOR3		oldpos;			// 移動する前の座標
	float			acttime;		// 動作感覚
	float			enemy_maxlife;	// ボスの体力の最大値
	float			enemy_life;		// ボスの現在の体力
	float			kaiten;			// 回転移動に必要なもの
	float			rockon;			// 自機に向かう方向
	float			movesetting;	// 制御用現在の回転値
	float			center;			// 中心点までの距離
	int				movemode;		// 動作制御
	bool			enemymoveok;		// 移動してもよいかどうか
	bool			moveon;			// 移動中
	STATUS			status;
	
	//	歪用
	bool			warning;		// 警戒中かどうか
	bool			muki;			// 今向いている向きだよ
									//float
} ENEMY;

typedef enum
{	//行動パターン

	SHOT
} ENEMYMODE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void DeleatEnemy(int no);
void CreateEnemy(D3DXVECTOR3 pos);

D3DXVECTOR3 GetPositionEnemy(int no);
D3DXVECTOR3 GetRotationEnemy(int no);
D3DXVECTOR3 GetRotationDestEnemy(int no);
ENEMY *GetEnemy(int no);
void SetShikenkan(void);

#endif
