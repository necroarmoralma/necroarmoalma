//*******************************************************************************
// ファイル名:	bossbullet.cpp
// 作成者:		山本壮将
// 説明:		ボスと敵の弾
// 
//*******************************************************************************
#include "bossbullet.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "debugproc.h"
#include "model.h"
#include "meshfield.h"
#include "boss.h"
#include "map.h"
#include "setting.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_BOSSBULLET		"data/TEXTURE/karinotama.png"		// 読み込むテクスチャファイル名
#define	VALUE_MOVE_BOSSBULLET		(1.5f)							// 弾速
#define BOSSBULLETLIMIT				(1500)
#define BOSSBULLETLIVE				(5*60)							// 生存時間
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBossbullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexBossbullet(int nIdxBossbullet, float fWidth, float fHeight);
void SetColorBossbullet(int nIdxBossbullet, D3DXCOLOR col);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureBossbullet[5] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBossbullet = NULL;		// 頂点バッファインターフェースへのポインタ

BOSSBULLET				bossbullet[BOSSBULLET_MAX];				// 弾の構造体配列
bool					bossbullet_alpatest;					// アルファテストON/OFF
int						bossbulletAlpha;						// アルファテストの閾値

char *bossbulletFileName[] =
{
	"data/TEXTURE/bossbullet.png",
	"data/TEXTURE/bossbullet.png",
	"data/TEXTURE/bossbullet.png",
	"data/TEXTURE/bossbullet.png",
	"data/TEXTURE/bossbullet.png",
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBossbullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexBossbullet(pDevice);

	// テクスチャの読み込み
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
			bossbulletFileName[nCntTex],			// ファイルの名前
			&g_apD3DTextureBossbullet[nCntTex]);	// 読み込むメモリー
	}

	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
	{
		//bossbullet[nCntBossbullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//bossbullet[nCntBossbullet].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		//bossbullet[nCntBossbullet].wide = BOSSBULLET_WIDTH;
		//bossbullet[nCntBossbullet].height = BOSSBULLET_HEIGHT;
		//bossbullet[nCntBossbullet].use = false;
		//bossbullet[nCntBossbullet].moveon = false;									//
	}

	bossbullet_alpatest = true;
	bossbulletAlpha = 0x0;


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBossbullet(void)
{
	// 強制終了(強制的にすべてを未使用にします）
	for (int i = 0; i < BOSSBULLET_MAX; i++)
	{
		bossbullet[i].use = false;
	}
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (g_apD3DTextureBossbullet[nCntTex] != NULL)
		{// テクスチャの開放
			g_apD3DTextureBossbullet[nCntTex]->Release();
			g_apD3DTextureBossbullet[nCntTex] = NULL;
		}
	}

	if (g_pD3DVtxBuffBossbullet != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffBossbullet->Release();
		g_pD3DVtxBuffBossbullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBossbullet(void)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);
	float rotsetBossBtoP;
	BOOL bossbullethit;
	float checkdistance;
	ENEMYLENGTH *length = GetEnemylength(0);
	rotCamera = GetRotCamera();

	
	// 移動
	for (int i = 0; i < BOSSBULLET_MAX; i++)
	{
		if (bossbullet[i].use == true)

		{
			bossbullet[i].count --;

			// 速度計さんと回転は一度確定したらそのまま
			// 移動量が決まっていないなら決める
			if (bossbullet[i].moveon == false)
			{
				//++自機に向かせる
			
				bossbullet[i].moveon = true;
				bossbullet[i].pos.y = model->pos.y;
				bossbullet[i].move.x = (sinf(D3DX_PI + bossbullet[i].bossbullet_rot) * VALUE_MOVE_BOSSBULLET *3.5f);	// 3.5は弾速あげてるだけでした
				bossbullet[i].move.z = (cosf(D3DX_PI + bossbullet[i].bossbullet_rot) * VALUE_MOVE_BOSSBULLET *3.5f);
			}

			/// 位置移動
			bossbullet[i].pos.x += bossbullet[i].move.x;
			bossbullet[i].pos.z += bossbullet[i].move.z;

			// 生存時間が0以下なら削除
			if(bossbullet[i].count <= 0)
			{
				bossbullet[i].use = false;
			}

		}
	}
	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
	{
		if (bossbullet[nCntBossbullet].use == true)
		{
			// 影の位置設定
		//	SetPositionShadow(bossbullet[nCntBossbullet].g_nIdxShadow, D3DXVECTOR3(bossbullet[nCntBossbullet].pos.x, 0.1f, bossbullet[nCntBossbullet].pos.z));
		}
	}

	// アルファテストON/OFF
	if (GetKeyboardTrigger(DIK_F1))
	{
		bossbullet_alpatest = bossbullet_alpatest ? false : true;
	}

	// アルファテストの閾値変更
	if (GetKeyboardPress(DIK_I))
	{
		bossbulletAlpha--;
		if (bossbulletAlpha < 0)
		{
			bossbulletAlpha = 0;
		}
	}
	if (GetKeyboardPress(DIK_K))
	{
		bossbulletAlpha++;
		if (bossbulletAlpha > 255)
		{
			bossbulletAlpha = 255;
		}
	}

	//PrintDebugProc("*** 木操作 ***\n");
	//PrintDebugProc("前移動   : ↑\n");
	//PrintDebugProc("後移動   : ↓\n");
	//PrintDebugProc("左移動   : ←\n");
	//PrintDebugProc("右移動   : →\n");
	//PrintDebugProc("\n");

	PrintDebugProc("*** アルファテスト ***\n");
	PrintDebugProc("ON / OFF：[F1] ( 現在：");
	if (bossbullet_alpatest == true)
	{
		PrintDebugProc("ON");
	}
	else
	{
		PrintDebugProc("OFF");
	}
	PrintDebugProc(" )\n");

	if (bossbullet_alpatest == true)
	{
		PrintDebugProc("アルファ閾値：減少[I] / 増加[K] ( 閾値：%d )\n", bossbulletAlpha);
	}



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBossbullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// αテスト設定
	if (bossbullet_alpatest == true)
	{
		// αテストを有効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, bossbulletAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	}

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
	{
		if (bossbullet[nCntBossbullet].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&bossbullet[nCntBossbullet].mtxWorld);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			// ポリゴンを正面に向ける
#if 1
			// 逆行列をもとめる
			D3DXMatrixInverse(&bossbullet[nCntBossbullet].mtxWorld, NULL, &mtxView);
			bossbullet[nCntBossbullet].mtxWorld._41 = 0.0f;
			bossbullet[nCntBossbullet].mtxWorld._42 = 0.0f;
			bossbullet[nCntBossbullet].mtxWorld._43 = 0.0f;
#else
			bossbullet[nCntBossbullet].mtxWorld._11 = mtxView._11;
			bossbullet[nCntBossbullet].mtxWorld._12 = mtxView._21;
			bossbullet[nCntBossbullet].mtxWorld._13 = mtxView._31;
			bossbullet[nCntBossbullet].mtxWorld._21 = mtxView._12;
			bossbullet[nCntBossbullet].mtxWorld._22 = mtxView._22;
			bossbullet[nCntBossbullet].mtxWorld._23 = mtxView._32;
			bossbullet[nCntBossbullet].mtxWorld._31 = mtxView._13;
			bossbullet[nCntBossbullet].mtxWorld._32 = mtxView._23;
			bossbullet[nCntBossbullet].mtxWorld._33 = mtxView._33;
#endif

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, bossbullet[nCntBossbullet].scl.x,
				bossbullet[nCntBossbullet].scl.y,
				bossbullet[nCntBossbullet].scl.z);
			D3DXMatrixMultiply(&bossbullet[nCntBossbullet].mtxWorld, &bossbullet[nCntBossbullet].mtxWorld, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, bossbullet[nCntBossbullet].pos.x,
				bossbullet[nCntBossbullet].pos.y,
				bossbullet[nCntBossbullet].pos.z);
			D3DXMatrixMultiply(&bossbullet[nCntBossbullet].mtxWorld, &bossbullet[nCntBossbullet].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &bossbullet[nCntBossbullet].mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffBossbullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apD3DTextureBossbullet[nCntBossbullet % 5]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntBossbullet * 4), NUM_POLYGON);
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
HRESULT MakeVertexBossbullet(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * BOSSBULLET_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
		FVF_VERTEX_3D,							// 使用する頂点フォーマット
		D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffBossbullet,						// 頂点バッファインターフェースへのポインタ
		NULL)))									// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBossbullet->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-BOSSBULLET_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-BOSSBULLET_WIDTH / 2.0f, BOSSBULLET_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(BOSSBULLET_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BOSSBULLET_WIDTH / 2.0f, BOSSBULLET_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffBossbullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBossbullet(int nIdxBossbullet, float fWidth, float fHeight)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBossbullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBossbullet * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffBossbullet->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorBossbullet(int nIdxBossbullet, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBossbullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBossbullet * 4);

		// 頂点座標の設定
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffBossbullet->Unlock();
	}
}

