//****************************************************
// �t�@�C����:	enemywave.cpp
// �쐬��:		�R�{ �s��
// ����:		�G�̏o���ʒu�Ǘ��̃v���O����
//****************************************************

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "enemywave.h"
#include "model.h"
#include "time.h"

//****************************************************
// �}�N����`
//****************************************************
#define WAVE1Z	(100.0f)
#define WAVE1X	(100.0f)

#define RASHPOS	(100.0f)


// �eWAVE�̓G�o����
#define WAVE2 (3)

// �G�̍ő�l
#define ENEMY_MAX (100)
#define ENEMY_RASHMAX	(10)
//****************************************************
// �O���[�o���ϐ�
//****************************************************

int enemy_rashcount;			// �G�l�~�[���b�V���̃J�E���g
int enemyrash_pos;
bool firstflag;					// �ŏ��ɓ��������ǂ����̃t���O
//****************************************************
//	�v���g�^�C�v�錾
//***************************************************
void enemy_rash(int no);


//****************************************************
// �֐���:	void Setwave_enemy(int lv)
// ����;	int�^��lv
// ����:	�i�����x���ɉ����ēG�̏o�����y�шʒu��ω�
// ����:	���̊֐���wave���オ��������Ɏg��
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
		// 0�Ȃ珉����
		enemy_rashcount = 0;
		enemyrash_pos = 0;
		firstflag = false;
		CreateEnemy(D3DXVECTOR3(model->pos.x, length->enemycenter, WAVE1Z));
		CreateEnemy(D3DXVECTOR3(model->pos.x+((length->enemycenter*5)+WAVE1X), length->enemycenter, WAVE1Z));
		CreateEnemy(D3DXVECTOR3(model->pos.x-( (length->enemycenter*5)+WAVE1X), length->enemycenter, WAVE1Z));
	}


	// ���̃E�F�[�u����̓}�b�v�̉�����X�^�[�g������
	// WAVE2

	else if(lv >= 1)
	{
		enemy_rashcount++;
		enemy_rash(enemy_rashcount);
		
	}







}

//******************************************************************
// �֐���;	void enemy_rash(int no)
// ����:	int no
// �߂�l:	void
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
	// no�̐������G��z�u
	for(int i = 0; i < no; i++)
	{
		rash_pop = enemyrash_pos % 10;			// 1�P�^�ڂ𕪊�ɗ��p
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
		// �z�u�����玟�̈ʒu��
		if(enemyrash_pos > 8)
		{
			enemyrash_pos = 0;
		}
	}
}