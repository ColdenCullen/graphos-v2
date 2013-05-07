#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "ShaderController.h"
#include "GameObject.h"
#include "Ingredient.h"
#include "Matrix.h"

using namespace Graphos;

namespace Graphos
{
	namespace Content
	{
		class Camera : public Ingredient
		{
		public:
								Camera( GameObject* owner );
			
			bool				Update( void );
			void				Draw( void );
			void				Shutdown( void );

		private:
			Matrix				viewMatrix;
		};
	}
}

#endif//_CAMERA_H_