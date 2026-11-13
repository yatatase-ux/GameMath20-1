#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	カメラクラス
//---------------------------------------------------------------------------------
class Camera
{
public:
	//	カメラ座標
	Float3		m_pos;
	//	カメラの向き
	Float3		m_rot;

	void Init();		//	初期化処理
	void Update( Float3 target_pos, Float3 target_rot );		//	更新処理（プレイヤーの座標と向きをもらう）
	void Setting();		//	描画前のカメラ設定
	void Exit();		//	終了処理
};
