#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Player.h"

//	プレイヤーの移動スピード
#define PLAYER_MOV_SPEED	0.1f
//	プレイヤーの回転スピード
#define PLAYER_ROT_SPEED	1.0f
//	プレイヤーの上下回転の範囲
#define PLAYER_ROT_X_MAX	30.0f
//	プレイヤーの高さの範囲
#define PLAYER_POS_Y_MIN	1.0f
#define PLAYER_POS_Y_MAX	3.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;
	//	Ｙ座標は少し上にしています
	m_pos.Set( 0.0f, 1.5f, -5.0f );
	//	向きは全部０度で開始
	m_rot.Clear();
	//	行列の初期化
	m_mat = MGetIdent();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	左右キーで向きの変更
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		//	右キーを押している時は右を向かせたいのでＹ軸回転はプラス
		m_rot.y += PLAYER_ROT_SPEED;
		//	Ｚ軸回転は右に傾けたいのでマイナス方向
		m_rot.z -= PLAYER_ROT_SPEED;
	}else if( CheckHitKey( KEY_INPUT_LEFT ) ){
		//	左キーを押している時は左を向かせたいのでＹ軸回転はマイナス
		m_rot.y -= PLAYER_ROT_SPEED;
		//	Ｚ軸回転は左に傾けたいのでプラス方向
		m_rot.z += PLAYER_ROT_SPEED;
	}else{
		//	じゃないとき（左右キーを押していない）Ｚ軸の角度を 0.0f に近づける
		m_rot.z *= 0.9f;
	}

	//	Ｚ軸の回転角度を -30.0f ～ 30.0f にします
	m_rot.z = clamp( m_rot.z, -30.0f, 30.0f );

	//	発展課題：上下キーで上下の向きの変更
	//	（ＤＸライブラリのＸ軸回転はプラスで下向きになるので、上はマイナス）
	if( CheckHitKey( KEY_INPUT_UP ) && m_pos.y < PLAYER_POS_Y_MAX ){
		//	上キーを押している時（まだ上に行ける時）は上を向かせる
		m_rot.x -= PLAYER_ROT_SPEED;
	}else if( CheckHitKey( KEY_INPUT_DOWN ) && m_pos.y > PLAYER_POS_Y_MIN ){
		//	下キーを押している時（まだ下に行ける時）は下を向かせる
		m_rot.x += PLAYER_ROT_SPEED;
	}else{
		//	キーを離した時や範囲まで行った時はＸ軸の角度を 0.0f に近づける
		m_rot.x *= 0.9f;
	}
	//	Ｘ軸の回転角度を -30.0f ～ 30.0f にします
	m_rot.x = clamp( m_rot.x, -PLAYER_ROT_X_MAX, PLAYER_ROT_X_MAX );

	//	それぞれの軸の回転角度が決まったのでそれに合わせた回転行列を作成
	//	Ｙ軸の回転行列
	MATRIX mat_y = MGetRotY( TO_RADIAN( m_rot.y ) );
	//	Ｘ軸の回転行列
	MATRIX mat_x = MGetRotX( TO_RADIAN( m_rot.x ) );
	//	Ｚ軸の回転行列
	MATRIX mat_z = MGetRotZ( TO_RADIAN( m_rot.z ) );
	//	この３つの行列を１個にします（Ｚ軸 → Ｘ軸 → Ｙ軸の順番で回転）
	m_mat = MMult( MMult( mat_z, mat_x ), mat_y );

	//	向いている方向に移動（常に移動し続ける）
	Float3 base( 0.0f, 0.0f, PLAYER_MOV_SPEED );		//	基準のベクトル（回転していない時の移動ベクトル）
//	MATRIX mat = MGetRotY( TO_RADIAN( m_rot.y ) );		//	Ｙ軸回転行列
	Float3 mov = GetFloat3VTransform( base, m_mat );	//	変換したベクトルを移動ベクトルとして
	m_pos += mov;										//	座標移動

	//	高さを 1.0f ～ 3.0f の範囲にします
	m_pos.y = clamp( m_pos.y, PLAYER_POS_Y_MIN, PLAYER_POS_Y_MAX );
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Player::Render()
{
	//	プレイヤーモデルの描画
	//	モデルの座標設定
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	//	モデルの向きの設定（回転の順番が決まっているので、今回の回転だとうまくいかない）
//	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	//	今回はこちらで用意した行列を使ってモデルの回転をさせます
	MV1SetRotationMatrix( m_model, m_mat );
	//	モデルの描画
	MV1DrawModel( m_model );

	//	プレイヤーが浮いているように見せるために地面のところに影っぽい半透明の円を描画
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 100 );				//	半透明の設定
	Float3 pos = m_pos;											//	プレイヤー座標の
	pos.y = 0.01f;												//	下の地面の少しだけ上の所
	DrawCircle3D_XZ( pos, 0.5f, GetColor( 0, 0, 0 ), true );	//	そこの場所に黒い円の描画
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );				//	描画設定を元に戻す
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
