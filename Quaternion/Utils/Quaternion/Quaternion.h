#pragma once
#include <string>

#define Epsilon 0.00001f

class Quaternion
{
#pragma region f/p
private:
	//cos des angles
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;
#pragma endregion f/p
#pragma region constructor/destructor
public:
	Quaternion() = default;
	Quaternion(const float _x, const float _y, const float _z, const float _w);
	Quaternion(const float _x, const float _y, const float _z);
	Quaternion(const float _x, const float _y);
	Quaternion(const float _value);
	~Quaternion() = default;
#pragma endregion constructor/destructor
#pragma region methods
public:
	/// <summary>
	/// Dot product of two quaternion.
	/// </summary>
	/// <returns>float</returns>
	static float Dot(Quaternion& _a, Quaternion& _b);
	/// <summary>
	/// Return the angle (degrees) between two quaternions.
	/// </summary>
	/// <returns>float</returns>
	static float Angle(Quaternion& _a, Quaternion& _b);
	/// <summary>
	/// Return a quaternion with no rotation.
	/// </summary>
	static Quaternion Identity();
	/// <summary>
	/// Conjugates a quaternion.
	/// </summary>
	/// <returns>Quaternion</returns>
	static Quaternion Conjugate(Quaternion& _value);
	/// <summary>
	/// Inverses a quaternion.
	/// </summary>
	/// <returns>Quaternion</returns>
	static Quaternion Inverse(Quaternion& _value);
	/// <summary>
	/// Linearly interpolates between two quaternions.
	/// </summary>
	/// <param name="_a">begin</param>
	/// <param name="_b">end</param>
	/// <param name="_t">time</param>
	/// <returns>Quaternion</returns>
	static Quaternion Lerp(Quaternion& _a, Quaternion& _b, const float _t);
	/// <summary>
	/// Linearly interpolates between two quaternions without clamping the interpolant.
	/// </summary>
	/// <param name="_a">begin</param>
	/// <param name="_b">end</param>
	/// <param name="_t">time</param>
	/// <returns>Quaternion</returns>
	static Quaternion LerpUnclamped(Quaternion& _a, Quaternion& _b, const float _t);
	/// <summary>
	/// Return a quaternion of the requested rotation.
	/// </summary>
	/// <param name="_pitch">x-axis</param>
	/// <param name="_yaw">y-axis</param>
	/// <param name="_roll">z-axis</param>
	static Quaternion CreateFromYawPitchRoll(const float _pitch, const float _yaw, const float _roll);
	/// <summary>
	/// Normalizes the quaternion.
	/// </summary>
	void Normalize();
	/// <summary>
	/// Set the components of the quaternion.
	/// </summary>
	void Set(const float _x, const float _y, const float _z, const float _w);
	/// <summary>
	/// Length of the quaternion.
	/// </summary>
	/// <returns>float</returns>
	float Length();
	/// <summary>
	/// Squared length of the quaternion.
	/// </summary>
	/// <returns>float</returns>
	float SquaredLength();
	/// <summary>
	/// Perform negation on the quaternion.
	/// </summary>
	Quaternion Negate();
	/// <summary>
	/// Formatted string of the quaternion.
	/// </summary>
	/// <returns>string</returns>
	std::string ToString() const;
#pragma endregion methods
#pragma region operator
public:
	float& operator[](const int _index);
	Quaternion operator+(Quaternion& _other) const;
	Quaternion operator-(Quaternion& _other) const;
	Quaternion operator*(Quaternion& _other) const;
	Quaternion operator*(const float _value) const;
	Quaternion operator/(Quaternion& _other) const;
	Quaternion operator=(Quaternion& _other);
	Quaternion& operator-();
	Quaternion& operator+=(Quaternion& _other);
	Quaternion& operator-=(Quaternion& _other);
	Quaternion& operator*=(Quaternion& _other);
	Quaternion& operator/=(Quaternion& _other);
	Quaternion& operator/=(const float _value);
	bool operator==(Quaternion& _other) const;
	bool operator!=(Quaternion& _other) const;
#pragma endregion operator
};