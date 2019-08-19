#ifndef MONEY_HPP
#define MONEY_HPP

#include <iostream>

class Money {
public:
	Money();
	Money(int d, int c);
	Money(int d);
	Money(double m);
	int getPennies() const;
	bool isNegative() const;

	const Money operator -() const;
	Money& operator ++();
	const Money operator ++(int);
	Money& operator --();
	const Money operator --(int);
	friend const Money operator +(const Money &left, const Money &right);
	friend const Money operator -(const Money &left, const Money &right);
	friend const Money operator *(const Money &left, const int right);
	friend const Money operator *(const int left, const Money &right);
	friend const Money operator *(const Money &left, const double right);
	friend const Money operator *(const double left, const Money &right);
	friend bool operator <(const Money &left, const Money &right);
	friend bool operator <=(const Money &left, const Money &right);
	friend bool operator >(const Money &left, const Money &right);
	friend bool operator >=(const Money &left, const Money &right);
	friend bool operator ==(const Money &left, const Money &right);
	friend bool operator !=(const Money &left, const Money &right);
	friend std::ostream& operator <<(std::ostream &outStream, const Money &right);
	friend std::istream& operator >>(std::istream &inStream, Money &right);
private:
	int dollars;
	int cents;
	// Helper functions
	int makePennies() const;	// EXTRA
	void validate();			// EXTRA
};

#endif