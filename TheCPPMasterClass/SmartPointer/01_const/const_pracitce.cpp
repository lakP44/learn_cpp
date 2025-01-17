#include "const_pracitce.h"

// 얘는 컴파일 타임에 초기화되는 변수입니다.
constinit float asd = 3.f;

/// consteval 제곱함수, 완벽히 컴파일 타임에 실행됩니다.
consteval int consteval_temp(int a)
{
	return a * a;
}

constexpr int const_practice::constexpr_temp(int a)
{
	int b = a * a;

	return b;
}

int const_practice::runtime_temp(int a)
{
	return 0;
}

int main(void)
{
	enum
	{
		test1 = const_practice::constexpr_temp(5),
		test2 = consteval_temp(2),
		// test3 = runtime_temp(3) // error
	};

	cout << test1 << "," << test2 << endl;
}