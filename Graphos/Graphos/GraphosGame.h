#ifndef _GRAPHOSGAME_H_
#define _GRAPHOSGAME_H_

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

using namespace std;

namespace Graphos
{
	class GraphosGame
	{
	public:
		void				Run( void );

	protected:
		virtual bool		Initialize( void ) = 0;
		virtual bool		Update( float deltaTime ) = 0;
		virtual void		Draw( void ) = 0;
		virtual void		Shutdown( void ) = 0;

		unordered_map<unsigned int, GameObject>*
							objects;

		float				deltaTime;

		void				LoadObjects( void );
		void				DeleteObjects( void );
		void				Reset( void );
	};
}

#endif//_GRAPHOSGAME_H_