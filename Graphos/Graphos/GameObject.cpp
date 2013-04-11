#include "GameObject.h"
#include <algorithm>

using namespace Graphos::Content;

bool GameObject::Update( void )
{
	bool result = true;

	for_each(
		begin( recipe ),
		end( recipe ),
		[ &result ]( pair<size_t, Ingredient*> ingredient )
		{
			if( !ingredient.second->Update() )
				result = false;
		}
	);

	return result;
}

void GameObject::Draw( void )
{
	shader.Use();
	shader.SetUniform( "modelMatrix", transform.Matrix() );
	shader.SetUniform( "shaderTexture", 0 );

	for_each(
		begin( recipe ),
		end( recipe ),
		[]( pair<size_t, Ingredient*> ingredient )
		{
			ingredient.second->Draw();
		}
	);
}