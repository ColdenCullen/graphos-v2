#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "Vector3.hpp"
#include "Matrix4.hpp"

namespace Graphos
{
	namespace Math
	{
		class Quaternion
		{
		public:
			Quaternion( void ) { };
			Quaternion( const Vector3& axis, const float w ) : axis( axis ), w( w ) { }
			Quaternion( const float x, const float y, const float z, const float w ) : axis( x, y, z ), w( w ) { }

			Quaternion operator*( Quaternion& other )
			{
				return Quaternion(
					axis.x * other.w + axis.y * other.axis.z - axis.z * other.axis.y + w * other.axis.x,
					-axis.x * other.axis.z + axis.y * other.w + axis.z * other.axis.x + w * other.axis.y,
					axis.x * other.axis.y - axis.y * other.axis.x + axis.z * other.w + w * other.axis.z,
					-axis.x * other.axis.x - axis.y * other.axis.y - axis.z * other.axis.z + w * other.w
					);
			}

			Matrix4 ToMatrix( void ) const
			{
				return Matrix4(
					1 - 2 * ( pow( axis.y, 2.0f ) - pow( axis.z, 2.0f ) ), 2 * ( axis.x * axis.y + axis.z * w ), 2 * ( axis.x * axis.z - axis.y * w ), 0.0f,
					2 * ( axis.x * axis.y - axis.z * w ), 1 - 2 * ( pow( axis.x, 2.0f ) - pow( axis.z, 2.0f ) ), 2 * ( axis.y * axis.z + axis.x * w ), 0.0f,
					2 * ( axis.x * axis.z + axis.y * w ), 2 * ( axis.y * axis.z - axis.x * w ), 1 - 2 * ( pow( axis.x, 2.0f ) - pow( axis.y, 2.0f ) ), 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
					);
			}

			static const Quaternion Identity;

			Vector3 axis;
			float w;
		};
	}
}

#endif //_QUATERNION_H_