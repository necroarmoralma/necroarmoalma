//=============================================================================
//
// ���f������ [wheel.cpp]
// Author : GP11B243 33 �R�{ �s��
// ����:	���f���̎ԗ֕����̏���
//
//=============================================================================
#include "model.h"
#include "wheel.h"
#include "camera.h"
#include "input.h"
#include "setting.h"
#include "camera.h"

#include "xinput.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODELTAIYA		"data/MODEL/yajirushi.x"
#define WHEELSPIN		(1.1f)							// �z�C�[���̉�]���x
// �v���C���[�̃p�[�c��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
float booster;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitWheel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODEL *model = GetModel(0);
	D3DXVECTOR3 rotCamera;

	booster = 0.0f;
	model->taiya_status.TextureModel = NULL;
	model->taiya_status.MeshModel = NULL;
	model->taiya_status.BuffMatModel = NULL;

	// �����ʒu�y�уX�e�[�^�X�̐ݒ�
	model->taiya_status.pos = model->pos;
	model->taiya_status.move = model->move;
	model->taiya_status.rot = model->rot;
	model->taiya_status.rotDest = model->rotDest;
	model->taiya_status.scl = model->scl;
	model->taiya_status.roton = false;
	// �^�C���p�[�c�̏����ʒu�y�уX�e�[�^�X�̐ݒ�


	// �{�̂̓ǂݍ���
	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(MODELTAIYA,				// LPCTSTR,�t�@�C���l�[��
		D3DXMESH_SYSTEMMEM,		// DWORD,���b�V���̍쐬�I�v�V�������_��C���f�b�N�X�o�b�t�@�̐ݒ�
		pDevice,				// LPDIRECT3DDEVICE9,���b�V���Ɋ֘A�t�����Ă���R�f�o�C�X�I�u�W�F�N�g��\��
		NULL,					// LPD3DXBUFFER,1�ʓ�����3��DWORD�z��ւ̃|�C���^�A�אږʎw��
		&model->taiya_status.BuffMatModel,	// LPD3DXBUFFER,�}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^D3DXMATERIAL�\���̂̔z�񂪊i�[
		NULL,					// LPD3DXBUFFER,�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&model->taiya_status.NumMatModel,		// DWORD,D3DXMATERIAL�\���̂ւ̃|�C���^
		&model->taiya_status.MeshModel)))	// LPD3DXMESH,���[�h���ꂽ���b�V����\��ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	{
		return E_FAIL;
	}



	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
	//								DOOMHAIKEI,		// �t�@�C���̖��O
	//							&model->taiya_status.TextureModel);	// �ǂݍ��ރ������[


	//// �e�̐���
	//model->taiya_status.IdxShadow = CreateShadow(model->pos, 25.0f, 25.0f);

	//model->taiya_status.SizeShadow = 25.0f;
	//model->taiya_status.colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);


	// model_longcheck�Ŏ擾�������a�����㏸������
	//model->pos.y += model->center;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWheel(void)
{
	MODEL *model = GetModel(0);

	//if(model->taiya_status.TextureModel != NULL)
	//{// �e�N�X�`���̊J��
	//	model->taiya_status.TextureModel->Release();
	//	model->taiya_status.TextureModel = NULL;
	//}

	if (model->taiya_status.MeshModel != NULL)
	{// ���b�V���̊J��
		model->taiya_status.MeshModel->Release();
		model->taiya_status.MeshModel = NULL;

	}

	if (model->taiya_status.BuffMatModel != NULL)
	{// �}�e���A���̊J��
		model->taiya_status.BuffMatModel->Release();
		model->taiya_status.BuffMatModel = NULL;

	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWheel(int movetypeno)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = GetModel(0);
	// �Q�[���p�b�h�̏��
	XINPUT_STATE state;
	XInputGetState(0, &state);

	// �Q�[���p�b�h�̏�ԕω�
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	// �J�����̌����擾
	rotCamera = GetRotCamera();


	if (movetypeno == model_game)
	{
		
		model->taiya_status.rot.z = model->rot.z;
		model->taiya_status.scl = model->scl;
		model->rotDest.y = rotCamera.y + D3DX_PI;



		// �����₩���Ă�

		// ��
		if (GetKeyboardPress(DIK_A))
		{
			// ����
			if (GetKeyboardPress(DIK_W))
			{
				booster += WHEELSPIN;
				model->taiya_status.rot.y = hidariue;
			}
			// ����
			else if (GetKeyboardPress(DIK_S))
			{
				booster -= WHEELSPIN;
				model->taiya_status.rot.y = hidarishita;
			}
		
			else
			{
				booster += WHEELSPIN;
				model->taiya_status.rot.y = hidari;
			}
		}

		// �E
		else if (GetKeyboardPress(DIK_A))
		{
			model->taiya_status.rot.y =  hidari;
			booster -= WHEELSPIN;		// �O
									// ����
			if (GetKeyboardPress(DIK_W))
			{
				model->taiya_status.rot.y =  hidariue;
			}
			// ����
			else if (GetKeyboardPress(DIK_S))
			{
				model->taiya_status.rot.y =  hidarishita;
			}
		}
		else  if (GetKeyboardPress(DIK_W))
		 {
			 booster -= WHEELSPIN;		// �O
		 }
		else if (GetKeyboardPress(DIK_S))
		{
			booster += WHEELSPIN;
		}


		 // �R���g���[���[����
		// �E
		 if (state.Gamepad.sThumbLX>STICKBASE)
		 {

			// �E��
			 if (state.Gamepad.sThumbLY>STICKBASE)
			 {
				 booster -= WHEELSPIN;
				 model->taiya_status.rot.y = migiue;
			 }
			 // �E��
			 else if (state.Gamepad.sThumbLY< -STICKBASE)
			 {
				 booster -= WHEELSPIN;
				 model->taiya_status.rot.y = migishita;
			 }
			 else
			 {
				 // �E
				 model->taiya_status.rot.y = migi;
				 booster += WHEELSPIN;
			 }
		 }
		 // ������
		 else if (state.Gamepad.sThumbLX < -STICKBASE)
		 {
			// ����
			 if (state.Gamepad.sThumbLY>STICKBASE)
			 {
				 booster -= WHEELSPIN;
				 model->taiya_status.rot.y = hidariue;
			 }
			 // ����
			 else if (state.Gamepad.sThumbLY< -STICKBASE)
			 {
				 booster -= WHEELSPIN;
				 model->taiya_status.rot.y = hidarishita;
			 }

			 // ��
			 else
			 {
				 booster += WHEELSPIN;
				 model->taiya_status.rot.y = hidari;
			 }
		 }
		 else  if (state.Gamepad.sThumbLY>STICKBASE)
		 {
			 booster -= WHEELSPIN;		// �O
			 model->taiya_status.rot.y = ue;
		 }
		 else if (state.Gamepad.sThumbLY< -STICKBASE)
		 {
			 booster += WHEELSPIN;
			 model->taiya_status.rot.y = shita;
		 }

		// �ړ��ʂ̕ύX���m�F�ł��Ȃ��ꍇ������~
		else
		{
			booster = 0.0f;
		}
		//modle->taiya_status.
	}

}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawWheel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	MODEL *model = GetModel(0);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&model->taiya_status.World);


	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, model->scl.x, model->scl.y, model->scl.z);
	D3DXMatrixMultiply(&model->World, &model->World, &mtxScl);


	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,  model->taiya_status.rot.y, booster, (model->taiya_status.rot.z)*0.0f);
	D3DXMatrixMultiply(&model->taiya_status.World, &model->taiya_status.World, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, model->pos.x, model->pos.y, model->pos.z);
	D3DXMatrixMultiply(&model->taiya_status.World, &model->taiya_status.World, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &model->taiya_status.World);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)model->taiya_status.BuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)model->taiya_status.NumMatModel; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, model->taiya_status.TextureModel);

		// �`��
		model->taiya_status.MeshModel->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionWheel(void)
{
	MODEL *model = GetModel(0);
	return model->taiya_status.pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationWheel(void)
{
	MODEL *model = GetModel(0);
	return model->taiya_status.pos;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestWheel(void)
{
	MODEL *model = GetModel(0);
	return model->rotDest;
}


