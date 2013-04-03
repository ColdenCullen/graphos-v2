#ifndef _SHADER_CONTROLLER_H_
#define _SHADER_CONTROLLER_H_

// Includes
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <dirent.h>

#include "WindowController.hpp"

using namespace std;

namespace Graphos
{
	namespace Graphics
	{
		class ShaderController
		{
		public:
			#pragma region Shader
			struct Shader
			{
			public:
				unsigned int		vertexShaderID;
				unsigned int		fragmentShaderID;
				unsigned int		programID;

				Shader( void )
					: vertexShaderID( 0 ), fragmentShaderID( 0 ), programID( 0 ) { }
				Shader( unsigned int vertex, unsigned int fragment, unsigned int program )
					: vertexShaderID( vertex ), fragmentShaderID( fragment ), programID( program ) { }

				void				Initialize( string text );

				void				Use( void ) const;
				bool				SetUniform( string name, int value ) const;
				bool				SetUniform( string name, float value ) const;
				bool				SetUniform( string name, Matrix4 value ) const;

			private:
				unordered_map<string, unsigned int>
					uniforms;
			};
			#pragma endregion

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