#include "stdafx.h"
#include "WindowController.hpp"

using namespace Graphos::Math;
using namespace Graphos::Content;
using namespace Graphos::Graphics;

bool Win32Controller::Initialize( void )
{
	fullScreen	= SettingsController::Get().GetData<bool>( "display/fullscreen" );
	width		= SettingsController::Get().GetData<unsigned int>( "display/width" );
	height		= SettingsController::Get().GetData<unsigned int>( "display/height" );

	if( !fullScreen && ( width <= 0 || height <= 0 ) )
		return false;

	unsigned int screenWidth = GetSystemMetrics( SM_CXSCREEN );
	unsigned int screenHeight = GetSystemMetrics( SM_CYSCREEN );

	unsigned int formatCount;
	int pixelFormat[1];
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;

	hInstance = GetModuleHandle( NULL );

	// Initialize global strings
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof( WNDCLASSEX );
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= &Win32Controller::WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAPHOSGRAPHICS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"Graphos";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx( &wcex );

	// Adjust for full screen
	this->fullScreen = fullScreen;
	if( fullScreen )
	{
		this->width = screenWidth;
		this->height = screenHeight;
	}
	else
	{
		this->width = width;
		this->height = height;
	}

	// Perform application initialization:
	hWnd = CreateWindow( L"Graphos", L"Graphos", fullScreen ? WS_POPUP : WS_OVERLAPPED | WS_SYSMENU,
		( screenWidth - this->width ) / 2, ( screenHeight - this->height ) / 2, this->width, this->height,
		NULL, NULL, hInstance, NULL );
	if( !hWnd )
		return false;

	ShowWindow( hWnd, SW_HIDE );

	// Get device context
	deviceContext = GetDC( hWnd );
	if( !deviceContext )
		return false;

	// Set the pixel format
	if( !SetPixelFormat( deviceContext, 1, &pixelFormatDescriptor ) )
		return false;

	renderContext = wglCreateContext( deviceContext );
	if( !renderContext )
		return false;

	if( !wglMakeCurrent( deviceContext, renderContext ) )
		return false;

	glewExperimental = GL_TRUE;
	GLenum result = glewInit();

	// Delete temp window
	Shutdown();

	// Create new permanent window
	hWnd = CreateWindow( L"Graphos", L"Graphos", fullScreen ? WS_POPUP : WS_OVERLAPPED | WS_SYSMENU,
		( screenWidth - this->width ) / 2, ( screenHeight - this->height ) / 2, this->width, this->height,
		NULL, NULL, hInstance, NULL );
	if( !hWnd )
		return false;

	// Set attributes list
	int attributeList[ 19 ] = {
		WGL_SUPPORT_OPENGL_ARB, TRUE,							// Support for OpenGL rendering
		WGL_DRAW_TO_WINDOW_ARB, TRUE,							// Support for rendering window
		WGL_ACCELERATION_ARB,	WGL_FULL_ACCELERATION_ARB,		// Support for hardware acceleration
		WGL_COLOR_BITS_ARB,		24,								// Support for 24bit color
		WGL_DEPTH_BITS_ARB,		24,								// Support for 24bit depth buffer
		WGL_DOUBLE_BUFFER_ARB,	TRUE,							// Support for double buffer
		WGL_SWAP_METHOD_ARB,	WGL_SWAP_EXCHANGE_ARB,			// Support for swapping buffers
		WGL_PIXEL_TYPE_ARB,		WGL_TYPE_RGBA_ARB,				// Support for RGBA pixel type
		WGL_STENCIL_BITS_ARB,	8,								// Support for 8 bit stencil buffer
		0														// Null terminate
	};

	// Set version to 4.0
	int versionInfo[ 5 ] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 0,
		0
	};

	// Get new Device Context
	deviceContext = GetDC( hWnd );
	if( !deviceContext )
		return false;

	// Query pixel format
	if( wglChoosePixelFormatARB( deviceContext, attributeList, NULL, 1, pixelFormat, &formatCount ) == -1 )
		return false;

	// Set the pixel format
	if( SetPixelFormat( deviceContext, *pixelFormat, &pixelFormatDescriptor ) == -1 )
		return false;

	// Create OpenGL rendering context
	renderContext = wglCreateContextAttribsARB( deviceContext, NULL, versionInfo );
	if( !renderContext )
		return false;

	// Set current context
	if( !wglMakeCurrent( deviceContext, renderContext ) )
		return false;

	// Set depth buffer
	glClearDepth( 1.0f );

	// Enable depth testing
	glEnable( GL_DEPTH_TEST );

	// Set front face
	glFrontFace( GL_CCW );

	// Enable back face culling
	if( BACKFACE_CULLING )
	{
		glEnable( GL_CULL_FACE );
		glCullFace( GL_BACK );
	}

	Resize( fullScreen, width, height );

	ShowWindow( hWnd, SW_NORMAL );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	return true;
}

void Win32Controller::Shutdown( void )
{
	// Release contexts
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( renderContext );
	renderContext = NULL;
	ReleaseDC( hWnd, deviceContext );
	deviceContext = NULL;

	if( IsWindow( hWnd ) )
	{
		DestroyWindow( hWnd );
		hWnd = NULL;
	}
}

void Win32Controller::Resize( bool fullScreen, unsigned int newWidth, unsigned int newHeight )
{
	if( !fullScreen && ( newWidth <= 0 || newHeight <= 0 ) )
		return;
	
	this->fullScreen = fullScreen;
	if( fullScreen )
	{
		width = GetSystemMetrics( SM_CXSCREEN );
		height = GetSystemMetrics( SM_CYSCREEN );
	}
	else
	{
		width = newWidth;
		height = newHeight;
	}

	SetWindowPos( hWnd, NULL, 0, 0, newWidth, newHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );

	perspectiveMatrix = Matrix4::BuildPerspective( (float)M_PI / 4.0f, (float)newWidth / (float)newHeight, 0.001f, 1000.0f );
}

void Win32Controller::MessageLoop( void )
{
	MSG msg;

	// Initialize the message structure.
	ZeroMemory( &msg, sizeof(MSG) );

	// Handle the windows messages.
	while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_DESTROY	- post a quit message and return
//
LRESULT CALLBACK Win32Controller::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
	case WM_CLOSE:
	case WM_DESTROY:
	case WM_QUIT:
		PostQuitMessage( 0 );
		break;
		// If key down, send it to input
	case WM_KEYDOWN:
		Input::Get().KeyDown( (unsigned int)wParam );
		return 0;
		// If key up, send it to input
	case WM_KEYUP:
		Input::Get().KeyUp( (unsigned int)wParam );
		return 0;
		// On Mouse Event
	case WM_RBUTTONDOWN:
		Input::Get().KeyDown( VK_RBUTTON );
		return 0;
		// On Mouse Event
	case WM_RBUTTONUP:
		Input::Get().KeyUp( VK_RBUTTON );
		return 0;
		// On Mouse Event
	case WM_LBUTTONDOWN:
		Input::Get().KeyDown( VK_LBUTTON );
		return 0;
		// On Mouse Event
	case WM_LBUTTONUP:
		Input::Get().KeyUp( VK_LBUTTON );
		return 0;
		// If no change, send to default windows handler
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return 0;
}