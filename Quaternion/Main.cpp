#include "Utils/Quaternion/Quaternion.h"

int main()
{
    Quaternion _one = Quaternion(50.0f, 25.0f, 80.0f, 125.0f);
    Quaternion _two = Quaternion(80.0f, 30.0f, 25.0f, 40.0f);

    _one.Normalize();
    std::cout << "Normalize: " << _one.ToString() << std::endl << std::endl;
    _one.Set(50.0f, 25.0f, 80.0f, 125.0f);
    std::cout << "Conjugate: " << Quaternion::Conjugate(_one).ToString() << std::endl << std::endl;
    std::cout << "Inverse: " << Quaternion::Inverse(_one).ToString() << std::endl << std::endl;
    _one.Negate();
    std::cout << "Negate: " << _one.ToString() << std::endl << std::endl;
    _one.Set(50.0f, 25.0f, 80.0f, 125.0f);
    std::cout << "Lerp (0): " << Quaternion::Lerp(_one, _two, 0.0f).ToString() << std::endl << std::endl;
    std::cout << "Lerp (0.5): " << Quaternion::Lerp(_one, _two, 0.5f).ToString() << std::endl << std::endl;
    std::cout << "Lerp (1): " << Quaternion::Lerp(_one, _two, 1.0f).ToString() << std::endl << std::endl;
    std::cout << "Dot: " << Quaternion::Dot(_one, _two) << std::endl << std::endl;
    std::cout << "Angle: " << Quaternion::Angle(_one, _two) << std::endl << std::endl;
    std::cout << "Length: " << _one.Length() << std::endl << std::endl;
    std::cout << "Squared length: " << _one.SquaredLength() << std::endl << std::endl;
    std::cout << "FromYawPitchRoll: " << Quaternion::CreateFromYawPitchRoll(45.0f, 90.0f, 25.0f).ToString() << std::endl << std::endl;
}