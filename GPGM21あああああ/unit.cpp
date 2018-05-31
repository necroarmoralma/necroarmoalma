//**************************************************************************************
// �t�@�C����:	unitWk[no].cpp
// ����:		�G�֘A�̃v���O����
// �쐬����:	2017/11/09
// �쐬��:		�R�{ �s��
//**************************************************************************************


//**************************************************************************************
// �C���N���[�h�t�@�C��
//**************************************************************************************
#include "unit.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"
#include "bulletmk2.h"
#include "meshfield.h"
#include "model.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	UNIT_AIRPLANE			// �ǂݍ��ރ��f����
#define	VALUE_MOVE_UNIT	(0.80f)						// �ړ����x
#define	RATE_MOVE_UNIT		(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_UNIT	(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_UNIT	(0.20f)						// ��]�����W��
#define	BULLET_SIZEX		(20.0f)						// �e�̑傫����lX
#define BULLET_SIZEY		(20.0f)						// �e�̑傫����lY
#define UNIT_MAX			(1)							// �W�J���郆�j�b�g�̐�
#define KAITEN_LONG				(60.5f)							// ��]�̑傫��
#define KAITEN_SPEED			(D3DX_PI * 0.03f)						// ��]���x


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	UNIT_TE
} UNITTEX;

typedef enum
{
	UE = 0,
	MIGIUE,
	MIGI,
	MIGISHITA,
	SHITA,
	HIDARISHITA,
	HIDARI,
	HIDARIUE,
	MUKI_MAX
} MUKI;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

DWORD				g_nNumMatUnit;				// �������̑���
UNIT				unitWk[UNIT_MAX];					// ���f���\����
int					haibi;

// �e�t�@�C���̏ꏊ
char *UNITFileName[] =
{
	"data/MODEL/bitmodel.x",
	"data/MODEL/ahiru.x",
};
//=============================================================================
// ����������
//=============================================================================
HRESULT InitUnit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	UNIT *unit = &unitWk[0];
	MODEL *model = GetModel(0);
	D3DXVECTOR3 rotCamera;

	for (int no = 0; no < UNIT_MAX; no++)
	{

		unitWk[no].Texture3D = NULL;
		unitWk[no].Mesh = NULL;
		unitWk[no].BuffMat = NULL;
		unitWk[no].use = false;
		haibi = no % BUTAI_MAX;		// �]��𗘗p

		switch (haibi)
		{
		case ICHI:

			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(UNITFileName[haibi],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&unitWk[no].BuffMat,
				NULL,
				&g_nNumMatUnit,
				&unitWk[no].Mesh)))
			{
				return E_FAIL;
			}
			break;

		case NI:

			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(UNITFileName[haibi],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&unitWk[no].BuffMat,
				NULL,
				&g_nNumMatUnit,
				&unitWk[no].Mesh)))
			{
				return E_FAIL;
			}
			break;

		default:			//�@�����ǂ�ɂ����Ă͂܂�Ȃ��ꍇ��s�@

			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(UNITFileName[0],		//�ǂ�ɂ����Ă͂܂�Ȃ��ꍇ0�Ԗ�
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&unitWk[no].BuffMat,
				NULL,
				&g_nNumMatUnit,
				&unitWk[no].Mesh)))
			{
				return E_FAIL;
			}
			break;
		}

#if 0
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				TEXTURE_FILENAME,		// �t�@�C���̖��O
				&unitWk[no].Texture3D);	// �ǂݍ��ރ������[
#endif

		// �����ݒ�
			unitWk[no].kaiten = 0;
			unitWk[no].pos = model->pos;
			if (no == 3)
			{
				unitWk[no].pos = model->pos;
			}
			unitWk[no].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			unitWk[no].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			unitWk[no].rotDest = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
			unitWk[no].scl = D3DXVECTOR3(1.0f, 1.0f,1.0f);
			//SetUnit();
			

			// �e�̐���
			unitWk[no].ShadowID = CreateShadow(unitWk[no].pos, 25.0f, 25.0f);

			unitWk[no].ShadowSize = 25.0f;
			unitWk[no].Shadowcol = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		}

		return S_OK;
	
}

