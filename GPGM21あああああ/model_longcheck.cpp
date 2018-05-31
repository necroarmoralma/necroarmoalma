//*****************************************************************************************************
// ファイル名:	model_longcheck.cpp
// 作成日:		1月22日
// 説明:		モデルを読み込み長さを決める
//*****************************************************************************************************

//*****************************************************************************************************
// インクルードファイル
//*****************************************************************************************************
#include "model_longcheck.h"
#include "model.h"
#include "setting.h"
#include "map.h"
//*****************************************************************************************************
// マクロ定義
//*****************************************************************************************************

//*****************************************************************************************************
// 構造体定義
//*****************************************************************************************************
// 測定用のレイを飛ばす基準点
#define CHECKBASE				D3DXVECTOR3(0.0f,0.0f,0.0f)
// 測定用モデルの場所
#define CHECKMODELCENTER		"data/LENCHECKMODEL/check_modelcenter.x"
#define CHECKMODELHIGHER		"data/LENCHECKMODEL/check_modelhigher.x"
#define CHECKENEMYCENTER		"data/LENCHECKMODEL/check_enemycenter.x"
//*****************************************************************************************************
// プロトタイプ宣言
//*****************************************************************************************************
HRESULT loadmodel(void);
void GetModelLong(void);
void EndLongCheck(void);



//*****************************************************************************************************
// グローバル変数
//*****************************************************************************************************

// 測定用(こっちに追加するのを忘れない)
char *CheckModelFileName[]=				// CheckModelFileNameにカーソル合わせると要素数でる
{
	CHECKMODELCENTER,
	CHECKMODELHIGHER,
	CHECKENEMYCENTER
};

MODELCHECK		modelcheck[CHECKMODEL_MAX];

//*****************************************************************************************************
// 関数名:	void checkmodellong(void)
// 引数:	無し
// 戻り値:	無し
// 説明:	モデルの長さ決定の処理
//*****************************************************************************************************
void checkmodellong(void)
{
	loadmodel();			// 測定用のモデルを読み込み
	GetModelLong();			// 長さを図り格納
	EndLongCheck();			// 終了
}

//*****************************************************************************************************
// 関数名:	HRESULT loadmodel(void)
// 引数:	なし
// 戻り値:	なし
// 説明:	長さを図るための板ポリゴンを読み込む
//*****************************************************************************************************
HRESULT loadmodel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	
	// Xファイルの読み込み
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
// 関数名:	void GetModelLong(void)
// 引数:	なし
// 戻り値:	なし
// 説明:	原点から測定用のポリゴンへレイを飛ばして長さを図る
//			自機関連の長さはここへ
//******************************************************************************************************
void GetModelLong(void)
{
	MODEL *model = GetModel(0);
	ENEMYLENGTH *enemylength = GetEnemylength(0);
	MAP *map = GetMap(0);

	// 基準点から測定用板ポリゴンへレイを飛ばし高さを図る
	// 中心まで
	D3DXIntersect(modelcheck[MODELCENTERCHECK].MeshModelCheck, &CHECKBASE, &D3DXVECTOR3(0, 1, 0), &modelcheck[MODELCENTERCHECK].hitcheck, NULL, NULL, NULL,
		&model->center, NULL, NULL);
	
	//　てき
	D3DXIntersect(modelcheck[ENEMYLENGTHCHECK].MeshModelCheck, &CHECKBASE, &D3DXVECTOR3(0, 1, 0), &modelcheck[MODELCENTERCHECK].hitcheck, NULL, NULL, NULL,
		&enemylength->enemycenter, NULL, NULL);

	// 全長
	D3DXIntersect(modelcheck[MODELCENTERCHECK].MeshModelCheck, &CHECKBASE, &D3DXVECTOR3(0, 1, 0), &modelcheck[MODELHIGHERCHECK].hitcheck, NULL, NULL, NULL,
		&model->higher, NULL, NULL);

	// マップ測定
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
// 関数名;	void EndLongCheck(void)
// 引数:	なし
// 戻り値:	なし
// 説明:	長さの測定と格納が終わったら使わないものは開放する
//*******************************************************************************************************
void EndLongCheck(void)
{
	for (int no = 0; no < CHECKMODEL_MAX; no++)
	{
		// メッシュ開放
		if (modelcheck[no].MeshModelCheck != NULL)
		{
			modelcheck[no].MeshModelCheck->Release();
			modelcheck[no].MeshModelCheck = NULL;
		}

		// マテリアル開放
		if (modelcheck[no].BuffMatCheck != NULL)
		{
			modelcheck[no].BuffMatCheck->Release();
			modelcheck[no].BuffMatCheck = NULL;
		}
	}

	UninitMap();
}