#ifndef _AWESOMIUM_H_
#define _AWESOMIUM_H_

#include <GL/glincludes.h>
#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

#include "Ingredient.h"
#include "ConfigController.hpp"

using namespace Awesomium;

namespace Graphos
{
	namespace Content
	{
		class AwesomiumView : public Ingredient
		{
		public:
			AwesomiumView( void );
			~AwesomiumView( void );

			bool				Update( void );
			void				Draw( void );

			unsigned int		textureThing;

		private:
			WebCore*			webCore;
			WebView*			webView;
			BitmapSurface*		surface;

			unsigned char*		buffer;
		};
	}
}

#endif//_AWESOMIUM_H_