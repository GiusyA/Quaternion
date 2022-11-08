#include "Quaternion.h"
#include "../Mathf/Mathf.h"
#include <format>

#pragma region constructor
Quaternion::Quaternion(const float _x, const float _y, const float _z, const float _w)
{
	x = Mathf::Clamp101(_x);
	y = Mathf::Clamp101(_y);
	z = Mathf::Clamp101(_z);
	w = Mathf::Clamp101(_w);
}
Quaternion::Quaternion(const float _x, const float _y, const float _z) : Quaternion(_x, _y, _z, 0.0f) {}
Quaternion::Quaternion(const float _x, const float _y) : Quaternion(_x, _y, 0.0f, 0.0f) {}
Quaternion::Quaternion(const float _value)
{
	const float _clamp = Mathf::Clamp101(_value);
	x = _clamp;
	y = _clamp;
	z = _clamp;
	w = _clamp;
}
#pragma endregion constructor

#pragma region methods
float Quaternion::Dot(Quaternion& _a, Quaternion& _b)
{
	return (_a.x * _b.x) + (_a.y * _b.y) + (_a.z * _b.z) + (_a.w * _b.w);
}
float Quaternion::Angle(Quaternion& _a, Quaternion& _b)
{
	//TODO angle

	return 0.0f;
}
Quaternion Quaternion::Identity()
{
	return Quaternion(0, 0, 0, 1);
}
Quaternion Quaternion::Conjugate(Quaternion& _value)
{
	_value.x = Mathf::Clamp101(-_value.x);
	_value.y = Mathf::Clamp101(-_value.y);
	_value.z = Mathf::Clamp101(-_value.z);
	return Quaternion(_value.x, _value.y, _value.z, _value.w);
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
	float _time = Mathf::Clamp101(_t);
	_time = (_time < 0) ? 0 : _time;
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
	Quaternion _rotPitch = Quaternion(_pitch, 0, 0, 0);
	Quaternion _rotYaw = Quaternion(0, _yaw, 0, 0);
	Quaternion _rotRoll = Quaternion(0, 0, _roll, 0);
	Quaternion _result = Identity();
	_result += _rotPitch;
	_result += _rotYaw;
	_result += _rotRoll;
	return _result;
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
	x = Mathf::Clamp101(_x);
	y = Mathf::Clamp101(_y);
	z = Mathf::Clamp101(_z);
	w = Mathf::Clamp101(_w);
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
	//if (_index < 0 || _index > 3)
		//return; //TODO macro
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
	x = Mathf::Clamp101(- x);
	y = Mathf::Clamp101(-y);
	z = Mathf::Clamp101(-z);
	w = Mathf::Clamp101(-w);
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