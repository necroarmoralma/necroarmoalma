//=============================================================================
// ���C�t�\��
// �^�C�g����ʏ��� [title.cpp]
// Author : 
//
//=============================================================================
#include "modellife.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_LIFEWAKU	"data/GAMEWINDOW/lifewaku.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_HPGAGE	"data/GAMEWINDOW/lifegreen.png"	// �ǂݍ��ރe�N�X�`���t�@�C����



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexModellife(LPDIRECT3DDEVICE9 pDevice);
void SetColorModellife(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureLifewaku = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffLifewaku = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureLifegage = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffLifegage = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
HRESULT InitModellife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// ���_���̍쐬
	MakeVertexModellife(pDevice);


	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_LIFEWAKU,			// �t�@�C���̖��O
		&g_pD3DTextureLifewaku);	// �ǂݍ��ރ������[


	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_HPGAGE,			// �t�@�C���̖��O
		&g_pD3DTextureLifegage);		// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModellife(void)
{

	if (g_pD3DTextureLifewaku != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureLifewaku->Release();
		g_pD3DTextureLifewaku = NULL;
	}

	if (g_pD3DVtxBuffLifewaku != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffLifewaku->Release();
		g_pD3DVtxBuffLifewaku = NULL;
	}

	if (g_pD3DTextureLifegage != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureLifegage->Release();
		g_pD3DTextureLifegage = NULL;
	}

	if (g_pD3DVtxBuffLifegage != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffLifegage->Release();
		g_pD3DVtxBuffLifegage = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModellife(void)
{
#if 0
	if (g_nCountAppearLifegage >= COUNT_APPERA_HPGAGE)
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
void DrawModellife(void)
{
	MODEL *model = GetModel(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float modelHPhiritsu;		// ���f����?�̔䗦
	float modelHPDraw;			// �\������HP�o�[�̒���

	modelHPhiritsu = (model->Nowlife) / (model->Maxlife);
	// �\������o�[�̒���
	modelHPDraw = (modelHPhiritsu * HPGAGE_WIDTH);
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffLifegage->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(HPGAGE_POS_X, HPGAGE_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(HPGAGE_POS_X + modelHPDraw, HPGAGE_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(HPGAGE_POS_X, HPGAGE_POS_Y + HPGAGE_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(HPGAGE_POS_X + modelHPDraw, HPGAGE_POS_Y + HPGAGE_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffLifegage->Unlock();
	}


	// ���C�t�̘g��`��
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffLifewaku, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureLifewaku);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


	// ���C�t�Q�[�W��`��
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffLifegage, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureLifegage);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexModellife(LPDIRECT3DDEVICE9 pDevice)
{
	
	// ���C�t�Q�[�W�̘g�����̃o�b�t�@�쐬
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&g_pD3DVtxBuffLifewaku,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_pD3DVtxBuffLifewaku->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(LIFEWAKU_POS_X, LIFEWAKU_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(LIFEWAKU_POS_X + LIFEWAKU_WIDTH, LIFEWAKU_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(LIFEWAKU_POS_X, LIFEWAKU_POS_Y + LIFEWAKU_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(LIFEWAKU_POS_X + LIFEWAKU_WIDTH, LIFEWAKU_POS_Y + LIFEWAKU_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffLifewaku->Unlock();
		}

	}
	// ���C�t�Q�[�W�̒��_�o�b�t�@�𐶐�
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&g_pD3DVtxBuffLifegage,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}
	
		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;
	
			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_pD3DVtxBuffLifegage->Lock(0, 0, (void**)&pVtx, 0);
	
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(HPGAGE_POS_X, HPGAGE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(HPGAGE_POS_X + HPGAGE_WIDTH, HPGAGE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(HPGAGE_POS_X, HPGAGE_POS_Y + HPGAGE_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(HPGAGE_POS_X + HPGAGE_WIDTH, HPGAGE_POS_Y + HPGAGE_HEIGHT, 0.0f);
	
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
			g_pD3DVtxBuffLifegage->Unlock();
		}
	}

	return S_OK;
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void SetColorModellife(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffLifewaku->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffLifewaku->Unlock();
	}

}

