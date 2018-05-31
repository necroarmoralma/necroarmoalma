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
#define LIGHT_MAX	(8)				// 平行光源の数
#define SPOT_MAX	(2)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
GAMELIGHT LightWk[LIGHT_MAX];				// ライトのワーク
bool		Directional_switch[LIGHT_MAX];
bool		Point_switch[LIGHT_MAX + ENEMYMAX];
bool		Anbient_switch;
bool		Spot_switch[LIGHT_MAX + ENEMYMAX + SPOT_MAX];

//=============================================================================
// ライトの初期化処理
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// フラグ初期化
	for (int no = 0; no < LIGHT_MAX;no++)
	{
		Directional_switch[no] = false;
	}

	for (int no = 0; no < ENEMYMAX; no++)
	{
		Point_switch[no] = true;
	}

	Anbient_switch = true;
	for (int no = 0; no < SPOT_MAX; no++)
	{
		Spot_switch[no] = true;
	}



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

	// 点高原設定
	// ポイントライト
	for (int no = LIGHT_MAX; no < LIGHT_MAX + ENEMYMAX; no++)
	{
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&LightWk[no], sizeof(D3DLIGHT9));

		// ライトのタイプの設定
		LightWk[no].Lightstatus.Type = D3DLIGHT_POINT;

		// 拡散光
		LightWk[no].Lightstatus.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// すぺきゅら
		LightWk[no].Lightstatus.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 環境光
		LightWk[no].Lightstatus.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

		// 位置
		LightWk[no].Lightstatus.Position = D3DXVECTOR3(0.0f, 40.0f, 0.0f);
		
		// 減衰
		LightWk[no].Lightstatus.Attenuation0 = 1.0f;
		LightWk[no].Lightstatus.Attenuation1 = 0.0f;
		LightWk[no].Lightstatus.Attenuation2 = 0.0f;
		LightWk[no].Lightstatus.Range = 1000.0f;

		// ライトをレンダリングパイプラインに設定
		pDevice->SetLight(no, &LightWk[no].Lightstatus);

		// ライトの設定
		pDevice->LightEnable(no, TRUE);

	}

	// スポットライト設定
	// 点高原設定
	for (int no = LIGHT_MAX + ENEMYMAX; no < LIGHT_MAX + ENEMYMAX + SPOT_MAX; no++)
	{
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&LightWk[no], sizeof(D3DLIGHT9));

		// ライトのタイプの設定
		LightWk[no].Lightstatus.Type = D3DLIGHT_SPOT;

		// 拡散光
		LightWk[no].Lightstatus.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// すぺきゅら
		LightWk[no].Lightstatus.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 環境光
		LightWk[no].Lightstatus.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

		// 位置
		LightWk[no].Lightstatus.Position = D3DXVECTOR3(0.0f, 40.0f, 40.0f);

		// 光の方向
		LightWk[no].Lightstatus.Direction = D3DXVECTOR3(0.20f, 0.60f, -0.80f);

		// 減衰
		LightWk[no].Lightstatus.Attenuation0 = 1.0f;
		LightWk[no].Lightstatus.Attenuation1 = 0.0f;
		LightWk[no].Lightstatus.Attenuation2 = 0.0f;
		LightWk[no].Lightstatus.Range = 10.0f;

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
// 関数名:	void UpdateLiht(void)
// 引数:	なし
// 説明:	ライトの更新処理(オンオフ)
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ディレク所なるライト　0～3をオフ
	if (GetKeyboardTrigger(DIK_1))
	{
		if (Directional_switch[0] == false)
		{
			pDevice->LightEnable(0, FALSE);
			Directional_switch[0] = true;
		}
		else
		{
			pDevice->LightEnable(0, TRUE);
			Directional_switch[0] = false;
		}

		if (Directional_switch[1] == false)
		{
			pDevice->LightEnable(1, FALSE);
			Directional_switch[1] = true;
		}
		else
		{
			pDevice->LightEnable(1, TRUE);
			Directional_switch[1] = false;
		}

		//2

		if (Directional_switch[2] == false)
		{
			pDevice->LightEnable(2, FALSE);
			Directional_switch[2] = true;
		}
		else
		{
			pDevice->LightEnable(2, TRUE);
			Directional_switch[2] = false;
		}

		// 3
		if (Directional_switch[3] == false)
		{
			pDevice->LightEnable(3, FALSE);
			Directional_switch[3] = true;
		}
		else
		{
			pDevice->LightEnable(3, TRUE);
			Directional_switch[3] = false;
		}
	}


	// ディレクショナルライト　4～7をオフ
	if (GetKeyboardTrigger(DIK_2))
	{

		if (Directional_switch[4] == false)
		{
			pDevice->LightEnable(4, FALSE);
			Directional_switch[4] = true;
		}
		else
		{
			pDevice->LightEnable(4, TRUE);
			Directional_switch[4] = false;
		}

		if (Directional_switch[5] == false)
		{
			pDevice->LightEnable(5, FALSE);
			Directional_switch[5] = true;
		}
		else
		{
			pDevice->LightEnable(5, TRUE);
			Directional_switch[5] = false;
		}

		if (Directional_switch[6] == false)
		{
			pDevice->LightEnable(6, FALSE);
			Directional_switch[6] = true;
		}
		else
		{
			pDevice->LightEnable(6, TRUE);
			Directional_switch[6] = false;
		}

		//7

		if (Directional_switch[7] == false)
		{
			pDevice->LightEnable(7, FALSE);
			Directional_switch[7] = true;
		}
		else
		{
			pDevice->LightEnable(7, TRUE);
			Directional_switch[7] = false;
		}

	}


	// スポットライトをオンオフ
	if (GetKeyboardTrigger(DIK_3))
	{
		for (int no = LIGHT_MAX + ENEMYMAX; no < LIGHT_MAX + ENEMYMAX + SPOT_MAX; no++)
		{
			if (Spot_switch[no] == false)
			{
				pDevice->LightEnable(no, TRUE);
				Spot_switch[no] = true;
			}
			else
			{
				pDevice->LightEnable(no, FALSE);
				Spot_switch[no] = false;
			}
		}
	}

	// ポイントライトをオンオフ
	if (GetKeyboardTrigger(DIK_4))
	{
		for (int no = LIGHT_MAX; no < LIGHT_MAX + ENEMYMAX; no++)
		{
			if (Point_switch[no] == false)
			{
				pDevice->LightEnable(no, TRUE);
				Point_switch[no] = true;
			}
			else
			{
				pDevice->LightEnable(no, FALSE);
				Point_switch[no] = false;
			}
		}
	}
}
