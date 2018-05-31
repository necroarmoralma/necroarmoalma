//=============================================================================
//
// モデル処理 [modelarm.cpp]
// Author : GP11B243 33 山本 壮将
// モデルの腕
//=============================================================================
#include "model.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "bulletmk2.h"
#include "meshfield.h"
#include "setting.h"
#include "camera.h"
#include "modelarm.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODELARM_MODEL		"data/MODEL/arrowarm.blend.x"	// 読み込むモデル名


// プレイヤーのパーツ数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureModelArm;			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshModelArm;			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatModelArm;		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatModelArm;				// 属性情報の総数


MODELARM			modelarmWk[1];					// モデル構造体(モデルは１）
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitModelArm(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELARM *modelarm = &modelarmWk[0];
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);

	// HPの設定(部位破壊を導入するならコメントアウト解除
	//modelarm->Maxlife = PLAYER_HP_MAX;
	//modelarm->Nowlife = modelarm->Maxlife;


	g_pD3DTextureModelArm = NULL;
	g_pD3DXMeshModelArm = NULL;
	g_pD3DXBuffMatModelArm = NULL;

	modelarm->pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	modelarm->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelarm->puremove = modelarm->move;
	modelarm->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelarm->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelarm->scl = model->scl;

	modelarm->rot.y = 90.0f;

	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(MODELARM_MODEL,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pD3DXBuffMatModelArm,
		NULL,
		&g_nNumMatModelArm,
		&g_pD3DXMeshModelArm)))
	{
		return E_FAIL;
	}

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&g_pD3DTextureModelArm);	// 読み込むメモリー
#endif

	// 影の生成(現段階ではこいつの影は出さない)
	//modelarm->g_nIdxShadow = CreateShadow(modelarm->pos, 25.0f, 25.0f);
	//modelarm->g_fSizeShadow = 25.0f;
	//modelarm->g_colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModelArm(void)
{
	if (g_pD3DTextureModelArm != NULL)
	{// テクスチャの開放
		g_pD3DTextureModelArm->Release();
		g_pD3DTextureModelArm = NULL;
	}

	if (g_pD3DXMeshModelArm != NULL)
	{// メッシュの開放
		g_pD3DXMeshModelArm->Release();
		g_pD3DXMeshModelArm = NULL;
	}

	if (g_pD3DXBuffMatModelArm != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatModelArm->Release();
		g_pD3DXBuffMatModelArm = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModelArm(void)
{
	D3DXVECTOR3 rotCamera;
	MODELARM *modelarm = &modelarmWk[0];
	MODEL *model = GetModel(0);
	float fDiffRotY;
	//modelarm->rot.z += 0.1f;
	// カメラの向き取得
	rotCamera = GetRotCamera();
	// 常に前へ
	modelarm->rotDest.y = rotCamera.y + D3DX_PI;


	// テスト
	if (GetKeyboardPress(DIK_U))
	{
		modelarm->Nowlife -= 10.0f;
	}
	// 横井童子の回転を一時的に無効か
	// メモ　10で割ってるのは10フレームで移動させるため
	



	modelarm->pos = model->pos;
	modelarm->rot = model->rot;

	//// 目的の角度までの差分
	//fDiffRotY = modelarm->rotDest.y - modelarm->rot.y;
	//if (fDiffRotY > D3DX_PI)
	//{
	//	fDiffRotY -= D3DX_PI * 2.0f;
	//}
	//if (fDiffRotY < -D3DX_PI)
	//{
	//	fDiffRotY += D3DX_PI * 2.0f;
	//}

	//// 目的の角度まで慣性をかける
	//modelarm->rot.y += fDiffRotY * RATE_ROTATE_MODEL;
	//if (modelarm->rot.y > D3DX_PI)
	//{
	//	modelarm->rot.y -= D3DX_PI * 2.0f;

	//}
	//if (modelarm->rot.y < -D3DX_PI)
	//{
	//	modelarm->rot.y += D3DX_PI * 2.0f;
	//}

	//	modelarm->rot.y = 3.14f;

	/// 位置移動
	modelarm->pos.x += modelarm->move.x;
	modelarm->pos.y += modelarm->move.y;
	if (modelarm->pos.y < 5.0f)
	{
		modelarm->pos.y = 5.0f;
	}
	if (modelarm->pos.y > 75.0f)
	{
		modelarm->pos.y = 75.0f;
	}
	modelarm->pos.z += modelarm->move.z;

	// 慣性かける前に移動量を保存
	modelarm->puremove = modelarm->move;


	// 移動量に慣性をかける
	modelarm->move.x += (0.0f - modelarm->move.x) * RATE_MOVE_MODEL;
	modelarm->move.y += (0.0f - modelarm->move.y) * RATE_MOVE_MODEL;
	modelarm->move.z += (0.0f - modelarm->move.z) * RATE_MOVE_MODEL;


	// 領域外に行ったらストップ(÷2しているのはめり込まないようにするため)
	//if (modelarm->pos.x < -DROWMAX_X)
	//{
	//	modelarm->pos.x = -DROWMAX_X;
	//}
	//if (modelarm->pos.x >  DROWMAX_X)
	//{
	//	modelarm->pos.x = DROWMAX_X;
	//}
	//if (modelarm->pos.z  < -DROWMAX_Z)
	//{
	//	modelarm->pos.z = -DROWMAX_Z;
	//}
	//if (modelarm->pos.z > DROWMAX_Z)
	//{
	//	modelarm->pos.z = DROWMAX_Z;
	//}




	// 影の位置設定
	//SetPositionShadow(modelarm->g_nIdxShadow, D3DXVECTOR3(modelarm->pos.x, 0.1f, modelarm->pos.z));

	//SetVertexShadow(modelarm->g_nIdxShadow, g_fSizeShadow, g_fSizeShadow);
	//SetColorShadow(g_nIdxShadow, g_colShadow);

	PrintDebugProc("[rotDest.yいくつ:(%f) ]\n", modelarm->rotDest.y);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModelArm(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	MODELARM *modelarm = &modelarmWk[0];

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&modelarm->World);


	// スケールを反映
	D3DXMatrixScaling(&mtxScl, modelarm->scl.x, modelarm->scl.y, modelarm->scl.z);
	D3DXMatrixMultiply(&modelarm->World, &modelarm->World, &mtxScl);


	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, modelarm->rot.y, modelarm->rot.x, modelarm->rot.z);
	D3DXMatrixMultiply(&modelarm->World, &modelarm->World, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, modelarm->pos.x, modelarm->pos.y, modelarm->pos.z);
	D3DXMatrixMultiply(&modelarm->World, &modelarm->World, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &modelarm->World);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatModelArm->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModelArm; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureModelArm);

		// 描画
		g_pD3DXMeshModelArm->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionModelArm(void)
{
	MODELARM *modelarm = &modelarmWk[0];
	return modelarm->pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationModelArm(void)
{
	MODELARM *modelarm = &modelarmWk[0];
	return modelarm->rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestModelArm(void)
{
	MODELARM *modelarm = &modelarmWk[0];
	return modelarm->rotDest;
}

//*****************************************************************************
// ゲット関数
//*****************************************************************************
MODELARM *GetModelArm(int no)
{
	return(&modelarmWk[0]);
}