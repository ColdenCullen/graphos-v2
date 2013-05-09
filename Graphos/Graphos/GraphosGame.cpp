#include "GraphosGame.h"

#define _USE_READ_FILE
#define _USE_SCAN_DIR
#include "Helpers.h"

#include <iostream>

#define OBJECTS_PATH "Resources/Assets/Objects/"

using namespace Graphos;
using namespace Graphos::Content;

void GraphosGame::Run( void )
{
	//////////////////////////////////////////////////////////////////////////
	// Initialize
	//////////////////////////////////////////////////////////////////////////

	// Initialize values and controllers
	bool isDone = Start();

	// Initialize time
	clock_t cur = clock();
	clock_t prev = clock();

	unsigned int frameCount = 0;
	float totalTime = 0;

	// Loop until there is a quit message from the window or the user.
	while( !isDone )
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
#ifdef DEBUG
			std::cout << frameCount << std::endl;
#endif
			totalTime = 0.0f;
			frameCount = 0;
		}

		//////////////////////////////////////////////////////////////////////////
		// Update
		//////////////////////////////////////////////////////////////////////////
		
		// Do the updating of the child class.
		isDone = !Update( deltaTime );

		// Update physics
		Physics::Get().Update();

		// Update the UI
		ui->Update( deltaTime );

		// Update objects in list
		if( currentState == Game )
		{
			if( !objectsLoaded )
				LoadObjects();

			for( auto iterator = objects->begin(); iterator != objects->end(); ++iterator )
				iterator->second.Update( deltaTime );	
		}

		//////////////////////////////////////////////////////////////////////////
		// Draw
		//////////////////////////////////////////////////////////////////////////
		
		// Begin drawing
		GraphicsController::Get().CallGLFunction( GraphicsController::BEGIN );

		// Draw in child class
		Draw();

		// Draw objects in list
		if( currentState == Game )
			for( auto iterator = objects->begin(); iterator != objects->end(); ++iterator )
				iterator->second.Draw();

		// Draw the UI last
		ui->Draw();

		// End drawing
		GraphicsController::Get().CallGLFunction( GraphicsController::END );
	}

	Stop();
}

