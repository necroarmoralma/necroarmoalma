//**************************************************************************************
// ファイル名:	unitWk[no].cpp
// 説明:		敵関連のプログラム
// 作成日時:	2017/11/09
// 作成者:		山本 壮将
//**************************************************************************************


//**************************************************************************************
// インクルードファイル
//**************************************************************************************
#include "unit.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"
#include "bulletmk2.h"
#include "meshfield.h"
#include "model.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	UNIT_AIRPLANE			// 読み込むモデル名
#define	VALUE_MOVE_UNIT	(0.80f)						// 移動速度
#define	RATE_MOVE_UNIT		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_UNIT	(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_UNIT	(0.20f)						// 回転慣性係数
#define	BULLET_SIZEX		(20.0f)						// 弾の大きさ基準値X
#define BULLET_SIZEY		(20.0f)						// 弾の大きさ基準値Y
#define UNIT_MAX			(1)							// 展開するユニットの数
#define KAITEN_LONG				(60.5f)							// 回転の大きさ
#define KAITEN_SPEED			(D3DX_PI * 0.03f)						// 回転速度


//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	UNIT_TE
} UNITTEX;

typedef enum
{
	UE = 0,
	MIGIUE,
	MIGI,
	MIGISHITA,
	SHITA,
	HIDARISHITA,
	HIDARI,
	HIDARIUE,
	MUKI_MAX
} MUKI;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

DWORD				g_nNumMatUnit;				// 属性情報の総数
UNIT				unitWk[UNIT_MAX];					// モデル構造体
int					haibi;

// 各ファイルの場所
char *UNITFileName[] =
{
	"data/MODEL/bitmodel.x",
	"data/MODEL/ahiru.x",
};
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUnit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	UNIT *unit = &unitWk[0];
	MODEL *model = GetModel(0);
	D3DXVECTOR3 rotCamera;

	for (int no = 0; no < UNIT_MAX; no++)
	{

		unitWk[no].Texture3D = NULL;
		unitWk[no].Mesh = NULL;
		unitWk[no].BuffMat = NULL;
		unitWk[no].use = false;
		haibi = no % BUTAI_MAX;		// 余りを利用

		switch (haibi)
		{
		case ICHI:

			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(UNITFileName[haibi],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&unitWk[no].BuffMat,
				NULL,
				&g_nNumMatUnit,
				&unitWk[no].Mesh)))
			{
				return E_FAIL;
			}
			break;

		case NI:

			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(UNITFileName[haibi],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&unitWk[no].BuffMat,
				NULL,
				&g_nNumMatUnit,
				&unitWk[no].Mesh)))
			{
				return E_FAIL;
			}
			break;

		default:			//　もしどれにも当てはまらない場合飛行機

			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(UNITFileName[0],		//どれにも当てはまらない場合0番目
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&unitWk[no].BuffMat,
				NULL,
				&g_nNumMatUnit,
				&unitWk[no].Mesh)))
			{
				return E_FAIL;
			}
			break;
		}

#if 0
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				TEXTURE_FILENAME,		// ファイルの名前
				&unitWk[no].Texture3D);	// 読み込むメモリー
