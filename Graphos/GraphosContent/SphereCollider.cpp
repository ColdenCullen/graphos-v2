#include "SphereCollider.h"
#include "GameObject.h"

using namespace Graphos;

SphereCollider::SphereCollider( GameObject* owner ) : Collider( Sphere, owner ) { }

Vector3 SphereCollider::GetFurthestPointInDirection( Vector3& direction ) const
{
	return owner->transform.Position() + centerOffset + ( direction.Normalize() * radius );
}