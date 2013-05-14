#ifndef __FLIPPER
#define __FLIPPER

#include "GameObject.h"

namespace Graphos
{
	class Flipper : public GameObject
	{
	public:
							Flipper( Shader* shader );

		void				OnCollision( GameObject* other );
	};
}

#endif//__FLIPPER