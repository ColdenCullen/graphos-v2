#ifndef _CONFIGCONTROLLER_H_
#define _CONFIGCONTROLLER_H_

#include <string>
#include <json/json.h>

#include "Vector3.h"

using namespace std;
using namespace Graphos::Math;

namespace Graphos
{
	namespace Content
	{
		class Config
		{
		public:
			// Initialize the settings controller
			bool				LoadSettings( void );

			#pragma region GetData
			// Get value from settings
			template<typename T>
			T					GetData( string path );
#if defined( _WIN32 )
			template<>
			int					GetData<int>( string path );
			template<>
			unsigned int		GetData<unsigned int>( string path );
			template<>
			float				GetData<float>( string path );
			template<>
			bool				GetData<bool>( string path );
			template<>
			string				GetData<string>( string path );
			template<>
			const char*			GetData<const char*>( string path );
			template<>
			Vector3				GetData<Vector3>( string path );
#endif
			#pragma endregion

			static Config&		Get( void )
			{
				static Config instance;
				return instance;
			}

		private:
								Config( void ) { }
								Config( const Config& );
			void				operator=( const Config& );

			Json::Value			GetValueAtPath( string path );

			// JSON values
			Json::Value			config;
		};

#pragma region GetData
#if defined( _WIN32 )
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
		template<>
		Vector3	Config::GetData<Vector3>( string path )
		{
			Json::Value root = GetValueAtPath( path );

			return Vector3(
				static_cast<float>( root.get( "x", root ).asDouble() ),
				static_cast<float>( root.get( "y", root ).asDouble() ),
				static_cast<float>( root.get( "z", root ).asDouble() )
			);
		}
#endif
#pragma endregion
	}
}

#endif//_CONFIGCONTROLLER_H_