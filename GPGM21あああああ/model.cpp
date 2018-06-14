//=============================================================================
//
// モデル処理 [model.cpp]
// Author : GP11B243 33 山本 壮将
// 説明: 名前変更予定(podbody or modelbody））
//		モデルの本体部分関連
//
//=============================================================================
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"
#include "bulletmk2.h"
#include "unit.h"
#include "setting.h"
#include "camera.h"
#include "map.h"
#include "steam.h"
// ゲームコントローターの動きを検出
#include "xinput.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLEUP   (4.0f)
#define MODELREFLECT	(1.80f);
// 弾の大きさ(基本的にXもYも同じ値)
#define BULLETMK2BASESIZE (15.0f)		//　基本的にXもYも同じサイズ
//#define BULLETMK2BASESIZEY 


//　壁との距離判定用、半径そのままだとめりこむので超するための値
#define LONGHOSEI	(0.0f)

// プレイヤーのパーツ数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void escapefromwall(void);
void keyboardmove(void);
void xinputmove(void);
void xinputrot(void);
void evolve_modelbullet(int shotlv);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int					g_nIdxShadow;				// 影ID
int					modelmovetype;				// モデルの動作モード
float				g_fSizeShadow;				// 影のサイズ
D3DXCOLOR			g_colShadow;				// 影の色
MODEL				modelWk[1];					// モデル構造体(モデルは１）
bool				roton;						// 今物体は回転
bool				modelcontroller = false;		// 既にコントローラーの入力を受けたのか
bool				jump = false;					// 今飛んでるの？
float				centertoleg = MODEL_DISTANCE_CL;
float				controlcount;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitModel(int gametypeno)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODEL *model = &modelWk[0];
	D3DXVECTOR3 rotCamera;
	

	// ショットの設定
	model->shot = SHOTKANKAKU;
	model->shot_on = true;			// 撃てるようにしておく
	
	// 回転
	roton = false;
	// HPの設定
	model->Maxlife = PLAYER_HP_MAX;
	model->Nowlife = model->Maxlife;

	// 回転制御
	model->rollon = false;
	model->cooltime = COOLTIME;

	model->status.TextureModel = NULL;
	model->status.MeshModel = NULL;
	model->status.BuffMatModel = NULL;

	// 初期位置及びステータスの設定(boolの設定もここで)
	model->pos = D3DXVECTOR3(8.0f, 0.0f, 55.6555443f);					// 微調整
	model->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model->puremove = model->move;
	model->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model->scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	//model->rot.y = 90.0f;			// 回転させないと変な方向向くので仮置き
	model->control = true;			// キー入力を受け付ける
	model->escapemode = false;
	model->shotlv = 0;				// レベルは０から
	controlcount = 0.0f;


	// タイヤパーツの初期位置及びステータスの設定

		// 本体の読み込み
		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(PITCH_MODEL,				// LPCTSTR,ファイルネーム
			D3DXMESH_SYSTEMMEM,		// DWORD,メッシュの作成オプション頂点やインデックスバッファの設定
			pDevice,				// LPDIRECT3DDEVICE9,メッシュに関連付けられていうRデバイスオブジェクトを表す
			NULL,					// LPD3DXBUFFER,1面当たり3つのDWORD配列へのポインタ、隣接面指定
			&model->status.BuffMatModel,	// LPD3DXBUFFER,マテリアルデータを含むバッファへのポインタD3DXMATERIAL構造体の配列が格納
			NULL,					// LPD3DXBUFFER,インスタンスの配列を含むバッファへのポインタ
			&model->status.NumMatModel,		// DWORD,D3DXMATERIAL構造体へのポインタ
			&model->status.MeshModel)))	// LPD3DXMESH,ロードされたメッシュを表すID3DXMeshインターフェイスへのポインタのアドレス
		{
			return E_FAIL;
		}
	

	

	// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
