#include "BoxCollider.h"
#include "GameObject.h"

using namespace Graphos;

BoxCollider::BoxCollider( GameObject* owner ) : Collider( Box, owner ) { }

Vector3 BoxCollider::GetFurthestPointInDirection( Vector3& direction ) const
{
	return owner->transform.Position() + centerOffset + Vector3(
		( direction.x > 0 ? 0.5f : -0.5f ) * size.x,
		( direction.y > 0 ? 0.5f : -0.5f ) * size.y,
		( direction.z > 0 ? 0.5f : -0.5f ) * size.z
	);
}