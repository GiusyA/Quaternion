#include "Mathf.h"
#include <complex>

#pragma region methods
float Mathf::Clamp01(const float _value)
{
    return (_value > 1.0f) ? 1.0f : (_value <= 0.0f) ? 0.0f : _value;
}
float Mathf::Sqrt(const float _value)
{
    return std::sqrt(_value);
}
#pragma endregion methods