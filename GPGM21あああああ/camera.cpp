//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : GP11B243 33 山本 壮将
//
//=============================================================================
#include "camera.h"
#include "model.h"
#include "input.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// 視野角
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z			(50.0f)					// ビュー平面のNearZ値(少なくするほど手前のやつうつる)
#define	VIEW_FAR_Z			(2100.0f)				// ビュー平面のFarZ値(この値を上げるほど遠くまで移せる)
#define	VALUE_MOVE_CAMERA	(2.0f)					// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// カメラの回転量

#define	INTERVAL_CAMERA_R	(20.5f)					// モデルの視線の先までの距離
#define	RATE_CHASE_CAMERA_P	(0.35f)					// カメラの視点への補正係数
#define	RATE_CHASE_CAMERA_R	(0.20f)					// カメラの注視点への補正係数

#define	CHASE_HEIGHT_P		(150.0f)				// 追跡時の視点の高さ
#define	CHASE_HEIGHT_R		(10.0f)					// 追跡時の注視点の高さ
// カメラの位置を調整
#define setCy				(70.0f)
#define setCz				(20.0f)

#define UEMIOROSHI			(400.0f)	// 上から見下ろした視点
#define KATAMUKI			(270.0f)

// カメラ距離を変える場合ここいじる
#define setting				(50.0f)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3		g_posCameraEye;				// カメラの視点
D3DXVECTOR3		g_posCameraAt;				// カメラの注視点
D3DXVECTOR3		g_posCameraUp;				// カメラの上方向
D3DXVECTOR3		g_posCameraEyeDest;			// カメラの視点の目的位置
D3DXVECTOR3		g_posCameraAtDest;			// カメラの注視点の目的位置
D3DXVECTOR3		g_rotCamera;				// カメラの回転
float			g_fLengthIntervalCamera;	// カメラの視点と注視点の距離
D3DXMATRIX		g_mtxView;					// ビューマトリックス
D3DXMATRIX		g_mtxProjection;			// プロジェクションマトリックス


