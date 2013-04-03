#include "DrawableGameObject.h"

using namespace Graphos;
using namespace Graphos::Graphics;

void DrawableGameObject::LoadObjectFile( string filePath )
{

}

void DrawableGameObject::BufferData( GLfloat vertexData[] )
{
	GLfloat vertexData2[] = {
		//  X     Y     Z	  R	    G     B
		-0.5f, 0.5f, 2.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f, 2.0f, 0.0f, 1.0f, 0.0f,
		0.5f,-0.5f, 2.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 2.0f, 1.0f, 0.0f, 1.0f
	};

	GLuint indices[] = { 0, 1, 2, 0, 2, 3 };

	// make and bind the VAO
	glGenVertexArrays( 1, &vertexArrayObject );
	glBindVertexArray( vertexArrayObject );

	// make and bind the VBO
	glGenBuffers( 1, &vertexBufferObject );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );

	// Buffer the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData2), vertexData2, GL_STATIC_DRAW);

	// Connect the position to the inputPosition attribute of the vertex shader
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * 6, NULL);
	// Connect color to the inputColor attribute of the vertex shader
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * 6, (unsigned char*)( sizeof( float ) * 3 ) );

	// Generate index buffer
	glGenBuffers( 1, &indexBuffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );

	// Buffer index data
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof( unsigned int ), indices, GL_STATIC_DRAW );

	// unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Graphos::DrawableGameObject::Draw( void )
{
	// Setup shader
	ShaderController::Get().GetShader( shaderName ).Use();
	ShaderController::Get().GetShader( shaderName ).SetUniform( "modelMatrix", transform.getMatrix() );
	
	// Bind all of the buffers
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
	glBindVertexArray( vertexArrayObject );

	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
}