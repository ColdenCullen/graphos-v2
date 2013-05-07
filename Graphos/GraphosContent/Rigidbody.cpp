#include "Rigidbody.h"

using namespace Graphos;

Rigidbody::Rigidbody( GameObject* owner ) : Ingredient( owner ), linearVelocity(), angularVelocity(), linearDrag( 0.0f ), angularDrag( 0.0f ) { }

bool Rigidbody::Update( float deltaTime )
{
	// Update velocities with drag
	//linearVelocity *= ( ( 1 - linearDrag ) * deltaTime );
	//angularVelocity *= ( ( 1 - angularDrag ) * deltaTime );	

	// Add gravity
	linearVelocity += Physics::Get().gravity * deltaTime;

	// Update object
	owner->transform.Translate( linearVelocity * deltaTime );
	owner->transform.Rotate( angularVelocity * deltaTime );

	return true;
}

void Rigidbody::Shutdown( void )
{

}

void Rigidbody::AddForce( const Vector3& force )
{
	linearVelocity += force;
}

void Rigidbody::AddForce( float x, float y, float z )
{
	linearVelocity.x += x;
	linearVelocity.y += y;
	linearVelocity.z += z;
}