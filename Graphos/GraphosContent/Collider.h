#ifndef __COLLIDER
#define __COLLIDER

#include "Ingredient.h"
#include "Vector3.h"

using namespace Graphos::Math;
using namespace Graphos::Content;

namespace Graphos
{
	// Enum for what type of collider this is
	enum ColliderType : unsigned char { Sphere, Box };

	class Collider : public Ingredient
	{
	public:
		virtual bool		Update( float deltaTime ) { return true; }
		virtual void		Draw( void ) { }
		virtual void		Shutdown( void ) { }

		GameObject*			Owner( void ) const	{ return owner; }
		const ColliderType	Type( void ) const	{ return type; }
		virtual Vector3		GetFurthestPointInDirection( Vector3& direction ) const = 0;

		Vector3				centerOffset;

		//friend class		Physics;

	protected:
							Collider( ColliderType colliderType, GameObject* owner );

	private:
		ColliderType		type;
	};
}

#endif//__COLLIDER