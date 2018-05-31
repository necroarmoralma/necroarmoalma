//=============================================================================
//
// モデル処理 [modelbooster.cpp]
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
#include "modelbooster.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODELBOOSTER_MODEL		"data/MODEL/modelbooster.x"	// 読み込むモデル名
#define MODELBOOSTERANIMCOUNT	(1*60);						// 秒数×フレーム数

// プレイヤーのパーツ数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureModelBooster;			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshModelBooster;			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatModelBooster;		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatModelBooster;				// 属性情報の総数
bool				boosteranim;
float				boostercount;

MODELBOOSTER			modelboosterWk[1];					// モデル構造体(モデルは１）
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitModelBooster(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBOOSTER *modelbooster = &modelboosterWk[0];
	D3DXVECTOR3 rotCamera;

	// HPの設定(部位破壊を導入するならコメントアウト解除
	//modelbooster->Maxlife = PLAYER_HP_MAX;
	//modelbooster->Nowlife = modelbooster->Maxlife;


	g_pD3DTextureModelBooster = NULL;
	g_pD3DXMeshModelBooster = NULL;
	g_pD3DXBuffMatModelBooster = NULL;

	modelbooster->pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	modelbooster->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelbooster->puremove = modelbooster->move;
	modelbooster->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelbooster->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelbooster->scl = D3DXVECTOR3(0.3f, 0.3f, 0.3f);

	modelbooster->rot.y = 90.0f;

	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(MODELBOOSTER_MODEL,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pD3DXBuffMatModelBooster,
		NULL,
		&g_nNumMatModelBooster,
		&g_pD3DXMeshModelBooster)))
	{
		return E_FAIL;
	}

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&g_pD3DTextureModelBooster);	// 読み込むメモリー
#endif

									// 影の生成(現段階ではこいつの影は出さない)
									//modelbooster->g_nIdxShadow = CreateShadow(modelbooster->pos, 25.0f, 25.0f);
									//modelbooster->g_fSizeShadow = 25.0f;
									//modelbooster->g_colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);


	// 動作
	boosteranim = false;
	boostercount = 0.0f;


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModelBooster(void)
{
	if (g_pD3DTextureModelBooster != NULL)
	{// テクスチャの開放
		g_pD3DTextureModelBooster->Release();
		g_pD3DTextureModelBooster = NULL;
	}

	if (g_pD3DXMeshModelBooster != NULL)
	{// メッシュの開放
		g_pD3DXMeshModelBooster->Release();
		g_pD3DXMeshModelBooster = NULL;
	}

	if (g_pD3DXBuffMatModelBooster != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatModelBooster->Release();
		g_pD3DXBuffMatModelBooster = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModelBooster(void)
{
	D3DXVECTOR3 rotCamera;
	MODELBOOSTER *modelbooster = &modelboosterWk[0];
	MODEL *model = GetModel(0);
	float fDiffRotY;
	//modelbooster->rot.z += 0.1f;
	// カメラの向き取得
	rotCamera = GetRotCamera();
	// 常に前へ
	modelbooster->rotDest.y = rotCamera.y + D3DX_PI;


	// テスト
	if (GetKeyboardPress(DIK_U))
	{
		modelbooster->Nowlife -= 10.0f;
	}
	// 横井童子の回転を一時的に無効か
	// メモ　10で割ってるのは10フレームで移動させるため


	modelbooster->pos = model->pos;
	modelbooster->rot = model->rot;

	//// 目的の角度までの差分
	//fDiffRotY = modelbooster->rotDest.y - modelbooster->rot.y;
	//if (fDiffRotY > D3DX_PI)
	//{
	//	fDiffRotY -= D3DX_PI * 2.0f;
	//}
	//if (fDiffRotY < -D3DX_PI)
	//{
	//	fDiffRotY += D3DX_PI * 2.0f;
	//}

	//// 目的の角度まで慣性をかける
	//modelbooster->rot.y += fDiffRotY * RATE_ROTATE_MODEL;
	//if (modelbooster->rot.y > D3DX_PI)
	//{
	//	modelbooster->rot.y -= D3DX_PI * 2.0f;

	//}
	//if (modelbooster->rot.y < -D3DX_PI)
	//{
	//	modelbooster->rot.y += D3DX_PI * 2.0f;
	//}

	//	modelbooster->rot.y = 3.14f;

	/// 位置移動
	modelbooster->pos.x += modelbooster->move.x;
	modelbooster->pos.y += modelbooster->move.y;
	if (modelbooster->pos.y < 5.0f)
	{
		modelbooster->pos.y = 5.0f;
	}
	if (modelbooster->pos.y > 75.0f)
	{
		modelbooster->pos.y = 75.0f;
	}
	modelbooster->pos.z += modelbooster->move.z;

	// 慣性かける前に移動量を保存
	modelbooster->puremove = modelbooster->move;


	// 移動量に慣性をかける
	modelbooster->move.x += (0.0f - modelbooster->move.x) * RATE_MOVE_MODEL;
	modelbooster->move.y += (0.0f - modelbooster->move.y) * RATE_MOVE_MODEL;
	modelbooster->move.z += (0.0f - modelbooster->move.z) * RATE_MOVE_MODEL;

	// スケール変更
	if (boosteranim == false)
	{
		modelbooster->scl.x += 0.01f;
		modelbooster->scl.y += 0.01f;
		modelbooster->scl.z += 0.01f;
		boostercount++;
		if (boostercount == 10.0f)			// テスト
		{
			boosteranim = true;
		}
	}
	else if (boosteranim == true)
	{
		modelbooster->scl.x -= 0.01f;
		modelbooster->scl.y -= 0.01f;
		modelbooster->scl.z -= 0.01f;
		boostercount--;
		if (boostercount == 0.0f)
		{
			boosteranim = false;
		}
	}

	// 領域外に行ったらストップ(÷2しているのはめり込まないようにするため)
	//if (modelbooster->pos.x < -DROWMAX_X)
	//{
	//	modelbooster->pos.x = -DROWMAX_X;
	//}
	//if (modelbooster->pos.x >  DROWMAX_X)
	//{
	//	modelbooster->pos.x = DROWMAX_X;
	//}
	//if (modelbooster->pos.z  < -DROWMAX_Z)
	//{
	//	modelbooster->pos.z = -DROWMAX_Z;
	//}
	//if (modelbooster->pos.z > DROWMAX_Z)
	//{
	//	modelbooster->pos.z = DROWMAX_Z;
	//}




	// 影の位置設定
	//SetPositionShadow(modelbooster->g_nIdxShadow, D3DXVECTOR3(modelbooster->pos.x, 0.1f, modelbooster->pos.z));

	//SetVertexShadow(modelbooster->g_nIdxShadow, g_fSizeShadow, g_fSizeShadow);
	//SetColorShadow(g_nIdxShadow, g_colShadow);

	PrintDebugProc("[rotDest.yいくつ:(%f) ]\n", modelbooster->rotDest.y);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModelBooster(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	MODELBOOSTER *modelbooster = &modelboosterWk[0];

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&modelbooster->World);


	// スケールを反映
	D3DXMatrixScaling(&mtxScl, modelbooster->scl.x, modelbooster->scl.y, modelbooster->scl.z);
	D3DXMatrixMultiply(&modelbooster->World, &modelbooster->World, &mtxScl);


	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, modelbooster->rot.y, modelbooster->rot.x, modelbooster->rot.z);
	D3DXMatrixMultiply(&modelbooster->World, &modelbooster->World, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, modelbooster->pos.x, modelbooster->pos.y, modelbooster->pos.z);
	D3DXMatrixMultiply(&modelbooster->World, &modelbooster->World, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &modelbooster->World);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatModelBooster->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModelBooster; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureModelBooster);

		// 描画
		g_pD3DXMeshModelBooster->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionModelBooster(void)
{
	MODELBOOSTER *modelbooster = &modelboosterWk[0];
	return modelbooster->pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationModelBooster(void)
{
	MODELBOOSTER *modelbooster = &modelboosterWk[0];
	return modelbooster->rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestModelBooster(void)
{
	MODELBOOSTER *modelbooster = &modelboosterWk[0];
	return modelbooster->rotDest;
}

//*****************************************************************************
// ゲット関数
//*****************************************************************************
MODELBOOSTER *GetModelBooster(int no)
{
	return(&modelboosterWk[0]);
}