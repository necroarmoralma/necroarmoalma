//*******************************************************************************
// �t�@�C����:	bossbullet.cpp
// �쐬��:		�R�{�s��
// ����:		�{�X�ƓG�̒e
// 
//*******************************************************************************
#include "bossbullet.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "debugproc.h"
#include "model.h"
#include "meshfield.h"
#include "boss.h"
#include "map.h"
#include "setting.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BOSSBULLET		"data/TEXTURE/karinotama.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VALUE_MOVE_BOSSBULLET		(1.5f)							// �e��
#define BOSSBULLETLIMIT				(1500)
#define BOSSBULLETLIVE				(5*60)							// ��������
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBossbullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexBossbullet(int nIdxBossbullet, float fWidth, float fHeight);
void SetColorBossbullet(int nIdxBossbullet, D3DXCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureBossbullet[5] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBossbullet = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

BOSSBULLET				bossbullet[BOSSBULLET_MAX];				// �e�̍\���̔z��
bool					bossbullet_alpatest;					// �A���t�@�e�X�gON/OFF
int						bossbulletAlpha;						// �A���t�@�e�X�g��臒l

char *bossbulletFileName[] =
{
	"data/TEXTURE/bossbullet.png",
	"data/TEXTURE/bossbullet.png",
	"data/TEXTURE/bossbullet.png",
	"data/TEXTURE/bossbullet.png",
	"data/TEXTURE/bossbullet.png",
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBossbullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexBossbullet(pDevice);

	// �e�N�X�`���̓ǂݍ���
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
			bossbulletFileName[nCntTex],			// �t�@�C���̖��O
			&g_apD3DTextureBossbullet[nCntTex]);	// �ǂݍ��ރ������[
	}

	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
	{
		//bossbullet[nCntBossbullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//bossbullet[nCntBossbullet].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		//bossbullet[nCntBossbullet].wide = BOSSBULLET_WIDTH;
		//bossbullet[nCntBossbullet].height = BOSSBULLET_HEIGHT;
		//bossbullet[nCntBossbullet].use = false;
		//bossbullet[nCntBossbullet].moveon = false;									//
	}

	bossbullet_alpatest = true;
	bossbulletAlpha = 0x0;


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBossbullet(void)
{
	// �����I��(�����I�ɂ��ׂĂ𖢎g�p�ɂ��܂��j
	for (int i = 0; i < BOSSBULLET_MAX; i++)
	{
		bossbullet[i].use = false;
	}
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (g_apD3DTextureBossbullet[nCntTex] != NULL)
		{// �e�N�X�`���̊J��
			g_apD3DTextureBossbullet[nCntTex]->Release();
			g_apD3DTextureBossbullet[nCntTex] = NULL;
		}
	}

	if (g_pD3DVtxBuffBossbullet != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffBossbullet->Release();
		g_pD3DVtxBuffBossbullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBossbullet(void)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);
	float rotsetBossBtoP;
	BOOL bossbullethit;
	float checkdistance;
	ENEMYLENGTH *length = GetEnemylength(0);
	rotCamera = GetRotCamera();

	
	// �ړ�
	for (int i = 0; i < BOSSBULLET_MAX; i++)
	{
		if (bossbullet[i].use == true)

		{
			bossbullet[i].count --;

			// ���x�v����Ɖ�]�͈�x�m�肵���炻�̂܂�
			// �ړ��ʂ����܂��Ă��Ȃ��Ȃ猈�߂�
			if (bossbullet[i].moveon == false)
			{
				//++���@�Ɍ�������
			
				bossbullet[i].moveon = true;
				bossbullet[i].pos.y = model->pos.y;
				bossbullet[i].move.x = (sinf(D3DX_PI + bossbullet[i].bossbullet_rot) * VALUE_MOVE_BOSSBULLET *3.5f);	// 3.5�͒e�������Ă邾���ł���
				bossbullet[i].move.z = (cosf(D3DX_PI + bossbullet[i].bossbullet_rot) * VALUE_MOVE_BOSSBULLET *3.5f);
			}

			/// �ʒu�ړ�
			bossbullet[i].pos.x += bossbullet[i].move.x;
			bossbullet[i].pos.z += bossbullet[i].move.z;

			// �������Ԃ�0�ȉ��Ȃ�폜
			if(bossbullet[i].count <= 0)
			{
				bossbullet[i].use = false;
			}

		}
	}
	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
	{
		if (bossbullet[nCntBossbullet].use == true)
		{
			// �e�̈ʒu�ݒ�
		//	SetPositionShadow(bossbullet[nCntBossbullet].g_nIdxShadow, D3DXVECTOR3(bossbullet[nCntBossbullet].pos.x, 0.1f, bossbullet[nCntBossbullet].pos.z));
		}
	}

	// �A���t�@�e�X�gON/OFF
	if (GetKeyboardTrigger(DIK_F1))
	{
		bossbullet_alpatest = bossbullet_alpatest ? false : true;
	}

	// �A���t�@�e�X�g��臒l�ύX
	if (GetKeyboardPress(DIK_I))
	{
		bossbulletAlpha--;
		if (bossbulletAlpha < 0)
		{
			bossbulletAlpha = 0;
		}
	}
	if (GetKeyboardPress(DIK_K))
	{
		bossbulletAlpha++;
		if (bossbulletAlpha > 255)
		{
			bossbulletAlpha = 255;
		}
	}

	//PrintDebugProc("*** �ؑ��� ***\n");
	//PrintDebugProc("�O�ړ�   : ��\n");
	//PrintDebugProc("��ړ�   : ��\n");
	//PrintDebugProc("���ړ�   : ��\n");
	//PrintDebugProc("�E�ړ�   : ��\n");
	//PrintDebugProc("\n");

	PrintDebugProc("*** �A���t�@�e�X�g ***\n");
	PrintDebugProc("ON / OFF�F[F1] ( ���݁F");
	if (bossbullet_alpatest == true)
	{
		PrintDebugProc("ON");
	}
	else
	{
		PrintDebugProc("OFF");
	}
	PrintDebugProc(" )\n");

	if (bossbullet_alpatest == true)
	{
		PrintDebugProc("�A���t�@臒l�F����[I] / ����[K] ( 臒l�F%d )\n", bossbulletAlpha);
	}



}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBossbullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���e�X�g�ݒ�
	if (bossbullet_alpatest == true)
	{
		// ���e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, bossbulletAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	}

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
	{
		if (bossbullet[nCntBossbullet].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&bossbullet[nCntBossbullet].mtxWorld);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			// �|���S���𐳖ʂɌ�����
#if 1
			// �t�s������Ƃ߂�
			D3DXMatrixInverse(&bossbullet[nCntBossbullet].mtxWorld, NULL, &mtxView);
			bossbullet[nCntBossbullet].mtxWorld._41 = 0.0f;
			bossbullet[nCntBossbullet].mtxWorld._42 = 0.0f;
			bossbullet[nCntBossbullet].mtxWorld._43 = 0.0f;
#else
			bossbullet[nCntBossbullet].mtxWorld._11 = mtxView._11;
			bossbullet[nCntBossbullet].mtxWorld._12 = mtxView._21;
			bossbullet[nCntBossbullet].mtxWorld._13 = mtxView._31;
			bossbullet[nCntBossbullet].mtxWorld._21 = mtxView._12;
			bossbullet[nCntBossbullet].mtxWorld._22 = mtxView._22;
			bossbullet[nCntBossbullet].mtxWorld._23 = mtxView._32;
			bossbullet[nCntBossbullet].mtxWorld._31 = mtxView._13;
			bossbullet[nCntBossbullet].mtxWorld._32 = mtxView._23;
			bossbullet[nCntBossbullet].mtxWorld._33 = mtxView._33;
#endif

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, bossbullet[nCntBossbullet].scl.x,
				bossbullet[nCntBossbullet].scl.y,
				bossbullet[nCntBossbullet].scl.z);
			D3DXMatrixMultiply(&bossbullet[nCntBossbullet].mtxWorld, &bossbullet[nCntBossbullet].mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, bossbullet[nCntBossbullet].pos.x,
				bossbullet[nCntBossbullet].pos.y,
				bossbullet[nCntBossbullet].pos.z);
			D3DXMatrixMultiply(&bossbullet[nCntBossbullet].mtxWorld, &bossbullet[nCntBossbullet].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &bossbullet[nCntBossbullet].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffBossbullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apD3DTextureBossbullet[nCntBossbullet % 5]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntBossbullet * 4), NUM_POLYGON);
		}
	}

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexBossbullet(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * BOSSBULLET_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffBossbullet,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBossbullet->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-BOSSBULLET_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-BOSSBULLET_WIDTH / 2.0f, BOSSBULLET_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(BOSSBULLET_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BOSSBULLET_WIDTH / 2.0f, BOSSBULLET_HEIGHT, 0.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBossbullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBossbullet(int nIdxBossbullet, float fWidth, float fHeight)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBossbullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBossbullet * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBossbullet->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorBossbullet(int nIdxBossbullet, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBossbullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBossbullet * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBossbullet->Unlock();
	}
}

//=============================================================================
// �{�X�̒e�̍쐬
//=============================================================================
int SetBossbullet(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col,float bossbulletrot )
{
	int nIdxBossbullet = -1;

	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
	{
		if (bossbullet[nCntBossbullet].use == false)
		{
			bossbullet[nCntBossbullet].pos = pos;
			bossbullet[nCntBossbullet].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			bossbullet[nCntBossbullet].wide = fWidth;
			bossbullet[nCntBossbullet].height = fHeight;
			bossbullet[nCntBossbullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			bossbullet[nCntBossbullet].use = true;
			bossbullet[nCntBossbullet].moveon = false;
			bossbullet[nCntBossbullet].bossbullet_rot = bossbulletrot;

			// ���_���W�̐ݒ�
			SetVertexBossbullet(nCntBossbullet, fWidth, fHeight);

			// ���_�J���[�̐ݒ�
			SetColorBossbullet(nCntBossbullet, col);

			// �e�̐ݒ�
			bossbullet[nCntBossbullet].g_nIdxShadow = CreateShadow(bossbullet[nCntBossbullet].pos, bossbullet[nCntBossbullet].wide, bossbullet[nCntBossbullet].wide);

			nIdxBossbullet = nCntBossbullet;

			break;
		}
	}

	return nIdxBossbullet;
}

//***********************************************************************************
// �֐���: SetEnemybullet

//***********************************************************************************
int SetEnemybullet(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, float enemytargetrot)
{
	int nIdxBossbullet = -1;

	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
	{
		if (bossbullet[nCntBossbullet].use == false)
		{
			bossbullet[nCntBossbullet].pos = pos;
			bossbullet[nCntBossbullet].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			bossbullet[nCntBossbullet].wide = fWidth;
			bossbullet[nCntBossbullet].height = fHeight;
			bossbullet[nCntBossbullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			bossbullet[nCntBossbullet].use = true;
			bossbullet[nCntBossbullet].moveon = false;
			bossbullet[nCntBossbullet].bossbullet_rot = enemytargetrot;
			bossbullet[nCntBossbullet].count = BOSSBULLETLIVE;
			// ���_���W�̐ݒ�
			SetVertexBossbullet(nCntBossbullet, fWidth, fHeight);

			// ���_�J���[�̐ݒ�
			SetColorBossbullet(nCntBossbullet, col);

			// �e�̐ݒ�
			bossbullet[nCntBossbullet].g_nIdxShadow = CreateShadow(bossbullet[nCntBossbullet].pos, bossbullet[nCntBossbullet].wide, bossbullet[nCntBossbullet].wide);

			nIdxBossbullet = nCntBossbullet;

			break;
		}
	}

	return nIdxBossbullet;
}


//=============================================================================
// �ォ�痎��������^�C�v
//=============================================================================
//int SetBossbullet(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, float bossbulletrot)
//{
//	int nIdxBossbullet = -1;
//
//	for (int nCntBossbullet = 0; nCntBossbullet < BOSSBULLET_MAX; nCntBossbullet++)
//	{
//		if (bossbullet[nCntBossbullet].use == false)
//		{
//			bossbullet[nCntBossbullet].pos = pos;
//			bossbullet[nCntBossbullet].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//			bossbullet[nCntBossbullet].wide = fWidth;
//			bossbullet[nCntBossbullet].height = fHeight;
//			bossbullet[nCntBossbullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			bossbullet[nCntBossbullet].use = true;
//			bossbullet[nCntBossbullet].moveon = false;
//			bossbullet[nCntBossbullet].bossbullet_rot = bossbulletrot;
//
//			// ���_���W�̐ݒ�
//			SetVertexBossbullet(nCntBossbullet, fWidth, fHeight);
//
//			// ���_�J���[�̐ݒ�
//			SetColorBossbullet(nCntBossbullet, col);
//
//			// �e�̐ݒ�
//			bossbullet[nCntBossbullet].g_nIdxShadow = CreateShadow(bossbullet[nCntBossbullet].pos, bossbullet[nCntBossbullet].wide, bossbullet[nCntBossbullet].wide);
//
//			nIdxBossbullet = nCntBossbullet;
//
//			break;
//		}
//	}
//
//	return nIdxBossbullet;
//}

//=============================================================================
// ���܂��擾
//=============================================================================
BOSSBULLET *GetBossbullet(int no)
{
	return &bossbullet[0];
}

