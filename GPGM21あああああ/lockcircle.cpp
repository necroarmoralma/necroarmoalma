//=============================================================================
//
// ���f������ [lockcircle.cpp]
// Author : GP11B243 33 �R�{ �s��
// ����:	���̕���
//
//=============================================================================
#include "model.h"
#include "lockcircle.h"
#include "camera.h"
#include "input.h"
#include "setting.h"
#include "camera.h"

#include "xinput.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LOCKCIRCLEMOD		"data/STAGE/sitanohaikei.x"
#define SHITANOHAIKEI		"data/STAGE/jimen.jpg"
#define CIRCLELENGTH		(3)							// ���f������T�[�N���܂ł̋���
// �v���C���[�̃p�[�c��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void controllcirclemove(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LOCKCIRCLE lockcircle;
float lockrot = 0.0f;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitLockcircle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODEL *model = GetModel(0);
	D3DXVECTOR3 rotCamera;


	// �����ʒu�y�уX�e�[�^�X�̐ݒ�
	lockcircle.status.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	lockcircle.status.move = model->move;
	lockcircle.status.rot = model->rot;
	lockcircle.status.rotDest = model->rotDest;
	lockcircle.status.scl = model->scl;
	lockcircle.status.roton = false;
	// �^�C���p�[�c�̏����ʒu�y�уX�e�[�^�X�̐ݒ�


	// �{�̂̓ǂݍ���
	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(LOCKCIRCLEMOD,				// LPCTSTR,�t�@�C���l�[��
		D3DXMESH_SYSTEMMEM,		// DWORD,���b�V���̍쐬�I�v�V�������_��C���f�b�N�X�o�b�t�@�̐ݒ�
		pDevice,				// LPDIRECT3DDEVICE9,���b�V���Ɋ֘A�t�����Ă���R�f�o�C�X�I�u�W�F�N�g��\��
		NULL,					// LPD3DXBUFFER,1�ʓ�����3��DWORD�z��ւ̃|�C���^�A�אږʎw��
		&lockcircle.status.BuffMatModel,	// LPD3DXBUFFER,�}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^D3DXMATERIAL�\���̂̔z�񂪊i�[
		NULL,					// LPD3DXBUFFER,�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&lockcircle.status.NumMatModel,		// DWORD,D3DXMATERIAL�\���̂ւ̃|�C���^
		&lockcircle.status.MeshModel)))	// LPD3DXMESH,���[�h���ꂽ���b�V����\��ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	{
		return E_FAIL;
	}



	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
									SHITANOHAIKEI,		// �t�@�C���̖��O
								&lockcircle.status.TextureModel);	// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitLockcircle(void)
{
	MODEL *model = GetModel(0);

	if(lockcircle.status.TextureModel != NULL)
	{// �e�N�X�`���̊J��
		lockcircle.status.TextureModel->Release();
		lockcircle.status.TextureModel = NULL;
	}

	if (lockcircle.status.MeshModel != NULL)
	{// ���b�V���̊J��
		lockcircle.status.MeshModel->Release();
		lockcircle.status.MeshModel = NULL;

	}

	if (lockcircle.status.BuffMatModel != NULL)
	{// �}�e���A���̊J��
		lockcircle.status.BuffMatModel->Release();
		lockcircle.status.BuffMatModel = NULL;

	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLockcircle(int movetypeno)
{
	float fDiffRotY;
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);




	//// �J�����̌����擾
	//rotCamera = GetRotCamera();

	//// ��ɑO��
	//lockcircle.status.rotDest.y = rotCamera.y + D3DX_PI;
	//// ����
	//// �R���g���[���[����
	//controllcirclemove();

	//// �ړI�̊p�x�܂ł̍���
	//fDiffRotY = lockcircle.status.rotDest.y - lockcircle.status.rot.y;
	//if (fDiffRotY > D3DX_PI)
	//	{
	//		fDiffRotY -= D3DX_PI * 2.0f;
	//	}
	//if (fDiffRotY < -D3DX_PI)
	//	{
	//		fDiffRotY += D3DX_PI * 2.0f;
	//	}

	//// �ړI�̊p�x�܂Ŋ�����������
	//lockcircle.status.rot.y += fDiffRotY * RATE_ROTATE_MODEL;

	//if (lockcircle.status.rot.y > D3DX_PI)
	//{
	//	lockcircle.status.rot.y -= D3DX_PI * 2.0f;


	//	}
	//	if (lockcircle.status.rot.y < -D3DX_PI)
	//	{
	//		lockcircle.status.rot.y += D3DX_PI * 2.0f;
	//	}

	//	lockcircle.status.pos.x += lockcircle.status.move.x;
	//	lockcircle.status.pos.y += lockcircle.status.move.y;
	//	lockcircle.status.pos.z += lockcircle.status.move.z;
	//	// �ړ��ʂɊ�����������
	//	lockcircle.status.move.x += (0.0f - lockcircle.status.move.x) * RATE_MOVE_MODEL;
	//	lockcircle.status.move.y += (0.0f - lockcircle.status.move.y) * RATE_MOVE_MODEL;
	//	lockcircle.status.move.z += (0.0f - lockcircle.status.move.z) * RATE_MOVE_MODEL;

}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawLockcircle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&lockcircle.status.World);


	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, lockcircle.status.scl.x, lockcircle.status.scl.y, lockcircle.status.scl.z);
	D3DXMatrixMultiply(&lockcircle.status.World, &lockcircle.status.World, &mtxScl);


	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, lockcircle.status.rot.y, lockcircle.status.rot.x, lockcircle.status.rot.z);
	D3DXMatrixMultiply(&lockcircle.status.World, &lockcircle.status.World, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, lockcircle.status.pos.x, lockcircle.status.pos.y, lockcircle.status.pos.z);
	D3DXMatrixMultiply(&lockcircle.status.World, &lockcircle.status.World, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &lockcircle.status.World);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)lockcircle.status.BuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)lockcircle.status.NumMatModel; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, lockcircle.status.TextureModel);

		// �`��
		lockcircle.status.MeshModel->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}


//*****************************************************************************
// �Q�b�g�֐�
//*****************************************************************************
LOCKCIRCLE *GetLockcircle(int no)
{
	return(&lockcircle);
}


//***************************************************************
// �֐���:	void controllcirclemove(void)
// ����:	void
// �߂�l:	�Ȃ�
// ����:	�R���g���[���[�Ń^�[�Q�b�g�T�[�N���̓���𐧌䂷��)
//****************************************************************
void controllcirclemove(void)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);
	// �Q�[���p�b�h�̏��
	XINPUT_STATE state;
	XInputGetState(0, &state);

	// �Q�[���p�b�h�̏�ԕω�
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	// ������
	if (state.Gamepad.sThumbRX < -STICKBASE)
	{
		lockcircle.status.pos.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
		lockcircle.status.pos.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
	}
	// �E����
	else if(state.Gamepad.sThumbRX > STICKBASE)
	{
		lockcircle.status.pos.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
		lockcircle.status.pos.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
	}
	// �㏸
	if (state.Gamepad.sThumbRY > STICKBASE)
	{
		lockcircle.status.pos.z -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
		lockcircle.status.pos.y -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
	}
	

	// ���~
	else if (state.Gamepad.sThumbRY < -STICKBASE)
	{
		lockcircle.status.pos.z -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
		lockcircle.status.pos.y -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

	}

}