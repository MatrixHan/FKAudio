//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once

#include <boost/smart_ptr.hpp>
#include <assert.h>
#include <algorithm>
#include <iostream>

typedef unsigned int uint32;

// �Զ�����ԣ�����֮���Ogre���
#ifdef _DEBUG
#define FK_ASSERT(exp) assert(exp)
#else
#define FK_ASSERT(exp) ((void)0)
#endif 

// ��Ч��������ָ��
typedef boost::shared_ptr<std::istream> SP_ISTREAM;

// ����OGG��Ч����������СΪ4KB
uint32 const	OGG_BUFFUR = 4096;
// ����float���ͱȽϵķ�ֵΪ0.00001f
const float		FLOAT_VALVE = 0.00001f;
// ����PIֵ 
const double	PI = 3.1415926535897932384626433832795028841971693993751;


namespace Ogre
{
	namespace FKAudio
	{
	//-------------------------------------------------------------------
	// ȡ��Сֵ
	template < typename T > 
	inline const T& FKMin( const T& value1, const T& value2)
	{
		//return value1 < value2 ? value1, value2;
		return value1 < value2 ? value1 : value2;
	}
	//-------------------------------------------------------------------
	// ȡ���ֵ
	template < typename T > 
	inline const T& FKMax( const T& value1, const T& value2)
	{
		return value1 > value2 ? value1 : value2;
	}
	//-------------------------------------------------------------------
	// ȡ�м�ֵ
	template < typename T > 
	inline const T& FKClamp( const T& value1, const T& value2, const T& value3)
	{
		return FKMax(value2, FKMin(value3 , value1));
	}
	//-------------------------------------------------------------------	
	// ��������FourCC����
	template <unsigned char ch0, unsigned char ch1, unsigned char ch2, unsigned char ch3>
	struct MakeFourCC
	{
		enum { value = (ch0 << 0) + (ch1 << 8) + (ch2 << 16) + (ch3 << 24) };
	};
	//-------------------------------------------------------------------
	// �ж�����float�����Ƿ����
	inline bool FloatEquals(const float value1, const float value2, const float tolerance = FLOAT_VALVE)
	{
		return (value1 + tolerance > value2) && (value1 - tolerance < value2);
	}
	//-------------------------------------------------------------------
	// ����floatƽ�����ĺ���
	__forceinline float QuickSquare(const float value)
	{
		__asm
		{
			movss	xmm0, value
			rsqrtss	xmm0, xmm0
			movss	value, xmm0
		}	
		return value;
	}
	//-------------------------------------------------------------------
	// �Ƕ�ת���Ⱥ���
	inline double DegToRad(double dDegrees)
	{
		return (dDegrees * (PI / 180.0));
	}
	//-------------------------------------------------------------------
	// ����ת�ǶȺ���
	inline double RadToDeg(double dRadians)
	{
		return (dRadians * (180.0 / PI));
	}
	//-------------------------------------------------------------------
	// �Զ��巵��һ����ṹ�е�һ����
	template <typename pair_type>
	struct select1st : public std::unary_function<const pair_type &,const typename pair_type::first_type &>
	{
		const typename pair_type::first_type& operator()(const pair_type& x) const
		{
			return x.first;
		}
	};
	//-------------------------------------------------------------------
	// �Զ��巵��һ����ṹ�еڶ�����
	template <typename pair_type>
	struct select2nd : public std::unary_function<const pair_type &,const typename pair_type::second_type &>
	{
		const typename pair_type::second_type& operator()(const pair_type& x) const
		{
			return x.second;
		}
	};
	//-------------------------------------------------------------------
	}
}
