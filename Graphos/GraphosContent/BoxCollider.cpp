#include "BoxCollider.h"

using namespace Graphos;

BoxCollider::BoxCollider( GameObject* owner ) : Collider( Box, owner ) { }

const Vector3 BoxCollider::GetFurthestPointInDirection( const Vector3& direction ) const
{
	const Matrix rotationMarix = owner->transform.RotationMatrix();

	Vector3 newDir = rotationMarix.Inverse() * direction;

	Vector3 point(
		( newDir.x > 0 ? 0.5f : -0.5f ) * size.x,
		( newDir.y > 0 ? 0.5f : -0.5f ) * size.y,
		( newDir.z > 0 ? 0.5f : -0.5f ) * size.z
	);

	Vector3 rotatedPoint = ( rotationMarix * point );

	Vector3 finalPoint = owner->transform.Position() + centerOffset + rotatedPoint;

	return owner->transform.Position() + centerOffset + ( rotationMarix * point );
}