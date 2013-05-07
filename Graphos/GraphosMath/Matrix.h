#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#define WIDTH 4

namespace Graphos
{
	namespace Math
	{
		//template<unsigned int HEIGHT = 4>
		struct Matrix
		{
		public:
			Matrix( void ) { }
			Matrix( float val00, float val01, float val02, float val03,
					float val10, float val11, float val12, float val13,
					float val20, float val21, float val22, float val23,
					float val30, float val31, float val32, float val33 )
			{
				dataArray[ 0 ] = val00; dataArray[ 1 ] = val01; dataArray[ 2 ] = val02; dataArray[ 3 ] = val03;
				dataArray[ 4 ] = val10; dataArray[ 5 ] = val11; dataArray[ 6 ] = val12; dataArray[ 7 ] = val13;
				dataArray[ 8 ] = val20; dataArray[ 9 ] = val21; dataArray[ 10 ] = val22; dataArray[ 11 ] = val23;
				dataArray[ 12 ] = val30; dataArray[ 13 ] = val31; dataArray[ 14 ] = val32; dataArray[ 15 ] = val33;
			}

			inline Matrix		operator*( const Matrix& other ) const
			{
				return Matrix(
					( dataArray[ 0 ] * other.dataArray[ 0 ] ) + ( dataArray[ 1 ] * other.dataArray[ 4 ] ) + ( dataArray[ 2 ] * other.dataArray[ 8 ] ) + ( dataArray[ 3 ] * other.dataArray[ 12 ] ),
					( dataArray[ 0 ] * other.dataArray[ 1 ] ) + ( dataArray[ 1 ] * other.dataArray[ 5 ] ) + ( dataArray[ 2 ] * other.dataArray[ 9 ] ) + ( dataArray[ 3 ] * other.dataArray[ 13 ] ),
					( dataArray[ 0 ] * other.dataArray[ 2 ] ) + ( dataArray[ 1 ] * other.dataArray[ 6 ] ) + ( dataArray[ 2 ] * other.dataArray[ 10 ] ) + ( dataArray[ 3 ] * other.dataArray[ 14 ] ),
					( dataArray[ 0 ] * other.dataArray[ 3 ] ) + ( dataArray[ 1 ] * other.dataArray[ 7 ] ) + ( dataArray[ 2 ] * other.dataArray[ 11 ] ) + ( dataArray[ 3 ] * other.dataArray[ 15 ] ),

					( dataArray[ 4 ] * other.dataArray[ 0 ] ) + ( dataArray[ 5 ] * other.dataArray[ 4 ] ) + ( dataArray[ 6 ] * other.dataArray[ 8 ] ) + ( dataArray[ 7 ] * other.dataArray[ 12 ] ),
					( dataArray[ 4 ] * other.dataArray[ 1 ] ) + ( dataArray[ 5 ] * other.dataArray[ 5 ] ) + ( dataArray[ 6 ] * other.dataArray[ 9 ] ) + ( dataArray[ 7 ] * other.dataArray[ 13 ] ),
					( dataArray[ 4 ] * other.dataArray[ 2 ] ) + ( dataArray[ 5 ] * other.dataArray[ 6 ] ) + ( dataArray[ 6 ] * other.dataArray[ 10 ] ) + ( dataArray[ 7 ] * other.dataArray[ 14 ] ),
					( dataArray[ 4 ] * other.dataArray[ 3 ] ) + ( dataArray[ 5 ] * other.dataArray[ 7 ] ) + ( dataArray[ 6 ] * other.dataArray[ 11 ] ) + ( dataArray[ 7 ] * other.dataArray[ 15 ] ),

					( dataArray[ 8 ] * other.dataArray[ 0 ] ) + ( dataArray[ 9 ] * other.dataArray[ 4 ] ) + ( dataArray[ 10 ] * other.dataArray[ 8 ] ) + ( dataArray[ 11 ] * other.dataArray[ 12 ] ),
					( dataArray[ 8 ] * other.dataArray[ 1 ] ) + ( dataArray[ 9 ] * other.dataArray[ 5 ] ) + ( dataArray[ 10 ] * other.dataArray[ 9 ] ) + ( dataArray[ 11 ] * other.dataArray[ 13 ] ),
					( dataArray[ 8 ] * other.dataArray[ 2 ] ) + ( dataArray[ 9 ] * other.dataArray[ 6 ] ) + ( dataArray[ 10 ] * other.dataArray[ 10 ] ) + ( dataArray[ 11 ] * other.dataArray[ 14 ] ),
					( dataArray[ 8 ] * other.dataArray[ 3 ] ) + ( dataArray[ 9 ] * other.dataArray[ 7 ] ) + ( dataArray[ 10 ] * other.dataArray[ 11 ] ) + ( dataArray[ 11 ] * other.dataArray[ 15 ] ),

					( dataArray[ 12 ] * other.dataArray[ 0 ] ) + ( dataArray[ 13 ] * other.dataArray[ 4 ] ) + ( dataArray[ 14 ] * other.dataArray[ 8 ] ) + ( dataArray[ 15 ] * other.dataArray[ 12 ] ),
					( dataArray[ 12 ] * other.dataArray[ 1 ] ) + ( dataArray[ 13 ] * other.dataArray[ 5 ] ) + ( dataArray[ 14 ] * other.dataArray[ 9 ] ) + ( dataArray[ 15 ] * other.dataArray[ 13 ] ),
					( dataArray[ 12 ] * other.dataArray[ 2 ] ) + ( dataArray[ 13 ] * other.dataArray[ 6 ] ) + ( dataArray[ 14 ] * other.dataArray[ 10 ] ) + ( dataArray[ 15 ] * other.dataArray[ 14 ] ),
					( dataArray[ 12 ] * other.dataArray[ 3 ] ) + ( dataArray[ 13 ] * other.dataArray[ 7 ] ) + ( dataArray[ 14 ] * other.dataArray[ 11 ] ) + ( dataArray[ 15 ] * other.dataArray[ 15 ] )
				);
			}

			Matrix				operator+( const Matrix& other ) const;

			void				operator*=( const Matrix& other );

			void				operator+=( const Matrix& other );

			bool				operator==( const Matrix& other ) const;

			static Matrix		BuildPerspective( const float fov, const float screenAspect, const float near, const float depth );
			static Matrix		BuildOrthogonal( const float width, const float height, const float near, const float far );

			static const Matrix Identity;

			union
			{
				float matrix[ WIDTH ][ WIDTH ];
				float dataArray[ WIDTH * WIDTH ];
			};
		};
	}
}

#endif //_MATRIX4_H_