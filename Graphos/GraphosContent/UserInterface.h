#ifndef __USERINTERFACE
#define __USERINTERFACE

#include <GL/GLIncludes.h>
#include <string>
//#include <Awesomium/WebCore.h>
//#include <Awesomium/STLHelpers.h>
//#include <Awesomium/BitmapSurface.h>

#include "Transform.h"
#include "AwesomiumView.h"
#include "WindowController.h"
#include "ShaderController.h"

#define DEPTH 1.0f

using namespace std;
//using namespace Awesomium;

namespace Graphos
{
	namespace Content
	{
		class UserInterface
		{
		public:
								UserInterface( string url );

			bool				Update( float deltaTime );
			void				Draw( void );

		//private:
			// GL Texture ID
			unsigned int		textureID;

			unsigned int		width;
			unsigned int		height;

			Transform			transform;

			// Awesomium view
			AwesomiumView*		view;

			// GL Mesh data
			unsigned int		vertexBufferObject;
			unsigned int		vertexArrayObject;
			unsigned int		indexBuffer;
			unsigned int		numElements;
		};
	}
}

#endif//__USERINTERFACE