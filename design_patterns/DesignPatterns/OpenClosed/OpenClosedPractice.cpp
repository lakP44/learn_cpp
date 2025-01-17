#include <iostream>
#include <string>
#include <vector>

enum class Color { black, white, yellow };
enum class Size { small, medium, large };

class Product
{
public: // 俩 臭澜
	std::string name; // 力前疙
	Color color; // 力前祸
	Size size; // 力前农扁
};

class ProductFilter
{
public:
	std::vector<Product> Filter;
};

int main()
{
	
}