#include "SettingsController.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

#define CONFIG_PATH "../config.json"

using namespace std;
using namespace Graphos::Content;

// Reads a file to a string
string ReadFileSC( string fileName )
{
	ifstream shaderFile( fileName.c_str() );
	if( !shaderFile )
		return NULL;

	stringstream shaderData;
	shaderData << shaderFile.rdbuf();
	shaderFile.close();

	return shaderData.str();
}

bool SettingsController::LoadSettings( void )
{
	Json::Reader reader;

	if( !reader.parse( ReadFileSC( CONFIG_PATH ), config ) )
		return false;

	const char* result = typeid( reader ).name();

	unsigned int height = config.get( "display", "" ).get( "height", "" ).asUInt();

	return true;
}

Json::Value SettingsController::GetValueAtPath( string path )
{
	string left;
	string right = path;
	int currentIndex;
	Json::Value currentValue = config;

	do
	{
		currentIndex = right.find( '/' );

		if( currentIndex != string::npos )
		{
			left = right.substr( 0, currentIndex );
			right = right.substr( currentIndex + 1, string::npos );
		}
		else
		{
			left = right;
		}

		currentValue = currentValue.get( left, NULL );
	} while( currentIndex != string::npos );

	return currentValue;
}