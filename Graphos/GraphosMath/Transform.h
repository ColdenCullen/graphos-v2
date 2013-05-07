#ifndef __TRANSFORM
#define __TRANSFORM

// Includes
#include "GraphosMath.h"
#include "Quaternion.h"
#include "Vector3.h"

using namespace Graphos::Math;

namespace Graphos
{
	namespace Math
	{
		struct Transform
		{
		public:
			Transform( void );

			void					Rotate( Quaternion rotation );
			void					Rotate( const float x, const float y, const float z, const float angle );
			void					Rotate( const float x, const float y, const float z );
			void					Rotate( const Vector3& eulerAngles );
			void					Translate( const float x, const float y, const float z );
			void					Translate( const Vector3& displacement );
			void					Scale( const float x, const float y, const float z );
			void					Scale( const Vector3& scale );

			const Vector3&			Position( void )	const { return position; }
			const Vector3&			Rotation( void )	const { return rotation; }
			const Vector3&			Scale( void )		const { return scale; }
			const Matrix			WorldMatrix()		const;

			Transform*				parent;

		private:
			void					RotateX( const float angle );
			void					RotateY( const float angle );
			void					RotateZ( const float angle );

			Matrix					matrix;

			Vector3					position;
			Vector3					rotation;
			Vector3					scale;
		};
	}
}

#endif//__TRANSFORM