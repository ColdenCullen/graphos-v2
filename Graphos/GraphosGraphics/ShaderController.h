#ifndef _SHADER_CONTROLLER_H_
#define _SHADER_CONTROLLER_H_

// Includes
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#ifdef _WIN32
#include <dirent.h>
#endif

#include "WindowController.hpp"
#include "Shader.h"

using namespace std;

namespace Graphos
{
	namespace Graphics
	{
		class ShaderController
		{
		public:
			bool				Initialize();
			Shader&				GetShader( string shaderName );

			static
			ShaderController&	Get( void )
			{
				static ShaderController instance;
				return instance;
			}

		private:
								ShaderController( void ) { }
								ShaderController( const ShaderController& );
			void				operator=( const ShaderController& );

			bool				AddShader( string path, string name );

		public:
			unordered_map<string, Shader>
								shaders;
		};
	}
}

#endif//_SHADER_CONTROLLER_H_