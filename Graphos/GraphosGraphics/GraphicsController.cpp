#include "StdAfx.h"
#include "GraphicsController.h"

using namespace Graphos::Content;
using namespace Graphos::Graphics;

bool GraphicsController::Initialize( void )
{
	if( !WindowController::Get().Initialize() )
		return false;

	if( !ShaderController::Get().Initialize() )
		return false;

	return true;
}

void GraphicsController::Resize( bool fullScreen, unsigned int newWidth, unsigned int newHeight )
{
	WindowController::Get().Resize( fullScreen, newWidth, newHeight );
	//OpenGLController::Get().Resize( newWidth, newHeight );
}

void GraphicsController::Resize( void )
{
	WindowController::Get().Resize(
		ConfigController::Get().GetData<bool>( "display/fullscreen" ),
		ConfigController::Get().GetData<unsigned int>( "display/width" ),
		ConfigController::Get().GetData<unsigned int>( "display/height" ) );
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