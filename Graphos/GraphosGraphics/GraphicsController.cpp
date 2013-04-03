#include "StdAfx.h"
#include "GraphicsController.h"

using namespace Graphos::Graphics;

bool GraphicsController::Initialize( void )
{
	if( !WindowController::Get().Initialize() )
		return false;

	ShaderController::Get().Initialize();

	return true;
}

void GraphicsController::Resize( bool fullScreen, unsigned int newWidth, unsigned int newHeight )
{
	WindowController::Get().Resize( fullScreen, newWidth, newHeight );
	//OpenGLController::Get().Resize( newWidth, newHeight );
}

void GraphicsController::CallGLFunction( GLFunctions function )
{
	switch( function )
	{
	case BEGIN:
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		break;
	case END:
		SwapBuffers( WindowController::Get().GetDeviceContext() );
		break;
	}
}