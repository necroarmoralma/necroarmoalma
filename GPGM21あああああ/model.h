	//=============================================================================
//
// モデル処理 [model.h]
// Author : GP11B243 33 山本 壮将
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "setting.h"
#include "xinput.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_MAX			(1)	// もでるのかず

// 方向rotDest.yの値
#define ue				(3.14f)
#define migiue			(-2.36f)
#define migi			(-1.57f)
#define migishita		(-0.79f)
#define shita			(0.00f)
#define hidarishita	(0.79f)
#define hidari			(1.57f)
#define hidariue		(2.36f)
#define rolluptime		(1.0f)
#define ROLLLIMIT		(rolluptime * 60)		// 60FPSだからね
#define rollcooltime	(3.0f)					// 1.0で1秒
#define COOLTIME		(rolluptime * 60)		// 60FPSだからね
// 最大HP
#define PLAYER_HP_MAX	(1000.0f)

#define	PITCH_MODEL		"data/MODEL/player.x"

#define	VALUE_MOVE_MODEL	(0.80f)						// 移動速度
#define	RATE_MOVE_MODEL		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_MODEL	(0.20f)						// 回転慣性係数
#define	BULLET_SIZEX		(20.0f)						// 弾の大きさ基準値X
#define BULLET_SIZEY		(20.0f)						// 弾の大きさ基準値Y
#define MODEL_MOVEROLL		(0.2f)						// 移動時の回転角
#define MODEL_MOVEROLlX		(0.2f)						// 移動時の回転(前後)
#define MODEL_DISTANCE_CL	(8.0f)						// モデルの中心から足元までの距離
#define MODEL_BAUNCE		(1.5f)						// 反転移動量



#define NOCONTROL			(0.2 * 60)	// 60fps
//*****************************************************************************
// 構造体定義
//*****************************************************************************

// モデル構造体
typedef struct
{

	// モデルの長さ
	float center;			// 中心点までの距離
	float higher;			// 高さ

	bool			use;			// true 使用　false 未使用
	D3DXVECTOR3		pos;			// モデルの現在位置
	D3DXVECTOR3		oldpos;			// モデルの1フレーム前の座標を保存
	D3DXVECTOR3		rot;			// モデルの向き(回転)
	D3DXVECTOR3		scl;			// モデルの大きさ(スケール)
	D3DXMATRIX		World;			// ワールドマトリックス
	D3DXVECTOR3		move;			// 移動量
	D3DXVECTOR3		puremove;		// 慣性かかる前の純粋な移動量
	D3DXVECTOR3		rotDest;		// 目的の向き
	D3DXVECTOR3		oldrotDest;		// 1つ前の目的の向き


	float			Maxlife;			// たいりょく
	float			Nowlife;		// 今の体力
	bool			rollon;			// かいひしてる?
	float			cooltime;		// クールタイム
	bool			control;		// キーボード入力可能かどうか
	bool			escapemode;		// 壁にめり込まないようにしているかどうか(基準はfalse)

	// マップとの各方向の当たり判定
	BOOL			tomapDown;			// マップとの当たり判定(下方向)
	BOOL			tomapUp;			// マップとの当たり判定(上方向)
	BOOL			tomapFront;			// マップとの当たり判定(前方向)
	BOOL			tomapBack;			// マップとの当たり判定(後ろ方向)
	BOOL			tomapRight;			// マップとの当たり判定(右方向)
	BOOL			tomapLeft;			// マップとの当たり判定(左方向)
	// レイとマップの距離
	float			R_RtoMdistance;	// 右
	float			L_RtoMdistance;	// 左
	float			U_RtoMdistance;	// 上
	float			D_RtoMdistance;	// 下
	float			F_RtoMdistance;	// 前方
	float			B_RtoMdistance;	// 後方
	// タイヤ
	STATUS			status;
	STATUS			taiya_status;
	// 球
	float			shot;					// 球の発射間隔
	float			nowshot_evolve;			// 今のポイント
	float			shot_evolve;			// レベルアップに必要な数値
	int				shotlv;
	bool			shot_on;				// 弾が打てるかどうかの判定
	// ブースト
	float			boostgage;
	// ゲーム本編でのモデル
	DWORD				NumMatModelgame;			// DWORD,D3DXMATERIAL構造体へのポインタ
	LPD3DXMESH			MeshModelgame;		// LPD3DXMESH,ロードされたメッシュを表すID3DXMeshインターフェイスへのポインタのアドレス
	LPDIRECT3DTEXTURE9	TextureModelgame;			// テクスチャ読み込み場所

} MODEL;



 // モデルのxファイル関連の構造体
typedef struct
{
	LPD3DXBUFFER	g_pD3DXBuffMatModel;	// LPD3DXBUFFER,マテリアルデータを含むバッファへのポインタD3DXMATERIAL構造体の配列が格納
	DWORD			g_nNumMatModel;			// DWORD,D3DXMATERIAL構造体へのポインタ
	LPD3DXMESH		g_pD3DXMeshModel;		// LPD3DXMESH,ロードされたメッシュを表すID3DXMeshインターフェイスへのポインタのアドレス
} MODEL_XFILE;

// モデルの動作
typedef enum
{
	model_game,
	model_title,
	MODELMOVETYPEMAX
} MODELMOVETYPE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitModel(int gametypeno);
void UninitModel(void);
void UpdateModel(int movetypeno);
void DrawModel(int gametypeno);

D3DXVECTOR3 GetPositionModel(void);
D3DXVECTOR3 GetRotationModel(void);
D3DXVECTOR3 GetRotationDestModel(void);
void model_RaypickTomap(void);
MODEL *GetModel(int no);

#endif
