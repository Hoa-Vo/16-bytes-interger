#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class QFloat
{
	int a[4];
public:
	QFloat();
	friend istream& operator>>(istream& is, QFloat& q);
	friend ostream& operator<<(ostream& os, QFloat& q);
	friend void loadBit(string num1, string num2,QFloat&q);
	void decPart(int sum, string& arr);
	void floatPart(string num, string& arr, int cod);
	void setBit(int& x, int i);
	int getBit(int& x, int i);
	string multiplyFloatString(string s, int num);
};

