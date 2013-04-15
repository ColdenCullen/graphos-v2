#ifndef _INGREDIENT_H_
#define _INGREDIENT_H_

namespace Graphos
{
	class GameObject;

	namespace Content
	{
		class Ingredient
		{
		public:
								Ingredient( GameObject* owner = nullptr ) : owner( owner ) { }

			virtual bool		Update( float deltaTime ) = 0;
			virtual void		Draw( void ) = 0;
			virtual void		Shutdown( void ) = 0;

		protected:
			GameObject* owner;
		};
	}
}

#endif//_INGREDIENT_H_