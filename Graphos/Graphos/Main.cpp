#include "GraphosGame.h"
#include "ConfigController.hpp"
#include "DrawableGameObject.h"
#include "Input.h"

#pragma region Leak Detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef DEBUG
 #ifndef DBG_NEW
  #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
  #define new DBG_NEW
 #endif
#endif// _DEBUG
#pragma endregion

#ifdef DEBUG
 #pragma  comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

using namespace Graphos;

class TestGame : public GraphosGame
{
private:
	Camera cam;
	DrawableGameObject test;

	bool Initialize( void )
	{
		test.SetShaderName( "texture" );

		//test.BufferData( nullptr );

		test.LoadObjectFile( "Resources/Assets/Cube.obj" );
		test.InitMaterial( "Resources/Assets/CubeMaterial.jpg" );
		test.transform.Scale( 0.5f, 0.5f, 0.5f );
		test.transform.Translate( 0.0f, 0.0f, 3.0f );

		return true;
	}

	bool Update( void )
	{
		// Quit condition
		if( Input::Get().IsKeyDown( VK_ESCAPE, true ) )
			return false;

		if( Input::Get().IsKeyDown( VK_SPACE, true ) )
		{
			ConfigController::Get().LoadSettings();
			GraphicsController::Get().Resize();
		}

		// Move object
		if( Input::Get().IsKeyDown( VK_LEFT, false ) )
		{
			test.transform.Translate( -0.01f, 0.0f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_RIGHT, false ) )
		{
			test.transform.Translate( 0.01f, 0.0f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_UP, false ) )
		{
			test.transform.Translate( 0.0f, 0.01f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_DOWN, false ) )
		{
			test.transform.Translate( 0.0f, -0.01f, 0.0f );
		}

		// Rotate
		if( Input::Get().IsKeyDown( VK_A, true ) )
		{
			test.transform.Rotate( 0.0f, 15.0f, 0.0f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_D, true ) )
		{
			test.transform.Rotate( 0.0f, -15.0f, .0f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_W, true ) )
		{
			test.transform.Rotate( -15.0f, 0.0f, 0.0f, 0.0f );
		}
		if( Input::Get().IsKeyDown( VK_S, true ) )
		{
			test.transform.Rotate( 15.0f, 0.0f, 0.0f, 0.0f );
		}

		return true;
	}

	void Draw( void )
	{
		ShaderController::Get().GetShader( "texture" ).SetUniform( "cameraMatrix", cam.transform.Matrix() );
		ShaderController::Get().GetShader( "texture" ).SetUniform( "projectionMatrix", WindowController::Get().GetPerspectiveMatrix() );

		test.Draw();
	}
};

int main()
{
	TestGame test;
	test.Run();

	//_CrtDumpMemoryLeaks();

	return 0;
}