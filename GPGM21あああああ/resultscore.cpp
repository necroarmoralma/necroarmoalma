//=============================================================================
//
// �X�R�A���� [resultscore.cpp]
// Author : 
//
//=============================================================================
#include "resultscore.h"



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME_SCORE	"data/TEXTURE/frame_score.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SCORE_SIZE_X		(100.0f)							// �X�R�A�̐����̕�
#define	SCORE_SIZE_Y		(100.0f)							// �X�R�A�̐����̍���
#define	SCORE_INTERVAL_X	(0.0f)							// �X�R�A�̐����̕\���Ԋu

#define	NUM_PLACE			(5)								// �X�R�A�̌���

#define	SCORE_POS_X			(SCREEN_CENTER_X - (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE +180.0f)	// �X�R�A�̕\����ʒu�w���W
#define	SCORE_POS_Y			(SCREEN_CENTER_Y-150.0f)																	// �X�R�A�̕\����ʒu�x���W

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResultscore(LPDIRECT3DDEVICE9 pDevice);
void SetTextureResultscore(int idx, int number);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResultscore[2] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultscore = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXVECTOR3				g_posResultscore;						// �ʒu
D3DXVECTOR3				g_rotResultscore;						// ����

int						g_resultscore;						// �X�R�A
RESULTSCORE				resultscoreWk[1];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitResultscore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posResultscore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotResultscore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �X�R�A�̏�����
	g_resultscore = 0;

	// ���_���̍쐬
	MakeVertexResultscore(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SCORE,			// �t�@�C���̖��O
		&g_pD3DTextureResultscore[0]);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FRAME_SCORE,		// �t�@�C���̖��O
		&g_pD3DTextureResultscore[1]);	// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResultscore(void)
{
	if(g_pD3DTextureResultscore[0] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResultscore[0]->Release();
		g_pD3DTextureResultscore[0] = NULL;
	}
	if(g_pD3DTextureResultscore[1] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResultscore[1]->Release();
		g_pD3DTextureResultscore[1] = NULL;
	}

	if(g_pD3DVtxBuffResultscore != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffResultscore->Release();
		g_pD3DVtxBuffResultscore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultscore(void)
{
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int number;

		number = (g_resultscore % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		SetTextureResultscore(nCntPlace, number);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultscore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultscore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResultscore[0]);

	// �|���S���̕`��
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}

	// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pD3DTextureResultscore[1]);

	// �|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResultscore(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffResultscore,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))											// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffResultscore->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

			// rhw�̐ݒ�
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
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y - 25, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y - 25, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y + 55, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y + 55, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffResultscore->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureResultscore(int idx, int number)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffResultscore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffResultscore->Unlock();
}

//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void ChangeResultscore(int value)
{
	g_resultscore += value;
	if(g_resultscore < 0)
	{
		g_resultscore = 0;
	}
	else if(g_resultscore >= (int)(powf(10.0f, (float)(NUM_PLACE + 1))))
	{
		g_resultscore = (int)(powf(10.0f, (float)(NUM_PLACE + 1))) - 1;
	}
}

//**************************************************************************************
//	�Q�b�g�֐�
//**************************************************************************************
RESULTSCORE *GetResultscore(int no)
{
	return(&resultscoreWk[0]);
}
