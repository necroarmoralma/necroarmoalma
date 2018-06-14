//=============================================================================
//
// ���f������ [model.cpp]
// Author : GP11B243 33 �R�{ �s��
// ����: ���O�ύX�\��(podbody or modelbody�j�j
//		���f���̖{�̕����֘A
//
//=============================================================================
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"
#include "bulletmk2.h"
#include "unit.h"
#include "setting.h"
#include "camera.h"
#include "map.h"
#include "steam.h"
// �Q�[���R���g���[�^�[�̓��������o
#include "xinput.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLEUP   (4.0f)
#define MODELREFLECT	(1.80f);
// �e�̑傫��(��{�I��X��Y�������l)
#define BULLETMK2BASESIZE (15.0f)		//�@��{�I��X��Y�������T�C�Y
//#define BULLETMK2BASESIZEY 


//�@�ǂƂ̋�������p�A���a���̂܂܂��Ƃ߂肱�ނ̂Œ����邽�߂̒l
#define LONGHOSEI	(0.0f)

// �v���C���[�̃p�[�c��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void escapefromwall(void);
void keyboardmove(void);
void xinputmove(void);
void xinputrot(void);
void evolve_modelbullet(int shotlv);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int					g_nIdxShadow;				// �eID
int					modelmovetype;				// ���f���̓��샂�[�h
float				g_fSizeShadow;				// �e�̃T�C�Y
D3DXCOLOR			g_colShadow;				// �e�̐F
MODEL				modelWk[1];					// ���f���\����(���f���͂P�j
bool				roton;						// �����͉̂�]
bool				modelcontroller = false;		// ���ɃR���g���[���[�̓��͂��󂯂��̂�
bool				jump = false;					// �����ł�́H
float				centertoleg = MODEL_DISTANCE_CL;
float				controlcount;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitModel(int gametypeno)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODEL *model = &modelWk[0];
	D3DXVECTOR3 rotCamera;
	

	// �V���b�g�̐ݒ�
	model->shot = SHOTKANKAKU;
	model->shot_on = true;			// ���Ă�悤�ɂ��Ă���
	
	// ��]
	roton = false;
	// HP�̐ݒ�
	model->Maxlife = PLAYER_HP_MAX;
	model->Nowlife = model->Maxlife;

	// ��]����
	model->rollon = false;
	model->cooltime = COOLTIME;

	model->status.TextureModel = NULL;
	model->status.MeshModel = NULL;
	model->status.BuffMatModel = NULL;

	// �����ʒu�y�уX�e�[�^�X�̐ݒ�(bool�̐ݒ��������)
	model->pos = D3DXVECTOR3(8.0f, 0.0f, 55.6555443f);					// ������
	model->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model->puremove = model->move;
	model->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model->scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	//model->rot.y = 90.0f;			// ��]�����Ȃ��ƕςȕ��������̂ŉ��u��
	model->control = true;			// �L�[���͂��󂯕t����
	model->escapemode = false;
	model->shotlv = 0;				// ���x���͂O����
	controlcount = 0.0f;


	// �^�C���p�[�c�̏����ʒu�y�уX�e�[�^�X�̐ݒ�

		// �{�̂̓ǂݍ���
		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(PITCH_MODEL,				// LPCTSTR,�t�@�C���l�[��
			D3DXMESH_SYSTEMMEM,		// DWORD,���b�V���̍쐬�I�v�V�������_��C���f�b�N�X�o�b�t�@�̐ݒ�
			pDevice,				// LPDIRECT3DDEVICE9,���b�V���Ɋ֘A�t�����Ă���R�f�o�C�X�I�u�W�F�N�g��\��
			NULL,					// LPD3DXBUFFER,1�ʓ�����3��DWORD�z��ւ̃|�C���^�A�אږʎw��
			&model->status.BuffMatModel,	// LPD3DXBUFFER,�}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^D3DXMATERIAL�\���̂̔z�񂪊i�[
			NULL,					// LPD3DXBUFFER,�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
			&model->status.NumMatModel,		// DWORD,D3DXMATERIAL�\���̂ւ̃|�C���^
			&model->status.MeshModel)))	// LPD3DXMESH,���[�h���ꂽ���b�V����\��ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
		{
			return E_FAIL;
		}
	

	

	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
