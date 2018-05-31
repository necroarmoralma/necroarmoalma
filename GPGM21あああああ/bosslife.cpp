//=============================================================================
// ���C�t�\��
// �^�C�g����ʏ��� [title.cpp]
// Author : 
//
//=============================================================================
#include "bosslife.h"
#include "boss.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BOSSLIFEWAKU	"data/GAMEWINDOW/bosslifewaku.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_BOSSHPGAGE	"data/GAMEWINDOW/lifered.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

// ���C�t�Q�[�W�̘g

#define	BOSSLIFEWAKU_WIDTH		(800)		// ���C�t�Q�[�W�̘g�̕�
#define	BOSSLIFEWAKU_HEIGHT		(80)		// ���C�t�Q�[�W�̘g�̍���
#define	BOSSLIFEWAKU_POS_X		(20)		// ���C�t�Q�[�W�̘g�̈ʒu(X���W)
#define	BOSSLIFEWAKU_POS_Y		(SCREEN_HEIGHT - BOSSLIFEWAKU_HEIGHT)		// ���C�t�Q�[�W�̘g�̈ʒu(Y���W)

// ���C�t��\���Q�[�W
#define	BOSSHPGAGE_WIDTH		(BOSSLIFEWAKU_WIDTH -100)		// ���C�t�Q�[�W�̕�
#define	BOSSHPGAGE_HEIGHT		(BOSSLIFEWAKU_HEIGHT - 60)		// ���C�t�Q�[�W�̍���
#define	BOSSHPGAGE_POS_X		(BOSSLIFEWAKU_POS_X +10)		// ���C�t�Q�[�W�̈ʒu(X���W)
#define	BOSSHPGAGE_POS_Y		(BOSSLIFEWAKU_POS_Y + 10)		// ���C�t�Q�[�W�̈ʒu(Y���W)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBosslife(LPDIRECT3DDEVICE9 pDevice);
void SetColorBosslife(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBossLifewaku = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBossLifewaku = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureBossLifegage = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBossLifegage = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBosslife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// ���_���̍쐬
	MakeVertexBosslife(pDevice);


	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BOSSLIFEWAKU,			// �t�@�C���̖��O
		&g_pD3DTextureBossLifewaku);	// �ǂݍ��ރ������[


	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BOSSHPGAGE,			// �t�@�C���̖��O
		&g_pD3DTextureBossLifegage);		// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBosslife(void)
{

	if (g_pD3DTextureBossLifewaku != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBossLifewaku->Release();
		g_pD3DTextureBossLifewaku = NULL;
	}

	if (g_pD3DVtxBuffBossLifewaku != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffBossLifewaku->Release();
		g_pD3DVtxBuffBossLifewaku = NULL;
	}

	if (g_pD3DTextureBossLifegage != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBossLifegage->Release();
		g_pD3DTextureBossLifegage = NULL;
	}

	if (g_pD3DVtxBuffBossLifegage != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffBossLifegage->Release();
		g_pD3DVtxBuffBossLifegage = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBosslife(void)
{
#if 0
	if (g_nCountAppearBossLifegage >= COUNT_APPERA_BOSSHPGAGE)
	{
		g_nConutDemo++;
		if (g_nConutDemo > COUNT_WAIT_DEMO)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
#endif



}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBosslife(void)
{
	BOSS *boss = GetBoss(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float bossHPhiritsu;		// ���f����?�̔䗦
	float bossHPDraw;			// �\������HP�o�[�̒���

	bossHPhiritsu = (boss->boss_life) / (boss->boss_maxlife);
	// �\������o�[�̒���
	bossHPDraw = (bossHPhiritsu * BOSSHPGAGE_WIDTH);
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBossLifegage->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X, BOSSHPGAGE_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X + bossHPDraw, BOSSHPGAGE_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X, BOSSHPGAGE_POS_Y + BOSSHPGAGE_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X + bossHPDraw, BOSSHPGAGE_POS_Y + BOSSHPGAGE_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBossLifegage->Unlock();
	}


	// ���C�t�̘g��`��
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffBossLifewaku, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureBossLifewaku);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


	// ���C�t�Q�[�W��`��
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffBossLifegage, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureBossLifegage);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBosslife(LPDIRECT3DDEVICE9 pDevice)
{

	// ���C�t�Q�[�W�̘g�����̃o�b�t�@�쐬
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&g_pD3DVtxBuffBossLifewaku,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_pD3DVtxBuffBossLifewaku->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(BOSSLIFEWAKU_POS_X, BOSSLIFEWAKU_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BOSSLIFEWAKU_POS_X + BOSSLIFEWAKU_WIDTH, BOSSLIFEWAKU_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(BOSSLIFEWAKU_POS_X, BOSSLIFEWAKU_POS_Y + BOSSLIFEWAKU_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BOSSLIFEWAKU_POS_X + BOSSLIFEWAKU_WIDTH, BOSSLIFEWAKU_POS_Y + BOSSLIFEWAKU_HEIGHT, 0.0f);

			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// ���_�f�[�^���A�����b�N����
			g_pD3DVtxBuffBossLifewaku->Unlock();
		}

	}
	// ���C�t�Q�[�W�̒��_�o�b�t�@�𐶐�
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&g_pD3DVtxBuffBossLifegage,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_pD3DVtxBuffBossLifegage->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X, BOSSHPGAGE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X + BOSSHPGAGE_WIDTH, BOSSHPGAGE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X, BOSSHPGAGE_POS_Y + BOSSHPGAGE_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BOSSHPGAGE_POS_X + BOSSHPGAGE_WIDTH, BOSSHPGAGE_POS_Y + BOSSHPGAGE_HEIGHT, 0.0f);

			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// ���_�f�[�^���A�����b�N����
			g_pD3DVtxBuffBossLifegage->Unlock();
		}
	}

	return S_OK;
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void SetColorBosslife(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBossLifewaku->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBossLifewaku->Unlock();
	}

}

