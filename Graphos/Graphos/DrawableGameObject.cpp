#include "DrawableGameObject.h"

#include <sstream>
#include <vector>

using namespace std;
using namespace Graphos;
using namespace Graphos::Graphics;

void DrawableGameObject::LoadObjectFile( string filePath )
{
	vector<Vector3> vertices;
	vector<Vector2> uvs;
	vector<Vector3> normals;

	vector<unsigned int> indices;
	unsigned int	dataPointer = 0;

	istringstream file( Helpers::ReadFile( filePath ) );
	string line;

	while( getline( file, line ) )
	{
		if( line.substr( 0, 2 ) == "v " )
		{
			Vector3 vertex;
			
			sscanf( line.c_str(), "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z );

			vertices.push_back( vertex );
		}
		else if( line.substr( 0, 2 ) == "vt" )
		{
			Vector2 uv;

			sscanf( line.c_str(), "vt %f %f\n", &uv.x, &uv.y );
			
			uvs.push_back( uv );
		}
		else if( line.substr( 0, 2 ) == "vn" )
		{
			Vector3 normal;

			sscanf( line.c_str(), "vn %f %f %f\n", &normal.x, &normal.y, &normal.z );

			normals.push_back( normal );
		}
		else if( line.substr( 0, 2 ) == "f " )
		{
			unsigned int vertexIndex[ 3 ];

			/* f %d/%d/%d %d/%d/%d %d/%d/%d\n */

			sscanf( line.c_str(), "f %d/%d/%d", &vertexIndex[ 0 ], /*&uvIndex[0], &normalIndex[0],*/ &vertexIndex[ 1 ], /*&uvIndex[1], &normalIndex[1],*/ &vertexIndex[ 2 ]/*, &uvIndex[2], &normalIndex[2]*/ );

			for( int ii = 0; ii < 3; ++ii )
				indices.push_back( vertexIndex[ ii ] );
		}
	}

	// make and bind the VAO
	glGenVertexArrays( 1, &vertexArrayObject );
	glBindVertexArray( vertexArrayObject );

	// make and bind the VBO
	glGenBuffers( 1, &vertexBufferObject );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );

	// Buffer the data
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof( float ), &vertices[ 0 ], GL_STATIC_DRAW);

	// Connect the position to the inputPosition attribute of the vertex shader
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * indices.size(), NULL);
	// Connect color to the inputColor attribute of the vertex shader
	//glEnableVertexAttribArray( 1 );
	//glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * indices.size(), (unsigned char*)( sizeof( float ) * 3 ) );

	// Generate index buffer
	glGenBuffers( 1, &indexBuffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );

	// Buffer index data
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( unsigned int ), &indices[ 0 ], GL_STATIC_DRAW );

	// unbind the VBO and VAO
	glBindBuffer( GL_ARRAY_BUFFER, NULL );
	glBindVertexArray( NULL );
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
	glBindBuffer( GL_ARRAY_BUFFER, NULL );
	glBindVertexArray( NULL );
}

void Graphos::DrawableGameObject::Draw( void )
{
	// Setup shader
	ShaderController::Get().GetShader( shaderName ).Use();
	ShaderController::Get().GetShader( shaderName ).SetUniform( "modelMatrix", transform.Matrix() );
	
	// Bind all of the buffers
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
	glBindVertexArray( vertexArrayObject );

	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
}