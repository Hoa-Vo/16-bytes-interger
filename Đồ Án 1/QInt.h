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
	string operator*(QInt b);
	bool operator>(QInt b);
	bool operator<(QInt b);
	bool operator==(QInt b);
	QInt subBit(QInt b, QInt c);
	void transForCal(QInt& temp);
	QInt negativeToPositve();
	friend istream& operator>>(istream& is, QInt& q);
	friend ostream& operator<<(ostream& os, QInt& q);
	friend void twoComplement(QInt& q);
	void shiftRight(QInt& temp, QInt& q, bool& q1,bool result[]);
	void combineArray(QInt temp, QInt q,bool q1, bool result[]);
	void splitArray(bool result[], QInt& temp, QInt& q, bool& q1);
	int* subBit256bytes(int* bit1, int* bit2);
	void tranForCal256bytes(int*& bit);
	string multiplyResult(int* bit);
	void transferTo256bytes(bool result[],int*&bit);
	void initArray(int*& bit);
};

