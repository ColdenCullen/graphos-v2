#include "StdAfx.h"
#include "ShaderController.h"

using namespace std;
using namespace Graphos::Graphics;

#pragma region Helper Methods
void OutputShaderErrorMessage( HWND hwnd, unsigned int shaderId, const char* shaderFilename )
{
	int logSize, i;
	char* infoLog;
	ofstream fout;
	wchar_t newString[128];
	unsigned int error, convertedChars;

	// Get the size of the string containing the information log for the failed shader compilation message.
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	// Create a char buffer to hold the info log.
	infoLog = new char[logSize];
	if(!infoLog)
	{
		return;
	}

	// Now retrieve the info log.
	glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for(i=0; i<logSize; i++)
	{
		fout << infoLog[i];
	}

	// Close the file.
	fout.close();

	// Convert the shader filename to a wide character string.
	error = mbstowcs_s(&convertedChars, newString, 128, shaderFilename, 128);
	if(error != 0)
	{
		return;
	}

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", newString, MB_OK);

	delete[] infoLog;

	return;
}

string ReadFile( string fileName )
{
	ifstream shaderFile( fileName.c_str() );
	if( !shaderFile )
		return NULL;

	stringstream shaderData;
	shaderData << shaderFile.rdbuf();
	shaderFile.close();

	return shaderData.str();
}
#pragma endregion

bool ShaderController::Initialize( void )
{
	char abspath[ MAX_PATH ];
#ifdef WIN32
	_fullpath( abspath, "Resources\\Shaders\\", MAX_PATH );
#else
	realpath( "Resources\\Shaders\\", abspath );
#endif

	DIR* dir;
	struct dirent* ent;
	// Open directory
	if( ( dir = opendir( abspath ) ) != NULL )
	{
		// Iterate through contents
		while( ( ent = readdir( dir ) ) != NULL )
		{
			if( ent->d_namlen > 5 && ent->d_name[ ent->d_namlen - 5 ] == 'f' )
			{
				string name = string( ent->d_name ).substr( 0, ent->d_namlen - 6 );

				if( !AddShader( abspath, name ) )
					return false;
			}
		}

		// Close dir
		closedir( dir );

		return true;
	}
	else
	{
		return false;
	}
}

ShaderController::Shader& ShaderController::GetShader( string shaderName )
{
	return shaders.at( shaderName );
}

bool ShaderController::AddShader( string path, string name )	
{
	int nameLength = path.length() + name.length() + 6;
	// Load shader text
	string vertexShaderBuffer = ReadFile( path + name + ".vs.sl" );
	string fragmentShaderBuffer = ReadFile( path + name + ".fs.sl" );
	int vertexShaderLength = vertexShaderBuffer.size();
	int fragmentShaderLength = fragmentShaderBuffer.size();

	// If text is valid
	if( !vertexShaderBuffer.empty() && !fragmentShaderBuffer.empty() )
	{
		unsigned int vertex = glCreateShader( GL_VERTEX_SHADER );
		unsigned int frag = glCreateShader( GL_FRAGMENT_SHADER );
		unsigned int prog = glCreateProgram();

		// Create shader
		Shader newShader( vertex, frag, prog );

		// Load the source
		const char* vertexShaderCString = vertexShaderBuffer.c_str();
		const char* fragmentShaderCString = fragmentShaderBuffer.c_str();

		glShaderSource( newShader.vertexShaderID, 1, &vertexShaderCString, &vertexShaderLength );
		glShaderSource( newShader.fragmentShaderID, 1, &fragmentShaderCString, &fragmentShaderLength );

		// Compile shaders, check for errors
		int compileStatus = GL_TRUE;

		glCompileShader( newShader.vertexShaderID );
		glGetShaderiv( newShader.vertexShaderID, GL_COMPILE_STATUS, &compileStatus );
		if( compileStatus != GL_TRUE )
		{
			// Output error
			OutputShaderErrorMessage( WindowController::Get().GetHWnd(), newShader.vertexShaderID, name.c_str() );

			return false;
		}

		glCompileShader( newShader.fragmentShaderID );
		glGetShaderiv( newShader.fragmentShaderID, GL_COMPILE_STATUS, &compileStatus );
		if( compileStatus != GL_TRUE )
		{
			// Output error
			OutputShaderErrorMessage( WindowController::Get().GetHWnd(), newShader.fragmentShaderID, name.c_str() );

			return false;
		}

		// Attach shaders to program
		glAttachShader( newShader.programID, newShader.vertexShaderID );
		glAttachShader( newShader.programID, newShader.fragmentShaderID );

		//Link everything
		glLinkProgram( newShader.programID );

		// Check completeness
		glGetProgramiv( newShader.programID, GL_LINK_STATUS, &compileStatus );
		if( compileStatus != GL_TRUE )
			return false;

		// Set shader variables
		newShader.Initialize( vertexShaderBuffer );

		// Add shader to map
		shaders[ name ] = newShader;

		return true;
	}
	else
		return false;
}