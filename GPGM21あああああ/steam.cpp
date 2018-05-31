//=============================================================================
//
// tama処理 [steam.cpp]
// Author : HALゲーム学科二年生課程1年　山本壮将
// tree.cppそのままコピ
//=============================================================================
#include "steam.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "debugproc.h"
#include "model.h"
#include "meshfield.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_STEAM		"data/TEXTURE/kemuri.png"		// 読み込むテクスチャファイル名
#define	VALUE_MOVE_STEAM		(9.00f)							
//#define STEAMSPEED				(0.1f)							// 移動速度
#define STEAMLIMIT				(11000)							// 仮　弾が移動する領域
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexSteam(LPDIRECT3DDEVICE9 pDevice);
void SetVertexSteam(int nIdxSteam, float fWidth, float fHeight);
void SetColorSteam(int nIdxSteam, D3DXCOLOR col);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureSteam[5] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSteam = NULL;		// 頂点バッファインターフェースへのポインタ

STEAM				steam[STEAM_MAX];				// 弾の構造体配列
bool					steam_alpatest;					// アルファテストON/OFF
int						steamAlpha;						// アルファテストの閾値

char *steamFileName[] =
{
	"data/TEXTURE/testpen.png",
	"data/TEXTURE/testpen.png",
	"data/TEXTURE/testpen.png",
	"data/TEXTURE/testpen.png",
	"data/TEXTURE/testpen.png",
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSteam(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexSteam(pDevice);

	// テクスチャの読み込み
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
			TEXTURE_STEAM,			// ファイルの名前
			&g_apD3DTextureSteam[nCntTex]);	// 読み込むメモリー
	}

	for (int nCntSteam = 0; nCntSteam < STEAM_MAX; nCntSteam++)
	{
		//steam[nCntSteam].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//steam[nCntSteam].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		//steam[nCntSteam].wide = STEAM_WIDTH;
		//steam[nCntSteam].height = STEAM_HEIGHT;
		//steam[nCntSteam].use = false;
		//steam[nCntSteam].moveon = false;									//
	}

	steam_alpatest = true;
	steamAlpha = 0x0;


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSteam(void)
{
	// 強制的にすべてを未使用に！

	for (int i = 0; i < STEAM_MAX; i++)
	{
		steam[i].use = false;
	}
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (g_apD3DTextureSteam[nCntTex] != NULL)
		{// テクスチャの開放
			g_apD3DTextureSteam[nCntTex]->Release();
			g_apD3DTextureSteam[nCntTex] = NULL;
		}
	}

	if (g_pD3DVtxBuffSteam != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffSteam->Release();
		g_pD3DVtxBuffSteam = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSteam(void)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);

	rotCamera = GetRotCamera();


	// 移動テスト
	for (int i = 0; i < STEAM_MAX; i++)
	{
		if (steam[i].use == true)

		{
			// 速度計さんと回転は一度確定したらそのまま
			// 移動量が決まっていないなら決める
			if (steam[i].moveon == false)
			{
				steam[i].move.y = STEAMSPEED;

			}

			//+model->rot.y
			//	+ model->rot.y

			/// 位置移動
			steam[i].pos.x += steam[i].move.x;
			steam[i].pos.z += steam[i].move.z;
			steam[i].pos.y += steam[i].move.y;

			// 左右に拡大
			steam[i].scl.x += 0.1f;

			// カウントを減らし０ならば削除
			steam[i].count--;
			if (steam[i].count < 0)
			{
				steam[i].use = false;
				ReleaseShadow(steam[i].g_nIdxShadow);
			}
		}
	}


	// アルファテストON/OFF
	if (GetKeyboardTrigger(DIK_F1))
	{
		steam_alpatest = steam_alpatest ? false : true;
	}

	// アルファテストの閾値変更
	if (GetKeyboardPress(DIK_I))
	{
		steamAlpha--;
		if (steamAlpha < 0)
		{
			steamAlpha = 0;
		}
	}
	if (GetKeyboardPress(DIK_K))
	{
		steamAlpha++;
		if (steamAlpha > 255)
		{
			steamAlpha = 255;
		}
	}

	PrintDebugProc("*** アルファテスト ***\n");
	PrintDebugProc("ON / OFF：[F1] ( 現在：");
	if (steam_alpatest == true)
	{
		PrintDebugProc("ON");
	}
	else
	{
		PrintDebugProc("OFF");
	}
	PrintDebugProc(" )\n");

	if (steam_alpatest == true)
	{
		PrintDebugProc("アルファ閾値：減少[I] / 増加[K] ( 閾値：%d )\n", steamAlpha);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSteam(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// αテスト設定
	if (steam_alpatest == true)
	{
		// αテストを有効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, steamAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	}

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntSteam = 0; nCntSteam < STEAM_MAX; nCntSteam++)
	{
		if (steam[nCntSteam].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&steam[nCntSteam].mtxWorld);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			// ポリゴンを正面に向ける
#if 1
			// 逆行列をもとめる
			D3DXMatrixInverse(&steam[nCntSteam].mtxWorld, NULL, &mtxView);
			steam[nCntSteam].mtxWorld._41 = 0.0f;
			steam[nCntSteam].mtxWorld._42 = 0.0f;
			steam[nCntSteam].mtxWorld._43 = 0.0f;
#else
			steam[nCntSteam].mtxWorld._11 = mtxView._11;
			steam[nCntSteam].mtxWorld._12 = mtxView._21;
			steam[nCntSteam].mtxWorld._13 = mtxView._31;
			steam[nCntSteam].mtxWorld._21 = mtxView._12;
			steam[nCntSteam].mtxWorld._22 = mtxView._22;
			steam[nCntSteam].mtxWorld._23 = mtxView._32;
			steam[nCntSteam].mtxWorld._31 = mtxView._13;
			steam[nCntSteam].mtxWorld._32 = mtxView._23;
			steam[nCntSteam].mtxWorld._33 = mtxView._33;
#endif

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, steam[nCntSteam].scl.x,
				steam[nCntSteam].scl.y,
				steam[nCntSteam].scl.z);
			D3DXMatrixMultiply(&steam[nCntSteam].mtxWorld, &steam[nCntSteam].mtxWorld, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, steam[nCntSteam].pos.x,
				steam[nCntSteam].pos.y,
				steam[nCntSteam].pos.z);
			D3DXMatrixMultiply(&steam[nCntSteam].mtxWorld, &steam[nCntSteam].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &steam[nCntSteam].mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffSteam, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apD3DTextureSteam[nCntSteam % 5]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntSteam * 4), NUM_POLYGON);
		}
	}

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexSteam(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * STEAM_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
		FVF_VERTEX_3D,							// 使用する頂点フォーマット
		D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffSteam,						// 頂点バッファインターフェースへのポインタ
		NULL)))									// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSteam->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntSteam = 0; nCntSteam < STEAM_MAX; nCntSteam++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-STEAM_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-STEAM_WIDTH / 2.0f, STEAM_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(STEAM_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(STEAM_WIDTH / 2.0f, STEAM_HEIGHT, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffSteam->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexSteam(int nIdxSteam, float fWidth, float fHeight)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSteam->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxSteam * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffSteam->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorSteam(int nIdxSteam, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSteam->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxSteam * 4);

		// 頂点座標の設定
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffSteam->Unlock();
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int SetSteam(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col)
{
	MODEL *model = GetModel(0);
	int nIdxSteam = -1;

	for (int nCntSteam = 0; nCntSteam < STEAM_MAX; nCntSteam++)
	{
		if (steam[nCntSteam].use == false)
		{
			steam[nCntSteam].rot = model->rot;
			steam[nCntSteam].pos = D3DXVECTOR3(model->pos.x, model->pos.y, model->pos.z);
			steam[nCntSteam].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			steam[nCntSteam].wide = fWidth;
			steam[nCntSteam].height = fHeight;
			steam[nCntSteam].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			steam[nCntSteam].use = true;
			steam[nCntSteam].moveon = false;
			// 頂点座標の設定
			SetVertexSteam(nCntSteam, fWidth, fHeight);

			// 頂点カラーの設定
			SetColorSteam(nCntSteam, col);

			// 影の設定
			steam[nCntSteam].g_nIdxShadow = CreateShadow(steam[nCntSteam].pos, steam[nCntSteam].wide, steam[nCntSteam].wide);

			nIdxSteam = nCntSteam;

			// カウントを初期化
			steam[nCntSteam].count = STEAM_RELEASECOUNT;
			break;
		}
	}

	return nIdxSteam;
}

//=============================================================================
// たまを取得
//=============================================================================
STEAM *GetSteam(int no)
{
	return &steam[0];
}

