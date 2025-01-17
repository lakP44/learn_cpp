#include <string>
#include <iostream>
#include <vector>

// 확장을 위해 열고, 수정을 위해 닫는다.
// 확장과 상속을 통해 코드를 수정하지 않고 확장할 수 있게 만드는 것이 목적
// 이 패턴의 이름 : Specification Pattern
// Specification Pattern은 객체의 상태를 나타내는 인터페이스를 정의하고, 이 인터페이스를 만족하는 객체를 만들어서 사용하는 패턴
using namespace std;

enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product
{
	string name;
	Color color;
	Size size;
};

// 제품 필터링
// 아래는 상속을 사용하지 않고 계속 코드를 붙여넣게 하는 잘못된 예제임
struct ProductFilter
{
#pragma region 이렇게 상속을 사용하지 않고 계속 코드를 붙여넣게 하면 시스템이 확장에 열려있지 않은 상태임.
	vector<Product*> by_color(vector<Product*> items, Color color)
	{
		vector<Product*> result;
		for (auto& i : items)
			if (i->color == color)
				result.push_back(i);
		return result;
	}
	
	// 만약 고객이 사이즈로 필터링을 하고싶다면?
	vector<Product*> by_size(vector<Product*> items, Size size)
	{
		vector<Product*> result;
		for (auto& i : items)
			if (i->size == size)
				result.push_back(i);
		return result;
	}

	// 둘다 만들었는데 이번엔 사이즈, 컬러 동시 필터링을 원한다면?
	vector<Product*> by_color_and_size(vector<Product*> items, Size size, Color color)
	{
		vector<Product*> result;
		for (auto& i : items)
			if (i->size == size && i->color == color)
				result.push_back(i);
		return result;
	}
#pragma endregion
};
////////////////////////////////////////////////////////////////////////////////////

// 아래 컴팩트한 operator 사용시 AndSpecification이 위에 선언되어 있지 않으면 오류가 발생함
// AndSpecification 구현은 맨밑에 되어있음
template <typename T> struct AndSpecification;

// 확장이 가능한 코드로 변경
template <typename T> struct Specification
{
	// virtual : 상속을 받는 클래스에서 재정의 해줄것으로 기대하는 함수
	virtual bool is_satisfied(T* item) = 0;
	// 순수 가상 함수(pure virtual function)
	// = 0이라는 뜻은 0으로 초기화 한다는 것이 아니라 순수 가상 함수라는 뜻
	// 구현이 없는 함수로, 상속받는 클래스에서 반드시 구현해야 함
	// 구현이 없는 함수를 가지고 있는 클래스는 추상 클래스(abstract class)라고 함
	// 추상 클래스는 객체를 생성할 수 없음

	// 더 컴팩트한 방법을 위한 operator
	// 컴팩트한 operator 사용시 AndSpecification이 위에 선언되어 있지 않으면 오류가 발생함 <-- 중요
	// &는 l-value 참조, &&는 r-value 참조, r-value는 상수와 같은것
	// 이 코드는 && 연산자 오버로딩에서 사용되며, Specification<T>&&를 사용하여 임시 객체를 안전하게 참조하려는 의도를 보여줍니다.
	// 즉, &&를 통해 전달된 객체는 기존에 이름이 없거나 일시적으로 생성된 객체일 가능성이 높습니다.
	AndSpecification<T> operator&&(Specification<T>&& other)
	{
		// *this는 현재 객체를 가리키는 포인터를 객체로 올림, other은 rvalue reference로 전달된 객체를 참조
		// 따라서 둘다 객체임
		return AndSpecification<T>(*this, other);
	}
};
// 확장이 가능한 코드로 변경, 템플릿을 사용
template <typename T> struct Filter
{
	virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

// 필터를 상속, 필터가 구현되는 구조체
struct BetterProductFilter : Filter<Product>
{
	// template T를 Product로 변경하여 override
	vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) override
	{
		// 제품 결과 벡터
		vector<Product*> result;
		// 제품들을 순회하며 spec.is_satisfied(item)이 true인 제품들을 result에 추가
		for (auto& item : items)
			if (spec.is_satisfied(item))
				result.push_back(item);
		return result;
	}
};

// 색상을 상속, 색상을 확인하는 구조체
struct ColorSpecification : Specification<Product>
{
	Color color;
	// ColorSpecification에 color 값을 넣어서 초기화를 먼저 시키고
	ColorSpecification(Color color) : color(color) {}
	
	// is_satisfied 함수에 넘겨준 item color와 일치하는지 확인함
	bool is_satisfied(Product* item) override
	{
		return item->color == color;
	}
};

