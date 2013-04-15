#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

// Includes
#include "GraphosMath.h"
#include "Quaternion.h"

using namespace Graphos::Math;

namespace Graphos
{
	namespace Math
	{
		class Transform
		{
		public:
			Transform( void );

			void					Rotate( Quaternion rotation );
			void					Rotate( const float x, const float y, const float z, const float angle );
			void					Rotate( const float x, const float y, const float z );
			void					Translate( const float x, const float y, const float z );
			void					Scale( const float x, const float y, const float z );

			const Vector3&			Position( void )	const { return position; }
			const Vector3&			Rotation( void )	const { return rotation; }
			const Vector3&			Scale( void )		const { return scale; }
			const Matrix4			WorldMatrix()		const
			{
				if( parent != nullptr ) return parent->WorldMatrix() * matrix;
				else					return matrix;
			}

			Transform*				parent;

		private:
			void					RotateX( const float angle );
			void					RotateY( const float angle );
			void					RotateZ( const float angle );

			Matrix4					matrix;

			Vector3					position;
			Vector3					rotation;
			Vector3					scale;
		};
	}
}

#endif //_TRANSFORM_H_