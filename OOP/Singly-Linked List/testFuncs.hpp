#ifndef TESTFUNCS_HPP
#define TESTFUNCS_HPP

#include <string>
#include "SLList.hpp"
#include "tests.hpp"
#include "Money.hpp"

bool constbegderef()
{
	SLList<int> obj(5);
	SLList<int>::iterator it = obj.begin();
	
	return IS_EQUAL(5, *it);
}

bool testfront()
{
	SLList<std::string> obj("MONDO");

	return EXPECT_TRUE(obj.front() == "MONDO");
}

bool testPushBack()
{
	SLList<double> obj;
	obj.push_back(3.14);

	return IS_EQUAL(3.14, obj.front());
}



bool testErase(char p)
{
	SLList<std::string> obj;
	obj.push_back("HELLO");
	obj.push_back("CRUEL");
	obj.push_back("WORLD");
	obj.push_back("HERE'S");
	obj.push_back("JOHNNY");

	auto it = obj.begin();

	switch (p) {
	case 'b':
		it = obj.erase(it);
		return IS_EQUAL(std::string("CRUEL"), obj.front());
		break;
	case 'm':
		++it;
		it = obj.erase(it);
		return IS_EQUAL(std::string("WORLD"), *it);
		break;
	case 'e':
		while (*it != std::string("JOHNNY") && it != obj.end())
			++it;
		it = obj.erase(it);
		return nullptr == it;
		break;
	default:
		std::cout << "Default case?\n";
		return false;
		break;
	}
}

bool testClear()
{
	SLList<Money> obj;

	obj.push_back(7.67);
	obj.push_back(5);
	obj.push_back(Money(3, 50));

	obj.clear();

	obj.push_back(4);

	return IS_EQUAL(Money(4), obj.front());
}

bool testSize(char t)
{
	SLList<Money> obj;

	obj.push_back(4.5);
	obj.push_back(6);
	obj.push_back(Money(7, 37));

	auto it = obj.begin();

	switch (t) {
	case 'p':
		obj.push_back(800);
		return IS_EQUAL(4, obj.size());
		break;
	case 'e':
		it = obj.erase(it);
		return IS_EQUAL(2, obj.size());
		break;
	default:
		std::cout << "Default case?\n";
		return false;
		break;
	}
}

bool testPostfixInc()
{
	SLList<int> obj;
	std::stringstream ss;

	for (int i = 5; i < 8; i++)
		obj.push_back(i);
	
	for (auto it = obj.begin(); it != obj.end(); it++)
		ss << *it;
	
	return IS_EQUAL(std::string("567"), ss.str());
}

bool testEQUIVT()
{
	SLList<double> obj;

	obj.push_back(3.14);
	obj.push_back(5.67);
	obj.push_back(88);

	auto itONE = obj.begin();
	auto itTWO = obj.begin();
	itONE++;
	itTWO++;

	return itONE == itTWO;
}

bool testEQUIVF()
{
	SLList<double> obj;

	obj.push_back(3.14);
	obj.push_back(5.67);
	obj.push_back(88);

	auto itONE = obj.begin();
	auto itTWO = obj.begin();

	itTWO++;

	return !(itONE == itTWO);
}

bool testINEQUIVT()
{
	SLList<double> obj;

	obj.push_back(3.14);
	obj.push_back(5.67);
	obj.push_back(88);

	auto itONE = obj.begin();
	auto itTWO = obj.begin();

	itTWO++;

	return itONE != itTWO;
}

bool testINEQUIVF()
{
	SLList<double> obj;

	obj.push_back(3.14);
	obj.push_back(5.67);
	obj.push_back(88);

	auto itONE = obj.begin();
	auto itTWO = obj.begin();
	itONE++;
	itTWO++;

	return !(itONE != itTWO);
}


#endif