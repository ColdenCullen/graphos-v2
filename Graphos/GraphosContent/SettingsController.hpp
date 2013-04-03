#ifndef _SETTINGSCONTROLLER_H_
#define _SETTINGSCONTROLLER_H_

#include <string>
#include <json\json.h>

using namespace std;

namespace Graphos
{
	namespace Content
	{
		class SettingsController
		{
		public:
			// Initialize the settings controller
			bool				LoadSettings( void );

#pragma region GetData
			// Get value from settings
			template<typename T>
			T					GetData( string path ) { }
			template<>
			int					GetData<int>( string path );
			template<>
			unsigned int		GetData<unsigned int>( string path );
			template<>
			double				GetData<double>( string path );
			template<>
			bool				GetData<bool>( string path );
			template<>
			string				GetData<string>( string path );
#pragma endregion

			static
			SettingsController&	Get( void )
			{
				static SettingsController instance;
				return instance;
			}

		private:
								SettingsController( void ) { }
								SettingsController( SettingsController& );
			void				operator=( SettingsController& );

			Json::Value			GetValueAtPath( string path );

			// JSON values
			Json::Value config;
		};

#pragma region GetData
		template<>
		int SettingsController::GetData<int>( string path )
		{
			return GetValueAtPath( path ).asInt();
		}
		template<>
		unsigned int SettingsController::GetData<unsigned int>( string path )
		{
			return GetValueAtPath( path ).asUInt();
		}
		template<>
		double SettingsController::GetData<double>( string path )
		{
			return GetValueAtPath( path ).asDouble();
		}
		template<>
		bool SettingsController::GetData<bool>( string path )
		{
			return GetValueAtPath( path ).asBool();
		}
		template<>
		string SettingsController::GetData<string>( string path )
		{
			return GetValueAtPath( path ).asString();
		}
#pragma endregion
	}
}

#endif//_SETTINGSCONTROLLER_H_