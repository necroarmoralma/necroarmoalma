//=============================================================================
//
// �J�������� [camera.cpp]
// Author : GP11B243 33 �R�{ �s��
//
//=============================================================================
#include "camera.h"
#include "model.h"
#include "input.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// ����p
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z			(50.0f)					// �r���[���ʂ�NearZ�l(���Ȃ�����قǎ�O�̂����)
#define	VIEW_FAR_Z			(2100.0f)				// �r���[���ʂ�FarZ�l(���̒l���グ��قǉ����܂ňڂ���)
#define	VALUE_MOVE_CAMERA	(2.0f)					// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// �J�����̉�]��

#define	INTERVAL_CAMERA_R	(20.5f)					// ���f���̎����̐�܂ł̋���
#define	RATE_CHASE_CAMERA_P	(0.35f)					// �J�����̎��_�ւ̕␳�W��
#define	RATE_CHASE_CAMERA_R	(0.20f)					// �J�����̒����_�ւ̕␳�W��

#define	CHASE_HEIGHT_P		(150.0f)				// �ǐՎ��̎��_�̍���
#define	CHASE_HEIGHT_R		(10.0f)					// �ǐՎ��̒����_�̍���
// �J�����̈ʒu�𒲐�
#define setCy				(70.0f)
#define setCz				(20.0f)

#define UEMIOROSHI			(400.0f)	// �ォ�猩���낵�����_
#define KATAMUKI			(270.0f)

// �J����������ς���ꍇ����������
#define setting				(50.0f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXVECTOR3		g_posCameraEye;				// �J�����̎��_
D3DXVECTOR3		g_posCameraAt;				// �J�����̒����_
D3DXVECTOR3		g_posCameraUp;				// �J�����̏����
D3DXVECTOR3		g_posCameraEyeDest;			// �J�����̎��_�̖ړI�ʒu
D3DXVECTOR3		g_posCameraAtDest;			// �J�����̒����_�̖ړI�ʒu
D3DXVECTOR3		g_rotCamera;				// �J�����̉�]
float			g_fLengthIntervalCamera;	// �J�����̎��_�ƒ����_�̋���
D3DXMATRIX		g_mtxView;					// �r���[�}�g���b�N�X
D3DXMATRIX		g_mtxProjection;			// �v���W�F�N�V�����}�g���b�N�X


