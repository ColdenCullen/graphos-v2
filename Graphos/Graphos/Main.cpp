#include "GraphosGame.h"
#include "ConfigController.hpp"
#include "DrawableGameObject.h"
#include "Input.h"
#include "Texture.h"
#include "Mesh.h"
#include "Camera.h"

#include "AwesomiumView.h"

#pragma region Suplimental Stuff
#if defined( _WIN32 )
 // Turn off console
 #ifndef DEBUG
  #pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
 #endif//DEBUG

 // Display memory leaks
 #define _CRTDBG_MAP_ALLOC
 #include <stdlib.h>
 #include <crtdbg.h>
 #ifdef DEBUG
  #ifndef DBG_NEW
   #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
   #define new DBG_NEW
  #endif//DBG_NEW
 #endif//_DEBUG
#elif defined( __APPLE__ )
 
#endif//_WIN32/__APPLE__
#pragma endregion

using namespace Graphos;

class TestGame : public GraphosGame
{
public:
	//TestGame( void ) : cube( nullptr ), sphere( nullptr ), av( nullptr ) { }

private:
	Camera* cam;
	GameObject* cube;
	GameObject* sphere;
	AwesomiumView* av;

	bool Initialize( void )
	{
		av = new AwesomiumView();
		cam = new Camera();

		cube = new GameObject( ShaderController::Get().GetShader( "texture" ) );
		sphere = new GameObject( ShaderController::Get().GetShader( "texture" ) );

		cube->AddIngredient( ContentController::Get().GetContent<Texture>( "Poop" ) );
		sphere->AddIngredient( av );
		
		cube->AddIngredient( ContentController::Get().GetContent<Mesh>( "Cube" ) );
		sphere->AddIngredient( ContentController::Get().GetContent<Mesh>( "Sphere" ) );

		cube->transform.Scale( 0.5f, 0.5f, 0.5f );
		cube->transform.Translate( 1.0f, 0.0f, 3.0f );

		sphere->transform.Scale( 0.5f, 0.5f, 0.5f );
		sphere->transform.Translate( -1.0f, 0.0f, 3.0f );

		objects.push_back( cube );
		objects.push_back( sphere );

		return true;
	}

	bool Update( void )
	{
#ifdef _WIN32
		// Quit condition
		if( Input::Get().IsKeyDown( VK_ESCAPE, true ) )
		{
			//delete cube;
			//delete sphere;

			return false;
		}

		if( Input::Get().IsKeyDown( VK_SPACE, true ) )
		{
			ConfigController::Get().LoadSettings();
			GraphicsController::Get().Reload();
		}

		// Move object
		if( Input::Get().IsKeyDown( VK_LEFT, false ) )
		{
			cube->transform.Translate( -0.01f, 0.0f, 0.0f );
			sphere->transform.Translate( -0.01f, 0.0f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_RIGHT, false ) )
		{
			cube->transform.Translate( 0.01f, 0.0f, 0.0f );
			sphere->transform.Translate( 0.01f, 0.0f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_UP, false ) )
		{
			cube->transform.Translate( 0.0f, 0.01f, 0.0f );
			sphere->transform.Translate( 0.0f, 0.01f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_DOWN, false ) )
		{
			cube->transform.Translate( 0.0f, -0.01f, 0.0f );
			sphere->transform.Translate( 0.0f, -0.01f, 0.0f );
		}

		// Rotate
		if( Input::Get().IsKeyDown( VK_A, false ) )
		{
			cube->transform.Rotate( 0.0f, 15.0f, 0.0f, 0.0f );
			sphere->transform.Rotate( 0.0f, 15.0f, 0.0f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_D, false ) )
		{
			cube->transform.Rotate( 0.0f, -15.0f, .0f, 0.0f );
			sphere->transform.Rotate( 0.0f, -15.0f, .0f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_W, false ) )
		{
			cube->transform.Rotate( -15.0f, 0.0f, 0.0f, 0.0f );
			sphere->transform.Rotate( -15.0f, 0.0f, 0.0f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_S, false ) )
		{
			cube->transform.Rotate( 15.0f, 0.0f, 0.0f, 0.0f );
			sphere->transform.Rotate( 15.0f, 0.0f, 0.0f, 0.0f );
		}
#endif

		//av.Update();

		//cout << deltaTime << endl;

		//cube->Update();
		//sphere->Update();

		return true;
	}

	void Draw( void )
	{
		ShaderController::Get().SetAllShadersUniform( "cameraMatrix", cam->transform.Matrix() );
		ShaderController::Get().SetAllShadersUniform( "projectionMatrix", WindowController::Get().PerspectiveMatrix() );
		//ShaderController::Get().GetShader( "texture" ).SetUniform( "projectionMatrix", WindowController::Get().OrthogonalMatrix() );

		//av->Draw();

		//glBindTexture( GL_TEXTURE_2D, av.textureThing );

		//cube->Draw();
		//sphere->Draw();
	}
};

int main()
{
	TestGame test;
	test.Run();

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}