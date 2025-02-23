/**
* Copyright � 2007 CD Projekt Red. All Rights Reserved.
*/

class Float16Compressor
{
protected:
	union Bits
	{
		Red::System::Float f;
		Red::System::Int32 si;
		Red::System::Uint32 ui;
	};

	static Red::System::Int32 const shift = 13;
	static Red::System::Int32 const shiftSign = 16;

	static Red::System::Int32 const infN = 0x7F800000; // flt32 infinity
	static Red::System::Int32 const maxN = 0x477FE000; // max flt16 normal as a flt32
	static Red::System::Int32 const minN = 0x38800000; // min flt16 normal as a flt32
	static Red::System::Int32 const signN = 0x80000000; // flt32 sign bit

	static Red::System::Int32 const infC = infN >> shift;
	static Red::System::Int32 const nanN = (infC + 1) << shift; // minimum flt16 nan as a flt32
	static Red::System::Int32 const maxC = maxN >> shift;
	static Red::System::Int32 const minC = minN >> shift;
	static Red::System::Int32 const signC = signN >> shiftSign; // flt16 sign bit

	static Red::System::Int32 const mulN = 0x52000000; // (1 << 23) / minN
	static Red::System::Int32 const mulC = 0x33800000; // minN / (1 << (23 - shift))

	static Red::System::Int32 const subC = 0x003FF; // max flt32 subnormal down shifted
	static Red::System::Int32 const norC = 0x00400; // min flt32 normal down shifted

	static Red::System::Int32 const maxD = infC - maxC - 1;
	static Red::System::Int32 const minD = minC - subC - 1;

public:
	//! Compress float to float16
	static Red::System::Uint16 Compress( Red::System::Float value )
	{
		Bits v, s;
		v.f = value;
		Red::System::Uint32 sign = v.si & signN;
		v.si ^= sign;
		sign >>= shiftSign; // logical shift
		s.si = mulN;
		s.si = (Red::System::Int32)( s.f * v.f ); // correct subnormals
		v.si ^= (s.si ^ v.si) & -(minN > v.si);
		v.si ^= (infN ^ v.si) & -((infN > v.si) & (v.si > maxN));
		v.si ^= (nanN ^ v.si) & -((nanN > v.si) & (v.si > infN));
		v.ui >>= shift; // logical shift
		v.si ^= ((v.si - maxD) ^ v.si) & -(v.si > maxC);
		v.si ^= ((v.si - minD) ^ v.si) & -(v.si > subC);
		return (Red::System::Uint16)( v.ui | sign );
	}

	//! Decompress float16 from float
	static Red::System::Float Decompress( Red::System::Uint16 value )
	{
		Bits v;
		v.ui = value;
		Red::System::Int32 sign = v.si & signC;
		v.si ^= sign;
		sign <<= shiftSign;
		v.si ^= ((v.si + minD) ^ v.si) & -(v.si > subC);
		v.si ^= ((v.si + maxD) ^ v.si) & -(v.si > maxC);
		Bits s;
		s.si = mulC;
		s.f *= v.si;
		Red::System::Int32 mask = -(norC > v.si);
		v.si <<= shift;
		v.si ^= (s.si ^ v.si) & mask;
		v.si |= sign;
		return v.f;
	}
};
