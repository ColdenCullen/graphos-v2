#include "GraphosGame.h"

#define _USE_READ_FILE
#define _USE_SCAN_DIR
#include "Helpers.h"

#define OBJECTS_PATH "Resources/Objects"

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

	if( !ContentController::Get().Initialize() )
		return;
	
	LoadObjects();

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

		// Update objects in list
		for_each(
			begin( objects ),
			end( objects ),
			[]( GameObject* object )
			{
				object->Update();
			}
		);

		// Do the frame processing.
		if( !Update() )
		{
			done = true;
		}
		
		GraphicsController::Get().CallGLFunction( GraphicsController::BEGIN );

		// Draw objects in list
		for_each(
			begin( objects ),
			end( objects ),
			[]( GameObject* object )
			{
				object->Draw();
			}
		);

		Draw();

		GraphicsController::Get().CallGLFunction( GraphicsController::END );
	}
}

Graphos::GraphosGame::~GraphosGame( void )
{
	for_each(
		begin( objects ),
		end( objects ),
		[]( GameObject* object )
		{
			delete object;
		}
	);
}

void Graphos::GraphosGame::LoadObjects( void )
{
	unordered_map<string, string> files = Helpers::ScanDir( OBJECTS_PATH );

	for_each(
		begin( files ),
		end( files ),
		[&]( pair<string, string> file )
		{
			if( file.second == ".json" )
			{
				Json::Reader reader;
				Json::Value root;

				if( reader.parse( Helpers::ReadFile( string( OBJECTS_PATH ).append( file.first ).append( file.second ) ), root ) )
				{
					GameObject* newObj = new GameObject( ShaderController::Get().GetShader( "texture" ) );

					if( root.get( "Texture", root ) != root )
						newObj->AddIngredient<Texture>( root.get( "Texture", root ).get( "filePath", root ).asString() );

					if( root.get( "Mesh", root ) != root )
						newObj->AddIngredient<Texture>( root.get( "Mesh", root ).get( "filePath", root ).asString() );

					if( root.get( "Transform", root ) != root )
					{
						Json::Value transform = root.get( "Transform", root );

						if( transform.get( "Position", root ) != root )
							newObj->transform.Translate(
								transform.get( "Position", root ).get( "x", root ).asDouble(),
								transform.get( "Position", root ).get( "y", root ).asDouble(),
								transform.get( "Position", root ).get( "z", root ).asDouble()
							);
						if( transform.get( "Rotation", root ) != root )
							newObj->transform.Rotate(
								transform.get( "Rotation", root ).get( "x", root ).asDouble(),
								transform.get( "Rotation", root ).get( "y", root ).asDouble(),
								transform.get( "Rotation", root ).get( "z", root ).asDouble()
							);
						if( transform.get( "Scale", root ) != root )
							newObj->transform.Scale(
								transform.get( "Scale", root ).get( "x", root ).asDouble(),
								transform.get( "Scale", root ).get( "y", root ).asDouble(),
								transform.get( "Scale", root ).get( "z", root ).asDouble()
							);
					}
				}
			}
		}
	);
}