//								DOOMHAIKEI,		// �t�@�C���̖��O
	//							&g_pD3DTextureModel);	// �ǂݍ��ރ������[


	// �e�̐���
	//g_nIdxShadow = CreateShadow(model->pos, 25.0f, 25.0f);

	//g_fSizeShadow = 25.0f;
	//g_colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	//// model_longcheck�Ŏ擾�������a�����㏸������
	//model->pos.y += model->center;


	
		// ���Ƃŏ���
		// ���f���Z���^�[���傤����
		//model->center += LONGHOSEI;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	MODEL *model = &modelWk[0];

	//if(model->status.TextureModel != NULL)
	//{// �e�N�X�`���̊J��
	//	model->status.TextureModel->Release();
	//	model->status.TextureModel = NULL;
	//}

	if(model->status.MeshModel != NULL)
	{// ���b�V���̊J��
		model->status.MeshModel->Release();
		model->status.MeshModel = NULL;

	}

	if(model->status.BuffMatModel != NULL)
	{// �}�e���A���̊J��
		model->status.BuffMatModel->Release();
		model->status.BuffMatModel = NULL;

	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(int movetypeno)
{
	D3DXVECTOR3 rotCamera;
	MODEL *model = &modelWk[0];
	UNIT *unit = GetUnit(0);
	float fDiffRotY;
	float hosei_y;			// ���f����Y���W�̕␳
	int movetype = movetypeno;

	// �J�����̌����擾
	rotCamera = GetRotCamera();
	// ���O�̓��͏�����
	modelcontroller = false;

	// �^�C�g����ʂ̏ꍇ
	if (movetype == model_title)
	{
		model->rot.y += 0.01f;

	}
	// �Q�[���̏ꍇ
	if (movetype == model_game)
	{
		// ���݂̍��W���擾����
		model->oldpos = model->pos;

		// ��ɑO��
		model->rotDest.y = rotCamera.y + D3DX_PI;

		// �ڐG�m�F
		// ���C�̒��������a�����Z��(�ڐG)
		if (model->R_RtoMdistance < model->center || model->L_RtoMdistance < model->center
			|| model->F_RtoMdistance < model->center || model->B_RtoMdistance < model->center || model->D_RtoMdistance < model->center
			)
		{
			escapefromwall();
		}



		// �e�X�g
		if (GetKeyboardPress(DIK_U))
		{
			model->Nowlife -= 10.0f;
		}

		// ����
		// �R���g���[���[����
			//xinputmove();
			//xinputrot();

		// �L�[�{�[�h����
		keyboardmove();


		// ����
		if (modelcontroller == false)
		{
			//keyboardmove();
		}



		if (model->rollon == false)
		{
			// �L�[��������Ă��Ȃ��̂Ȃ��]��߂�
			if (roton == false)
			{
				if (model->rot.z < 0)
				{
					model->rot.z += MODEL_MOVEROLL / 10;
				}

				if (model->rot.z > 0)
				{
					model->rot.z -= MODEL_MOVEROLL / 10;
				}

				if (model->rot.x < 0)
				{
					model->rot.x += MODEL_MOVEROLL / 10;
				}

				if (model->rot.x > 0)
				{
					model->rot.x -= MODEL_MOVEROLL / 10;
				}
			}

		}
		roton = false;
		// �ړI�̊p�x�܂ł̍���
		fDiffRotY = model->rotDest.y - model->rot.y;
		if (fDiffRotY > D3DX_PI)
		{
			fDiffRotY -= D3DX_PI * 2.0f;
		}
		if (fDiffRotY < -D3DX_PI)
		{
			fDiffRotY += D3DX_PI * 2.0f;
		}

		// �ړI�̊p�x�܂Ŋ�����������
		//model->rot.y += fDiffRotY * RATE_ROTATE_MODEL;

		// �ʒu�ړ�

		//// �ړ��O�ɂԂ����ĂȂ����m���߂�
		//if (model->tomapDown == FALSE)	// ���ɉ����Ȃ�
		//{
		//	model->pos = model->oldpos;
		//	model->move.x *= -1.2;		// �ړ��ʂ𔽓]�������Ⴄ
		//	model->move.y *= -1.2;
		//	model->move.z *= -1.2;
		//	// ���肵���ꍇ�L�[���͎�t������
		//	model->control = false;
		//	controlcount = NOCONTROL;
		//}




		model->pos.x += model->move.x;
		model->pos.y += model->move.y;
		model->pos.z += model->move.z;

	

		// ����������O�Ɉړ��ʂ�ۑ�
		model->puremove = model->move;


		// �ړ��ʂɊ�����������
		model->move.x += (0.0f - model->move.x) * RATE_MOVE_MODEL;
		model->move.y += (0.0f - model->move.y) * RATE_MOVE_MODEL;
		model->move.z += (0.0f - model->move.z) * RATE_MOVE_MODEL;


		// �ړ����I������烌�C�s�b�N���s��
		model_RaypickTomap();

		// �n�ʂɉ����Ĉړ�������
		// ���Ƀ��C�����邩�ǂ���
		//if (model->tomapUp == FALSE)			// ������ɂ͉����Ȃ�
		//{
		//	if (model->tomapDown == TRUE)		// �}�b�v�����ɂ���
		//	{
		//		if (model->D_RtoMdistance >= model->center)	// ���f���ƒn�ʂ���ɐڂ���悤�ɂ��邽�߂�
		//		{
		//			model->pos.y -= 1.0f;		// ���f����蕂���Ă�����ʒu��������
		//			if ((model->D_RtoMdistance) <= model->center)
		//			{
		//				model->pos.y += model->center - model->D_RtoMdistance;
		//			}
		//			else if (model->pos.y <= model->center)
		//			{
		//				// �n�ʂɂԂ��Ă�������グ��
		//			//	model->pos.y -= model->D_RtoMdistance;
		//			//	model->pos.y += model->center;
		//			}
		//		}
		//	}

		//}
		// ���~
		// �␳�𑫂����@�ł��܂����킹��
		if (model->D_RtoMdistance > model->center)
		{
			jump = true;
		}
		else
		{
			jump = false;
		}

		if (jump == true)
		{
		//	model->pos.y -= 0.5f;
		}
		// �ǂ�Ȓl���낤�Ƃ߂荞��ł�Ȃ炠����͂�
		if (model->D_RtoMdistance <= model->center)
		{
			hosei_y = model->center - model->D_RtoMdistance;
			model->pos.y +=hosei_y;
			jump = false;
		}
		


		// �e�̈ʒu�ݒ�
		SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(model->pos.x, 0.1f, model->pos.z));

		SetVertexShadow(g_nIdxShadow, g_fSizeShadow, g_fSizeShadow);
		SetColorShadow(g_nIdxShadow, g_colShadow);

		PrintDebugProc("modelpos������:(%f)(%f)(%f) ]\n", model->pos.x,model->pos.y,model->pos.z);
		PrintDebugProc("�V���b�g�̃��x���́H:(%d)]\n", model->shotlv);

		// �ړ��ʂ�1�t���[���ȏ�ς��Ȃ��ꍇ�R���g���[���\�ɂ���
		if (controlcount == 0.0f)
		{
			model->control = true;
		}
		if (model->control == false)
		{
			controlcount--;
			model->rot.z += 0.1f;
		}

		// �Ō�ɃX�`�[�������Ă����
		//SetSteam(D3DXVECTOR3(model->pos.x,model->pos.y,model->pos.z), 1, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(int gametypeno)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl,mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	MODEL *model = &modelWk[0];

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&model->World);


	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, model->scl.x, model->scl.y, model->scl.z);
	D3DXMatrixMultiply(&model->World, &model->World, &mtxScl);


	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, model->rot.y, model->rot.x+ MODEL_MOVEROLlX, model->rot.z);
	D3DXMatrixMultiply(&model->World, &model->World, &mtxRot);

	// �ړ��𔽉f
	if (gametypeno == model_title)
	{
		// �����Ƃ�̂Ƃ���������������肿����Ƃ����ɂ���
		D3DXMatrixTranslation(&mtxTranslate, model->pos.x , model->pos.y + TITLEUP, model->pos.z);
	}
	else if (gametypeno == model_game)
	{
		D3DXMatrixTranslation(&mtxTranslate, model->pos.x, model->pos.y, model->pos.z);
	}
	D3DXMatrixMultiply(&model->World, &model->World, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &model->World);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)model->status.BuffMatModel->GetBufferPointer();

	for(int nCntMat = 0; nCntMat < (int)model->status.NumMatModel; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, model->status.TextureModel);

		// �`��
		model->status.MeshModel->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionModel(void)
{
	MODEL *model = &modelWk[0];
	return model->pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationModel(void)
{
	MODEL *model = &modelWk[0];
	return model->rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestModel(void)
{
	MODEL *model = &modelWk[0];
	return model->rotDest;
}

//*****************************************************************************
// �Q�b�g�֐�
//*****************************************************************************
MODEL *GetModel(int no)
{
	return(&modelWk[0]);
}

//*****************************************************************************
// �֐���:	void model_RaypickToMap(int no)
// ����:	int no
// �߂�l:	����
// ����:	���@�ƃ}�b�v�Ƃ̃��C�s�b�N�A�����̓��C���΂�����
//*****************************************************************************
void model_RaypickTomap(void)
{

	MODEL *model = &modelWk[0];
	MAP *map = GetMap(0);

		// �֗��֐��ƈ����̐���(�����p)
		// ���֔�΂�
		D3DXIntersect(
			map->MeshMap,				// �����蔻�����肽�����b�V���@�^��LPD3DXBASEMESH(LPD3DXMESH��OK?)
			&D3DXVECTOR3(model->pos.x, model->pos.y + 0.0f, model->pos.z),				// ���C�̎��_���W��ݒ�(�v���C���[�̍��W�Ƃ�) �^��D3DXVECTOR3
			&D3DXVECTOR3(0, -1, 0),		// ���C�̕�����ݒ� �^��D3DXVECTOR3 XYZ 1�Ő�����-1�ŕ��̕���
			&model->tomapDown,				// �Փ˔��� �^��BOOL(bool�ł͂Ȃ�) �Փ˂��Ă�����TRUE�������Ă��Ȃ����FALSE
			NULL,						// ��L�̔��肪TRUE�̏ꍇ���C�̎��_�ɍł��߂��ʂ̃C���f�b�N�X�l�ւ̃|�C���^
			NULL,						// �d�S�q�b�g���W�ւ̃|�C���^����1���C�������������b�V���̏ꏊ
			NULL,						// �d�S�q�b�g���W�ւ̃|�C���^����2����������������b�V���̓��������ꏊ
			&model->D_RtoMdistance,		// ���C���烁�b�V���܂ł̋����͂�����
			NULL,						// D3DXINTERSECTINFO�\���̂̔z����i�[����ID3DXBuffer�I�u�W�F�N�g�ւ̃|�C���^
			NULL						// ppAllHits�z����̃G���g�������i�[����|�C���^�A�^��DWORD
		);


		// ���C�s�b�N(���f�������ɔ�΂������C�ƃ}�b�v)
		D3DXIntersect(map->MeshMap, &model->pos, &D3DXVECTOR3(0, 1, 0), &model->tomapUp, NULL, NULL, NULL,
			&model->U_RtoMdistance, NULL, NULL);

		// ���C�s�b�N(�E�ɔ�΂������C�ƃ}�b�v)
		D3DXIntersect(map->MeshMap, &model->pos, &D3DXVECTOR3(1, 0, 0), &model->tomapRight, NULL, NULL, NULL,
			&model->R_RtoMdistance, NULL, NULL);

		// ���C�s�b�N(���ɔ�΂������C�ƃ}�b�v)
		D3DXIntersect(map->MeshMap, &model->pos, &D3DXVECTOR3(-1, 0, 0), &model->tomapLeft, NULL, NULL, NULL,
			&model->L_RtoMdistance, NULL, NULL);

		// ���C�s�b�N(�O�������ɔ�΂������C�ƃ}�b�v)
		D3DXIntersect(map->MeshMap, &model->pos, &D3DXVECTOR3(0, 0, 1), &model->tomapFront, NULL, NULL, NULL,
			&model->F_RtoMdistance, NULL, NULL);

		// ���C�s�b�N(������Z�ɔ�΂������C�ƃ}�b�v)
		D3DXIntersect(map->MeshMap, &model->pos, &D3DXVECTOR3(0, 0, -1), &model->tomapBack, NULL, NULL, NULL,
			&model->B_RtoMdistance, NULL, NULL);
		
	}


//**********************************************************************************
// �֐���:	void escapefromwall(void)
// �߂�l:	�Ȃ�
// ����:	�Ȃ�
// ����:	�ǂւ߂荞�ނ��Ƃ����O�ɖh��
//**********************************************************************************
void escapefromwall(void)
{
	MODEL *model = &modelWk[0];
	D3DXVECTOR3 hosei;
	D3DXVECTOR3 rotCamera;
	float		escapmodellmove = 1.0f;		// �l��␳�����邽��
	float		hoseichi;					// �␳�l���݂̔��a
	// �J�����̌����擾
	rotCamera = GetRotCamera();

//model->move.x *= -MODEL_BAUNCE;
//model->move.y *= -MODEL_BAUNCE;
//model->move.z *= -MODEL_BAUNCE;

	//controlcount = NOCONTROL;
	//model->control = false;


	// �␳�l������
	hoseichi = model->center + LONGHOSEI;
	// �e�X�g�ǂɂ����ĂƂ߂Ă��܂�
	// �ǂƂ̃��C�𔼌a�ɂ���΂���
	// ���C�����a�ȉ��ɂȂ��Ă���ꍇ���a�ɂȂ�悤�ړ������Ă�����΂���
	if (model->R_RtoMdistance <= model->center)
	{
		// ���ɕ␳��������
		hosei.x = model->center - model->R_RtoMdistance;
		model->pos.x -= hosei.x;

	//	model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * 10.0f;
	//	model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * 10.0f;
	}
		
	else if (model->L_RtoMdistance <= model->center)
	{	// �E�ɕ␳��������
		hosei.x = model->center - model->L_RtoMdistance;
		model->pos.x += hosei.x;
	}

	if (model->F_RtoMdistance <= model->center)
	{	// ���ɕ␳��������
		hosei.z = model->center - model->F_RtoMdistance;
		model->pos.z -= hosei.z;

	}
	else if (model->B_RtoMdistance <= model->center)
	{	// �O�ɕ␳��������
		hosei.z = model->center - model->B_RtoMdistance;
		model->pos.z += hosei.z;
	}

	if (model->D_RtoMdistance <= model->center)
	{
	//	hosei.y = model->center - model->D_RtoMdistance;
	//	model->pos.y += hosei.y;
	}




	model->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


//****************************************************************************
// �֐���:	void xinputmove(void)
// ����:	�Ȃ�
// �߂�l:	�Ȃ�
// ����:	xinput�𗘗p���ē����𐧌䂷��
//****************************************************************************
void xinputmove(void)
{
	MODEL *model = &modelWk[0];
	D3DXVECTOR3 rotCamera;

	// �Q�[���p�b�h�̏��
	XINPUT_STATE state;
	// �X�e�B�b�N���͏�����
	state.Gamepad.sThumbLX = 0;
	state.Gamepad.sThumbLY = 0;

	XInputGetState(0, &state);

	// �Q�[���p�b�h�̏�ԕω�
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);




	// �J�����̌����擾
	rotCamera = GetRotCamera();
	// ��ɑO��
	//model->rotDest.y = rotCamera.y + D3DX_PI;

	// �R���g���[���\�Ȃ�󂯕t���鏈��
	if (model->control == true)
	{
		if (model->escapemode == false)
		{
			// �����@10�Ŋ����Ă�̂�10�t���[���ňړ������邽��
			if (state.Gamepad.sThumbLX < -STICKBASE)
			{
				if (state.Gamepad.sThumbLY > STICKBASE)
				{// ���O�ړ�b
					model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

				}
				else if (state.Gamepad.sThumbLY<-STICKBASE)
				{// ����ړ�
					model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;

				}
					else
					{// ���ړ�
						model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
						model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
					}
				}

				// �E
				else if (state.Gamepad.sThumbLX>STICKBASE)
				{
					if (state.Gamepad.sThumbLY>STICKBASE)
					{// �E�O�ړ�
						model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
						model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

					}
					else if (state.Gamepad.sThumbLY< -STICKBASE)
					{// �E��ړ�
						model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
						model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;


					}
					else
					{// �E�ړ�
						model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
						model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

					}
				}
				else if (state.Gamepad.sThumbLY>STICKBASE)
				{// �O�ړ�
					model->move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;

				}
				else if (state.Gamepad.sThumbLY< -STICKBASE)
				{// ��ړ�
					model->move.x -= sinf(rotCamera.y) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y) * VALUE_MOVE_MODEL;
				}
			}
		}
		// �R���g�[���s�\�ȏ�Ԃł��󂯕t���鏈��

	// ���@�̏㏸�Ɖ��~(75.0��20.0�͂��ꂼ�����Ɖ����̒ldefine����)

	if (GetKeyboardPress(DIK_I))
		{// �㏸
			model->move.y += VALUE_MOVE_MODEL * 0.5f;

			if (model->pos.y < 75.0f)
			{
				g_fSizeShadow += 0.2f;
				g_colShadow.a -= 0.004f;
			}
		}
	if (GetKeyboardPress(DIK_K))
		{// ���~
			model->move.y -= VALUE_MOVE_MODEL * 0.5f;

			if (model->pos.y > 20.0f)
			{
				g_fSizeShadow -= 0.2f;
				g_colShadow.a += 0.004f;
			}
		}

	if (model->shot_on == true)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER || state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			// �ʔ���
			D3DXVECTOR3 pos = model->pos;
			evolve_modelbullet(model->shotlv);
			model->shot = 0.0f;
			model->shot_on = false;


		}
	}

	 if (model->shot_on == false)
	{
		model->shot++;
		if (model->shot >= SHOTKANKAKU)
		{
			model->shot_on = true;
		}
	}


	// �㏸
	if (state.Gamepad.sThumbRY > STICKBASE)
	{
		model->rot.x += 0.01f;
	}


	// ���~
	else if (state.Gamepad.sThumbRY < -STICKBASE)
	{
		model->rot.x -= 0.01f;
	

	}
}

