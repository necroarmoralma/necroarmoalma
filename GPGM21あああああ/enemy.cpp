//=============================================================================
//
// モデル処理 [enemy.cpp]
//  Author : HALゲーム学科二年生課程1年　山本壮将
// 
//=============================================================================
#include "enemy.h"
#include "shadow.h"
#include "bossbullet.h"
#include "model.h"
#include "enemycontrol.h"
#include "map.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ENEMY_AIRPLANE		"data/MODEL/enemypod.x"	// 読み込むモデル名
#define	VALUE_MOVE_ENEMY	(0.80f)						// 移動速度
#define	RATE_MOVE_ENEMY		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_ENEMY	(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_ENEMY	(0.20f)						// 回転慣性係数
#define	ENEMY_BULLET_SIZEX		(20.0f)						// 弾の大きさ基準値X
#define ENEMY_BULLET_SIZEY		(20.0f)						// 弾の大きさ基準値Y
#define SPEEDSETTING_ENEMY	()						// ボスがXZ平面上で回転するときの調整
#define ENEMYSPEED			(1.1f)
#define ENEMYMODE			(1.57f)					// 動作切り替えが行われる回転値
// 各モードの弾の大きさ　Xが横方向　Yが縦方向
//　DEBIRUの弾
#define ENEMYBULLET_1_SIZE_X	(10.0f)
#define ENEMYBULLET_1_SIZE_Y	(10.0f)

#define ENEMY_SHOTACT			(1*60)		// 秒数×FPS

#define VALUE_MOVE_ENEMY		(0.5f)
#define ENEMYKANKAKUPLUS		(4.0f)// 敵の間隔をこれだけあげる

// 試験管
#define SHIKENKAN_NINZU			(3)			// 試験管の人数

// 方向転換(指定に使う
#define	HIDARI	(1.57f)
#define	MIGI	(-1.57f)
#define	UE		(0.0f)
#define	SHITA	(3.57f)


// 仮置き
#define ENEMY_HANKEI	(20.0f)			//	エネミーの半径


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CheckEnemypos(D3DXVECTOR3 pos, int enemyno);
void enemy_RaypickTomap(void);
void move_change(void);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	TextureEnemy;			// テクスチャ読み込み場所
LPD3DXMESH			MeshEnemy;			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		BuffMatEnemy;		// メッシュのマテリアル情報を格納
DWORD				NumMatEnemy;				// 属性情報の総数
												
int					enemynidxShadow;				// 影ID
float				enemysizeShadow;				// 影のサイズ
D3DXCOLOR			enemycolShadow;				// 影の色
D3DXVECTOR3			ENEMYBASEPOS(0.0f, 0.0f, 5.0f);
ENEMY				enemyWk[ENEMYMAX];					// モデル構造体(モデルは１）
float				enemyActtime;				// ボスが行動する感覚



int no = 0;
//=============================================================================
// 敵の初期化
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 rotCamera;

	// モデルの初期化
	MeshEnemy = NULL;
	BuffMatEnemy = NULL;
	NumMatEnemy = NULL;

	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(ENEMY_AIRPLANE,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&BuffMatEnemy,
		NULL,
		&NumMatEnemy,
		&MeshEnemy)))
	{
		return E_FAIL;
	}

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&g_pD3DTextureEnemy);	// 読み込むメモリー
#endif

	// 構造体全ての初期化を行う

	for (int no=0; no < ENEMYMAX; no++)
	{
		
		// 影の生成
		enemynidxShadow = CreateShadow(enemyWk[no].status.pos, 25.0f, 25.0f);

		// 初期化
		enemyWk[no].status.BuffMatModel = NULL;
		enemyWk[no].status.NumMatModel = NULL;
		enemyWk[no].status.MeshModel = NULL;

		// 最初に読み込んだモデルを適用
		enemyWk[no].status.BuffMatModel = BuffMatEnemy;
		enemyWk[no].status.NumMatModel = NumMatEnemy;
		enemyWk[no].status.MeshModel = MeshEnemy;

		enemysizeShadow = 25.0f;
		enemycolShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		enemyWk[no].use = false;
		enemyWk[no].acttime = ENEMY_SHOTACT;
	}
	return S_OK;
}




//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{

	for (int no = 0; no < ENEMYMAX; no++)
	{
		if (enemyWk[no].use == true)
		{
			if (enemyWk[no].status.TextureModel != NULL)
			{// テクスチャの開放
				enemyWk[no].status.TextureModel->Release();
				enemyWk[no].status.TextureModel = NULL;
			}

			if (enemyWk[no].status.MeshModel != NULL)
			{// メッシュの開放
				enemyWk[no].status.MeshModel->Release();
				enemyWk[no].status.MeshModel = NULL;
			}

			if (enemyWk[no].status.BuffMatModel != NULL)
			{// マテリアルの開放
				enemyWk[no].status.BuffMatModel->Release();
				enemyWk[no].status.BuffMatModel = NULL;
			}
		}
	}
}