void GraphosGame::LoadObjects( void )
{
	unordered_map<string, string> files = Helpers::ScanDir( OBJECTS_PATH );
	Json::Reader reader;
	Json::Value root;

	Json::Value current;

	// For iterating (sometimes)
	int ii = 0;

	// Map for parents, to be added after all objects are loaded
	unordered_map<unsigned int, string> parentMap;

	for( auto file = begin( files ); file != end( files ); ++file )
	{
		if( reader.parse( Helpers::ReadFile( string( OBJECTS_PATH ).append( file->second ).append( file->first ) ), root ) )
		{
			if( ( current = root.get( "Name", root ) ) != root )
			{
				// Create object, get pointer to it
				string name = current.asString();
				unsigned int id = GameObject::CreateObject( name, &( ShaderController::Get().GetShader( root.get( "Shader", root ).asString() ) ) );
				GameObject* newObj = GameObject::GetGameObject( name );

				// Get parent
				if( ( current = root.get( "Parent", root ) ) != root )
					parentMap[ id ] = current.asString();

				// Set texture
				if( ( current = root.get( "Texture", root ) ) != root )
					newObj->AddIngredient<Texture>(
						AssetController::Get().GetContent<Texture>( current.get( "Name", root ).asString() )
					);
					
				// Set physics Rigid Body object
				if( ( current = root.get( "Rigidbody", root ) ) != root )
				{
					Rigidbody* rb = new Rigidbody( newObj );

					// Get rigid body's values
					Json::Value currentRigidbody = current.get( "LinearVelocity", root );

					// Add initial velocities and drags
					rb->linearVelocity.x = currentRigidbody.get( "x", root ).asDouble();
					rb->linearVelocity.y = currentRigidbody.get( "y", root ).asDouble();
					rb->linearVelocity.z = currentRigidbody.get( "z", root ).asDouble();

					currentRigidbody = root.get( "Rigidbody", root ).get( "AngularVelocity", root );

					// Add initial velocities and drags
					rb->angularVelocity.x = currentRigidbody.get( "x", root ).asDouble();
					rb->angularVelocity.y = currentRigidbody.get( "y", root ).asDouble();
					rb->angularVelocity.z = currentRigidbody.get( "z", root ).asDouble();

					// Add initial velocities and drags
					rb->linearDrag = root.get( "Rigidbody", root ).get( "LinearDrag", root ).asDouble();
					rb->angularDrag = root.get( "Rigidbody", root ).get( "AngularDrag", root ).asDouble();

					newObj->AddIngredient<Rigidbody>( rb );
				}

				// Add webview
				if( ( current = root.get( "AwesomiumView", root ) ) != root && ii == 0 )
					newObj->AddIngredient<AwesomiumView>(
						new AwesomiumView(
							current.get( "url", root ).asString(),
							current.get( "width", root ).asUInt(),
							current.get( "height", root ).asUInt()
						)
					);

				// Add a script
				if( ( current = root.get( "Script", root ) ) != root )
					newObj->AddIngredient<Content::Script>(
						ScriptController::Get().CreateObjectInstance(
							current.get( "Class", root ).asString(),
							id,
							newObj
						)
					);

				// Add a mesh
				if( ( current = root.get( "Mesh", root ) ) != root )
					newObj->AddIngredient<Mesh>(
						AssetController::Get().GetContent<Mesh>( current.get( "Name", root ).asString() )
					);

				// Transform object
				if( ( current = root.get( "Transform", root ) ) != root )
				{
					Json::Value currentTransform;

					if( ( currentTransform = current.get( "Scale", root ) ) != root )
						newObj->transform.Scale(
							currentTransform.get( "x", root ).asDouble(),
							currentTransform.get( "y", root ).asDouble(),
							currentTransform.get( "z", root ).asDouble()
						);
					if( ( currentTransform = current.get( "Position", root ) ) != root )
						newObj->transform.Translate(
							currentTransform.get( "x", root ).asDouble(),
							currentTransform.get( "y", root ).asDouble(),
							currentTransform.get( "z", root ).asDouble()
						);
					if( ( currentTransform = current.get( "Rotation", root ) ) != root )
						newObj->transform.Rotate(
							currentTransform.get( "x", root ).asDouble(),
							currentTransform.get( "y", root ).asDouble(),
							currentTransform.get( "z", root ).asDouble()
						);
				}

				// Setup collider
				if( ( current = root.get( "Collider", root ) ) != root )
				{
					Json::Value currentCol;
					string type = current.get( "Type", root ).asString();
					Collider* col;

					if( type == "Sphere" )
					{
						col = new SphereCollider( newObj );
						static_cast<SphereCollider*>( col )->radius = static_cast<float>( current.get( "Radius", root ).asDouble() );
					}
					else if( type == "Box" )
					{
						col = new BoxCollider( newObj );

						if( ( currentCol = current.get( "Size", root ) ) != root )
							static_cast<BoxCollider*>( col )->size = Vector3(
								currentCol.get( "x", root ).asDouble(),
								currentCol.get( "y", root ).asDouble(),
								currentCol.get( "z", root ).asDouble()

							);
						else
							static_cast<BoxCollider*>( col )->size = Vector3( 1.0f, 1.0f, 1.0f );
					}

					if( ( currentCol = current.get( "Offset", root ) ) != root )
					{
						col->centerOffset = Vector3(
							currentCol.get( "x", root ).asDouble(),
							currentCol.get( "y", root ).asDouble(),
							currentCol.get( "z", root ).asDouble()
						);
					}

					if( ( currentCol = current.get( "Bounce", root ) ) != root )
					{
						col->bounce = currentCol.asDouble();
					}

					newObj->AddIngredient<Collider>( col );
					Physics::Get().AddCollider( col );
				}
			}
		}
	}

	objects = &GameObject::GetObjectsList();

	for( auto parentPair = begin( parentMap ); parentPair != end( parentMap ); ++parentPair )
		GameObject::GetGameObject( parentPair->first )->transform.parent = &GameObject::GetGameObject( parentPair->second )->transform;

	objectsLoaded = true;
}

void GraphosGame::DeleteObjects( void )
{
	for( auto object = objects->begin(); object != objects->end(); ++object )
		object->second.Shutdown();
	
	GameObject::ClearObjects();
}

void GraphosGame::Reset( void )
{
	Config::Get().LoadSettings();
	GraphicsController::Get().Reload();

	// Delete loaded objects
	DeleteObjects();

	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete ui;
	Physics::Get().Shutdown();
	AssetController::Get().Shutdown();
	ScriptController::Get().Shutdown();

	// Restart
	ScriptController::Get().Initialize();
	AssetController::Get().Initialize();
	Physics::Get().Initialize();
	ui = new UserInterface( this );

	currentState = Menu;

	Initialize();
}

bool GraphosGame::Start( void )
{
	objectsLoaded = false;
	currentState = Menu;

	bool isDone = false;

	if( !isDone && !Config::Get().LoadSettings() )
		isDone = true;

	if( !isDone && !GraphicsController::Get().Initialize() )
		isDone = true;

	if( !isDone && !AssetController::Get().Initialize() )
		isDone = true;

	if( !isDone && !Physics::Get().Initialize() )
		isDone = true;

	ui = new UserInterface( this );

	if( !isDone && !Initialize() )
		isDone = true;

	return isDone;
}

void GraphosGame::Stop( void )
{
	// Delete loaded objects
	DeleteObjects();

	// Call child shutdown
	Shutdown();

	// Shutdown UI and controllers
	delete ui;
	Physics::Get().Shutdown();
	AssetController::Get().Shutdown();
	ScriptController::Get().Shutdown();
}