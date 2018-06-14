//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : HALゲーム学科二年生課程1年　山本壮将
//
//=============================================================================
#include "input.h"
#include "game.h"
#include "light.h"
#include "camera.h"
#include "shadow.h"
#include "sound.h"
#include "unit.h"
#include "bossbullet.h"
//#include "boss.h"
// ウィンドウ
#include "modellife.h"
#include "enemyinfo.h"
#include "pause.h"
#include "bosslife.h"
#include "evolve.h"

// モデル関連
#include "model.h"
#include "modelarm.h"
#include "modelbooster.h"
#include "wheel.h"
#include "steam.h"
#include "lockcircle.h"
// モデル関連はここまで

// 敵
#include "fade.h"
#include "map.h"
#include "hit.h"
#include "bulletmk2.h"
#include "meshfield.h"
#include "enemycontrol.h"
#include "enemywave.h"
#include "boss.h"
// 長さ測定
#include "model_longcheck.h"

#include "score.h"
#include "debugproc.h"
#include "resultscore.h"

#include "enemy.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODELKARISIZE			(100.0f)		// モデルの仮のサイズ
#define BOSSSIZE			(400.0f)		// ボスの仮のサイズ
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CheckHitM_E(void);
//*****************************************************************************
// グローバル変数
//*****************************************************************************

