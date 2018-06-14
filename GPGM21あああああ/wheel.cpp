//=============================================================================
//
// モデル処理 [wheel.cpp]
// Author : GP11B243 33 山本 壮将
// 説明:	モデルの車輪部分の処理
//
//=============================================================================
#include "model.h"
#include "wheel.h"
#include "camera.h"
#include "input.h"
#include "setting.h"
#include "camera.h"

#include "xinput.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODELTAIYA		"data/MODEL/yajirushi.x"
#define WHEELSPIN		(1.1f)							// ホイールの回転速度
// プレイヤーのパーツ数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
float booster;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitWheel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODEL *model = GetModel(0);
	D3DXVECTOR3 rotCamera;

	booster = 0.0f;
	model->taiya_status.TextureModel = NULL;
	model->taiya_status.MeshModel = NULL;
	model->taiya_status.BuffMatModel = NULL;

	// 初期位置及びステータスの設定
	model->taiya_status.pos = model->pos;
	model->taiya_status.move = model->move;
	model->taiya_status.rot = model->rot;
	model->taiya_status.rotDest = model->rotDest;
	model->taiya_status.scl = model->scl;
	model->taiya_status.roton = false;
	// タイヤパーツの初期位置及びステータスの設定


	// 本体の読み込み
	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(MODELTAIYA,				// LPCTSTR,ファイルネーム
		D3DXMESH_SYSTEMMEM,		// DWORD,メッシュの作成オプション頂点やインデックスバッファの設定
		pDevice,				// LPDIRECT3DDEVICE9,メッシュに関連付けられていうRデバイスオブジェクトを表す
		NULL,					// LPD3DXBUFFER,1面当たり3つのDWORD配列へのポインタ、隣接面指定
		&model->taiya_status.BuffMatModel,	// LPD3DXBUFFER,マテリアルデータを含むバッファへのポインタD3DXMATERIAL構造体の配列が格納
		NULL,					// LPD3DXBUFFER,インスタンスの配列を含むバッファへのポインタ
		&model->taiya_status.NumMatModel,		// DWORD,D3DXMATERIAL構造体へのポインタ
		&model->taiya_status.MeshModel)))	// LPD3DXMESH,ロードされたメッシュを表すID3DXMeshインターフェイスへのポインタのアドレス
	{
		return E_FAIL;
	}



	// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
	//								DOOMHAIKEI,		// ファイルの名前
	//							&model->taiya_status.TextureModel);	// 読み込むメモリー


	//// 影の生成
	//model->taiya_status.IdxShadow = CreateShadow(model->pos, 25.0f, 25.0f);

	//model->taiya_status.SizeShadow = 25.0f;
	//model->taiya_status.colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);


	// model_longcheckで取得した半径だけ上昇させる
	//model->pos.y += model->center;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWheel(void)
{
	MODEL *model = GetModel(0);

	//if(model->taiya_status.TextureModel != NULL)
	//{// テクスチャの開放
	//	model->taiya_status.TextureModel->Release();
	//	model->taiya_status.TextureModel = NULL;
	//}

	if (model->taiya_status.MeshModel != NULL)
	{// メッシュの開放
		model->taiya_status.MeshModel->Release();
		model->taiya_status.MeshModel = NULL;

	}

	if (model->taiya_status.BuffMatModel != NULL)
	{// マテリアルの開放
		model->taiya_status.BuffMatModel->Release();
		model->taiya_status.BuffMatModel = NULL;

	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWheel(int movetypeno)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);
	// ゲームパッドの状態
	XINPUT_STATE state;
	XInputGetState(0, &state);

	// ゲームパッドの状態変化
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	// カメラの向き取得
	rotCamera = GetRotCamera();


	if (movetypeno == model_game)
	{
		
		model->taiya_status.rot.z = model->rot.z;
		model->taiya_status.scl = model->scl;
		model->rotDest.y = rotCamera.y + D3DX_PI;



		// たいやかいてん

		// 左
		if (GetKeyboardPress(DIK_A))
		{
			// 左上
			if (GetKeyboardPress(DIK_W))
			{
				booster += WHEELSPIN;
				model->taiya_status.rot.y = hidariue;
			}
			// 左下
			else if (GetKeyboardPress(DIK_S))
			{
				booster -= WHEELSPIN;
				model->taiya_status.rot.y = hidarishita;
			}
		
			else
			{
				booster += WHEELSPIN;
				model->taiya_status.rot.y = hidari;
			}
		}

		// 右
		else if (GetKeyboardPress(DIK_A))
		{
			model->taiya_status.rot.y =  hidari;
			booster -= WHEELSPIN;		// 前
									// 左上
			if (GetKeyboardPress(DIK_W))
			{
				model->taiya_status.rot.y =  hidariue;
			}
			// 左下
			else if (GetKeyboardPress(DIK_S))
			{
				model->taiya_status.rot.y =  hidarishita;
			}
		}
		else  if (GetKeyboardPress(DIK_W))
		 {
			 booster -= WHEELSPIN;		// 前
		 }
		else if (GetKeyboardPress(DIK_S))
		{
			booster += WHEELSPIN;
		}


		 // コントローラー操作
		// 右
		 if (state.Gamepad.sThumbLX>STICKBASE)
		 {

			// 右上
			 if (state.Gamepad.sThumbLY>STICKBASE)
			 {
				 booster -= WHEELSPIN;
				 model->taiya_status.rot.y = migiue;
			 }
			 // 右下
			 else if (state.Gamepad.sThumbLY< -STICKBASE)
			 {
				 booster -= WHEELSPIN;
				 model->taiya_status.rot.y = migishita;
			 }
			 else
			 {
				 // 右
				 model->taiya_status.rot.y = migi;
				 booster += WHEELSPIN;
			 }
		 }
		 // 左方向
		 else if (state.Gamepad.sThumbLX < -STICKBASE)
		 {
			// 左上
			 if (state.Gamepad.sThumbLY>STICKBASE)
			 {
				 booster -= WHEELSPIN;
				 model->taiya_status.rot.y = hidariue;
			 }
			 // 左下
			 else if (state.Gamepad.sThumbLY< -STICKBASE)
			 {
				 booster -= WHEELSPIN;
				 model->taiya_status.rot.y = hidarishita;
			 }

			 // 左
			 else
			 {
				 booster += WHEELSPIN;
				 model->taiya_status.rot.y = hidari;
			 }
		 }
		 else  if (state.Gamepad.sThumbLY>STICKBASE)
		 {
			 booster -= WHEELSPIN;		// 前
			 model->taiya_status.rot.y = ue;
		 }
		 else if (state.Gamepad.sThumbLY< -STICKBASE)
		 {
			 booster += WHEELSPIN;
			 model->taiya_status.rot.y = shita;
		 }

		// 移動量の変更が確認できない場合強制停止
		else
		{
			booster = 0.0f;
		}
		//modle->taiya_status.
	}

}


//=============================================================================
// 描画処理
//=============================================================================
void DrawWheel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	MODEL *model = GetModel(0);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&model->taiya_status.World);


	// スケールを反映
	D3DXMatrixScaling(&mtxScl, model->scl.x, model->scl.y, model->scl.z);
	D3DXMatrixMultiply(&model->World, &model->World, &mtxScl);


	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,  model->taiya_status.rot.y, booster, (model->taiya_status.rot.z)*0.0f);
	D3DXMatrixMultiply(&model->taiya_status.World, &model->taiya_status.World, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, model->pos.x, model->pos.y, model->pos.z);
	D3DXMatrixMultiply(&model->taiya_status.World, &model->taiya_status.World, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &model->taiya_status.World);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)model->taiya_status.BuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)model->taiya_status.NumMatModel; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, model->taiya_status.TextureModel);

		// 描画
		model->taiya_status.MeshModel->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionWheel(void)
{
	MODEL *model = GetModel(0);
	return model->taiya_status.pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationWheel(void)
{
	MODEL *model = GetModel(0);
	return model->taiya_status.pos;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestWheel(void)
{
	MODEL *model = GetModel(0);
	return model->rotDest;
}


