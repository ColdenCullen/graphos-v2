#include <iostream>

#include "ScriptController.h"

#define _USE_READ_FILE
#include "Helpers.h"

using namespace std;
using namespace Awesomium;
using namespace Graphos::Content;
using namespace Graphos::Graphics;

Graphos::Content::ScriptController::~ScriptController( void )
{
	//delete window;

	if( WebCore::instance() )
		WebCore::Shutdown();

	delete jsHandler;
}

bool ScriptController::Initialize( void )
{
	// Initialize Awesomium
	if( WebCore::instance() )
		webCore = WebCore::instance();
	else
	{
		WebConfig config;

		//config.log_level = kLogLevel_Verbose;
		//config.log_path = WSLit( "D:/Awesomium.log" );

		webCore = WebCore::Initialize( config );
	}

	// Get file path
	char abspath[ 256 ];
#ifdef WIN32
	_fullpath( abspath, ConfigController::Get().GetData<string>( "scripts.indexPath" ).c_str(), MAX_PATH );
#else
	realpath( filePath.c_str(), abspath );
#endif

	webView = webCore->CreateWebView( 800, 600 );
	webView->LoadURL( WebURL( WSLit( abspath ) ) );

	jsHandler = new MyHandler( this );

	webView->set_js_method_handler( jsHandler );

	while( webView->IsLoading() )
		webCore->Update();

	webCore->Update();

	// Get window, default scope
	window = webView->ExecuteJavascriptWithResult( WSLit( "window" ), WSLit( "" ) ).ToObject();

	// Reassign console.log so that it outputs through the console
	window.GetProperty( WSLit( "console" ) ).ToObject().SetCustomMethod( WSLit( "log" ), false );

	// Assign Input.IsKeyDown
	webView->CreateGlobalJavascriptObject( WSLit( "Input" ) );
	input = window.GetProperty( WSLit( "Input" ) ).ToObject();
	input.SetCustomMethod( WSLit( "IsKeyDown" ), true );

	return true;
}

Script* ScriptController::CreateInstanceVariable( string className, GameObject* owner /*= nullptr */ )
{
	if( webView )
	{
		JSValue newInstance = webView->ExecuteJavascriptWithResult( WSLit( string( "new " ).append( className ).append( "()" ).c_str() ), WSLit( "" ) );

		if( newInstance.IsObject() )
		{
			webView->CreateGlobalJavascriptObject( WSLit( className.c_str() ) );
			window.SetProperty( WSLit( className.c_str() ), newInstance.ToObject() );
			return new Script( window.GetProperty( WSLit( className.c_str() ) ).ToObject(), owner );
		}
		else
			return nullptr;
	}
	else
		return nullptr;
}

void ScriptController::MyHandler::OnMethodCall( WebView* caller, unsigned int remoteObjId, const WebString& methodName, const JSArray& args )
{
	if( methodName == WSLit( "log" ) )
	{
		if( args.size() )
		{
			cout << args[ 0 ].ToString();
	
			for( unsigned int ii = 1; ii < args.size(); ++ii )
				cout << ", " << args[ ii ].ToString();
		}

		cout << endl;
	}
}

JSValue ScriptController::MyHandler::OnMethodCallWithReturnValue( WebView* caller, unsigned int remoteObjectId, const WebString& methodName, const JSArray& args )
{
	if( remoteObjectId == owner->input.remote_id() && methodName == WSLit( "IsKeyDown" ) && args.size() )
	{
		if( args[ 0 ].IsInteger() )
			return JSValue( Input::Get().IsKeyDown( args[ 0 ].ToInteger() ) );
	}

	return JSValue::Undefined();
}