//=============================================================================
// ボスの弾の作成
//=============================================================================
int SetBossbullet(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col,float bossbulletrot )
{
	int nIdxBossbullet = -1;

	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
	{
		if (bossbullet[nCntBossbullet].use == false)
		{
			bossbullet[nCntBossbullet].pos = pos;
			bossbullet[nCntBossbullet].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			bossbullet[nCntBossbullet].wide = fWidth;
			bossbullet[nCntBossbullet].height = fHeight;
			bossbullet[nCntBossbullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			bossbullet[nCntBossbullet].use = true;
			bossbullet[nCntBossbullet].moveon = false;
			bossbullet[nCntBossbullet].bossbullet_rot = bossbulletrot;

			// 頂点座標の設定
			SetVertexBossbullet(nCntBossbullet, fWidth, fHeight);

			// 頂点カラーの設定
			SetColorBossbullet(nCntBossbullet, col);

			// 影の設定
			bossbullet[nCntBossbullet].g_nIdxShadow = CreateShadow(bossbullet[nCntBossbullet].pos, bossbullet[nCntBossbullet].wide, bossbullet[nCntBossbullet].wide);

			nIdxBossbullet = nCntBossbullet;

			break;
		}
	}

	return nIdxBossbullet;
}

//***********************************************************************************
// 関数名: SetEnemybullet

//***********************************************************************************
int SetEnemybullet(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, float enemytargetrot)
{
	int nIdxBossbullet = -1;

	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
	{
		if (bossbullet[nCntBossbullet].use == false)
		{
			bossbullet[nCntBossbullet].pos = pos;
			bossbullet[nCntBossbullet].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			bossbullet[nCntBossbullet].wide = fWidth;
			bossbullet[nCntBossbullet].height = fHeight;
			bossbullet[nCntBossbullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			bossbullet[nCntBossbullet].use = true;
			bossbullet[nCntBossbullet].moveon = false;
			bossbullet[nCntBossbullet].bossbullet_rot = enemytargetrot;
			bossbullet[nCntBossbullet].count = BOSSBULLETLIVE;
			// 頂点座標の設定
			SetVertexBossbullet(nCntBossbullet, fWidth, fHeight);

			// 頂点カラーの設定
			SetColorBossbullet(nCntBossbullet, col);

			// 影の設定
			bossbullet[nCntBossbullet].g_nIdxShadow = CreateShadow(bossbullet[nCntBossbullet].pos, bossbullet[nCntBossbullet].wide, bossbullet[nCntBossbullet].wide);

			nIdxBossbullet = nCntBossbullet;

			break;
		}
	}

	return nIdxBossbullet;
}


//=============================================================================
// 上から落っこちるタイプ
//=============================================================================
//int SetBossbullet(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, float bossbulletrot)
//{
//	int nIdxBossbullet = -1;
//
//	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
//	{
//		if (bossbullet[nCntBossbullet].use == false)
//		{
//			bossbullet[nCntBossbullet].pos = pos;
//			bossbullet[nCntBossbullet].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//			bossbullet[nCntBossbullet].wide = fWidth;
//			bossbullet[nCntBossbullet].height = fHeight;
//			bossbullet[nCntBossbullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			bossbullet[nCntBossbullet].use = true;
//			bossbullet[nCntBossbullet].moveon = false;
//			bossbullet[nCntBossbullet].bossbullet_rot = bossbulletrot;
//
//			// 頂点座標の設定
//			SetVertexBossbullet(nCntBossbullet, fWidth, fHeight);
//
//			// 頂点カラーの設定
//			SetColorBossbullet(nCntBossbullet, col);
//
//			// 影の設定
//			bossbullet[nCntBossbullet].g_nIdxShadow = CreateShadow(bossbullet[nCntBossbullet].pos, bossbullet[nCntBossbullet].wide, bossbullet[nCntBossbullet].wide);
//
//			nIdxBossbullet = nCntBossbullet;
//
//			break;
//		}
//	}
//
//	return nIdxBossbullet;
//}

//=============================================================================
// たまを取得
//=============================================================================
BOSSBULLET *GetBossbullet(int no)
{
	return &bossbullet[0];
}

