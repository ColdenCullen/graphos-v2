#include "GraphosGame.h"

using namespace Graphos;

void GraphosGame::Run( void )
{
	SettingsController::Get().LoadSettings();
	GraphicsController::Get().Initialize();

	Initialize();

	bool done = false;

	// Loop until there is a quit message from the window or the user.
	while( !done )
	{
		// Platform specific program stuff
		GraphicsController::Get().MessageLoop();

		// Otherwise do the frame processing.
		if( !Update() )
		{
			done = true;
		}

		GraphicsController::Get().CallGLFunction( GraphicsController::BEGIN );

		Draw();

		GraphicsController::Get().CallGLFunction( GraphicsController::END );
	}
}