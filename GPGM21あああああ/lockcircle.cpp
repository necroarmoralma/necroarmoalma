//=============================================================================
//
// モデル処理 [lockcircle.cpp]
// Author : GP11B243 33 山本 壮将
// 説明:	下の部分
//
//=============================================================================
#include "model.h"
#include "lockcircle.h"
#include "camera.h"
#include "input.h"
#include "setting.h"
#include "camera.h"

#include "xinput.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LOCKCIRCLEMOD		"data/STAGE/sitanohaikei.x"
#define SHITANOHAIKEI		"data/STAGE/jimen.jpg"
#define CIRCLELENGTH		(3)							// モデルからサークルまでの距離
// プレイヤーのパーツ数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void controllcirclemove(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LOCKCIRCLE lockcircle;
float lockrot = 0.0f;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitLockcircle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODEL *model = GetModel(0);
	D3DXVECTOR3 rotCamera;


	// 初期位置及びステータスの設定
	lockcircle.status.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	lockcircle.status.move = model->move;
	lockcircle.status.rot = model->rot;
	lockcircle.status.rotDest = model->rotDest;
	lockcircle.status.scl = model->scl;
	lockcircle.status.roton = false;
	// タイヤパーツの初期位置及びステータスの設定


	// 本体の読み込み
	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(LOCKCIRCLEMOD,				// LPCTSTR,ファイルネーム
		D3DXMESH_SYSTEMMEM,		// DWORD,メッシュの作成オプション頂点やインデックスバッファの設定
		pDevice,				// LPDIRECT3DDEVICE9,メッシュに関連付けられていうRデバイスオブジェクトを表す
		NULL,					// LPD3DXBUFFER,1面当たり3つのDWORD配列へのポインタ、隣接面指定
		&lockcircle.status.BuffMatModel,	// LPD3DXBUFFER,マテリアルデータを含むバッファへのポインタD3DXMATERIAL構造体の配列が格納
		NULL,					// LPD3DXBUFFER,インスタンスの配列を含むバッファへのポインタ
		&lockcircle.status.NumMatModel,		// DWORD,D3DXMATERIAL構造体へのポインタ
		&lockcircle.status.MeshModel)))	// LPD3DXMESH,ロードされたメッシュを表すID3DXMeshインターフェイスへのポインタのアドレス
	{
		return E_FAIL;
	}



	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
									SHITANOHAIKEI,		// ファイルの名前
								&lockcircle.status.TextureModel);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLockcircle(void)
{
	MODEL *model = GetModel(0);

	if(lockcircle.status.TextureModel != NULL)
	{// テクスチャの開放
		lockcircle.status.TextureModel->Release();
		lockcircle.status.TextureModel = NULL;
	}

	if (lockcircle.status.MeshModel != NULL)
	{// メッシュの開放
		lockcircle.status.MeshModel->Release();
		lockcircle.status.MeshModel = NULL;

	}

	if (lockcircle.status.BuffMatModel != NULL)
	{// マテリアルの開放
		lockcircle.status.BuffMatModel->Release();
		lockcircle.status.BuffMatModel = NULL;

	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLockcircle(int movetypeno)
{
	float fDiffRotY;
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);




	//// カメラの向き取得
	//rotCamera = GetRotCamera();

	//// 常に前へ
	//lockcircle.status.rotDest.y = rotCamera.y + D3DX_PI;
	//// 動作
	//// コントローラー入力
	//controllcirclemove();

	//// 目的の角度までの差分
	//fDiffRotY = lockcircle.status.rotDest.y - lockcircle.status.rot.y;
	//if (fDiffRotY > D3DX_PI)
	//	{
	//		fDiffRotY -= D3DX_PI * 2.0f;
	//	}
	//if (fDiffRotY < -D3DX_PI)
	//	{
	//		fDiffRotY += D3DX_PI * 2.0f;
	//	}

	//// 目的の角度まで慣性をかける
	//lockcircle.status.rot.y += fDiffRotY * RATE_ROTATE_MODEL;

	//if (lockcircle.status.rot.y > D3DX_PI)
	//{
	//	lockcircle.status.rot.y -= D3DX_PI * 2.0f;


	//	}
	//	if (lockcircle.status.rot.y < -D3DX_PI)
	//	{
	//		lockcircle.status.rot.y += D3DX_PI * 2.0f;
	//	}

	//	lockcircle.status.pos.x += lockcircle.status.move.x;
	//	lockcircle.status.pos.y += lockcircle.status.move.y;
	//	lockcircle.status.pos.z += lockcircle.status.move.z;
	//	// 移動量に慣性をかける
	//	lockcircle.status.move.x += (0.0f - lockcircle.status.move.x) * RATE_MOVE_MODEL;
	//	lockcircle.status.move.y += (0.0f - lockcircle.status.move.y) * RATE_MOVE_MODEL;
	//	lockcircle.status.move.z += (0.0f - lockcircle.status.move.z) * RATE_MOVE_MODEL;

}


//=============================================================================
// 描画処理
//=============================================================================
void DrawLockcircle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&lockcircle.status.World);


	// スケールを反映
	D3DXMatrixScaling(&mtxScl, lockcircle.status.scl.x, lockcircle.status.scl.y, lockcircle.status.scl.z);
	D3DXMatrixMultiply(&lockcircle.status.World, &lockcircle.status.World, &mtxScl);


	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, lockcircle.status.rot.y, lockcircle.status.rot.x, lockcircle.status.rot.z);
	D3DXMatrixMultiply(&lockcircle.status.World, &lockcircle.status.World, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, lockcircle.status.pos.x, lockcircle.status.pos.y, lockcircle.status.pos.z);
	D3DXMatrixMultiply(&lockcircle.status.World, &lockcircle.status.World, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &lockcircle.status.World);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)lockcircle.status.BuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)lockcircle.status.NumMatModel; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, lockcircle.status.TextureModel);

		// 描画
		lockcircle.status.MeshModel->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}


//*****************************************************************************
// ゲット関数
//*****************************************************************************
LOCKCIRCLE *GetLockcircle(int no)
{
	return(&lockcircle);
}


//***************************************************************
// 関数名:	void controllcirclemove(void)
// 引数:	void
// 戻り値:	なし
// 説明:	コントローラーでターゲットサークルの動作を制御する)
//****************************************************************
void controllcirclemove(void)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);
	// ゲームパッドの状態
	XINPUT_STATE state;
	XInputGetState(0, &state);

	// ゲームパッドの状態変化
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	// 左方向
	if (state.Gamepad.sThumbRX < -STICKBASE)
	{
		lockcircle.status.pos.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
		lockcircle.status.pos.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
	}
	// 右方向
	else if(state.Gamepad.sThumbRX > STICKBASE)
	{
		lockcircle.status.pos.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
		lockcircle.status.pos.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
	}
	// 上昇
	if (state.Gamepad.sThumbRY > STICKBASE)
	{
		lockcircle.status.pos.z -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
		lockcircle.status.pos.y -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
	}
	

	// 下降
	else if (state.Gamepad.sThumbRY < -STICKBASE)
	{
		lockcircle.status.pos.z -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
		lockcircle.status.pos.y -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

	}

}