//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : HAL�Q�[���w�ȓ�N���ے�1�N�@�R�{�s��
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
// �E�B���h�E
#include "modellife.h"
#include "enemyinfo.h"
#include "pause.h"
#include "bosslife.h"
#include "evolve.h"

// ���f���֘A
#include "model.h"
#include "modelarm.h"
#include "modelbooster.h"
#include "wheel.h"
#include "steam.h"
#include "lockcircle.h"
// ���f���֘A�͂����܂�

// �G
#include "fade.h"
#include "map.h"
#include "hit.h"
#include "bulletmk2.h"
#include "meshfield.h"
#include "enemycontrol.h"
#include "enemywave.h"
#include "boss.h"
// ��������
#include "model_longcheck.h"

#include "score.h"
#include "debugproc.h"
#include "resultscore.h"

#include "enemy.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODELKARISIZE			(100.0f)		// ���f���̉��̃T�C�Y
#define BOSSSIZE			(400.0f)		// �{�X�̉��̃T�C�Y
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CheckHitM_E(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

// �t���O
bool wcheck;
bool pause;					// �|�[�Y��ʒ����ǂ���
bool posset;
bool check;					// ���W����\�����邩�ǂ���
bool wave0set;				// �ŏ��̓G�͔z�u���ꂽ�̂��ǂ���
bool firstbreak;			// �G�͈�̂ł��|���ꂽ�̂��H

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	
	// �t���O������
	wcheck = false;
	pause = false;
	posset = false;
	check = false;
	wave0set = false;

	// score
	InitScore();

	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();


	// �e�̏�����
	InitShadow();

	// �{�X�̏�����
	InitBoss();

	// �e�̏�����

	InitBulletmk2();

	// �{�X�̒e�̏�����
	InitBossbullet();

	//********************************************
	// ���f���̓ǂݍ���(�������܂Ƃ߂��t�@�C������
	//********************************************
	// �{�f�B(�)
	InitModel(model_game);
	// �z�C�[��
	InitWheel();

	// �G
	InitEnemyall();

	// �^�[�Q�b�g�T�[�N���̏�����
	InitLockcircle();

	// �}�b�v�̏���
	InitMap();



	//*************************************************
	//�E�B���h�E(2D)
	//*************************************************

	// ���E�C���h�E������
	InitModellife();
	InitBosslife();
	InitModelevolve();
	// �G��񏉊���
	InitEnemyinfo();
	// �|�[�Y������
	InitPause();

	InitHit();
	// BGM�Đ�
	//PlaySound(SOUND_LABEL_BGM000);

	// �X�`�[��
	InitSteam();

	// �f�o�b�O�\��
	InitDebugProc();

	// �G�̔z�u(�ŏ�)
	// �ŏ��̃��[�v�̏ꍇ
	if (firstwave == false)
	{
		//Setwave_enemy(0);
		//wave0set = true;
		SetShikenkan();
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{

	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	// �e�̏I������
	UninitBulletmk2();

	// �{�X�o���b�g�̏I������
	UninitBossbullet();


	// �e�̏I������
	UninitShadow();

	
	// ���f���̏I������
	UninitModel();
	UninitModelBooster();
	UninitWheel();

	// ���b�N�I���J�[�\���̏I������
	UninitLockcircle();

	// ���j�b�g�̏I������
//	UninitUnit();
	
	//***************************************
	// �E�C���h�E
	//***************************************
	// ���E�C���h�E�̏I��
	UninitModellife();
	UninitBosslife();
	UninitModelevolve();
	// �G�l�~�[���̏I��
	UninitEnemyinfo();

	// �|�[�Y
	UninitPause();

	

	//****************************************
	// �{�X�̏I������
	//****************************************
	UninitBoss();
	//UninitBossarml();
	//UninitBossarmr();

	// �G�̏I��
	UninitEnemyall();

	// �}�b�v�̏I������
	UninitMap();


	// �X�R�A�I��
	UninitScore();

	// BGM��~
	PlaySound(SOUND_LABEL_BGM000);

	// �����[��
	UninitSteam();



	// �f�o�b�O�\��
	UninitDebugProc();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	MODEL *model = GetModel(0);
	MAP *map = GetMap(0);
	XINPUT_STATE state;
	XInputGetState(0, &state);
	// �Q�[���p�b�h�̏�ԕω�
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);



	// �|�[�Y��ʒ��̏���
	if (pause == true)
	{
		if (GetKeyboardTrigger(DIK_P) || keystroke.Flags & XINPUT_KEYSTROKE_KEYDOWN && keystroke.VirtualKey == VK_PAD_START)
		{// �|�[�Y����
			pause = false;
		}
		else if (GetKeyboardTrigger(DIK_R) || state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			pause = false;
			// �^�C�g����ʂ�
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
		// �����蔻��`�F�b�N
		//CheckHit();
	//	CheckHitBB_M();
	//	CheckHitM_E();
		//CheckHitBMk2_Boss();
		//CheckHitBMk2_Bossarmr();


		// �J�����X�V
		UpdateCamera();

		// �e�����̍X�V
		UpdateShadow();


		// ���f���̍X�V
		UpdateModel(model_game);
		UpdateWheel(model_game);


		// �E�B���h�E�X�V
		UpdateEnemyinfo();
		// ���C�t�̍X�V
		UpdateModellife();

		// �G�̍X�V
		UpdateEnemyall();

		//UpdateBoss();

		// �X�R�A�X�V
		UpdateScore();

	}



	// �B���R�}���h
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
// �`�揈��
//=============================================================================
void DrawGame(void)
{

	// �J�����̐ݒ�
	SetCamera();





	// ���f�������̕`��
	DrawModel(model_game);
	DrawWheel();
	DrawLockcircle();


	// �G�̕`��
	DrawEnemyall();


	/////****************
	//// �{�X
	////*****************
	DrawBoss();



	// �e�̕`��
	DrawBulletmk2();

	// �{�X�o���b�g�̕`��
	DrawBossbullet();

	// �e�����̕`��
	DrawShadow();



	// HIT
	DrawHit();

	// �}�b�v�`��
	DrawMap();

	//***********************************************
	// 2D�͓��������𓧖��Ɉڂ����߁A�Ō�ɕ`��
	// 2D�͑S�ČX�̉��ɓ����
	//***********************************************
	// �E�B���h�E
	// �G�l�~�[���`��
	//DrawEnemyinfo();
	// ���E�C���h�E�`��
	//DrawModellife();
	//DrawBosslife();
	//DrawModelevolve();



	// �X�R�A�`��
	DrawScore();

	if (pause == true)
	{
		DrawPause();


	}



	// �}�b�v�`��
	DrawMap();

	if (check == true)
	{
		DrawDebugProc();
	}
}


/*******************************************************************************
�֐���;	void CheckHit(void)
����;	void
�߂�l:	����
����:	�e�ƓG�̓����蔻�菈��
*******************************************************************************/
void CheckHitBMk2_Boss(void)
{
	MODEL *model = GetModel(0);
	ENEMY *enemyWk = GetEnemy(0);							// �؂̃|�C���^�[��������
	BULLETMK2 *bulletmk2 = GetBulletmk2(0);			// �e�̃|�C���^�[��������
	ENEMYLENGTH *enemylength = GetEnemylength(0);
	float bank;


	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletmk2[i].use == false)continue;
		// ��]���邽��Y���̒l�͋C�ɂ��Ȃ�
		for(int no = 0; no < ENEMYMAX; no++)
		{
			if(enemyWk[no].use == true)
			{
				if(CheckHitBC3D(D3DXVECTOR3(enemyWk[no].status.pos.x, model->pos.y, enemyWk[no].status.pos.z), bulletmk2[i].pos, model->center, bulletmk2[i].wide) == true)		//pos pos ���f���̓����蔻��(�G�l�~�[)�@�o���b�g�̃T�C�Y
				{
					SetHit(bulletmk2[i].pos, 100.0f, 50.0f, D3DXCOLOR(1.0f, 0.7f, 0.8f, 0.75f));		// pos,���̑傫��, �c�̑傫��,�F
					bulletmk2[i].use = false;
					ReleaseShadow(bulletmk2[i].g_nIdxShadow);
					enemyWk[no].enemy_life -= 100.0f;
					if(enemyWk[no].enemy_life <= 0.0f)
					{
						//SetFade(FADE_OUT);
						// �e�i���e�X�g
						//model->nowshot_evolve += EVOLVEPOINT_BOSS;	// �i���|�C���g�����Z
						//if (model->nowshot_evolve >= model->shot_evolve)
						//{
							//bank = model->nowshot_evolve - model->shot_evolve;	// ��������l��a����
							//model->nowshot_evolve = 0.0;
						model->shotlv++;
						//}// ���x���A�b�v�ɕK�v�Ȑ��l
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
�֐���;	void CheckHitM_E(void)
����;	void
�߂�l:	����
����:	���@�ƓG�̓����蔻�菈��
*******************************************************************************/
void CheckHitM_E(void)
{
	MODEL *model = GetModel(0);
	ENEMY *enemyWk = GetEnemy(0);							// �G�̃|�C���^�[��������
	ENEMYLENGTH *enemylength = GetEnemylength(0);
	float bank;

		// �G�̐������`�F�b�N
		for(int no = 0; no < ENEMYMAX; no++)
		{
			if(enemyWk[no].use == true)
			{
				// Y���W�������f���̕���ݒ肵�Ă�������!
				// �G�����@�ɏՓ˂����ꍇ
				if(CheckHitBC3D(D3DXVECTOR3(enemyWk[no].status.pos.x, model->pos.y, enemyWk[no].status.pos.z), model->pos, model->center, 8.0f) == true)		//pos pos ���f���̓����蔻��(���a�j,8.0f�̓G�l�~�[�̔��a(�\��)
				{
					//SetHit(bulletmk2[i].pos, 100.0f, 50.0f, D3DXCOLOR(1.0f, 0.7f, 0.8f, 0.75f));		// pos,���̑傫��, �c�̑傫��,�F
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
�֐���;	void CheckHitBB_M(void)
����;	void
�߂�l:	����
����:	�G�̒e�Ǝ��@�̓����蔻�菈��
*******************************************************************************/
void CheckHitBB_M(void)
{
	MODEL *model = GetModel(0);							// �؂̃|�C���^�[��������
	BOSSBULLET *bossbullet = GetBossbullet(0);			// �e�̃|�C���^�[��������
	ENEMY *enemy = GetEnemy(0);

	for (int i = 0; i < BOSSBULLET_MAX; i++)
	{
		if (bossbullet[i].use == false) continue;
		// ��]���邽��Y���̒l�͋C�ɂ��Ȃ�
		if (CheckHitBC3D(D3DXVECTOR3(model[0].pos.x, model[0].pos.y, model[0].pos.z), bossbullet[i].pos, 8.0f, bossbullet[i].wide) == true)		//8.0�̓��f���̓����蔻��(���j
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
�֐���;	void CheckHitM_E(void)
����;	void
�߂�l:	����
����:	�e�Ƃڂ��̓����蔻�菈��
*******************************************************************************/
//void CheckHitM_E(void)
//{
//	MODEL *model = GetModel(0);
//	BOSS *boss = GetBoss(0);						// �{�X�̃|�C���^�[��������
//	BULLETMK2 *bulletmk2 = GetBulletmk2(0);			// �e�̃|�C���^�[��������
//	float bank;
//
//
//	for (int i = 0; i < BOSSBULLET_MAX; i++)
//	{
//		if (bulletmk2[i].use == false)continue;
//		// ��]���邽��Y���̒l�͋C�ɂ��Ȃ�
//		if (CheckHitBC3D(D3DXVECTOR3(boss[0].pos.x, boss[0].pos.y, boss[0].pos.z), bulletmk2[i].pos, BOSSSIZE*0.2, bulletmk2[i].wide) == true)		//pos pos ���f���̓����蔻��(�{�X)�@�o���b�g�̃T�C�Y
//		{
//			SetHit(bulletmk2[i].pos, 100.0f, 50.0f, D3DXCOLOR(1.0f, 0.7f, 0.8f, 0.75f));
//			bulletmk2[i].use = false;
//			ReleaseShadow(bulletmk2[i].g_nIdxShadow);
//			boss->boss_life -= 100.0f;
//			if (boss->boss_life <= 0.0f)
//			{
//				//SetFade(FADE_OUT);
//				// �e�i���e�X�g
//				//model->nowshot_evolve += EVOLVEPOINT_BOSS;	// �i���|�C���g�����Z
//				//if (model->nowshot_evolve >= model->shot_evolve)
//				//{
//				//bank = model->nowshot_evolve - model->shot_evolve;	// ��������l��a����
//				//model->nowshot_evolve = 0.0;
//				model->shotlv++;
//				//}// ���x���A�b�v�ɕK�v�Ȑ��l
//				UninitBoss;
//				//InitBoss;		
//			}
//		}
//	}
//}
/****************************************************************************************
�֐���:	bool CheckHitBC3D(D3DXVECTOR3 pos1,D3DXVECTOR3 pos2,float size1,float size2)
����:	D3DXVECTOR3 pos1,D3DXVECTOR3 pos2,float size1,float size2
�߂�l:	�������Ă����ꍇtrue �����łȂ��Ȃ�false
����:	3D�ł̋��̓����蔻��
*****************************************************************************************/
bool CheckHitBC3D(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	if ((size1 + size2)*(size1 + size2) >= (pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y) + (pos1.z - pos2.z)*(pos1.z - pos2.z))
	{
		return true;			// �������Ă�
	}
	return false;				// �O��
}




