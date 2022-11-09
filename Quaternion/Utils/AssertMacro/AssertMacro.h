#pragma once
#include <string>
#include <Windows.h>
#include <format>
#include <iostream>

class AssertMacro
{
public:
	static void CheckVerifyFailed(const char* _expr, const char* _functionName, const int _line)
	{
		const HANDLE _console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(_console, 4);
		try
		{
			throw std::exception();
		}
		catch (const std::exception&)
		{
			std::string _str = std::format("error: {} in function {} at line {}", _expr, _functionName, _line);
			std::cout << _str << std::endl;
		}
		SetConsoleTextAttribute(_console, 15);

	}
};

#define UNLIKELY(x) (x) 

#define check(expr) \
{\
	if (UNLIKELY(!(expr))) \
	{\
		AssertMacro::CheckVerifyFailed(#expr, __FUNCTION__, __LINE__);\
	}\
}
