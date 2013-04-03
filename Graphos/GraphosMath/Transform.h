#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

// Includes
#include "GraphosMath.h"

using namespace Graphos::Math;

namespace Graphos
{
	namespace Math
	{
		class Transform
		{
		public:
			Transform( void );

			Vector3					position;
			Vector3					rotation;
			Vector3					scale;

			Matrix4&				getMatrix() { return matrix; }

			void					Rotate( const float x, const float y, const float z, const float angle );
			void					Translate( const float x, const float y, const float z );
			void					Scale( const float x, const float y, const float z );

		private:
			void					RotateX( const float angle );
			void					RotateY( const float angle );
			void					RotateZ( const float angle );

			Matrix4					matrix;
		};
	}
}

#endif //_TRANSFORM_H_