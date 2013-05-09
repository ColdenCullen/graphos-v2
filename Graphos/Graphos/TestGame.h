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
		Camera* cam;
		GameObject* cube;
		GameObject* sphere;
		
		bool Initialize( void )
		{
			// Call parent's load objects
			//LoadObjects();

			cam = nullptr;//new Camera();
			cube = nullptr;
			sphere = nullptr;

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

			if( Input::Get().IsKeyDown( VK_F5, true ) )
			{
				Reset();
			}

			if( currentState == Game )
			{
				if( sphere == nullptr || cube == nullptr )
				{
					cube = GameObject::GetGameObject( "LeftCube" );
					sphere = GameObject::GetGameObject( "Sphere" );
				}

				if( Input::Get().IsKeyDown( VK_SPACE, true ) )
					sphere->GetIngredient<Rigidbody>()->AddForce( 1.0f, 0.0f, 0.0f );
	
				// Move object
				if( Input::Get().IsKeyDown( VK_LEFT, false ) )
				{
					cube->transform.Translate( -0.01f, 0.0f, 0.0f );
					//sphere->transform.Translate( -0.01f, 0.0f, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_RIGHT, false ) )
				{
					cube->transform.Translate( 0.01f, 0.0f, 0.0f );
					//sphere->transform.Translate( 0.01f, 0.0f, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_UP, false ) )
				{
					cube->transform.Translate( 0.0f, 0.01f, 0.0f );
					//sphere->transform.Translate( 0.0f, 0.01f, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_DOWN, false ) )
				{
					cube->transform.Translate( 0.0f, -0.01f, 0.0f );
					//sphere->transform.Translate( 0.0f, -0.01f, 0.0f );
				}
	
				// Rotate
				if( Input::Get().IsKeyDown( VK_A, false ) )
				{
					cube->transform.Rotate( 0.0f, 15.0f, 0.0f );
					//sphere->transform.Rotate( 0.0f, 15.0f, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_D, false ) )
				{
					cube->transform.Rotate( 0.0f, -15.0f, .0f );
					//sphere->transform.Rotate( 0.0f, -15.0f, .0f );
				}
				if( Input::Get().IsKeyDown( VK_W, false ) )
				{
					cube->transform.Rotate( -15.0f, 0.0f, 0.0f );
					//sphere->transform.Rotate( -15.0f, 0.0f, 0.0f );
				}
				if( Input::Get().IsKeyDown( VK_S, false ) )
				{
					cube->transform.Rotate( 15.0f, 0.0f, 0.0f );
					//sphere->transform.Rotate( 15.0f, 0.0f, 0.0f );
				}
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
			delete_s( cam );
		}
	};
}

#endif//__TEST_GAME