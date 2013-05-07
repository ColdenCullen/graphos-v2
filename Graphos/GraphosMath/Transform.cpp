#include "Transform.h"

using namespace Graphos::Math;

Transform::Transform( void ) : parent( nullptr ), matrix( Matrix::Identity ), scale( Vector3( 1.0f, 1.0f, 1.0f ) ) { }

void Transform::Rotate( Quaternion rotation )
{
	Rotate( rotation.x, rotation.y, rotation.z, rotation.w );

	//matrix *= rotation.ToRotationMatrix();
}

void Transform::Rotate( const float x, const float y, const float z, const float angle )
{
	Vector3 oldCoord = position;

	Translate( -oldCoord.x, -oldCoord.y, -oldCoord.z );

	//TODO: Make better
	if( z != 0.0f ) RotateZ( z * M_PI / 180 );
	if( x != 0.0f ) RotateX( x * M_PI / 180 );
	if( y != 0.0f ) RotateY( y * M_PI / 180 );

	Translate( oldCoord.x, oldCoord.y, oldCoord.z );
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

void Transform::Rotate( const Vector3& eulerAngles )
{
	Rotate( eulerAngles.x, eulerAngles.y, eulerAngles.z );
}

void Transform::Translate( const float x, const float y, const float z )
{
	Matrix translateMatrix = Matrix::Identity;

	/*
	translateMatrix.matrix[ 0 ][ 3 ] = x;
	translateMatrix.matrix[ 1 ][ 3 ] = y;
	translateMatrix.matrix[ 2 ][ 3 ] = z;
	/*/
	translateMatrix.matrix[ 3 ][ 0 ] = x;
	translateMatrix.matrix[ 3 ][ 1 ] = y;
	translateMatrix.matrix[ 3 ][ 2 ] = z;
	//*/

	position.x += x;
	position.y += y;
	position.z += z;

	matrix *= translateMatrix;
}

void Transform::Translate( const Vector3& displacement )
{
	Translate( displacement.x, displacement.y, displacement.z );
}

void Transform::Scale( const float x, const float y, const float z )
{
	Matrix scaleMatrix = Matrix::Identity;

	scaleMatrix.matrix[ 0 ][ 0 ] = x;
	scaleMatrix.matrix[ 1 ][ 1 ] = y;
	scaleMatrix.matrix[ 2 ][ 2 ] = z;

	matrix *= scaleMatrix;

	scale.x *= x;
	scale.y *= y;
	scale.z *= z;
}

void Transform::Scale( const Vector3& scale )
{
	Scale( scale.x, scale.y, scale.z );
}

void Transform::RotateX( const float angle )
{
	Matrix newTrans = Matrix::Identity;

	/*
	newTrans.matrix[ 1 ][ 1 ] = cos( angle );
	newTrans.matrix[ 2 ][ 1 ] = -sin( angle );
	newTrans.matrix[ 1 ][ 2 ] = sin( angle );
	newTrans.matrix[ 2 ][ 2 ] = cos( angle );
	/*/
	newTrans.matrix[ 1 ][ 1 ] = cos( angle );
	newTrans.matrix[ 1 ][ 2 ] = -sin( angle );
	newTrans.matrix[ 2 ][ 1 ] = sin( angle );
	newTrans.matrix[ 2 ][ 2 ] = cos( angle );
	//*/
	matrix *= newTrans;

	rotation.x += angle;
}

void Transform::RotateY( const float angle )
{
	Matrix newTrans = Matrix::Identity;

	/*
	newTrans.matrix[ 0 ][ 0 ] = cos( angle );
	newTrans.matrix[ 2 ][ 0 ] = -sin( angle );
	newTrans.matrix[ 0 ][ 2 ] = sin( angle );
	newTrans.matrix[ 2 ][ 2 ] = cos( angle );
	/*/
	newTrans.matrix[ 0 ][ 0 ] = cos( angle );
	newTrans.matrix[ 0 ][ 2 ] = -sin( angle );
	newTrans.matrix[ 2 ][ 0 ] = sin( angle );
	newTrans.matrix[ 2 ][ 2 ] = cos( angle );
	//*/
	matrix *= newTrans;

	rotation.y += angle;
}

void Transform::RotateZ( const float angle )
{
	Matrix newTrans = Matrix::Identity;

	/*
	newTrans.matrix[ 0 ][ 0 ] = cos( angle );
	newTrans.matrix[ 1 ][ 0 ] = -sin( angle );
	newTrans.matrix[ 0 ][ 1 ] = sin( angle );
	newTrans.matrix[ 1 ][ 1 ] = cos( angle );
	/*/
	newTrans.matrix[ 0 ][ 0 ] = cos( angle );
	newTrans.matrix[ 0 ][ 1 ] = -sin( angle );
	newTrans.matrix[ 1 ][ 0 ] = sin( angle );
	newTrans.matrix[ 1 ][ 1 ] = cos( angle );
	//*/

	matrix *= newTrans;

	rotation.z += angle;
}

const Matrix Transform::WorldMatrix() const
{
	if( parent != nullptr ) return parent->WorldMatrix() * matrix;
	else					return matrix;
}