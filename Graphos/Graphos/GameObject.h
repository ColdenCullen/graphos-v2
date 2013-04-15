#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

// Includes
#include <string>
#include <unordered_map>
#include <type_traits>

#include "ShaderController.h"
#include "Ingredient.h"
#include "Transform.h"
#include "Shader.h"
#include "Script.h"
#include "AwesomiumView.h"

using namespace std;
using namespace Graphos::Content;
using namespace Graphos::Graphics;

namespace Graphos
{
	const class GameObject
	{
	public:
		GameObject( void ) : shader( nullptr ) { }
		GameObject( Shader* shader ) : shader( shader ) { }

		void				Shutdown( void );

		bool				Update( float deltaTime );
		void				Draw( void );

		template<class T>
		typename enable_if<is_base_of<Ingredient, T>::value, void>::type
			AddIngredient( T* newIngredient )
		{
			recipe[ typeid(T).hash_code() ] = newIngredient;
		}

		Shader&				GetShader( void ) const { return *shader; }
		void				SetShader( string newName ) { shader = &( ShaderController::Get().GetShader( newName ) ); }

		Transform			transform;

	private:
		unordered_map<size_t, Ingredient*>
							recipe;

		Shader*				shader;
	};
}

#endif//_GAMEOBJECT_H_