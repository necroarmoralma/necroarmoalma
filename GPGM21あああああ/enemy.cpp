//=============================================================================
//
// ���f������ [enemy.cpp]
//  Author : HAL�Q�[���w�ȓ�N���ے�1�N�@�R�{�s��
// 
//=============================================================================
#include "enemy.h"
#include "shadow.h"
#include "bossbullet.h"
#include "model.h"
#include "enemycontrol.h"
#include "map.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ENEMY_AIRPLANE		"data/MODEL/enemypod.x"	// �ǂݍ��ރ��f����
#define	VALUE_MOVE_ENEMY	(0.80f)						// �ړ����x
#define	RATE_MOVE_ENEMY		(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_ENEMY	(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_ENEMY	(0.20f)						// ��]�����W��
#define	ENEMY_BULLET_SIZEX		(20.0f)						// �e�̑傫����lX
#define ENEMY_BULLET_SIZEY		(20.0f)						// �e�̑傫����lY
#define SPEEDSETTING_ENEMY	()						// �{�X��XZ���ʏ�ŉ�]����Ƃ��̒���
#define ENEMYSPEED			(1.1f)
#define ENEMYMODE			(1.57f)					// ����؂�ւ����s�����]�l
// �e���[�h�̒e�̑傫���@X���������@Y���c����
//�@DEBIRU�̒e
#define ENEMYBULLET_1_SIZE_X	(10.0f)
#define ENEMYBULLET_1_SIZE_Y	(10.0f)

#define ENEMY_SHOTACT			(1*60)		// �b���~FPS

#define VALUE_MOVE_ENEMY		(0.5f)
#define ENEMYKANKAKUPLUS		(4.0f)// �G�̊Ԋu�����ꂾ��������

// ������
#define SHIKENKAN_NINZU			(3)			// �����ǂ̐l��

// �����]��(�w��Ɏg��
#define	HIDARI	(1.57f)
#define	MIGI	(-1.57f)
#define	UE		(0.0f)
#define	SHITA	(3.57f)


// ���u��
#define ENEMY_HANKEI	(20.0f)			//	�G�l�~�[�̔��a


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CheckEnemypos(D3DXVECTOR3 pos, int enemyno);
void enemy_RaypickTomap(void);
void move_change(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	TextureEnemy;			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			MeshEnemy;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		BuffMatEnemy;		// ���b�V���̃}�e���A�������i�[
DWORD				NumMatEnemy;				// �������̑���
												
int					enemynidxShadow;				// �eID
float				enemysizeShadow;				// �e�̃T�C�Y
D3DXCOLOR			enemycolShadow;				// �e�̐F
D3DXVECTOR3			ENEMYBASEPOS(0.0f, 0.0f, 5.0f);
ENEMY				enemyWk[ENEMYMAX];					// ���f���\����(���f���͂P�j
float				enemyActtime;				// �{�X���s�����銴�o



int no = 0;
//=============================================================================
// �G�̏�����
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 rotCamera;

	// ���f���̏�����
	MeshEnemy = NULL;
	BuffMatEnemy = NULL;
	NumMatEnemy = NULL;

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(ENEMY_AIRPLANE,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&BuffMatEnemy,
		NULL,
		&NumMatEnemy,
		&MeshEnemy)))
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTextureEnemy);	// �ǂݍ��ރ������[
#endif

	// �\���̑S�Ă̏��������s��

	for (int no=0; no < ENEMYMAX; no++)
	{
		
		// �e�̐���
		enemynidxShadow = CreateShadow(enemyWk[no].status.pos, 25.0f, 25.0f);

		// ������
		enemyWk[no].status.BuffMatModel = NULL;
		enemyWk[no].status.NumMatModel = NULL;
		enemyWk[no].status.MeshModel = NULL;

		// �ŏ��ɓǂݍ��񂾃��f����K�p
		enemyWk[no].status.BuffMatModel = BuffMatEnemy;
		enemyWk[no].status.NumMatModel = NumMatEnemy;
		enemyWk[no].status.MeshModel = MeshEnemy;

		enemysizeShadow = 25.0f;
		enemycolShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		enemyWk[no].use = false;
		enemyWk[no].acttime = ENEMY_SHOTACT;
	}
	return S_OK;
}




