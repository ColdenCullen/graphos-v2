#include "AwesomiumView.h"

using namespace Graphos;

AwesomiumView::AwesomiumView( void )
{
	// Generate a texture to use
	glGenTextures( 1, &textureThing );

	// Initialize Awesomium
	webCore = WebCore::Initialize( WebConfig() );
	webView = webCore->CreateWebView( 1280, 720 );
	webView->LoadURL( WebURL( WSLit( "http://ColdenCullen.com" ) ) );

	// Initialize buffer
	buffer = new unsigned char[ 1280 * 720 * 4 ];
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
	surface = static_cast<BitmapSurface*>( webView->surface() );

	return true;
}

void AwesomiumView::Draw( void )
{
	if( surface && surface->is_dirty() )
	{
		// Copy to buffer
		surface->CopyTo( buffer, surface->row_span(), 4, false, false );

		glBindTexture( GL_TEXTURE_2D, textureThing );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface->width(), surface->height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)buffer );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	}
}