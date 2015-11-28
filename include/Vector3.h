//-------------------------------------------------------------------
// 
//
// 
//-------------------------------------------------------------------

#pragma once

#include "Unorderly.h"

namespace Ogre
{
	namespace FKAudio
	{
		template < typename T >
		class Vector3
		{
		public:
			Vector3() : X(0), Y(0), Z(0) {};
			Vector3(T tX, T tY, T tZ) : X(tX), Y(tY), Z(tZ){};
			Vector3(const Vector3< T >& otherVector3) : X(otherVector3.X), Y(otherVector3.Y), Z(otherVector3.Z) {};

			// ============================����������============================
			//-------------------------------------------------------------------
			Vector3< T > operator-() const 
			{
				return Vector3< T >(-X, -Y, -Z); 
			}
			//-------------------------------------------------------------------
			Vector3< T > operator=(const Vector3< T >& otherVector3)
			{
				X = otherVector3.X;
				Y = otherVector3.Y;
				Z = otherVector3.Z;
			}
			//-------------------------------------------------------------------
			Vector3< T > operator+(const Vector3< T >& otherVector3) const
			{
				return Vector3< T >(X + otherVector3.X, Y + otherVector3.Y, Z + otherVector3.Z);
			}
			//-------------------------------------------------------------------
			Vector3< T > operator+=(const Vector3< T >& otherVector3)
			{
				X += otherVector3.X;
				Y += otherVector3.Y;
				Z += otherVector3.Z;
				return *this;
			}
			//-------------------------------------------------------------------
			Vector3< T > operator-(const Vector3< T >& otherVector3) const
			{
				return Vector3< T >(X - otherVector3.X, Y - otherVector3.Y, Z - otherVector3.Z);
			}
			//-------------------------------------------------------------------
			Vector3< T > operator-=(const Vector3< T >& otherVector3)
			{
				X -= otherVector3.X;
				Y -= otherVector3.Y;
				Z -= otherVector3.Z;
				return *this;
			}
			//-------------------------------------------------------------------
			Vector3< T > operator*(const Vector3< T >& otherVector3) const
			{
				return Vector3< T >(X * otherVector3.X, Y * otherVector3.Y, Z * otherVector3.Z);
			}
			//-------------------------------------------------------------------
			Vector3< T > operator*=(const Vector3< T >& otherVector3)
			{
				X *= otherVector3.X;
				Y *= otherVector3.Y;
				Z *= otherVector3.Z;
				return *this;
			}
			//-------------------------------------------------------------------
			Vector3< T > operator/(const Vector3< T >& otherVector3) const
			{
				return Vector3< T >(X / otherVector3.X, Y / otherVector3.Y, Z / otherVector3.Z);
			}
			//-------------------------------------------------------------------
			Vector3< T > operator/=(const Vector3< T >& otherVector3)
			{
				X /= otherVector3.X;
				Y /= otherVector3.Y;
				Z /= otherVector3.Z;
				return *this;
			}
			//-------------------------------------------------------------------
			Vector3 < T > operator*(const T scaleNum)const 
			{
				return Vector3< T >( X * scaleNum, Y * scaleNum, Z * scaleNum);
			}
			//-------------------------------------------------------------------
			Vector3 < T > operator*=(const T scaleNum)
			{
				X *= scaleNum;
				Y *= scaleNum;
				Z *= scaleNum;
				return *this;
			}
			//-------------------------------------------------------------------
			Vector3 < T > operator/(const T scaleNum)const 
			{
				return Vector3< T >( X / scaleNum, Y / scaleNum, Z / scaleNum);
			}
			//-------------------------------------------------------------------
			Vector3 < T > operator/=(const T scaleNum)
			{
				X /= scaleNum;
				Y /= scaleNum;
				Z /= scaleNum;
				return *this;
			}
			//-------------------------------------------------------------------
			// ע�������жϲ������Ǽ򵥵� otherVector3.X == X,Ҫ���Ǹ�����
			bool operator==(const Vector3< T >& otherVector3) const
			{
				return FloatEquals(X ,otherVector3.X) && FloatEquals(Y ,otherVector3.Y) && FloatEquals(Z ,otherVector3.Z);
			}
			//-------------------------------------------------------------------
			// ע�������жϲ������Ǽ򵥵� otherVector3.X == X,Ҫ���Ǹ�����
			bool operator!=(const Vector3< T >& otherVector3) const
			{
				return !FloatEquals(X ,otherVector3.X) || !FloatEquals(Y ,otherVector3.Y) || !FloatEquals(Z ,otherVector3.Z);
			}
			//-------------------------------------------------------------------
			bool operator<=(const Vector3< T >& otherVector3) const
			{
				return X <= otherVector3.X && Y <= otherVector3.Y && Z <= otherVector3.Z;
			}
			//-------------------------------------------------------------------
			bool operator>=(const Vector3< T >& otherVector3) const
			{
				return X >= otherVector3.X && Y >= otherVector3.Y && Z >= otherVector3.Z;
			}
			//-------------------------------------------------------------------
			bool operator<(const Vector3< T >& otherVector3) const
			{
				return X < otherVector3.X && Y < otherVector3.Y && Z < otherVector3.Z;
			}
			//-------------------------------------------------------------------
			bool operator>(const Vector3< T >& otherVector3) const
			{
				return X > otherVector3.X && Y > otherVector3.Y && Z > otherVector3.Z;
			}
			//-------------------------------------------------------------------

