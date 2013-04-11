#include "DrawableGameObject.h"
/*
using namespace std;
using namespace Graphos;
using namespace Graphos::Graphics;

void DrawableGameObject::LoadObjectFile( string filePath )
{
	model.LoadFromObjFile( filePath );
}

void DrawableGameObject::Draw( void )
{
	// Setup shader
	shader.Use();
	shader.SetUniform( "modelMatrix", transform.Matrix() );
	shader.SetUniform( "shaderTexture", 0 );
	
	material.Draw();
	model.Draw();

	//glBindTexture( GL_TEXTURE_2D, NULL );
	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, NULL );
	//glBindVertexArray( NULL );
}

void DrawableGameObject::InitMaterial( string filePath )
{
	material.LoadFromFile( filePath.c_str() );
}
*/