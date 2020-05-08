#pragma once
#include<iostream>
#include<string.h>
#include<string>
using namespace std;
class QInt
{
	int a[4];
public:
	QInt();
	void setBit(int& x, int i);
	void reverseBitValue(int& x, int i);
	void outputBin();
	int getBit(int x, int i);
	string divideOnString(string number, int divisor);
	string multiplyItseft(int x, string number);
	string power(int number, int exp);
	string addString(string num1, string num2);
	string binToDec();
	QInt operator+(QInt b);
	QInt operator-(QInt b);
	bool operator>(QInt b);
	bool operator<(QInt b);
	QInt subBit(QInt b, QInt c);
	void transForCal(QInt& temp);
	QInt negativeToPositve();
	friend istream& operator>>(istream& is, QInt& q);
	friend ostream& operator<<(ostream& os, QInt& q);
	friend void twoComplement(QInt& q);
};