float			zzoom;						// ���f���ƃJ������Z�������̋���
float			yzoom;						// ���f���ƃJ������Y�������̋���
float			len;						// ���_�ƒ����_�̋���
//=============================================================================
// �J�����̏�����
//=============================================================================
HRESULT InitCamera(void)
{
	g_posCameraEye = D3DXVECTOR3(0.0f, 200.0f, -200.0f);
	g_posCameraAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_posCameraEyeDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_posCameraAtDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx, vz;
	vx = g_posCameraEye.x - g_posCameraAt.x;
	vz = g_posCameraEye.z - g_posCameraAt.z;
	g_fLengthIntervalCamera = sqrtf(vx * vx + vz * vz);
	// �Y�[�������̏�����
	zzoom = ZJIKU;
	yzoom = YJIKU;

	yzoom += KATAMUKI;
	// �����_�Ǝ��_�̋������v�Z����
	D3DXVECTOR3 temp = g_posCameraAt - g_posCameraEye;

	len = g_fLengthIntervalCamera +50.0f;

	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	MODEL *model = GetModel(0);
	D3DXVECTOR3 temp = g_posCameraEye - g_posCameraAt;					// ���_�ƒ����_�̍���
	temp /= 300;														// ���ꂼ��̗v�f������


																		// �J�����̒����_���v���C���[�̍��W��
	g_posCameraAt.x = model->pos.x;
	g_posCameraAt.y = model->pos.y;
	g_posCameraAt.z = model->pos.z;


	////
	////// �J�����̎��_�𒍎��_��菭����O���������
	g_posCameraEye.x = g_posCameraAt.x -sin(g_rotCamera.y)*len;			//-sin(��]�p�x)*�J�����̋���
	g_posCameraEye.y = g_posCameraAt.y + 500.0f;// +yzoom + setCy;// +400.0f;// +yzoom + setCy;
	g_posCameraEye.z = g_posCameraAt.z - cos(g_rotCamera.y)*len;// -300.0f;



	if(GetKeyboardPress(DIK_Z))
	{
		zzoom += 10;
	}
	if(GetKeyboardPress(DIK_C))
	{
		zzoom -= 10;
	}

	if(GetKeyboardPress(DIK_V))
	{
		yzoom += 10;
	}

	if(GetKeyboardPress(DIK_N))
	{
		yzoom -= 10;
	}

	if(GetKeyboardPress(DIK_Y))
	{// ���_�ړ��u��v
		g_posCameraEye.y += VALUE_MOVE_CAMERA;
	}
	if(GetKeyboardPress(DIK_N))
	{// ���_�ړ��u���v
		g_posCameraEye.y -= VALUE_MOVE_CAMERA;
	}

	if(GetKeyboardPress(DIK_Q))
	{// �����_����u���v
		g_rotCamera.y -= VALUE_ROTATE_CAMERA;
		if(g_rotCamera.y < -D3DX_PI)
		{
			g_rotCamera.y += D3DX_PI*2.0f;
		}

		g_posCameraAt.x = g_posCameraEye.x + sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraAt.z = g_posCameraEye.z + cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_E))
	{// �����_����u�E�v
		g_rotCamera.y += VALUE_ROTATE_CAMERA;
		if(g_rotCamera.y > D3DX_PI)
		{
			g_rotCamera.y -= D3DX_PI*2.0f;
		}

		g_posCameraAt.x = g_posCameraEye.x + sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraAt.z = g_posCameraEye.z + cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}

	//g_rotCamera = model->rot;

	//if(GetKeyboardPress(DIK_T))
	//{// �����_�ړ��u��v
	//	g_posCameraAt.y += VALUE_MOVE_CAMERA;
	//}
	//if(GetKeyboardPress(DIK_B))
	//{// �����_�ړ��u���v
	//	g_posCameraAt.y -= VALUE_MOVE_CAMERA;
	//}

	//

	//PrintDebugProc("len = %f", len);
	//PrintDebugProc("�J�����̋���Y	: (%f)]ln", yzoom); 
	//PrintDebugProc("[�J�����̋���Z  : (%f)]|n", zzoom);
	//PrintDebugProc("[�J�����̎��_  �F(%f : %f : %f)]\n", g_posCameraEye.x, g_posCameraEye.y, g_posCameraEye.z);
	//PrintDebugProc("[�J�����̒����_�F(%f : %f : %f)]\n", g_posCameraAt.x, g_posCameraAt.y, g_posCameraAt.z);
	//PrintDebugProc("[�J�����̌���  �F(%f)]\n", g_rotCamera.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("*** ���_���� ***\n");
	//PrintDebugProc("�O�ړ� : W\n");
	//PrintDebugProc("��ړ� : S\n");
	//PrintDebugProc("���ړ� : A\n");
	//PrintDebugProc("�E�ړ� : D\n");
	//PrintDebugProc("��ړ� : Y\n");
	//PrintDebugProc("���ړ� : N\n");
	//PrintDebugProc("������ : Z\n");
	//PrintDebugProc("�E���� : C\n");
	//PrintDebugProc("\n");

	PrintDebugProc("*** �����_���� ***\n");
	PrintDebugProc("��ړ� : T\n");
	PrintDebugProc("���ړ� : B\n");
	PrintDebugProc("������ : Q\n");
	PrintDebugProc("�E���� : E\n");
	PrintDebugProc("\n");
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_mtxView,
		&g_posCameraEye,		// �J�����̎��_
		&g_posCameraAt,		// �J�����̒����_
		&g_posCameraUp);		// �J�����̏����

								// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
		VIEW_ANGLE,			// ����p
		VIEW_ASPECT,		// �A�X�y�N�g��
		VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l

							// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);
}

//=============================================================================
// �J�����̌����̎擾
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

//=============================================================================
// �r���[�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}

