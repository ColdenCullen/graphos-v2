#ifndef __USERINTERFACE
#define __USERINTERFACE

#include <GL/GLIncludes.h>
#include <string>
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
//#include <Awesomium/BitmapSurface.h>

#include "Input.h"
#include "Transform.h"
#include "AwesomiumView.h"
#include "WindowController.h"
#include "ShaderController.h"

#define DEPTH 1.0f

using namespace std;
using namespace Awesomium;

namespace Graphos
{
	class GraphosGame;

	namespace Content
	{
		class UserInterface
		{
		public:
								UserInterface( GraphosGame* owner );
								~UserInterface();

			bool				Update( float deltaTime );
			void				Draw( void );

		private:
			// GL Texture ID
			unsigned int		textureID;

			unsigned int		width;
			unsigned int		height;

			Transform			transform;

			GraphosGame*		owner;

			// Awesomium view
			AwesomiumView*		view;
			JSObject			graphosGame;

			// GL Mesh data
			unsigned int		vertexBufferObject;
			unsigned int		vertexArrayObject;
			unsigned int		indexBuffer;
			unsigned int		numElements;

			//////////////////////////////////////////////////////////////////////////
			// JS Method Handler
			//////////////////////////////////////////////////////////////////////////
			struct JavaScriptHandler : public JSMethodHandler
			{
			public:
								JavaScriptHandler( UserInterface* owner ) : owner( owner ) { }

				void			OnMethodCall( WebView* caller, unsigned int remoteObjectID, const WebString& methodName, const JSArray& args );
				JSValue			OnMethodCallWithReturnValue( WebView* caller, unsigned int remoteObjectID, const WebString& methodName, const JSArray& args );

			private:
				UserInterface*	owner;
			};
		};
	}
}

#endif//__USERINTERFACE