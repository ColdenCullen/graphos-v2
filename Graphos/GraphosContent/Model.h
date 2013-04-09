#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>
#include <GL/GLIncludes.h>

#include "Vector3.hpp"
#include "Vector2.hpp"

namespace Graphos
{
	namespace Content
	{
		class Model
		{
		public:
			bool				LoadFromObjFile( std::string filePath );

			void				Draw( void );

		private:
			unsigned int		vertexBufferObject;
			unsigned int		vertexArrayObject;
			unsigned int		indexBuffer;
			unsigned int		numElements;
		};
	}
}

#endif//_MODEL_H_