//****************************************************************************
// �֐���:	void xinputrot(void)
// ����:	�Ȃ�
// �߂�l:	�Ȃ�
// ����:	xinput�𗘗p���Ď��@�̉�]�𐧌䂷��
//****************************************************************************
void xinputrot(void)
{
	MODEL *model = &modelWk[0];
	D3DXVECTOR3 rotCamera;

	// �Q�[���p�b�h�̏��
	XINPUT_STATE state;
	XInputGetState(0, &state);

	// �Q�[���p�b�h�̏�ԕω�
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	//model->rot.y

	// ������
	if (state.Gamepad.sThumbRX < -STICKBASE)
	{
		model->rot.y = hidari;
		// ����Ɍ�����
		if (state.Gamepad.sThumbRY > STICKBASE/2)
		{
			model->rot.y = hidariue;
		}
		// �����֌�����
		else if(state.Gamepad.sThumbRY < -STICKBASE/2)
		{
			model->rot.y = hidarishita;
		}

	}

	// �E����
	else if (state.Gamepad.sThumbRX > STICKBASE)
	{
		model->rot.y = migi;
		// �E��
		if (state.Gamepad.sThumbRY > STICKBASE)
		{
			model->rot.y = migiue;
		}

		// �E��
		else if (state.Gamepad.sThumbRY < -STICKBASE)
		{
			model->rot.y = migishita;
		}

	}

	else if (state.Gamepad.sThumbRY > STICKBASE)
	{
		model->rot.y = ue;
	}

	else if (state.Gamepad.sThumbRY < -STICKBASE)
	{
		model->rot.y = shita;
	}
		

}
//****************************************************************************
// �֐���:	void keyboardmove(void)
// ����:	�Ȃ�
// �߂�l:	�Ȃ�
// ����:	�L�[�{�[�h�œ��삳����
//****************************************************************************
void keyboardmove(void)
{
	MODEL *model = &modelWk[0];
	D3DXVECTOR3 rotCamera;
	// �J�����̌����擾
	rotCamera = GetRotCamera();
	// ��ɑO��
	//model->rotDest.y = rotCamera.y + D3DX_PI;


	// �R���g���[���\�Ȃ�󂯕t���鏈��
	if (model->control == true)
	{
		if (model->escapemode == false)
		{
			// ���䓶�q�̉�]���ꎞ�I�ɖ�����
			// �����@10�Ŋ����Ă�̂�10�t���[���ňړ������邽��
			if (GetKeyboardPress(DIK_A))
			{
				if (GetKeyboardPress(DIK_W))
				{// ���O�ړ�b
					model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

					model->rot.x += -MODEL_MOVEROLlX / 10;
					if (model->rot.x <= -MODEL_MOVEROLlX)
					{
						model->rot.x = -MODEL_MOVEROLlX;
					}
					model->rot.z += -MODEL_MOVEROLL / 10;
					if (model->rot.z <= -MODEL_MOVEROLL)
					{
						model->rot.z = -MODEL_MOVEROLL;
					}
					roton = true;
					//model->rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
				}
				else if (GetKeyboardPress(DIK_S))
				{// ����ړ�
					model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
				
					model->rot.x += MODEL_MOVEROLlX / 10;
					if (model->rot.x >= MODEL_MOVEROLlX)
					{
						model->rot.x = MODEL_MOVEROLlX;
					}
					model->rot.z += -MODEL_MOVEROLL / 10;
					if (model->rot.z <= -MODEL_MOVEROLL)
					{
						model->rot.z = -MODEL_MOVEROLL;
					}
					//	model->rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
					roton = true;
				}
				else
				{// ���ړ�
					model->move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

					model->rot.z += -MODEL_MOVEROLL / 10;
					if (model->rot.z <= -MODEL_MOVEROLL)
					{
						model->rot.z = -MODEL_MOVEROLL;
					}

					model->rot.y = 1.57f;		// ��
					//model->rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
					roton = true;
				}
			}
			else if (GetKeyboardPress(DIK_D))
			{
				if (GetKeyboardPress(DIK_W))
				{// �E�O�ړ�
					model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

					model->rot.x += -MODEL_MOVEROLL / 10;
					if (model->rot.x <= -MODEL_MOVEROLL)
					{
						model->rot.x = -MODEL_MOVEROLL;
					}
					model->rot.z += MODEL_MOVEROLL / 10;
					if (model->rot.z >= MODEL_MOVEROLL)
					{
						model->rot.z = MODEL_MOVEROLL;
					}
					//model->rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
					roton = true;
				}
				else if (GetKeyboardPress(DIK_S))
				{// �E��ړ�
					model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
					model->rot.x += MODEL_MOVEROLlX / 10;
					if (model->rot.x >= MODEL_MOVEROLlX)
					{
						model->rot.x = MODEL_MOVEROLlX;
					}
					model->rot.z += MODEL_MOVEROLL / 10;
					if (model->rot.z >= MODEL_MOVEROLL)
					{
						model->rot.z = MODEL_MOVEROLL;
					}
					//	model->rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
					roton = true;
				}
				else
				{// �E�ړ�
					model->move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
					model->move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

					model->rot.z += MODEL_MOVEROLL / 10;
					if (model->rot.z >= MODEL_MOVEROLL)
					{
						model->rot.z = MODEL_MOVEROLL;
					}

					model->rot.y = -1.57f;			// �E
					//model->rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
					roton = true;
				}
			}
			else if (GetKeyboardPress(DIK_W))
			{// �O�ړ�
				model->move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;
				model->move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;
				model->rot.x += -MODEL_MOVEROLlX / 10;
				if (model->rot.x <= -MODEL_MOVEROLlX)
				{
					model->rot.x = -MODEL_MOVEROLlX;
				}

				model->rot.y = 3.14f;

				//model->rotDest.y = rotCamera.y + D3DX_PI;
				roton = true;
			}
			else if (GetKeyboardPress(DIK_S))
			{// ��ړ�
				model->move.x -= sinf(rotCamera.y) * VALUE_MOVE_MODEL;
				model->move.z -= cosf(rotCamera.y) * VALUE_MOVE_MODEL;

				model->rot.x += MODEL_MOVEROLlX / 10;
				if (model->rot.x > MODEL_MOVEROLlX)
				{
					model->rot.x = MODEL_MOVEROLlX;
				}
				//model->rotDest.y = rotCamera.y ;
				model->rot.y = 0.0f;
				roton = true;
			}
		}
	}
	// �R���g�[���s�\�ȏ�Ԃł��󂯕t���鏈��

	//if (GetKeyboardPress(DIK_LSHIFT))
	//{// ����]
	//	model->rotDest.y -= VALUE_ROTATE_MODEL;
	//	if (model->rotDest.y < -D3DX_PI)
	//	{
	//		model->rotDest.y += D3DX_PI * 2.0f;
	//	}
	//}
	//if (GetKeyboardPress(DIK_RSHIFT))
	//{
	//	// �E��]
	//	model->rotDest.y += VALUE_ROTATE_MODEL;
	//	if (model->rotDest.y > D3DX_PI)
	//	{
	//		model->rotDest.y -= D3DX_PI * 2.0f;
	//	}
	//}

	// ���@�̏㏸�Ɖ��~(75.0��20.0�͂��ꂼ�����Ɖ����̒ldefine����)

	if (GetKeyboardPress(DIK_I))
	{// �㏸
		model->move.y += VALUE_MOVE_MODEL * 0.5f;

		if (model->pos.y < 75.0f)
		{
			g_fSizeShadow += 0.2f;
			g_colShadow.a -= 0.004f;
		}
	}
	if (GetKeyboardPress(DIK_K))
	{// ���~
		model->move.y -= VALUE_MOVE_MODEL * 0.5f;
	
		if (model->pos.y > 20.0f)
		{
			g_fSizeShadow -= 0.2f;
			g_colShadow.a += 0.004f;
		}
	}

	if (GetKeyboardTrigger(DIK_L))
	{
		// �ʔ���
		D3DXVECTOR3 pos = model->pos;
		evolve_modelbullet(model->shotlv);
	}

}