//								DOOMHAIKEI,		// ファイルの名前
	//							&g_pD3DTextureModel);	// 読み込むメモリー


	// 影の生成
	//g_nIdxShadow = CreateShadow(model->pos, 25.0f, 25.0f);

	//g_fSizeShadow = 25.0f;
	//g_colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	//// model_longcheckで取得した半径だけ上昇させる
	//model->pos.y += model->center;


	
		// あとで消す
		// モデルセンターちょうせい
		//model->center += LONGHOSEI;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	MODEL *model = &modelWk[0];

	//if(model->status.TextureModel != NULL)
	//{// テクスチャの開放
	//	model->status.TextureModel->Release();
	//	model->status.TextureModel = NULL;
	//}

	if(model->status.MeshModel != NULL)
	{// メッシュの開放
		model->status.MeshModel->Release();
		model->status.MeshModel = NULL;

	}

	if(model->status.BuffMatModel != NULL)
	{// マテリアルの開放
		model->status.BuffMatModel->Release();
		model->status.BuffMatModel = NULL;

	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(int movetypeno)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = &modelWk[0];
	UNIT *unit = GetUnit(0);
	float fDiffRotY;
	float hosei_y;			// モデルのY座標の補正
	int movetype = movetypeno;

	// カメラの向き取得
	rotCamera = GetRotCamera();
	// 直前の入力初期化
	modelcontroller = false;

	// タイトル画面の場合
	if (movetype == model_title)
	{
		model->rot.y += 0.01f;

	}
	// ゲームの場合
	if (movetype == model_game)
	{
		// 現在の座標を取得する
		model->oldpos = model->pos;

		// 常に前へ
		model->rotDest.y = rotCamera.y + D3DX_PI;

		// 接触確認
		// レイの長さが半径よりも短い(接触)
		if (model->R_RtoMdistance < model->center || model->L_RtoMdistance < model->center
			|| model->F_RtoMdistance < model->center || model->B_RtoMdistance < model->center || model->D_RtoMdistance < model->center
			)
		{
			escapefromwall();
		}



		// テスト
		if (GetKeyboardPress(DIK_U))
		{
			model->Nowlife -= 10.0f;
		}

		// 動作
		// コントローラー入力
			//xinputmove();
			//xinputrot();

		// キーボード入力
		keyboardmove();


		// 動作
		if (modelcontroller == false)
		{
			//keyboardmove();
		}



		if (model->rollon == false)
		{
			// キーが押されていないのなら回転を戻す
			if (roton == false)
			{
				if (model->rot.z < 0)
				{
					model->rot.z += MODEL_MOVEROLL / 10;
				}

				if (model->rot.z > 0)
				{
					model->rot.z -= MODEL_MOVEROLL / 10;
				}

				if (model->rot.x < 0)
				{
					model->rot.x += MODEL_MOVEROLL / 10;
				}

				if (model->rot.x > 0)
				{
					model->rot.x -= MODEL_MOVEROLL / 10;
				}
			}

		}
		roton = false;
		// 目的の角度までの差分
		fDiffRotY = model->rotDest.y - model->rot.y;
		if (fDiffRotY > D3DX_PI)
		{
			fDiffRotY -= D3DX_PI * 2.0f;
		}
		if (fDiffRotY < -D3DX_PI)
		{
			fDiffRotY += D3DX_PI * 2.0f;
		}

		// 目的の角度まで慣性をかける
		//model->rot.y += fDiffRotY * RATE_ROTATE_MODEL;

		// 位置移動

		//// 移動前にぶつかってないか確かめる
		//if (model->tomapDown == FALSE)	// 下に何もない
		//{
		//	model->pos = model->oldpos;
		//	model->move.x *= -1.2;		// 移動量を反転させちゃう
		//	model->move.y *= -1.2;
		//	model->move.z *= -1.2;
		//	// 判定した場合キー入力受付を拒否
		//	model->control = false;
		//	controlcount = NOCONTROL;
		//}




		model->pos.x += model->move.x;
		model->pos.y += model->move.y;
		model->pos.z += model->move.z;

	

		// 慣性かける前に移動量を保存
		model->puremove = model->move;


		// 移動量に慣性をかける
		model->move.x += (0.0f - model->move.x) * RATE_MOVE_MODEL;
		model->move.y += (0.0f - model->move.y) * RATE_MOVE_MODEL;
		model->move.z += (0.0f - model->move.z) * RATE_MOVE_MODEL;


		// 移動が終わったらレイピックを行う
		model_RaypickTomap();

		// 地面に沿って移動させる
		// 下にレイがあるかどうか
		//if (model->tomapUp == FALSE)			// 上方向には何もない
		//{
		//	if (model->tomapDown == TRUE)		// マップが下にある
		//	{
		//		if (model->D_RtoMdistance >= model->center)	// モデルと地面が常に接するようにするために
		//		{
		//			model->pos.y -= 1.0f;		// モデルより浮いていたら位置を下げる
		//			if ((model->D_RtoMdistance) <= model->center)
		//			{
		//				model->pos.y += model->center - model->D_RtoMdistance;
		//			}
		//			else if (model->pos.y <= model->center)
		//			{
		//				// 地面にぶつけてから引き上げる
		//			//	model->pos.y -= model->D_RtoMdistance;
		//			//	model->pos.y += model->center;
		//			}
		//		}
		//	}

		//}
		// 下降
		// 補正を足す方法でつじつまを合わせる
		if (model->D_RtoMdistance > model->center)
		{
			jump = true;
		}
		else
		{
			jump = false;
		}

		if (jump == true)
		{
		//	model->pos.y -= 0.5f;
		}
		// どんな値だろうとめり込んでるならあがるはず
		if (model->D_RtoMdistance <= model->center)
		{
			hosei_y = model->center - model->D_RtoMdistance;
			model->pos.y +=hosei_y;
			jump = false;
		}
		


		// 影の位置設定
		SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(model->pos.x, 0.1f, model->pos.z));

		SetVertexShadow(g_nIdxShadow, g_fSizeShadow, g_fSizeShadow);
		SetColorShadow(g_nIdxShadow, g_colShadow);

		PrintDebugProc("modelposいくつ:(%f)(%f)(%f) ]\n", model->pos.x,model->pos.y,model->pos.z);
		PrintDebugProc("ショットのレベルは？:(%d)]\n", model->shotlv);

		// 移動量が1フレーム以上変わらない場合コントロール可能にする
		if (controlcount == 0.0f)
		{
			model->control = true;
		}
		if (model->control == false)
		{
			controlcount--;
			model->rot.z += 0.1f;
		}

		// 最後にスチームだしておわり
		//SetSteam(D3DXVECTOR3(model->pos.x,model->pos.y,model->pos.z), 1, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(int gametypeno)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl,mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	MODEL *model = &modelWk[0];

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&model->World);


	// スケールを反映
	D3DXMatrixScaling(&mtxScl, model->scl.x, model->scl.y, model->scl.z);
	D3DXMatrixMultiply(&model->World, &model->World, &mtxScl);


	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, model->rot.y, model->rot.x+ MODEL_MOVEROLlX, model->rot.z);
	D3DXMatrixMultiply(&model->World, &model->World, &mtxRot);

	// 移動を反映
	if (gametypeno == model_title)
	{
		// たいとるのときだけじっさいよりちょっとうえにうつす
		D3DXMatrixTranslation(&mtxTranslate, model->pos.x , model->pos.y + TITLEUP, model->pos.z);
	}
	else if (gametypeno == model_game)
	{
		D3DXMatrixTranslation(&mtxTranslate, model->pos.x, model->pos.y, model->pos.z);
	}
	D3DXMatrixMultiply(&model->World, &model->World, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &model->World);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)model->status.BuffMatModel->GetBufferPointer();

	for(int nCntMat = 0; nCntMat < (int)model->status.NumMatModel; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, model->status.TextureModel);

		// 描画
		model->status.MeshModel->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionModel(void)
{
	MODEL *model = &modelWk[0];
	return model->pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationModel(void)
{
	MODEL *model = &modelWk[0];
	return model->rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestModel(void)
{
	MODEL *model = &modelWk[0];
	return model->rotDest;
}

//*****************************************************************************
// ゲット関数
//*****************************************************************************
MODEL *GetModel(int no)
{
	return(&modelWk[0]);
}

//*****************************************************************************
// 関数名:	void model_RaypickToMap(int no)
// 引数:	int no
// 戻り値:	無し
// 説明:	自機とマップとのレイピック、引数はレイを飛ばす方向
//*****************************************************************************
void model_RaypickTomap(void)
{

	MODEL *model = &modelWk[0];
	MAP *map = GetMap(0);

		// 便利関数と引数の説明(自分用)
		// 下へ飛ばす
		D3DXIntersect(
			map->MeshMap,				// 当たり判定を取りたいメッシュ　型はLPD3DXBASEMESH(LPD3DXMESHもOK?)
			&D3DXVECTOR3(model->pos.x, model->pos.y + 0.0f, model->pos.z),				// レイの視点座標を設定(プレイヤーの座標とか) 型はD3DXVECTOR3
			&D3DXVECTOR3(0, -1, 0),		// レイの方向を設定 型はD3DXVECTOR3 XYZ 1で正方向-1で負の方向
			&model->tomapDown,				// 衝突判定 型はBOOL(boolではない) 衝突していたらTRUE当たっていなければFALSE
			NULL,						// 上記の判定がTRUEの場合レイの視点に最も近い面のインデックス値へのポインタ
			NULL,						// 重心ヒット座標へのポインタその1レイが当たったメッシュの場所
			NULL,						// 重心ヒット座標へのポインタその2こちらも同じくメッシュの当たった場所
			&model->D_RtoMdistance,		// レイからメッシュまでの距離はいくつ
			NULL,						// D3DXINTERSECTINFO構造体の配列を格納するID3DXBufferオブジェクトへのポインタ
			NULL						// ppAllHits配列内のエントリ数を格納するポインタ、型はDWORD
		);


		// レイピック(モデルから上に飛ばしたレイとマップ)
		D3DXIntersect(map->MeshMap, &model->pos, &D3DXVECTOR3(0, 1, 0), &model->tomapUp, NULL, NULL, NULL,
			&model->U_RtoMdistance, NULL, NULL);

		// レイピック(右に飛ばしたレイとマップ)
		D3DXIntersect(map->MeshMap, &model->pos, &D3DXVECTOR3(1, 0, 0), &model->tomapRight, NULL, NULL, NULL,
			&model->R_RtoMdistance, NULL, NULL);

		// レイピック(左に飛ばしたレイとマップ)
		D3DXIntersect(map->MeshMap, &model->pos, &D3DXVECTOR3(-1, 0, 0), &model->tomapLeft, NULL, NULL, NULL,
			&model->L_RtoMdistance, NULL, NULL);

		// レイピック(前方方向に飛ばしたレイとマップ)
		D3DXIntersect(map->MeshMap, &model->pos, &D3DXVECTOR3(0, 0, 1), &model->tomapFront, NULL, NULL, NULL,
			&model->F_RtoMdistance, NULL, NULL);

		// レイピック(後方高校に飛ばしたレイとマップ)
		D3DXIntersect(map->MeshMap, &model->pos, &D3DXVECTOR3(0, 0, -1), &model->tomapBack, NULL, NULL, NULL,
			&model->B_RtoMdistance, NULL, NULL);
		
	}


//**********************************************************************************
// 関数名:	void escapefromwall(void)
// 戻り値:	なし
// 引数:	なし
// 説明:	壁へめり込むことを事前に防ぐ
//**********************************************************************************
void escapefromwall(void)
{
	MODEL *model = &modelWk[0];
	D3DXVECTOR3 hosei;
	D3DXVECTOR3 rotCamera;
	float		escapmodellmove = 1.0f;		// 値を補正させるため
	float		hoseichi;					// 補正値こみの半径
	// カメラの向き取得
	rotCamera = GetRotCamera();

//model->move.x *= -MODEL_BAUNCE;
//model->move.y *= -MODEL_BAUNCE;
//model->move.z *= -MODEL_BAUNCE;

	//controlcount = NOCONTROL;
	//model->control = false;


	// 補正値をたす
	hoseichi = model->center + LONGHOSEI;
	// テスト壁にそってとめてしまう
	// 壁とのレイを半径にすればいい
	// レイが半径以下になっている場合半径になるよう移動させてあげればいい
	if (model->R_RtoMdistance <= model->center)
	{
		// 左に補正をかける
		hosei.x = model->center - model->R_RtoMdistance;
		model->pos.x -= hosei.x;

	//	model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * 10.0f;
	//	model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * 10.0f;
	}
		
	else if (model->L_RtoMdistance <= model->center)
	{	// 右に補正をかける
		hosei.x = model->center - model->L_RtoMdistance;
		model->pos.x += hosei.x;
	}

	if (model->F_RtoMdistance <= model->center)
	{	// 後ろに補正をかける
		hosei.z = model->center - model->F_RtoMdistance;
		model->pos.z -= hosei.z;

	}
	else if (model->B_RtoMdistance <= model->center)
	{	// 前に補正をかける
		hosei.z = model->center - model->B_RtoMdistance;
		model->pos.z += hosei.z;
	}

	if (model->D_RtoMdistance <= model->center)
	{
	//	hosei.y = model->center - model->D_RtoMdistance;
	//	model->pos.y += hosei.y;
	}




	model->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


//****************************************************************************
// 関数名:	void xinputmove(void)
// 引数:	なし
// 戻り値:	なし
// 説明:	xinputを利用して動きを制御する
//****************************************************************************
void xinputmove(void)
{
	MODEL *model = &modelWk[0];
	D3DXVECTOR3 rotCamera;

	// ゲームパッドの状態
	XINPUT_STATE state;
	// スティック入力初期化
	state.Gamepad.sThumbLX = 0;
	state.Gamepad.sThumbLY = 0;

	XInputGetState(0, &state);

	// ゲームパッドの状態変化
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);




	// カメラの向き取得
	rotCamera = GetRotCamera();
	// 常に前へ
	//model->rotDest.y = rotCamera.y + D3DX_PI;

	// コントロール可能なら受け付ける処理
	if (model->control == true)
	{
		if (model->escapemode == false)
		{
			// メモ　10で割ってるのは10フレームで移動させるため
			if (state.Gamepad.sThumbLX < -STICKBASE)
			{
				if (state.Gamepad.sThumbLY > STICKBASE)
				{// 左前移動b
					model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

				}
				else if (state.Gamepad.sThumbLY<-STICKBASE)
				{// 左後移動
					model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;

				}
					else
					{// 左移動
						model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
						model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
					}
				}

				// 右
				else if (state.Gamepad.sThumbLX>STICKBASE)
				{
					if (state.Gamepad.sThumbLY>STICKBASE)
					{// 右前移動
						model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
						model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

					}
					else if (state.Gamepad.sThumbLY< -STICKBASE)
					{// 右後移動
						model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
						model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;


					}
					else
					{// 右移動
						model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
						model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

					}
				}
				else if (state.Gamepad.sThumbLY>STICKBASE)
				{// 前移動
					model->move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;

				}
				else if (state.Gamepad.sThumbLY< -STICKBASE)
				{// 後移動
					model->move.x -= sinf(rotCamera.y) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y) * VALUE_MOVE_MODEL;
				}
			}
		}
		// コントール不可能な状態でも受け付ける処理

	// 自機の上昇と下降(75.0と20.0はそれぞれ上限と下限の値defineする)

	if (GetKeyboardPress(DIK_I))
		{// 上昇
			model->move.y += VALUE_MOVE_MODEL * 0.5f;

			if (model->pos.y < 75.0f)
			{
				g_fSizeShadow += 0.2f;
				g_colShadow.a -= 0.004f;
			}
		}
	if (GetKeyboardPress(DIK_K))
		{// 下降
			model->move.y -= VALUE_MOVE_MODEL * 0.5f;

			if (model->pos.y > 20.0f)
			{
				g_fSizeShadow -= 0.2f;
				g_colShadow.a += 0.004f;
			}
		}

	if (model->shot_on == true)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER || state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			// 玉発射
			D3DXVECTOR3 pos = model->pos;
			evolve_modelbullet(model->shotlv);
			model->shot = 0.0f;
			model->shot_on = false;


		}
	}

	 if (model->shot_on == false)
	{
		model->shot++;
		if (model->shot >= SHOTKANKAKU)
		{
			model->shot_on = true;
		}
	}


	// 上昇
	if (state.Gamepad.sThumbRY > STICKBASE)
	{
		model->rot.x += 0.01f;
	}


	// 下降
	else if (state.Gamepad.sThumbRY < -STICKBASE)
	{
		model->rot.x -= 0.01f;
	

	}
}

