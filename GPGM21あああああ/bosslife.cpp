//=============================================================================
// ライフ表示
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "bosslife.h"
#include "boss.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_BOSSLIFEWAKU	"data/GAMEWINDOW/bosslifewaku.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_BOSSHPGAGE	"data/GAMEWINDOW/lifered.png"	// 読み込むテクスチャファイル名

// ライフゲージの枠

#define	BOSSLIFEWAKU_WIDTH		(800)		// ライフゲージの枠の幅
#define	BOSSLIFEWAKU_HEIGHT		(80)		// ライフゲージの枠の高さ
#define	BOSSLIFEWAKU_POS_X		(20)		// ライフゲージの枠の位置(X座標)
#define	BOSSLIFEWAKU_POS_Y		(SCREEN_HEIGHT - BOSSLIFEWAKU_HEIGHT)		// ライフゲージの枠の位置(Y座標)

// ライフを表すゲージ
#define	BOSSHPGAGE_WIDTH		(BOSSLIFEWAKU_WIDTH -100)		// ライフゲージの幅
#define	BOSSHPGAGE_HEIGHT		(BOSSLIFEWAKU_HEIGHT - 60)		// ライフゲージの高さ
#define	BOSSHPGAGE_POS_X		(BOSSLIFEWAKU_POS_X +10)		// ライフゲージの位置(X座標)
#define	BOSSHPGAGE_POS_Y		(BOSSLIFEWAKU_POS_Y + 10)		// ライフゲージの位置(Y座標)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBosslife(LPDIRECT3DDEVICE9 pDevice);
void SetColorBosslife(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBossLifewaku = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBossLifewaku = NULL;	// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureBossLifegage = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBossLifegage = NULL;		// 頂点バッファインターフェースへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBosslife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// 頂点情報の作成
	MakeVertexBosslife(pDevice);


	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_BOSSLIFEWAKU,			// ファイルの名前
		&g_pD3DTextureBossLifewaku);	// 読み込むメモリー


	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_BOSSHPGAGE,			// ファイルの名前
		&g_pD3DTextureBossLifegage);		// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBosslife(void)
{

	if (g_pD3DTextureBossLifewaku != NULL)
	{// テクスチャの開放
		g_pD3DTextureBossLifewaku->Release();
		g_pD3DTextureBossLifewaku = NULL;
	}

	if (g_pD3DVtxBuffBossLifewaku != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffBossLifewaku->Release();
		g_pD3DVtxBuffBossLifewaku = NULL;
	}

	if (g_pD3DTextureBossLifegage != NULL)
	{// テクスチャの開放
		g_pD3DTextureBossLifegage->Release();
		g_pD3DTextureBossLifegage = NULL;
	}

	if (g_pD3DVtxBuffBossLifegage != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffBossLifegage->Release();
		g_pD3DVtxBuffBossLifegage = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBosslife(void)
{
#if 0
	if (g_nCountAppearBossLifegage >= COUNT_APPERA_BOSSHPGAGE)
	{
		g_nConutDemo++;
		if (g_nConutDemo > COUNT_WAIT_DEMO)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
#endif



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBosslife(void)
{
	BOSS *boss = GetBoss(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float bossHPhiritsu;		// モデルの?の比率
	float bossHPDraw;			// 表示するHPバーの長さ

	bossHPhiritsu = (boss->boss_life) / (boss->boss_maxlife);
	// 表示するバーの長さ
	bossHPDraw = (bossHPhiritsu * BOSSHPGAGE_WIDTH);
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBossLifegage->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X, BOSSHPGAGE_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X + bossHPDraw, BOSSHPGAGE_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X, BOSSHPGAGE_POS_Y + BOSSHPGAGE_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X + bossHPDraw, BOSSHPGAGE_POS_Y + BOSSHPGAGE_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffBossLifegage->Unlock();
	}


	// ライフの枠を描画
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffBossLifewaku, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureBossLifewaku);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


	// ライフゲージを描画
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffBossLifegage, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureBossLifegage);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBosslife(LPDIRECT3DDEVICE9 pDevice)
{

	// ライフゲージの枠部分のバッファ作成
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_2D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&g_pD3DVtxBuffBossLifewaku,	// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_pD3DVtxBuffBossLifewaku->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(BOSSLIFEWAKU_POS_X, BOSSLIFEWAKU_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BOSSLIFEWAKU_POS_X + BOSSLIFEWAKU_WIDTH, BOSSLIFEWAKU_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(BOSSLIFEWAKU_POS_X, BOSSLIFEWAKU_POS_Y + BOSSLIFEWAKU_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BOSSLIFEWAKU_POS_X + BOSSLIFEWAKU_WIDTH, BOSSLIFEWAKU_POS_Y + BOSSLIFEWAKU_HEIGHT, 0.0f);

			// テクスチャのパースペクティブコレクト用
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// 頂点データをアンロックする
			g_pD3DVtxBuffBossLifewaku->Unlock();
		}

	}
	// ライフゲージの頂点バッファを生成
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_2D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&g_pD3DVtxBuffBossLifegage,		// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_pD3DVtxBuffBossLifegage->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X, BOSSHPGAGE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X + BOSSHPGAGE_WIDTH, BOSSHPGAGE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X, BOSSHPGAGE_POS_Y + BOSSHPGAGE_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X + BOSSHPGAGE_WIDTH, BOSSHPGAGE_POS_Y + BOSSHPGAGE_HEIGHT, 0.0f);

			// テクスチャのパースペクティブコレクト用
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// 頂点データをアンロックする
			g_pD3DVtxBuffBossLifegage->Unlock();
		}
	}

	return S_OK;
}

//=============================================================================
// 頂点の作成
//=============================================================================
void SetColorBosslife(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBossLifewaku->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffBossLifewaku->Unlock();
	}

}

