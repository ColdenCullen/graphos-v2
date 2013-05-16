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

}

void Flipper::OnCollision( GameObject* other )
{
	other->GetIngredient<Rigidbody>()->AddForce( other->transform.RotationMatrix() * Vector3( 1.0f, 1.0f, 0.0f ) );
}