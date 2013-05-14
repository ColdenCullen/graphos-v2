#include "Flipper.h"
#include "Mesh.h"
#include "Texture.h"
#include "AssetController.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "Physics.h"

using namespace Graphos;
using namespace Graphos::Content;

Flipper::Flipper( Shader* shader ) : GameObject( shader )
{
	AddIngredient<Texture>( AssetController::Get().GetContent<Texture>( "FlipperTexture" ) );
	AddIngredient<Mesh>( AssetController::Get().GetContent<Mesh>( "Flipper" ) );

	BoxCollider* col = new BoxCollider( this );
	col->size.x = 0.2f;
	col->size.y = 0.1f;
	col->size.z = 0.1f;
	AddIngredient<Collider>( static_cast<Collider*>( col ) );
	Physics::Get().AddCollider( col );

	transform.Rotate( 90.0f, 0.0f, 0.0f );
	transform.Translate( 0.0f, -0.5f, 0.0f );
}

void Flipper::OnCollision( GameObject* other )
{
	other->GetIngredient<Rigidbody>()->AddForce( other->transform.RotationMatrix() * Vector3( 1.0f, 1.0f, 0.0f ) );
}