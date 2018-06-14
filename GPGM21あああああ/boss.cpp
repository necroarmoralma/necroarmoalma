//=============================================================================
//
// モデル処理 [boss.cpp]
//  Author : HALゲーム学科二年生課程1年　山本壮将
// 
//=============================================================================
#include "boss.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"
#include "bossbullet.h"
#include "meshfield.h"
#include "model.h"
#include "bulletmk2.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BOSS_AIRPLANE		"data/MODEL/student.x"	// 読み込むモデル名
#define	VALUE_MOVE_BOSS	(0.80f)						// 移動速度
#define	RATE_MOVE_BOSS		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_BOSS	(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_BOSS	(0.20f)						// 回転慣性係数
#define	BULLET_SIZEX		(20.0f)						// 弾の大きさ基準値X
#define BULLET_SIZEY		(20.0f)						// 弾の大きさ基準値Y
#define SPEEDSETTING_BOSS	()						// ボスがXZ平面上で回転するときの調整
#define BOSSLENGTH			(800)					// マップ中心点からボスの距離
#define BOSSSPEED			(1.1f)
#define NEXTMOVE			(1.57f)					// 動作切り替えが行われる回転値


// 各モードの弾の大きさ　Xが横方向　Yが縦方向
//　DEBIRUの弾
#define DEBIRUBULLET_1_SIZE_X	(100.0f)
#define DEBIRUBULLET_1_SIZE_Y	(100.0f)

// AHIRUの弾
#define AHIRUBULLET_1_SIZE_X	(10.0f)
#define AHIRUBULLET_1_SIZE_Y	(10.0f)

#define AHIRUBULLET_2_SIZE_X	(5.0f)
#define AHIRUBULLET_2_SIZE_Y	(10.0f)

#define AHIRUBULLET_3_SIZE_X	(10.0f)
#define AHIRUBULLET_3_SIZE_Y	(10.0f)