//=============================================================================
// �I������
//=============================================================================
void UninitUnit(void)
{
	for (int no = 0; no < UNIT_MAX; no++)
	{
		if (unitWk[no].Texture3D != NULL)
		{// �e�N�X�`���̊J��
			unitWk[no].Texture3D->Release();
			unitWk[no].Texture3D = NULL;
		}

		if (unitWk[no].Mesh != NULL)
		{// ���b�V���̊J��
			unitWk[no].Mesh->Release();
			unitWk[no].Mesh = NULL;
		}

		if (unitWk[no].BuffMat != NULL)
		{// �}�e���A���̊J��
			unitWk[no].BuffMat->Release();
			unitWk[no].BuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUnit(void)
{
	MODEL *model = GetModel(0);
	D3DXVECTOR3 rotCamera;
	UNIT *unit = &unitWk[0];
//	float fDiffRotY;
	int haibi;				// ���j�b�g�͂ǂ��ɔz�������̂�
	int muki = 0;				// ���j�b�g�̌���
	// �J�����̌����擾
	rotCamera = GetRotCamera();

	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unitWk[i].use = true)
		{
			// muki�̒l����(���f���̕��p�j
			if (model->rotDest.y == ue)
			{
				muki = UE;
			}
			if (model->rotDest.y == migiue)
			{
				muki = MIGIUE;
			}
			if (model->rotDest.y == migi)
			{
				muki = MIGI;
			}
			if (model->rotDest.y == migishita)
			{
				muki = MIGISHITA;
			}
			if (model->rotDest.y == shita)
			{
				muki = SHITA;
			}
			if (model->rotDest.y == hidarishita)
			{
				muki = HIDARISHITA;
			}
			if (model->rotDest.y == hidari)
			{
				muki = HIDARI;
			}
			if (model->rotDest.y == hidariue)
			{
				muki = HIDARIUE;
			}
		}
	}

	
	for (int no = 0; no < UNIT_MAX; no++)
	{
		if (unitWk[no].use == true)
		{
		


		//
		// �e�X�g�p

			unitWk[no].kaiten += KAITEN_SPEED;
			if (unitWk[no].kaiten > -D3DX_PI)
			{
				unitWk[no].kaiten -= D3DX_PI * 2.0f;
			}
		// �q�@�͂ǂ��̃`�[���ɂ����̂�����
			haibi = no % BUTAI_MAX;		// �]��𗘗p
			switch (haibi)
			{
				//�΂߈ړ�
			case ICHI:
				


				unitWk[no].pos.x = model->pos.x + (sinf(unitWk[no].kaiten) * VALUE_MOVE_MODEL *KAITEN_LONG);				// ������31.5f�Ƃ��͂��񂵂イ�݂�����
				unitWk[no].pos.y = model->pos.y;
				unitWk[no].pos.z = model->pos.z + (cosf(unitWk[no].kaiten) * VALUE_MOVE_MODEL *KAITEN_LONG);			// xsin������ + zcos������ sin(10)

					break;

				default :
					unitWk[no].pos.z += 1.0f;

					break;

			}
			unitWk[no].rot = model->rot;

			

			// �ړ��ʉ��Z
			//unitWk[no].pos.x +=  unitWk[no].move.x;//+ unitWk[no].move.x;
			//unitWk[no].pos.y +=  unitWk[no].move.y;//+ unitWk[no].move.y;
			//unitWk[no].pos.z +=  unitWk[no].move.z;//+ unitWk[no].move.z;

			if (unitWk[no].pos.y < 5.0f)
			{
				unitWk[no].pos.y = 5.0f;
			}
			if (unitWk[no].pos.y > 75.0f)
			{
				unitWk[no].pos.y = 75.0f;
			}

			// �ړ��ʂɊ�����������
			//unitWk[no].move.x += (0.0f - model->move.x) * RATE_MOVE_MODEL;
			//unitWk[no].move.y += (0.0f - model->move.y) * RATE_MOVE_MODEL;
			//unitWk[no].move.z += (0.0f - model->move.z) * RATE_MOVE_MODEL;


			// �̈�O�ɍs������X�g�b�v(��2���Ă���̂͂߂荞�܂Ȃ��悤�ɂ��邽��)
			if (unitWk[no].pos.x + (unitWk[no].scl.x) < -MAPLIMIT_X)
			{
				unitWk[no].pos.x = -MAPLIMIT_X;
			}
			if (unitWk[no].pos.x > MAPLIMIT_X)
			{
				unitWk[no].pos.x = MAPLIMIT_X;
			}
			if (unitWk[no].pos.z < -MAPLIMIT_Z)
			{
				unitWk[no].pos.z = -MAPLIMIT_Z;
			}
			if (unitWk[no].pos.z / 2.0f > MAPLIMIT_Z)
			{
				unitWk[no].pos.z = MAPLIMIT_Z;
			}



			// �e�̈ʒu�ݒ�
			SetPositionShadow(unitWk[no].ShadowID, D3DXVECTOR3(unitWk[no].pos.x, 0.1f, unitWk[no].pos.z));

			SetVertexShadow(unitWk[no].ShadowID, unitWk[no].ShadowSize, unitWk[no].ShadowSize);
			SetColorShadow(unitWk[no].ShadowID, unitWk[no].Shadowcol);
		}
	}
	//
	//PrintDebugProc("[��s�@�̈ʒu  �F(%f : %f : %f)]\n", unitWk[no].pos.x, unitWk[no].pos.y, unitWk[no].pos.z);
	//PrintDebugProc("[��s�@�̌���  �F(%f) < �ړI�̌���:(%f) >]\n", unitWk[no].rot.y, unitWk[no].rotDest.y);
	//PrintDebugProc("\n");
	//
	//PrintDebugProc("*** ��s�@���� ***\n");
	//PrintDebugProc("�O�ړ� : ��\n");
	//PrintDebugProc("��ړ� : ��\n");
	//PrintDebugProc("���ړ� : ��\n");
	//PrintDebugProc("�E�ړ� : ��\n");
	//PrintDebugProc("�㏸   : T\n");
	//PrintDebugProc("���~   : Y\n");
	//PrintDebugProc("������ : LSHIFT\n");
	//PrintDebugProc("�E���� : RSHIFT\n");
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUnit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	UNIT *unit = &unitWk[0];


	for (int no = 0; no < UNIT_MAX; no++)
	{
		if (unitWk[no].use = true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&unitWk[no].World);


			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, unitWk[no].scl.x, unitWk[no].scl.y, unitWk[no].scl.z);
			D3DXMatrixMultiply(&unitWk[no].World, &unitWk[no].World, &mtxScl);


			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, unitWk[no].rot.y, unitWk[no].rot.x, unitWk[no].rot.z);
			D3DXMatrixMultiply(&unitWk[no].World, &unitWk[no].World, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, unitWk[no].pos.x, unitWk[no].pos.y, unitWk[no].pos.z);
			D3DXMatrixMultiply(&unitWk[no].World, &unitWk[no].World, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &unitWk[no].World);


			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)unitWk[no].BuffMat->GetBufferPointer();



			//// ���݂̃}�e���A�����擾
			//pDevice->GetMaterial(&matDef);

			//// �}�e���A�����ɑ΂���|�C���^���擾
			//pD3DXMat = (D3DXMATERIAL*)unitWk[no].BuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatUnit; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, unitWk[no].Texture3D);

				// �`��
				unitWk[no].Mesh->DrawSubset(nCntMat);
			}
		}
	}
	// �}�e���A�����f�t�H���g�ɖ߂����Q
	pDevice->SetMaterial(&matDef);
}

