//=============================================================================
//
// タイトル画面処理 [title.cpp]
//  Author : HALゲーム学科二年生課程1年　山本壮将
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "shadow.h"

#include "light.h"
#include "camera.h"
// モデル関連
#include "model.h"
#include "modelarm.h"
#include "modelbooster.h"
#include "titlerogo.h"
#include "bulletmk2.h"
#include "wheel.h"

#include "map.h"
#include "setting.h"
#include "score.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE		"data/TEXTURE/title.png"		// 読み込むテクスチャファイル名




//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);
void SetColorTitleLogo(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTitle = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleLogo = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTitleLogo = NULL;	// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureStart = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffStart = NULL;		// 頂点バッファインターフェースへのポインタ
int						g_nCountAppearStart = 0;		//
float					g_fAlphaLogo = 0.0f;			//
int						g_nCountDisp = 0;				//
bool					g_bDispStart = false;			//
int						g_nConutDemo = 0;				//

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	GAMEPADX *gamepad = GetPADX(0);
	// ゲームパッドの状態
	XINPUT_STATE state;
	XINPUT_KEYSTROKE keystroke;
	// 念のためスティックの入力情報を毎回初期化
	// キーボードのみの場合変な値で初期化されて誤作動が起きたため、必ず初期化する事
	state.Gamepad.sThumbLY = 0;
	state.Gamepad.sThumbLX = 0;

	XInputGetState(0, &state);
	XInputGetKeystroke(0, 0, &keystroke);

	// パッド入力情報
	gamepad->use = false;

	g_nCountAppearStart = 0;
	g_fAlphaLogo = 0.0f;
	g_nCountDisp = 0;
	g_bDispStart = false;
	g_nConutDemo = 0;

	// 頂点情報の作成
	MakeVertexTitle(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_TITLE,				// ファイルの名前
								&g_pD3DTextureTitle);		// 読み込むメモリー

	// ライト初期化
	InitLight();
	// カメラの初期化
	InitCamera();

	// 影の初期化
	InitShadow();

	// タイトルの初期化
//	InitTitlelogo();

	// モデル
	// ボディ(基準)
	InitModel(model_title);
	
	// ホイール
	InitWheel();
	// ブースター
	InitModelBooster();

	//タマ
	InitBulletmk2();

	InitTitlelogo();
	
	// マップ初期化
	InitMap();


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	if(g_pD3DTextureTitle != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitle->Release();
		g_pD3DTextureTitle = NULL;
	}

	if(g_pD3DVtxBuffTitle != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffTitle->Release();
		g_pD3DVtxBuffTitle = NULL;
	}

	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	// モデルの終了処理
	UninitModel();
	UninitWheel();
	UninitModelBooster();

	// マップの終了処理
	UninitMap();

	// タイトルロゴ終了処理
	UninitTitlelogo();

	// 弾の終了処理
	UninitBulletmk2();

	// モデル終了
	UninitModel();

	
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	GAMEPADX *gamepad = GetPADX(0);
	// ゲームパッドの状態
	XINPUT_STATE state;
	XINPUT_KEYSTROKE keystroke;
	// 念のためスティックの入力情報を毎回初期化
	// キーボードのみの場合変な値で初期化されて誤作動が起きたため、必ず初期化する事
	state.Gamepad.sThumbLY = 0;
	state.Gamepad.sThumbLX = 0;

	XInputGetState(0, &state);
	XInputGetKeystroke(0, 0, &keystroke);

#if 0
	if(g_nCountAppearStart >= COUNT_APPERA_START)
	{
		g_nConutDemo++;
		if(g_nConutDemo > COUNT_WAIT_DEMO)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
#endif




	// カメラ更新
	UpdateCamera();
	// モデルの更新
	UpdateModel(model_title);
	UpdateWheel(model_title);
	UpdateModelBooster();

	// 弾の更新
	UpdateBulletmk2();

	// タイトルロゴ更新
	UpdateTitlelogo();


	// マップの更新
	UpdateMap();


	// フェード
	// スタートボタン
	if (keystroke.Flags & XINPUT_KEYSTROKE_KEYDOWN && keystroke.VirtualKey == VK_PAD_START)
	{
		gamepad->use = true;	// ゲームパッドで操作するとみなす
		InitGame();
		SetFade(FADE_OUT);
		

	}
	else if(GetKeyboardTrigger(DIK_RETURN))
	{
		if(g_nCountAppearStart == 0)
		{// タイトル登場スキップ
			InitGame();
			SetFade(FADE_OUT);
		}
		else
		{// ゲームへ
			InitGame();
			SetFade(FADE_OUT);
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitle);

	// ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



	// カメラの設定
	SetCamera();


	// マップの描画
	DrawMap();
	// 弾の描画
	DrawBulletmk2();


	// モデル処理の描画
	DrawModel(model_game);
	DrawWheel();
	//DrawModelBooster();

	// タイトルロゴの描画
	DrawTitlelogo();


}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_2D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffTitle,		// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffTitle->Unlock();
	}

	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_2D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffTitleLogo,	// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	//{//頂点バッファの中身を埋める
	//	VERTEX_2D *pVtx;

	//	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	//	g_pD3DVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	//	// 頂点座標の設定
	//	pVtx[0].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y, 0.0f);
	//	pVtx[1].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X + TITLE_LOGO_WIDTH, TITLE_LOGO_POS_Y, 0.0f);
	//	pVtx[2].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y + TITLE_LOGO_HEIGHT, 0.0f);
	//	pVtx[3].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X + TITLE_LOGO_WIDTH, TITLE_LOGO_POS_Y + TITLE_LOGO_HEIGHT, 0.0f);

	//	// テクスチャのパースペクティブコレクト用
	//	pVtx[0].rhw =
	//	pVtx[1].rhw =
	//	pVtx[2].rhw =
	//	pVtx[3].rhw = 1.0f;

	//	// 反射光の設定
	//	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
	//	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
	//	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
	//	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);

	//	// テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//	// 頂点データをアンロックする
	//	g_pD3DVtxBuffTitleLogo->Unlock();
	//}


	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_2D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffStart,		// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	//{//頂点バッファの中身を埋める
	//	VERTEX_2D *pVtx;

	//	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	//	g_pD3DVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

	//	// 頂点座標の設定
	//	pVtx[0].vtx = D3DXVECTOR3(START_POS_X, START_POS_Y, 0.0f);
	//	pVtx[1].vtx = D3DXVECTOR3(START_POS_X + START_WIDTH, START_POS_Y, 0.0f);
	//	pVtx[2].vtx = D3DXVECTOR3(START_POS_X, START_POS_Y + START_HEIGHT, 0.0f);
	//	pVtx[3].vtx = D3DXVECTOR3(START_POS_X + START_WIDTH, START_POS_Y + START_HEIGHT, 0.0f);

	//	// テクスチャのパースペクティブコレクト用
	//	pVtx[0].rhw =
	//	pVtx[1].rhw =
	//	pVtx[2].rhw =
	//	pVtx[3].rhw = 1.0f;

	//	// 反射光の設定
	//	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	// テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//	// 頂点データをアンロックする
	//	g_pD3DVtxBuffStart->Unlock();
	//}

	return S_OK;
}

//=============================================================================
// 頂点の作成
//=============================================================================
void SetColorTitleLogo(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);

		// 頂点データをアンロックする
		g_pD3DVtxBuffTitleLogo->Unlock();
	}

}

