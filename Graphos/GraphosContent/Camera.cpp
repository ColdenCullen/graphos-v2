#include "Camera.h"

using namespace Graphos;
using namespace Graphos::Content;

Camera::Camera( GameObject* owner ) : Ingredient( owner ) { }

bool Camera::Update( float deltaTime )
{
	Vector3 up( 0.0f, 1.0f, 0.0f );
	Vector3 lookAt( 0.0f, 0.0f, 1.0f );

	up = owner->transform.RotationMatrix() * up;
	lookAt = owner->transform.RotationMatrix() * lookAt;

	//up += owner->transform.Position();
	lookAt += owner->transform.Position();

	UpdateViewMatrix( lookAt, up );

	return true;
}

void Camera::Draw( void )
{
	ShaderController::Get().SetAllShadersUniform( "cameraMatrix", viewMatrix );
}

void Camera::Shutdown( void )
{

}

void Camera::UpdateViewMatrix( Vector3& lookAt, Vector3& up )
{
	Vector3 xAxis, yAxis, zAxis;
	float length, result1, result2, result3;
	Vector3 position = owner->transform.Position();

	// zAxis = normal( lookAt - position )
	zAxis.x = lookAt.x - position.x;
	zAxis.y = lookAt.y - position.y;
	zAxis.z = lookAt.z - position.z;
	length = sqrt( ( zAxis.x * zAxis.x ) + ( zAxis.y * zAxis.y ) + ( zAxis.z * zAxis.z ) );
	zAxis.x /= length;
	zAxis.y /= length;
	zAxis.z /= length;

	// xAxis = normal(cross(up, zAxis))
	xAxis.x = ( up.y * zAxis.z) - (up.z * zAxis.y );
	xAxis.y = ( up.z * zAxis.x) - (up.x * zAxis.z );
	xAxis.z = ( up.x * zAxis.y) - (up.y * zAxis.x );
	length = sqrt( ( xAxis.x * xAxis.x ) + ( xAxis.y * xAxis.y ) + ( xAxis.z * xAxis.z ) );
	xAxis.x /= length;
	xAxis.y /= length;
	xAxis.z /= length;

	// yAxis = cross(zAxis, xAxis)
	yAxis.x = ( zAxis.y * xAxis.z ) - ( zAxis.z * xAxis.y );
	yAxis.y = ( zAxis.z * xAxis.x ) - ( zAxis.x * xAxis.z );
	yAxis.z = ( zAxis.x * xAxis.y ) - ( zAxis.y * xAxis.x );

	// -dot( xAxis, position )
	result1 = ( ( xAxis.x * position.x ) + ( xAxis.y * position.y ) + ( xAxis.z * position.z ) ) * -1.0f;

	// -dot( yAxis, eye )
	result2 = ( ( yAxis.x * position.x ) + ( yAxis.y * position.y ) + ( yAxis.z * position.z ) ) * -1.0f;

	// -dot( zAxis, eye )
	result3 = ( ( zAxis.x * position.x ) + ( zAxis.y * position.y ) + ( zAxis.z * position.z ) ) * -1.0f;

	// Set the computed values in the matrix
	viewMatrix.dataArray[ 0 ] = xAxis.x;
	viewMatrix.dataArray[ 1 ] = yAxis.x;
	viewMatrix.dataArray[ 2 ] = zAxis.x;
	viewMatrix.dataArray[ 3 ] = 0.0f;

	viewMatrix.dataArray[ 4 ] = xAxis.y;
	viewMatrix.dataArray[ 5 ] = yAxis.y;
	viewMatrix.dataArray[ 6 ] = zAxis.y;
	viewMatrix.dataArray[ 7 ] = 0.0f;

	viewMatrix.dataArray[ 8 ] = xAxis.z;
	viewMatrix.dataArray[ 9 ] = yAxis.z;
	viewMatrix.dataArray[ 10 ] = zAxis.z;
	viewMatrix.dataArray[ 11 ] = 0.0f;

	viewMatrix.dataArray[ 12 ] = result1;
	viewMatrix.dataArray[ 13 ] = result2;
	viewMatrix.dataArray[ 14 ] = result3;
	viewMatrix.dataArray[ 15 ] = 1.0f;
}