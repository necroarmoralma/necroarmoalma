//=============================================================================
//
// tama���� [steam.cpp]
// Author : HAL�Q�[���w�ȓ�N���ے�1�N�@�R�{�s��
// tree.cpp���̂܂܃R�s
//=============================================================================
#include "steam.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "debugproc.h"
#include "model.h"
#include "meshfield.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_STEAM		"data/TEXTURE/kemuri.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VALUE_MOVE_STEAM		(9.00f)							
//#define STEAMSPEED				(0.1f)							// �ړ����x
#define STEAMLIMIT				(11000)							// ���@�e���ړ�����̈�
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSteam(LPDIRECT3DDEVICE9 pDevice);
void SetVertexSteam(int nIdxSteam, float fWidth, float fHeight);
void SetColorSteam(int nIdxSteam, D3DXCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureSteam[5] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSteam = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

STEAM				steam[STEAM_MAX];				// �e�̍\���̔z��
bool					steam_alpatest;					// �A���t�@�e�X�gON/OFF
int						steamAlpha;						// �A���t�@�e�X�g��臒l

char *steamFileName[] =
{
	"data/TEXTURE/testpen.png",
	"data/TEXTURE/testpen.png",
	"data/TEXTURE/testpen.png",
	"data/TEXTURE/testpen.png",
	"data/TEXTURE/testpen.png",
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSteam(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexSteam(pDevice);

	// �e�N�X�`���̓ǂݍ���
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
			TEXTURE_STEAM,			// �t�@�C���̖��O
			&g_apD3DTextureSteam[nCntTex]);	// �ǂݍ��ރ������[
	}

	for (int nCntSteam = 0; nCntSteam < STEAM_MAX; nCntSteam++)
	{
		//steam[nCntSteam].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//steam[nCntSteam].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		//steam[nCntSteam].wide = STEAM_WIDTH;
		//steam[nCntSteam].height = STEAM_HEIGHT;
		//steam[nCntSteam].use = false;
		//steam[nCntSteam].moveon = false;									//
	}

	steam_alpatest = true;
	steamAlpha = 0x0;


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSteam(void)
{
	// �����I�ɂ��ׂĂ𖢎g�p�ɁI

	for (int i = 0; i < STEAM_MAX; i++)
	{
		steam[i].use = false;
	}
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (g_apD3DTextureSteam[nCntTex] != NULL)
		{// �e�N�X�`���̊J��
			g_apD3DTextureSteam[nCntTex]->Release();
			g_apD3DTextureSteam[nCntTex] = NULL;
		}
	}

	if (g_pD3DVtxBuffSteam != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffSteam->Release();
		g_pD3DVtxBuffSteam = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSteam(void)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);

	rotCamera = GetRotCamera();


	// �ړ��e�X�g
	for (int i = 0; i < STEAM_MAX; i++)
	{
		if (steam[i].use == true)

		{
			// ���x�v����Ɖ�]�͈�x�m�肵���炻�̂܂�
			// �ړ��ʂ����܂��Ă��Ȃ��Ȃ猈�߂�
			if (steam[i].moveon == false)
			{
				steam[i].move.y = STEAMSPEED;

			}

			//+model->rot.y
			//	+ model->rot.y

			/// �ʒu�ړ�
			steam[i].pos.x += steam[i].move.x;
			steam[i].pos.z += steam[i].move.z;
			steam[i].pos.y += steam[i].move.y;

			// ���E�Ɋg��
			steam[i].scl.x += 0.1f;

			// �J�E���g�����炵�O�Ȃ�΍폜
			steam[i].count--;
			if (steam[i].count < 0)
			{
				steam[i].use = false;
				ReleaseShadow(steam[i].g_nIdxShadow);
			}
		}
	}


	// �A���t�@�e�X�gON/OFF
	if (GetKeyboardTrigger(DIK_F1))
	{
		steam_alpatest = steam_alpatest ? false : true;
	}

	// �A���t�@�e�X�g��臒l�ύX
	if (GetKeyboardPress(DIK_I))
	{
		steamAlpha--;
		if (steamAlpha < 0)
		{
			steamAlpha = 0;
		}
	}
	if (GetKeyboardPress(DIK_K))
	{
		steamAlpha++;
		if (steamAlpha > 255)
		{
			steamAlpha = 255;
		}
	}

	PrintDebugProc("*** �A���t�@�e�X�g ***\n");
	PrintDebugProc("ON / OFF�F[F1] ( ���݁F");
	if (steam_alpatest == true)
	{
		PrintDebugProc("ON");
	}
	else
	{
		PrintDebugProc("OFF");
	}
	PrintDebugProc(" )\n");

	if (steam_alpatest == true)
	{
		PrintDebugProc("�A���t�@臒l�F����[I] / ����[K] ( 臒l�F%d )\n", steamAlpha);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSteam(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���e�X�g�ݒ�
	if (steam_alpatest == true)
	{
		// ���e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, steamAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	}

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntSteam = 0; nCntSteam < STEAM_MAX; nCntSteam++)
	{
		if (steam[nCntSteam].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&steam[nCntSteam].mtxWorld);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			// �|���S���𐳖ʂɌ�����
#if 1
			// �t�s������Ƃ߂�
			D3DXMatrixInverse(&steam[nCntSteam].mtxWorld, NULL, &mtxView);
			steam[nCntSteam].mtxWorld._41 = 0.0f;
			steam[nCntSteam].mtxWorld._42 = 0.0f;
			steam[nCntSteam].mtxWorld._43 = 0.0f;
#else
			steam[nCntSteam].mtxWorld._11 = mtxView._11;
			steam[nCntSteam].mtxWorld._12 = mtxView._21;
			steam[nCntSteam].mtxWorld._13 = mtxView._31;
			steam[nCntSteam].mtxWorld._21 = mtxView._12;
			steam[nCntSteam].mtxWorld._22 = mtxView._22;
			steam[nCntSteam].mtxWorld._23 = mtxView._32;
			steam[nCntSteam].mtxWorld._31 = mtxView._13;
			steam[nCntSteam].mtxWorld._32 = mtxView._23;
			steam[nCntSteam].mtxWorld._33 = mtxView._33;
#endif

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, steam[nCntSteam].scl.x,
				steam[nCntSteam].scl.y,
				steam[nCntSteam].scl.z);
			D3DXMatrixMultiply(&steam[nCntSteam].mtxWorld, &steam[nCntSteam].mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, steam[nCntSteam].pos.x,
				steam[nCntSteam].pos.y,
				steam[nCntSteam].pos.z);
			D3DXMatrixMultiply(&steam[nCntSteam].mtxWorld, &steam[nCntSteam].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &steam[nCntSteam].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffSteam, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apD3DTextureSteam[nCntSteam % 5]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntSteam * 4), NUM_POLYGON);
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
HRESULT MakeVertexSteam(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * STEAM_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffSteam,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffSteam->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntSteam = 0; nCntSteam < STEAM_MAX; nCntSteam++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-STEAM_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-STEAM_WIDTH / 2.0f, STEAM_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(STEAM_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(STEAM_WIDTH / 2.0f, STEAM_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffSteam->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexSteam(int nIdxSteam, float fWidth, float fHeight)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffSteam->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxSteam * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffSteam->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorSteam(int nIdxSteam, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffSteam->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxSteam * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffSteam->Unlock();
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
int SetSteam(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col)
{
	MODEL *model = GetModel(0);
	int nIdxSteam = -1;

	for (int nCntSteam = 0; nCntSteam < STEAM_MAX; nCntSteam++)
	{
		if (steam[nCntSteam].use == false)
		{
			steam[nCntSteam].rot = model->rot;
			steam[nCntSteam].pos = D3DXVECTOR3(model->pos.x, model->pos.y, model->pos.z);
			steam[nCntSteam].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			steam[nCntSteam].wide = fWidth;
			steam[nCntSteam].height = fHeight;
			steam[nCntSteam].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			steam[nCntSteam].use = true;
			steam[nCntSteam].moveon = false;
			// ���_���W�̐ݒ�
			SetVertexSteam(nCntSteam, fWidth, fHeight);

			// ���_�J���[�̐ݒ�
			SetColorSteam(nCntSteam, col);

			// �e�̐ݒ�
			steam[nCntSteam].g_nIdxShadow = CreateShadow(steam[nCntSteam].pos, steam[nCntSteam].wide, steam[nCntSteam].wide);

			nIdxSteam = nCntSteam;

			// �J�E���g��������
			steam[nCntSteam].count = STEAM_RELEASECOUNT;
			break;
		}
	}

	return nIdxSteam;
}

//=============================================================================
// ���܂��擾
//=============================================================================
STEAM *GetSteam(int no)
{
	return &steam[0];
}

