//=============================================================================
// ファイル名:	infowindow.cpp
// 説明:		作戦目標と敵ライフの情報
// Author : 山本 壮将
//
//=============================================================================
#include "enemyinfo.h"
#include "main.h"
#include "boss.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_ENEMYINFOWAKU	"data/GAMEWINDOW/mokuhyouwindow.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ENEMYINFOICON	"data/GAMEWINDOW/enemyinfo.png"	// 読み込むテクスチャファイル名
#define TEXTURE_ENEMYLIFEGAGE	"data/GAMEWINDOW/lifered.png"
#define ENEMYLIFE


#define	ENEMYINFOWAKU_WIDTH		(200)		// ライフゲージの枠の幅
#define	ENEMYINFOWAKU_HEIGHT		(200)		// ライフゲージの枠の高さ
#define	ENEMYINFOWAKU_POS_X		(SCREEN_WIDTH-ENEMYINFOWAKU_WIDTH)		// ライフゲージの枠の位置(X座標)
#define	ENEMYINFOWAKU_POS_Y		(50)		// ライフゲージの枠の位置(Y座標)

// エネミーアイコンｎ
#define	ENEMYINFOICON_WIDTH				(ENEMYINFOWAKU_WIDTH)		// ライフゲージの幅
#define	ENEMYINFOICON_HEIGHT			(50)		// ライフゲージの高さ
#define	ENEMYINFOICON_POS_X				(SCREEN_WIDTH-ENEMYINFOWAKU_WIDTH)		// ライフゲージの位置(X座標)
#define	ENEMYINFOICON_POS_Y				(ENEMYINFOWAKU_POS_Y-10 + ENEMYINFOWAKU_HEIGHT)		// ライフゲージの位置(Y座標)

// エネミーライフ(エネミーアイコンに重ねる)
#define	ENEMYLIFEGAGE_WIDTH				(ENEMYINFOICON_WIDTH - 40)		// ライフバーの幅
#define	ENEMYLIFEGAGE_HEIGHT			(ENEMYINFOICON_HEIGHT -30)		// ライフバーの高さ
#define	ENEMYLIFEGAGE_POS_X				(ENEMYINFOICON_POS_X+30)							// ライフバーの位置(X座標)
#define	ENEMYLIFEGAGE_POS_Y				(ENEMYINFOICON_POS_Y + 15)		// ライフバーの位置(Y座標)



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemyinfo(LPDIRECT3DDEVICE9 pDevice);
void SetColorEnemyinfo(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyinfowaku = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemyinfowaku = NULL;	// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyinfogage = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemyinfogage = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemylife = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemylife = NULL;		// 頂点バッファインターフェースへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyinfo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// 頂点情報の作成
	MakeVertexEnemyinfo(pDevice);


	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_ENEMYINFOWAKU,			// ファイルの名前
		&g_pD3DTextureEnemyinfowaku);	// 読み込むメモリー


	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_ENEMYINFOICON,			// ファイルの名前
		&g_pD3DTextureEnemyinfogage);		// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_ENEMYLIFEGAGE,			// ファイルの名前
		&g_pD3DTextureEnemylife);		// 読み込むメモリー


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyinfo(void)
{

	if (g_pD3DTextureEnemyinfowaku != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemyinfowaku->Release();
		g_pD3DTextureEnemyinfowaku = NULL;
	}

	if (g_pD3DVtxBuffEnemyinfowaku != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEnemyinfowaku->Release();
		g_pD3DVtxBuffEnemyinfowaku = NULL;
	}

	// アイコン
	if (g_pD3DTextureEnemyinfogage != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemyinfogage->Release();
		g_pD3DTextureEnemyinfogage = NULL;
	}

	if (g_pD3DVtxBuffEnemyinfogage != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEnemyinfogage->Release();
		g_pD3DVtxBuffEnemyinfogage = NULL;
	}

	// 敵のライフゲージ

	if (g_pD3DTextureEnemyinfogage != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemylife->Release();
		g_pD3DTextureEnemylife = NULL;
	}

	if (g_pD3DVtxBuffEnemyinfogage != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEnemylife->Release();
		g_pD3DVtxBuffEnemylife = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyinfo(void)
{
#if 0
	if (g_nCountAppearEnemyinfogage >= COUNT_APPERA_ENEMYINFOICON)
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
void DrawEnemyinfo(void)
{
	BOSS *boss = GetBoss(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float bossHPhiritsu;		// モデルの?の比率
	float bossHPDraw;			// 表示するHPバーの長さ

	// ライフの枠を描画
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemyinfowaku, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureEnemyinfowaku);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


	// エネミーアイコン(情報バー)描画
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemyinfogage, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureEnemyinfogage);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}

	// エネミーのライフゲージを描画
	bossHPhiritsu = (boss->boss_life) / (boss->boss_maxlife);
	// 表示するバーの長さ
	bossHPDraw = (bossHPhiritsu * ENEMYLIFEGAGE_WIDTH);
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemylife->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X, ENEMYLIFEGAGE_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X + bossHPDraw, ENEMYLIFEGAGE_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X, ENEMYLIFEGAGE_POS_Y + ENEMYLIFEGAGE_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X + bossHPDraw, ENEMYLIFEGAGE_POS_Y + ENEMYLIFEGAGE_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffEnemylife->Unlock();
	}
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemylife, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureEnemylife);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemyinfo(LPDIRECT3DDEVICE9 pDevice)
{


	// エネミー情報の枠部分のバッファ作成
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_2D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&g_pD3DVtxBuffEnemyinfowaku,	// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_pD3DVtxBuffEnemyinfowaku->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(ENEMYINFOWAKU_POS_X, ENEMYINFOWAKU_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(ENEMYINFOWAKU_POS_X + ENEMYINFOWAKU_WIDTH, ENEMYINFOWAKU_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(ENEMYINFOWAKU_POS_X, ENEMYINFOWAKU_POS_Y + ENEMYINFOWAKU_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(ENEMYINFOWAKU_POS_X + ENEMYINFOWAKU_WIDTH, ENEMYINFOWAKU_POS_Y + ENEMYINFOWAKU_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffEnemyinfowaku->Unlock();
		}

	}
	// エネミーアイコンの頂点バッファを生成
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_2D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&g_pD3DVtxBuffEnemyinfogage,		// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_pD3DVtxBuffEnemyinfogage->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(ENEMYINFOICON_POS_X, ENEMYINFOICON_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(ENEMYINFOICON_POS_X + ENEMYINFOICON_WIDTH, ENEMYINFOICON_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(ENEMYINFOICON_POS_X, ENEMYINFOICON_POS_Y + ENEMYINFOICON_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(ENEMYINFOICON_POS_X + ENEMYINFOICON_WIDTH, ENEMYINFOICON_POS_Y + ENEMYINFOICON_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffEnemyinfogage->Unlock();
		}
	}

	// エネミーライフゲージの頂点バッファを生成
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_2D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&g_pD3DVtxBuffEnemylife,		// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_pD3DVtxBuffEnemylife->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X, ENEMYLIFEGAGE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X + ENEMYLIFEGAGE_WIDTH, ENEMYLIFEGAGE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X, ENEMYLIFEGAGE_POS_Y + ENEMYLIFEGAGE_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X + ENEMYLIFEGAGE_WIDTH, ENEMYLIFEGAGE_POS_Y + ENEMYLIFEGAGE_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffEnemylife->Unlock();
		}
	}



	return S_OK;
}

//=============================================================================
// 頂点の作成
//=============================================================================
void SetColorEnemyinfo(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemyinfowaku->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEnemyinfowaku->Unlock();
	}

}

