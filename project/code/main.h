//*****************************************************
//
// メイン処理[main.h]
// Author:��山桃也
//
//*****************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************
// インクルード
//*****************************************************
#include "universal.h"
#include "debug.h"

//*****************************************************
// ライブラリ
//*****************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//*****************************************************
//マクロ定義
//*****************************************************
#ifdef _DEBUG
#define SCREEN_WIDTH			(1280)									// ウィンドウの幅
#define SCREEN_HEIGHT			(720)									// ウィンドウの高さ
#else
#define SCREEN_WIDTH			(1280)									// ウィンドウの幅
#define SCREEN_HEIGHT			(720)									// ウィンドウの高さ
#endif
#define SCRN_MID (D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f))	// 画面中心
#define FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// 頂点フォーマット設定
#define FVF_VERTEX_3D			(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEX2)		//頂点フォーマット設定
#define NUM_PLAYER (4)	// プレイヤーの最大数
#define MAX_STRING (256)	// 文字数の最大
#define CLASS_NAME				"WindowClass"					// ウィンドウクラスの名前
#define WINDOW_NAME				"サンタさんのあとしまつ"		// ウィンドウの名前(キャプション)
#define COLOR_CLEAR (D3DCOLOR_RGBA(0, 0, 0, 255))	// 画面クリア色

//*****************************************************
// 定数定義
//*****************************************************
namespace
{

}

//*****************************************************
// 構造体定義
//*****************************************************
typedef struct
{// 2Dの頂点情報
	D3DXVECTOR3 pos;			//頂点座標
	float rhw;					//座標変換用係数（１．０ｆで固定）
	D3DCOLOR col;				//頂点カラー
	D3DXVECTOR2 tex;			//テクスチャ座標
}VERTEX_2D;

typedef struct
{// 3Dの頂点情報
	D3DXVECTOR3 pos;			//頂点座標
	D3DXVECTOR3 nor;			//法線ベクトル
	D3DCOLOR col;				//頂点カラー
	D3DXVECTOR2 tex;			//テクスチャ座標
	D3DXVECTOR2 tex2;			//テクスチャ座標2
}VERTEX_3D;

//*****************************************************
// プロトタイプ宣言
//*****************************************************
int GetFPS(void);

#endif