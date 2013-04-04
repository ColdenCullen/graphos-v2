#include "Texture.h"

using namespace Graphos::Content;

bool Texture::LoadFromFile( const char* filePath )
{
	// Load image
	FIBITMAP* imageData = FreeImage_Load( FreeImage_GetFileType( filePath, 0 ), filePath );

	// Convert to 32 bits
	FIBITMAP* temp = imageData;
	imageData = FreeImage_ConvertTo32Bits( imageData );
	FreeImage_Unload( temp );

	// Get dimensions
	width = FreeImage_GetWidth( imageData );
	height = FreeImage_GetHeight( imageData );

	// Buffer to GL
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA ,GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits( imageData ) );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	if( glGetError() )
		return false;

	FreeImage_Unload( imageData );

	return true;
}