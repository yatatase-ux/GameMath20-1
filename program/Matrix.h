#pragma once

//---------------------------------------------------------------------------------
//	s—ñ
//---------------------------------------------------------------------------------
struct Matrix
{
public:
	float	m[4][4];

	Matrix();
	Matrix( float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33 );

	MATRIX MGet();
};

//	’PˆÊs—ñ‚ğ•Ô‚·
Matrix GetMatrixIdentity();
//	‚w²‰ñ“]s—ñ‚ğ•Ô‚·
Matrix GetMatrixRotX( float rot );
//	‚x²‰ñ“]s—ñ‚ğ•Ô‚·
Matrix GetMatrixRotY( float rot );
//	‚y²‰ñ“]s—ñ‚ğ•Ô‚·
Matrix GetMatrixRotZ( float rot );
//	‚Q‚Â‚Ìs—ñ‚ğ‡¬‚µ‚½‚à‚Ì•Ô‚·
Matrix GetMatrixMultiply( Matrix In1, Matrix In2 );
//	Float3 ‚ğs—ñ•ÏŠ·‚µ‚½ Float3 ‚ğ•Ô‚·
Float3 GetFloat3VTransform( Float3 v, Matrix mat );
