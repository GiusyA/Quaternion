#include "Quaternion.h"
#include "../AssertMacro/AssertMacro.h"
#include "../Mathf/Mathf.h"
#include <format>

#pragma region constructor
Quaternion::Quaternion(const float _x, const float _y, const float _z, const float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}
Quaternion::Quaternion(const float _x, const float _y, const float _z) : Quaternion(_x, _y, _z, 0.0f) {}
Quaternion::Quaternion(const float _x, const float _y) : Quaternion(_x, _y, 0.0f, 0.0f) {}
Quaternion::Quaternion(const float _value)
{
	x = _value;
	y = _value;
	z = _value;
	w = _value;
}
#pragma endregion constructor

#pragma region methods
float Quaternion::Dot(Quaternion& _a, Quaternion& _b)
{
	return (_a.x * _b.x) + (_a.y * _b.y) + (_a.z * _b.z) + (_a.w * _b.w);
}
float Quaternion::Angle(Quaternion& _a, Quaternion& _b)
{
	const float _y = _a.y - _b.y; //b
	const float _sqy = _y * _y; //b²
	const float _sqa = _a.w * _a.w; //c²
	const float _sqb = _b.w * _b.w; //a²

	float _tot = (_sqb + _sqa - _sqy) / (2.0f * _b.w * _a.w);
	_tot = Mathf::Clamp01(_tot);

	return acos(_tot) * 180.0f / 3.14159265359f;
}
Quaternion Quaternion::Identity()
{
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}
Quaternion Quaternion::Conjugate(Quaternion& _value)
{
	const float _x = (_value.x == 0.0f) ? 0.0f : -_value.x;
	const float _y = (_value.y == 0.0f) ? 0.0f : -_value.y;
	const float _z = (_value.z == 0.0f) ? 0.0f : -_value.z;
	const float _w = (_value.w == 0.0f) ? 0.0f : -_value.w;
	return Quaternion(_x, _y, _z, _w);
}
Quaternion Quaternion::Inverse(Quaternion& _value)
{
	Quaternion _inverse = Conjugate(_value);
	if (_inverse.SquaredLength() > Epsilon)
		_inverse /= _inverse.SquaredLength();
	else
	{
		Quaternion _identity = Identity();
		Quaternion _conjugate = Conjugate(_identity);
		_inverse = _conjugate;
	}
	return _inverse;
}
Quaternion Quaternion::Lerp(Quaternion& _a, Quaternion& _b, const float _t)
{
	float _time = Mathf::Clamp01(_t);
	Quaternion _lerp = Quaternion(
										_a.x + ((_b.x - _a.x) * _time),
										_a.y + ((_b.y - _a.y) * _time),
										_a.z + ((_b.z - _a.z) * _time),
										_a.w + ((_b.w - _a.w) * _time)
								 );
	_lerp.Normalize();
	return _lerp;
}
Quaternion Quaternion::LerpUnclamped(Quaternion& _a, Quaternion& _b, const float _t)
{
	Quaternion _lerp = Quaternion(
										_a.x + ((_b.x - _a.x) * _t),
										_a.y + ((_b.y - _a.y) * _t),
										_a.z + ((_b.z - _a.z) * _t),
										_a.w + ((_b.w - _a.w) * _t)
								 );
	_lerp.Normalize();
	return _lerp;
}
Quaternion Quaternion::CreateFromYawPitchRoll(const float _pitch, const float _yaw, const float _roll)
{
	const float _cr = cos(_roll * 0.5f);
	const float _sr = sin(_roll * 0.5f);
	const float _cp = cos(_pitch * 0.5f);
	const float _sp = sin(_pitch * 0.5f);
	const float _cy = cos(_yaw * 0.5f);
	const float _sy = sin(_yaw * 0.5f);
	const float _rotPitch = _sy * _cp * _cr + _cy * _sp * _sr;
	const float _rotYaw = _cy * _sp * _cr - _sy * _cp * _sr;
	const float _rotRoll = _cy * _cp * _sr - _sy * _sp * _cr;
	const float _rotScal = _cy * _cp * _cr + _sy * _sp * _sr;
	return Quaternion(_rotPitch, _rotYaw, _rotRoll, _rotScal);
}
void Quaternion::Normalize()
{
	if (Length() > Epsilon)
		*this /= Length();
	else
	{
		Quaternion _identity = Identity();
		*this = _identity;
	}
}
void Quaternion::Set(const float _x, const float _y, const float _z, const float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}
float Quaternion::Length()
{
	return Mathf::Sqrt(SquaredLength());
}
float Quaternion::SquaredLength()
{
	return Dot(*this, *this);
}
Quaternion Quaternion::Negate()
{
	return -*this;
}
std::string Quaternion::ToString() const
{
	return std::format("[{}, {}, {}, {}]", x, y, z, w);
}
#pragma endregion methods

#pragma region operator
float& Quaternion::operator[](const int _index)
{
	check (_index > 0 && _index < 4)
	switch (_index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	}
}
Quaternion Quaternion::operator+(Quaternion& _other) const
{
	return Quaternion(x + _other.x, y + _other.y, z + _other.z, w + _other.w);
}
Quaternion Quaternion::operator-(Quaternion& _other) const
{
	return Quaternion(x - _other.x, y - _other.y, z - _other.z, w - _other.w);
}
Quaternion Quaternion::operator*(Quaternion& _other) const
{
	return Quaternion(x * _other.x, y * _other.y, z * _other.z, w * _other.w);
}
Quaternion Quaternion::operator*(const float _value) const
{
	return Quaternion(x * _value, y * _value, z * _value, w * _value);
}
Quaternion Quaternion::operator/(Quaternion& _other) const
{
	return Quaternion(x / _other.x, y / _other.y, z / _other.z, w / _other.w);
}
Quaternion Quaternion::operator=(Quaternion& _other)
{
	x = _other.x;
	y = _other.y;
	z = _other.z;
	w = _other.w;
	return *this;
}
Quaternion& Quaternion::operator-()
{
	x = (x == 0.0f) ? 0.0f : - x;
	y = (y == 0.0f) ? 0.0f : - y;
	z = (z == 0.0f) ? 0.0f : - z;
	w = (w == 0.0f) ? 0.0f : - w;
	return *this;
}
Quaternion& Quaternion::operator+=(Quaternion& _other)
{
	x += _other.x;
	y += _other.y;
	z += _other.z;
	w += _other.w;
	return *this;
}
Quaternion& Quaternion::operator-=(Quaternion& _other)
{
	x -= _other.x;
	y -= _other.y;
	z -= _other.z;
	w -= _other.w;
	return *this;
}
Quaternion& Quaternion::operator*=(Quaternion& _other)
{
	x *= _other.x;
	y *= _other.y;
	z *= _other.z;
	w *= _other.w;
	return *this;
}
Quaternion& Quaternion::operator/=(Quaternion& _other)
{
	x /= _other.x;
	y /= _other.y;
	z /= _other.z;
	w /= _other.w;
	return *this;
}
Quaternion& Quaternion::operator/=(const float _value)
{
	x /= _value;
	y /= _value;
	z /= _value;
	w /= _value;
	return *this;
}
bool Quaternion::operator==(Quaternion& _other) const
{
	return x == _other.x && y == _other.y && z == _other.z && w == _other.w;
}
bool Quaternion::operator!=(Quaternion& _other) const
{
	return x != _other.x || y != _other.y || z != _other.z || w != _other.w;
}
#pragma endregion operator