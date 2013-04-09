#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <iostream>
using namespace std;

namespace Graphos
{
	namespace Math
	{
		class Vector3
		{
		public:
			Vector3( const float values[ 3 ] ) : x( values[ 0 ] ), y( values[ 1 ] ), z( values[ 2 ] ) { }
			Vector3( float x = 0.0f, float y = 0.0f, float z = 0.0f ) : x( x ), y( y ), z( z ) { }
			Vector3( const Vector3& other ) : x( other.x ), y( other.y ), z( other.z ) { }

			float operator[]( const int index ) const
			{
				return *( &x + index );
			}

			Vector3& operator=( const Vector3& other )
			{
				if( &other != this )
				{
					x = other.x;
					y = other.y;
					z = other.z;
				}

				return *this;
			}

			Vector3 operator+( const Vector3& other ) const
			{
				return Vector3( x + other.x, y + other.y, z + other.z );
			}

			Vector3 operator-( const Vector3& other ) const
			{
				return Vector3( x - other.x, y - other.y, z - other.z );
			}
			
			Vector3 operator%( const Vector3& other ) const
			{
				return Vector3( ( y * other.z ) - ( z * other.y ), ( x * other.z ) - ( z * other.x ), ( x * other.y ) - ( y * other.x ) );
			}

			float operator*( const Vector3& other ) const
			{
				return ( x * other.x ) + ( y * other.y ) + ( z * other.z );
			}

			Vector3 operator*( const float other ) const
			{
				return Vector3( x * other, y * other, z * other );
			}

			float Magnitude( void ) const
			{
				return sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
			}

			Vector3 Normalize( void ) const
			{
				float mag = sqrt( ( x * x ) + ( y * y ) + ( z * z ) );

				return Vector3( x / mag, y / mag, z / mag );
			}

			friend std::ostream& operator<<( std::ostream& os, const Vector3& vec )
			{
				os << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z;

				return os;
			}

			float x, y, z;
		};
	}
}

#endif //_VECTOR3_H_