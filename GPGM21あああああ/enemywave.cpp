//****************************************************
// ファイル名:	enemywave.cpp
// 作成者:		山本 壮将
// 説明:		敵の出現位置管理のプログラム
//****************************************************

//****************************************************
// インクルードファイル
//****************************************************
#include "enemywave.h"
#include "model.h"
#include "time.h"

//****************************************************
// マクロ定義
//****************************************************
#define WAVE1Z	(100.0f)
#define WAVE1X	(100.0f)

#define RASHPOS	(100.0f)


// 各WAVEの敵出現数
#define WAVE2 (3)

// 敵の最大値
#define ENEMY_MAX (100)
#define ENEMY_RASHMAX	(10)
//****************************************************
// グローバル変数
//****************************************************

int enemy_rashcount;			// エネミーラッシュのカウント
int enemyrash_pos;
bool firstflag;					// 最初に入ったかどうかのフラグ
//****************************************************
//	プロトタイプ宣言
//***************************************************
void enemy_rash(int no);


//****************************************************
// 関数名:	void Setwave_enemy(int lv)
// 引数;	int型のlv
// 説明:	進化レベルに応じて敵の出現数及び位置を変化
// 説明:	この関数はwaveが上がった直後に使う
//****************************************************
void Setwave_enemy(int lv)
{
	ENEMYLENGTH *length = GetEnemylength(0);
	MODEL *model = GetModel(0);
	srand((unsigned int)time(NULL));
	int pos = (rand() % 10);
	int pop = (rand() % 4 + 1);

	if (lv == 0)
	{
		// 0なら初期化
		enemy_rashcount = 0;
		enemyrash_pos = 0;
		firstflag = false;
		CreateEnemy(D3DXVECTOR3(model->pos.x, length->enemycenter, WAVE1Z));
		CreateEnemy(D3DXVECTOR3(model->pos.x+((length->enemycenter*5)+WAVE1X), length->enemycenter, WAVE1Z));
		CreateEnemy(D3DXVECTOR3(model->pos.x-( (length->enemycenter*5)+WAVE1X), length->enemycenter, WAVE1Z));
	}


	// 次のウェーブからはマップの奥からスタートさせる
	// WAVE2

	else if(lv >= 1)
	{
		enemy_rashcount++;
		enemy_rash(enemy_rashcount);
		
	}







}

//******************************************************************
// 関数名;	void enemy_rash(int no)
// 引数:	int no
// 戻り値:	void
//******************************************************************
void enemy_rash(int no)
{
	ENEMYLENGTH *length = GetEnemylength(0);
	MODEL *model = GetModel(0);

	srand((unsigned int)time(NULL));
	int pos = (rand() % 10);
	int pop = (rand() % 4 + 1);
	int enemy = 1.5;
	int rash_pop;

	if(firstflag == false)
	{
		rash_pop = 0;
		firstflag = true;
	}
	
	// 360/9 = 40
	// noの数だけ敵を配置
	for(int i = 0; i < no; i++)
	{
		rash_pop = enemyrash_pos % 10;			// 1ケタ目を分岐に利用
		enemyrash_pos++;

		switch(rash_pop)
		{
		case 0:
			CreateEnemy(D3DXVECTOR3(0.0f,
				length->enemycenter,
				length->map_zmax));
				break;
		case 1:
			CreateEnemy(D3DXVECTOR3(length->map_zmax,
				length->enemycenter,
				length->map_zmax));
			break;

		case 2:
			CreateEnemy(D3DXVECTOR3(0.0f,
				length->enemycenter,
				length->map_zmax));
			break;

		case 3:
			CreateEnemy(D3DXVECTOR3(length->map_zmax,
				length->enemycenter,
				-length->map_zmax));
			break;

		case 4:
			CreateEnemy(D3DXVECTOR3(0.0f,
				length->enemycenter,
				-length->map_zmax));
			break;

		case 5:
			CreateEnemy(D3DXVECTOR3(-length->map_zmax,
				length->enemycenter,
				-length->map_zmax));
			break;

		case 6:
			CreateEnemy(D3DXVECTOR3(-length->map_zmax,
				length->enemycenter,
				0.0f));
			break;

		case 7:
			CreateEnemy(D3DXVECTOR3(-length->map_zmax,
				length->enemycenter,
				+length->map_zmax));
			break;

		case 8:
			CreateEnemy(D3DXVECTOR3(length->map_zmax,
				length->enemycenter,
				0.0f));
			break;

			
		}
		// 配置したら次の位置へ
		if(enemyrash_pos > 8)
		{
			enemyrash_pos = 0;
		}
	}
}