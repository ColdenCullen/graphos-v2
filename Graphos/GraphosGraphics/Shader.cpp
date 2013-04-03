#include "stdafx.h"
#include "ShaderController.h"

#define MIN(x,y) (x < y ? x : y)

using namespace std;
using namespace Graphos::Graphics;

void ShaderController::Shader::Initialize( string text )
{
	// Init uniform values
	int currentLocation = text.find( "uniform " );

	while( currentLocation != string::npos )
	{
		int start = text.find( " ", currentLocation + 8 ) + 1;
		string uniformName = text.substr( start, MIN( text.find( ";", start + 1 ), text.find( " ", start + 1 ) ) - start );

		uniforms[ uniformName ] = glGetUniformLocation( programID, uniformName.c_str() );

		currentLocation = text.find( "uniform ", start );
	}

	// Init in values
	currentLocation = text.find( "in " );
	int counter = 0;

	while( currentLocation != string::npos )
	{
		int start = text.find( " ", currentLocation + 3 ) + 1;
 		string inName = text.substr( start, MIN( text.find( ";", start + 1 ), text.find( " ", start + 1 ) ) - start );

		glBindAttribLocation( programID, counter, inName.c_str() );

		currentLocation = text.find( "in ", start );

		++counter;
	}
}


void ShaderController::Shader::Use( void ) const
{
	glUseProgram( programID );
}

bool ShaderController::Shader::SetUniform( string name, int value ) const
{
	if( uniforms.find( name ) != uniforms.end() && uniforms.at( name ) != -1 )
		glUniform1i( uniforms.at( name ), value );
	else
		return false;

	return true;
}

bool ShaderController::Shader::SetUniform( string name, float value ) const
{
	if( uniforms.find( name ) != uniforms.end() && uniforms.at( name ) != -1 )
		glUniform1f( uniforms.at( name ), value );
	else
		return false;

	return true;
}

bool ShaderController::Shader::SetUniform( string name, Matrix4 value ) const
{
	if( uniforms.find( name ) != uniforms.end() && uniforms.at( name ) != -1 )
		glUniformMatrix4fv( uniforms.at( name ), 1, false, value.matrix );
	else
		return false;

	return true;
}