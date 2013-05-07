#include "Camera.h"

using namespace Graphos;
using namespace Graphos::Content;

Camera::Camera( GameObject* owner ) : Ingredient( owner )
{

}

bool Camera::Update( void )
{
	return true;
}

void Camera::Draw( void )
{
	ShaderController::Get().SetAllShadersUniform( "cameraMatrix", viewMatrix );
}

void Camera::Shutdown( void )
{

}
