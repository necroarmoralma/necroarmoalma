//=============================================================================
//
// tama���� [hit.cpp]
// Author : �R�{�@�s��
// tree.cpp���̂܂܃R�s
//=============================================================================
#include "hit.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "debugproc.h"
#include "model.h"
#include "meshfield.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_HIT		"data/TEXTURE/hit.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VALUE_MOVE_HIT		(3.00f)							// �ړ����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexHit(LPDIRECT3DDEVICE9 pDevice);
void SetVertexHit(int nIdxHit, float fWidth, float fHeight);
void SetColorHit(int nIdxHit, D3DXCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureHit[5] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHit = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

HIT				hit[BULLET_MAX];				// �e�̍\���̔z��
bool					hit_alpatest;					// �A���t�@�e�X�gON/OFF
int						hitAlpha;						// �A���t�@�e�X�g��臒l

char *hitFileName[] =
{
	"data/TEXTURE/hit.png",
	"data/TEXTURE/hit.png",
	"data/TEXTURE/hit.png",
	"data/TEXTURE/hit.png",
	"data/TEXTURE/hit.png",
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitHit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexHit(pDevice);

	// �e�N�X�`���̓ǂݍ���
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
			hitFileName[nCntTex],			// �t�@�C���̖��O
			&g_apD3DTextureHit[nCntTex]);	// �ǂݍ��ރ������[
	}

	for (int nCntHit = 0; nCntHit < BULLET_MAX; nCntHit++)
	{
		//hit[nCntHit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//hit[nCntHit].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		//hit[nCntHit].wide = HIT_WIDTH;
		//hit[nCntHit].height = HIT_HEIGHT;
		//hit[nCntHit].use = false;
		//hit[nCntHit].moveon = false;									//
	}

	hit_alpatest = true;
	hitAlpha = 0x0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitHit(void)
{
	// �����I�ɂ��ׂĂ𖢎g�p�ɁI

	for (int i = 0; i < BULLET_MAX; i++)
	{
		hit[i].use = false;
	}
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (g_apD3DTextureHit[nCntTex] != NULL)
		{// �e�N�X�`���̊J��
			g_apD3DTextureHit[nCntTex]->Release();
			g_apD3DTextureHit[nCntTex] = NULL;
		}
	}

	if (g_pD3DVtxBuffHit != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffHit->Release();
		g_pD3DVtxBuffHit = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHit(void)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);

	rotCamera = GetRotCamera();

	for (int nCntHit = 0; nCntHit < BULLET_MAX; nCntHit++)
	{
		if (hit[nCntHit].use == true)
		{
			hit[nCntHit].life--;
			if (hit[nCntHit].life <= 0.0f)
			{
				hit[nCntHit].use = false;
			}
		}
	}


	// �A���t�@�e�X�gON/OFF
	if (GetKeyboardTrigger(DIK_F1))
	{
		hit_alpatest = hit_alpatest ? false : true;
	}

	// �A���t�@�e�X�g��臒l�ύX
	if (GetKeyboardPress(DIK_I))
	{
		hitAlpha--;
		if (hitAlpha < 0)
		{
			hitAlpha = 0;
		}
	}
	if (GetKeyboardPress(DIK_K))
	{
		hitAlpha++;
		if (hitAlpha > 255)
		{
			hitAlpha = 255;
		}
	}


	PrintDebugProc("*** �A���t�@�e�X�g ***\n");
	PrintDebugProc("ON / OFF�F[F1] ( ���݁F");
	if (hit_alpatest == true)
	{
		PrintDebugProc("ON");
	}
	else
	{
		PrintDebugProc("OFF");
	}
	PrintDebugProc(" )\n");

	if (hit_alpatest == true)
	{
		PrintDebugProc("�A���t�@臒l�F����[I] / ����[K] ( 臒l�F%d )\n", hitAlpha);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���e�X�g�ݒ�
	if (hit_alpatest == true)
	{
		// ���e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, hitAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	}

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntHit = 0; nCntHit < BULLET_MAX; nCntHit++)
	{
		if (hit[nCntHit].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&hit[nCntHit].mtxWorld);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			// �|���S���𐳖ʂɌ�����
#if 1
			// �t�s������Ƃ߂�
			D3DXMatrixInverse(&hit[nCntHit].mtxWorld, NULL, &mtxView);
			hit[nCntHit].mtxWorld._41 = 0.0f;
			hit[nCntHit].mtxWorld._42 = 0.0f;
			hit[nCntHit].mtxWorld._43 = 0.0f;
#else
			hit[nCntHit].mtxWorld._11 = mtxView._11;
			hit[nCntHit].mtxWorld._12 = mtxView._21;
			hit[nCntHit].mtxWorld._13 = mtxView._31;
			hit[nCntHit].mtxWorld._21 = mtxView._12;
			hit[nCntHit].mtxWorld._22 = mtxView._22;
			hit[nCntHit].mtxWorld._23 = mtxView._32;
			hit[nCntHit].mtxWorld._31 = mtxView._13;
			hit[nCntHit].mtxWorld._32 = mtxView._23;
			hit[nCntHit].mtxWorld._33 = mtxView._33;
#endif

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, hit[nCntHit].scl.x,
				hit[nCntHit].scl.y,
				hit[nCntHit].scl.z);
			D3DXMatrixMultiply(&hit[nCntHit].mtxWorld, &hit[nCntHit].mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, hit[nCntHit].pos.x,
				hit[nCntHit].pos.y,
				hit[nCntHit].pos.z);
			D3DXMatrixMultiply(&hit[nCntHit].mtxWorld, &hit[nCntHit].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &hit[nCntHit].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffHit, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apD3DTextureHit[nCntHit % 5]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntHit * 4), NUM_POLYGON);
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
HRESULT MakeVertexHit(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * BULLET_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffHit,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffHit->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntHit = 0; nCntHit < BULLET_MAX; nCntHit++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-HIT_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-HIT_WIDTH / 2.0f, HIT_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(HIT_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(HIT_WIDTH / 2.0f, HIT_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffHit->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexHit(int nIdxHit, float fWidth, float fHeight)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffHit->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxHit * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffHit->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorHit(int nIdxHit, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffHit->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxHit * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffHit->Unlock();
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
int SetHit(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col)
{
	int nIdxHit = -1;

	for (int nCntHit = 0; nCntHit < BULLET_MAX; nCntHit++)
	{
		if (hit[nCntHit].use == false)
		{
			hit[nCntHit].pos = pos;
			hit[nCntHit].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			hit[nCntHit].wide = fWidth;
			hit[nCntHit].height = fHeight;
			hit[nCntHit].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			hit[nCntHit].use = true;
			hit[nCntHit].moveon = false;
			hit[nCntHit].life = HITON;
			// ���_���W�̐ݒ�
			SetVertexHit(nCntHit, fWidth, fHeight);

			// ���_�J���[�̐ݒ�
			SetColorHit(nCntHit, col);

			//// �e�̐ݒ�
			//hit[nCntHit].g_nIdxShadow = CreateShadow(hit[nCntHit].pos, hit[nCntHit].wide, hit[nCntHit].wide);

			//nIdxHit = nCntHit;

			break;
		}
		
	}

	return nIdxHit;
}

//=============================================================================
// ���܂��擾
//=============================================================================
HIT *GetHit(int no)
{
	return &hit[0];
}