			// ============================���溯��============================
			// ����Vector3�е�Ԫ��ֵ
			void SetX( const T tX){ X = tX; }
			void SetY( const T tY){ Y = tY; }
			void SetZ( const T tZ){ Z = tZ; }
			void Set(const T tX, const T tY, const T tZ){ X = tX; Y = tY; Z = tZ; }
			void Set(const Vector3< T >&  otherVector3) { X = otherVector3.X; Y = otherVector3.Y; Z = otherVector3.Z; }
			// ��ȡ��Vector3�ĳ���
			T GetLength() const { return reinterpret_cast< T >(QuickSquare(X * X + Y * Y + Z * Z)); }
			// ��ȡ��Vector3����ƽ��( ����ʹ���������,�ٶȱ�GetLength()�� )
			T GetLengthSquare() const { return reinterpret_cast< T >(X * X + Y * Y + Z * Z); }
			// ����Vector3�ĵ��
			T DotProduct(const Vector3< T >& otherVector3){ return (T)(X * otherVector3.X + Y * otherVector3.Y + Z * otherVector3.Z); }
			// ����Vector3��ľ��� ( ��ʱVector3��ʾ����3D�ռ��е���Ϣ )
			T GetDistance(const Vector3< T >& otherVector3) const{ return Vector3< T >(X - otherVector3.X, Y - otherVector3.Y, Z - otherVector3.Z).GetLength(); }
			// ����Vector3��ľ����ƽ�� ( ��ʱVector3��ʾ����3D�ռ��е���Ϣ,����ʹ���������,�ٶȱ�GetDistance()�� )
			T GetDistanceSquare(const Vector3< T >& otherVector3) const{ return (T)(X - otherVector3.X, Y - otherVector3.Y, Z - otherVector3.Z).GetLengthSquare(); }
			// ����Vector3D�Ĳ��
			Vector3< T > CrossProduct(const Vector3<T>& otherVector3)const
			{ return Vector3< T >(Y * otherVector3.Z - Z * otherVector3.Y, Z * otherVector3.X - X * otherVector3.Z, X * otherVector3.Y - Y * otherVector3.X); }
			// �ж������Ƿ�ͬ��
			bool IsOnOneLine(const Vector3< T >& otherVector3_1, const Vector3< T >& otherVector3_2)const
			{
				T lengthSquare = (otherVector3_2 - otherVector3_1).GetLengthSquare();
				return GetDistanceSquare(otherVector3_1) < lengthSquare && GetDistanceSquare(otherVector3_2) < lengthSquare;
			}
			// �Զ��巧ֵ��������Vector�ıȽ�
			bool IsEquals(const Vector3< T >& otherVector3, const float tolerance = FLOAT_VALVE) const
			{
				return FloatEquals(X ,otherVector3.X, tolerance) 
					&& FloatEquals(Y ,otherVector3.Y, tolerance) 
					&& FloatEquals(Z ,otherVector3.Z, tolerance);
			}
			// ��׼������
			Vector3< T >& Normalize()
			{
				T length = static_cast< T >(QuickSquare( reinterpret_cast<float>(X * X + Y * Y + Z * Z)));
				X *= length; Y *= length; Z *= length; 
				return *this;
			}
			// ����Vector3�ĳ���
			void SetLength( T newLength )
			{
				Normalize();
				*this *= newLength;
			}
			// ��ת��Vector3
			void Invert(){ X *= -1.0f;  Y *= -1.0f;  Z *= -1.0f; }
			// ��һ��ָ���ĵ�Ϊ���ģ���Y����תָ���ĽǶ�
			void RotateXZBy(double dDegrees, const Vector3< T >& centerPos)
			{
				double dRad = DegToRad(dDegrees);	
				T cs = (T)cos(dRad);
				T sn = (T)sin(dRad);
				X -= center.X;
				Z -= center.Z;
				Set( X * cs - Z * sn, Y, X * sn + Z * cs);
				X += center.X;
				Z += center.Z;
			}
			// ��һ��ָ���ĵ�Ϊ���ģ���Z����תָ���ĽǶ�
			void RotateXYBy(double dDegrees, const Vector3< T >& centerPos)
			{
				double dRad = DegToRad(dDegrees);	
				T cs = (T)cos(dRad);
				T sn = (T)sin(dRad);
				X -= center.X;
				Y -= center.Y;
				Set( X * cs - Y * sn, X * sn + Y * cs, Z);
				X += center.X;
				Y += center.Y;
			}
			// ��һ��ָ���ĵ�Ϊ���ģ���X����תָ���ĽǶ�
			void RotateYZBy(double dDegrees, const Vector3< T >& centerPos)
			{
				double dRad = DegToRad(dDegrees);	
				T cs = (T)cos(dRad);
				T sn = (T)sin(dRad);
				Z -= center.Z;
				Y -= center.Y;
				Set( X, Y * cs - Z * sn, Y * sn + Z * cs);
				Z += center.Z;
				Y += center.Y;
			}
		public:
			T X;
			T Y;
			T Z;
		};
		// ����float���͵���Ԫ����
		typedef Vector3<float> Vector3f;
	}
}