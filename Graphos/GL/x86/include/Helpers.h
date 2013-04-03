#define delete_s(x) if( x != nullptr ) { delete x; x = nullptr; }

#if defined( _USE_READ_FILE )

#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <iostream>
#include <fstream>
#include <sstream>

struct Helpers
{
#ifdef _USE_READ_FILE
	// Reads a file to a string
	static string ReadFile( string fileName )
	{
		ifstream shaderFile( fileName.c_str() );
		if( !shaderFile )
			return NULL;

		stringstream shaderData;
		shaderData << shaderFile.rdbuf();
		shaderFile.close();

		return shaderData.str();
	}
#endif
};

#endif//_HELPERS_H_

#endif