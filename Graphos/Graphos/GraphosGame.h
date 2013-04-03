#ifndef _GRAPHOSGAME_H_
#define _GRAPHOSGAME_H_

#include "GraphicsController.h"
#include "Camera.h"

namespace Graphos
{
	using namespace Content;
	using namespace Graphics;

	class GraphosGame
	{
	public:
		void					Run( void );

	protected:
		virtual bool			Initialize( void ) = 0;
		virtual bool			Update( void ) = 0;
		virtual void			Draw( void ) = 0;
	};
}

#endif//_GRAPHOSGAME_H_