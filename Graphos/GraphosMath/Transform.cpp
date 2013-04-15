#include "Transform.h"

using namespace Graphos::Math;

Transform::Transform( void ) : parent( nullptr ), matrix( Matrix4::Identity ), scale( Vector3( 1.0f, 1.0f, 1.0f ) ) { }

void Transform::Rotate( Quaternion rotation )
{
	Rotate( rotation.x, rotation.y, rotation.z, rotation.w );
}

void Transform::Rotate( const float x, const float y, const float z )
{
	Vector3 oldCoord = position;

	Translate( -oldCoord.x, -oldCoord.y, -oldCoord.z );

	if( x != 0.0f ) RotateX( x * M_PI / 180 );
	if( y != 0.0f ) RotateY( y * M_PI / 180 );
	if( z != 0.0f ) RotateZ( z * M_PI / 180 );

	Translate( oldCoord.x, oldCoord.y, oldCoord.z );
}

void Transform::Rotate( const float x, const float y, const float z, const float angle )
{
	Vector3 oldCoord = position;

	Translate( -oldCoord.x, -oldCoord.y, -oldCoord.z );

	//TODO: Make better
	if( x != 0.0f ) RotateX( x * M_PI / 180 );
	if( y != 0.0f ) RotateY( y * M_PI / 180 );
	if( z != 0.0f ) RotateZ( z * M_PI / 180 );

	Translate( oldCoord.x, oldCoord.y, oldCoord.z );
}

void Transform::Translate( const float x, const float y, const float z )
{
	Matrix4 translateMatrix = Matrix4::Identity;

	translateMatrix.Set( 0, 3, x );
	translateMatrix.Set( 1, 3, y );
	translateMatrix.Set( 2, 3, z );

	position.x += x;
	position.y += y;
	position.z += z;

	matrix *= translateMatrix;
}

void Transform::Scale( const float x, const float y, const float z )
{
	Matrix4 scaleMatrix = Matrix4::Identity;

	scaleMatrix.Set( 0, 0, x );
	scaleMatrix.Set( 1, 1, y );
	scaleMatrix.Set( 2, 2, z );

	matrix *= scaleMatrix;

	scale.x *= x;
	scale.y *= y;
	scale.z *= z;
}

void Transform::RotateX( const float angle )
{
	Matrix4 newTrans = Matrix4::Identity;

	newTrans.Set( 1, 1, cos( angle ) );
	newTrans.Set( 2, 1, -sin( angle ) );
	newTrans.Set( 1, 2, sin( angle ) );
	newTrans.Set( 2, 2, cos( angle ) );

	matrix *= newTrans;

	rotation.x += angle;
}

void Transform::RotateY( const float angle )
{
	Matrix4 newTrans = Matrix4::Identity;

	newTrans.Set( 0, 0, cos( angle ) );
	newTrans.Set( 2, 0, -sin( angle ) );
	newTrans.Set( 0, 2, sin( angle ) );
	newTrans.Set( 2, 2, cos( angle ) );

	matrix *= newTrans;

	rotation.y += angle;
}

void Transform::RotateZ( const float angle )
{
	Matrix4 newTrans = Matrix4::Identity;

	newTrans.Set( 0, 0, cos( angle ) );
	newTrans.Set( 1, 0, -sin( angle ) );
	newTrans.Set( 0, 1, sin( angle ) );
	newTrans.Set( 1, 1, cos( angle ) );

	matrix *= newTrans;

	rotation.z += angle;
}