#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include "Money.hpp"

// MEMBER FUNCTIONS
Money::Money()
	: dollars(0)
	, cents(0)
{
}

Money::Money(int d, int c)
	: dollars(d)
	, cents(c)
{
	validate();
}

Money::Money(int d)
	: dollars(d)
	, cents(0)
{
}

Money::Money(double m)
{
	int pennies = round(m * 100);
	dollars = pennies / 100;
	cents = pennies % 100;
}

int Money::getPennies() const
{
	return makePennies();
}

bool Money::isNegative() const
{
	if (dollars < 0 || cents < 0)
		return true;
	else
		return false;
}

const Money Money::operator -() const
{
	int negDollars = -dollars;
	int negCents = -cents;

	return Money(negDollars, negCents);
}

Money& Money::operator ++()
{
	++dollars;

	if (dollars > 0 && cents < 0)
		cents *= -1;

	return *this;
}

const Money Money::operator ++(int)
{
	Money temp = *this;
	++(*this);

	return temp;
}

Money& Money::operator --()
{
	--dollars;

	if (dollars < 0 && cents > 0)
		cents *= -1;

	return *this;
}

const Money Money::operator --(int)
{
	Money temp = *this;
	--(*this);

	return temp;
}

int Money::makePennies() const
{
	return (dollars * 100) + cents;
}

void Money::validate()
{
	if (dollars < 0 && cents > 0)
		cents *= -1;
	else if (cents < 0 && dollars > 0)
		dollars *= -1;
}

// NON-MEMBER FRIEND FUNCTIONS
const Money operator +(const Money &left, const Money &right)
{
	int leftPennies = left.makePennies();
	int rightPennies = right.makePennies();
	int sumPennies = leftPennies + rightPennies;

	return Money(sumPennies / 100, sumPennies % 100);	
}

const Money operator -(const Money &left, const Money &right)
{
	int leftPennies = left.makePennies();
	int rightPennies = right.makePennies();
	int difference = leftPennies - rightPennies;

	return Money(difference / 100, difference % 100);
}

const Money operator *(const Money &left, const int right)
{
	int leftPennies = left.makePennies();
	int product = leftPennies * right;

	return Money(product / 100, product % 100);
}

const Money operator *(const int left, const Money &right)
{
	return (right * left);
}

const Money operator *(const Money &left, const double right)
{
	int leftPennies = left.makePennies();
	double product = round(static_cast<double>(leftPennies) * right);
	int finalPennies = static_cast<int>(product);

	return Money(finalPennies / 100, finalPennies % 100);
}

const Money operator *(const double left, const Money &right)
{
	return (right * left);
}

bool operator <(const Money &left, const Money &right)
{
	if (left.dollars < right.dollars)
		return true;
	else if (left.dollars == right.dollars && left.cents < right.cents)
		return true;
	else
		return false;
}

bool operator <=(const Money &left, const Money &right)
{
	return (!(right < left));
}

bool operator >(const Money &left, const Money &right)
{
	return (right < left);
}

bool operator >=(const Money &left, const Money &right)
{
	return (!(left < right));
}

bool operator ==(const Money &left, const Money &right)
{
	return (!(left < right) && !(right < left));
}

bool operator !=(const Money &left, const Money &right)
{
	return !(left == right);
}

std::ostream& operator <<(std::ostream &outStream, const Money &right)
{
	bool neg = right.isNegative();
	std::string value;

	if (neg)
		value.push_back('(');
	value = value + "$" + std::to_string(abs(right.dollars)) + ".";
	if (abs(right.cents) < 10)
		value.push_back('0');
	value = value + std::to_string(abs(right.cents));
	if (neg)
		value.push_back(')');

	outStream << value;

	return outStream;
}

std::istream& operator >>(std::istream &inStream, Money &right)
{
	std::string input;
	inStream >> input;

	// Flush stream after getting what I need
	inStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (input.at(0) == '$') {
		input.erase(0, 1);
	}
	
	std::string::size_type sz;
	double value = std::stod(input, &sz);
	if (sz != input.length())
		value = 0;
	
	int pennies = round(value * 100);
	right.dollars = pennies / 100;
	right.cents = pennies % 100;

	return inStream;
}