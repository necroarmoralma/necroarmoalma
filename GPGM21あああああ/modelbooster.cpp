//=============================================================================
//
// ���f������ [modelbooster.cpp]
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
#include "modelbooster.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODELBOOSTER_MODEL		"data/MODEL/modelbooster.x"	// �ǂݍ��ރ��f����
#define MODELBOOSTERANIMCOUNT	(1*60);						// �b���~�t���[����

// �v���C���[�̃p�[�c��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureModelBooster;			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshModelBooster;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatModelBooster;		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatModelBooster;				// �������̑���
bool				boosteranim;
float				boostercount;

MODELBOOSTER			modelboosterWk[1];					// ���f���\����(���f���͂P�j
//=============================================================================
// ����������
//=============================================================================
HRESULT InitModelBooster(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBOOSTER *modelbooster = &modelboosterWk[0];
	D3DXVECTOR3 rotCamera;

	// HP�̐ݒ�(���ʔj��𓱓�����Ȃ�R�����g�A�E�g����
	//modelbooster->Maxlife = PLAYER_HP_MAX;
	//modelbooster->Nowlife = modelbooster->Maxlife;


	g_pD3DTextureModelBooster = NULL;
	g_pD3DXMeshModelBooster = NULL;
	g_pD3DXBuffMatModelBooster = NULL;

	modelbooster->pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	modelbooster->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelbooster->puremove = modelbooster->move;
	modelbooster->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelbooster->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelbooster->scl = D3DXVECTOR3(0.3f, 0.3f, 0.3f);

	modelbooster->rot.y = 90.0f;

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(MODELBOOSTER_MODEL,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pD3DXBuffMatModelBooster,
		NULL,
		&g_nNumMatModelBooster,
		&g_pD3DXMeshModelBooster)))
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTextureModelBooster);	// �ǂݍ��ރ������[
#endif

									// �e�̐���(���i�K�ł͂����̉e�͏o���Ȃ�)
									//modelbooster->g_nIdxShadow = CreateShadow(modelbooster->pos, 25.0f, 25.0f);
									//modelbooster->g_fSizeShadow = 25.0f;
									//modelbooster->g_colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);


	// ����
	boosteranim = false;
	boostercount = 0.0f;


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModelBooster(void)
{
	if (g_pD3DTextureModelBooster != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureModelBooster->Release();
		g_pD3DTextureModelBooster = NULL;
	}

	if (g_pD3DXMeshModelBooster != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshModelBooster->Release();
		g_pD3DXMeshModelBooster = NULL;
	}

	if (g_pD3DXBuffMatModelBooster != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatModelBooster->Release();
		g_pD3DXBuffMatModelBooster = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModelBooster(void)
{
	D3DXVECTOR3 rotCamera;
	MODELBOOSTER *modelbooster = &modelboosterWk[0];
	MODEL *model = GetModel(0);
	float fDiffRotY;
	//modelbooster->rot.z += 0.1f;
	// �J�����̌����擾
	rotCamera = GetRotCamera();
	// ��ɑO��
	modelbooster->rotDest.y = rotCamera.y + D3DX_PI;


	// �e�X�g
	if (GetKeyboardPress(DIK_U))
	{
		modelbooster->Nowlife -= 10.0f;
	}
	// ���䓶�q�̉�]���ꎞ�I�ɖ�����
	// �����@10�Ŋ����Ă�̂�10�t���[���ňړ������邽��


	modelbooster->pos = model->pos;
	modelbooster->rot = model->rot;

	//// �ړI�̊p�x�܂ł̍���
	//fDiffRotY = modelbooster->rotDest.y - modelbooster->rot.y;
	//if (fDiffRotY > D3DX_PI)
	//{
	//	fDiffRotY -= D3DX_PI * 2.0f;
	//}
	//if (fDiffRotY < -D3DX_PI)
	//{
	//	fDiffRotY += D3DX_PI * 2.0f;
	//}

	//// �ړI�̊p�x�܂Ŋ�����������
	//modelbooster->rot.y += fDiffRotY * RATE_ROTATE_MODEL;
	//if (modelbooster->rot.y > D3DX_PI)
	//{
	//	modelbooster->rot.y -= D3DX_PI * 2.0f;

	//}
	//if (modelbooster->rot.y < -D3DX_PI)
	//{
	//	modelbooster->rot.y += D3DX_PI * 2.0f;
	//}

	//	modelbooster->rot.y = 3.14f;

	/// �ʒu�ړ�
	modelbooster->pos.x += modelbooster->move.x;
	modelbooster->pos.y += modelbooster->move.y;
	if (modelbooster->pos.y < 5.0f)
	{
		modelbooster->pos.y = 5.0f;
	}
	if (modelbooster->pos.y > 75.0f)
	{
		modelbooster->pos.y = 75.0f;
	}
	modelbooster->pos.z += modelbooster->move.z;

	// ����������O�Ɉړ��ʂ�ۑ�
	modelbooster->puremove = modelbooster->move;


	// �ړ��ʂɊ�����������
	modelbooster->move.x += (0.0f - modelbooster->move.x) * RATE_MOVE_MODEL;
	modelbooster->move.y += (0.0f - modelbooster->move.y) * RATE_MOVE_MODEL;
	modelbooster->move.z += (0.0f - modelbooster->move.z) * RATE_MOVE_MODEL;

	// �X�P�[���ύX
	if (boosteranim == false)
	{
		modelbooster->scl.x += 0.01f;
		modelbooster->scl.y += 0.01f;
		modelbooster->scl.z += 0.01f;
		boostercount++;
		if (boostercount == 10.0f)			// �e�X�g
		{
			boosteranim = true;
		}
	}
	else if (boosteranim == true)
	{
		modelbooster->scl.x -= 0.01f;
		modelbooster->scl.y -= 0.01f;
		modelbooster->scl.z -= 0.01f;
		boostercount--;
		if (boostercount == 0.0f)
		{
			boosteranim = false;
		}
	}

	// �̈�O�ɍs������X�g�b�v(��2���Ă���̂͂߂荞�܂Ȃ��悤�ɂ��邽��)
	//if (modelbooster->pos.x < -DROWMAX_X)
	//{
	//	modelbooster->pos.x = -DROWMAX_X;
	//}
	//if (modelbooster->pos.x >  DROWMAX_X)
	//{
	//	modelbooster->pos.x = DROWMAX_X;
	//}
	//if (modelbooster->pos.z  < -DROWMAX_Z)
	//{
	//	modelbooster->pos.z = -DROWMAX_Z;
	//}
	//if (modelbooster->pos.z > DROWMAX_Z)
	//{
	//	modelbooster->pos.z = DROWMAX_Z;
	//}




	// �e�̈ʒu�ݒ�
	//SetPositionShadow(modelbooster->g_nIdxShadow, D3DXVECTOR3(modelbooster->pos.x, 0.1f, modelbooster->pos.z));

	//SetVertexShadow(modelbooster->g_nIdxShadow, g_fSizeShadow, g_fSizeShadow);
	//SetColorShadow(g_nIdxShadow, g_colShadow);

	PrintDebugProc("[rotDest.y������:(%f) ]\n", modelbooster->rotDest.y);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModelBooster(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	MODELBOOSTER *modelbooster = &modelboosterWk[0];

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&modelbooster->World);


	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, modelbooster->scl.x, modelbooster->scl.y, modelbooster->scl.z);
	D3DXMatrixMultiply(&modelbooster->World, &modelbooster->World, &mtxScl);


	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, modelbooster->rot.y, modelbooster->rot.x, modelbooster->rot.z);
	D3DXMatrixMultiply(&modelbooster->World, &modelbooster->World, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, modelbooster->pos.x, modelbooster->pos.y, modelbooster->pos.z);
	D3DXMatrixMultiply(&modelbooster->World, &modelbooster->World, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &modelbooster->World);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatModelBooster->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModelBooster; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureModelBooster);

		// �`��
		g_pD3DXMeshModelBooster->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionModelBooster(void)
{
	MODELBOOSTER *modelbooster = &modelboosterWk[0];
	return modelbooster->pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationModelBooster(void)
{
	MODELBOOSTER *modelbooster = &modelboosterWk[0];
	return modelbooster->rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestModelBooster(void)
{
	MODELBOOSTER *modelbooster = &modelboosterWk[0];
	return modelbooster->rotDest;
}

//*****************************************************************************
// �Q�b�g�֐�
//*****************************************************************************
MODELBOOSTER *GetModelBooster(int no)
{
	return(&modelboosterWk[0]);
}