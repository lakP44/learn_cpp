// 02_bitwise_operators.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>

#include "02_bitwise_operators.h"

using namespace std;

int main()
{
	cout << "===================================================================================" << "\n";
	temp1::bitwise_1();

	////////////////////////////////////////////////////////////////////////

	cout << "===================================================================================" << "\n";
	temp1::bitwise_2();

	return 0;
}

void temp1::bitwise_1()
{
	unsigned int a = 567; // 0000 0101
	unsigned int b = 9; // 0000 1001
	cout << "a = " << bitset<8>(a) << "\n";
	cout << "a = " << dec << a << "\n"; // decimal
	cout << "a = " << oct << a << "\n"; // octal
	cout << "a = " << hex << a << "\n"; // hexadecimal
	cout << "b = " << bitset<8>(b) << "\n";
	// Bitwise AND
	cout << "a & b = " << bitset<8>(a & b) << "\n";
	// Bitwise OR
	cout << "a | b = " << bitset<8>(a | b) << "\n";
	// Bitwise XOR
	cout << "a ^ b = " << bitset<8>(a ^ b) << "\n";
	// Bitwise NOT
	cout << "~a = " << bitset<8>(~a) << "\n";
	// Bitwise left shift
	cout << "a << 1 = " << bitset<8>(a << 1) << "\n";
	// Bitwise right shift
	cout << "a >> 1 = " << bitset<8>(a >> 1) << "\n";
}

void temp1::bitwise_2()
{
	unsigned int a = 567; // 0000 0101
	unsigned int b = 9; // 0000 1001

	int test = 0;

	test &= a;

	cout << "test = " << bitset<8>(test) << "\n";
}
