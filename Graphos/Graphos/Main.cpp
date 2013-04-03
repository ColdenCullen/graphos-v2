#include "GraphosGame.h"
#include "SettingsController.hpp"
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
		test.SetShaderName( "color" );

		// Put the three triangle vertices into the VBO
		GLfloat vertexData[] = {
			//  X     Y     Z	  R	    G     B
			0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
			-0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
			0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		test.BufferData( vertexData );

		//test.transform.Scale( 0.5f, 0.5f, 0.0f );

		return true;
	}

	bool Update( void )
	{
		if( Input::Get().IsKeyDown( VK_ESCAPE, true ) )
			return false;

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

		return true;
	}

	void Draw( void )
	{
		ShaderController::Get().GetShader( "color" ).Use();
		ShaderController::Get().GetShader( "color" ).SetUniform( "cameraMatrix", cam.transform.getMatrix() );
		ShaderController::Get().GetShader( "color" ).SetUniform( "projectionMatrix", WindowController::Get().GetPerspectiveMatrix() );

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