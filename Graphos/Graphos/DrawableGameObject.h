#ifndef _DRAWABLEGAMEOBJECT_H_
#define _DRAWABLEGAMEOBJECT_H_

#include <string>
#include <GL/GLIncludes.h>
#include "GameObject.h"
#include "GraphosMath.h"
#include "ShaderController.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"

#define _USE_READ_FILE
#include <Helpers.h>

namespace Graphos
{
	using namespace Math;
	using namespace Content;
	using namespace Graphics;

	class DrawableGameObject : public GameObject
	{
	public:
							DrawableGameObject( Shader& shader ) : shader( shader ) { }

		void				LoadObjectFile( string filePath );
		void				InitMaterial( string filePath );

		void				Draw( void );

		Shader&				GetShader( void ) const { return shader; }
		void				SetShader( string newName ) { shader = ShaderController::Get().GetShader( newName ); }

	private:
		Texture				material;
		Model				model;

		Shader&				shader;
	};
}

#endif//_DRAWABLEGAMEOBJECT_H_