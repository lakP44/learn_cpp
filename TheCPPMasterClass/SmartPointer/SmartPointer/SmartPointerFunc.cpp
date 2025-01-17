#include "SmartPointerFunc.h"

void SmartPointerFunc::use_dog_v1(std::shared_ptr<Dog> dog)
{
	std::cout << "���纻 dog ������ ���� ī��Ʈ : " << dog.use_count() << std::endl;
}

void SmartPointerFunc::use_dog_v2(const std::shared_ptr<Dog>& dog)
{
	std::cout << "const reference dog ������ ���� ī��Ʈ : " << dog.use_count() << std::endl;
}


