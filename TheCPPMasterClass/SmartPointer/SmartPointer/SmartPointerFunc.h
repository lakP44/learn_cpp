#pragma once

#include <iostream>
#include <memory>
#include <string>

struct Dog : public std::enable_shared_from_this<Dog>
{
	std::string name;
	std::shared_ptr<Dog> dog;
	std::weak_ptr<Dog> weak_dog;

	Dog(std::string name) : name(name)
	{
		std::cout << name << " initialized dog" << std::endl;
	}

	~Dog()
	{
		std::cout << name << " destructed dog" << std::endl;
	}

	void print_dog()
	{
		std::cout << name << std::endl;
	}

	std::shared_ptr<Dog> get_shared_ptr_error() { return std::shared_ptr<Dog>(this); }
	std::shared_ptr<Dog> get_shared_ptr() { return shared_from_this(); }

	void set_other_error(std::shared_ptr<Dog> o) { dog = o; }

	void set_other(std::weak_ptr<Dog> o) { weak_dog = o; }
	void access_other()
	{
		std::shared_ptr<Dog> o = weak_dog.lock();
		if (o) {
			std::cout << "접근 : " << o->get_name() << std::endl;
		}
		else {
			std::cout << "이미 소멸됨 ㅠ" << std::endl;
		}
	}

	// 뒤에 붙은 const는 멤버변수를 바꾸지 않는다는걸 컴파일러에게 알리는 용도
	std::string get_name() const {
		return name;
	}
};

struct Person
{
	std::string name;

	Person(std::string name) : name(name)
	{
		std::cout << name << " initialized person" << std::endl;
	}

	~Person()
	{
		std::cout << name << " destructed person" << std::endl;
	}

	void adopt_dog(std::unique_ptr<Dog> dog) {
		std::cout << name << " just adopted the dog " << dog->get_name() << std::endl;
	}

	void adopt_dog_v2(const std::unique_ptr<Dog>& dog) {
		std::cout << name << " just adopted the dog!!!!! " << dog->get_name() << std::endl;
	}
};


class SmartPointerFunc
{
public:
	void use_dog_v1(std::shared_ptr<Dog> dog);
	void use_dog_v2(const std::shared_ptr<Dog>& dog);
};

