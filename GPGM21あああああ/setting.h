//*****************************************************************************************************
// ファイル名:	setting.h
// 作成日:		12月16日
// 説明:		ゲーム内で使う物の読み込み設定
//*****************************************************************************************************

#ifndef _SETTING_H_
#define _SETTING_H_

//*****************************************************************************************************
// インクルードファイル
//******************************************************************************************************

#include "main.h"
#include "xinput.h"
//*****************************************************************************************************
// マクロ定義
//*****************************************************************************************************
#define DROWMAX_X		(360.0f)			//　x方向の描画範囲
#define DROWMAX_Z		(400.0f)			// Ｙ方向の描画範囲
#define PODREFRECT		(2.8)				// 壁に当たった時どれだけの大きさで跳ね返るのか
#define STICKBASE		(1000)				// スティック入力を受け付ける基準値(少なすぎると勝手に動いたり誤動作したり…)
#define TRIGGERBASE			(10)			// トリガーの入力を受け付ける基準値(0～255)
#define EVOLVEPOINT_BOSS	(10.0f)			// ボス撃破で貰える進化ポイント

#define SHOTKANKAKU		(0.5*60*0.5)		// 通常ショットの感覚
//*****************************************************************************************************
// 構造体定義
//*****************************************************************************************************


typedef enum
{
	RAY_FRONT,
	RAY_RIGHT,
	RAY_LEFT,
	RAY_BACK,
	RAY_UP,
	RAY_DOWN,
	RAY_MAX
} RAYS;



// 全てのモデルで必要になるもの
// STATUS status構造体
typedef struct
{
	bool				roton;			// 今回転しているか
	D3DXVECTOR3			pos;
	D3DXVECTOR3			oldpos;
	D3DXVECTOR3			move;
	D3DXVECTOR3		puremove;		// 慣性かかる前の純粋な移動量
	D3DXVECTOR3			scl;
	D3DXVECTOR3			rot;
	D3DXVECTOR3			rotDest;
	D3DXMATRIX			World;			// ワールドマトリックス
	D3DXVECTOR3		oldrotDest;		// 1つ前の目的の向き
	float				hp;
	float				sabunRotY;
	LPD3DXBUFFER		BuffMatModel;	// LPD3DXBUFFER,マテリアルデータを含むバッファへのポインタD3DXMATERIAL構造体の配列が格納
	DWORD				NumMatModel;			// DWORD,D3DXMATERIAL構造体へのポインタ
	LPD3DXMESH			MeshModel;		// LPD3DXMESH,ロードされたメッシュを表すID3DXMeshインターフェイスへのポインタのアドレス
	LPDIRECT3DTEXTURE9	TextureModel;			// テクスチャ読み込み場所

	// 影を表示する場合
	int					IdxShadow;				// 影ID
	int					modelmovetype;				// モデルの動作モード
	float				SizeShadow;				// 影のサイズ
	D3DXCOLOR			colShadow;				// 影の色

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

}STATUS;


typedef struct
{
	float	enemycenter;			// 敵の半径
	float	map_zmax;				// 原点から各マップの壁への距離
	float	map_zlow;
	float	map_xmax;
	float	map_xlow;
}ENEMYLENGTH;


// xinput用キー情報
typedef struct
{
	// ゲームパッドの状態
	XINPUT_STATE	state;
	bool			use;

}GAMEPADX;

typedef enum
{
	firstwave
}WAVE;


//*****************************************************************************************************
// プロトタイプ宣言
//*****************************************************************************************************

GAMEPADX *GetPADX(int no);			// xinputの入力
ENEMYLENGTH *GetEnemylength(int no);


#endif