#include <iostream>
#include <string>
#include <vector>

enum class Color { black, white, yellow };
enum class Size { small, medium, large };

class Product
{
public: // �� ����
	std::string name; // ��ǰ��
	Color color; // ��ǰ��
	Size size; // ��ǰũ��
};

class ProductFilter
{
public:
	std::vector<Product> Filter;
};

int main()
{
	
}