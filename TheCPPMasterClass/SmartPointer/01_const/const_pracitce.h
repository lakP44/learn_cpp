#pragma once

#include <iostream>

using namespace std;

class const_practice
{
public:
	/// constexpr 제곱함수, 최대한 컴파일 타임에 근접하도록 실행됩니다.
	static constexpr int constexpr_temp(int a);
	/// 그냥 런타임 함수
	int runtime_temp(int a);

};

