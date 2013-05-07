#include "Config.h"

#define _USE_READ_FILE
#include <Helpers.h>

#define CONFIG_PATH "Resources/Config/Config.json"

using namespace std;
using namespace Graphos::Content;

bool Config::LoadSettings( void )
{
	Json::Reader reader;

	if( !reader.parse( Helpers::ReadFile( CONFIG_PATH ), config ) )
		return false;

	return true;
}

Json::Value Config::GetValueAtPath( string path )
{
	string left;
	string right = path;
	int currentIndex;
	Json::Value currentValue = config;

	do
	{
		currentIndex = right.find( '.' );

		if( currentIndex != string::npos )
		{
			left = right.substr( 0, currentIndex );
			right = right.substr( currentIndex + 1, string::npos );
		}
		else
		{
			left = right;
		}

		currentValue = currentValue.get( left, currentValue );
	} while( currentIndex != string::npos );

	return currentValue;
}

#pragma region GetData
#if defined( __APPLE__ )
template<>
int Config::GetData<int>( string path )
{
	return GetValueAtPath( path ).asInt();
}
template<>
unsigned int Config::GetData<unsigned int>( string path )
{
	return GetValueAtPath( path ).asUInt();
}
template<>
float Config::GetData<float>( string path )
{
	return static_cast<float>( GetValueAtPath( path ).asDouble() );
}
template<>
bool Config::GetData<bool>( string path )
{
	return GetValueAtPath( path ).asBool();
}
template<>
string Config::GetData<string>( string path )
{
	return GetValueAtPath( path ).asString();
}
template<>
const char* Config::GetData<const char*>( string path )
{
	return GetValueAtPath( path ).asCString();
}
#endif
#pragma endregion