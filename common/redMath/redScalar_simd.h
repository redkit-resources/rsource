/**
* Copyright � 2014 CD Projekt Red. All Rights Reserved.
*/
#pragma once
#ifndef _REDMATH_LIB_REDSCALAR_SIMD_H_
#define _REDMATH_LIB_REDSCALAR_SIMD_H_
#include "../redSystem/types.h"
#include "mathTypes.h"
namespace RedMath
{
	namespace SIMD
	{
		RED_ALIGNED_CLASS( RedScalar, 16 )
		{
		public:
			// Constructors
			RED_INLINE RedScalar();
			RED_INLINE RedScalar( const Red::System::Float _f );
			RED_INLINE RedScalar( const RedScalar& _v );
			RED_INLINE RedScalar( const Red::System::Float* _f );
			RED_INLINE RedScalar( SIMDVector _v );

			// Destructor
			RED_INLINE ~RedScalar();

			RED_INLINE const Red::System::Float* AsFloat() const;

			// Assignment Operator - We shouldn't allow for more than this.
			RED_INLINE RedScalar& operator = ( const RedScalar& _v );
			RED_INLINE operator float() const;

			// Setting
			RED_INLINE void Set( Red::System::Float _f );
			RED_INLINE void Set( const RedScalar& _v );
			RED_INLINE void Set( const Red::System::Float* _f );

			// Special Sets
			RED_INLINE void SetZeros();
			RED_INLINE void SetOnes();

			// Manipulation Methods.
			RED_INLINE RedScalar& Negate();
			RED_INLINE RedScalar Negated() const;
			RED_INLINE RedScalar Abs() const;

			RED_INLINE Red::System::Bool IsZero() const;
			RED_INLINE Red::System::Bool IsAlmostZero( const SIMDVector _epsilon = EPSILON_VALUE ) const;
			
			union 
			{
				struct
				{
					Red::System::Float X;
					Red::System::Float Y;
					Red::System::Float Z;
					Red::System::Float W;
				};
				struct 
				{
					Red::System::Uint32 Xi;
					Red::System::Uint32 Yi;
					Red::System::Uint32 Zi;
					Red::System::Uint32 Wi;
				};
				SIMDVector V;
			};
			
		};
	}
}

#endif