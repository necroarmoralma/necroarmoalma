//=============================================================================
//
// ���f������ [map.cpp]
// Author : GP11B243 33 �R�{ �s��
//=============================================================================
#include "map.h"
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
#define MAP_SCHOOL "data/STAGE/stage0613.x"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void mapshot(void);
//void mapbeam(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureMap;			// �e�N�X�`���ǂݍ��ݏꏊ
//LPD3DXMESH			g_pD3DXMeshMap;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
//LPD3DXBUFFER		g_pD3DXBuffMatMap;		// ���b�V���̃}�e���A�������i�[
//DWORD				g_nNumMatMap;				// �������̑���
												/*
D3DXMATRIX			map->World;			// ���[���h�}�g���b�N�X
D3DXVECTOR3			map->pos;					// ���݂̈ʒu
D3DXVECTOR3			map->move;				// �ړ���
D3DXVECTOR3			map->rot;					// ���݂̌���
D3DXVECTOR3			map->rotDest;				// �ړI�̌���
												*/

int					mapnidxShadow;				// �eID
float				mapsizeShadow;				// �e�̃T�C�Y
D3DXCOLOR			mapcolShadow;				// �e�̐F
MAP				mapWk[1];					// ���f���\����(���f���͂P�j

int					mapactcheck;					// �Ă���
//=============================================================================
// ����������
//=============================================================================
HRESULT InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MAP *map = &mapWk[0];
	D3DXVECTOR3 rotCamera;

	// HP�̐ݒ�
	map->map_maxlife = MAPLIFE;
	map->map_life = map->map_maxlife;

	g_pD3DTextureMap = NULL;
	map->MeshMap = NULL;
	map->BuffMatMap = NULL;

	map->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	map->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	map->puremove = map->move;
	map->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	map->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	map->scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(MAP_SCHOOL,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&map->BuffMatMap,
		NULL,
		&map->NumMatMap,
		&map->MeshMap)))
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTextureMap);	// �ǂݍ��ރ������[
#endif

								// �e�̐���
	//mapnidxShadow = CreateShadow(map->pos, 25.0f, 25.0f);

	//mapsizeShadow = 25.0f;
	//mapcolShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMap(void)
{
	MAP *map = &mapWk[0];
	if (g_pD3DTextureMap != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureMap->Release();
		g_pD3DTextureMap = NULL;
	}

	if (map->MeshMap != NULL)
	{// ���b�V���̊J��
		map->MeshMap->Release();
		map->MeshMap = NULL;
	}

	if (map->BuffMatMap != NULL)
	{// �}�e���A���̊J��
		map->BuffMatMap->Release();
		map->BuffMatMap = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMap(void)
{
	D3DXVECTOR3 rotCamera;
	MAP *map = &mapWk[0];
	MODEL *model = GetModel(0);
	float fDiffRotY;
	D3DXVECTOR3 SubposMaptoModel;
	float rotcheckBtoM;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	MAP *map = &mapWk[0];

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&map->World);


	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, map->scl.x, map->scl.y, map->scl.z);
	D3DXMatrixMultiply(&map->World, &map->World, &mtxScl);


	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, map->rot.y, map->rot.x, map->rot.z);
	D3DXMatrixMultiply(&map->World, &map->World, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, map->pos.x, map->pos.y, map->pos.z);
	D3DXMatrixMultiply(&map->World, &map->World, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &map->World);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)map->BuffMatMap->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)map->NumMatMap; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureMap);

		// �`��
		map->MeshMap->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionMap(void)
{
	MAP *map = &mapWk[0];
	return map->pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationMap(void)
{
	MAP *map = &mapWk[0];
	return map->rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestMap(void)
{
	MAP *map = &mapWk[0];
	return map->rotDest;
}

//*****************************************************************************
// �Q�b�g�֐�
//*****************************************************************************
MAP *GetMap(int no)
{
	return(&mapWk[0]);
}

////*****************************************************************************
//// �{�X�̍s���܂Ƃ�
////*****************************************************************************
//void mapshot(void)
//{
//	MAP *map = &mapWk[0];
//	// �ʔ���
//	D3DXVECTOR3 pos = map->pos;
//	SetMapbullet(map->pos, 30.0f, 30.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//	map->acttime = MAPACT;
//}
//
////*******************************
//// ���[�U�[
////*******************************
//void mapbeam(void)
//{
//	MAP *map = &mapWk[0];
//	D3DXVECTOR3 pos = map->pos;
//	map->rot.y = 0;
//	SetMapbullet(map->pos, 20.0f, 60.0f, D3DXCOLOR(0.6f, 1.0f, 1.0f, 1.0f));
//	map->acttime = MAPACT;
//
//}