#ifndef __SPHERE_COLLIDER
#define __SPHERE_COLLIDER

#include "Collider.h"

using namespace Graphos::Content;

namespace Graphos
{
	class SphereCollider : public Collider
	{
	public:
							SphereCollider( GameObject* owner );

		bool				Update( float deltaTime ) { return true; }
		void				Draw( void ) { }
		void				Shutdown( void ) { }

		Vector3				GetFurthestPointInDirection( Vector3& direction ) const;

		float				radius;
	};
}

#endif//__SPHERE_COLLIDER