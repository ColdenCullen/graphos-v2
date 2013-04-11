#include "AwesomiumView.h"

using namespace Graphos::Content;

AwesomiumView::AwesomiumView( void )
{
	// Get size values
	int width = ConfigController::Get().GetData<int>( "display.width" );
	int height = ConfigController::Get().GetData<int>( "display.height" );

	// Generate a texture to use
	glGenTextures( 1, &textureThing );

	// Initialize Awesomium
	webCore = WebCore::Initialize( WebConfig() );
	webView = webCore->CreateWebView( width, height );
	webView->LoadURL( WebURL( WSLit( "http://ColdenCullen.com" ) ) );

	// Initialize buffer
	buffer = new unsigned char[ width * height * 4 ];
}

AwesomiumView::~AwesomiumView( void )
{
	// KILL EVERYTHING	webView->Destroy();
	WebCore::Shutdown();
	delete[] buffer;
}

bool AwesomiumView::Update( void )
{
	// Update page
	webCore->Update();

	// Get the surface
	surface = (BitmapSurface*)webView->surface();

	return true;
}

void AwesomiumView::Draw( void )
{
	glBindTexture( GL_TEXTURE_2D, textureThing );

	if( surface )
	{
		if( surface->is_dirty() )
		{
			// Copy to buffer
			surface->CopyTo( buffer, surface->row_span(), 4, false, false );

			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface->width(), surface->height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)buffer );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		}
	}
}