float			zzoom;						// モデルとカメラのZ軸方向の距離
float			yzoom;						// モデルとカメラのY軸方向の距離
float			len;						// 視点と注視点の距離
//=============================================================================
// カメラの初期化
//=============================================================================
HRESULT InitCamera(void)
{
	g_posCameraEye = D3DXVECTOR3(0.0f, 200.0f, -200.0f);
	g_posCameraAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_posCameraEyeDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_posCameraAtDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx, vz;
	vx = g_posCameraEye.x - g_posCameraAt.x;
	vz = g_posCameraEye.z - g_posCameraAt.z;
	g_fLengthIntervalCamera = sqrtf(vx * vx + vz * vz);
	// ズーム距離の初期化
	zzoom = ZJIKU;
	yzoom = YJIKU;

	yzoom += KATAMUKI;
	// 注視点と視点の距離を計算する
	D3DXVECTOR3 temp = g_posCameraAt - g_posCameraEye;

	len = g_fLengthIntervalCamera +50.0f;

	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	MODEL *model = GetModel(0);
	D3DXVECTOR3 temp = g_posCameraEye - g_posCameraAt;					// 視点と注視点の差分
	temp /= 300;														// それぞれの要素を割る


																		// カメラの注視点をプレイヤーの座標に
	g_posCameraAt.x = model->pos.x;
	g_posCameraAt.y = model->pos.y;
	g_posCameraAt.z = model->pos.z;


	////
	////// カメラの視点を注視点より少し手前＆少し上へ
	g_posCameraEye.x = g_posCameraAt.x -sin(g_rotCamera.y)*len;			//-sin(回転角度)*カメラの距離
	g_posCameraEye.y = g_posCameraAt.y + 500.0f;// +yzoom + setCy;// +400.0f;// +yzoom + setCy;
	g_posCameraEye.z = g_posCameraAt.z - cos(g_rotCamera.y)*len;// -300.0f;



	if(GetKeyboardPress(DIK_Z))
	{
		zzoom += 10;
	}
	if(GetKeyboardPress(DIK_C))
	{
		zzoom -= 10;
	}

	if(GetKeyboardPress(DIK_V))
	{
		yzoom += 10;
	}

	if(GetKeyboardPress(DIK_N))
	{
		yzoom -= 10;
	}

	if(GetKeyboardPress(DIK_Y))
	{// 視点移動「上」
		g_posCameraEye.y += VALUE_MOVE_CAMERA;
	}
	if(GetKeyboardPress(DIK_N))
	{// 視点移動「下」
		g_posCameraEye.y -= VALUE_MOVE_CAMERA;
	}

	if(GetKeyboardPress(DIK_Q))
	{// 注視点旋回「左」
		g_rotCamera.y -= VALUE_ROTATE_CAMERA;
		if(g_rotCamera.y < -D3DX_PI)
		{
			g_rotCamera.y += D3DX_PI*2.0f;
		}

		g_posCameraAt.x = g_posCameraEye.x + sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraAt.z = g_posCameraEye.z + cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_E))
	{// 注視点旋回「右」
		g_rotCamera.y += VALUE_ROTATE_CAMERA;
		if(g_rotCamera.y > D3DX_PI)
		{
			g_rotCamera.y -= D3DX_PI*2.0f;
		}

		g_posCameraAt.x = g_posCameraEye.x + sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraAt.z = g_posCameraEye.z + cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}

	//g_rotCamera = model->rot;

	//if(GetKeyboardPress(DIK_T))
	//{// 注視点移動「上」
	//	g_posCameraAt.y += VALUE_MOVE_CAMERA;
	//}
	//if(GetKeyboardPress(DIK_B))
	//{// 注視点移動「下」
	//	g_posCameraAt.y -= VALUE_MOVE_CAMERA;
	//}

	//

	//PrintDebugProc("len = %f", len);
	//PrintDebugProc("カメラの距離Y	: (%f)]ln", yzoom); 
	//PrintDebugProc("[カメラの距離Z  : (%f)]|n", zzoom);
	//PrintDebugProc("[カメラの視点  ：(%f : %f : %f)]\n", g_posCameraEye.x, g_posCameraEye.y, g_posCameraEye.z);
	//PrintDebugProc("[カメラの注視点：(%f : %f : %f)]\n", g_posCameraAt.x, g_posCameraAt.y, g_posCameraAt.z);
	//PrintDebugProc("[カメラの向き  ：(%f)]\n", g_rotCamera.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("*** 視点操作 ***\n");
	//PrintDebugProc("前移動 : W\n");
	//PrintDebugProc("後移動 : S\n");
	//PrintDebugProc("左移動 : A\n");
	//PrintDebugProc("右移動 : D\n");
	//PrintDebugProc("上移動 : Y\n");
	//PrintDebugProc("下移動 : N\n");
	//PrintDebugProc("左旋回 : Z\n");
	//PrintDebugProc("右旋回 : C\n");
	//PrintDebugProc("\n");

	PrintDebugProc("*** 注視点操作 ***\n");
	PrintDebugProc("上移動 : T\n");
	PrintDebugProc("下移動 : B\n");
	PrintDebugProc("左旋回 : Q\n");
	PrintDebugProc("右旋回 : E\n");
	PrintDebugProc("\n");
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_mtxView,
		&g_posCameraEye,		// カメラの視点
		&g_posCameraAt,		// カメラの注視点
		&g_posCameraUp);		// カメラの上方向

								// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
		VIEW_ANGLE,			// 視野角
		VIEW_ASPECT,		// アスペクト比
		VIEW_NEAR_Z,		// ビュー平面のNearZ値
		VIEW_FAR_Z);		// ビュー平面のFarZ値

							// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);
}

//=============================================================================
// カメラの向きの取得
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

//=============================================================================
// ビューマトリックスの取得
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}

