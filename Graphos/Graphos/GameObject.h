#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

// Includes
#include "Transform.h"

namespace Graphos
{
	class GameObject
	{
	public:
		GameObject( void );
		~GameObject( void );

		Transform transform;
		GameObject* parent;
	};
}

#endif //_GAMEOBJECT_H_