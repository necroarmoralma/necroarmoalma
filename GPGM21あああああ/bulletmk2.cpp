//=============================================================================
//
// tama���� [bulletmk2.cpp]
// Author : HAL�Q�[���w�ȓ�N���ے�1�N�@�R�{�s��
// tree.cpp���̂܂܃R�s
//=============================================================================
#include "bulletmk2.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "debugproc.h"
#include "model.h"
#include "meshfield.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BULLETMK2		"data/TEXTURE/karinotama.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VALUE_MOVE_BULLETMK2		(9.00f)							// �ړ����x
#define BULLETMK2SPEED				(9.5f)
#define BULLETMK2LIFE				(10 * 60)						// �������ԁ@�b��*FPS

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBulletmk2(LPDIRECT3DDEVICE9 pDevice);
void SetVertexBulletmk2(int nIdxBulletmk2, float fWidth, float fHeight);
void SetColorBulletmk2(int nIdxBulletmk2, D3DXCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureBulletmk2[5] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBulletmk2 = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

BULLETMK2				bulletmk2[BULLET_MAX];				// �e�̍\���̔z��
bool					bullet_alpatest;					// �A���t�@�e�X�gON/OFF
int						bulletAlpha;						// �A���t�@�e�X�g��臒l

char *bulletFileName[] =
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
HRESULT InitBulletmk2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexBulletmk2(pDevice);

	// �e�N�X�`���̓ǂݍ���
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
			TEXTURE_BULLETMK2,			// �t�@�C���̖��O
			&g_apD3DTextureBulletmk2[nCntTex]);	// �ǂݍ��ރ������[
	}

	for (int nCntBulletmk2 = 0; nCntBulletmk2 < BULLET_MAX; nCntBulletmk2++)
	{
		//bulletmk2[nCntBulletmk2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//bulletmk2[nCntBulletmk2].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		//bulletmk2[nCntBulletmk2].wide = BULLETMK2_WIDTH;
		//bulletmk2[nCntBulletmk2].height = BULLETMK2_HEIGHT;
		//bulletmk2[nCntBulletmk2].use = false;
		//bulletmk2[nCntBulletmk2].moveon = false;									//
	}

	bullet_alpatest = true;
	bulletAlpha = 0x0;


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBulletmk2(void)
{
	// �����I�ɂ��ׂĂ𖢎g�p�ɁI

	for (int i=0; i < BULLET_MAX; i++)
	{
		bulletmk2[i].use = false;
	} 
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (g_apD3DTextureBulletmk2[nCntTex] != NULL)
		{// �e�N�X�`���̊J��
			g_apD3DTextureBulletmk2[nCntTex]->Release();
			g_apD3DTextureBulletmk2[nCntTex] = NULL;
		}
	}

	if (g_pD3DVtxBuffBulletmk2 != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffBulletmk2->Release();
		g_pD3DVtxBuffBulletmk2 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBulletmk2(void)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);

	rotCamera = GetRotCamera();


	// �ړ��e�X�g
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bulletmk2[i].use == true)

		{
			// ���x�v����Ɖ�]�͈�x�m�肵���炻�̂܂�
			// �ړ��ʂ����܂��Ă��Ȃ��Ȃ猈�߂�
			if (bulletmk2[i].moveon == false)
			{
				bulletmk2[i].rot.y += bulletmk2[i].hoseix;
				bulletmk2[i].moveon = true;
				bulletmk2[i].move.x = (sinf(D3DX_PI + bulletmk2[i].rot.y) * VALUE_MOVE_MODEL *3.5f);	// 3.5�͒e�������Ă邾���ł���
				bulletmk2[i].move.z = (cosf(D3DX_PI + bulletmk2[i].rot.y) * VALUE_MOVE_MODEL *3.5f);
				bulletmk2[i].move.y = bulletmk2[i].hoseiz;
			}

			//+model->rot.y
			//	+ model->rot.y

			/// �ʒu�ړ�
			bulletmk2[i].pos.x += bulletmk2[i].move.x;
			bulletmk2[i].pos.z += bulletmk2[i].move.z;
			bulletmk2[i].pos.y += bulletmk2[i].move.y;

			// ���C�t���ȉ��Ȃ�폜
			bulletmk2[i].life--;
			if(bulletmk2[i].life <= 0)
			{
				bulletmk2[i].use = false;
			}

		}
	}
	for (int nCntBulletmk2 = 0; nCntBulletmk2 < BULLET_MAX; nCntBulletmk2++)
	{
		if (bulletmk2[nCntBulletmk2].use == true)
		{
			// �e�̈ʒu�ݒ�
			SetPositionShadow(bulletmk2[nCntBulletmk2].g_nIdxShadow, D3DXVECTOR3(bulletmk2[nCntBulletmk2].pos.x, 0.1f, bulletmk2[nCntBulletmk2].pos.z));
		}
	}

	// �A���t�@�e�X�gON/OFF
	if (GetKeyboardTrigger(DIK_F1))
	{
		bullet_alpatest = bullet_alpatest ? false : true;
	}

	// �A���t�@�e�X�g��臒l�ύX
	if (GetKeyboardPress(DIK_I))
	{
		bulletAlpha--;
		if (bulletAlpha < 0)
		{
			bulletAlpha = 0;
		}
	}
	if (GetKeyboardPress(DIK_K))
	{
		bulletAlpha++;
		if (bulletAlpha > 255)
		{
			bulletAlpha = 255;
		}
	}

	PrintDebugProc("*** �A���t�@�e�X�g ***\n");
	PrintDebugProc("ON / OFF�F[F1] ( ���݁F");
	if (bullet_alpatest == true)
	{
		PrintDebugProc("ON");
	}
	else
	{
		PrintDebugProc("OFF");
	}
	PrintDebugProc(" )\n");

	if (bullet_alpatest == true)
	{
		PrintDebugProc("�A���t�@臒l�F����[I] / ����[K] ( 臒l�F%d )\n", bulletAlpha);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBulletmk2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���e�X�g�ݒ�
	if (bullet_alpatest == true)
	{
		// ���e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, bulletAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	}

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBulletmk2 = 0; nCntBulletmk2 < BULLET_MAX; nCntBulletmk2++)
	{
		if (bulletmk2[nCntBulletmk2].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&bulletmk2[nCntBulletmk2].mtxWorld);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			// �|���S���𐳖ʂɌ�����
#if 1
			// �t�s������Ƃ߂�
			D3DXMatrixInverse(&bulletmk2[nCntBulletmk2].mtxWorld, NULL, &mtxView);
			bulletmk2[nCntBulletmk2].mtxWorld._41 = 0.0f;
			bulletmk2[nCntBulletmk2].mtxWorld._42 = 0.0f;
			bulletmk2[nCntBulletmk2].mtxWorld._43 = 0.0f;
#else
			bulletmk2[nCntBulletmk2].mtxWorld._11 = mtxView._11;
			bulletmk2[nCntBulletmk2].mtxWorld._12 = mtxView._21;
			bulletmk2[nCntBulletmk2].mtxWorld._13 = mtxView._31;
			bulletmk2[nCntBulletmk2].mtxWorld._21 = mtxView._12;
			bulletmk2[nCntBulletmk2].mtxWorld._22 = mtxView._22;
			bulletmk2[nCntBulletmk2].mtxWorld._23 = mtxView._32;
			bulletmk2[nCntBulletmk2].mtxWorld._31 = mtxView._13;
			bulletmk2[nCntBulletmk2].mtxWorld._32 = mtxView._23;
			bulletmk2[nCntBulletmk2].mtxWorld._33 = mtxView._33;
#endif

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, bulletmk2[nCntBulletmk2].scl.x,
				bulletmk2[nCntBulletmk2].scl.y,
				bulletmk2[nCntBulletmk2].scl.z);
			D3DXMatrixMultiply(&bulletmk2[nCntBulletmk2].mtxWorld, &bulletmk2[nCntBulletmk2].mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, bulletmk2[nCntBulletmk2].pos.x,
				bulletmk2[nCntBulletmk2].pos.y,
				bulletmk2[nCntBulletmk2].pos.z);
			D3DXMatrixMultiply(&bulletmk2[nCntBulletmk2].mtxWorld, &bulletmk2[nCntBulletmk2].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &bulletmk2[nCntBulletmk2].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffBulletmk2, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apD3DTextureBulletmk2[nCntBulletmk2 % 5]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntBulletmk2 * 4), NUM_POLYGON);
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
HRESULT MakeVertexBulletmk2(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * BULLET_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffBulletmk2,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBulletmk2->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntBulletmk2 = 0; nCntBulletmk2 < BULLET_MAX; nCntBulletmk2++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-BULLETMK2_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-BULLETMK2_WIDTH / 2.0f, BULLETMK2_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(BULLETMK2_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULLETMK2_WIDTH / 2.0f, BULLETMK2_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffBulletmk2->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBulletmk2(int nIdxBulletmk2, float fWidth, float fHeight)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBulletmk2->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBulletmk2 * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBulletmk2->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorBulletmk2(int nIdxBulletmk2, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBulletmk2->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBulletmk2 * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBulletmk2->Unlock();
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
int SetBulletmk2(D3DXVECTOR3 pos, float fWidth, float fHeight,float SIDE,float UP, D3DXCOLOR col)
{
	MODEL *model = GetModel(0);
	int nIdxBulletmk2 = -1;

	for (int nCntBulletmk2 = 0; nCntBulletmk2 < BULLET_MAX; nCntBulletmk2++)
	{
		if (bulletmk2[nCntBulletmk2].use == false)
		{
			bulletmk2[nCntBulletmk2].rot = model->rot;
			bulletmk2[nCntBulletmk2].pos = D3DXVECTOR3(model->pos.x, model->pos.y, model->pos.z);
			bulletmk2[nCntBulletmk2].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			bulletmk2[nCntBulletmk2].wide = fWidth;
			bulletmk2[nCntBulletmk2].height = fHeight;
			bulletmk2[nCntBulletmk2].move = D3DXVECTOR3(0.0f,0.0f,0.0f);
			bulletmk2[nCntBulletmk2].use = true;
			bulletmk2[nCntBulletmk2].moveon = false;
			bulletmk2[nCntBulletmk2].hoseix = SIDE;
			bulletmk2[nCntBulletmk2].hoseiz = UP;
			bulletmk2[nCntBulletmk2].life = BULLETMK2LIFE;
			// ���_���W�̐ݒ�
			SetVertexBulletmk2(nCntBulletmk2, fWidth, fHeight);

			// ���_�J���[�̐ݒ�
			SetColorBulletmk2(nCntBulletmk2, col);

			// �e�̐ݒ�
			bulletmk2[nCntBulletmk2].g_nIdxShadow = CreateShadow(bulletmk2[nCntBulletmk2].pos, bulletmk2[nCntBulletmk2].wide, bulletmk2[nCntBulletmk2].wide);

			nIdxBulletmk2 = nCntBulletmk2;

			break;
		}
	}

	return nIdxBulletmk2;
}

//=============================================================================
// ���܂��擾
//=============================================================================
BULLETMK2 *GetBulletmk2(int no)
{
	return &bulletmk2[0];
}