// HENANOの弾
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void bossshot(void);
void bossbeam(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureBoss;			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshBoss;			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatBoss;		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatBoss;				// 属性情報の総数
												/*
												D3DXMATRIX			boss->World;			// ワールドマトリックス
												D3DXVECTOR3			boss->pos;					// 現在の位置
												D3DXVECTOR3			boss->move;				// 移動量
												D3DXVECTOR3			boss->rot;					// 現在の向き
												D3DXVECTOR3			boss->rotDest;				// 目的の向き
												*/

int					bossnidxShadow;				// 影ID
float				bosssizeShadow;				// 影のサイズ
D3DXCOLOR			bosscolShadow;				// 影の色
D3DXVECTOR3			BOSSBASEPOS(0.0f,0.0f,5.0f);
BOSS				bossWk[1];					// モデル構造体(モデルは１）
float				bossActtime;				// ボスが行動する感覚

int					actcheck;					// てすと
float				viewrot_y;					// テスト(見た目上の回転)
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS *boss = &bossWk[0];
	D3DXVECTOR3 rotCamera;
	
	// HPの設定
	boss->boss_maxlife = BOSSLIFE;
	boss->boss_life = boss->boss_maxlife;

	g_pD3DTextureBoss = NULL;
	g_pD3DXMeshBoss = NULL;
	g_pD3DXBuffMatBoss = NULL;

	boss->pos = BOSSBASEPOS;
	boss->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	boss->puremove = boss->move;
	boss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	boss->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	boss->scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	boss->acttime = BOSSACT;


	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(BOSS_AIRPLANE,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pD3DXBuffMatBoss,
		NULL,
		&g_nNumMatBoss,
		&g_pD3DXMeshBoss)))
	{
		return E_FAIL;
	}

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&g_pD3DTextureBoss);	// 読み込むメモリー
#endif


								// 影の生成
	bossnidxShadow = CreateShadow(boss->pos, 25.0f, 25.0f);

	bosssizeShadow = 25.0f;
	bosscolShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	// テストviewrot_yを設定(見た目だけ回転させる)
	viewrot_y = boss->rot.y;

	// 動作制御に必要な値を設定
	boss->movesetting = 0.0f;
	boss->movemode = DEBIRU;		// 最初はあくま？が正面を向いているため
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBoss(void)
{
	if (g_pD3DTextureBoss != NULL)
	{// テクスチャの開放
		g_pD3DTextureBoss->Release();
		g_pD3DTextureBoss = NULL;
	}

	if (g_pD3DXMeshBoss != NULL)
	{// メッシュの開放
		g_pD3DXMeshBoss->Release();
		g_pD3DXMeshBoss = NULL;
	}

	if (g_pD3DXBuffMatBoss != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatBoss->Release();
		g_pD3DXBuffMatBoss = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBoss(void)
{
	D3DXVECTOR3 rotCamera;
	BOSS *boss = &bossWk[0];
	MODEL *model = GetModel(0);
	float fDiffRotY;
	D3DXVECTOR3 SubposBosstoModel;
	float rotcheckBtoM;


	// カメラの向き取得
	//rotCamera = GetRotCamera();
	
	//++自機に向かせる
	// 目標-自分
	rotcheckBtoM = atan2f((model->pos.x - boss->pos.x),(model->pos.z - boss->pos.z)) + 3.14;
	
	boss->rockon = rotcheckBtoM;	// プレイヤーの方向を向かせる
	//boss->rot.z = rotcheckBtoM;
	// 上下
	// 目標-自分（（ボスから見て前方に自機が存在する場合)
	//rotcheckBtoM = atan2f((model->pos.y - boss->pos.y), (model->pos.z - boss->pos.z)) + 3.14;
	//boss->rot.x = -rotcheckBtoM;	// プレイヤーの方向を向かせる
	
	// 行動
	// 動作出来る状態か
	boss->acttime -= 1.0f;		//　デクリメントでいいかも？1フレームで1減らしたい


	
		//boss->pos.x =   (sinf(boss->kaiten) * BOSSSPEED *BOSSLENGTH);				// ここの31.5fとかはえんしゅうみたいね
		////boss->pos.y = model->pos.y;
		//boss->pos.z =   (cosf(boss->kaiten) *BOSSSPEED *BOSSLENGTH);			// xsinかくど + zcosかくど sin(10)
		//
		//

	// 影の位置設定
	SetPositionShadow(bossnidxShadow, D3DXVECTOR3(boss->pos.x, 0.1f, boss->pos.z));

	SetVertexShadow(bossnidxShadow, bosssizeShadow, bosssizeShadow);
	SetColorShadow(bossnidxShadow, bosscolShadow);

	PrintDebugProc("[rotDest.yいくつ:(%f) ]\n", boss->rotDest.y);


	//回転テスト
	boss->rot.y += 0.01f;
	
	// 回転制御
	boss->movesetting += 0.01f;
	// NEXTMOVEに到達していたらモード切替
	if (boss->movesetting >= NEXTMOVE)
	{
		// 次のモードへ移動
		if (boss->movemode == DEBIRU)
		{
			boss->movemode = AHIRU;
			boss->movesetting = 0.0f;
		}

		else if (boss->movemode == AHIRU)
		{
			boss->movemode = HENANO;
			boss->movesetting = 0.0f;
		}

		else if (boss->movemode == HENANO)
		{
			boss->movemode = MEKA;
			boss->movesetting = 0.0f;
		}

		else if (boss->movemode == MEKA)
		{
			boss->movemode = DEBIRU;
			boss->movesetting = 0.0f;
		}

		PrintDebugProc("bosscubeposいくつ:(%f)(%f)(%f) ]\n", boss->pos.x, boss->pos.y, boss->pos.z);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	BOSS *boss = &bossWk[0];

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&boss->World);


	// スケールを反映
	D3DXMatrixScaling(&mtxScl, boss->scl.x, boss->scl.y, boss->scl.z);
	D3DXMatrixMultiply(&boss->World, &boss->World, &mtxScl);


	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, boss->rot.y, boss->rot.x, boss->rot.z);
	D3DXMatrixMultiply(&boss->World, &boss->World, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, boss->pos.x, boss->pos.y, boss->pos.z);
	D3DXMatrixMultiply(&boss->World, &boss->World, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &boss->World);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatBoss->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatBoss; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureBoss);

		// 描画
		g_pD3DXMeshBoss->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionBoss(void)
{
	BOSS *boss = &bossWk[0];
	return boss->pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationBoss(void)
{
	BOSS *boss = &bossWk[0];
	return boss->rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestBoss(void)
{
	BOSS *boss = &bossWk[0];
	return boss->rotDest;
}

//*****************************************************************************
// ゲット関数
//*****************************************************************************
BOSS *GetBoss(int no)
{
	return(&bossWk[0]);
}

//*****************************************************************************
// ボスの行動まとめ
//*****************************************************************************
void bossshot(void)
{
	BOSS *boss = &bossWk[0];
	// 玉発射
	D3DXVECTOR3 pos = boss->pos;
	SetBossbullet(boss->pos, 20.0f, 20.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), boss->rockon);
	
	
	boss->acttime = BOSSACT;
}

//*******************************
// レーザー
//*******************************
void bossbeam(void)
{
	BOSS *boss = &bossWk[0];
			D3DXVECTOR3 pos = boss->pos;
			boss->rot.y = 0;
			SetBossbullet(boss->pos, 20.0f, 60.0f, D3DXCOLOR(0.6f, 1.0f, 1.0f, 1.0f),boss->rot.y);
			boss->acttime = BOSSACT;
	
}