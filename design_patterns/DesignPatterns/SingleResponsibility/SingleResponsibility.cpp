#include <iostream>
#include <fstream>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

/// 하나의 구조체가 하나의 책임만 가지도록 하는 것이 SRP
/// HOS_hero에 save 함수까지 넣으면 SRP를 위반함
/// 이름 : Single Responsibility Principle

// HOS 영웅의 이름과 스탯을 저장하는 구조체
struct HOS_hero
{
	string name;
	vector<string> stat;

	HOS_hero(string name) : name(name) {} // 생성자

	// stat에 추가하는 함수
	void add_stat(const string& s)
	{
		static int count = 0;
		stat.push_back(lexical_cast<string>(count++) + ": " + s);
	}

	//void save(const string& filename)
	//{
	//	ofstream file(filename);
	//	try
	//	{
	//		if (!file)
	//			throw std::exception("file open error");
	//
	//		for (auto& e : stat)
	//			file << e << endl;
	//
	//		cout << filename + " saved" << endl;
	//	}
	//	catch (std::exception& err)
	//	{
	//		cout << err.what() << endl;
	//		return;
	//	}
	//}
};

// 지속성 관리자
struct PersistenceManager
{
	// 이렇게 하면 HOS_hero의 save 함수가 PersistenceManager로 옮겨짐
	// 하나의 구조체가 하나의 책임만 가지도록 하는 것이 SRP
	void save(const HOS_hero& HOS, const string& filename)
	{
		ofstream file(filename);
		try
		{
			if (!file)
				throw std::exception("file open error");

			for (auto& e : HOS.stat)
				file << e << endl;

			cout << filename + " saved" << endl;
		}
		catch (std::exception& err)
		{
			cout << err.what() << endl;
			return;
		}
	}
};

int main()
{
	HOS_hero hero("Abathru");

	hero.add_stat("HP: 100");
	hero.add_stat("MP: 50");
	hero.add_stat("ramen");

	// hero.save("Abathru.txt");
	PersistenceManager pm;
	pm.save(hero, "Abathru.txt");
}
