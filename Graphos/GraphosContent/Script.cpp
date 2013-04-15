#include "Script.h"
#include "GameObject.h"

#include <iostream>

using namespace Graphos::Content;

bool Script::Update( float deltaTime )
{
	if( owner )
	{
		JSObject transform, position;

		position.SetProperty( WSLit( "x" ), JSValue( owner->transform.Position().x ) );
		position.SetProperty( WSLit( "y" ), JSValue( owner->transform.Position().y ) );
		position.SetProperty( WSLit( "z" ), JSValue( owner->transform.Position().z ) );

		transform.SetProperty( WSLit( "position" ), position );

		instance.SetPropertyAsync( WSLit( "transform" ), transform );
	}

	JSArray args;
	args.Push( JSValue( deltaTime ) );

	instance.InvokeAsync( WSLit( "Update" ), args );

	return true;
}