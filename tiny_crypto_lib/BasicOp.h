#pragma once
#include"constant.h"
#include<iostream>
#include<array>
#include<string>
using std::ostream;
using std::array;

class BasicOp
{
	friend void swap(BasicOp&, BasicOp&);

	friend BasicOp operator+(const BasicOp&, const BasicOp&);
	friend BasicOp operator+(const BasicOp&, const lint&);
	friend BasicOp operator-(const BasicOp&, const BasicOp&);
	friend BasicOp operator-(const BasicOp&, const lint&);

	friend bool operator>(const BasicOp&, const BasicOp&);
	friend bool operator<(const BasicOp&, const BasicOp&);
	friend bool operator==(const BasicOp&, const BasicOp&);
	friend bool operator!=(const BasicOp&, const BasicOp&);
	friend bool operator>=(const BasicOp&, const BasicOp&);
	friend bool operator<=(BasicOp&, BasicOp&);

	friend BasicOp mul(const BasicOp& _a, const BasicOp& _b);
	friend BasicOp sqr(const BasicOp& _a);
	friend BasicOp operator*(const BasicOp&, const BasicOp&);
	friend BasicOp operator*(const BasicOp&, const lint&);
	
	friend BasicOp operator%(const BasicOp&, const BasicOp&);
	friend BasicOp operator%(const BasicOp&, const lint&);
	friend BasicOp operator/(const BasicOp&, const BasicOp&);
	friend BasicOp operator/(const BasicOp&, const lint&);

	friend BasicOp operator&(const BasicOp& _a, const BasicOp& _b);
	friend BasicOp operator^(const BasicOp& _a, const BasicOp& _b);
	friend BasicOp operator|(const BasicOp& _a, const BasicOp& _b);
	friend BasicOp operator<<(const BasicOp& _a, unsigned int _b);
	friend BasicOp operator>>(const BasicOp& _a, unsigned int _b);

	friend ostream& operator<<(ostream&, const BasicOp&);

public:
	BasicOp();
	BasicOp(unsigned long);
	BasicOp(int);
	BasicOp(unsigned int);
	BasicOp(lint);
	BasicOp(const BasicOp&);
	BasicOp(BasicOp&&) noexcept;
	BasicOp(const LINT&);
	//输入一个十六进制字符串
	BasicOp(const std::string&);
	BasicOp& operator=(BasicOp);
	~BasicOp();

	void set_max();
	
	BasicOp& operator++();
	BasicOp operator++(int);
	BasicOp& operator+=(const BasicOp&);
	BasicOp& operator+=(lint);
	BasicOp& operator--();
	BasicOp operator--(int);
	BasicOp& operator-=(const BasicOp&);
	BasicOp& operator-=(lint);

	BasicOp& operator *=(const BasicOp&);
	BasicOp& operator *=(lint);
	
	BasicOp& operator %=(const BasicOp&);
	BasicOp& operator %=(lint);
	BasicOp& operator /=(const BasicOp&);
	BasicOp& operator /=(lint);

	BasicOp& operator &=(const BasicOp& _a);
	BasicOp& operator ^=(const BasicOp& _a);
	BasicOp& operator |=(const BasicOp& _a);
	BasicOp& operator <<=(unsigned int _a);
	BasicOp& operator >>=(unsigned int _a);


private:
	LINT* number_ = nullptr;

	//左移一位
	BasicOp left_shift() const;
	//右移一位
	BasicOp right_shift()const;
	
};
void swap(BasicOp&, BasicOp&);

BasicOp operator+(const BasicOp&, const BasicOp&);
BasicOp operator+(const BasicOp&, const lint&);
BasicOp operator-(const BasicOp&, const BasicOp&);
BasicOp operator-(const BasicOp&, const lint&);

bool operator>(const BasicOp&, const BasicOp&);
bool operator<(const BasicOp&, const BasicOp&);
bool operator==(const BasicOp&, const BasicOp&);
bool operator!=(const BasicOp&, const BasicOp&);
bool operator>=(const BasicOp&, const BasicOp&);
bool operator<=(const BasicOp&, const BasicOp&);


BasicOp mul(const BasicOp& _a, const BasicOp& _b);
BasicOp sqr(const BasicOp& _a);
BasicOp operator*(const BasicOp&, const BasicOp&);
BasicOp operator*(const BasicOp&, const lint&);


BasicOp operator%(const BasicOp&, const BasicOp&);
BasicOp operator%(const BasicOp&, const lint&);
BasicOp operator/(const BasicOp&, const BasicOp&);
BasicOp operator/(const BasicOp&, const lint&);

BasicOp operator&(const BasicOp& _a, const BasicOp& _b);
BasicOp operator^(const BasicOp& _a, const BasicOp& _b);
BasicOp operator|(const BasicOp& _a, const BasicOp& _b);
BasicOp operator<<(const BasicOp& _a, unsigned int _b);
BasicOp operator>>(const BasicOp& _a, unsigned int _b);


ostream& operator<<(ostream&, const BasicOp&);

