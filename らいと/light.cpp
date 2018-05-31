//=============================================================================
//
// ���C�g���� [light.cpp]
//  Author : HAL�Q�[���w�ȓ�N���ے�1�N�@�R�{�s��
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LIGHT_MAX	(8)				// ���s�����̐�
#define SPOT_MAX	(2)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
GAMELIGHT LightWk[LIGHT_MAX];				// ���C�g�̃��[�N
bool		Directional_switch[LIGHT_MAX];
bool		Point_switch[LIGHT_MAX + ENEMYMAX];
bool		Anbient_switch;
bool		Spot_switch[LIGHT_MAX + ENEMYMAX + SPOT_MAX];

//=============================================================================
// ���C�g�̏���������
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �t���O������
	for (int no = 0; no < LIGHT_MAX;no++)
	{
		Directional_switch[no] = false;
	}

	for (int no = 0; no < ENEMYMAX; no++)
	{
		Point_switch[no] = true;
	}

	Anbient_switch = true;
	for (int no = 0; no < SPOT_MAX; no++)
	{
		Spot_switch[no] = true;
	}



	for (int no = 0; no < LIGHT_MAX; no++)
	{
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&LightWk[no], sizeof(D3DLIGHT9));

		// ���C�g�̃^�C�v�̐ݒ�
		LightWk[no].Lightstatus.Type = D3DLIGHT_DIRECTIONAL;

		// �g�U��
		LightWk[no].Lightstatus.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ����
		LightWk[no].Lightstatus.Ambient = D3DXCOLOR(0.8f,0.8f,0.8f, 1.0f);

		// ���C�g�̕����̐ݒ�
		LightWk[0].Lightvec = D3DXVECTOR3(0.20f, 0.60f, 0.80f);
		LightWk[1].Lightvec = D3DXVECTOR3(-0.20f, -0.60f, 0.80f);
		LightWk[2].Lightvec = D3DXVECTOR3(0.60f, 0.20f, 0.80f);
		LightWk[3].Lightvec = D3DXVECTOR3(-0.60f, -0.20f, -0.80f);
		LightWk[4].Lightvec = D3DXVECTOR3(0.20f, 0.60f, 0.80f);
		LightWk[5].Lightvec = D3DXVECTOR3(0.20f, 0.60f, -0.80f);
		LightWk[6].Lightvec = D3DXVECTOR3(-0.20f, 0.60f, 0.80f);
		LightWk[7].Lightvec = D3DXVECTOR3(-0.20f, 0.60f, -0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&LightWk[no].Lightstatus.Direction, &LightWk[no].Lightvec);

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(no, &LightWk[no].Lightstatus);

		// ���C�g�̐ݒ�
		pDevice->LightEnable(no, TRUE);

	}

	// �_�����ݒ�
	// �|�C���g���C�g
	for (int no = LIGHT_MAX; no < LIGHT_MAX + ENEMYMAX; no++)
	{
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&LightWk[no], sizeof(D3DLIGHT9));

		// ���C�g�̃^�C�v�̐ݒ�
		LightWk[no].Lightstatus.Type = D3DLIGHT_POINT;

		// �g�U��
		LightWk[no].Lightstatus.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���؂����
		LightWk[no].Lightstatus.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ����
		LightWk[no].Lightstatus.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

		// �ʒu
		LightWk[no].Lightstatus.Position = D3DXVECTOR3(0.0f, 40.0f, 0.0f);
		
		// ����
		LightWk[no].Lightstatus.Attenuation0 = 1.0f;
		LightWk[no].Lightstatus.Attenuation1 = 0.0f;
		LightWk[no].Lightstatus.Attenuation2 = 0.0f;
		LightWk[no].Lightstatus.Range = 1000.0f;

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(no, &LightWk[no].Lightstatus);

		// ���C�g�̐ݒ�
		pDevice->LightEnable(no, TRUE);

	}

	// �X�|�b�g���C�g�ݒ�
	// �_�����ݒ�
	for (int no = LIGHT_MAX + ENEMYMAX; no < LIGHT_MAX + ENEMYMAX + SPOT_MAX; no++)
	{
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&LightWk[no], sizeof(D3DLIGHT9));

		// ���C�g�̃^�C�v�̐ݒ�
		LightWk[no].Lightstatus.Type = D3DLIGHT_SPOT;

		// �g�U��
		LightWk[no].Lightstatus.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���؂����
		LightWk[no].Lightstatus.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ����
		LightWk[no].Lightstatus.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

		// �ʒu
		LightWk[no].Lightstatus.Position = D3DXVECTOR3(0.0f, 40.0f, 40.0f);

		// ���̕���
		LightWk[no].Lightstatus.Direction = D3DXVECTOR3(0.20f, 0.60f, -0.80f);

		// ����
		LightWk[no].Lightstatus.Attenuation0 = 1.0f;
		LightWk[no].Lightstatus.Attenuation1 = 0.0f;
		LightWk[no].Lightstatus.Attenuation2 = 0.0f;
		LightWk[no].Lightstatus.Range = 10.0f;

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(no, &LightWk[no].Lightstatus);

		// ���C�g�̐ݒ�
		pDevice->LightEnable(no, TRUE);

	}


	// ���C�e�B���O���[�h
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// �֐���:	void UpdateLiht(void)
// ����:	�Ȃ�
// ����:	���C�g�̍X�V����(�I���I�t)
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �f�B���N���Ȃ郉�C�g�@0�`3���I�t
	if (GetKeyboardTrigger(DIK_1))
	{
		if (Directional_switch[0] == false)
		{
			pDevice->LightEnable(0, FALSE);
			Directional_switch[0] = true;
		}
		else
		{
			pDevice->LightEnable(0, TRUE);
			Directional_switch[0] = false;
		}

		if (Directional_switch[1] == false)
		{
			pDevice->LightEnable(1, FALSE);
			Directional_switch[1] = true;
		}
		else
		{
			pDevice->LightEnable(1, TRUE);
			Directional_switch[1] = false;
		}

		//2

		if (Directional_switch[2] == false)
		{
			pDevice->LightEnable(2, FALSE);
			Directional_switch[2] = true;
		}
		else
		{
			pDevice->LightEnable(2, TRUE);
			Directional_switch[2] = false;
		}

		// 3
		if (Directional_switch[3] == false)
		{
			pDevice->LightEnable(3, FALSE);
			Directional_switch[3] = true;
		}
		else
		{
			pDevice->LightEnable(3, TRUE);
			Directional_switch[3] = false;
		}
	}


	// �f�B���N�V���i�����C�g�@4�`7���I�t
	if (GetKeyboardTrigger(DIK_2))
	{

		if (Directional_switch[4] == false)
		{
			pDevice->LightEnable(4, FALSE);
			Directional_switch[4] = true;
		}
		else
		{
			pDevice->LightEnable(4, TRUE);
			Directional_switch[4] = false;
		}

		if (Directional_switch[5] == false)
		{
			pDevice->LightEnable(5, FALSE);
			Directional_switch[5] = true;
		}
		else
		{
			pDevice->LightEnable(5, TRUE);
			Directional_switch[5] = false;
		}

		if (Directional_switch[6] == false)
		{
			pDevice->LightEnable(6, FALSE);
			Directional_switch[6] = true;
		}
		else
		{
			pDevice->LightEnable(6, TRUE);
			Directional_switch[6] = false;
		}

		//7

		if (Directional_switch[7] == false)
		{
			pDevice->LightEnable(7, FALSE);
			Directional_switch[7] = true;
		}
		else
		{
			pDevice->LightEnable(7, TRUE);
			Directional_switch[7] = false;
		}

	}


	// �X�|�b�g���C�g���I���I�t
	if (GetKeyboardTrigger(DIK_3))
	{
		for (int no = LIGHT_MAX + ENEMYMAX; no < LIGHT_MAX + ENEMYMAX + SPOT_MAX; no++)
		{
			if (Spot_switch[no] == false)
			{
				pDevice->LightEnable(no, TRUE);
				Spot_switch[no] = true;
			}
			else
			{
				pDevice->LightEnable(no, FALSE);
				Spot_switch[no] = false;
			}
		}
	}

	// �|�C���g���C�g���I���I�t
	if (GetKeyboardTrigger(DIK_4))
	{
		for (int no = LIGHT_MAX; no < LIGHT_MAX + ENEMYMAX; no++)
		{
			if (Point_switch[no] == false)
			{
				pDevice->LightEnable(no, TRUE);
				Point_switch[no] = true;
			}
			else
			{
				pDevice->LightEnable(no, FALSE);
				Point_switch[no] = false;
			}
		}
	}
}
