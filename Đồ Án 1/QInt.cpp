#include "QInt.h"
QInt::QInt() {
	for (int i = 0; i < 4; i++)
		a[i] = 0;
}

istream& operator>>(istream& is, QInt& q) {
    string s;
    is >> s;
    int i = 3, j = 31;
    if (s[0] == '-') {
        s.erase(0, 1);
        q.setBit(q.a[0], 0);
    }
    if ((s[s.length() - 1] - '0') % 2) {
        q.setBit(q.a[i], j);
        j--;
    }
    else j--;
    while (1) {
        s = q.divideOnString(s, 2);
        if (s == "0")
            break;
        if ((s[s.length() - 1] - '0') % 2) {
            q.setBit(q.a[i], j);
        }
        j--;
        if (j < 0) {
            i--;
            j = 31;
        }
    }
    if (q.getBit(q.a[0],0)) {
        twoComplement(q);
    }
    return is;
}

ostream& operator<<(ostream& os, QInt& q) {
    os << q.binToDec();
    return os;
}
//Hàm đảo bit tại vị trí i
void QInt::reverseBitValue(int& x, int i){
    x = x ^ (1 << (31 - i));
}
//Hàm set bit tại vị trí i
void QInt::setBit(int& x, int i){
    x = x | (1 << (31 - i));
}
//Hàm lấy bit tại vị trí i
int QInt::getBit(int x, int i){
    return (x >> (31 - i)) & 1;
}
//Hàm chia chuỗi
string QInt::divideOnString(string number, int divisor){
    string result;
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor) {
        if (++idx > number.length())
            return "0";
        temp = temp * 10 + (number[idx] - '0');
    }
    while (number.size() > idx){
        result += (temp / divisor) + '0';
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }
    if (result.length() == 0)
        return "0";
    return result;
}
//Hàm nhân 1 số cho chính nó
string QInt::multiplyItseft(int x, string number) {
    int carry = 0;
    for (int i = 0; i < number.length(); i++) {
        int prod = (number[i] - '0') * x + carry; 
        number[i] = '0' + prod % 10;
        carry = prod / 10;
    }
    if (carry) {
        number.append(to_string(carry % 10));
    }
    return number;
}
//Hàm mũ cho số lớn
string QInt::power(int number, int exp){
    if (exp == 0) {
        return "1";
    }
    string result;
    int temp = number;
    while (temp != 0) {
        result.append(to_string(temp % 10));
        temp = temp / 10;
    }
    for (int i = 2; i <= exp; i++)
        result = multiplyItseft(number, result);
    reverse(result.begin(), result.end());
    return result;
}
//Hàm cộng chuỗi
string QInt::addString(string num1,string num2){
    if (num1.length() > num2.length())
        swap(num1, num2);
    string result;
    int l1 = num1.length(), l2 = num2.length();
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    int carry = 0;
    for (int i = 0; i < l1; i++){
        int sum = ((num1[i] - '0') + (num2[i] - '0') + carry);
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    for (int i = l1; i < l2; i++) {
        int sum = ((num2[i] - '0') + carry);
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    if (carry)
        result.push_back(carry + '0');
    reverse(result.begin(), result.end());
    return result;
}
//Chuyển từ 2-->10
string QInt::binToDec(){
    int exp = 127, count = 0;
    string result = "0";
    QInt temp = *this;
    if (getBit(a[0],0)) {
        transForCal(temp);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 32;j++) {
            if (temp.getBit(temp.a[i], j)) {
                string s1 = power(2, exp);
                result = addString(result, s1);
            }
            exp--;
        }
    }
    if (getBit(a[0],0)) {
        return result.insert(0,"-");
    }
    return result;
}
QInt QInt::operator+(QInt b) {
    QInt c;
    int carryBit = 0;
    for (int i = 3; i >=0; i--) {
        for (int j = 31; j >= 0; j--) {
            int temp = getBit(a[i], j) + getBit(b.a[i], j)+carryBit;
            if (temp <= 1) {
                carryBit = 0;
                if (temp == 1)
                    setBit(c.a[i], j);
            }
            else if (temp==2) {
                carryBit = 1;
            }
            else {
                carryBit = 1;
                setBit(c.a[i], j);
            }
        }
    }
    return c;
}

QInt QInt::operator-(QInt b){
    QInt c;
    QInt temp = b;
    if (b.binToDec()[0] == '-')
        temp = temp.negativeToPositve();
    else {
        twoComplement(temp);
        temp.setBit(temp.a[0], 0);
    }
    c = *this + temp;
    return c;
}
bool QInt::operator>(QInt b){
    string num1 = binToDec();
    string num2 = b.binToDec();
    int l1 = num1.length();
    int l2 = num2.length();
    if (num2[0] == '-' && num1[0] != '-')
        return true;
    else if (num1[0] == '-' && num2[0] != '-')
        return false;
    if (num1[0] == '-') {
        if (l1 < l2)
            return true;
        else if (l1 > l2)
            return false;
        else {
            for (int i = 0; i < num1.length(); i++) {
                if (num2[i] - '0' > num1[i] - '0')
                    return true;
            }
        }
        return false;
    }
    else {
        if (l1 > l2)
            return true;
        else if (l1 < l2)
            return false;
        else {
            for (int i = 0; i < num1.length(); i++) {
                if (num2[i] - '0' < num1[i] - '0')
                    return true;
            }
        }
        return false;
    }
}
//Hàm trừ 2 dãy bit
QInt QInt::subBit(QInt b, QInt c){
    QInt d;
    int carryBit = 0;
    for (int i = 3; i >= 0; i--) {
        for (int j = 31; j >= 0; j--) {
            int temp = b.getBit(b.a[i], j) - c.getBit(c.a[i], j) - carryBit;
            if (temp == 0) {
                carryBit = 0;
            }
            else if (temp < 0) {
                carryBit = 1;
                d.setBit(d.a[i], j);
         ;   }
            else {
                carryBit = 0;
                d.setBit(d.a[i], j);
            }
        }
    }
    return d;
}
//Xuất dãy bit
void QInt::outputBin() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 32; j++) {
            cout << getBit(a[i], j);
        }
    }
    cout << endl;
}
bool QInt::operator<(QInt b){
    if (*this > b)
        return false;
    else
        return true;
}
//Chuyển đổi về số không dấu để tính toán
void QInt::transForCal(QInt& temp) {
    QInt temp1;
    temp1.setBit(temp1.a[3], 31);
    temp = subBit(temp, temp1);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 32; j++) {
            temp.reverseBitValue(temp.a[i], j);
        }
    }
}
//Chuyển sang dạng bù 2
void twoComplement(QInt&q) {
    QInt temp;
    temp.setBit(temp.a[3], 31);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 32; j++) {
            if (i == 0 && j == 0)
                continue;
            else
                q.reverseBitValue(q.a[i], j);
        }
    }
    q = q + temp;
}
//Đổi số âm thành số dương
QInt QInt::negativeToPositve() {
    QInt temp = *this;
    transForCal(temp);
    return temp;
}
