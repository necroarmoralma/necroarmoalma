//=============================================================================
//
// tama処理 [bulletmk2.cpp]
// Author : HALゲーム学科二年生課程1年　山本壮将
// tree.cppそのままコピ
//=============================================================================
#include "bulletmk2.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "debugproc.h"
#include "model.h"
#include "meshfield.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_BULLETMK2		"data/TEXTURE/karinotama.png"		// 読み込むテクスチャファイル名
#define	VALUE_MOVE_BULLETMK2		(9.00f)							// 移動速度
#define BULLETMK2SPEED				(9.5f)
#define BULLETMK2LIFE				(10 * 60)						// 生存時間　秒数*FPS

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBulletmk2(LPDIRECT3DDEVICE9 pDevice);
void SetVertexBulletmk2(int nIdxBulletmk2, float fWidth, float fHeight);
void SetColorBulletmk2(int nIdxBulletmk2, D3DXCOLOR col);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureBulletmk2[5] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBulletmk2 = NULL;		// 頂点バッファインターフェースへのポインタ

BULLETMK2				bulletmk2[BULLET_MAX];				// 弾の構造体配列
bool					bullet_alpatest;					// アルファテストON/OFF
int						bulletAlpha;						// アルファテストの閾値

char *bulletFileName[] =
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
HRESULT InitBulletmk2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexBulletmk2(pDevice);

	// テクスチャの読み込み
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
			TEXTURE_BULLETMK2,			// ファイルの名前
			&g_apD3DTextureBulletmk2[nCntTex]);	// 読み込むメモリー
	}

	for (int nCntBulletmk2 = 0; nCntBulletmk2 < BULLET_MAX; nCntBulletmk2++)
	{
		//bulletmk2[nCntBulletmk2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//bulletmk2[nCntBulletmk2].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		//bulletmk2[nCntBulletmk2].wide = BULLETMK2_WIDTH;
		//bulletmk2[nCntBulletmk2].height = BULLETMK2_HEIGHT;
		//bulletmk2[nCntBulletmk2].use = false;
		//bulletmk2[nCntBulletmk2].moveon = false;									//
	}

	bullet_alpatest = true;
	bulletAlpha = 0x0;


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBulletmk2(void)
{
	// 強制的にすべてを未使用に！

	for (int i=0; i < BULLET_MAX; i++)
	{
		bulletmk2[i].use = false;
	} 
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (g_apD3DTextureBulletmk2[nCntTex] != NULL)
		{// テクスチャの開放
			g_apD3DTextureBulletmk2[nCntTex]->Release();
			g_apD3DTextureBulletmk2[nCntTex] = NULL;
		}
	}

	if (g_pD3DVtxBuffBulletmk2 != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffBulletmk2->Release();
		g_pD3DVtxBuffBulletmk2 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBulletmk2(void)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);

	rotCamera = GetRotCamera();


	// 移動テスト
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletmk2[i].use == true)

		{
			// 速度計さんと回転は一度確定したらそのまま
			// 移動量が決まっていないなら決める
			if (bulletmk2[i].moveon == false)
			{
				bulletmk2[i].rot.y += bulletmk2[i].hoseix;
				bulletmk2[i].moveon = true;
				bulletmk2[i].move.x = (sinf(D3DX_PI + bulletmk2[i].rot.y) * VALUE_MOVE_MODEL *3.5f);	// 3.5は弾速あげてるだけでした
				bulletmk2[i].move.z = (cosf(D3DX_PI + bulletmk2[i].rot.y) * VALUE_MOVE_MODEL *3.5f);
				bulletmk2[i].move.y = bulletmk2[i].hoseiz;
			}

			//+model->rot.y
			//	+ model->rot.y

			/// 位置移動
			bulletmk2[i].pos.x += bulletmk2[i].move.x;
			bulletmk2[i].pos.z += bulletmk2[i].move.z;
			bulletmk2[i].pos.y += bulletmk2[i].move.y;

			// ライフ一定以下なら削除
			bulletmk2[i].life--;
			if(bulletmk2[i].life <= 0)
			{
				bulletmk2[i].use = false;
			}

		}
	}
	for (int nCntBulletmk2 = 0; nCntBulletmk2 < BULLET_MAX; nCntBulletmk2++)
	{
		if (bulletmk2[nCntBulletmk2].use == true)
		{
			// 影の位置設定
			SetPositionShadow(bulletmk2[nCntBulletmk2].g_nIdxShadow, D3DXVECTOR3(bulletmk2[nCntBulletmk2].pos.x, 0.1f, bulletmk2[nCntBulletmk2].pos.z));
		}
	}

	// アルファテストON/OFF
	if (GetKeyboardTrigger(DIK_F1))
	{
		bullet_alpatest = bullet_alpatest ? false : true;
	}

	// アルファテストの閾値変更
	if (GetKeyboardPress(DIK_I))
	{
		bulletAlpha--;
		if (bulletAlpha < 0)
		{
			bulletAlpha = 0;
		}
	}
	if (GetKeyboardPress(DIK_K))
	{
		bulletAlpha++;
		if (bulletAlpha > 255)
		{
			bulletAlpha = 255;
		}
	}

	PrintDebugProc("*** アルファテスト ***\n");
	PrintDebugProc("ON / OFF：[F1] ( 現在：");
	if (bullet_alpatest == true)
	{
		PrintDebugProc("ON");
	}
	else
	{
		PrintDebugProc("OFF");
	}
	PrintDebugProc(" )\n");

	if (bullet_alpatest == true)
	{
		PrintDebugProc("アルファ閾値：減少[I] / 増加[K] ( 閾値：%d )\n", bulletAlpha);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBulletmk2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// αテスト設定
	if (bullet_alpatest == true)
	{
		// αテストを有効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, bulletAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	}

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBulletmk2 = 0; nCntBulletmk2 < BULLET_MAX; nCntBulletmk2++)
	{
		if (bulletmk2[nCntBulletmk2].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&bulletmk2[nCntBulletmk2].mtxWorld);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			// ポリゴンを正面に向ける
#if 1
			// 逆行列をもとめる
			D3DXMatrixInverse(&bulletmk2[nCntBulletmk2].mtxWorld, NULL, &mtxView);
			bulletmk2[nCntBulletmk2].mtxWorld._41 = 0.0f;
			bulletmk2[nCntBulletmk2].mtxWorld._42 = 0.0f;
			bulletmk2[nCntBulletmk2].mtxWorld._43 = 0.0f;
#else
			bulletmk2[nCntBulletmk2].mtxWorld._11 = mtxView._11;
			bulletmk2[nCntBulletmk2].mtxWorld._12 = mtxView._21;
			bulletmk2[nCntBulletmk2].mtxWorld._13 = mtxView._31;
			bulletmk2[nCntBulletmk2].mtxWorld._21 = mtxView._12;
			bulletmk2[nCntBulletmk2].mtxWorld._22 = mtxView._22;
			bulletmk2[nCntBulletmk2].mtxWorld._23 = mtxView._32;
			bulletmk2[nCntBulletmk2].mtxWorld._31 = mtxView._13;
			bulletmk2[nCntBulletmk2].mtxWorld._32 = mtxView._23;
			bulletmk2[nCntBulletmk2].mtxWorld._33 = mtxView._33;
#endif

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, bulletmk2[nCntBulletmk2].scl.x,
				bulletmk2[nCntBulletmk2].scl.y,
				bulletmk2[nCntBulletmk2].scl.z);
			D3DXMatrixMultiply(&bulletmk2[nCntBulletmk2].mtxWorld, &bulletmk2[nCntBulletmk2].mtxWorld, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, bulletmk2[nCntBulletmk2].pos.x,
				bulletmk2[nCntBulletmk2].pos.y,
				bulletmk2[nCntBulletmk2].pos.z);
			D3DXMatrixMultiply(&bulletmk2[nCntBulletmk2].mtxWorld, &bulletmk2[nCntBulletmk2].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &bulletmk2[nCntBulletmk2].mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffBulletmk2, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apD3DTextureBulletmk2[nCntBulletmk2 % 5]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntBulletmk2 * 4), NUM_POLYGON);
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
HRESULT MakeVertexBulletmk2(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * BULLET_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
		FVF_VERTEX_3D,							// 使用する頂点フォーマット
		D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffBulletmk2,						// 頂点バッファインターフェースへのポインタ
		NULL)))									// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBulletmk2->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntBulletmk2 = 0; nCntBulletmk2 < BULLET_MAX; nCntBulletmk2++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-BULLETMK2_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-BULLETMK2_WIDTH / 2.0f, BULLETMK2_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(BULLETMK2_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULLETMK2_WIDTH / 2.0f, BULLETMK2_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffBulletmk2->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBulletmk2(int nIdxBulletmk2, float fWidth, float fHeight)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBulletmk2->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBulletmk2 * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffBulletmk2->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorBulletmk2(int nIdxBulletmk2, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBulletmk2->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBulletmk2 * 4);

		// 頂点座標の設定
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffBulletmk2->Unlock();
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int SetBulletmk2(D3DXVECTOR3 pos, float fWidth, float fHeight,float SIDE,float UP, D3DXCOLOR col)
{
	MODEL *model = GetModel(0);
	int nIdxBulletmk2 = -1;

	for (int nCntBulletmk2 = 0; nCntBulletmk2 < BULLET_MAX; nCntBulletmk2++)
	{
		if (bulletmk2[nCntBulletmk2].use == false)
		{
			bulletmk2[nCntBulletmk2].rot = model->rot;
			bulletmk2[nCntBulletmk2].pos = D3DXVECTOR3(model->pos.x, model->pos.y, model->pos.z);
			bulletmk2[nCntBulletmk2].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			bulletmk2[nCntBulletmk2].wide = fWidth;
			bulletmk2[nCntBulletmk2].height = fHeight;
			bulletmk2[nCntBulletmk2].move = D3DXVECTOR3(0.0f,0.0f,0.0f);
			bulletmk2[nCntBulletmk2].use = true;
			bulletmk2[nCntBulletmk2].moveon = false;
			bulletmk2[nCntBulletmk2].hoseix = SIDE;
			bulletmk2[nCntBulletmk2].hoseiz = UP;
			bulletmk2[nCntBulletmk2].life = BULLETMK2LIFE;
			// 頂点座標の設定
			SetVertexBulletmk2(nCntBulletmk2, fWidth, fHeight);

			// 頂点カラーの設定
			SetColorBulletmk2(nCntBulletmk2, col);

			// 影の設定
			bulletmk2[nCntBulletmk2].g_nIdxShadow = CreateShadow(bulletmk2[nCntBulletmk2].pos, bulletmk2[nCntBulletmk2].wide, bulletmk2[nCntBulletmk2].wide);

			nIdxBulletmk2 = nCntBulletmk2;

			break;
		}
	}

	return nIdxBulletmk2;
}

//=============================================================================
// たまを取得
//=============================================================================
BULLETMK2 *GetBulletmk2(int no)
{
	return &bulletmk2[0];
}

