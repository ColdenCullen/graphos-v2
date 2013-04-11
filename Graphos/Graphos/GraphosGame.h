#ifndef _GRAPHOSGAME_H_
#define _GRAPHOSGAME_H_

#include <ctime>
#include <vector>
#include <algorithm>
#include <string>
#include <json/json.h>

#include "GraphicsController.h"
#include "ContentController.h"
#include "ShaderController.h"
#include "GameObject.h"

using namespace std;

namespace Graphos
{
	using namespace Content;
	using namespace Graphics;

	class GraphosGame
	{
	public:
							~GraphosGame( void );

		void				Run( void );

	protected:
		virtual bool		Initialize( void ) = 0;
		virtual bool		Update( void ) = 0;
		virtual void		Draw( void ) = 0;

		unordered_map<string, GameObject*>
							objects;

		float				deltaTime;

	private:
		void				LoadObjects( void );
	};
}

#endif//_GRAPHOSGAME_H_