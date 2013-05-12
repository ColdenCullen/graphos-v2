#include "UserInterface.h"
#include "GraphosGame.h"

using namespace Graphos;
using namespace Graphos::Content;
using namespace Graphos::Graphics;

UserInterface::UserInterface( GraphosGame* owner ) : owner( owner )
{
	char abspath[ 256 ];
#ifdef WIN32
	_fullpath( abspath, Config::Get().GetData<string>( "ui.filePath" ).c_str(), MAX_PATH );
#else
	realpath( url.c_str(), abspath );
#endif

	// Get dimensions
	width = Config::Get().GetData<unsigned int>( "display.width" ) * Config::Get().GetData<float>( "ui.scale.x" );
	height = Config::Get().GetData<unsigned int>( "display.height" ) * Config::Get().GetData<float>( "ui.scale.y" );

	// Generate mesh
	numElements = 6;
	unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };

	GLfloat floatWidth = static_cast<GLfloat>( width );
	GLfloat floatHeight = static_cast<GLfloat>( height );;

	GLfloat vertices[] = {
		-floatWidth / 2.0f,	floatHeight / 2.0f,	DEPTH, 0.0f, 1.0f,
		-floatWidth / 2.0f,	-floatHeight / 2.0f,DEPTH, 0.0f, 0.0f,
		floatWidth / 2.0f,	-floatHeight / 2.0f,DEPTH, 1.0f, 0.0f,
		floatWidth / 2.0f,	floatHeight / 2.0f,	DEPTH, 1.0f, 1.0f
	};

	// Setup GL buffers
	glGenVertexArrays( 1, &vertexArrayObject );

	glBindVertexArray( vertexArrayObject );

	glGenBuffers( 1, &vertexBufferObject );

	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );
	glBufferData( GL_ARRAY_BUFFER, 6/*4*/ * 5 * sizeof( GLfloat ), vertices, GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );// Position
	glEnableVertexAttribArray( 1 );// UV

	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );
	glVertexAttribPointer( 0, 3, GL_FLOAT, false, 5 * sizeof( GLfloat ), 0 );

	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );
	glVertexAttribPointer( 1, 2, GL_FLOAT, false, 5 * sizeof( GLfloat ), (unsigned char*)NULL + ( 3 * sizeof( GLfloat ) ) );

	glGenBuffers( 1, &indexBuffer );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, numElements * sizeof( unsigned int ), indices, GL_STATIC_DRAW );

	view = new AwesomiumView( abspath, width, height );
	view->webView->set_js_method_handler( new JavaScriptHandler( this ) );

	graphosGame = view->webView->CreateGlobalJavascriptObject( WSLit( "GraphosGame" ) ).ToObject();
	graphosGame.SetCustomMethod( WSLit( "ChangeState" ), false );
	graphosGame.SetCustomMethod( WSLit( "SetConfig" ), false );
	graphosGame.SetCustomMethod( WSLit( "Reset" ), false );

	// Scale to fix awesomium issue
	transform.Scale( 1.0f, -1.0f, 1.0f );
}

UserInterface::~UserInterface()
{
	view->Shutdown();
	delete view;
}

bool UserInterface::Update( float deltaTime )
{
	Point cursor = Input::Get().GetMousePos();
	view->webView->InjectMouseMove( cursor.x, cursor.y );

	if( Input::Get().IsKeyDown( VK_LBUTTON, false ) )
		view->webView->InjectMouseDown( kMouseButton_Left );
	else
		view->webView->InjectMouseUp( kMouseButton_Left );

	view->Update( deltaTime );

	return true;
}

void UserInterface::Draw( void )
{
	ShaderController::Get().GetShader( "texture" ).Use();
	ShaderController::Get().GetShader( "texture" ).SetUniform( "modelMatrix", transform.WorldMatrix() );
	ShaderController::Get().GetShader( "texture" ).SetUniform( "shaderTexture", 0 );
	ShaderController::Get().GetShader( "texture" ).SetUniform( "projectionMatrix", WindowController::Get().OrthogonalMatrix() );

	view->Draw();

	// Bind and draw buffer
	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
	glBindVertexArray( vertexArrayObject );

	glDrawElements( GL_TRIANGLES, numElements, GL_UNSIGNED_INT, NULL );

	ShaderController::Get().GetShader( "texture" ).SetUniform( "projectionMatrix", WindowController::Get().PerspectiveMatrix() );
}

void UserInterface::JavaScriptHandler::OnMethodCall( WebView* caller, unsigned int remoteObjectID, const WebString& methodName, const JSArray& args )
{
	// If called on GraphosGame
	if( remoteObjectID == owner->graphosGame.remote_id() )
	{
		if( methodName == WSLit( "ChangeState" ) && args.size() == 1 )
		{
			if( args[ 0 ].ToString() == WSLit( "Game" ) )
				owner->owner->ChangeState( Game );
			else if( args[ 0 ].ToString() == WSLit( "Menu" ) )
				owner->owner->ChangeState( Menu );
		}
		else if( methodName == WSLit( "SetConfig" ) && args.size() == 2 )
		{
			if( args[ 0 ].IsBoolean() )
				Config::Get().SetData( ToString( args[ 0 ].ToString() ), args[ 1 ].ToBoolean() );
			else if( args[ 0 ].IsInteger() )
				Config::Get().SetData( ToString( args[ 0 ].ToString() ), args[ 1 ].ToInteger() );
			else if( args[ 0 ].IsDouble() )
				Config::Get().SetData( ToString( args[ 0 ].ToString() ), static_cast<float>( args[ 1 ].ToDouble() ) );
			else if( args[ 0 ].IsString() )
				Config::Get().SetData( ToString( args[ 0 ].ToString() ), ToString( args[ 1 ].ToString() ) );
		}
		else if( methodName == WSLit( "Reset" ) && args.size() == 0 )
		{
			owner->owner->Reset();
		}
	}
}

JSValue UserInterface::JavaScriptHandler::OnMethodCallWithReturnValue( WebView* caller, unsigned int remoteObjectID, const WebString& methodName, const JSArray& args )
{
	return JSValue::Undefined();
}