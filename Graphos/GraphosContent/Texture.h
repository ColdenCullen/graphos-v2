#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <GL/glincludes.h>
#ifdef WIN32
 #include <Windows.h>
#endif
#include <FreeImage.h>
//#include "OpenGLController.h"
//#include "WindowController.hpp"

namespace Graphos
{
	namespace Content
	{
		class Texture
		{
		public:
			bool				LoadFromFile( const char* filePath );
			void				Bind( void );

		private:
			unsigned int		textureID;
			int					width, height;
		};
	}
}

#endif //_TEXTURE_H_