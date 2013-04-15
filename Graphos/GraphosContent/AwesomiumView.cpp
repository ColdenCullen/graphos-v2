#include "AwesomiumView.h"

using namespace std;
using namespace Graphos::Content;

AwesomiumView::~AwesomiumView( void )
{
	// KILL EVERYTHING	webView->Destroy();
	WebCore::Shutdown();
	delete[] buffer;
}

bool AwesomiumView::Initialize( string url, unsigned int width, unsigned int height )
{
	// Generate a texture to use
	glGenTextures( 1, &textureID );

	// Initialize Awesomium
	if( WebCore::instance() )
		webCore = WebCore::instance();
	else
		webCore = WebCore::Initialize( WebConfig() );

	webView = webCore->CreateWebView( width, height );
	webView->LoadURL( WebURL( WSLit( url.c_str() ) ) );

	// Initialize buffer
	buffer = new unsigned char[ width * height * 4 ];

	return true;
}

bool AwesomiumView::Update( float deltaTime )
{
	if( webCore )
	{
		// Update page
		webCore->Update();

		// Get the surface
		surface = (BitmapSurface*)webView->surface();
	}

	return true;
}

void AwesomiumView::Draw( void )
{
	if( webCore )
	{
		glBindTexture( GL_TEXTURE_2D, textureID );

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
}

void AwesomiumView::Shutdown( void )
{
	delete[] buffer;
}