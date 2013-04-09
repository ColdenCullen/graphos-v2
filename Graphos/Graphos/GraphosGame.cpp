#include "GraphosGame.h"

using namespace Graphos;

void GraphosGame::Run( void )
{
	// Initialize time
	clock_t cur = clock();
	clock_t prev = clock();

	if( !ConfigController::Get().LoadSettings() )
		return;

	if( !GraphicsController::Get().Initialize() )
		return;
	
	if( !Initialize() )
		return;

	bool done = false;

	// Loop until there is a quit message from the window or the user.
	while( !done )
	{
		// Platform specific program stuff
		GraphicsController::Get().MessageLoop();

		// Update time
		prev = cur;
		cur = clock();

		deltaTime = static_cast<float>( cur - prev ) / CLOCKS_PER_SEC;

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