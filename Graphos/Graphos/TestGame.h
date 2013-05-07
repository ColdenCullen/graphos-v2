//
//  TestGAme.h
//  Graphos
//
//  Created by Colden Cullen on 5/1/13.
//  Copyright (c) 2013 Colden Cullen. All rights reserved.
//

#ifndef __TESTGAME
#define __TESTGAME

#include "GraphosGame.h"
#include "GameObject.h"
#include "Input.h"
#include "Camera.h"
#include "Rigidbody.h"
#include "Helpers.h"
#include "UserInterface.h"

namespace Graphos
{
	class TestGame : public GraphosGame
	{
	private:
		Camera* cam;
		GameObject* cube;
		GameObject* sphere;
		UserInterface* ui;

		bool Initialize( void )
		{
			cam = nullptr;//new Camera();

			cube = GameObject::GetGameObject( "LeftCube" );
			sphere = GameObject::GetGameObject( "Sphere" );

			ui = new UserInterface( "Resources/UIs/MainMenu.html" );

			return true;
		}

		bool Update( float deltaTime )
		{
#ifdef _WIN32
			// Quit condition
			if( Input::Get().IsKeyDown( VK_ESCAPE, true ) )
			{
				return false;
			}

			if( Input::Get().IsKeyDown( VK_F5, true ) )
			{
				Reset();

				delete ui;
				ui = new UserInterface( "Resources/UIs/MainMenu.html" );
			}

			Point cursor = Input::Get().GetMousePos();
			ui->view->webView->InjectMouseMove( cursor.x, cursor.y );

			if( Input::Get().IsKeyDown( VK_LBUTTON, false ) )
				ui->view->webView->InjectMouseDown( kMouseButton_Left );
			if( !Input::Get().IsKeyDown( VK_LBUTTON, false ) )
				ui->view->webView->InjectMouseUp( kMouseButton_Left );

			if( Input::Get().IsKeyDown( VK_SPACE, true ) )
				sphere->GetIngredient<Rigidbody>()->AddForce( 1.0f, 0.0f, 0.0f );

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

			ui->Update( deltaTime );

			return true;
		}

		void Draw( void )
		{
			//ShaderController::Get().SetAllShadersUniform( "cameraMatrix", cam->transform.Matrix() );
			//ShaderController::Get().SetAllShadersUniform( "projectionMatrix", WindowController::Get().PerspectiveMatrix() );

			ShaderController::Get().GetShader( "texture" ).SetUniform( "cameraMatrix", /*cam->transform.WorldMatrix()*/Matrix::Identity );
			ShaderController::Get().GetShader( "texture" ).SetUniform( "projectionMatrix", WindowController::Get().PerspectiveMatrix() );

			ui->Draw();
		}

		void Shutdown( void )
		{
			delete_s( cam );
		}
	};
}

#endif
