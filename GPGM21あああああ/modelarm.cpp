//=============================================================================
//
// ���f������ [modelarm.cpp]
// Author : GP11B243 33 �R�{ �s��
// ���f���̘r
//=============================================================================
#include "model.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "bulletmk2.h"
#include "meshfield.h"
#include "setting.h"
#include "camera.h"
#include "modelarm.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODELARM_MODEL		"data/MODEL/arrowarm.blend.x"	// �ǂݍ��ރ��f����


// �v���C���[�̃p�[�c��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureModelArm;			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshModelArm;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatModelArm;		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatModelArm;				// �������̑���


MODELARM			modelarmWk[1];					// ���f���\����(���f���͂P�j
//=============================================================================
// ����������
//=============================================================================
HRESULT InitModelArm(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELARM *modelarm = &modelarmWk[0];
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);

	// HP�̐ݒ�(���ʔj��𓱓�����Ȃ�R�����g�A�E�g����
	//modelarm->Maxlife = PLAYER_HP_MAX;
	//modelarm->Nowlife = modelarm->Maxlife;


	g_pD3DTextureModelArm = NULL;
	g_pD3DXMeshModelArm = NULL;
	g_pD3DXBuffMatModelArm = NULL;

	modelarm->pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	modelarm->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelarm->puremove = modelarm->move;
	modelarm->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelarm->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelarm->scl = model->scl;

	modelarm->rot.y = 90.0f;

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(MODELARM_MODEL,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pD3DXBuffMatModelArm,
		NULL,
		&g_nNumMatModelArm,
		&g_pD3DXMeshModelArm)))
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTextureModelArm);	// �ǂݍ��ރ������[
#endif

	// �e�̐���(���i�K�ł͂����̉e�͏o���Ȃ�)
	//modelarm->g_nIdxShadow = CreateShadow(modelarm->pos, 25.0f, 25.0f);
	//modelarm->g_fSizeShadow = 25.0f;
	//modelarm->g_colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);




	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModelArm(void)
{
	if (g_pD3DTextureModelArm != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureModelArm->Release();
		g_pD3DTextureModelArm = NULL;
	}

	if (g_pD3DXMeshModelArm != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshModelArm->Release();
		g_pD3DXMeshModelArm = NULL;
	}

	if (g_pD3DXBuffMatModelArm != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatModelArm->Release();
		g_pD3DXBuffMatModelArm = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModelArm(void)
{
	D3DXVECTOR3 rotCamera;
	MODELARM *modelarm = &modelarmWk[0];
	MODEL *model = GetModel(0);
	float fDiffRotY;
	//modelarm->rot.z += 0.1f;
	// �J�����̌����擾
	rotCamera = GetRotCamera();
	// ��ɑO��
	modelarm->rotDest.y = rotCamera.y + D3DX_PI;


	// �e�X�g
	if (GetKeyboardPress(DIK_U))
	{
		modelarm->Nowlife -= 10.0f;
	}
	// ���䓶�q�̉�]���ꎞ�I�ɖ�����
	// �����@10�Ŋ����Ă�̂�10�t���[���ňړ������邽��
	



	modelarm->pos = model->pos;
	modelarm->rot = model->rot;

	//// �ړI�̊p�x�܂ł̍���
	//fDiffRotY = modelarm->rotDest.y - modelarm->rot.y;
	//if (fDiffRotY > D3DX_PI)
	//{
	//	fDiffRotY -= D3DX_PI * 2.0f;
	//}
	//if (fDiffRotY < -D3DX_PI)
	//{
	//	fDiffRotY += D3DX_PI * 2.0f;
	//}

	//// �ړI�̊p�x�܂Ŋ�����������
	//modelarm->rot.y += fDiffRotY * RATE_ROTATE_MODEL;
	//if (modelarm->rot.y > D3DX_PI)
	//{
	//	modelarm->rot.y -= D3DX_PI * 2.0f;

	//}
	//if (modelarm->rot.y < -D3DX_PI)
	//{
	//	modelarm->rot.y += D3DX_PI * 2.0f;
	//}

	//	modelarm->rot.y = 3.14f;

	/// �ʒu�ړ�
	modelarm->pos.x += modelarm->move.x;
	modelarm->pos.y += modelarm->move.y;
	if (modelarm->pos.y < 5.0f)
	{
		modelarm->pos.y = 5.0f;
	}
	if (modelarm->pos.y > 75.0f)
	{
		modelarm->pos.y = 75.0f;
	}
	modelarm->pos.z += modelarm->move.z;

	// ����������O�Ɉړ��ʂ�ۑ�
	modelarm->puremove = modelarm->move;


	// �ړ��ʂɊ�����������
	modelarm->move.x += (0.0f - modelarm->move.x) * RATE_MOVE_MODEL;
	modelarm->move.y += (0.0f - modelarm->move.y) * RATE_MOVE_MODEL;
	modelarm->move.z += (0.0f - modelarm->move.z) * RATE_MOVE_MODEL;


	// �̈�O�ɍs������X�g�b�v(��2���Ă���̂͂߂荞�܂Ȃ��悤�ɂ��邽��)
	//if (modelarm->pos.x < -DROWMAX_X)
	//{
	//	modelarm->pos.x = -DROWMAX_X;
	//}
	//if (modelarm->pos.x >  DROWMAX_X)
	//{
	//	modelarm->pos.x = DROWMAX_X;
	//}
	//if (modelarm->pos.z  < -DROWMAX_Z)
	//{
	//	modelarm->pos.z = -DROWMAX_Z;
	//}
	//if (modelarm->pos.z > DROWMAX_Z)
	//{
	//	modelarm->pos.z = DROWMAX_Z;
	//}




	// �e�̈ʒu�ݒ�
	//SetPositionShadow(modelarm->g_nIdxShadow, D3DXVECTOR3(modelarm->pos.x, 0.1f, modelarm->pos.z));

	//SetVertexShadow(modelarm->g_nIdxShadow, g_fSizeShadow, g_fSizeShadow);
	//SetColorShadow(g_nIdxShadow, g_colShadow);

	PrintDebugProc("[rotDest.y������:(%f) ]\n", modelarm->rotDest.y);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModelArm(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	MODELARM *modelarm = &modelarmWk[0];

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&modelarm->World);


	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, modelarm->scl.x, modelarm->scl.y, modelarm->scl.z);
	D3DXMatrixMultiply(&modelarm->World, &modelarm->World, &mtxScl);


	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, modelarm->rot.y, modelarm->rot.x, modelarm->rot.z);
	D3DXMatrixMultiply(&modelarm->World, &modelarm->World, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, modelarm->pos.x, modelarm->pos.y, modelarm->pos.z);
	D3DXMatrixMultiply(&modelarm->World, &modelarm->World, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &modelarm->World);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatModelArm->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModelArm; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureModelArm);

		// �`��
		g_pD3DXMeshModelArm->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionModelArm(void)
{
	MODELARM *modelarm = &modelarmWk[0];
	return modelarm->pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationModelArm(void)
{
	MODELARM *modelarm = &modelarmWk[0];
	return modelarm->rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestModelArm(void)
{
	MODELARM *modelarm = &modelarmWk[0];
	return modelarm->rotDest;
}

//*****************************************************************************
// �Q�b�g�֐�
//*****************************************************************************
MODELARM *GetModelArm(int no)
{
	return(&modelarmWk[0]);
}