//=============================================================================
//
// ���C�t�`�揈�� [modellife.h]
//  Author : HAL�Q�[���w�ȓ�N���ے�1�N�@�R�{�s��
//
//=============================================================================
#ifndef _LMODELLIFE_H_
#define _LMODELLIFE_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

// ���C�t�Q�[�W�̘g
#define	LIFEWAKU_POS_X		(20)		// ���C�t�Q�[�W�̘g�̈ʒu(X���W)
#define	LIFEWAKU_POS_Y		(20)		// ���C�t�Q�[�W�̘g�̈ʒu(Y���W)
#define	LIFEWAKU_WIDTH		(500)		// ���C�t�Q�[�W�̘g�̕�
#define	LIFEWAKU_HEIGHT		(80)		// ���C�t�Q�[�W�̘g�̍���

// ���C�t��\���Q�[�W
#define	HPGAGE_POS_X				(30)		// ���C�t�Q�[�W�̈ʒu(X���W)
#define	HPGAGE_POS_Y				(30)		// ���C�t�Q�[�W�̈ʒu(Y���W)
#define	HPGAGE_WIDTH				(470)		// ���C�t�Q�[�W�̕�
#define	HPGAGE_HEIGHT			(20)		// ���C�t�Q�[�W�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitModellife(void);
void UninitModellife(void);
void UpdateModellife(void);
void DrawModellife(void);



#endif
