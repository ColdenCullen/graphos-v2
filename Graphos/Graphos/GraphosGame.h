#ifndef __GRAPHOS_GAME
#define __GRAPHOS_GAME

#include <ctime>
#include <vector>
#include <algorithm>
#include <string>
#include <json/json.h>

#include "GraphicsController.h"
#include "AssetController.h"
#include "ShaderController.h"
#include "AwesomiumView.h"
#include "GameObject.h"
#include "ScriptController.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Physics.h"
#include "UserInterface.h"

using namespace std;

namespace Graphos
{
	enum GameState { Menu, Game };

	class GraphosGame
	{
	public:
		void				Run( void );
		void				ChangeState( GameState newState ) { currentState = newState; }

	protected:
		virtual bool		Initialize( void ) = 0;
		virtual bool		Update( float deltaTime ) = 0;
		virtual void		Draw( void ) = 0;
		virtual void		Shutdown( void ) = 0;

		unordered_map<unsigned int, GameObject>*
							objects;

		bool				objectsLoaded;
		GameState			currentState;
		float				deltaTime;
		UserInterface*		ui;

		void				LoadObjects( void );
		void				DeleteObjects( void );
		void				Reset( void );

	private:
		bool				Start( void );
		void				Stop( void );
	};
}

#endif//__GRAPHOS_GAME