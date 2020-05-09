#include "QFloat.h"
QFloat::QFloat() {
	for (int i = 0; i < 4; i++) {
		a[i] = 0;
	}
}
istream& operator>>(istream& is, QFloat& q){
	string s;
	is >> s;
	if (s == "0.0")
		return is;
	int sum = 0;
	if (s[0] == '-') {
		s.erase(0, 1);
		q.setBit(q.a[0], 0);
	}
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '.'){
			sum /= 10;
			break;
		}
		else {
			sum += s[i] - '0';
			sum *= 10;
		}
	}
	string pointPart;
	for (int i = s.length() - 1; s[i]!='.'; i--) {
		pointPart.push_back(s[i]);
	}
    reverse(pointPart.begin(), pointPart.end());
	pointPart.insert(0, "0.");
	string arr,brr;
	q.decPart(sum, arr);
	int cod = 112-arr.length();
	q.floatPart(pointPart, brr,cod);
	loadBit(arr, brr, q);
	return is;
}
int QFloat::getBit(int& x, int i){
	return (x >> (31 - i)) & 1;
}
ostream& operator<<(ostream& os, QFloat& q){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 32; j++) {
			os << q.getBit(q.a[i], j);
		}
	}
	return os;
}
void QFloat::decPart(int sum, string& arr) {
	if (sum == 0) {
		arr = "0";
		return;
	}
	while (sum) {
		arr.push_back('0'+sum % 2);
		sum /= 2;
	}
	reverse(arr.begin(), arr.end());
}
void QFloat::floatPart(string num, string& arr,int cod){
	int count = 0;
	if (num == "0.0") {
		arr = "0";
		return;
	}
	while(num!="1.0"){
		if (count == cod+1)
			break;
		count++;
		num = multiplyFloatString(num, 2);
		if (num[0]=='0') {
			arr.push_back('0');
		}
		else if (stof(num) > 1) {
			arr.push_back('1');
			num[0] = '0';
		}
		else
			arr.push_back('1');
	}
}
string QFloat::multiplyFloatString(string s, int num) {
	string temp;
	string decPart;
	decPart.push_back(s[0]);
	for (int i = s.length() - 1; s[i] != '.'; i--) {
		temp.push_back(s[i]);
	}
	reverse(temp.begin(), temp.end());
	int carry = 0;
	for (int i = temp.length() - 1; i >= 0; i--) {
		int prod = (temp[i] - '0') * num + carry;
		temp[i]= '0' + prod % 10;
		carry = prod / 10;
	}
	if (carry) {
		decPart[0] = '0' + carry % 10;
	}
	temp = decPart + "." + temp;
	for (int i = temp.length() - 1; i > 0; i--) {
		if (temp[i] == '0' && temp[i - 1] != '.') {
			temp.erase(i, i);
		}
		else 
			break;
	}
	return temp;
}
void loadBit(string num1, string num2, QFloat& q){
	int e = num1.length() - 1, idx = 0,idx2=0;
	string temp = num1 + num2;
	string temp1;
	for (int i = 1; i < num1.length(); i++) {
		temp1.push_back(num1[i]);
	}
	temp1 = temp1 + num2;
	int exp = 16383 + e;
	string sexp;
	q.decPart(exp, sexp);
	for (int j = 15; j >= 1; j--) {
		if (sexp[idx2++] == '1') {
			q.setBit(q.a[0], j);
		}
	}
	for (int j = 16; j < 32; j++) {
		if (temp1[idx++]=='1') {
			q.setBit(q.a[0], j);
		}
		if (idx == temp1.length())
			break;
	}
	if (idx != temp1.length()) {
		for (int i = 1; i < 4; i++) {
			for (int j = 0; j < 32; j++) {
				if (temp1[idx++] == '1') {
					q.setBit(q.a[i], j);
				}
			}
			if (idx == temp1.length())
				break;
		}
	}
}
void QFloat::setBit(int& x, int i){
	x = x | (1 << (31 - i));
}