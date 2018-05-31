//=============================================================================
// ライフ表示
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "evolve.h"
#include "model.h"
#include "modellife.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EVOLVEWAKU	"data/GAMEWINDOW/evolve.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_EVOLVEGAGE	"data/GAMEWINDOW/lifeegreen.png"	// 読み込むテクスチャファイル名

// ライフゲージの枠
#define	EVOLVEWAKU_POS_X		(LIFEWAKU_POS_X+LIFEWAKU_WIDTH)		// ライフゲージの枠の位置(X座標)
#define	EVOLVEWAKU_POS_Y		(LIFEWAKU_POS_Y)		// ライフゲージの枠の位置(Y座標)
#define	EVOLVEWAKU_WIDTH		(500)		// ライフゲージの枠の幅
#define	EVOLVEWAKU_HEIGHT		(80)		// ライフゲージの枠の高さ

// ライフを表すゲージ
#define	EVOLVEGAGE_POS_X				(HPGAGE_WIDTH + 10)		// ライフゲージの位置(X座標)
#define	EVOLVEGAGE_POS_Y				(HPGAGE_POS_Y)		// ライフゲージの位置(Y座標)
#define	EVOLVEGAGE_WIDTH				(470)		// ライフゲージの幅
#define	EVOLVEGAGE_HEIGHT			(20)		// ライフゲージの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexModelevolve(LPDIRECT3DDEVICE9 pDevice);
void SetColorModelevolve(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEvolvewaku = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEvolvewaku = NULL;	// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureEvolvegage = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEvolvegage = NULL;		// 頂点バッファインターフェースへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitModelevolve(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// 頂点情報の作成
	MakeVertexModelevolve(pDevice);


	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_EVOLVEWAKU,			// ファイルの名前
		&g_pD3DTextureEvolvewaku);	// 読み込むメモリー


	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_EVOLVEGAGE,			// ファイルの名前
		&g_pD3DTextureEvolvegage);		// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModelevolve(void)
{

	if (g_pD3DTextureEvolvewaku != NULL)
	{// テクスチャの開放
		g_pD3DTextureEvolvewaku->Release();
		g_pD3DTextureEvolvewaku = NULL;
	}

	if (g_pD3DVtxBuffEvolvewaku != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEvolvewaku->Release();
		g_pD3DVtxBuffEvolvewaku = NULL;
	}

	if (g_pD3DTextureEvolvegage != NULL)
	{// テクスチャの開放
		g_pD3DTextureEvolvegage->Release();
		g_pD3DTextureEvolvegage = NULL;
	}

	if (g_pD3DVtxBuffEvolvegage != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEvolvegage->Release();
		g_pD3DVtxBuffEvolvegage = NULL;
	}
}//*void

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModelevolve(void)
{
#if 0
	if (g_nCountAppearEvolvegage >= COUNT_APPERA_EVOLVEGAGE)
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
void DrawModelevolve(void)
{
	MODEL *model = GetModel(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float modelEVOLVEhiritsu;		// 比率
	float modelEVOLVEDraw;			// 表示するEVOLVEバーの長さ

	modelEVOLVEhiritsu = (model->nowshot_evolve) / (model->shot_evolve);
	// 表示するバーの長さ
	modelEVOLVEDraw = (modelEVOLVEhiritsu * EVOLVEGAGE_WIDTH);
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEvolvegage->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X, EVOLVEGAGE_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X + modelEVOLVEDraw, EVOLVEGAGE_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X, EVOLVEGAGE_POS_Y + EVOLVEGAGE_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X + modelEVOLVEDraw, EVOLVEGAGE_POS_Y + EVOLVEGAGE_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffEvolvegage->Unlock();
	}


	// ライフの枠を描画
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEvolvewaku, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureEvolvewaku);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


	// ライフゲージを描画
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEvolvegage, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureEvolvegage);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexModelevolve(LPDIRECT3DDEVICE9 pDevice)
{

	// ライフゲージの枠部分のバッファ作成
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_2D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&g_pD3DVtxBuffEvolvewaku,	// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_pD3DVtxBuffEvolvewaku->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(EVOLVEWAKU_POS_X, EVOLVEWAKU_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(EVOLVEWAKU_POS_X + EVOLVEWAKU_WIDTH, EVOLVEWAKU_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(EVOLVEWAKU_POS_X, EVOLVEWAKU_POS_Y + EVOLVEWAKU_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EVOLVEWAKU_POS_X + EVOLVEWAKU_WIDTH, EVOLVEWAKU_POS_Y + EVOLVEWAKU_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffEvolvewaku->Unlock();
		}

	}
	// ライフゲージの頂点バッファを生成
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_2D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&g_pD3DVtxBuffEvolvegage,		// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_pD3DVtxBuffEvolvegage->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X, EVOLVEGAGE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X + EVOLVEGAGE_WIDTH, EVOLVEGAGE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X, EVOLVEGAGE_POS_Y + EVOLVEGAGE_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X + EVOLVEGAGE_WIDTH, EVOLVEGAGE_POS_Y + EVOLVEGAGE_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffEvolvegage->Unlock();
		}
	}

	return S_OK;
}

//=============================================================================
// 頂点の作成
//=============================================================================
void SetColorModelevolve(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEvolvewaku->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEvolvewaku->Unlock();
	}

}