//*****************************************************************************
// 消去処理
//*****************************************************************************
void DeleatEnemy(int no)
{
		enemyWk[no].use = false;
	
}



//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	for (int no=0; no < ENEMYMAX; no++)
	{
		if (enemyWk[no].use == true)
		{
			D3DXVECTOR3 rotCamera;
			ENEMY *enemy = &enemyWk[0];
			MODEL *model = GetModel(0);
			float fDiffRotY;
			D3DXVECTOR3 SubposEnemytoModel;
			float rotcheckEtoM;


			if (GetKeyboardTrigger(DIK_Z))
			{
				if (enemyWk[no].warning == false)
				{
					enemyWk[no].warning = true;
				}

				else
				{
					enemyWk[no].warning = false;
				}
			}

			// 警戒状態ならプレイヤーの方へ向かう
			if (enemyWk[no].warning == true)
			{
				// 目標-自分
				rotcheckEtoM = atan2f((model->pos.x - enemyWk[no].status.pos.x), (model->pos.z - enemyWk[no].status.pos.z)) + D3DX_PI;
				enemyWk[no].status.rot.y = rotcheckEtoM;	// プレイヤーの方向を向かせる
			}

			enemy_RaypickTomap();
			move_change();

			// 行動
			// 動作出来る状態か
			enemyWk[no].acttime--;		//　デクリメントでいいかも？1フレームで1減らした

			if (enemyWk[no].acttime <= 0.0f)

			// 重複チェック
			{	// 0なら実行する処理
				// 弾の発射
			//	SetEnemybullet(enemyWk[no].status.pos, ENEMYBULLET_1_SIZE_X, ENEMYBULLET_1_SIZE_Y, D3DXCOLOR(1.0f, 0.7f, 0.8f, 0.75f), enemyWk[no].status.rot.y);
				enemyWk[no].acttime = ENEMYACT;
			}



			// 向いている方向へ移動する

			// 移動量の決定
			enemyWk[no].status.move.x += sinf(D3DX_PI + enemyWk[no].status.rot.y) * VALUE_MOVE_ENEMY;
			enemyWk[no].status.move.z += cosf(D3DX_PI + enemyWk[no].status.rot.y) * VALUE_MOVE_ENEMY;
			CheckEnemypos(enemyWk[no].status.pos, no);

			enemyWk[no].status.pos.x += enemyWk[no].status.move.x;
			enemyWk[no].status.pos.z += enemyWk[no].status.move.z;

			enemyWk[no].status.move.x += (0.0f - enemyWk[no].status.move.x) * RATE_MOVE_MODEL;
			enemyWk[no].status.move.z += (0.0f - enemyWk[no].status.move.z) * RATE_MOVE_MODEL;

			
			// 影の位置設定
			SetPositionShadow(enemynidxShadow, D3DXVECTOR3(enemyWk[no].status.pos.x, 0.1f, enemyWk[no].status.pos.z));

			SetVertexShadow(enemynidxShadow, enemysizeShadow, enemysizeShadow);
			SetColorShadow(enemynidxShadow, enemycolShadow);



			//　向きの制御
			//enemyWk[no].status.rot.y = MIGI;

			// 回転制御
			enemyWk[no].movesetting += 0.01f;

			// 行動カウントを減らす
			enemyWk[no].acttime--;
		}
	}
	
}
 
