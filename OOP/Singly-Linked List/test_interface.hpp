#ifndef TEST_INTERFACE_HPP
#define TEST_INTERFACE_HPP

#include <iostream>
#include <iomanip>
#include "testFuncs.hpp"
#include "tests.hpp"
#include "SLList.hpp"

void runTests()
{
    using std::cout;
    using std::left;
    using std::setw;
    using std::endl;

    const int COL = 70;

    char prev = cout.fill('.');
    cout << "SLList Class Tests\n";
    cout << setw(COL) << left << "Contructor (First Item Provided), begin(), & iterator::operator*" << constbegderef() << endl;
    cout << setw(COL) << left << "Empty()" << EXPECT_TRUE(SLList<double>().empty()) << endl;
    cout << setw(COL) << left << "front()" << testfront() << endl;
    cout << setw(COL) << left << "Basic size()" << EXPECT_TRUE(SLList<char>('a').size() == 1) << endl;
    cout << setw(COL) << left << "Default Constructor" << EXPECT_TRUE(SLList<int>().size() == 0) << endl;
    cout << setw(COL) << left << "push_back()" << testPushBack() << endl;
    cout << setw(COL) << left << "erase() (first)" << testErase('b') << endl;
    cout << setw(COL) << left << "erase() (middle) & iterator operator++()" << testErase('m') << endl;
    cout << setw(COL) << left << "erase() (last)" << testErase('e') << endl;
    cout << setw(COL) << left << "clear()" << testClear() << endl;
    cout << setw(COL) << left << "size() (after push_back)" << testSize('p') << endl;
    cout << setw(COL) << left << "size() (after erase)" << testSize('e') << endl;
    cout << setw(COL) << left << "iterator operator++(int)" << testPostfixInc() << endl;
    cout << setw(COL) << left << "iterator Equality (T)" << testEQUIVT() << endl;
    cout << setw(COL) << left << "iterator Equality (F)" << testEQUIVF() << endl;
    cout << setw(COL) << left << "iterator Inequality (T)" << testINEQUIVT() << endl;
    cout << setw(COL) << left << "iterator Inequality (F)" << testINEQUIVF() << endl;

    cout.fill(prev);
}

#endif
