//=============================================================================
//
// スコア処理 [resultscore.cpp]
// Author : 
//
//=============================================================================
#include "resultscore.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_FRAME_SCORE	"data/TEXTURE/frame_score.png"	// 読み込むテクスチャファイル名
#define	SCORE_SIZE_X		(100.0f)							// スコアの数字の幅
#define	SCORE_SIZE_Y		(100.0f)							// スコアの数字の高さ
#define	SCORE_INTERVAL_X	(0.0f)							// スコアの数字の表示間隔

#define	NUM_PLACE			(5)								// スコアの桁数

#define	SCORE_POS_X			(SCREEN_CENTER_X - (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE +180.0f)	// スコアの表示基準位置Ｘ座標
#define	SCORE_POS_Y			(SCREEN_CENTER_Y-150.0f)																	// スコアの表示基準位置Ｙ座標

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResultscore(LPDIRECT3DDEVICE9 pDevice);
void SetTextureResultscore(int idx, int number);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResultscore[2] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultscore = NULL;		// 頂点バッファインターフェースへのポインタ

D3DXVECTOR3				g_posResultscore;						// 位置
D3DXVECTOR3				g_rotResultscore;						// 向き

int						g_resultscore;						// スコア
RESULTSCORE				resultscoreWk[1];
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResultscore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posResultscore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotResultscore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// スコアの初期化
	g_resultscore = 0;

	// 頂点情報の作成
	MakeVertexResultscore(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_SCORE,			// ファイルの名前
		&g_pD3DTextureResultscore[0]);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FRAME_SCORE,		// ファイルの名前
		&g_pD3DTextureResultscore[1]);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultscore(void)
{
	if(g_pD3DTextureResultscore[0] != NULL)
	{// テクスチャの開放
		g_pD3DTextureResultscore[0]->Release();
		g_pD3DTextureResultscore[0] = NULL;
	}
	if(g_pD3DTextureResultscore[1] != NULL)
	{// テクスチャの開放
		g_pD3DTextureResultscore[1]->Release();
		g_pD3DTextureResultscore[1] = NULL;
	}

	if(g_pD3DVtxBuffResultscore != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffResultscore->Release();
		g_pD3DVtxBuffResultscore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultscore(void)
{
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int number;

		number = (g_resultscore % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		SetTextureResultscore(nCntPlace, number);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResultscore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultscore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureResultscore[0]);

	// ポリゴンの描画
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}

	// テクスチャの設定
	//pDevice->SetTexture(0, g_pD3DTextureResultscore[1]);

	// ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexResultscore(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法　
		FVF_VERTEX_2D,									// 使用する頂点フォーマット
		D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResultscore,							// 頂点バッファインターフェースへのポインタ
		NULL)))											// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultscore->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

			// rhwの設定
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
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y - 25, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y - 25, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y + 55, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y + 55, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffResultscore->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureResultscore(int idx, int number)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffResultscore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// 頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// 頂点データをアンロックする
	g_pD3DVtxBuffResultscore->Unlock();
}

//=============================================================================
// スコアの変更
//=============================================================================
void ChangeResultscore(int value)
{
	g_resultscore += value;
	if(g_resultscore < 0)
	{
		g_resultscore = 0;
	}
	else if(g_resultscore >= (int)(powf(10.0f, (float)(NUM_PLACE + 1))))
	{
		g_resultscore = (int)(powf(10.0f, (float)(NUM_PLACE + 1))) - 1;
	}
}

//**************************************************************************************
//	ゲット関数
//**************************************************************************************
RESULTSCORE *GetResultscore(int no)
{
	return(&resultscoreWk[0]);
}
