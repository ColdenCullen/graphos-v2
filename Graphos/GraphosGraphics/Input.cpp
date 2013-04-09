#include "stdafx.h"
#include "Input.h"

#include <stdio.h>

using namespace Graphos::Math;
using namespace Graphos::Graphics;

Input::Input( void )
{
	// Initialize array
	for( int ii = 0; ii < 256; ii++ )
	{
		keys[ ii ] = false;
		prevState[ ii ] = false;
	}
}

// Called when keys are down
void Input::KeyDown( unsigned int input )
{
	keys[ input ] = true;
}

// Called when keys are up
void Input::KeyUp( unsigned int input )
{
	keys[ input ] = false;
}

// Is key down?
bool Input::IsKeyDown( unsigned int input, const bool checkPrevious )
{
	bool result = keys[ input ] && ( !checkPrevious || !prevState[ input ] );

	prevState[ input ] = keys[ input ];

	return result;
}

Point Input::GetMousePos( Transform& camera, float zPlane ) const
{
	/*
#ifdef _WIN32
	Win32Controller& wc = WindowController::Get();

	const float ASPECT_FACTOR = ( zPlane - camera.position.z ) * .825f / wc.GetHeight();

	POINT i;
	GetCursorPos( &i );
	ScreenToClient( wc.GetHWnd(), &i );

	Point p( i.x, i.y );

	p.x -= wc.GetWidth() / 2;
	p.y -= wc.GetHeight() / 2;

	p.x *= ASPECT_FACTOR;
	p.y *= -ASPECT_FACTOR;

	p.x += camera.position.x;
	p.y += camera.position.y;

	return p;
#endif
	*/

	return Point( 0.0f, 0.0f );
}