#ifndef _SCRIPTCONTROLLER_H_
#define _SCRIPTCONTROLLER_H_

#include <string>
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>

#include "Script.h"
#include "Input.h"
#include "ConfigController.h"

using namespace std;
using namespace Graphos;
using namespace Awesomium;

namespace Graphos
{
	namespace Content
	{
		class ScriptController
		{
		public:
			bool				Initialize( void );

			Script*				CreateInstanceVariable( string className, GameObject* owner = nullptr );

			static
			ScriptController&	Get( void )
			{
				static ScriptController instance;
				return instance;
			}
		
		private:
								ScriptController( void ) : webCore( nullptr ), webView( nullptr ) { }
								ScriptController( const ScriptController& );
								~ScriptController( void );
			void				operator=( const ScriptController& );

			class MyHandler : public JSMethodHandler
			{
			public:
				MyHandler( ScriptController* owner ) : owner( owner ) { }

				void OnMethodCall( WebView* caller, unsigned int remoteObjId, const WebString& methodName, const JSArray& args );

				JSValue OnMethodCallWithReturnValue( WebView* caller, unsigned int remote_object_id, const WebString& method_name, const JSArray& args );

				ScriptController* owner;
			};

			WebCore*			webCore;
			WebView*			webView;

			MyHandler*			jsHandler;

			JSObject			window;
			JSObject			input;
		};
	}
}

#endif//_SCRIPTCONTROLLER_H_