#ifndef _DRAWABLEGAMEOBJECT_H_
#define _DRAWABLEGAMEOBJECT_H_

#include <string>
#include <GL/GLIncludes.h>
#include "GameObject.h"
#include "GraphosMath.h"
#include "ShaderController.h"

#define _USE_READ_FILE
#include <Helpers.h>

namespace Graphos
{
	using namespace Math;

	class DrawableGameObject : public GameObject
	{
	public:
		void				LoadObjectFile( string filePath );
		void				BufferData( GLfloat vertexData[] );
		void				Draw( void );

		string				GetShaderName( void ) const { return shaderName; }
		void				SetShaderName( string newName ) { shaderName = newName; }

	private:
		unsigned int		vertexBufferObject;
		unsigned int		vertexArrayObject;
		unsigned int		indexBuffer;
		string				shaderName;
	};
}

#endif//_DRAWABLEGAMEOBJECT_H_