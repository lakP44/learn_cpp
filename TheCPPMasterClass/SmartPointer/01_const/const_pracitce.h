#pragma once

#include <iostream>

using namespace std;

class const_practice
{
public:
	/// constexpr �����Լ�, �ִ��� ������ Ÿ�ӿ� �����ϵ��� ����˴ϴ�.
	static constexpr int constexpr_temp(int a);
	/// �׳� ��Ÿ�� �Լ�
	int runtime_temp(int a);

};

