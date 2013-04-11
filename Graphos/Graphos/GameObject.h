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

using namespace std;

namespace Graphos
{
	using namespace Graphics;

	namespace Content
	{
		const class GameObject
		{
		public:
								GameObject( void ) : shader( Shader() ) { }
								GameObject( Shader& shader ) : shader( shader ) { }
	
			bool				Update( void );
			void				Draw( void );
	
			template<class T>
			typename enable_if<is_base_of<Ingredient, T>::value, void>::type
								AddIngredient( T* newIngredient )
			{
				recipe[ typeid(T).hash_code() ] = newIngredient;
			}

			Shader&				GetShader( void ) const { return shader; }
			void				SetShader( string newName ) { shader = ShaderController::Get().GetShader( newName ); }
	
			Transform			transform;
			GameObject*			parent;
	
		private:
			unordered_map<size_t, Ingredient*>
								recipe;
			Shader&				shader;
		};
	}
}

#endif //_GAMEOBJECT_H_