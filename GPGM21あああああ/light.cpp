//=============================================================================
//
// ライト処理 [light.cpp]
//  Author : HALゲーム学科二年生課程1年　山本壮将
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LIGHT_MAX	(8)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
GAMELIGHT LightWk[LIGHT_MAX];				// ライトのワーク

//=============================================================================
// ライトの初期化処理
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	for (int no = 0; no < LIGHT_MAX; no++)
	{
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&LightWk[no], sizeof(D3DLIGHT9));

		// ライトのタイプの設定
		LightWk[no].Lightstatus.Type = D3DLIGHT_DIRECTIONAL;


		// 拡散光
		LightWk[no].Lightstatus.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 環境光
		LightWk[no].Lightstatus.Ambient = D3DXCOLOR(0.8f,0.8f,0.8f, 1.0f);

		// ライトの方向の設定
		LightWk[0].Lightvec = D3DXVECTOR3(0.20f, 0.60f, 0.80f);
		LightWk[1].Lightvec = D3DXVECTOR3(-0.20f, -0.60f, 0.80f);
		LightWk[2].Lightvec = D3DXVECTOR3(0.60f, 0.20f, 0.80f);
		LightWk[3].Lightvec = D3DXVECTOR3(-0.60f, -0.20f, -0.80f);
		LightWk[4].Lightvec = D3DXVECTOR3(0.20f, 0.60f, 0.80f);
		LightWk[5].Lightvec = D3DXVECTOR3(0.20f, 0.60f, -0.80f);
		LightWk[6].Lightvec = D3DXVECTOR3(-0.20f, 0.60f, 0.80f);
		LightWk[7].Lightvec = D3DXVECTOR3(-0.20f, 0.60f, -0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&LightWk[no].Lightstatus.Direction, &LightWk[no].Lightvec);

		// ライトをレンダリングパイプラインに設定
		pDevice->SetLight(no, &LightWk[no].Lightstatus);

		// ライトの設定
		pDevice->LightEnable(no, TRUE);

	}


	// ライティングモード
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{
}
