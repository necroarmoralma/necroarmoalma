//=============================================================================
//
// tama処理 [hit.cpp]
// Author : 山本　壮将
// tree.cppそのままコピ
//=============================================================================
#include "hit.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "debugproc.h"
#include "model.h"
#include "meshfield.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_HIT		"data/TEXTURE/hit.png"		// 読み込むテクスチャファイル名
#define	VALUE_MOVE_HIT		(3.00f)							// 移動速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexHit(LPDIRECT3DDEVICE9 pDevice);
void SetVertexHit(int nIdxHit, float fWidth, float fHeight);
void SetColorHit(int nIdxHit, D3DXCOLOR col);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureHit[5] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHit = NULL;		// 頂点バッファインターフェースへのポインタ

HIT				hit[BULLET_MAX];				// 弾の構造体配列
bool					hit_alpatest;					// アルファテストON/OFF
int						hitAlpha;						// アルファテストの閾値

char *hitFileName[] =
{
	"data/TEXTURE/hit.png",
	"data/TEXTURE/hit.png",
	"data/TEXTURE/hit.png",
	"data/TEXTURE/hit.png",
	"data/TEXTURE/hit.png",
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitHit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexHit(pDevice);

	// テクスチャの読み込み
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
			hitFileName[nCntTex],			// ファイルの名前
			&g_apD3DTextureHit[nCntTex]);	// 読み込むメモリー
	}

	for (int nCntHit = 0; nCntHit < BULLET_MAX; nCntHit++)
	{
		//hit[nCntHit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//hit[nCntHit].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		//hit[nCntHit].wide = HIT_WIDTH;
		//hit[nCntHit].height = HIT_HEIGHT;
		//hit[nCntHit].use = false;
		//hit[nCntHit].moveon = false;									//
	}

	hit_alpatest = true;
	hitAlpha = 0x0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitHit(void)
{
	// 強制的にすべてを未使用に！

	for (int i = 0; i < BULLET_MAX; i++)
	{
		hit[i].use = false;
	}
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (g_apD3DTextureHit[nCntTex] != NULL)
		{// テクスチャの開放
			g_apD3DTextureHit[nCntTex]->Release();
			g_apD3DTextureHit[nCntTex] = NULL;
		}
	}

	if (g_pD3DVtxBuffHit != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffHit->Release();
		g_pD3DVtxBuffHit = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateHit(void)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);

	rotCamera = GetRotCamera();

	for (int nCntHit = 0; nCntHit < BULLET_MAX; nCntHit++)
	{
		if (hit[nCntHit].use == true)
		{
			hit[nCntHit].life--;
			if (hit[nCntHit].life <= 0.0f)
			{
				hit[nCntHit].use = false;
			}
		}
	}


	// アルファテストON/OFF
	if (GetKeyboardTrigger(DIK_F1))
	{
		hit_alpatest = hit_alpatest ? false : true;
	}

	// アルファテストの閾値変更
	if (GetKeyboardPress(DIK_I))
	{
		hitAlpha--;
		if (hitAlpha < 0)
		{
			hitAlpha = 0;
		}
	}
	if (GetKeyboardPress(DIK_K))
	{
		hitAlpha++;
		if (hitAlpha > 255)
		{
			hitAlpha = 255;
		}
	}


	PrintDebugProc("*** アルファテスト ***\n");
	PrintDebugProc("ON / OFF：[F1] ( 現在：");
	if (hit_alpatest == true)
	{
		PrintDebugProc("ON");
	}
	else
	{
		PrintDebugProc("OFF");
	}
	PrintDebugProc(" )\n");

	if (hit_alpatest == true)
	{
		PrintDebugProc("アルファ閾値：減少[I] / 増加[K] ( 閾値：%d )\n", hitAlpha);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawHit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// αテスト設定
	if (hit_alpatest == true)
	{
		// αテストを有効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, hitAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	}

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntHit = 0; nCntHit < BULLET_MAX; nCntHit++)
	{
		if (hit[nCntHit].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&hit[nCntHit].mtxWorld);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			// ポリゴンを正面に向ける
#if 1
			// 逆行列をもとめる
			D3DXMatrixInverse(&hit[nCntHit].mtxWorld, NULL, &mtxView);
			hit[nCntHit].mtxWorld._41 = 0.0f;
			hit[nCntHit].mtxWorld._42 = 0.0f;
			hit[nCntHit].mtxWorld._43 = 0.0f;
#else
			hit[nCntHit].mtxWorld._11 = mtxView._11;
			hit[nCntHit].mtxWorld._12 = mtxView._21;
			hit[nCntHit].mtxWorld._13 = mtxView._31;
			hit[nCntHit].mtxWorld._21 = mtxView._12;
			hit[nCntHit].mtxWorld._22 = mtxView._22;
			hit[nCntHit].mtxWorld._23 = mtxView._32;
			hit[nCntHit].mtxWorld._31 = mtxView._13;
			hit[nCntHit].mtxWorld._32 = mtxView._23;
			hit[nCntHit].mtxWorld._33 = mtxView._33;
#endif

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, hit[nCntHit].scl.x,
				hit[nCntHit].scl.y,
				hit[nCntHit].scl.z);
			D3DXMatrixMultiply(&hit[nCntHit].mtxWorld, &hit[nCntHit].mtxWorld, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, hit[nCntHit].pos.x,
				hit[nCntHit].pos.y,
				hit[nCntHit].pos.z);
			D3DXMatrixMultiply(&hit[nCntHit].mtxWorld, &hit[nCntHit].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &hit[nCntHit].mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffHit, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apD3DTextureHit[nCntHit % 5]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntHit * 4), NUM_POLYGON);
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
HRESULT MakeVertexHit(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * BULLET_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
		FVF_VERTEX_3D,							// 使用する頂点フォーマット
		D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffHit,						// 頂点バッファインターフェースへのポインタ
		NULL)))									// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffHit->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntHit = 0; nCntHit < BULLET_MAX; nCntHit++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-HIT_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-HIT_WIDTH / 2.0f, HIT_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(HIT_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(HIT_WIDTH / 2.0f, HIT_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffHit->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexHit(int nIdxHit, float fWidth, float fHeight)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffHit->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxHit * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffHit->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorHit(int nIdxHit, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffHit->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxHit * 4);

		// 頂点座標の設定
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffHit->Unlock();
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int SetHit(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col)
{
	int nIdxHit = -1;

	for (int nCntHit = 0; nCntHit < BULLET_MAX; nCntHit++)
	{
		if (hit[nCntHit].use == false)
		{
			hit[nCntHit].pos = pos;
			hit[nCntHit].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			hit[nCntHit].wide = fWidth;
			hit[nCntHit].height = fHeight;
			hit[nCntHit].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			hit[nCntHit].use = true;
			hit[nCntHit].moveon = false;
			hit[nCntHit].life = HITON;
			// 頂点座標の設定
			SetVertexHit(nCntHit, fWidth, fHeight);

			// 頂点カラーの設定
			SetColorHit(nCntHit, col);

			//// 影の設定
			//hit[nCntHit].g_nIdxShadow = CreateShadow(hit[nCntHit].pos, hit[nCntHit].wide, hit[nCntHit].wide);

			//nIdxHit = nCntHit;

			break;
		}
		
	}

	return nIdxHit;
}

//=============================================================================
// たまを取得
//=============================================================================
HIT *GetHit(int no)
{
	return &hit[0];
}

