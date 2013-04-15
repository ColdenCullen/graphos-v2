#include "GraphosGame.h"
#include "GameObject.h"
#include "Input.h"
#include "Camera.h"

//#define _CHECK_LEAKS

#pragma region Suplimental Stuff
#if defined( _WIN32 )

 // Turn off console
 #ifndef DEBUG
  #pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
 #endif//DEBUG

 // Display memory leaks
 #if defined( DEBUG ) && defined( _CHECK_LEAKS )
  #include <vld.h>
 #endif//_DEBUG && _CHECK_LEAKS

#elif defined( __APPLE__ )
 
#endif//_WIN32/__APPLE__
#pragma endregion

namespace Graphos
{
	class TestGame : public GraphosGame
	{
	public:
		//TestGame( void ) : cube( nullptr ), sphere( nullptr ), av( nullptr ) { }

	private:
		Camera* cam;
		GameObject* cube;
		GameObject* sphere;

		bool Initialize( void )
		{
			cam = new Camera();

			cube = objects[ "Cube" ];
			sphere = objects[ "Sphere" ];

			return true;
		}

		bool Update( void )
		{
#ifdef _WIN32
			// Quit condition
			if( Input::Get().IsKeyDown( VK_ESCAPE, true ) )
			{
				return false;
			}

			if( Input::Get().IsKeyDown( VK_F5, true ) )
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

			return true;
		}

		void Draw( void )
		{
			//ShaderController::Get().SetAllShadersUniform( "cameraMatrix", cam->transform.Matrix() );
			//ShaderController::Get().SetAllShadersUniform( "projectionMatrix", WindowController::Get().PerspectiveMatrix() );

			ShaderController::Get().GetShader( "texture" ).SetUniform( "cameraMatrix", cam->transform.WorldMatrix() );
			ShaderController::Get().GetShader( "texture" ).SetUniform( "projectionMatrix", WindowController::Get().PerspectiveMatrix() );
			//ShaderController::Get().GetShader( "texture" ).SetUniform( "projectionMatrix", WindowController::Get().OrthogonalMatrix() );

			//av->Draw();

			//glBindTexture( GL_TEXTURE_2D, av.textureThing );

			//cube->Draw();
			//sphere->Draw();
		}

		void Shutdown( void )
		{
			delete cam;
		}
	};
}

int main()
{
	Graphos::TestGame test;
	test.Run();

	return 0;
}