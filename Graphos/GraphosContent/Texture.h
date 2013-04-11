#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
#include <GL/glincludes.h>
#ifdef WIN32
 //#include <Windows.h>
#endif
#include <FreeImage.h>
//#include "OpenGLController.h"
//#include "WindowController.hpp"

#include "Ingredient.h"

namespace Graphos
{
	namespace Content
	{
		class Texture : public Ingredient
		{
		public:
								Texture( void ) { }
								Texture( std::string filePath ) { LoadFromFile( filePath ); }
			
			bool				LoadFromFile( std::string filePath );

			bool				Update( void ) { return true; }
			void				Draw( void );

		private:
			unsigned int		textureID;
			unsigned int		width;
			unsigned int		height;
		};
	}
}

#endif //_TEXTURE_H_