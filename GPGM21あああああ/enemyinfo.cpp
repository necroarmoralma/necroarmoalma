//=============================================================================
// �t�@�C����:	infowindow.cpp
// ����:		���ڕW�ƓG���C�t�̏��
// Author : �R�{ �s��
//
//=============================================================================
#include "enemyinfo.h"
#include "main.h"
#include "boss.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_ENEMYINFOWAKU	"data/GAMEWINDOW/mokuhyouwindow.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ENEMYINFOICON	"data/GAMEWINDOW/enemyinfo.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_ENEMYLIFEGAGE	"data/GAMEWINDOW/lifered.png"
#define ENEMYLIFE


#define	ENEMYINFOWAKU_WIDTH		(200)		// ���C�t�Q�[�W�̘g�̕�
#define	ENEMYINFOWAKU_HEIGHT		(200)		// ���C�t�Q�[�W�̘g�̍���
#define	ENEMYINFOWAKU_POS_X		(SCREEN_WIDTH-ENEMYINFOWAKU_WIDTH)		// ���C�t�Q�[�W�̘g�̈ʒu(X���W)
#define	ENEMYINFOWAKU_POS_Y		(50)		// ���C�t�Q�[�W�̘g�̈ʒu(Y���W)

// �G�l�~�[�A�C�R����
#define	ENEMYINFOICON_WIDTH				(ENEMYINFOWAKU_WIDTH)		// ���C�t�Q�[�W�̕�
#define	ENEMYINFOICON_HEIGHT			(50)		// ���C�t�Q�[�W�̍���
#define	ENEMYINFOICON_POS_X				(SCREEN_WIDTH-ENEMYINFOWAKU_WIDTH)		// ���C�t�Q�[�W�̈ʒu(X���W)
#define	ENEMYINFOICON_POS_Y				(ENEMYINFOWAKU_POS_Y-10 + ENEMYINFOWAKU_HEIGHT)		// ���C�t�Q�[�W�̈ʒu(Y���W)