//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{

	for (int no = 0; no < ENEMYMAX; no++)
	{
		if (enemyWk[no].use == true)
		{
			if (enemyWk[no].status.TextureModel != NULL)
			{// �e�N�X�`���̊J��
				enemyWk[no].status.TextureModel->Release();
				enemyWk[no].status.TextureModel = NULL;
			}

			if (enemyWk[no].status.MeshModel != NULL)
			{// ���b�V���̊J��
				enemyWk[no].status.MeshModel->Release();
				enemyWk[no].status.MeshModel = NULL;
			}

			if (enemyWk[no].status.BuffMatModel != NULL)
			{// �}�e���A���̊J��
				enemyWk[no].status.BuffMatModel->Release();
				enemyWk[no].status.BuffMatModel = NULL;
			}
		}
	}
}

//*****************************************************************************
// ��������
//*****************************************************************************
void DeleatEnemy(int no)
{
		enemyWk[no].use = false;
	
}



//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	for (int no=0; no < ENEMYMAX; no++)
	{
		if (enemyWk[no].use == true)
		{
			D3DXVECTOR3 rotCamera;
			ENEMY *enemy = &enemyWk[0];
			MODEL *model = GetModel(0);
			float fDiffRotY;
			D3DXVECTOR3 SubposEnemytoModel;
			float rotcheckEtoM;


			if (GetKeyboardTrigger(DIK_Z))
			{
				if (enemyWk[no].warning == false)
				{
					enemyWk[no].warning = true;
				}

				else
				{
					enemyWk[no].warning = false;
				}
			}

			// �x����ԂȂ�v���C���[�̕��֌�����
			if (enemyWk[no].warning == true)
			{
				// �ڕW-����
				rotcheckEtoM = atan2f((model->pos.x - enemyWk[no].status.pos.x), (model->pos.z - enemyWk[no].status.pos.z)) + D3DX_PI;
				enemyWk[no].status.rot.y = rotcheckEtoM;	// �v���C���[�̕�������������
			}

			enemy_RaypickTomap();
			move_change();

			// �s��
			// ����o�����Ԃ�
			enemyWk[no].acttime--;		//�@�f�N�������g�ł��������H1�t���[����1���炵��

			if (enemyWk[no].acttime <= 0.0f)

			// �d���`�F�b�N
			{	// 0�Ȃ���s���鏈��
				// �e�̔���
			//	SetEnemybullet(enemyWk[no].status.pos, ENEMYBULLET_1_SIZE_X, ENEMYBULLET_1_SIZE_Y, D3DXCOLOR(1.0f, 0.7f, 0.8f, 0.75f), enemyWk[no].status.rot.y);
				enemyWk[no].acttime = ENEMYACT;
			}



			// �����Ă�������ֈړ�����

			// �ړ��ʂ̌���
			enemyWk[no].status.move.x += sinf(D3DX_PI + enemyWk[no].status.rot.y) * VALUE_MOVE_ENEMY;
			enemyWk[no].status.move.z += cosf(D3DX_PI + enemyWk[no].status.rot.y) * VALUE_MOVE_ENEMY;
			CheckEnemypos(enemyWk[no].status.pos, no);

			enemyWk[no].status.pos.x += enemyWk[no].status.move.x;
			enemyWk[no].status.pos.z += enemyWk[no].status.move.z;

			enemyWk[no].status.move.x += (0.0f - enemyWk[no].status.move.x) * RATE_MOVE_MODEL;
			enemyWk[no].status.move.z += (0.0f - enemyWk[no].status.move.z) * RATE_MOVE_MODEL;

			
			// �e�̈ʒu�ݒ�
			SetPositionShadow(enemynidxShadow, D3DXVECTOR3(enemyWk[no].status.pos.x, 0.1f, enemyWk[no].status.pos.z));

			SetVertexShadow(enemynidxShadow, enemysizeShadow, enemysizeShadow);
			SetColorShadow(enemynidxShadow, enemycolShadow);



			//�@�����̐���
			//enemyWk[no].status.rot.y = MIGI;

			// ��]����
			enemyWk[no].movesetting += 0.01f;

			// �s���J�E���g�����炷
			enemyWk[no].acttime--;
		}
	}
	
}
 
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	for (int no = 0; no < ENEMYMAX; no++)
	{
		if (enemyWk[no].use == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&enemyWk[no].status.World);


			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, enemyWk[no].status.scl.x, enemyWk[no].status.scl.y, enemyWk[no].status.scl.z);
			D3DXMatrixMultiply(&enemyWk[no].status.World, &enemyWk[no].status.World, &mtxScl);


			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, enemyWk[no].status.rot.y, enemyWk[no].status.rot.x, enemyWk[no].status.rot.z);
			D3DXMatrixMultiply(&enemyWk[no].status.World, &enemyWk[no].status.World, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, enemyWk[no].status.pos.x, enemyWk[no].status.pos.y, enemyWk[no].status.pos.z);
			D3DXMatrixMultiply(&enemyWk[no].status.World, &enemyWk[no].status.World, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &enemyWk[no].status.World);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)enemyWk[no].status.BuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)enemyWk[no].status.NumMatModel; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, enemyWk[no].status.TextureModel);

				// �`��
				enemyWk[no].status.MeshModel->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionEnemy(int no)
{
	ENEMY *enemy = &enemyWk[0];
	return enemyWk[no].status.pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationEnemy(int no)
{
	ENEMY *enemy = &enemyWk[no];
	return enemyWk[no].status.rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestEnemy(int no)
{
	ENEMY *enemy = &enemyWk[no];
	return enemyWk[no].status.rotDest;
}

//*****************************************************************************
// �Q�b�g�֐�
//*****************************************************************************
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}

//******************************************************************************
// �֐���:	HRESULT CreateEnemy(void)
// ����:	�Ȃ�
// �߂�l:	����I���@HRESULT�^��S_OK
// ����:	�G��z�u
//******************************************************************************
void CreateEnemy(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int createno;	// �ݒ肷��\���̂̔ԍ�

	for (int no = 0; no < ENEMYMAX; no++)
	{
		if (enemyWk[no].use == false)		// ���g�p�݂�����
		{
			enemyWk[no].use = true;
			// ��Ԃ̏�����
			enemyWk[no].warning = false;	// �x����Ԃł͂Ȃ�
			// HP�̐ݒ�
			enemyWk[no].enemy_maxlife = ENEMYLIFE;
			enemyWk[no].enemy_life = enemyWk[no].enemy_maxlife;



			enemyWk[no].status.pos = pos;
			enemyWk[no].status.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemyWk[no].status.puremove = enemyWk[no].status.move;
			enemyWk[no].status.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemyWk[no].status.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			enemyWk[no].status.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			enemyWk[no].acttime = ENEMYACT;


			// ���쐧��ɕK�v�Ȓl��ݒ�
			enemyWk[no].movesetting = 0.0f;
			enemyWk[no].movemode = SHOT;
			break;
		}
	}
}

//******************************************************************************
// �֐���:	void CheckEnemypos(D3DXVECTOR3 pos,int no)
// ����:	D3DXVECTOR3 pos,int no
// �߂�l:	�Ȃ�
// ����:	�G���m�̊Ԋu�������Ă��ɂ�����
//******************************************************************************
void CheckEnemypos(D3DXVECTOR3 pos, int enemyno)
{
	ENEMYLENGTH *enemylength = GetEnemylength(0);
	float lengthcheck;	// �����ɋ������i�[

	lengthcheck = (enemylength->enemycenter * 2);

	for(int no = 0; no < ENEMYMAX; no++)
	{
		if(enemyWk[no].use == true && no != enemyno)
		{
			if(((enemyWk[no].status.pos.x - pos.x)*(enemyWk[no].status.pos.x - pos.x)) + ((enemyWk[no].status.pos.z - pos.z)*(enemyWk[no].status.pos.z - pos.z))
				<= ((lengthcheck)*(lengthcheck)))
			{
				enemyWk[no].status.move.x = 0.0f;
				enemyWk[no].status.move.z = 0.0f;
			}
		}
	}
}


//******************************************************************************
//	�֐���:	void SetShikenkan(void)
//	����:	��΂�
//	�߂�l:	�Ȃ�
//	����:	�����ǂ̔z�u
//*******************************************************************************
void SetShikenkan(void)
{
	ENEMYLENGTH *length = GetEnemylength(0);
	MODEL *model = GetModel(0);
	
	//int pos = (rand() % 10);
	//int pop = (rand() % 4 + 1);

		CreateEnemy(D3DXVECTOR3(-100.0f,0.0f,100.0f));
		CreateEnemy(D3DXVECTOR3(0.0f,0.0f,100.0f));
		CreateEnemy(D3DXVECTOR3(100.0f,0.0f,100.0f));
	
		// �����ǂ̏�������
		enemyWk[0].status.rot.y = MIGI;
		enemyWk[1].status.rot.y = SHITA;
		enemyWk[2].status.rot.y = UE;
}


//*****************************************************************************
// �֐���:	void model_RaypickToMap(int no)
// ����:	int no
// �߂�l:	����
// ����:	���@�ƃ}�b�v�Ƃ̃��C�s�b�N�A�����̓��C���΂�����
//*****************************************************************************
void enemy_RaypickTomap(void)
{


	MAP *map = GetMap(0);

	for (int no = 0; no < SHIKENKAN_NINZU; no++)
	{
		// �֗��֐��ƈ����̐���(�����p)
		// ���֔�΂�
		D3DXIntersect(
			map->MeshMap,				// �����蔻�����肽�����b�V���@�^��LPD3DXBASEMESH(LPD3DXMESH��OK?)
			&D3DXVECTOR3(enemyWk[no].status.pos.x, enemyWk[no].status.pos.y + 0.0f, enemyWk[no].status.pos.z),				// ���C�̎��_���W��ݒ�(�v���C���[�̍��W�Ƃ���) �^��D3DXVECTOR3
			&D3DXVECTOR3(0, -1, 0),		// ���C�̕�����ݒ� �^��D3DXVECTOR3 XYZ 1�Ő�����-1�ŕ��̕���
			&enemyWk[no].status.tomapDown,				// �Փ˔��� �^��BOOL(bool�ł͂Ȃ�) �Փ˂��Ă�����TRUE�������Ă��Ȃ����FALSE
			NULL,						// ��L�̔��肪TRUE�̏ꍇ���C�̎��_�ɍł��߂��ʂ̃C���f�b�N�X�l�ւ̃|�C���^
			NULL,						// �d�S�q�b�g���W�ւ̃|�C���^����1���C�������������b�V���̏ꏊ
			NULL,						// �d�S�q�b�g���W�ւ̃|�C���^����2����������������b�V���̓��������ꏊ
			&enemyWk[no].status.D_RtoMdistance,		// ���C���烁�b�V���܂ł̋����͂�����
			NULL,						// D3DXINTERSECTINFO�\���̂̔z����i�[����ID3DXBuffer�I�u�W�F�N�g�ւ̃|�C���^
			NULL						// ppAllHits�z����̃G���g�������i�[����|�C���^�A�^��DWORD
		);


		// ���C�s�b�N(���f�������ɔ�΂������C�ƃ}�b�v)
		D3DXIntersect(map->MeshMap, &enemyWk[no].status.pos, &D3DXVECTOR3(0, 1, 0), &enemyWk[no].status.tomapUp, NULL, NULL, NULL,
			&enemyWk[no].status.U_RtoMdistance, NULL, NULL);

		// ���C�s�b�N(�E�ɔ�΂������C�ƃ}�b�v)
		D3DXIntersect(map->MeshMap, &enemyWk[no].status.pos, &D3DXVECTOR3(1, 0, 0), &enemyWk[no].status.tomapRight, NULL, NULL, NULL,
			&enemyWk[no].status.R_RtoMdistance, NULL, NULL);

		// ���C�s�b�N(���ɔ�΂������C�ƃ}�b�v)
		D3DXIntersect(map->MeshMap, &enemyWk[no].status.pos, &D3DXVECTOR3(-1, 0, 0), &enemyWk[no].status.tomapLeft, NULL, NULL, NULL,
			&enemyWk[no].status.L_RtoMdistance, NULL, NULL);

		// ���C�s�b�N(�O�������ɔ�΂������C�ƃ}�b�v)
		D3DXIntersect(map->MeshMap, &enemyWk[no].status.pos, &D3DXVECTOR3(0, 0, 1), &enemyWk[no].status.tomapFront, NULL, NULL, NULL,
			&enemyWk[no].status.F_RtoMdistance, NULL, NULL);

		// ���C�s�b�N(������Z�ɔ�΂������C�ƃ}�b�v)
		D3DXIntersect(map->MeshMap, &enemyWk[no].status.pos, &D3DXVECTOR3(0, 0, -1), &enemyWk[no].status.tomapBack, NULL, NULL, NULL,
			&enemyWk[no].status.B_RtoMdistance, NULL, NULL);
	}
}


//**********************************************************************************
// �֐���:	void move_change(void)
// �߂�l:	�Ȃ�
// ����:	�Ȃ�
// ����:	�ǂ�����Ȃ������ς��Ă��܂�
//**********************************************************************************
void move_change(void)
{
	D3DXVECTOR3 hosei;
	D3DXVECTOR3 rotCamera;
	float		escapmodellmove = 1.0f;		// �l��␳�����邽��
											// �J�����̌����擾

	// �e�X�g�ǂɂ����ĂƂ߂Ă��܂�
	// �ǂƂ̃��C�𔼌a�ɂ���΂���
	// ���C�����a�ȉ��ɂȂ��Ă���ꍇ���a�ɂȂ�悤�ړ������Ă�����΂���

	for (int no = 0; no < SHIKENKAN_NINZU; no++)
	{
		// �E�����ڐG
		if (enemyWk[no].status.R_RtoMdistance <= ENEMY_HANKEI)
		{
			// ��
			enemyWk[no].status.rot.y = HIDARI;
		}

		// ���ڐG
		else if (enemyWk[no].status.L_RtoMdistance <= ENEMY_HANKEI)
		{	// �E
			enemyWk[no].status.rot.y = MIGI;
		}

		// shita�ڐG
		if (enemyWk[no].status.F_RtoMdistance <= ENEMY_HANKEI)
		{	// ���
			enemyWk[no].status.rot.y = UE;
		}
		//ue�ڐG
		else if (enemyWk[no].status.B_RtoMdistance <= ENEMY_HANKEI)
		{	// �O
			enemyWk[no].status.rot.y = SHITA;
		}

	}
	/// �����W�����v�Ȃǂ���������ۂ�
	/// �n�ʂւ̂߂荞�݂����
//if (model->D_RtoMdistance <= model->center)
//{
//	hosei.y = model->center - model->D_RtoMdistance;
//	model->pos.y += hosei.y;
//}




//	model->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}