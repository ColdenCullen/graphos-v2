#include "Physics.h"

#include <algorithm>
#include "Rigidbody.h"

using namespace Graphos;
using namespace Graphos::Content;

Physics::Physics( void ) : gravity() { }

void Physics::AddCollider( Collider* col )
{
	colliders.push_back( col );
}

void Physics::Update( void )
{
	Vector3 normal;
	bool isColliding;

	// Iterate through each collider
	for( auto outside = begin( colliders ); outside != end( colliders ); ++outside )
	{
		//*
		Collider* insideTemp = GameObject::GetGameObject( "Sphere" )->GetIngredient<Collider>();
		Collider** inside = &insideTemp;
		//*/

		// Iterate through each collider after it
		//for( auto inside = outside + 1; inside != end( colliders ); ++inside )
		if( outside != find( begin( colliders ), end( colliders ), *inside ) )
		{
			// Check for collisions
			if( ( *inside )->Type() == Sphere && ( *outside )->Type() == Sphere )
			{
				// Check if colliding.
				isColliding = ( normal = ( ( *outside )->Owner()->transform.Position() - ( *inside )->Owner()->transform.Position() ) ).Magnitude() <
					static_cast<SphereCollider*>( *outside )->radius + static_cast<SphereCollider*>( *inside )->radius;
			}
			else
			{
				isColliding = CheckGJK( *inside, *outside );
			}
			
			// Act on collisions;
			if( isColliding )
			{
				// Get rigid bodies involved in the collision
				Rigidbody* outsideRB = ( *outside )->Owner()->GetIngredient<Rigidbody>();
				Rigidbody* insideRB = ( *inside )->Owner()->GetIngredient<Rigidbody>();

				// If one object is movable
				if( outsideRB == nullptr || insideRB == nullptr )
				{
					GameObject* movableObj = outsideRB != nullptr ? ( *outside )->Owner() : ( *inside )->Owner();
					GameObject* nonMovable = outsideRB == nullptr ? ( *outside )->Owner() : ( *inside )->Owner();

					//if( movableObj->GetIngredient<Collider>()->Type() == Sphere )
					switch( nonMovable->GetIngredient<Collider>()->Type() )
					{
					case Sphere:
						normal = (
								( movableObj->transform.Position() + movableObj->GetIngredient<Collider>()->centerOffset ) -
								( nonMovable->transform.Position() + nonMovable->GetIngredient<Collider>()->centerOffset )
							).Normalize();
						break;
					case Box:
						normal = Vector3( 1.0f, 0.0f, 0.0f );
						break;
					default:

						break;
					}
					
					Vector3& movVel = movableObj->GetIngredient<Rigidbody>()->linearVelocity;

					if( movVel.Dot( normal ) > 0.0f )
						movVel = ( -2 * movVel.Dot( normal ) * normal + movVel );
				}
				// if both are movable
				else
				{

				}
			}
		}
	}
}

bool Physics::Initialize( void )
{
	gravity = Config::Get().GetData<Vector3>( "physics.gravity" );

	return true;
}

void Physics::Shutdown( void )
{
	gravity = Vector3();
	colliders.clear();
}

Vector3 Physics::Support( Collider* shape1, Collider* shape2, Vector3& direction )
{
	Vector3 p1 = shape1->GetFurthestPointInDirection( direction );
	Vector3 p2 = shape2->GetFurthestPointInDirection( -direction );

	p1.z = 0.0f;
	p2.z = 0.0f;

	return p1 - p2;
}

bool Physics::CheckGJK( Collider* shape1, Collider* shape2 )
{
	Vector3 direction( 1.0f, 0.0f, 0.0f );
	Simplex simplex;

	simplex.Add( Support( shape1, shape2, direction ) );

	direction = -simplex.points[ 0 ];

	while( true )
	{
		simplex.Add( Support( shape1, shape2, direction ) );

		if( simplex.GetLast().Dot( direction ) <= 0.0f )
			return false;
		else if( simplex.ContainsOrigin( direction ) )
			return true;
	}
}

/*const*/ Vector3& Physics::Simplex::GetLast( void )// const
{
	return points[ size - 1 ];
}

void Physics::Simplex::Add( const Vector3& newPoint )
{
	if( size < 4 )
		points[ size++ ] = newPoint;
}

void Physics::Simplex::Remove( const Vector3& target )
{
	bool moveBack = false;

	for( byte ii = 0; ii < 4; ++ii )
	{
		if( points[ ii ] == target )
			moveBack = true;

		if( moveBack && ii < 3 )
			points[ ii ] = points[ ii + 1 ];
	}

	if( moveBack )
		--size;
}

bool Physics::Simplex::ContainsOrigin( Vector3& direction )
{
	Vector3 a = GetLast();
	Vector3 ao = -a;

	if( size == 2 )
	{
		Vector3 ab = points[ 0 ] - a;
		Vector3 abPerp = Vector3::TripleProduct( ab, ao, ab );

		direction = abPerp;
	}
	else if( size == 3 )//4 )
	{
		Vector3 b = points[ 0 ];
		Vector3 c = points[ 1 ];

		Vector3 ab = b - a;
		Vector3 ac = c - a;

		Vector3 abPerp = Vector3::TripleProduct( ac, ab, ab );
		abPerp *= abPerp.Dot( -ac );

		Vector3 acPerp = Vector3::TripleProduct( ab, ac, ac );
		acPerp *= acPerp.Dot( -ab );

		float abDot = abPerp.Dot( ao );
		float acDot = acPerp.Dot( ao );

		if( abPerp.Dot( ao ) > 0.0f )
		{
			Remove( c );
			direction = abPerp;
		}
		else if( acPerp.Dot( ao ) > 0.0f )
		{
			Remove( b );
			direction = acPerp;
		}
		else
		{
			return true;
		}
	}

	return false;
}