#include"constant.h"
#include"BasicOp.h"
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

int main() {
	string a = "0x123456789abcdef";
	BasicOp c = a;
	cout << "c: " << c << endl;
	cout << "c*c: " << c * c << endl;
	cout << "c*2: " << c * 2 << endl;
	cout << "++c: " << ++c << endl;
	c--;
	cout << "--c: " << --c << endl;
	c++;
	cout << "c^1: " << (c ^ 1) << endl;
	cout << "c&1: " << (c & 1) << endl;
	cout << "c|1: " << (c | 1) << endl;
	cout << "c>1: " << boolalpha << (c > 1) << endl;
	cout << "c<<2: " << (c << 2) << endl;
	cout << "c>>2: " << (c >> 2) << endl;
	BasicOp b;
	b.set_max();
	cout << "c+max: " << b + c << endl;
	cout << "max-max: " << b - b << endl;
	cout << "0*max: " << 0 * c << endl;
	cout << "c>max: " << boolalpha << (c > b) << endl;
}