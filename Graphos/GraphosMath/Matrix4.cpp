#include "Matrix4.hpp"
#include <math.h>

using namespace Graphos::Math;

const Matrix4 Matrix4::Identity = Matrix4(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
);

Matrix4 Matrix4::operator+( const Matrix4& other ) const
{
	Matrix4 toReturn;

	for( int ii = 0; ii < 16; ++ii )
		toReturn.matrix[ ii ] = matrix[ ii ] + other.matrix[ ii ];

	return toReturn;
}

void Matrix4::operator*=( const Matrix4& other )
{
	float result[ 16 ];

	// Perform multiply, store in result
	result[ 0 ] = ( matrix[ 0 ] * other.matrix[ 0 ] ) + ( matrix[ 1 ] * other.matrix[ 4 ] ) + ( matrix[ 2 ] * other.matrix[ 8 ] ) + ( matrix[ 3 ] * other.matrix[ 12 ] );
	result[ 1 ] = ( matrix[ 0 ] * other.matrix[ 1 ] ) + ( matrix[ 1 ] * other.matrix[ 5 ] ) + ( matrix[ 2 ] * other.matrix[ 9 ] ) + ( matrix[ 3 ] * other.matrix[ 13 ] );
	result[ 2 ] = ( matrix[ 0 ] * other.matrix[ 2 ] ) + ( matrix[ 1 ] * other.matrix[ 6 ] ) + ( matrix[ 2 ] * other.matrix[ 10 ] ) + ( matrix[ 3 ] * other.matrix[ 14 ] );
	result[ 3 ] = ( matrix[ 0 ] * other.matrix[ 3 ] ) + ( matrix[ 1 ] * other.matrix[ 7 ] ) + ( matrix[ 2 ] * other.matrix[ 11 ] ) + ( matrix[ 3 ] * other.matrix[ 15 ] );

	result[ 4 ] = ( matrix[ 4 ] * other.matrix[ 0 ] ) + ( matrix[ 5 ] * other.matrix[ 4 ] ) + ( matrix[ 6 ] * other.matrix[ 8 ] ) + ( matrix[ 7 ] * other.matrix[ 12 ] );
	result[ 5 ] = ( matrix[ 4 ] * other.matrix[ 1 ] ) + ( matrix[ 5 ] * other.matrix[ 5 ] ) + ( matrix[ 6 ] * other.matrix[ 9 ] ) + ( matrix[ 7 ] * other.matrix[ 13 ] );
	result[ 6 ] = ( matrix[ 4 ] * other.matrix[ 2 ] ) + ( matrix[ 5 ] * other.matrix[ 6 ] ) + ( matrix[ 6 ] * other.matrix[ 10 ] ) + ( matrix[ 7 ] * other.matrix[ 14 ] );
	result[ 7 ] = ( matrix[ 4 ] * other.matrix[ 3 ] ) + ( matrix[ 5 ] * other.matrix[ 7 ] ) + ( matrix[ 6 ] * other.matrix[ 11 ] ) + ( matrix[ 7 ] * other.matrix[ 15 ] );

	result[ 8 ] = ( matrix[ 8 ] * other.matrix[ 0 ] ) + ( matrix[ 9 ] * other.matrix[ 4 ] ) + ( matrix[ 10 ] * other.matrix[ 8 ] ) + ( matrix[ 11 ] * other.matrix[ 12 ] );
	result[ 9 ] = ( matrix[ 8 ] * other.matrix[ 1 ] ) + ( matrix[ 9 ] * other.matrix[ 5 ] ) + ( matrix[ 10 ] * other.matrix[ 9 ] ) + ( matrix[ 11 ] * other.matrix[ 13 ] );
	result[ 10 ] = ( matrix[ 8 ] * other.matrix[ 2 ] ) + ( matrix[ 9 ] * other.matrix[ 6 ] ) + ( matrix[ 10 ] * other.matrix[ 10 ] ) + ( matrix[ 11 ] * other.matrix[ 14 ] );
	result[ 11 ] = ( matrix[ 8 ] * other.matrix[ 3 ] ) + ( matrix[ 9 ] * other.matrix[ 7 ] ) + ( matrix[ 10 ] * other.matrix[ 11 ] ) + ( matrix[ 11 ] * other.matrix[ 15 ] );

	result[ 12 ] = ( matrix[ 12 ] * other.matrix[ 0 ] ) + ( matrix[ 13 ] * other.matrix[ 4 ] ) + ( matrix[ 14 ] * other.matrix[ 8 ] ) + ( matrix[ 15 ] * other.matrix[ 12 ] );
	result[ 13 ] = ( matrix[ 12 ] * other.matrix[ 1 ] ) + ( matrix[ 13 ] * other.matrix[ 5 ] ) + ( matrix[ 14 ] * other.matrix[ 9 ] ) + ( matrix[ 15 ] * other.matrix[ 13 ] );
	result[ 14 ] = ( matrix[ 12 ] * other.matrix[ 2 ] ) + ( matrix[ 13 ] * other.matrix[ 6 ] ) + ( matrix[ 14 ] * other.matrix[ 10 ] ) + ( matrix[ 15 ] * other.matrix[ 14 ] );
	result[ 15 ] = ( matrix[ 12 ] * other.matrix[ 3 ] ) + ( matrix[ 13 ] * other.matrix[ 7 ] ) + ( matrix[ 14 ] * other.matrix[ 11 ] ) + ( matrix[ 15 ] * other.matrix[ 15 ] );

	// Transfer results across
	for( int ii = 0; ii < 16; ++ii )
		matrix[ ii ] = result[ ii ];
}

void Matrix4::operator+=( const Matrix4& other )
{
	for( int ii = 0; ii < 16; ++ii )
		matrix[ ii ] += other.matrix[ ii ];
}

bool Matrix4::operator==( const Matrix4& other ) const
{
	for( int ii = 0; ii < 16; ++ii )
		if( matrix[ ii ] != other.matrix[ ii ] )
			return false;

	return true;
}

Matrix4 Matrix4::BuildPerspective( float fov, float screenAspect, float near, float depth )
{
	Matrix4 toReturn = Matrix4::Identity;

	toReturn.data[ 0 ][ 0 ] = 1.0f / ( screenAspect * tan( fov * 0.5f ) );
	toReturn.data[ 1 ][ 1 ] = 1.0f / tan( fov * 0.5f );
	toReturn.data[ 2 ][ 2 ] = depth / ( depth - near );
	toReturn.data[ 2 ][ 3 ] = 1.0f;
	toReturn.data[ 3 ][ 2 ] = ( -near * depth ) / ( depth - near );
	toReturn.data[ 3 ][ 3 ] = 0.0f;

	return toReturn;
}