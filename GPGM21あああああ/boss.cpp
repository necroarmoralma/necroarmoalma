//=============================================================================
//
// ���f������ [boss.cpp]
//  Author : HAL�Q�[���w�ȓ�N���ے�1�N�@�R�{�s��
// 
//=============================================================================
#include "boss.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"
#include "bossbullet.h"
#include "meshfield.h"
#include "model.h"
#include "bulletmk2.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BOSS_AIRPLANE		"data/MODEL/student.x"	// �ǂݍ��ރ��f����
#define	VALUE_MOVE_BOSS	(0.80f)						// �ړ����x
#define	RATE_MOVE_BOSS		(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_BOSS	(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_BOSS	(0.20f)						// ��]�����W��
#define	BULLET_SIZEX		(20.0f)						// �e�̑傫����lX
#define BULLET_SIZEY		(20.0f)						// �e�̑傫����lY
#define SPEEDSETTING_BOSS	()						// �{�X��XZ���ʏ�ŉ�]����Ƃ��̒���
#define BOSSLENGTH			(800)					// �}�b�v���S�_����{�X�̋���
#define BOSSSPEED			(1.1f)
#define NEXTMOVE			(1.57f)					// ����؂�ւ����s�����]�l


// �e���[�h�̒e�̑傫���@X���������@Y���c����
//�@DEBIRU�̒e
#define DEBIRUBULLET_1_SIZE_X	(100.0f)
#define DEBIRUBULLET_1_SIZE_Y	(100.0f)

// AHIRU�̒e
#define AHIRUBULLET_1_SIZE_X	(10.0f)
#define AHIRUBULLET_1_SIZE_Y	(10.0f)

#define AHIRUBULLET_2_SIZE_X	(5.0f)
#define AHIRUBULLET_2_SIZE_Y	(10.0f)

#define AHIRUBULLET_3_SIZE_X	(10.0f)
#define AHIRUBULLET_3_SIZE_Y	(10.0f)