// 크기를 상속, 크기를 확인하는 구조체
struct SizeSpecification : Specification<Product>
{
	Size size;
	// ColorSpecification에 size 값을 넣어서 초기화를 먼저 시키고
	SizeSpecification(Size size) : size(size) {}

	// is_satisfied 함수에 넘겨준 item size와 일치하는지 확인함
	bool is_satisfied(Product* item) override
	{
		return item->size == size;
	}
};

template <typename T> struct AndSpecification : Specification<T>
{
	Specification<T>& first;
	Specification<T>& second;
	AndSpecification(Specification<T>& first, Specification<T>& second) : first(first), second(second) {}
	bool is_satisfied(T* item) override
	{
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};

// 이래도 돌아는 감
//struct AndSpecification : Specification<Product>
//{
//	Specification<Product>& first;
//	Specification<Product>& second;
//	AndSpecification(Specification<Product>& first, Specification<Product>& second) : first(first), second(second) {}
//	bool is_satisfied(Product* item) override
//	{
//		return first.is_satisfied(item) && second.is_satisfied(item);
//	}
//};

int main()
{
	Product apple{ "Apple", Color::red, Size::small };
	Product tree{ "Tree", Color::green, Size::large };
	Product house{ "House", Color::blue, Size::large };
	Product light{ "Light", Color::green, Size::small };
	Product phone{ "Phone", Color::red, Size::small };

	vector<Product*> items{ &apple, &tree, &house, &light, &phone };

	{
		// template을 사용하지 않은 코드, 확장성 낮음
		ProductFilter pf;
		auto green_things = pf.by_color(items, Color::green);
		for (auto& item : green_things)
			cout << item->name << " is green" << endl;
	}
	////////////////////////////////////////////////////////////////////////////////////
	{
		// template을 사용한 코드
		BetterProductFilter bpf;
		// 특정 색의 객체 초기화
		// ColorSpecification은 Specification을 상속받고, Specification 구조체에는 is_satisfied 함수가 선언되어 있음 (순수 가상 함수)
		// 이 순수 가상 함수를 ColorSpecification에서 override 해줌, item color를 생성자에서 초기화된 color와 비교
		ColorSpecification red(Color::red);
		
		// 특정 사이즈의 객체 초기화
		// SizeSpecification은 Specification을 상속받고, Specification 구조체에는 is_satisfied 함수가 선언되어 있음 (순수 가상 함수)
		// 이 순수 가상 함수를 SizeSpecification에서 override 해줌, item size를 생성자에서 초기화된 size와 비교
		SizeSpecification small(Size::small);

		// red_and_small은 만들어지자마자 생성자로 red, small로 초기화 됨
		// red_and_small을 초기화 할때 first, second에 각각 red, small이 들어가는데 ColorSpecification과 SizeSpecification이 Specification을 상속받았기 때문에 가능
		// AndSpecification 객체인 red_and_small의 first는 ColorSpecification, second는 SizeSpecification 상태가 됨
		// 따라서 is_satisfied 함수가 first, second 각각 실행될때 본인 구조체를 따라가 거기 override된 함수를 실행하게 됨
		AndSpecification<Product> red_and_small(red, small);

			// 이래도 돌아는 감
			// AndSpecification red_and_small(red, small);

		// BetterProductFilter 객체의 filter 함수를 실행할때 items는 Product들, red_and_small은 AndSpecification<Product> 객체가 됨
		// items는 상관없지만 red_and_small은 AndSpecification<Product> 객체이기 때문에 is_satisfied 함수가 실행될때 AndSpecification<Product>의 is_satisfied 함수가 실행됨
		// 위와 마찬가지로 AndSpecification는 Specification을 상속받았기 때문에 가능
		// AndSpecification의 is_satisfied 함수는 first, second의 is_satisfied 함수를 실행하고 둘다 true일때 true를 반환함
		auto red_and_small_things = bpf.filter(items, red_and_small);

		// 결과값 : red_and_small_things은 vector<Product*>
		for (auto& item : red_and_small_things)
			cout << item->name << " is red and small" << endl;

		// operator 사용시 앞쪽의 ColorSpecification 객체가 this로 들어가고, 뒤쪽의 SizeSpecification 객체가 other로 들어감
		// 그럼 자동으로 AndSpecification 객체가 생성되고, AndSpecification 객체의 first, second에 각각 ColorSpecification, SizeSpecification이 들어가게 됨
		auto spec = ColorSpecification(Color::red) && SizeSpecification(Size::small);
	}
	
	return 0;
}