//****************************************************************************
// �֐���:	void evolve_modelbullet(void)
// ����:	�Ȃ�
// �߂�l:	�Ȃ�
// ����:	���@�̃V���b�g���x���ɉ����Ēe�̐ݒu���@��ς���
//****************************************************************************
void evolve_modelbullet(int shotlv)
{
	MODEL *model = &modelWk[0];
	int lvkakunou;				// �󂯎�������x�������Ă���
	// SetBulletmk2�̐���
	// ��4�����@�������̕ω���(�v���X�ŉE�@�}�C�i�X�͍�)
	// ��5�����@�c�����̕ω���(�v���X�ŏ�@�}�C�i�X�͉�����)
	// ��{�I�ɏ����Ŏw��

	if (shotlv == 0)
	{
		SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE,0, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (shotlv == 1)
	{
		SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE,0, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f));
		SetBulletmk2(D3DXVECTOR3(model->pos.x +3.0f,model->pos.y,model->pos.z), BULLETMK2BASESIZE, BULLETMK2BASESIZE,0, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (shotlv == 2)
	{
		SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE,0, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE,0.1f, 0.01f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE,-0.1f, 0.01f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (shotlv >= 3)
	{
		if(shotlv > 4)
		{
			shotlv = 4;
		}

		for(int no = 0; no < shotlv; no++)
		{
			SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE, 0, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE / 2, 0.2f*(1.5f*no), 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			SetBulletmk2(model->pos, BULLETMK2BASESIZE, BULLETMK2BASESIZE / 2, -0.2f*(1.5f*no), 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		}
	}
}