//*****************************************************************************
// �֐���:	int SetUnit(D3DXVECTOR3 pos, float wide, float height, D3DXCOLOR col)
//
//
// ����: ���j�b�g�̍쐬
//*****************************************************************************
int SetUnit(void)
{
	MODEL *model = GetModel(0);
	int nIdxUnit = -1;

	for (int no = 0; no < UNIT_MAX; no++)
	{
		if (unitWk[no].use = false)		// ���g�p�̃o���b�g����
		{
			// �����ݒ�
			unitWk[no].kaiten = 0;
			unitWk[no].pos = model->pos;
			unitWk[no].move = model->move;
			unitWk[no].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			unitWk[no].rotDest = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
			unitWk[no].scl = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
			unitWk[no].use = true;

			// �e�̐���
			unitWk[no].ShadowID = CreateShadow(unitWk[no].pos, 25.0f, 25.0f);

			unitWk[no].ShadowSize = 25.0f;
			unitWk[no].Shadowcol = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

			break;
		}
	}
	return nIdxUnit;
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionUnit(int unitno)
{
	//UNIT *unit = &unitWk[0];
	return unitWk[unitno].pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationUnit(int unitno)
{
	UNIT *unit = &unitWk[0];
	return unitWk[unitno].rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestUnit(int unitno)
{
	UNIT *unit = &unitWk[0];
	return  unitWk[unitno].rotDest;
}

//*****************************************************************************
// �Q�b�g�֐�
//*****************************************************************************
UNIT *GetUnit(int no)
{
	return(&unitWk[0]);
}