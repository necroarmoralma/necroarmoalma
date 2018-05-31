//*****************************************************************************************************
// �t�@�C����:	model_longcheck.cpp
// �쐬��:		1��22��
// ����:		���f����ǂݍ��ݒ��������߂�
//*****************************************************************************************************

//*****************************************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************************************
#include "model_longcheck.h"
#include "model.h"
#include "setting.h"
#include "map.h"
//*****************************************************************************************************
// �}�N����`
//*****************************************************************************************************

//*****************************************************************************************************
// �\���̒�`
//*****************************************************************************************************
// ����p�̃��C���΂���_
#define CHECKBASE				D3DXVECTOR3(0.0f,0.0f,0.0f)
// ����p���f���̏ꏊ
#define CHECKMODELCENTER		"data/LENCHECKMODEL/check_modelcenter.x"
#define CHECKMODELHIGHER		"data/LENCHECKMODEL/check_modelhigher.x"
#define CHECKENEMYCENTER		"data/LENCHECKMODEL/check_enemycenter.x"
//*****************************************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************************************
HRESULT loadmodel(void);
void GetModelLong(void);
void EndLongCheck(void);



//*****************************************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************************************

// ����p(�������ɒǉ�����̂�Y��Ȃ�)
char *CheckModelFileName[]=				// CheckModelFileName�ɃJ�[�\�����킹��Ɨv�f���ł�
{
	CHECKMODELCENTER,
	CHECKMODELHIGHER,
	CHECKENEMYCENTER
};

MODELCHECK		modelcheck[CHECKMODEL_MAX];

//*****************************************************************************************************
// �֐���:	void checkmodellong(void)
// ����:	����
// �߂�l:	����
// ����:	���f���̒�������̏���
//*****************************************************************************************************
void checkmodellong(void)
{
	loadmodel();			// ����p�̃��f����ǂݍ���
	GetModelLong();			// ������}��i�[
	EndLongCheck();			// �I��
}

//*****************************************************************************************************
// �֐���:	HRESULT loadmodel(void)
// ����:	�Ȃ�
// �߂�l:	�Ȃ�
// ����:	������}�邽�߂̔|���S����ǂݍ���
//*****************************************************************************************************
HRESULT loadmodel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	
	// X�t�@�C���̓ǂݍ���
	for (int no = 0; no < CHECKMODEL_MAX; no++)
	{
		if (FAILED(D3DXLoadMeshFromX(CheckModelFileName[no],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&modelcheck[no].BuffMatCheck,
			NULL,
			&modelcheck[no].NumMatCheck,
			&modelcheck[no].MeshModelCheck)))
		{
			return E_FAIL;
		}
	}

	InitMap();

}

//******************************************************************************************************
// �֐���:	void GetModelLong(void)
// ����:	�Ȃ�
// �߂�l:	�Ȃ�
// ����:	���_���瑪��p�̃|���S���փ��C���΂��Ē�����}��
//			���@�֘A�̒����͂�����
//******************************************************************************************************
void GetModelLong(void)
{
	MODEL *model = GetModel(0);
	ENEMYLENGTH *enemylength = GetEnemylength(0);
	MAP *map = GetMap(0);

	// ��_���瑪��p�|���S���փ��C���΂�������}��
	// ���S�܂�
	D3DXIntersect(modelcheck[MODELCENTERCHECK].MeshModelCheck, &CHECKBASE, &D3DXVECTOR3(0, 1, 0), &modelcheck[MODELCENTERCHECK].hitcheck, NULL, NULL, NULL,
		&model->center, NULL, NULL);
	
	//�@�Ă�
	D3DXIntersect(modelcheck[ENEMYLENGTHCHECK].MeshModelCheck, &CHECKBASE, &D3DXVECTOR3(0, 1, 0), &modelcheck[MODELCENTERCHECK].hitcheck, NULL, NULL, NULL,
		&enemylength->enemycenter, NULL, NULL);

	// �S��
	D3DXIntersect(modelcheck[MODELCENTERCHECK].MeshModelCheck, &CHECKBASE, &D3DXVECTOR3(0, 1, 0), &modelcheck[MODELHIGHERCHECK].hitcheck, NULL, NULL, NULL,
		&model->higher, NULL, NULL);

	// �}�b�v����
	D3DXIntersect(map->MeshMap, &CHECKBASE, &D3DXVECTOR3(1, 0, 0), &modelcheck[MODELHIGHERCHECK].hitcheck, NULL, NULL, NULL,
		&enemylength->map_xmax, NULL, NULL);

	D3DXIntersect(map->MeshMap, &CHECKBASE, &D3DXVECTOR3(-1, 0, 0), &modelcheck[MODELHIGHERCHECK].hitcheck, NULL, NULL, NULL,
		&enemylength->map_xlow, NULL, NULL);

	D3DXIntersect(map->MeshMap, &CHECKBASE, &D3DXVECTOR3(0, 0, 1), &modelcheck[MODELHIGHERCHECK].hitcheck, NULL, NULL, NULL,
		&enemylength->map_zmax, NULL, NULL);

	D3DXIntersect(map->MeshMap, &CHECKBASE, &D3DXVECTOR3(0, 0, -1), &modelcheck[MODELHIGHERCHECK].hitcheck, NULL, NULL, NULL,
		&enemylength->map_zlow, NULL, NULL);


}

//*******************************************************************************************************
// �֐���;	void EndLongCheck(void)
// ����:	�Ȃ�
// �߂�l:	�Ȃ�
// ����:	�����̑���Ɗi�[���I�������g��Ȃ����̂͊J������
//*******************************************************************************************************
void EndLongCheck(void)
{
	for (int no = 0; no < CHECKMODEL_MAX; no++)
	{
		// ���b�V���J��
		if (modelcheck[no].MeshModelCheck != NULL)
		{
			modelcheck[no].MeshModelCheck->Release();
			modelcheck[no].MeshModelCheck = NULL;
		}

		// �}�e���A���J��
		if (modelcheck[no].BuffMatCheck != NULL)
		{
			modelcheck[no].BuffMatCheck->Release();
			modelcheck[no].BuffMatCheck = NULL;
		}
	}

	UninitMap();
}