// �G�l�~�[���C�t(�G�l�~�[�A�C�R���ɏd�˂�)
#define	ENEMYLIFEGAGE_WIDTH				(ENEMYINFOICON_WIDTH - 40)		// ���C�t�o�[�̕�
#define	ENEMYLIFEGAGE_HEIGHT			(ENEMYINFOICON_HEIGHT -30)		// ���C�t�o�[�̍���
#define	ENEMYLIFEGAGE_POS_X				(ENEMYINFOICON_POS_X+30)							// ���C�t�o�[�̈ʒu(X���W)
#define	ENEMYLIFEGAGE_POS_Y				(ENEMYINFOICON_POS_Y + 15)		// ���C�t�o�[�̈ʒu(Y���W)



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemyinfo(LPDIRECT3DDEVICE9 pDevice);
void SetColorEnemyinfo(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyinfowaku = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemyinfowaku = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyinfogage = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemyinfogage = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemylife = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemylife = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyinfo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// ���_���̍쐬
	MakeVertexEnemyinfo(pDevice);


	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_ENEMYINFOWAKU,			// �t�@�C���̖��O
		&g_pD3DTextureEnemyinfowaku);	// �ǂݍ��ރ������[


	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_ENEMYINFOICON,			// �t�@�C���̖��O
		&g_pD3DTextureEnemyinfogage);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_ENEMYLIFEGAGE,			// �t�@�C���̖��O
		&g_pD3DTextureEnemylife);		// �ǂݍ��ރ������[


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyinfo(void)
{

	if (g_pD3DTextureEnemyinfowaku != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemyinfowaku->Release();
		g_pD3DTextureEnemyinfowaku = NULL;
	}

	if (g_pD3DVtxBuffEnemyinfowaku != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEnemyinfowaku->Release();
		g_pD3DVtxBuffEnemyinfowaku = NULL;
	}

	// �A�C�R��
	if (g_pD3DTextureEnemyinfogage != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemyinfogage->Release();
		g_pD3DTextureEnemyinfogage = NULL;
	}

	if (g_pD3DVtxBuffEnemyinfogage != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEnemyinfogage->Release();
		g_pD3DVtxBuffEnemyinfogage = NULL;
	}

	// �G�̃��C�t�Q�[�W

	if (g_pD3DTextureEnemyinfogage != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemylife->Release();
		g_pD3DTextureEnemylife = NULL;
	}

	if (g_pD3DVtxBuffEnemyinfogage != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEnemylife->Release();
		g_pD3DVtxBuffEnemylife = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyinfo(void)
{
#if 0
	if (g_nCountAppearEnemyinfogage >= COUNT_APPERA_ENEMYINFOICON)
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
void DrawEnemyinfo(void)
{
	BOSS *boss = GetBoss(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	float bossHPhiritsu;		// ���f����?�̔䗦
	float bossHPDraw;			// �\������HP�o�[�̒���

	// ���C�t�̘g��`��
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemyinfowaku, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureEnemyinfowaku);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


	// �G�l�~�[�A�C�R��(���o�[)�`��
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemyinfogage, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureEnemyinfogage);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}

	// �G�l�~�[�̃��C�t�Q�[�W��`��
	bossHPhiritsu = (boss->boss_life) / (boss->boss_maxlife);
	// �\������o�[�̒���
	bossHPDraw = (bossHPhiritsu * ENEMYLIFEGAGE_WIDTH);
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemylife->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X, ENEMYLIFEGAGE_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X + bossHPDraw, ENEMYLIFEGAGE_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X, ENEMYLIFEGAGE_POS_Y + ENEMYLIFEGAGE_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X + bossHPDraw, ENEMYLIFEGAGE_POS_Y + ENEMYLIFEGAGE_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffEnemylife->Unlock();
	}
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemylife, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureEnemylife);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemyinfo(LPDIRECT3DDEVICE9 pDevice)
{


	// �G�l�~�[���̘g�����̃o�b�t�@�쐬
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&g_pD3DVtxBuffEnemyinfowaku,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_pD3DVtxBuffEnemyinfowaku->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(ENEMYINFOWAKU_POS_X, ENEMYINFOWAKU_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(ENEMYINFOWAKU_POS_X + ENEMYINFOWAKU_WIDTH, ENEMYINFOWAKU_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(ENEMYINFOWAKU_POS_X, ENEMYINFOWAKU_POS_Y + ENEMYINFOWAKU_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(ENEMYINFOWAKU_POS_X + ENEMYINFOWAKU_WIDTH, ENEMYINFOWAKU_POS_Y + ENEMYINFOWAKU_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffEnemyinfowaku->Unlock();
		}

	}
	// �G�l�~�[�A�C�R���̒��_�o�b�t�@�𐶐�
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&g_pD3DVtxBuffEnemyinfogage,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_pD3DVtxBuffEnemyinfogage->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(ENEMYINFOICON_POS_X, ENEMYINFOICON_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(ENEMYINFOICON_POS_X + ENEMYINFOICON_WIDTH, ENEMYINFOICON_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(ENEMYINFOICON_POS_X, ENEMYINFOICON_POS_Y + ENEMYINFOICON_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(ENEMYINFOICON_POS_X + ENEMYINFOICON_WIDTH, ENEMYINFOICON_POS_Y + ENEMYINFOICON_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffEnemyinfogage->Unlock();
		}
	}

	// �G�l�~�[���C�t�Q�[�W�̒��_�o�b�t�@�𐶐�
	{
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&g_pD3DVtxBuffEnemylife,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_pD3DVtxBuffEnemylife->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X, ENEMYLIFEGAGE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X + ENEMYLIFEGAGE_WIDTH, ENEMYLIFEGAGE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X, ENEMYLIFEGAGE_POS_Y + ENEMYLIFEGAGE_HEIGHT, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(ENEMYLIFEGAGE_POS_X + ENEMYLIFEGAGE_WIDTH, ENEMYLIFEGAGE_POS_Y + ENEMYLIFEGAGE_HEIGHT, 0.0f);

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
			g_pD3DVtxBuffEnemylife->Unlock();
		}
	}



	return S_OK;
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void SetColorEnemyinfo(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemyinfowaku->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEnemyinfowaku->Unlock();
	}

}

