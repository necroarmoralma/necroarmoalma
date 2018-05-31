//******************************************************
// ファイル名:	hitcheck.cpp
// 説明:		衝突判定
// 制作者:		山本 壮将
//******************************************************

//インクルードファイル
#include "hitcheck.h"
#include "model.h"
#include "bulletmk2.h"
#include "enemy.h"

//*******************************************************
// プロトタイプ宣言
//*******************************************************


//*******************************************************
// 関数名:	void checkBB_bullet_enemy(void)

// 説明:	プレイヤーの弾と敵が衝突しているか判定し処理
//*******************************************************
void checkBB_bullet_enemy(void)
{
	BULLETMK2 *bulletmk2 = GetBulletmk2(0);
	ENEMY *enemy = GetEnemy(0);
	MODEL *model = GetModel(0);

	for(int no= 0;no < BULLET_MAX;no++)
	{
		if(bulletmk2[no].use == false)
		{	// 使われていなければ終了する
			continue;
		}
		for(int i = 0; i < ENEMYMAX;i++)
		{
			if(enemy[i].use == true)
			{
				// model->centerは敵モデルの中心までの長さ
				//if(CheckHitBC3D(enemy[i].status.pos,bulletmk2[i].pos,model->center,bulletmk2[i].wide))
			}

		}
	}
}




/****************************************************************************************
関数名:	bool CheckHitBC3D(D3DXVECTOR3 pos1,D3DXVECTOR3 pos2,float size1,float size2)
引数:	D3DXVECTOR3 pos1,D3DXVECTOR3 pos2,float size1,float size2
戻り値:	当たっていた場合true そうでないならfalse
説明:	3Dモデル同士の球の当たり判定
*****************************************************************************************/
//bool CheckHitBC3D(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
//{
//	if((size1 + size2)*(size1 + size2) >= (pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y) + (pos1.z - pos2.z)*(pos1.z - pos2.z))
//	{
//		return true;			// 当たってる
//	}
//	return false;				// 外れ
//}
//
//
//
//