//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	for (int no = 0; no < ENEMYMAX; no++)
	{
		if (enemyWk[no].use == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&enemyWk[no].status.World);


			// スケールを反映
			D3DXMatrixScaling(&mtxScl, enemyWk[no].status.scl.x, enemyWk[no].status.scl.y, enemyWk[no].status.scl.z);
			D3DXMatrixMultiply(&enemyWk[no].status.World, &enemyWk[no].status.World, &mtxScl);


			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, enemyWk[no].status.rot.y, enemyWk[no].status.rot.x, enemyWk[no].status.rot.z);
			D3DXMatrixMultiply(&enemyWk[no].status.World, &enemyWk[no].status.World, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, enemyWk[no].status.pos.x, enemyWk[no].status.pos.y, enemyWk[no].status.pos.z);
			D3DXMatrixMultiply(&enemyWk[no].status.World, &enemyWk[no].status.World, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &enemyWk[no].status.World);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)enemyWk[no].status.BuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)enemyWk[no].status.NumMatModel; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, enemyWk[no].status.TextureModel);

				// 描画
				enemyWk[no].status.MeshModel->DrawSubset(nCntMat);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionEnemy(int no)
{
	ENEMY *enemy = &enemyWk[0];
	return enemyWk[no].status.pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationEnemy(int no)
{
	ENEMY *enemy = &enemyWk[no];
	return enemyWk[no].status.rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestEnemy(int no)
{
	ENEMY *enemy = &enemyWk[no];
	return enemyWk[no].status.rotDest;
}

//*****************************************************************************
// ゲット関数
//*****************************************************************************
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}

//******************************************************************************
// 関数名:	HRESULT CreateEnemy(void)
// 引数:	なし
// 戻り値:	正常終了　HRESULT型のS_OK
// 説明:	敵を配置
//******************************************************************************
void CreateEnemy(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int createno;	// 設定する構造体の番号

	for (int no = 0; no < ENEMYMAX; no++)
	{
		if (enemyWk[no].use == false)		// 未使用みつけたら
		{
			enemyWk[no].use = true;
			// 状態の初期化
			enemyWk[no].warning = false;	// 警戒状態ではない
			// HPの設定
			enemyWk[no].enemy_maxlife = ENEMYLIFE;
			enemyWk[no].enemy_life = enemyWk[no].enemy_maxlife;



			enemyWk[no].status.pos = pos;
			enemyWk[no].status.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemyWk[no].status.puremove = enemyWk[no].status.move;
			enemyWk[no].status.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemyWk[no].status.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemyWk[no].status.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			enemyWk[no].acttime = ENEMYACT;


			// 動作制御に必要な値を設定
			enemyWk[no].movesetting = 0.0f;
			enemyWk[no].movemode = SHOT;
			break;
		}
	}
}

//******************************************************************************
// 関数名:	void CheckEnemypos(D3DXVECTOR3 pos,int no)
// 引数:	D3DXVECTOR3 pos,int no
// 戻り値:	なし
// 説明:	敵同士の間隔をいっていにたもつ
//******************************************************************************
void CheckEnemypos(D3DXVECTOR3 pos, int enemyno)
{
	ENEMYLENGTH *enemylength = GetEnemylength(0);
	float lengthcheck;	// ここに距離を格納

	lengthcheck = (enemylength->enemycenter * 2);

	for(int no = 0; no < ENEMYMAX; no++)
	{
		if(enemyWk[no].use == true && no != enemyno)
		{
			if(((enemyWk[no].status.pos.x - pos.x)*(enemyWk[no].status.pos.x - pos.x)) + ((enemyWk[no].status.pos.z - pos.z)*(enemyWk[no].status.pos.z - pos.z))
				<= ((lengthcheck)*(lengthcheck)))
			{
				enemyWk[no].status.move.x = 0.0f;
				enemyWk[no].status.move.z = 0.0f;
			}
		}
	}
}


//******************************************************************************
//	関数名:	void SetShikenkan(void)
//	引数:	んばし
//	戻り値:	なし
//	説明:	試験管の配置
//*******************************************************************************
void SetShikenkan(void)
{
	ENEMYLENGTH *length = GetEnemylength(0);
	MODEL *model = GetModel(0);
	
	//int pos = (rand() % 10);
	//int pop = (rand() % 4 + 1);

		CreateEnemy(D3DXVECTOR3(-100.0f,0.0f,100.0f));
		CreateEnemy(D3DXVECTOR3(0.0f,0.0f,100.0f));
		CreateEnemy(D3DXVECTOR3(100.0f,0.0f,100.0f));
	
		// 試験管の初期向き
		enemyWk[0].status.rot.y = MIGI;
		enemyWk[1].status.rot.y = SHITA;
		enemyWk[2].status.rot.y = UE;
}


//*****************************************************************************
// 関数名:	void model_RaypickToMap(int no)
// 引数:	int no
// 戻り値:	無し
// 説明:	自機とマップとのレイピック、引数はレイを飛ばす方向
//*****************************************************************************
void enemy_RaypickTomap(void)
{


	MAP *map = GetMap(0);

	for (int no = 0; no < SHIKENKAN_NINZU; no++)
	{
		// 便利関数と引数の説明(自分用)
		// 下へ飛ばす
		D3DXIntersect(
			map->MeshMap,				// 当たり判定を取りたいメッシュ　型はLPD3DXBASEMESH(LPD3DXMESHもOK?)
			&D3DXVECTOR3(enemyWk[no].status.pos.x, enemyWk[no].status.pos.y + 0.0f, enemyWk[no].status.pos.z),				// レイの視点座標を設定(プレイヤーの座標とかね) 型はD3DXVECTOR3
			&D3DXVECTOR3(0, -1, 0),		// レイの方向を設定 型はD3DXVECTOR3 XYZ 1で正方向-1で負の方向
			&enemyWk[no].status.tomapDown,				// 衝突判定 型はBOOL(boolではない) 衝突していたらTRUE当たっていなければFALSE
			NULL,						// 上記の判定がTRUEの場合レイの視点に最も近い面のインデックス値へのポインタ
			NULL,						// 重心ヒット座標へのポインタその1レイが当たったメッシュの場所
			NULL,						// 重心ヒット座標へのポインタその2こちらも同じくメッシュの当たった場所
			&enemyWk[no].status.D_RtoMdistance,		// レイからメッシュまでの距離はいくつ
			NULL,						// D3DXINTERSECTINFO構造体の配列を格納するID3DXBufferオブジェクトへのポインタ
			NULL						// ppAllHits配列内のエントリ数を格納するポインタ、型はDWORD
		);


		// レイピック(モデルから上に飛ばしたレイとマップ)
		D3DXIntersect(map->MeshMap, &enemyWk[no].status.pos, &D3DXVECTOR3(0, 1, 0), &enemyWk[no].status.tomapUp, NULL, NULL, NULL,
			&enemyWk[no].status.U_RtoMdistance, NULL, NULL);

		// レイピック(右に飛ばしたレイとマップ)
		D3DXIntersect(map->MeshMap, &enemyWk[no].status.pos, &D3DXVECTOR3(1, 0, 0), &enemyWk[no].status.tomapRight, NULL, NULL, NULL,
			&enemyWk[no].status.R_RtoMdistance, NULL, NULL);

		// レイピック(左に飛ばしたレイとマップ)
		D3DXIntersect(map->MeshMap, &enemyWk[no].status.pos, &D3DXVECTOR3(-1, 0, 0), &enemyWk[no].status.tomapLeft, NULL, NULL, NULL,
			&enemyWk[no].status.L_RtoMdistance, NULL, NULL);

		// レイピック(前方方向に飛ばしたレイとマップ)
		D3DXIntersect(map->MeshMap, &enemyWk[no].status.pos, &D3DXVECTOR3(0, 0, 1), &enemyWk[no].status.tomapFront, NULL, NULL, NULL,
			&enemyWk[no].status.F_RtoMdistance, NULL, NULL);

		// レイピック(後方高校に飛ばしたレイとマップ)
		D3DXIntersect(map->MeshMap, &enemyWk[no].status.pos, &D3DXVECTOR3(0, 0, -1), &enemyWk[no].status.tomapBack, NULL, NULL, NULL,
			&enemyWk[no].status.B_RtoMdistance, NULL, NULL);
	}
}


//**********************************************************************************
// 関数名:	void move_change(void)
// 戻り値:	なし
// 引数:	なし
// 説明:	壁があるなら方向を変えてしまう
//**********************************************************************************
void move_change(void)
{
	D3DXVECTOR3 hosei;
	D3DXVECTOR3 rotCamera;
	float		escapmodellmove = 1.0f;		// 値を補正させるため
											// カメラの向き取得

	// テスト壁にそってとめてしまう
	// 壁とのレイを半径にすればいい
	// レイが半径以下になっている場合半径になるよう移動させてあげればいい

	for (int no = 0; no < SHIKENKAN_NINZU; no++)
	{
		// 右方向接触
		if (enemyWk[no].status.R_RtoMdistance <= ENEMY_HANKEI)
		{
			// 左
			enemyWk[no].status.rot.y = HIDARI;
		}

		// 左接触
		else if (enemyWk[no].status.L_RtoMdistance <= ENEMY_HANKEI)
		{	// 右
			enemyWk[no].status.rot.y = MIGI;
		}

		// shita接触
		if (enemyWk[no].status.F_RtoMdistance <= ENEMY_HANKEI)
		{	// 後ろ
			enemyWk[no].status.rot.y = UE;
		}
		//ue接触
		else if (enemyWk[no].status.B_RtoMdistance <= ENEMY_HANKEI)
		{	// 前
			enemyWk[no].status.rot.y = SHITA;
		}

	}
	/// もしジャンプなどを実装する際に
	/// 地面へのめり込みを回避
//if (model->D_RtoMdistance <= model->center)
//{
//	hosei.y = model->center - model->D_RtoMdistance;
//	model->pos.y += hosei.y;
//}




//	model->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}