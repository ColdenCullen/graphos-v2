#include "GraphosGame.h"

#define _USE_READ_FILE
#define _USE_SCAN_DIR
#include "Helpers.h"

#include <iostream>

#define OBJECTS_PATH "Resources/Assets/Objects/"

using namespace Graphos;

void GraphosGame::Run( void )
{
	// Initialize time
	clock_t cur = clock();
	clock_t prev = clock();

	unsigned int frameCount = 0;
	float totalTime = 0;

	if( !ConfigController::Get().LoadSettings() )
		return;

	if( !GraphicsController::Get().Initialize() )
		return;

	if( !ContentController::Get().Initialize() )
		return;

	if( !ScriptController::Get().Initialize() )
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
		totalTime += deltaTime;
		frameCount++;

		if( totalTime >= 1.0f )
		{
			std::cout << frameCount << std::endl;
			totalTime = 0.0f;
			frameCount = 0;
		}

		// Update objects in list
		for( auto iterator = begin( objects ); iterator != end( objects ); ++iterator )
			iterator->second->Update( deltaTime );

		// Do the frame processing.
		if( !Update() )
		{
			done = true;
		}
		
		GraphicsController::Get().CallGLFunction( GraphicsController::BEGIN );

		// Draw objects in list
		for( auto iterator = begin( objects ); iterator != end( objects ); ++iterator )
			iterator->second->Draw();

		Draw();

		GraphicsController::Get().CallGLFunction( GraphicsController::END );
	}

	DeleteObjects();

	Shutdown();

	ContentController::Get().Shutdown();
}

GraphosGame::~GraphosGame( void )
{
	for( auto object = begin( objects ); object != end( objects ); ++object )
		delete object->second;

	objects.clear();
}

void GraphosGame::LoadObjects( void )
{
	unordered_map<string, string> files = Helpers::ScanDir( OBJECTS_PATH );
	Json::Reader reader;
	Json::Value root;

	for( auto file = begin( files ); file != end( files ); ++file )
	{
		if( reader.parse( Helpers::ReadFile( string( OBJECTS_PATH ).append( file->second ).append( file->first ) ), root ) )
		{
			if( root.get( "Name", root ) != root )
			{
				GameObject* newObj = new GameObject( &( ShaderController::Get().GetShader( "texture" ) ) );

				if( root.get( "Texture", root ) != root )
					newObj->AddIngredient<Texture>(
						ContentController::Get().GetContent<Texture>( root.get( "Texture", root ).get( "Name", root ).asString() )
					);

				if( root.get( "AwesomiumView", root ) != root )
					newObj->AddIngredient<AwesomiumView>(
						new AwesomiumView(
							root.get( "AwesomiumView", root ).get( "url", root ).asString(),
							root.get( "AwesomiumView", root ).get( "width", root ).asUInt(),
							root.get( "AwesomiumView", root ).get( "height", root ).asUInt()
						)
					);

				if( root.get( "Script", root ) != root )
					newObj->AddIngredient<Script>(
						ScriptController::Get().CreateInstanceVariable(
							root.get( "Script", root ).get( "class", root ).asString(),
							newObj
						)
					);

				if( root.get( "Mesh", root ) != root )
					newObj->AddIngredient<Mesh>(
						ContentController::Get().GetContent<Mesh>( root.get( "Mesh", root ).get( "Name", root ).asString() )
					);

				if( root.get( "Transform", root ) != root )
				{
					Json::Value transform = root.get( "Transform", root );

					if( transform.get( "Scale", root ) != root )
						newObj->transform.Scale(
							transform.get( "Scale", root ).get( "x", root ).asDouble(),
							transform.get( "Scale", root ).get( "y", root ).asDouble(),
							transform.get( "Scale", root ).get( "z", root ).asDouble()
						);
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
				}

				objects[ root.get( "Name", root ).asString() ] = newObj;
			}
		}
	}
}

void GraphosGame::DeleteObjects( void )
{
	for( auto object = begin( objects); object != end( objects ); ++object )
	{
		object->second->Shutdown();
		delete object->second;
	}
	
	objects.clear();
}