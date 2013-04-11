#include "ContentController.h"

#define _USE_READ_FILE
#define _USE_SCAN_DIR
#include <Helpers.h>

#define CONTENT_PATH "Resources/Assets/"

using namespace Graphos::Content;

bool ContentController::Initialize( void )
{
	unordered_map<string, string> files = Helpers::ScanDir( CONTENT_PATH );

	for_each(
		begin( files ),
		end( files ),
		[&]( pair<string, string> pair )
		{
			if( pair.second == ".obj" )
			{
				ingredientShelf[ pair.first ] = new Mesh( string( CONTENT_PATH ).append( pair.first ).append( pair.second ) );
			}
			else if( FreeImage_GetFileType( string( CONTENT_PATH ).append( pair.first ).append( pair.second ).c_str() ) != FIF_UNKNOWN )
			{
				ingredientShelf[ pair.first ] = new Texture( string( CONTENT_PATH ).append( pair.first ).append( pair.second ) );
			}
		}
	);

	return true;
}