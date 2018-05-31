//=============================================================================
// ライフ表示
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "titlerogo.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLEGAMEN	"data/TITLE/title.png"	// 読み込むテクスチャファイル名
//#define	TEXTURE_HPGAGE	"data/GAMEWINDOW/lifegreen.png"	// 読み込むテクスチャファイル名

#define	TITLEGAMEN_POS_X		(0)		// ライフゲージの枠の位置(X座標)
#define	TITLEGAMEN_POS_Y		(0)		// ライフゲージの枠の位置(Y座標)
#define	TITLEGAMEN_WIDTH		(SCREEN_WIDTH)		// ライフゲージの枠の幅
#define	TITLEGAMEN_HEIGHT		(SCREEN_HEIGHT)		// ライフゲージの枠の高さ

//#define	HPGAGE_POS_X				(30)		// ライフゲージの位置(X座標)
//#define	HPGAGE_POS_Y				(30)		// ライフゲージの位置(Y座標)
//#define	HPGAGE_WIDTH				(470)		// ライフゲージの幅
//#define	HPGAGE_HEIGHT			(20)		// ライフゲージの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTitlelogo(LPDIRECT3DDEVICE9 pDevice);
void SetColorTitlelogo(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTitlerogo = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTitlerogo = NULL;	// 頂点バッファインターフェースへのポインタ
//LPDIRECT3DTEXTURE9		g_pD3DTextureLifegage = NULL;		// テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffLifegage = NULL;		// 頂点バッファインターフェースへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitlelogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// 頂点情報の作成
	MakeVertexTitlelogo(pDevice);


	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_TITLEGAMEN,			// ファイルの名前
		&g_pD3DTextureTitlerogo);	// 読み込むメモリー


	//D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
	//	TEXTURE_HPGAGE,			// ファイルの名前
	//	&g_pD3DTextureLifegage);		// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitlelogo(void)
{

	if (g_pD3DTextureTitlerogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitlerogo->Release();
		g_pD3DTextureTitlerogo = NULL;
	}

	if (g_pD3DVtxBuffTitlerogo != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffTitlerogo->Release();
		g_pD3DVtxBuffTitlerogo = NULL;
	}

	//if (g_pD3DTextureLifegage != NULL)
	//{// テクスチャの開放
	//	g_pD3DTextureLifegage->Release();
	//	g_pD3DTextureLifegage = NULL;
	//}

	//if (g_pD3DVtxBuffLifegage != NULL)
	//{// 頂点バッファの開放
	//	g_pD3DVtxBuffLifegage->Release();
	//	g_pD3DVtxBuffLifegage = NULL;
	//}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitlelogo(void)
{
#if 0
	if (g_nCountAppearLifegage >= COUNT_APPERA_HPGAGE)
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
void DrawTitlelogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ライフの枠を描画
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffTitlerogo, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureTitlerogo);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


	//// ライフゲージを描画
	//{
	//	// 頂点バッファをデバイスのデータストリームにバインド
	//	pDevice->SetStreamSource(0, g_pD3DVtxBuffLifegage, 0, sizeof(VERTEX_2D));

	//	// 頂点フォーマットの設定
	//	pDevice->SetFVF(FVF_VERTEX_2D);

	//	// テクスチャの設定
	//	pDevice->SetTexture(0, g_pD3DTextureLifegage);

	//	// ポリゴンの描画
	//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	//}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitlelogo(LPDIRECT3DDEVICE9 pDevice)
{


	// タイトルロゴのバッファ作成
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_2D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&g_pD3DVtxBuffTitlerogo,	// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_pD3DVtxBuffTitlerogo->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(TITLEGAMEN_POS_X, TITLEGAMEN_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(TITLEGAMEN_POS_X + TITLEGAMEN_WIDTH, TITLEGAMEN_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(TITLEGAMEN_POS_X, TITLEGAMEN_POS_Y + TITLEGAMEN_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(TITLEGAMEN_POS_X + TITLEGAMEN_WIDTH, TITLEGAMEN_POS_Y + TITLEGAMEN_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffTitlerogo->Unlock();
		}

	}
	//// ライフゲージの頂点バッファを生成
	//{
	//	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
	//		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
	//		FVF_VERTEX_2D,				// 使用する頂点フォーマット
	//		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
	//		&g_pD3DVtxBuffLifegage,		// 頂点バッファインターフェースへのポインタ
	//		NULL)))						// NULLに設定
	//	{
	//		return E_FAIL;
	//	}

	//	{//頂点バッファの中身を埋める
	//		VERTEX_2D *pVtx;

	//		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	//		g_pD3DVtxBuffLifegage->Lock(0, 0, (void**)&pVtx, 0);

	//		// 頂点座標の設定
	//		pVtx[0].vtx = D3DXVECTOR3(HPGAGE_POS_X, HPGAGE_POS_Y, 0.0f);
	//		pVtx[1].vtx = D3DXVECTOR3(HPGAGE_POS_X + HPGAGE_WIDTH, HPGAGE_POS_Y, 0.0f);
	//		pVtx[2].vtx = D3DXVECTOR3(HPGAGE_POS_X, HPGAGE_POS_Y + HPGAGE_HEIGHT, 0.0f);
	//		pVtx[3].vtx = D3DXVECTOR3(HPGAGE_POS_X + HPGAGE_WIDTH, HPGAGE_POS_Y + HPGAGE_HEIGHT, 0.0f);

	//		// テクスチャのパースペクティブコレクト用
	//		pVtx[0].rhw =
	//			pVtx[1].rhw =
	//			pVtx[2].rhw =
	//			pVtx[3].rhw = 1.0f;

	//		// 反射光の設定
	//		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//		// テクスチャ座標の設定
	//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//		// 頂点データをアンロックする
	//		g_pD3DVtxBuffLifegage->Unlock();
	//	}
	//}

	return S_OK;
}

//=============================================================================
// 頂点の作成
//=============================================================================
void SetColorTitlelogo(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTitlerogo->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffTitlerogo->Unlock();
	}

}

