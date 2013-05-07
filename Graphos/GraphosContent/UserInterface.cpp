#include "UserInterface.h"

using namespace Graphos::Content;
using namespace Graphos::Graphics;

UserInterface::UserInterface( string url )
{
	char abspath[ 256 ];
#ifdef WIN32
	_fullpath( abspath, url.c_str(), MAX_PATH );
#else
	realpath( url.c_str(), abspath );
#endif

	// Get dimensions
	width = Config::Get().GetData<unsigned int>( "display.width" );
	height = Config::Get().GetData<unsigned int>( "display.height" );

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

	// Scale to fix awesomium issue
	transform.Scale( 1.0f, -1.0f, 1.0f );
}

bool UserInterface::Update( float deltaTime )
{
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