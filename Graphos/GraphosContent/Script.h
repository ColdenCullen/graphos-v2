#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <string>
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>

#include "Ingredient.h"

using namespace std;
using namespace Awesomium;

namespace Graphos
{
	namespace Content
	{
		class Script : public Ingredient
		{
		public:
								Script( JSObject& instance, GameObject* owner = nullptr ) : instance( instance ), Ingredient( owner ) { }

			bool				Update( float deltaTime );
			void				Draw( void ) { }
			void				Shutdown( void ) { }

		private:
			JSObject			instance;
		};
	}
}

#endif//_SCRIPT_H_