#endif

		// 初期設定
			unitWk[no].kaiten = 0;
			unitWk[no].pos = model->pos;
			if (no == 3)
			{
				unitWk[no].pos = model->pos;
			}
			unitWk[no].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			unitWk[no].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			unitWk[no].rotDest = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
			unitWk[no].scl = D3DXVECTOR3(1.0f, 1.0f,1.0f);
			//SetUnit();
			

			// 影の生成
			unitWk[no].ShadowID = CreateShadow(unitWk[no].pos, 25.0f, 25.0f);

			unitWk[no].ShadowSize = 25.0f;
			unitWk[no].Shadowcol = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		}

		return S_OK;
	
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUnit(void)
{
	for (int no = 0; no < UNIT_MAX; no++)
	{
		if (unitWk[no].Texture3D != NULL)
		{// テクスチャの開放
			unitWk[no].Texture3D->Release();
			unitWk[no].Texture3D = NULL;
		}

		if (unitWk[no].Mesh != NULL)
		{// メッシュの開放
			unitWk[no].Mesh->Release();
			unitWk[no].Mesh = NULL;
		}

		if (unitWk[no].BuffMat != NULL)
		{// マテリアルの開放
			unitWk[no].BuffMat->Release();
			unitWk[no].BuffMat = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateUnit(void)
{
	MODEL *model = GetModel(0);
	D3DXVECTOR3 rotCamera;
	UNIT *unit = &unitWk[0];
//	float fDiffRotY;
	int haibi;				// ユニットはどこに配備されるのか
	int muki = 0;				// ユニットの向き
	// カメラの向き取得
	rotCamera = GetRotCamera();

	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unitWk[i].use = true)
		{
			// mukiの値決定(モデルの方角）
			if (model->rotDest.y == ue)
			{
				muki = UE;
			}
			if (model->rotDest.y == migiue)
			{
				muki = MIGIUE;
			}
			if (model->rotDest.y == migi)
			{
				muki = MIGI;
			}
			if (model->rotDest.y == migishita)
			{
				muki = MIGISHITA;
			}
			if (model->rotDest.y == shita)
			{
				muki = SHITA;
			}
			if (model->rotDest.y == hidarishita)
			{
				muki = HIDARISHITA;
			}
			if (model->rotDest.y == hidari)
			{
				muki = HIDARI;
			}
			if (model->rotDest.y == hidariue)
			{
				muki = HIDARIUE;
			}
		}
	}

	
	for (int no = 0; no < UNIT_MAX; no++)
	{
		if (unitWk[no].use == true)
		{
		


		//
		// テスト用

			unitWk[no].kaiten += KAITEN_SPEED;
			if (unitWk[no].kaiten > -D3DX_PI)
			{
				unitWk[no].kaiten -= D3DX_PI * 2.0f;
			}
		// 子機はどこのチームにいくのか決定
			haibi = no % BUTAI_MAX;		// 余りを利用
			switch (haibi)
			{
				//斜め移動
			case ICHI:
				


				unitWk[no].pos.x = model->pos.x + (sinf(unitWk[no].kaiten) * VALUE_MOVE_MODEL *KAITEN_LONG);				// ここの31.5fとかはえんしゅうみたいね
				unitWk[no].pos.y = model->pos.y;
				unitWk[no].pos.z = model->pos.z + (cosf(unitWk[no].kaiten) * VALUE_MOVE_MODEL *KAITEN_LONG);			// xsinかくど + zcosかくど sin(10)

					break;

				default :
					unitWk[no].pos.z += 1.0f;

					break;

			}
			unitWk[no].rot = model->rot;

			

			// 移動量加算
			//unitWk[no].pos.x +=  unitWk[no].move.x;//+ unitWk[no].move.x;
			//unitWk[no].pos.y +=  unitWk[no].move.y;//+ unitWk[no].move.y;
			//unitWk[no].pos.z +=  unitWk[no].move.z;//+ unitWk[no].move.z;

			if (unitWk[no].pos.y < 5.0f)
			{
				unitWk[no].pos.y = 5.0f;
			}
			if (unitWk[no].pos.y > 75.0f)
			{
				unitWk[no].pos.y = 75.0f;
			}

			// 移動量に慣性をかける
			//unitWk[no].move.x += (0.0f - model->move.x) * RATE_MOVE_MODEL;
			//unitWk[no].move.y += (0.0f - model->move.y) * RATE_MOVE_MODEL;
			//unitWk[no].move.z += (0.0f - model->move.z) * RATE_MOVE_MODEL;


			// 領域外に行ったらストップ(÷2しているのはめり込まないようにするため)
			if (unitWk[no].pos.x + (unitWk[no].scl.x) < -MAPLIMIT_X)
			{
				unitWk[no].pos.x = -MAPLIMIT_X;
			}
			if (unitWk[no].pos.x > MAPLIMIT_X)
			{
				unitWk[no].pos.x = MAPLIMIT_X;
			}
			if (unitWk[no].pos.z < -MAPLIMIT_Z)
			{
				unitWk[no].pos.z = -MAPLIMIT_Z;
			}
			if (unitWk[no].pos.z / 2.0f > MAPLIMIT_Z)
			{
				unitWk[no].pos.z = MAPLIMIT_Z;
			}



			// 影の位置設定
			SetPositionShadow(unitWk[no].ShadowID, D3DXVECTOR3(unitWk[no].pos.x, 0.1f, unitWk[no].pos.z));

			SetVertexShadow(unitWk[no].ShadowID, unitWk[no].ShadowSize, unitWk[no].ShadowSize);
			SetColorShadow(unitWk[no].ShadowID, unitWk[no].Shadowcol);
		}
	}
	//
	//PrintDebugProc("[飛行機の位置  ：(%f : %f : %f)]\n", unitWk[no].pos.x, unitWk[no].pos.y, unitWk[no].pos.z);
	//PrintDebugProc("[飛行機の向き  ：(%f) < 目的の向き:(%f) >]\n", unitWk[no].rot.y, unitWk[no].rotDest.y);
	//PrintDebugProc("\n");
	//
	//PrintDebugProc("*** 飛行機操作 ***\n");
	//PrintDebugProc("前移動 : ↑\n");
	//PrintDebugProc("後移動 : ↓\n");
	//PrintDebugProc("左移動 : ←\n");
	//PrintDebugProc("右移動 : →\n");
	//PrintDebugProc("上昇   : T\n");
	//PrintDebugProc("下降   : Y\n");
	//PrintDebugProc("左旋回 : LSHIFT\n");
	//PrintDebugProc("右旋回 : RSHIFT\n");
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUnit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	UNIT *unit = &unitWk[0];


	for (int no = 0; no < UNIT_MAX; no++)
	{
		if (unitWk[no].use = true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&unitWk[no].World);


			// スケールを反映
			D3DXMatrixScaling(&mtxScl, unitWk[no].scl.x, unitWk[no].scl.y, unitWk[no].scl.z);
			D3DXMatrixMultiply(&unitWk[no].World, &unitWk[no].World, &mtxScl);


			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, unitWk[no].rot.y, unitWk[no].rot.x, unitWk[no].rot.z);
			D3DXMatrixMultiply(&unitWk[no].World, &unitWk[no].World, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, unitWk[no].pos.x, unitWk[no].pos.y, unitWk[no].pos.z);
			D3DXMatrixMultiply(&unitWk[no].World, &unitWk[no].World, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &unitWk[no].World);


			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)unitWk[no].BuffMat->GetBufferPointer();



			//// 現在のマテリアルを取得
			//pDevice->GetMaterial(&matDef);

			//// マテリアル情報に対するポインタを取得
			//pD3DXMat = (D3DXMATERIAL*)unitWk[no].BuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatUnit; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, unitWk[no].Texture3D);

				// 描画
				unitWk[no].Mesh->DrawSubset(nCntMat);
			}
		}
	}
	// マテリアルをデフォルトに戻す愛媛
	pDevice->SetMaterial(&matDef);
}

