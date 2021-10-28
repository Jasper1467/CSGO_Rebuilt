#pragma once

#include <iostream>

class Vector
{
public:
	Vector(void)
	{
		Invalidate();
	}

	Vector(float _x, float _y, float _z)
	{
		Init(_x, _y, _z);
	}

	void Init(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	bool IsValid()
	{
		return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
	}

	void Invalidate()
	{
		x = y = z = std::numeric_limits<float>::infinity();
	}

	void Reset()
	{
		x = y = z = 0.0f;
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	bool operator==(const Vector& src) const
	{
		return (src.x == x) && (src.y == y) && (src.z == z);
	}

	bool operator!=(const Vector& src) const
	{
		return (src.x != x) || (src.y != y) || (src.z != z);
	}

	Vector& operator+=(const Vector& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	Vector& operator-=(const Vector& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	Vector& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		z *= fl;
		return *this;
	}

	Vector& operator*=(const Vector& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vector& operator/=(const Vector& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	Vector& operator+=(float fl)
	{
		x += fl;
		y += fl;
		z += fl;
		return *this;
	}

	Vector& operator/=(float fl)
	{
		x /= fl;
		y /= fl;
		z /= fl;
		return *this;
	}

	Vector& operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		z -= fl;
		return *this;
	}

	void NormalizeInPlace()
	{
		*this = Normalized();
	}

	Vector Normalized() const
	{
		Vector res = *this;
		float l = res.Length();
		if (l != 0.0f) {
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}

	float DistTo(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.Length();
	}

	float DistToSqr(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}

	float Dot(const Vector& vOther) const
	{
		return (x * vOther.x + y * vOther.y + z * vOther.z);
	}

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	float Length2D() const
	{
		return sqrt(x * x + y * y);
	}

	Vector& operator=(const Vector& vOther)
	{
		x = vOther.x; y = vOther.y; z = vOther.z;
		return *this;
	}

	Vector operator-(void) const
	{
		return Vector(-x, -y, -z);
	}

	Vector operator+(const Vector& v) const
	{
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	Vector operator-(const Vector& v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	Vector operator*(float fl) const
	{
		return Vector(x * fl, y * fl, z * fl);
	}

	Vector operator*(const Vector& v) const
	{
		return Vector(x * v.x, y * v.y, z * v.z);
	}

	Vector operator/(float fl) const
	{
		return Vector(x / fl, y / fl, z / fl);
	}

	Vector operator/(const Vector& v) const
	{
		return Vector(x / v.x, y / v.y, z / v.z);
	}

	float x;
	float y;
	float z;
};

class __declspec(align(16)) VectorAligned : public Vector
{
public:
	inline VectorAligned(void) {};
	inline VectorAligned(float X, float Y, float Z)
	{
		Init(X, Y, Z);
	}

public:
	explicit VectorAligned(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
	}

	VectorAligned& operator=(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	VectorAligned& operator=(const VectorAligned& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	float w;
};

class QAngle
{
public:
	QAngle(void)
	{
		Invalidate();
	}

	QAngle(float _x, float _y, float _z)
	{
		Init(_x, _y, _z);
	}

	void Init(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	bool IsValid()
	{
		return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
	}

	void Invalidate()
	{
		x = y = z = std::numeric_limits<float>::infinity();
	}

	void Reset()
	{
		x = y = z = 0.0f;
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	bool operator==(const QAngle& src) const
	{
		return (src.x == x) && (src.y == y) && (src.z == z);
	}

	bool operator!=(const QAngle& src) const
	{
		return (src.x != x) || (src.y != y) || (src.z != z);
	}

	QAngle& operator+=(const QAngle& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	QAngle& operator-=(const QAngle& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	QAngle& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		z *= fl;
		return *this;
	}

	QAngle& operator*=(const QAngle& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	QAngle& operator/=(const QAngle& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	QAngle& operator+=(float fl)
	{
		x += fl;
		y += fl;
		z += fl;
		return *this;
	}

	QAngle& operator/=(float fl)
	{
		x /= fl;
		y /= fl;
		z /= fl;
		return *this;
	}

	QAngle& operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		z -= fl;
		return *this;
	}

	void NormalizeInPlace()
	{
		*this = Normalized();
	}

	QAngle Normalized() const
	{
		QAngle res = *this;
		float l = res.Length();
		if (l != 0.0f) {
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}

	float DistTo(const QAngle& vOther) const
	{
		QAngle delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.Length();
	}

	float DistToSqr(const QAngle& vOther) const
	{
		QAngle delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}

	float Dot(const QAngle& vOther) const
	{
		return (x * vOther.x + y * vOther.y + z * vOther.z);
	}

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	float Length2D() const
	{
		return sqrt(x * x + y * y);
	}

	QAngle& operator=(const QAngle& vOther)
	{
		x = vOther.x; y = vOther.y; z = vOther.z;
		return *this;
	}

	QAngle operator-(void) const
	{
		return QAngle(-x, -y, -z);
	}

	QAngle operator+(const QAngle& v) const
	{
		return QAngle(x + v.x, y + v.y, z + v.z);
	}

	QAngle operator-(const QAngle& v) const
	{
		return QAngle(x - v.x, y - v.y, z - v.z);
	}

	QAngle operator*(float fl) const
	{
		return QAngle(x * fl, y * fl, z * fl);
	}

	QAngle operator*(const QAngle& v) const
	{
		return QAngle(x * v.x, y * v.y, z * v.z);
	}

	QAngle operator/(float fl) const
	{
		return QAngle(x / fl, y / fl, z / fl);
	}

	QAngle operator/(const QAngle& v) const
	{
		return QAngle(x / v.x, y / v.y, z / v.z);
	}

	float x;
	float y;
	float z;
};

struct CViewVectors
{
	CViewVectors(Vector view, Vector hullmin, Vector hullmax, Vector duckhullmin, Vector duckhullmax, Vector duckview, Vector obshullmin, Vector obshullmax, Vector deadviewheight)
	{
		m_vecView = view;
		m_vecHullMin = hullmin;
		m_vecHullMax = hullmax;
		m_vecDuckHullMin = duckhullmin;
		m_vecDuckHullMax = duckhullmax;
		m_vecDuckView = duckview;
		m_vecObsHullMin = obshullmin;
		m_vecObsHullMax = obshullmax;
		m_vecDeadViewHeight = deadviewheight;
	}

	Vector m_vecView;
	Vector m_vecHullMin;
	Vector m_vecHullMax;
	Vector m_vecDuckHullMin;
	Vector m_vecDuckHullMax;
	Vector m_vecDuckView;
	Vector m_vecObsHullMin;
	Vector m_vecObsHullMax;
	Vector m_vecDeadViewHeight;
};

using matrix4x4_t = float[4][4];

class matrix3x4_t
{
public:
	matrix3x4_t() = default;

	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;
		m_flMatVal[0][1] = m01;
		m_flMatVal[0][2] = m02;
		m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;
		m_flMatVal[1][1] = m11;
		m_flMatVal[1][2] = m12;
		m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;
		m_flMatVal[2][1] = m21;
		m_flMatVal[2][2] = m22;
		m_flMatVal[2][3] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void Init(const Vector& x_axis, const Vector& y_axis, const Vector& z_axis, const Vector& vec_origin) {
		m_flMatVal[0][0] = x_axis.x;
		m_flMatVal[0][1] = y_axis.x;
		m_flMatVal[0][2] = z_axis.x;
		m_flMatVal[0][3] = vec_origin.x;
		m_flMatVal[1][0] = x_axis.y;
		m_flMatVal[1][1] = y_axis.y;
		m_flMatVal[1][2] = z_axis.y;
		m_flMatVal[1][3] = vec_origin.y;
		m_flMatVal[2][0] = x_axis.z;
		m_flMatVal[2][1] = y_axis.z;
		m_flMatVal[2][2] = z_axis.z;
		m_flMatVal[2][3] = vec_origin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t(const Vector& x_axis, const Vector& y_axis, const Vector& z_axis, const Vector& vec_origin)
	{
		Init(x_axis, y_axis, z_axis, vec_origin);
	}

	void SetOrigin(const Vector& p)
	{
		m_flMatVal[0][3] = p.x;
		m_flMatVal[1][3] = p.y;
		m_flMatVal[2][3] = p.z;
	}

	void Invalidate()
	{
		for (auto& i : m_flMatVal)
		{
			for (float& j : i)
				j = std::numeric_limits< float >::infinity();
		}
	}

	float* operator[](int i)
	{
		return m_flMatVal[i];
	}

	const float* operator[](int i) const
	{
		return m_flMatVal[i];
	}

	float* Base()
	{
		return &m_flMatVal[0][0];
	}

	const float* Base() const
	{
		return &m_flMatVal[0][0];
	}

	float m_flMatVal[3][4];
};

struct __declspec(align(16)) matrix3x4a_t : public matrix3x4_t
{
public:
	matrix3x4a_t& operator=(const matrix3x4_t& src) { memcpy(Base(), src.Base(), sizeof(float) * 3 * 4); return *this; };
};

class VMatrix
{
public:
	float m[4][4];
};

class Vector2D
{
public:
	Vector2D(void)
	{
		Invalidate();
	}

	Vector2D(float _x, float _y)
	{
		Init(_x, _y);
	}

	void Init(float _x = 0.0f, float _y = 0.0f)
	{
		x = _x;
		y = _y;
	}

	bool IsValid()
	{
		return std::isfinite(x) && std::isfinite(y);
	}

	void Invalidate()
	{
		x = y = std::numeric_limits<float>::infinity();
	}

	void Reset()
	{
		x = y = 0.0f;
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	bool operator==(const Vector2D& src) const
	{
		return (src.x == x) && (src.y == y);
	}

	bool operator!=(const Vector2D& src) const
	{
		return (src.x != x) || (src.y != y);
	}

	Vector2D& operator+=(const Vector2D& v)
	{
		x += v.x; y += v.y;
		return *this;
	}

	Vector2D& operator-=(const Vector2D& v)
	{
		x -= v.x; y -= v.y;
		return *this;
	}

	Vector2D& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		return *this;
	}

	Vector2D& operator*=(const Vector2D& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vector2D& operator/=(const Vector2D& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	Vector2D& operator+=(float fl)
	{
		x += fl;
		y += fl;
		return *this;
	}

	Vector2D& operator/=(float fl)
	{
		x /= fl;
		y /= fl;
		return *this;
	}

	Vector2D& operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		return *this;
	}

	void NormalizeInPlace()
	{
		*this = Normalized();
	}

	Vector2D Normalized() const
	{
		Vector2D res = *this;
		float l = res.Length();
		if (l != 0.0f) {
			res /= l;
		}
		else {
			res.x = res.y = 0.0f;
		}
		return res;
	}

	float DistTo(const Vector2D& vOther) const
	{
		Vector2D delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;

		return delta.Length();
	}

	float DistToSqr(const Vector2D& vOther) const
	{
		Vector2D delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;

		return delta.LengthSqr();
	}

	float Dot(const Vector2D& vOther) const
	{
		return (x * vOther.x + y * vOther.y);
	}

	float Length() const
	{
		return sqrt(x * x + y * y);
	}

	float LengthSqr(void) const
	{
		return (x * x + y * y);
	}

	float Length2D() const
	{
		return sqrt(x * x + y * y);
	}

	Vector2D& operator=(const Vector2D& vOther)
	{
		x = vOther.x; y = vOther.y;
		return *this;
	}

	Vector2D operator-(void) const
	{
		return Vector2D(-x, -y);
	}

	Vector2D operator+(const Vector2D& v) const
	{
		return Vector2D(x + v.x, y + v.y);
	}

	Vector2D operator-(const Vector2D& v) const
	{
		return Vector2D(x - v.x, y - v.y);
	}

	Vector2D operator*(float fl) const
	{
		return Vector2D(x * fl, y * fl);
	}

	Vector2D operator*(const Vector2D& v) const
	{
		return Vector2D(x * v.x, y * v.y);
	}

	Vector2D operator/(float fl) const
	{
		return Vector2D(x / fl, y / fl);
	}

	Vector2D operator/(const Vector2D& v) const
	{
		return Vector2D(x / v.x, y / v.y);
	}

	float x;
	float y;
};