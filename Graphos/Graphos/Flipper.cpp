#include "Flipper.h"
#include "Mesh.h"
#include "Texture.h"
#include "AssetController.h"
#include "Rigidbody.h"
#include "BoxCollider.h"

using namespace Graphos;
using namespace Graphos::Content;

Flipper::Flipper( Shader* shader ) : GameObject( shader )
{
	AddIngredient<Texture>( AssetController::Get().GetContent<Texture>( "" ) );
	AddIngredient<Mesh>( AssetController::Get().GetContent<Mesh>( "" ) );
	AddIngredient<BoxCollider>( new BoxCollider( this ) );
}

void Flipper::OnCollision( GameObject* other )
{
	other->GetIngredient<Rigidbody>()->AddForce( other->transform.RotationMatrix() * Vector3( 1.0f, 1.0f, 0.0f ) );
}