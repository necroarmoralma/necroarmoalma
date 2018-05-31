//=============================================================================
//
// ���f������ [skydoom.cpp]
// Author : GP11B243 33 �R�{ �s��
//=============================================================================
#include "skydoom.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"
#include "meshfield.h"
#include "model.h"
#include "bulletmk2.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ��#define	SKYDOOM_AIRPLANE		"data/MODEL/chesboad.blend.x"	// �ǂݍ��ރ��f����
#define	SKYDOOM_AIRPLANE		"data/MODEL/skydoom0.x"
#define	SKYDOOM_CIRCLE			"data/STAGE/skydoom.x"
#define	TEXTURESKYDOOM			"data/TEXTURE/skydome0102.png"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void skydoomshot(void);
//void skydoombeam(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureSkydoom;			// �e�N�X�`���ǂݍ��ݏꏊ
												//LPD3DXMESH			g_pD3DXMeshSkydoom;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
												//LPD3DXBUFFER		g_pD3DXBuffMatSkydoom;		// ���b�V���̃}�e���A�������i�[
												//DWORD				g_nNumMatSkydoom;				// �������̑���
												/*
												D3DXMATRIX			skydoom->World;			// ���[���h�}�g���b�N�X
												D3DXVECTOR3			skydoom->pos;					// ���݂̈ʒu
												D3DXVECTOR3			skydoom->move;				// �ړ���
												D3DXVECTOR3			skydoom->rot;					// ���݂̌���
												D3DXVECTOR3			skydoom->rotDest;				// �ړI�̌���
												*/

int					skydoomnidxShadow;				// �eID
float				skydoomsizeShadow;				// �e�̃T�C�Y
D3DXCOLOR			skydoomcolShadow;				// �e�̐F
SKYDOOM				skydoomWk[1];					// ���f���\����(���f���͂P�j

int					skydoomactcheck;					// �Ă���
													//=============================================================================
													// ����������
													//=============================================================================
HRESULT InitSkydoom(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SKYDOOM *skydoom = &skydoomWk[0];
	D3DXVECTOR3 rotCamera;

	// HP�̐ݒ�
	skydoom->skydoom_maxlife = SKYDOOMLIFE;
	skydoom->skydoom_life = skydoom->skydoom_maxlife;

	g_pD3DTextureSkydoom = NULL;
	skydoom->MeshSkydoom = NULL;
	skydoom->BuffMatSkydoom = NULL;

	skydoom->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	skydoom->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	skydoom->puremove = skydoom->move;
	skydoom->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	skydoom->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	skydoom->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);


	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(SKYDOOM_CIRCLE,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&skydoom->BuffMatSkydoom,
		NULL,
		&skydoom->NumMatSkydoom,
		&skydoom->MeshSkydoom)))
	{
		return E_FAIL;
	}


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURESKYDOOM,		// �t�@�C���̖��O
		&g_pD3DTextureSkydoom);	// �ǂݍ��ރ������[


							// �e�̐���
							//skydoomnidxShadow = CreateShadow(skydoom->pos, 25.0f, 25.0f);

							//skydoomsizeShadow = 25.0f;
							//skydoomcolShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSkydoom(void)
{
	SKYDOOM *skydoom = &skydoomWk[0];
	if (g_pD3DTextureSkydoom != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureSkydoom->Release();
		g_pD3DTextureSkydoom = NULL;
	}

	if (skydoom->MeshSkydoom != NULL)
	{// ���b�V���̊J��
		skydoom->MeshSkydoom->Release();
		skydoom->MeshSkydoom = NULL;
	}

	if (skydoom->BuffMatSkydoom != NULL)
	{// �}�e���A���̊J��
		skydoom->BuffMatSkydoom->Release();
		skydoom->BuffMatSkydoom = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSkydoom(void)
{
	D3DXVECTOR3 rotCamera;
	SKYDOOM *skydoom = &skydoomWk[0];
	MODEL *model = GetModel(0);
	float fDiffRotY;
	D3DXVECTOR3 SubposSkydoomtoModel;
	float rotcheckBtoM;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSkydoom(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	SKYDOOM *skydoom = &skydoomWk[0];

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&skydoom->World);


	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, skydoom->scl.x, skydoom->scl.y, skydoom->scl.z);
	D3DXMatrixMultiply(&skydoom->World, &skydoom->World, &mtxScl);


	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, skydoom->rot.y, skydoom->rot.x, skydoom->rot.z);
	D3DXMatrixMultiply(&skydoom->World, &skydoom->World, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, skydoom->pos.x, skydoom->pos.y, skydoom->pos.z);
	D3DXMatrixMultiply(&skydoom->World, &skydoom->World, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &skydoom->World);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)skydoom->BuffMatSkydoom->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)skydoom->NumMatSkydoom; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureSkydoom);

		// �`��
		skydoom->MeshSkydoom->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionSkydoom(void)
{
	SKYDOOM *skydoom = &skydoomWk[0];
	return skydoom->pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationSkydoom(void)
{
	SKYDOOM *skydoom = &skydoomWk[0];
	return skydoom->rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestSkydoom(void)
{
	SKYDOOM *skydoom = &skydoomWk[0];
	return skydoom->rotDest;
}

//*****************************************************************************
// �Q�b�g�֐�
//*****************************************************************************
SKYDOOM *GetSkydoom(int no)
{
	return(&skydoomWk[0]);
}
