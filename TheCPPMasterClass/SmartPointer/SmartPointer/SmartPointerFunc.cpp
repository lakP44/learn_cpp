#include "SmartPointerFunc.h"

void SmartPointerFunc::use_dog_v1(std::shared_ptr<Dog> dog)
{
	std::cout << "복사본 dog 포인터 참조 카운트 : " << dog.use_count() << std::endl;
}

void SmartPointerFunc::use_dog_v2(const std::shared_ptr<Dog>& dog)
{
	std::cout << "const reference dog 포인터 참조 카운트 : " << dog.use_count() << std::endl;
}


