//******************************************************
// �t�@�C����:	hitcheck.cpp
// ����:		�Փ˔���
// �����:		�R�{ �s��
//******************************************************

//�C���N���[�h�t�@�C��
#include "hitcheck.h"
#include "model.h"
#include "bulletmk2.h"
#include "enemy.h"

//*******************************************************
// �v���g�^�C�v�錾
//*******************************************************


//*******************************************************
// �֐���:	void checkBB_bullet_enemy(void)

// ����:	�v���C���[�̒e�ƓG���Փ˂��Ă��邩���肵����
//*******************************************************
void checkBB_bullet_enemy(void)
{
	BULLETMK2 *bulletmk2 = GetBulletmk2(0);
	ENEMY *enemy = GetEnemy(0);
	MODEL *model = GetModel(0);

	for(int no= 0;no < BULLET_MAX;no++)
	{
		if(bulletmk2[no].use == false)
		{	// �g���Ă��Ȃ���ΏI������
			continue;
		}
		for(int i = 0; i < ENEMYMAX;i++)
		{
			if(enemy[i].use == true)
			{
				// model->center�͓G���f���̒��S�܂ł̒���
				//if(CheckHitBC3D(enemy[i].status.pos,bulletmk2[i].pos,model->center,bulletmk2[i].wide))
			}

		}
	}
}




/****************************************************************************************
�֐���:	bool CheckHitBC3D(D3DXVECTOR3 pos1,D3DXVECTOR3 pos2,float size1,float size2)
����:	D3DXVECTOR3 pos1,D3DXVECTOR3 pos2,float size1,float size2
�߂�l:	�������Ă����ꍇtrue �����łȂ��Ȃ�false
����:	3D���f�����m�̋��̓����蔻��
*****************************************************************************************/
//bool CheckHitBC3D(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
//{
//	if((size1 + size2)*(size1 + size2) >= (pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y) + (pos1.z - pos2.z)*(pos1.z - pos2.z))
//	{
//		return true;			// �������Ă�
//	}
//	return false;				// �O��
//}
//
//
//
//
