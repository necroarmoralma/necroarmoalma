//=============================================================================
//
// モデル処理 [skydoom.cpp]
// Author : GP11B243 33 山本 壮将
//=============================================================================
#include "skydoom.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"
#include "meshfield.h"
#include "model.h"
#include "bulletmk2.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 旧#define	SKYDOOM_AIRPLANE		"data/MODEL/chesboad.blend.x"	// 読み込むモデル名
#define	SKYDOOM_AIRPLANE		"data/MODEL/skydoom0.x"
#define	SKYDOOM_CIRCLE			"data/STAGE/skydoom.x"
#define	TEXTURESKYDOOM			"data/TEXTURE/skydome0102.png"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void skydoomshot(void);
//void skydoombeam(void);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureSkydoom;			// テクスチャ読み込み場所
												//LPD3DXMESH			g_pD3DXMeshSkydoom;			// ID3DXMeshインターフェイスへのポインタ
												//LPD3DXBUFFER		g_pD3DXBuffMatSkydoom;		// メッシュのマテリアル情報を格納
												//DWORD				g_nNumMatSkydoom;				// 属性情報の総数
												/*
												D3DXMATRIX			skydoom->World;			// ワールドマトリックス
												D3DXVECTOR3			skydoom->pos;					// 現在の位置
												D3DXVECTOR3			skydoom->move;				// 移動量
												D3DXVECTOR3			skydoom->rot;					// 現在の向き
												D3DXVECTOR3			skydoom->rotDest;				// 目的の向き
												*/

int					skydoomnidxShadow;				// 影ID
float				skydoomsizeShadow;				// 影のサイズ
D3DXCOLOR			skydoomcolShadow;				// 影の色
SKYDOOM				skydoomWk[1];					// モデル構造体(モデルは１）

int					skydoomactcheck;					// てすと
													//=============================================================================
													// 初期化処理
													//=============================================================================
HRESULT InitSkydoom(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SKYDOOM *skydoom = &skydoomWk[0];
	D3DXVECTOR3 rotCamera;

	// HPの設定
	skydoom->skydoom_maxlife = SKYDOOMLIFE;
	skydoom->skydoom_life = skydoom->skydoom_maxlife;

	g_pD3DTextureSkydoom = NULL;
	skydoom->MeshSkydoom = NULL;
	skydoom->BuffMatSkydoom = NULL;

	skydoom->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	skydoom->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	skydoom->puremove = skydoom->move;
	skydoom->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	skydoom->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	skydoom->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);


	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(SKYDOOM_CIRCLE,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&skydoom->BuffMatSkydoom,
		NULL,
		&skydoom->NumMatSkydoom,
		&skydoom->MeshSkydoom)))
	{
		return E_FAIL;
	}


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURESKYDOOM,		// ファイルの名前
		&g_pD3DTextureSkydoom);	// 読み込むメモリー


							// 影の生成
							//skydoomnidxShadow = CreateShadow(skydoom->pos, 25.0f, 25.0f);

							//skydoomsizeShadow = 25.0f;
							//skydoomcolShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSkydoom(void)
{
	SKYDOOM *skydoom = &skydoomWk[0];
	if (g_pD3DTextureSkydoom != NULL)
	{// テクスチャの開放
		g_pD3DTextureSkydoom->Release();
		g_pD3DTextureSkydoom = NULL;
	}

	if (skydoom->MeshSkydoom != NULL)
	{// メッシュの開放
		skydoom->MeshSkydoom->Release();
		skydoom->MeshSkydoom = NULL;
	}

	if (skydoom->BuffMatSkydoom != NULL)
	{// マテリアルの開放
		skydoom->BuffMatSkydoom->Release();
		skydoom->BuffMatSkydoom = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSkydoom(void)
{
	D3DXVECTOR3 rotCamera;
	SKYDOOM *skydoom = &skydoomWk[0];
	MODEL *model = GetModel(0);
	float fDiffRotY;
	D3DXVECTOR3 SubposSkydoomtoModel;
	float rotcheckBtoM;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSkydoom(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	SKYDOOM *skydoom = &skydoomWk[0];

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&skydoom->World);


	// スケールを反映
	D3DXMatrixScaling(&mtxScl, skydoom->scl.x, skydoom->scl.y, skydoom->scl.z);
	D3DXMatrixMultiply(&skydoom->World, &skydoom->World, &mtxScl);


	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, skydoom->rot.y, skydoom->rot.x, skydoom->rot.z);
	D3DXMatrixMultiply(&skydoom->World, &skydoom->World, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, skydoom->pos.x, skydoom->pos.y, skydoom->pos.z);
	D3DXMatrixMultiply(&skydoom->World, &skydoom->World, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &skydoom->World);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)skydoom->BuffMatSkydoom->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)skydoom->NumMatSkydoom; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureSkydoom);

		// 描画
		skydoom->MeshSkydoom->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionSkydoom(void)
{
	SKYDOOM *skydoom = &skydoomWk[0];
	return skydoom->pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationSkydoom(void)
{
	SKYDOOM *skydoom = &skydoomWk[0];
	return skydoom->rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestSkydoom(void)
{
	SKYDOOM *skydoom = &skydoomWk[0];
	return skydoom->rotDest;
}

//*****************************************************************************
// ゲット関数
//*****************************************************************************
SKYDOOM *GetSkydoom(int no)
{
	return(&skydoomWk[0]);
}