// HENANO�̒e
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void bossshot(void);
void bossbeam(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureBoss;			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshBoss;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatBoss;		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatBoss;				// �������̑���
												/*
												D3DXMATRIX			boss->World;			// ���[���h�}�g���b�N�X
												D3DXVECTOR3			boss->pos;					// ���݂̈ʒu
												D3DXVECTOR3			boss->move;				// �ړ���
												D3DXVECTOR3			boss->rot;					// ���݂̌���
												D3DXVECTOR3			boss->rotDest;				// �ړI�̌���
												*/

int					bossnidxShadow;				// �eID
float				bosssizeShadow;				// �e�̃T�C�Y
D3DXCOLOR			bosscolShadow;				// �e�̐F
D3DXVECTOR3			BOSSBASEPOS(0.0f,0.0f,5.0f);
BOSS				bossWk[1];					// ���f���\����(���f���͂P�j
float				bossActtime;				// �{�X���s�����銴�o

int					actcheck;					// �Ă���
float				viewrot_y;					// �e�X�g(�����ڏ�̉�])
//=============================================================================
// ����������
//=============================================================================
HRESULT InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS *boss = &bossWk[0];
	D3DXVECTOR3 rotCamera;
	
	// HP�̐ݒ�
	boss->boss_maxlife = BOSSLIFE;
	boss->boss_life = boss->boss_maxlife;

	g_pD3DTextureBoss = NULL;
	g_pD3DXMeshBoss = NULL;
	g_pD3DXBuffMatBoss = NULL;

	boss->pos = BOSSBASEPOS;
	boss->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	boss->puremove = boss->move;
	boss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	boss->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	boss->scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	boss->acttime = BOSSACT;


	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(BOSS_AIRPLANE,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pD3DXBuffMatBoss,
		NULL,
		&g_nNumMatBoss,
		&g_pD3DXMeshBoss)))
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTextureBoss);	// �ǂݍ��ރ������[
#endif


								// �e�̐���
	bossnidxShadow = CreateShadow(boss->pos, 25.0f, 25.0f);

	bosssizeShadow = 25.0f;
	bosscolShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	// �e�X�gviewrot_y��ݒ�(�����ڂ�����]������)
	viewrot_y = boss->rot.y;

	// ���쐧��ɕK�v�Ȓl��ݒ�
	boss->movesetting = 0.0f;
	boss->movemode = DEBIRU;		// �ŏ��͂����܁H�����ʂ������Ă��邽��
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss(void)
{
	if (g_pD3DTextureBoss != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBoss->Release();
		g_pD3DTextureBoss = NULL;
	}

	if (g_pD3DXMeshBoss != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshBoss->Release();
		g_pD3DXMeshBoss = NULL;
	}

	if (g_pD3DXBuffMatBoss != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatBoss->Release();
		g_pD3DXBuffMatBoss = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss(void)
{
	D3DXVECTOR3 rotCamera;
	BOSS *boss = &bossWk[0];
	MODEL *model = GetModel(0);
	float fDiffRotY;
	D3DXVECTOR3 SubposBosstoModel;
	float rotcheckBtoM;


	// �J�����̌����擾
	//rotCamera = GetRotCamera();
	
	//++���@�Ɍ�������
	// �ڕW-����
	rotcheckBtoM = atan2f((model->pos.x - boss->pos.x),(model->pos.z - boss->pos.z)) + 3.14;
	
	boss->rockon = rotcheckBtoM;	// �v���C���[�̕�������������
	//boss->rot.z = rotcheckBtoM;
	// �㉺
	// �ڕW-�����i�i�{�X���猩�đO���Ɏ��@�����݂���ꍇ)
	//rotcheckBtoM = atan2f((model->pos.y - boss->pos.y), (model->pos.z - boss->pos.z)) + 3.14;
	//boss->rot.x = -rotcheckBtoM;	// �v���C���[�̕�������������
	
	// �s��
	// ����o�����Ԃ�
	boss->acttime -= 1.0f;		//�@�f�N�������g�ł��������H1�t���[����1���炵����


	
		//boss->pos.x =   (sinf(boss->kaiten) * BOSSSPEED *BOSSLENGTH);				// ������31.5f�Ƃ��͂��񂵂イ�݂�����
		////boss->pos.y = model->pos.y;
		//boss->pos.z =   (cosf(boss->kaiten) *BOSSSPEED *BOSSLENGTH);			// xsin������ + zcos������ sin(10)
		//
		//

	// �e�̈ʒu�ݒ�
	SetPositionShadow(bossnidxShadow, D3DXVECTOR3(boss->pos.x, 0.1f, boss->pos.z));

	SetVertexShadow(bossnidxShadow, bosssizeShadow, bosssizeShadow);
	SetColorShadow(bossnidxShadow, bosscolShadow);

	PrintDebugProc("[rotDest.y������:(%f) ]\n", boss->rotDest.y);


	//��]�e�X�g
	boss->rot.y += 0.01f;
	
	// ��]����
	boss->movesetting += 0.01f;
	// NEXTMOVE�ɓ��B���Ă����烂�[�h�ؑ�
	if (boss->movesetting >= NEXTMOVE)
	{
		// ���̃��[�h�ֈړ�
		if (boss->movemode == DEBIRU)
		{
			boss->movemode = AHIRU;
			boss->movesetting = 0.0f;
		}

		else if (boss->movemode == AHIRU)
		{
			boss->movemode = HENANO;
			boss->movesetting = 0.0f;
		}

		else if (boss->movemode == HENANO)
		{
			boss->movemode = MEKA;
			boss->movesetting = 0.0f;
		}

		else if (boss->movemode == MEKA)
		{
			boss->movemode = DEBIRU;
			boss->movesetting = 0.0f;
		}

		PrintDebugProc("bosscubepos������:(%f)(%f)(%f) ]\n", boss->pos.x, boss->pos.y, boss->pos.z);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	BOSS *boss = &bossWk[0];

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&boss->World);


	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, boss->scl.x, boss->scl.y, boss->scl.z);
	D3DXMatrixMultiply(&boss->World, &boss->World, &mtxScl);


	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, boss->rot.y, boss->rot.x, boss->rot.z);
	D3DXMatrixMultiply(&boss->World, &boss->World, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, boss->pos.x, boss->pos.y, boss->pos.z);
	D3DXMatrixMultiply(&boss->World, &boss->World, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &boss->World);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatBoss->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatBoss; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureBoss);

		// �`��
		g_pD3DXMeshBoss->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionBoss(void)
{
	BOSS *boss = &bossWk[0];
	return boss->pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationBoss(void)
{
	BOSS *boss = &bossWk[0];
	return boss->rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestBoss(void)
{
	BOSS *boss = &bossWk[0];
	return boss->rotDest;
}

//*****************************************************************************
// �Q�b�g�֐�
//*****************************************************************************
BOSS *GetBoss(int no)
{
	return(&bossWk[0]);
}

//*****************************************************************************
// �{�X�̍s���܂Ƃ�
//*****************************************************************************
void bossshot(void)
{
	BOSS *boss = &bossWk[0];
	// �ʔ���
	D3DXVECTOR3 pos = boss->pos;
	SetBossbullet(boss->pos, 20.0f, 20.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), boss->rockon);
	
	
	boss->acttime = BOSSACT;
}

//*******************************
// ���[�U�[
//*******************************
void bossbeam(void)
{
	BOSS *boss = &bossWk[0];
			D3DXVECTOR3 pos = boss->pos;
			boss->rot.y = 0;
			SetBossbullet(boss->pos, 20.0f, 60.0f, D3DXCOLOR(0.6f, 1.0f, 1.0f, 1.0f),boss->rot.y);
			boss->acttime = BOSSACT;
	
}