#ifndef SDLT_MATH_H
#define SDLT_MATH_H

#include <cmath>
#include <atomic>

////	SECTION: Vector2	////

template<typename T>
class Vector2
{	
public:
	Vector2(T xI, T yI)
	{
		x = xI;
		y = yI;
	}
	
	Vector2(const Vector2<T> &vec)
	{
		x = vec.x;
		y = vec.y;
	}
	
	void Set(const Vector2<T> &vec)
	{
		x = vec.x;
		y = vec.y;
	}
			
	//Operators
	
	Vector2<T>& operator+=(const Vector2<T> &v2)
	{
		*this + v2;
		return *this;
	}
	
	Vector2<T>& operator-=(const Vector2<T> &v2)
	{
		*this - v2;
		return *this;
	}
	
	Vector2<T>& operator*=(const Vector2<T> &v2)
	{
		*this * v2;
		return *this;
	}
	
	Vector2<T>& operator/=(const Vector2<T> &v2)
	{
		*this / v2;
		return *this;
	}
	
	//	Const values \/		Vectors	^
	
	Vector2<T>& operator+=(const T val)
	{
		*this + val;
		return *this;
	}
	
	Vector2<T>& operator-=(const T val)
	{
		*this - val;
		return *this;
	}
	
	Vector2<T>& operator*=(const T val)
	{
		*this * val;
		return *this;
	}
	
	Vector2<T>& operator/=(const T val)
	{
		*this / val;
		return *this;
	}
	
	//Fields
	T x;
	T y;
};

template<typename T>
Vector2<T>& operator+(const Vector2<T> &v1, const Vector2<T> &v2)
{
	return Vector2<T>(	v1.x + v2.x,
						v1.y + v2.y);
}

template<typename T>
Vector2<T>& operator-(const Vector2<T> &v1, const Vector2<T> &v2)
{
	return Vector2<T>(	v1.x - v2.x,
						v1.y - v2.y);
}

template<typename T>
Vector2<T>& operator*(const Vector2<T> &v1, const Vector2<T> &v2)
{
	return Vector2<T>(	v1.x * v2.x,
						v1.y * v2.y);
}

template<typename T>
Vector2<T>& operator/(const Vector2<T> &v1, const Vector2<T> &v2)
{
	return Vector2<T>(	v1.x / v2.x,
						v1.y / v2.y);
}

//	Const values \/		Vectors	^

template<typename T>
Vector2<T>& operator+(const Vector2<T> &v1, const T val)
{
	return Vector2<T>(	v1.x + val,
						v1.y + val);
}

template<typename T>
Vector2<T>& operator-(const Vector2<T> &v1, const T val)
{
	return Vector2<T>(	v1.x - val,
						v1.y - val);
}

template<typename T>
Vector2<T>& operator*(const Vector2<T> &v1, const T val)
{
	return Vector2<T>(	v1.x * val,
						v1.y * val);
}

template<typename T>
Vector2<T>& operator/(const Vector2<T> &v1, const T val)
{
	return Vector2<T>(	v1.x / val,
						v1.y / val);
}

////	ENDSECT: Vector2	////

////	SECTION: Misc Functions	////

template<typename T>
static inline T clamp(T &val, T lower, T upper)
{
	return max(lower, min(val, upper));
}

template<typename T>
static void SafeDelete(T *var)
{
	delete var;
	var = nullptr;
}

static inline float RandomScaleFloat()
{
	return ((float) rand() / (RAND_MAX));
}

static unsigned int GenerateUid(bool increment = true)
{
	static std::atomic_uint	uidGen;
	if(increment)
		return uidGen.fetch_add(1);
	else
		return uidGen.load();
}

////	ENDSECT: Misc Functions	////

#endif
