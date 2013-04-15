#ifndef _MATRIX4_H_
#define _MATRIX4_H_

namespace Graphos
{
	namespace Math
	{
		class Matrix4
		{
		public:
			Matrix4( void ) { }
			Matrix4( float val00, float val01, float val02, float val03,
					 float val10, float val11, float val12, float val13,
					 float val20, float val21, float val22, float val23,
					 float val30, float val31, float val32, float val33 )
			{
				matrix[ 0 ] = val00; matrix[ 1 ] = val01; matrix[ 2 ] = val02; matrix[ 3 ] = val03;
				matrix[ 4 ] = val10; matrix[ 5 ] = val11; matrix[ 6 ] = val12; matrix[ 7 ] = val13;
				matrix[ 8 ] = val20; matrix[ 9 ] = val21; matrix[ 10 ] = val22; matrix[ 11 ] = val23;
				matrix[ 12 ] = val30; matrix[ 13 ] = val31; matrix[ 14 ] = val32; matrix[ 15 ] = val33;
			}

			float				Get( int indexX, int indexY ) const { return matrix[ indexY * 4 + indexX ]; }
			void				Set( int indexX, int indexY, float val ) { matrix[ indexY * 4 + indexX ] = val; }

			inline Matrix4		operator*( const Matrix4& other ) const
			{
				return Matrix4(
					( data[ 0 ][ 0 ] * other.data[ 0 ][ 0 ] ) + ( data[ 0 ][ 1 ] * other.data[ 1 ][ 0 ] ) + ( data[ 0 ][ 2 ] * other.data[ 2 ][ 0 ] ) + ( data[ 0 ][ 3 ] * other.data[ 3 ][ 0 ] ),
					( matrix[ 0 ] * other.matrix[ 1 ] ) + ( matrix[ 1 ] * other.matrix[ 5 ] ) + ( matrix[ 2 ] * other.matrix[ 9 ] ) + ( matrix[ 3 ] * other.matrix[ 13 ] ),
					( matrix[ 0 ] * other.matrix[ 2 ] ) + ( matrix[ 1 ] * other.matrix[ 6 ] ) + ( matrix[ 2 ] * other.matrix[ 10 ] ) + ( matrix[ 3 ] * other.matrix[ 14 ] ),
					( matrix[ 0 ] * other.matrix[ 3 ] ) + ( matrix[ 1 ] * other.matrix[ 7 ] ) + ( matrix[ 2 ] * other.matrix[ 11 ] ) + ( matrix[ 3 ] * other.matrix[ 15 ] ),

					( matrix[ 4 ] * other.matrix[ 0 ] ) + ( matrix[ 5 ] * other.matrix[ 4 ] ) + ( matrix[ 6 ] * other.matrix[ 8 ] ) + ( matrix[ 7 ] * other.matrix[ 12 ] ),
					( matrix[ 4 ] * other.matrix[ 1 ] ) + ( matrix[ 5 ] * other.matrix[ 5 ] ) + ( matrix[ 6 ] * other.matrix[ 9 ] ) + ( matrix[ 7 ] * other.matrix[ 13 ] ),
					( matrix[ 4 ] * other.matrix[ 2 ] ) + ( matrix[ 5 ] * other.matrix[ 6 ] ) + ( matrix[ 6 ] * other.matrix[ 10 ] ) + ( matrix[ 7 ] * other.matrix[ 14 ] ),
					( matrix[ 4 ] * other.matrix[ 3 ] ) + ( matrix[ 5 ] * other.matrix[ 7 ] ) + ( matrix[ 6 ] * other.matrix[ 11 ] ) + ( matrix[ 7 ] * other.matrix[ 15 ] ),

					( matrix[ 8 ] * other.matrix[ 0 ] ) + ( matrix[ 9 ] * other.matrix[ 4 ] ) + ( matrix[ 10 ] * other.matrix[ 8 ] ) + ( matrix[ 11 ] * other.matrix[ 12 ] ),
					( matrix[ 8 ] * other.matrix[ 1 ] ) + ( matrix[ 9 ] * other.matrix[ 5 ] ) + ( matrix[ 10 ] * other.matrix[ 9 ] ) + ( matrix[ 11 ] * other.matrix[ 13 ] ),
					( matrix[ 8 ] * other.matrix[ 2 ] ) + ( matrix[ 9 ] * other.matrix[ 6 ] ) + ( matrix[ 10 ] * other.matrix[ 10 ] ) + ( matrix[ 11 ] * other.matrix[ 14 ] ),
					( matrix[ 8 ] * other.matrix[ 3 ] ) + ( matrix[ 9 ] * other.matrix[ 7 ] ) + ( matrix[ 10 ] * other.matrix[ 11 ] ) + ( matrix[ 11 ] * other.matrix[ 15 ] ),

					( matrix[ 12 ] * other.matrix[ 0 ] ) + ( matrix[ 13 ] * other.matrix[ 4 ] ) + ( matrix[ 14 ] * other.matrix[ 8 ] ) + ( matrix[ 15 ] * other.matrix[ 12 ] ),
					( matrix[ 12 ] * other.matrix[ 1 ] ) + ( matrix[ 13 ] * other.matrix[ 5 ] ) + ( matrix[ 14 ] * other.matrix[ 9 ] ) + ( matrix[ 15 ] * other.matrix[ 13 ] ),
					( matrix[ 12 ] * other.matrix[ 2 ] ) + ( matrix[ 13 ] * other.matrix[ 6 ] ) + ( matrix[ 14 ] * other.matrix[ 10 ] ) + ( matrix[ 15 ] * other.matrix[ 14 ] ),
					( matrix[ 12 ] * other.matrix[ 3 ] ) + ( matrix[ 13 ] * other.matrix[ 7 ] ) + ( matrix[ 14 ] * other.matrix[ 11 ] ) + ( matrix[ 15 ] * other.matrix[ 15 ] )
					);
			}

			Matrix4				operator+( const Matrix4& other ) const;

			void				operator*=( const Matrix4& other );

			void				operator+=( const Matrix4& other );

			bool				operator==( const Matrix4& other ) const;

			static Matrix4		BuildPerspective( const float fov, const float screenAspect, const float near, const float depth );
			static Matrix4		BuildOrthogonal( const float width, const float height, const float near, const float far );

			static const Matrix4 Identity;

			union
			{
				float matrix[ 16 ];
				float data[ 4 ][ 4 ];
			};
		};
	}
}

#endif //_MATRIX4_H_