//*****************************************************************************
// 関数名:	int SetUnit(D3DXVECTOR3 pos, float wide, float height, D3DXCOLOR col)
//
//
// 説明: ユニットの作成
//*****************************************************************************
int SetUnit(void)
{
	MODEL *model = GetModel(0);
	int nIdxUnit = -1;

	for (int no = 0; no < UNIT_MAX; no++)
	{
		if (unitWk[no].use = false)		// 未使用のバレット検索
		{
			// 初期設定
			unitWk[no].kaiten = 0;
			unitWk[no].pos = model->pos;
			unitWk[no].move = model->move;
			unitWk[no].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			unitWk[no].rotDest = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
			unitWk[no].scl = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
			unitWk[no].use = true;

			// 影の生成
			unitWk[no].ShadowID = CreateShadow(unitWk[no].pos, 25.0f, 25.0f);

			unitWk[no].ShadowSize = 25.0f;
			unitWk[no].Shadowcol = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

			break;
		}
	}
	return nIdxUnit;
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionUnit(int unitno)
{
	//UNIT *unit = &unitWk[0];
	return unitWk[unitno].pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationUnit(int unitno)
{
	UNIT *unit = &unitWk[0];
	return unitWk[unitno].rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestUnit(int unitno)
{
	UNIT *unit = &unitWk[0];
	return  unitWk[unitno].rotDest;
}

//*****************************************************************************
// ゲット関数
//*****************************************************************************
UNIT *GetUnit(int no)
{
	return(&unitWk[0]);
}