#define delete_s(x) if( x != nullptr ) { delete x; x = nullptr; }

#if defined( _USE_READ_FILE ) || defined( _USE_SCAN_DIR )

#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <dirent.h>

using namespace std;

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
#ifdef _USE_SCAN_DIR
	static unordered_map<string, string> ScanDir( string dirPath )
	{
		unordered_map<string, string> files;

		DIR* dir;
		dirent* ent;
		// Open directory
		if( ( dir = opendir( dirPath.c_str() ) ) != NULL )
		{
			// Iterate through contents
			while( ( ent = readdir( dir ) ) != NULL )
			{
				if( ent->d_namlen > 4 )
					files[ string( ent->d_name ).substr( 0, ent->d_namlen - 4 ) ] = string( ent->d_name ).substr( ent->d_namlen - 4 );
			}

			// Close dir
			closedir( dir );
		}

		return files;
	}
#endif
};

#endif//_HELPERS_H_

#endif