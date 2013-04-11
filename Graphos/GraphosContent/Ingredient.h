#ifndef _INGREDIENT_H_
#define _INGREDIENT_H_

namespace Graphos
{
	namespace Content
	{
		class Ingredient
		{
		public:
			virtual bool		Update( void ) = 0;
			virtual void		Draw( void ) = 0;
		};
	}
}

#endif//_INGREDIENT_H_