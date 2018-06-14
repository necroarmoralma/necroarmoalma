//=============================================================================
//
// モデル処理 [map.cpp]
// Author : GP11B243 33 山本 壮将
//=============================================================================
#include "map.h"
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
#define MAP_SCHOOL "data/STAGE/stage0613.x"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void mapshot(void);
//void mapbeam(void);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureMap;			// テクスチャ読み込み場所
//LPD3DXMESH			g_pD3DXMeshMap;			// ID3DXMeshインターフェイスへのポインタ
//LPD3DXBUFFER		g_pD3DXBuffMatMap;		// メッシュのマテリアル情報を格納
//DWORD				g_nNumMatMap;				// 属性情報の総数
												/*
D3DXMATRIX			map->World;			// ワールドマトリックス
D3DXVECTOR3			map->pos;					// 現在の位置
D3DXVECTOR3			map->move;				// 移動量
D3DXVECTOR3			map->rot;					// 現在の向き
D3DXVECTOR3			map->rotDest;				// 目的の向き
												*/

int					mapnidxShadow;				// 影ID
float				mapsizeShadow;				// 影のサイズ
D3DXCOLOR			mapcolShadow;				// 影の色
MAP				mapWk[1];					// モデル構造体(モデルは１）

int					mapactcheck;					// てすと
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MAP *map = &mapWk[0];
	D3DXVECTOR3 rotCamera;

	// HPの設定
	map->map_maxlife = MAPLIFE;
	map->map_life = map->map_maxlife;

	g_pD3DTextureMap = NULL;
	map->MeshMap = NULL;
	map->BuffMatMap = NULL;

	map->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	map->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	map->puremove = map->move;
	map->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	map->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	map->scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	

	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(MAP_SCHOOL,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&map->BuffMatMap,
		NULL,
		&map->NumMatMap,
		&map->MeshMap)))
	{
		return E_FAIL;
	}

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&g_pD3DTextureMap);	// 読み込むメモリー
#endif

								// 影の生成
	//mapnidxShadow = CreateShadow(map->pos, 25.0f, 25.0f);

	//mapsizeShadow = 25.0f;
	//mapcolShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMap(void)
{
	MAP *map = &mapWk[0];
	if (g_pD3DTextureMap != NULL)
	{// テクスチャの開放
		g_pD3DTextureMap->Release();
		g_pD3DTextureMap = NULL;
	}

	if (map->MeshMap != NULL)
	{// メッシュの開放
		map->MeshMap->Release();
		map->MeshMap = NULL;
	}

	if (map->BuffMatMap != NULL)
	{// マテリアルの開放
		map->BuffMatMap->Release();
		map->BuffMatMap = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMap(void)
{
	D3DXVECTOR3 rotCamera;
	MAP *map = &mapWk[0];
	MODEL *model = GetModel(0);
	float fDiffRotY;
	D3DXVECTOR3 SubposMaptoModel;
	float rotcheckBtoM;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	MAP *map = &mapWk[0];

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&map->World);


	// スケールを反映
	D3DXMatrixScaling(&mtxScl, map->scl.x, map->scl.y, map->scl.z);
	D3DXMatrixMultiply(&map->World, &map->World, &mtxScl);


	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, map->rot.y, map->rot.x, map->rot.z);
	D3DXMatrixMultiply(&map->World, &map->World, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, map->pos.x, map->pos.y, map->pos.z);
	D3DXMatrixMultiply(&map->World, &map->World, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &map->World);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)map->BuffMatMap->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)map->NumMatMap; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureMap);

		// 描画
		map->MeshMap->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionMap(void)
{
	MAP *map = &mapWk[0];
	return map->pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationMap(void)
{
	MAP *map = &mapWk[0];
	return map->rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestMap(void)
{
	MAP *map = &mapWk[0];
	return map->rotDest;
}

//*****************************************************************************
// ゲット関数
//*****************************************************************************
MAP *GetMap(int no)
{
	return(&mapWk[0]);
}

////*****************************************************************************
//// ボスの行動まとめ
////*****************************************************************************
//void mapshot(void)
//{
//	MAP *map = &mapWk[0];
//	// 玉発射
//	D3DXVECTOR3 pos = map->pos;
//	SetMapbullet(map->pos, 30.0f, 30.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//	map->acttime = MAPACT;
//}
//
////*******************************
//// レーザー
////*******************************
//void mapbeam(void)
//{
//	MAP *map = &mapWk[0];
//	D3DXVECTOR3 pos = map->pos;
//	map->rot.y = 0;
//	SetMapbullet(map->pos, 20.0f, 60.0f, D3DXCOLOR(0.6f, 1.0f, 1.0f, 1.0f));
//	map->acttime = MAPACT;
//
//}