//****************************************************************************
// 関数名:	void xinputrot(void)
// 引数:	なし
// 戻り値:	なし
// 説明:	xinputを利用して自機の回転を制御する
//****************************************************************************
void xinputrot(void)
{
	MODEL *model = &modelWk[0];
	D3DXVECTOR3 rotCamera;

	// ゲームパッドの状態
	XINPUT_STATE state;
	XInputGetState(0, &state);

	// ゲームパッドの状態変化
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	//model->rot.y

	// 左方向
	if (state.Gamepad.sThumbRX < -STICKBASE)
	{
		model->rot.y = hidari;
		// 左上に向ける
		if (state.Gamepad.sThumbRY > STICKBASE/2)
		{
			model->rot.y = hidariue;
		}
		// 左下へ向ける
		else if(state.Gamepad.sThumbRY < -STICKBASE/2)
		{
			model->rot.y = hidarishita;
		}

	}

	// 右方向
	else if (state.Gamepad.sThumbRX > STICKBASE)
	{
		model->rot.y = migi;
		// 右上
		if (state.Gamepad.sThumbRY > STICKBASE)
		{
			model->rot.y = migiue;
		}

		// 右下
		else if (state.Gamepad.sThumbRY < -STICKBASE)
		{
			model->rot.y = migishita;
		}

	}

	else if (state.Gamepad.sThumbRY > STICKBASE)
	{
		model->rot.y = ue;
	}

	else if (state.Gamepad.sThumbRY < -STICKBASE)
	{
		model->rot.y = shita;
	}
		

}
//****************************************************************************
// 関数名:	void keyboardmove(void)
// 引数:	なし
// 戻り値:	なし
// 説明:	キーボードで動作させる
//****************************************************************************
void keyboardmove(void)
{
	MODEL *model = &modelWk[0];
	D3DXVECTOR3 rotCamera;
	// カメラの向き取得
	rotCamera = GetRotCamera();
	// 常に前へ
	//model->rotDest.y = rotCamera.y + D3DX_PI;


	// コントロール可能なら受け付ける処理
	if (model->control == true)
	{
		if (model->escapemode == false)
		{
			// 横井童子の回転を一時的に無効か
			// メモ　10で割ってるのは10フレームで移動させるため
			if (GetKeyboardPress(DIK_A))
			{
				if (GetKeyboardPress(DIK_W))
				{// 左前移動b
					model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

					model->rot.x += -MODEL_MOVEROLlX / 10;
					if (model->rot.x <= -MODEL_MOVEROLlX)
					{
						model->rot.x = -MODEL_MOVEROLlX;
					}
					model->rot.z += -MODEL_MOVEROLL / 10;
					if (model->rot.z <= -MODEL_MOVEROLL)
					{
						model->rot.z = -MODEL_MOVEROLL;
					}
					roton = true;
					//model->rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
				}
				else if (GetKeyboardPress(DIK_S))
				{// 左後移動
					model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
				
					model->rot.x += MODEL_MOVEROLlX / 10;
					if (model->rot.x >= MODEL_MOVEROLlX)
					{
						model->rot.x = MODEL_MOVEROLlX;
					}
					model->rot.z += -MODEL_MOVEROLL / 10;
					if (model->rot.z <= -MODEL_MOVEROLL)
					{
						model->rot.z = -MODEL_MOVEROLL;
					}
					//	model->rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
					roton = true;
				}
				else
				{// 左移動
					model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

					model->rot.z += -MODEL_MOVEROLL / 10;
					if (model->rot.z <= -MODEL_MOVEROLL)
					{
						model->rot.z = -MODEL_MOVEROLL;
					}

					model->rot.y = 1.57f;		// 左
					//model->rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
					roton = true;
				}
			}
			else if (GetKeyboardPress(DIK_D))
			{
				if (GetKeyboardPress(DIK_W))
				{// 右前移動
					model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

					model->rot.x += -MODEL_MOVEROLL / 10;
					if (model->rot.x <= -MODEL_MOVEROLL)
					{
						model->rot.x = -MODEL_MOVEROLL;
					}
					model->rot.z += MODEL_MOVEROLL / 10;
					if (model->rot.z >= MODEL_MOVEROLL)
					{
						model->rot.z = MODEL_MOVEROLL;
					}
					//model->rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
					roton = true;
				}
				else if (GetKeyboardPress(DIK_S))
				{// 右後移動
					model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
					model->rot.x += MODEL_MOVEROLlX / 10;
					if (model->rot.x >= MODEL_MOVEROLlX)
					{
						model->rot.x = MODEL_MOVEROLlX;
					}
					model->rot.z += MODEL_MOVEROLL / 10;
					if (model->rot.z >= MODEL_MOVEROLL)
					{
						model->rot.z = MODEL_MOVEROLL;
					}
					//	model->rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
					roton = true;
				}
				else
				{// 右移動
					model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

					model->rot.z += MODEL_MOVEROLL / 10;
					if (model->rot.z >= MODEL_MOVEROLL)
					{
						model->rot.z = MODEL_MOVEROLL;
					}

					model->rot.y = -1.57f;			// 右
					//model->rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
					roton = true;
				}
			}
			else if (GetKeyboardPress(DIK_W))
			{// 前移動
				model->move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;
				model->move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;
				model->rot.x += -MODEL_MOVEROLlX / 10;
				if (model->rot.x <= -MODEL_MOVEROLlX)
				{
					model->rot.x = -MODEL_MOVEROLlX;
				}

				model->rot.y = 3.14f;

				//model->rotDest.y = rotCamera.y + D3DX_PI;
				roton = true;
			}
			else if (GetKeyboardPress(DIK_S))
			{// 後移動
				model->move.x -= sinf(rotCamera.y) * VALUE_MOVE_MODEL;
				model->move.z -= cosf(rotCamera.y) * VALUE_MOVE_MODEL;

				model->rot.x += MODEL_MOVEROLlX / 10;
				if (model->rot.x > MODEL_MOVEROLlX)
				{
					model->rot.x = MODEL_MOVEROLlX;
				}
				//model->rotDest.y = rotCamera.y ;
				model->rot.y = 0.0f;
				roton = true;
			}
		}
	}
	// コントール不可能な状態でも受け付ける処理

	//if (GetKeyboardPress(DIK_LSHIFT))
	//{// 左回転
	//	model->rotDest.y -= VALUE_ROTATE_MODEL;
	//	if (model->rotDest.y < -D3DX_PI)
	//	{
	//		model->rotDest.y += D3DX_PI * 2.0f;
	//	}
	//}
	//if (GetKeyboardPress(DIK_RSHIFT))
	//{
	//	// 右回転
	//	model->rotDest.y += VALUE_ROTATE_MODEL;
	//	if (model->rotDest.y > D3DX_PI)
	//	{
	//		model->rotDest.y -= D3DX_PI * 2.0f;
	//	}
	//}

	// 自機の上昇と下降(75.0と20.0はそれぞれ上限と下限の値defineする)

	if (GetKeyboardPress(DIK_I))
	{// 上昇
		model->move.y += VALUE_MOVE_MODEL * 0.5f;

		if (model->pos.y < 75.0f)
		{
			g_fSizeShadow += 0.2f;
			g_colShadow.a -= 0.004f;
		}
	}
	if (GetKeyboardPress(DIK_K))
	{// 下降
		model->move.y -= VALUE_MOVE_MODEL * 0.5f;
	
		if (model->pos.y > 20.0f)
		{
			g_fSizeShadow -= 0.2f;
			g_colShadow.a += 0.004f;
		}
	}

	if (GetKeyboardTrigger(DIK_L))
	{
		// 玉発射
		D3DXVECTOR3 pos = model->pos;
		evolve_modelbullet(model->shotlv);
	}

}


