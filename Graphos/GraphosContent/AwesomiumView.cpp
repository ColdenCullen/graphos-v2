#include "AwesomiumView.h"

using namespace std;
using namespace Graphos::Content;

bool AwesomiumView::Initialize( string url, unsigned int width, unsigned int height )
{
	// Generate a texture to use
	glGenTextures( 1, &textureID );

	if( !WebCore::instance() )
		WebCore::Initialize( WebConfig() );

	webView = WebCore::instance()->CreateWebView( width, height );
	webView->LoadURL( WebURL( WSLit( url.c_str() ) ) );
	webView->SetTransparent( true );

	// Initialize buffer
	buffer = new unsigned char[ width * height * 4 ];

	return true;
}

bool AwesomiumView::Update( float deltaTime )
{
	if( WebCore::instance() )
	{
		// Update page
		WebCore::instance()->Update();

		// Get the surface
		surface = static_cast<BitmapSurface*>( webView->surface() );
	}

	return true;
}

void AwesomiumView::Draw( void )
{
	if( WebCore::instance() )
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
	// KILL EVERYTHING
	webView->Destroy();
	//WebCore::Shutdown();
	delete[] buffer;
}