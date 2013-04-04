#ifndef _DRAWABLEGAMEOBJECT_H_
#define _DRAWABLEGAMEOBJECT_H_

#include <string>
#include <GL/GLIncludes.h>
#include "GameObject.h"
#include "GraphosMath.h"
#include "ShaderController.h"
#include "Texture.h"

#define _USE_READ_FILE
#include <Helpers.h>

namespace Graphos
{
	using namespace Math;
	using namespace Content;

	class DrawableGameObject : public GameObject
	{
	public:
		void				LoadObjectFile( string filePath );
		void				BufferData( GLfloat vertexData[] );
		void				Draw( void );
		void				InitMaterial( string filePath );

		string				GetShaderName( void ) const { return shaderName; }
		void				SetShaderName( string newName ) { shaderName = newName; }

	private:
		Texture				material;
		unsigned int		vertexBufferObject;
		unsigned int		vertexArrayObject;
		unsigned int		indexBuffer;
		unsigned int		numElements;
		string				shaderName;
	};
}

#endif//_DRAWABLEGAMEOBJECT_H_