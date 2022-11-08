#include "Utils/Quaternion/Quaternion.h"
#include <iostream>

int main()
{
    Quaternion _one = Quaternion(5.0f, 0.0f, 0.0f, 1.0f);
    Quaternion _two = Quaternion(0.0f, 0.0f, 1.0f, 1.0f);
    Quaternion _three = Quaternion(0.0f, 0.0f, -1.0f, 1.0f);

    std::cout << Quaternion::Conjugate(_two).ToString() << std::endl;
    std::cout << Quaternion::Inverse(_two).ToString() << std::endl;
    std::cout << Quaternion::Lerp(_three, _two, 0.0f).ToString() << std::endl;
    std::cout << Quaternion::CreateFromYawPitchRoll(1.0f, 1.0f, 0.0f).ToString() << std::endl;

    _one.Set(0.0f, 2.0f, 3.0f, 1.0f);
    std::cout << _one.ToString() << std::endl;
    std::cout << _two.Length() << std::endl;
    std::cout << _two.SquaredLength() << std::endl;

    _one.Normalize();
    std::cout << _one.Length() << std::endl;

    _three.Negate();
    std::cout << _three.ToString() << std::endl;
}