//****************************************************************************
// 関数名:	void evolve_modelbullet(void)
// 引数:	なし
// 戻り値:	なし
// 説明:	自機のショットレベルに応じて弾の設置方法を変える
//****************************************************************************
void evolve_modelbullet(int shotlv)
{
	MODEL *model = &modelWk[0];
	int lvkakunou;				// 受け取ったレベルを入れておく
	// SetBulletmk2の説明
	// 第4引数　横方向の変化量(プラスで右　マイナスは左)
	// 第5引数　縦方向の変化量(プラスで上　マイナスは下向き)
	// 基本的に小数で指定

	if (shotlv == 0)
	{
		SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE,0, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (shotlv == 1)
	{
		SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE,0, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f));
		SetBulletmk2(D3DXVECTOR3(model->pos.x +3.0f,model->pos.y,model->pos.z), BULLETMK2BASESIZE, BULLETMK2BASESIZE,0, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (shotlv == 2)
	{
		SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE,0, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE,0.1f, 0.01f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE,-0.1f, 0.01f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (shotlv >= 3)
	{
		if(shotlv > 4)
		{
			shotlv = 4;
		}

		for(int no = 0; no < shotlv; no++)
		{
			SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE, 0, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE / 2, 0.2f*(1.5f*no), 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE / 2, -0.2f*(1.5f*no), 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		}
	}
}