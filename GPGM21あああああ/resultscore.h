//=============================================================================
//
// �X�R�A���� [resultscore.h]
// Author : 
//
//=============================================================================
#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	int score;
}RESULTSCORE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResultscore(void);
void UninitResultscore(void);
void UpdateResultscore(void);
void DrawResultscore(void);

void ChangeResultscore(int value);

#endif