// フラグ
bool wcheck;
bool pause;					// ポーズ画面中かどうか
bool posset;
bool check;					// 座標等を表示するかどうか
bool wave0set;				// 最初の敵は配置されたのかどうか
bool firstbreak;			// 敵は一体でも倒されたのか？

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	
	// フラグ初期化
	wcheck = false;
	pause = false;
	posset = false;
	check = false;
	wave0set = false;

	// score
	InitScore();

	// ライトの初期化
	InitLight();

	// カメラの初期化
	InitCamera();


	// 影の初期化
	InitShadow();

	// ボスの初期化
	InitBoss();

	// 弾の初期化

	InitBulletmk2();

	// ボスの弾の初期化
	InitBossbullet();

	//********************************************
	// モデルの読み込み(これらをまとめたファイルつくる
	//********************************************
	// ボディ(基準)
	InitModel(model_game);
	// ホイール
	InitWheel();

	// 敵
	InitEnemyall();

	// ターゲットサークルの初期化
	InitLockcircle();

	// マップの初期
	InitMap();



	//*************************************************
	//ウィンドウ(2D)
	//*************************************************

	// 情報ウインドウ初期化
	InitModellife();
	InitBosslife();
	InitModelevolve();
	// 敵情報初期化
	InitEnemyinfo();
	// ポーズ初期化
	InitPause();

	InitHit();
	// BGM再生
	//PlaySound(SOUND_LABEL_BGM000);

	// スチーム
	InitSteam();

	// デバッグ表示
	InitDebugProc();

	// 敵の配置(最初)
	// 最初のループの場合
	if (firstwave == false)
	{
		//Setwave_enemy(0);
		//wave0set = true;
		SetShikenkan();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{

	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	// 弾の終了処理
	UninitBulletmk2();

	// ボスバレットの終了処理
	UninitBossbullet();


	// 影の終了処理
	UninitShadow();

	
	// モデルの終了処理
	UninitModel();
	UninitModelBooster();
	UninitWheel();

	// ロックオンカーソルの終了処理
	UninitLockcircle();

	// ユニットの終了処理
//	UninitUnit();
	
	//***************************************
	// ウインドウ
	//***************************************
	// 情報ウインドウの終了
	UninitModellife();
	UninitBosslife();
	UninitModelevolve();
	// エネミー情報の終了
	UninitEnemyinfo();

	// ポーズ
	UninitPause();

	

	//****************************************
	// ボスの終了処理
	//****************************************
	UninitBoss();
	//UninitBossarml();
	//UninitBossarmr();

	// 敵の終了
	UninitEnemyall();

	// マップの終了処理
	UninitMap();


	// スコア終了
	UninitScore();

	// BGM停止
	PlaySound(SOUND_LABEL_BGM000);

	// すちーむ
	UninitSteam();



	// デバッグ表示
	UninitDebugProc();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	MODEL *model = GetModel(0);
	MAP *map = GetMap(0);
	XINPUT_STATE state;
	XInputGetState(0, &state);
	// ゲームパッドの状態変化
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);



	// ポーズ画面中の処理
	if (pause == true)
	{
		if (GetKeyboardTrigger(DIK_P) || keystroke.Flags & XINPUT_KEYSTROKE_KEYDOWN && keystroke.VirtualKey == VK_PAD_START)
		{// ポーズ解除
			pause = false;
		}
		else if (GetKeyboardTrigger(DIK_R) || state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			pause = false;
			// タイトル画面に
			UninitGame();
		}
	}
	else if (pause == false && posset == false)
	{
		if (GetKeyboardTrigger(DIK_P) || keystroke.Flags & XINPUT_KEYSTROKE_KEYDOWN && keystroke.VirtualKey == VK_PAD_START)
		{
			pause = true;
		}
	}
	
	
	if (pause == false)
	{
		// 当たり判定チェック
		//CheckHit();
	//	CheckHitBB_M();
	//	CheckHitM_E();
		//CheckHitBMk2_Boss();
		//CheckHitBMk2_Bossarmr();


		// カメラ更新
		UpdateCamera();

		// 影処理の更新
		UpdateShadow();


		// モデルの更新
		UpdateModel(model_game);
		UpdateWheel(model_game);


		// ウィンドウ更新
		UpdateEnemyinfo();
		// ライフの更新
		UpdateModellife();

		// 敵の更新
		UpdateEnemyall();

		//UpdateBoss();

		// スコア更新
		UpdateScore();

	}



	// 隠しコマンド
	if (GetKeyboardPress(DIK_H))
	{
		model->shotlv++;
	}

	if (GetKeyboardPress(DIK_4))
	{
		Setwave_enemy(0);
	}


	if (GetKeyboardPress(DIK_5))
	{
		if (check == false)
		{
			check = true;
		}

		else
		{
			check = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{

	// カメラの設定
	SetCamera();





	// モデル処理の描画
	DrawModel(model_game);
	DrawWheel();
	DrawLockcircle();


	// 敵の描画
	DrawEnemyall();


	/////****************
	//// ボス
	////*****************
	DrawBoss();



	// 弾の描画
	DrawBulletmk2();

	// ボスバレットの描画
	DrawBossbullet();

	// 影処理の描画
	DrawShadow();



	// HIT
	DrawHit();

	// マップ描画
	DrawMap();

	//***********************************************
	// 2Dは透明部分を透明に移すため、最後に描画
	// 2Dは全て個々の下に入れる
	//***********************************************
	// ウィンドウ
	// エネミー情報描画
	//DrawEnemyinfo();
	// 情報ウインドウ描画
	//DrawModellife();
	//DrawBosslife();
	//DrawModelevolve();



	// スコア描画
	DrawScore();

	if (pause == true)
	{
		DrawPause();


	}



	// マップ描画
	DrawMap();

	if (check == true)
	{
		DrawDebugProc();
	}
}


/*******************************************************************************
関数名;	void CheckHit(void)
引数;	void
戻り値:	無し
説明:	弾と敵の当たり判定処理
*******************************************************************************/
void CheckHitBMk2_Boss(void)
{
	MODEL *model = GetModel(0);
	ENEMY *enemyWk = GetEnemy(0);							// 木のポインターを初期化
	BULLETMK2 *bulletmk2 = GetBulletmk2(0);			// 弾のポインターを初期化
	ENEMYLENGTH *enemylength = GetEnemylength(0);
	float bank;


	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletmk2[i].use == false)continue;
		// 回転するためY軸の値は気にしない
		for(int no = 0; no < ENEMYMAX; no++)
		{
			if(enemyWk[no].use == true)
			{
				if(CheckHitBC3D(D3DXVECTOR3(enemyWk[no].status.pos.x, model->pos.y, enemyWk[no].status.pos.z), bulletmk2[i].pos, model->center, bulletmk2[i].wide) == true)		//pos pos モデルの当たり判定(エネミー)　バレットのサイズ
				{
					SetHit(bulletmk2[i].pos, 100.0f, 50.0f, D3DXCOLOR(1.0f, 0.7f, 0.8f, 0.75f));		// pos,横の大きさ, 縦の大きさ,色
					bulletmk2[i].use = false;
					ReleaseShadow(bulletmk2[i].g_nIdxShadow);
					enemyWk[no].enemy_life -= 100.0f;
					if(enemyWk[no].enemy_life <= 0.0f)
					{
						//SetFade(FADE_OUT);
						// 弾進化テスト
						//model->nowshot_evolve += EVOLVEPOINT_BOSS;	// 進化ポイントを加算
						//if (model->nowshot_evolve >= model->shot_evolve)
						//{
							//bank = model->nowshot_evolve - model->shot_evolve;	// いったん値を預かる
							//model->nowshot_evolve = 0.0;
						model->shotlv++;
						//}// レベルアップに必要な数値
						DeleatEnemy(no);
						ChangeScore(1);
						//InitBoss;		
						Setwave_enemy(model->shotlv);
					}
				}
			}
		}
	}
}

/*******************************************************************************
関数名;	void CheckHitM_E(void)
引数;	void
戻り値:	無し
説明:	自機と敵の当たり判定処理
*******************************************************************************/
void CheckHitM_E(void)
{
	MODEL *model = GetModel(0);
	ENEMY *enemyWk = GetEnemy(0);							// 敵のポインターを初期化
	ENEMYLENGTH *enemylength = GetEnemylength(0);
	float bank;

		// 敵の数だけチェック
		for(int no = 0; no < ENEMYMAX; no++)
		{
			if(enemyWk[no].use == true)
			{
				// Y座標だけモデルの物を設定してください!
				// 敵が自機に衝突した場合
				if(CheckHitBC3D(D3DXVECTOR3(enemyWk[no].status.pos.x, model->pos.y, enemyWk[no].status.pos.z), model->pos, model->center, 8.0f) == true)		//pos pos モデルの当たり判定(半径）,8.0fはエネミーの半径(予定)
				{
					//SetHit(bulletmk2[i].pos, 100.0f, 50.0f, D3DXCOLOR(1.0f, 0.7f, 0.8f, 0.75f));		// pos,横の大きさ, 縦の大きさ,色
					DeleatEnemy(no);
					model->Nowlife -= 10.0f;
					Setwave_enemy(model->shotlv);
					if(model->Nowlife <= 0.0f)
					{
						SetFade(FADE_OUT);
					}

				}
			}
		}
	
}


/*******************************************************************************
関数名;	void CheckHitBB_M(void)
引数;	void
戻り値:	無し
説明:	敵の弾と自機の当たり判定処理
*******************************************************************************/
void CheckHitBB_M(void)
{
	MODEL *model = GetModel(0);							// 木のポインターを初期化
	BOSSBULLET *bossbullet = GetBossbullet(0);			// 弾のポインターを初期化
	ENEMY *enemy = GetEnemy(0);

	for (int i = 0; i < BOSSBULLET_MAX; i++)
	{
		if (bossbullet[i].use == false) continue;
		// 回転するためY軸の値は気にしない
		if (CheckHitBC3D(D3DXVECTOR3(model[0].pos.x, model[0].pos.y, model[0].pos.z), bossbullet[i].pos, 8.0f, bossbullet[i].wide) == true)		//8.0はモデルの当たり判定(仮）
		{
			SetHit(bossbullet[i].pos, 50.0f, 25.0f, D3DXCOLOR(1.0f, 0.7f, 0.8f, 0.55f));
			bossbullet[i].use = false;
			ReleaseShadow(bossbullet[i].g_nIdxShadow);
			model->Nowlife -= 10.0f;
			if (model->Nowlife <= 0.0f)
			{
				SetFade(FADE_OUT);
			}
		}


	}
}


/*******************************************************************************
関数名;	void CheckHitM_E(void)
引数;	void
戻り値:	無し
説明:	弾とぼすの当たり判定処理
*******************************************************************************/
//void CheckHitM_E(void)
//{
//	MODEL *model = GetModel(0);
//	BOSS *boss = GetBoss(0);						// ボスのポインターを初期化
//	BULLETMK2 *bulletmk2 = GetBulletmk2(0);			// 弾のポインターを初期化
//	float bank;
//
//
//	for (int i = 0; i < BOSSBULLET_MAX; i++)
//	{
//		if (bulletmk2[i].use == false)continue;
//		// 回転するためY軸の値は気にしない
//		if (CheckHitBC3D(D3DXVECTOR3(boss[0].pos.x, boss[0].pos.y, boss[0].pos.z), bulletmk2[i].pos, BOSSSIZE*0.2, bulletmk2[i].wide) == true)		//pos pos モデルの当たり判定(ボス)　バレットのサイズ
//		{
//			SetHit(bulletmk2[i].pos, 100.0f, 50.0f, D3DXCOLOR(1.0f, 0.7f, 0.8f, 0.75f));
//			bulletmk2[i].use = false;
//			ReleaseShadow(bulletmk2[i].g_nIdxShadow);
//			boss->boss_life -= 100.0f;
//			if (boss->boss_life <= 0.0f)
//			{
//				//SetFade(FADE_OUT);
//				// 弾進化テスト
//				//model->nowshot_evolve += EVOLVEPOINT_BOSS;	// 進化ポイントを加算
//				//if (model->nowshot_evolve >= model->shot_evolve)
//				//{
//				//bank = model->nowshot_evolve - model->shot_evolve;	// いったん値を預かる
//				//model->nowshot_evolve = 0.0;
//				model->shotlv++;
//				//}// レベルアップに必要な数値
//				UninitBoss;
//				//InitBoss;		
//			}
//		}
//	}
//}
/****************************************************************************************
関数名:	bool CheckHitBC3D(D3DXVECTOR3 pos1,D3DXVECTOR3 pos2,float size1,float size2)
引数:	D3DXVECTOR3 pos1,D3DXVECTOR3 pos2,float size1,float size2
戻り値:	当たっていた場合true そうでないならfalse
説明:	3Dでの球の当たり判定
*****************************************************************************************/
bool CheckHitBC3D(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	if ((size1 + size2)*(size1 + size2) >= (pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y) + (pos1.z - pos2.z)*(pos1.z - pos2.z))
	{
		return true;			// 当たってる
	}
	return false;				// 外れ
}




