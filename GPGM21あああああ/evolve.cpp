//=============================================================================
// ���C�t�\��
// �^�C�g����ʏ��� [title.cpp]
// Author : 
//
//=============================================================================
#include "evolve.h"
#include "model.h"
#include "modellife.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EVOLVEWAKU	"data/GAMEWINDOW/evolve.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EVOLVEGAGE	"data/GAMEWINDOW/lifeegreen.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

// ���C�t�Q�[�W�̘g
#define	EVOLVEWAKU_POS_X		(LIFEWAKU_POS_X+LIFEWAKU_WIDTH)		// ���C�t�Q�[�W�̘g�̈ʒu(X���W)
#define	EVOLVEWAKU_POS_Y		(LIFEWAKU_POS_Y)		// ���C�t�Q�[�W�̘g�̈ʒu(Y���W)
#define	EVOLVEWAKU_WIDTH		(500)		// ���C�t�Q�[�W�̘g�̕�
#define	EVOLVEWAKU_HEIGHT		(80)		// ���C�t�Q�[�W�̘g�̍���

// ���C�t��\���Q�[�W
#define	EVOLVEGAGE_POS_X				(HPGAGE_WIDTH + 10)		// ���C�t�Q�[�W�̈ʒu(X���W)
#define	EVOLVEGAGE_POS_Y				(HPGAGE_POS_Y)		// ���C�t�Q�[�W�̈ʒu(Y���W)
#define	EVOLVEGAGE_WIDTH				(470)		// ���C�t�Q�[�W�̕�
#define	EVOLVEGAGE_HEIGHT			(20)		// ���C�t�Q�[�W�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexModelevolve(LPDIRECT3DDEVICE9 pDevice);
void SetColorModelevolve(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEvolvewaku = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEvolvewaku = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureEvolvegage = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEvolvegage = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
HRESULT InitModelevolve(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// ���_���̍쐬
	MakeVertexModelevolve(pDevice);


	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EVOLVEWAKU,			// �t�@�C���̖��O
		&g_pD3DTextureEvolvewaku);	// �ǂݍ��ރ������[


	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EVOLVEGAGE,			// �t�@�C���̖��O
		&g_pD3DTextureEvolvegage);		// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModelevolve(void)
{

	if (g_pD3DTextureEvolvewaku != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEvolvewaku->Release();
		g_pD3DTextureEvolvewaku = NULL;
	}

	if (g_pD3DVtxBuffEvolvewaku != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEvolvewaku->Release();
		g_pD3DVtxBuffEvolvewaku = NULL;
	}

	if (g_pD3DTextureEvolvegage != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEvolvegage->Release();
		g_pD3DTextureEvolvegage = NULL;
	}

	if (g_pD3DVtxBuffEvolvegage != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEvolvegage->Release();
		g_pD3DVtxBuffEvolvegage = NULL;
	}
}//*void

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModelevolve(void)
{
#if 0
	if (g_nCountAppearEvolvegage >= COUNT_APPERA_EVOLVEGAGE)
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
void DrawModelevolve(void)
{
	MODEL *model = GetModel(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float modelEVOLVEhiritsu;		// �䗦
	float modelEVOLVEDraw;			// �\������EVOLVE�o�[�̒���

	modelEVOLVEhiritsu = (model->nowshot_evolve) / (model->shot_evolve);
	// �\������o�[�̒���
	modelEVOLVEDraw = (modelEVOLVEhiritsu * EVOLVEGAGE_WIDTH);
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEvolvegage->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X, EVOLVEGAGE_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X + modelEVOLVEDraw, EVOLVEGAGE_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X, EVOLVEGAGE_POS_Y + EVOLVEGAGE_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X + modelEVOLVEDraw, EVOLVEGAGE_POS_Y + EVOLVEGAGE_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffEvolvegage->Unlock();
	}


	// ���C�t�̘g��`��
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEvolvewaku, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureEvolvewaku);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


	// ���C�t�Q�[�W��`��
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEvolvegage, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureEvolvegage);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexModelevolve(LPDIRECT3DDEVICE9 pDevice)
{

	// ���C�t�Q�[�W�̘g�����̃o�b�t�@�쐬
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&g_pD3DVtxBuffEvolvewaku,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_pD3DVtxBuffEvolvewaku->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(EVOLVEWAKU_POS_X, EVOLVEWAKU_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(EVOLVEWAKU_POS_X + EVOLVEWAKU_WIDTH, EVOLVEWAKU_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(EVOLVEWAKU_POS_X, EVOLVEWAKU_POS_Y + EVOLVEWAKU_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EVOLVEWAKU_POS_X + EVOLVEWAKU_WIDTH, EVOLVEWAKU_POS_Y + EVOLVEWAKU_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffEvolvewaku->Unlock();
		}

	}
	// ���C�t�Q�[�W�̒��_�o�b�t�@�𐶐�
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&g_pD3DVtxBuffEvolvegage,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_pD3DVtxBuffEvolvegage->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X, EVOLVEGAGE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X + EVOLVEGAGE_WIDTH, EVOLVEGAGE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X, EVOLVEGAGE_POS_Y + EVOLVEGAGE_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EVOLVEGAGE_POS_X + EVOLVEGAGE_WIDTH, EVOLVEGAGE_POS_Y + EVOLVEGAGE_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffEvolvegage->Unlock();
		}
	}

	return S_OK;
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void SetColorModelevolve(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEvolvewaku->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEvolvewaku->Unlock();
	}

}

