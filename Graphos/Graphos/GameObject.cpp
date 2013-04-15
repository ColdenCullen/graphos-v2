#include "GameObject.h"

using namespace Graphos;

bool GameObject::Update( float deltaTime )
{
	bool result = true;

	for( auto ingredient = begin( recipe ); ingredient != end( recipe ); ++ingredient )
		if( !ingredient->second->Update( deltaTime ) )
			result = false;

	return result;
}

void GameObject::Draw( void )
{
	shader->Use();
	shader->SetUniform( "modelMatrix", transform.WorldMatrix() );
	shader->SetUniform( "shaderTexture", 0 );

	for( auto ingredient = begin( recipe ); ingredient != end( recipe ); ++ingredient )
		ingredient->second->Draw();
}

void GameObject::Shutdown( void )
{
	for( auto ingredient = begin( recipe ); ingredient != end( recipe ); ++ingredient )
		if( dynamic_cast<AwesomiumView*>( ingredient->second ) || dynamic_cast<Script*>( ingredient->second ) )
		{
			ingredient->second->Shutdown();
			delete ingredient->second;
		}

	recipe.clear();
}