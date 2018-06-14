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
#define LIGHT_MAX	(8)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
GAMELIGHT LightWk[LIGHT_MAX];				// ���C�g�̃��[�N

//=============================================================================
// ���C�g�̏���������
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



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
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
}
