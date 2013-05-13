//
//  TestGame.h
//  Graphos
//
//  Created by Colden Cullen on 5/1/13.
//  Copyright (c) 2013 Colden Cullen. All rights reserved.
//

#ifndef __TEST_GAME
#define __TEST_GAME

#include "GraphosGame.h"
#include "GameObject.h"
#include "Input.h"
#include "Camera.h"
#include "Rigidbody.h"
#include "Helpers.h"
#include "Config.h"

namespace Graphos
{
	class TestGame : public GraphosGame
	{
	private:
		

		bool Initialize( void )
		{
			

			return true;
		}

		bool Update( float deltaTime )
		{
#ifdef _WIN32
			// Quit condition
			if( Input::Get().IsKeyDown( VK_ESCAPE, true ) )
			{
				if( currentState == Game )
					currentState = Menu;
				else if( currentState == Menu )
					return false;
			}

			// 
			if( Input::Get().IsKeyDown( VK_F5, true ) )
				Reset();

			if( currentState == Game )
			{
				
	
				#pragma region Camera
				// Move camera
				if( Input::Get().IsKeyDown( VK_LEFT, false ) )
				{
					camera->Owner()->transform.Rotate( 0.0f, -3.0f * deltaTime, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_RIGHT, false ) )
				{
					camera->Owner()->transform.Rotate( 0.0f, 3.0f * deltaTime, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_UP, false ) )
				{
					camera->Owner()->transform.Rotate( 3.0f * deltaTime, 0.0f, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_DOWN, false ) )
				{
					camera->Owner()->transform.Rotate( -3.0f * deltaTime, 0.0f, 0.0f );
				}
	
				// Rotate camera
				if( Input::Get().IsKeyDown( VK_A, false ) )
				{
					camera->Owner()->transform.Translate( -1.0f * deltaTime, 0.0f, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_D, false ) )
				{
					camera->Owner()->transform.Translate( 1.0f * deltaTime, 0.0f, .0f );
				}
				if( Input::Get().IsKeyDown( VK_W, false ) )
				{
					camera->Owner()->transform.Translate( 0.0f, 0.0f, 1.0f * deltaTime );
				}
				if( Input::Get().IsKeyDown( VK_S, false ) )
				{
					camera->Owner()->transform.Translate( 0.0f, 0.0f, -1.0f * deltaTime );
				}
				#pragma endregion
			}
#endif

			return true;
		}

		void Draw( void )
		{
			//ShaderController::Get().SetAllShadersUniform( "cameraMatrix", cam->transform.Matrix() );
			//ShaderController::Get().SetAllShadersUniform( "projectionMatrix", WindowController::Get().PerspectiveMatrix() );

			ShaderController::Get().GetShader( "texture" ).SetUniform( "cameraMatrix", /*cam->transform.WorldMatrix()*/Matrix::Identity );
			ShaderController::Get().GetShader( "texture" ).SetUniform( "projectionMatrix", WindowController::Get().PerspectiveMatrix() );
		}

		void Shutdown( void )
		{
			delete_s( camera );
		}
	};
}

#endif//__TEST_GAME