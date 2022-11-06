#include "BasicOp.h"
#include"constant.h"
#include<algorithm>
#include<string>
using namespace std;
BasicOp::BasicOp()  {
	if (number_ != nullptr) {
		delete number_;
	}
	number_ = new LINT;
}

BasicOp::BasicOp(unsigned long _ul) {
	if (number_ != nullptr) {
		delete number_;
	}
	number_ = new LINT;
	ul2lint_l(*number_, _ul);
}

BasicOp::BasicOp(int _i) {
	if (number_ != nullptr) {
		delete number_;
	}
	number_ = new LINT;
	ul2lint_l(*number_,(unsigned long) _i);
}

BasicOp::BasicOp(unsigned int _i) {
	if (number_ != nullptr) {
		delete number_;
	}
	number_ = new LINT;
	ul2lint_l(*number_, (unsigned long)_i);
}

BasicOp::BasicOp(lint _u){
	if (number_ != nullptr) {
		delete number_;
	}
	number_ = new LINT;
	u2lint_l(*number_, _u);
}

BasicOp::BasicOp(const BasicOp& _b) {
	if (number_ != nullptr) {
		delete number_;
	}
	number_ = new LINT(*_b.number_);
}

BasicOp::BasicOp(BasicOp&& _b) noexcept {
	if (number_ != nullptr) {
		delete number_;
	}
	number_ = new LINT(*_b.number_);
}

BasicOp::BasicOp(const LINT& _b) {
	if (number_ != nullptr) {
		delete number_;
	}
	number_ = new LINT(_b);
}

BasicOp::BasicOp(const string& _s) {
	try {
		if (_s.size() > (kLINTMAXBIT / 4))
			throw invalid_argument("the string is too long");
	}
	catch (invalid_argument e) {
		cerr << e.what() << endl;
		exit(1);
	}
	if (number_ != nullptr) {
		delete number_;
	}
	number_ = new LINT;
	str2LINT_l(*number_, _s);
}

BasicOp& BasicOp::operator=(BasicOp _b) {
	swap(*this, _b);
	return *this;
}

BasicOp::~BasicOp() {
	delete number_;
}



void swap(BasicOp& _a, BasicOp& _b) {
	using std::swap;
	swap(_a.number_, _b.number_);
}

void BasicOp::set_max(){
	SETMAX_L(*number_);
}


BasicOp operator+(const BasicOp& _a, const BasicOp& _b) {
	LINT result;
	const LINT a = *(_a.number_);
	const LINT b = *(_b.number_);
	const lint* longer_number_msd_ptr, * longer_number_lsd_ptr;
	const lint* shorter_number_msd_ptr, * shorter_number_lsd_ptr;
	lint* result_msd_ptr = LSDPTR_L(result);
	unsigned long carry = 0x0;
	if (DIGITS_L(a) < DIGITS_L(b)) {
		shorter_number_lsd_ptr = LSDPTR_L(a);
		shorter_number_msd_ptr = MSDPTR_L(a);
		longer_number_lsd_ptr = LSDPTR_L(b);
		longer_number_msd_ptr = MSDPTR_L(b);
		SETDIGITS_L(result, DIGITS_L(b));
	}
	else {
		shorter_number_lsd_ptr = LSDPTR_L(b);
		shorter_number_msd_ptr = MSDPTR_L(b);
		longer_number_lsd_ptr = LSDPTR_L(a);
		longer_number_msd_ptr = MSDPTR_L(a);
		SETDIGITS_L(result, DIGITS_L(a));
	}
	while (shorter_number_lsd_ptr <= shorter_number_msd_ptr) {
		*(result_msd_ptr++) = (unsigned short)(carry = (unsigned long)(*(shorter_number_lsd_ptr++))
			+ (unsigned long)(*(longer_number_lsd_ptr++))
			+ (unsigned long)((unsigned short)(carry >> kBITPERDIG)));
	}
	while (longer_number_lsd_ptr <= longer_number_msd_ptr) {
		*(result_msd_ptr++) = (unsigned short)(carry = (unsigned long)(*(longer_number_lsd_ptr++))
			+ (unsigned long)((unsigned short)(carry >> kBITPERDIG)));
	}
	if (carry & kBASE) {
		//ÉÏÒç--mod(N+1)
		if (DIGITS_L(result) + 1 > (unsigned short)(kLINTMAXDIGIT)) {
			ANDMAX_L(result);
		}
		else {
			*result_msd_ptr = 1;
			SETDIGITS_L(result, DIGITS_L(result) + 1);
		}

	}
	return BasicOp(result);
}

BasicOp operator+(const BasicOp& _a, const lint& _b) {
	return _a + BasicOp(_b);
}

BasicOp& BasicOp::operator++() {
	*this = *this + 1;
	return *this;
}

BasicOp BasicOp::operator++(int) {
	BasicOp tmp (*this);
	*this = *this + 1;
	return tmp;
}

BasicOp& BasicOp::operator+=(const BasicOp& _a) {
	*this = *this + _a;
	return *this;
}

BasicOp& BasicOp::operator+=(lint _a) {
	*this = *this + _a;
	return *this;
}

BasicOp operator-(const BasicOp& _a, const BasicOp& _b) {
	LINT result;
	LINT a = *(_a.number_);
	LINT b = *(_b.number_);
	const lint* a_msd_ptr, * b_msd_ptr;
	lint* result_lsd_ptr;
	const lint* a_lsd_ptr, * b_lsd_ptr;
	a_msd_ptr = MSDPTR_L(a); 
	b_msd_ptr = MSDPTR_L(b);
	result_lsd_ptr = LSDPTR_L(result);
	a_lsd_ptr = LSDPTR_L(a);
	b_lsd_ptr = LSDPTR_L(b);
	unsigned long  carry = 0x0;
	//ÏÂÒç£¿
	if (cmp_l(a,b)==-1) {
		LINT max,one;
		SETMAX_L(max);
		SETONE_L(one);
		return (max - b + a + one);
	}
	else {
		SETDIGITS_L(result, DIGITS_L(a)); 
	}
	while (b_lsd_ptr <= b_msd_ptr) {
		*result_lsd_ptr++ = (unsigned short)(carry = (unsigned long)(*a_lsd_ptr++)
			- (unsigned long)(*b_lsd_ptr++)
			- ((carry & kBASE) >> kBITPERDIG));
	}
	while (a_lsd_ptr <= a_msd_ptr) {
		*result_lsd_ptr++ = (unsigned short)(carry = (unsigned long)(*a_lsd_ptr++)
			- ((carry & kBASE) >> kBITPERDIG));
	}
	RMLDZRS_L(result);

	return BasicOp(result);
	}

BasicOp operator-(const BasicOp& _a, const lint& _b) {
	return _a - BasicOp(_b);
}

BasicOp& BasicOp::operator--() {
	*this = *this - 1;
	return *this;
}

BasicOp BasicOp::operator--(int) {
	BasicOp tmp(*this);
	*this = *this - 1;
	return tmp;
}

BasicOp& BasicOp::operator-=(const BasicOp& _a) {
	*this = *this - _a;
	return *this;
}

BasicOp& BasicOp::operator-=(lint _a ) {
	*this = *this - _a;
	return *this;
}



bool operator>(const BasicOp& _a, const BasicOp& _b) {
	return GT_L(*(_a.number_), *(_b.number_));
}

bool operator<(const BasicOp& _a, const BasicOp& _b) {
	return LT_L(*(_a.number_), *(_b.number_));
}

bool operator==(const BasicOp& _a, const BasicOp& _b) {
	return equ_l(*(_a.number_), *(_b.number_));
}

bool operator!=(const BasicOp& _a, const BasicOp& _b) {
	return !(_a == _b);
}

bool operator>=(const BasicOp& _a, const BasicOp& _b) {
	return GE_L(*(_a.number_), *(_b.number_));
}

bool operator<=(const BasicOp& _a, const BasicOp& _b) {
	return !(_a > _b);
}



BasicOp mul(const BasicOp& _a, const BasicOp& _b) {
	LINTD result = { 0 };
	const LINT a = *_a.number_, b = *_b.number_;
	const lint* longer_number, * shorter_number;
	lint* result_lsd_ptr = LSDPTR_L(result);
	unsigned long carry = 0x0;
	if (EQZ_L(a) || EQZ_L(b)) {
		return BasicOp(0);
	}
	if (DIGITS_L(a) < DIGITS_L(b)) {
		longer_number = &b[0];
		shorter_number = &a[0];
	}
	else {
		longer_number = &a[0];
		shorter_number = &b[0];
	}
	const lint* longer_number_msd_ptr = longer_number + *longer_number;
	const lint* shorter_number_msd_ptr = shorter_number + *shorter_number;
	const lint* longer_number_lsd_ptr = longer_number + 1;
	const lint* shorter_number_lsd_ptr = shorter_number + 1;
	for (; shorter_number_lsd_ptr <= shorter_number_msd_ptr; shorter_number_lsd_ptr++, result_lsd_ptr++) {
		*result_lsd_ptr = (unsigned short)(carry = (unsigned long)(*longer_number_lsd_ptr) * (unsigned long)(*shorter_number_lsd_ptr)
			+ (unsigned long)(unsigned short)(carry >> kBITPERDIG));
	}
	*result_lsd_ptr = (unsigned short)(carry >> kBITPERDIG);

	lint* csptr = LSDPTR_L(result) + 1;
	const lint* aptr = longer_number + 2;
	for (; aptr <= longer_number_msd_ptr; csptr++, aptr++) {
		carry = 0x0;
		for (shorter_number_lsd_ptr = shorter_number + 1, result_lsd_ptr = csptr; shorter_number_lsd_ptr <= shorter_number_msd_ptr; shorter_number_lsd_ptr++, result_lsd_ptr++) {
			*result_lsd_ptr = (unsigned short)(carry = (unsigned long)(*aptr) * (unsigned long)(*shorter_number_lsd_ptr)
				+ (unsigned long)(*result_lsd_ptr) + (unsigned long)(unsigned short)(carry >> kBITPERDIG));
		}
		*result_lsd_ptr = (unsigned short)(carry >> kBITPERDIG);
	}
	SETDIGITS_L(result, DIGITS_L(a) + DIGITS_L(b));
	RMLDZRS_L(result);
	//ÉÏÒç
	if (DIGITS_L(result) > (unsigned short)(kLINTMAXDIGIT)) {
		ANDMAX_L(result);
	}

	LINT result_final;
	for (size_t i = 0; i < kLINTMAXDIGIT; i++) {
		result_final[i] = result[i];
	}
	return BasicOp(result_final);

}

BasicOp sqr(const BasicOp& _a) {
	LINT a_l = *_a.number_;
	LINTD p_l;
	lint* aptr_l, *csptr_l, * msdptra_l, * msdptrb_l, * msdptrc_l;
	lint* pptr_l, *bptr_l;
	unsigned short av;
	unsigned long carry;
	LINT pp_l;
	if (EQZ_L(a_l))
		return 0;
	msdptrb_l = MSDPTR_L(a_l);
	msdptra_l = msdptrb_l - 1;
	*LSDPTR_L(p_l) = 0;
	carry = 0;
	av = *LSDPTR_L(a_l);
	for (bptr_l = LSDPTR_L(a_l) + 1, pptr_l = LSDPTR_L(p_l) + 1; bptr_l <= msdptrb_l; bptr_l++, pptr_l++) {
		*pptr_l = (unsigned short)(carry = (unsigned long)av * (unsigned long)(*bptr_l) + (unsigned long)(unsigned short)(carry >> kBITPERDIG));
	}
	*pptr_l = (unsigned short)(carry >> kBITPERDIG);
	for (aptr_l = LSDPTR_L(a_l) + 1, csptr_l = LSDPTR_L(p_l) + 3; aptr_l <= msdptra_l; aptr_l++, csptr_l += 2) {
		carry = 0;
		av = *aptr_l;
		for (bptr_l = aptr_l + 1, pptr_l = csptr_l; bptr_l <= msdptrb_l; bptr_l++, pptr_l++) {
			*pptr_l = (unsigned short)(carry = (unsigned long)av * (unsigned long)(*bptr_l) + (unsigned long)(*pptr_l) + (unsigned long)(unsigned short)(carry >> kBITPERDIG));
		}
		*pptr_l = (unsigned short)(carry >> kBITPERDIG);
	}
	msdptrc_l = pptr_l;
	carry = 0;
	for (pptr_l = LSDPTR_L(p_l); pptr_l <= msdptrc_l; pptr_l++) {
		*pptr_l = (unsigned short)(carry = (((unsigned long)*pptr_l) << 1) + (unsigned long)(unsigned short)(carry >> kBITPERDIG));
	}
	*pptr_l = (unsigned short)(carry >> kBITPERDIG);
	carry = 0;
	for (bptr_l = LSDPTR_L(a_l), pptr_l = LSDPTR_L(p_l); bptr_l <= msdptrb_l; bptr_l++, pptr_l++) {
		*pptr_l = (unsigned short)(carry = (unsigned long)(*bptr_l) * (unsigned long)(*bptr_l) + (unsigned long)(*pptr_l) + (unsigned long)(unsigned short)(carry >> kBITPERDIG));
		pptr_l++;
		*pptr_l = (unsigned short)(carry = (unsigned long)(*pptr_l) + (carry >> kBITPERDIG));
	}
	SETDIGITS_L(p_l, DIGITS_L(a_l) << 1);
	RMLDZRS_L(p_l);
	if (DIGITS_L(p_l) > (unsigned short)kLINTMAXDIGIT) {
		ANDMAX_L(p_l);
	}
	for (size_t i = 0; i < kLINTMAXDIGIT; i++) {
		pp_l[i] = p_l[i];
	}

	return BasicOp(pp_l);
}

BasicOp operator*(const BasicOp& _a, const BasicOp& _b) {
	if (_a == _b) {
		return sqr(_a);
	}
	return mul(_a, _b);

}

BasicOp operator*(const BasicOp& _a, const lint& _b) {
	return _a * BasicOp(_b);
}

BasicOp& BasicOp::operator *=(const BasicOp& _a) {
	*this = *this * _a;
	return *this;
}

BasicOp& BasicOp::operator *=(lint _a) {
	*this = *this * _a;
	return *this;
}



BasicOp operator&(const BasicOp& _a, const BasicOp& _b) {
	if ((vcheck_l(*_a.number_) & vcheck_l(*_b.number_)) == false) {
		throw invalid_argument("the BasicOp object is illegal");
	}
	LINT result;
	lint* shorter_number_lsd_ptr, *longer_number_lsd_ptr;
	lint* last_ptr;
	if (DIGITS_L(*_a.number_) < DIGITS_L(*_b.number_)) {
		shorter_number_lsd_ptr = LSDPTR_L(*_a.number_);
		longer_number_lsd_ptr = LSDPTR_L(*_b.number_);
		last_ptr = MSDPTR_L(*_a.number_);
	}
	else {
		shorter_number_lsd_ptr = LSDPTR_L(*_b.number_);
		longer_number_lsd_ptr = LSDPTR_L(*_a.number_);
		last_ptr = MSDPTR_L(*_b.number_);
	}
	
	SETDIGITS_L(result, *(shorter_number_lsd_ptr - 1));
	lint* result_ptr = LSDPTR_L(result);
	while (shorter_number_lsd_ptr <= last_ptr) {
		*result_ptr++ = *shorter_number_lsd_ptr++ & *longer_number_lsd_ptr++;
	}
	RMLDZRS_L(result);
	return BasicOp(result);
	
}

BasicOp operator^(const BasicOp& _a, const BasicOp& _b) {
	if ((vcheck_l(*_a.number_) & vcheck_l(*_b.number_)) == false) {
		throw invalid_argument("the BasicOp object is illegal");
	}
	LINT result;
	lint* shorter_number_lsd_ptr, * shorter_number_msd_ptr, * longer_number_lsd_ptr, * longer_number_msd_ptr, * result_ptr;
	if (DIGITS_L(*_a.number_) < DIGITS_L(*_b.number_)) {
		shorter_number_lsd_ptr = LSDPTR_L(*_a.number_);
		longer_number_lsd_ptr = LSDPTR_L(*_b.number_);
		shorter_number_msd_ptr = MSDPTR_L(*_a.number_);
		longer_number_msd_ptr = MSDPTR_L(*_b.number_);
	}
	else {
		shorter_number_lsd_ptr = LSDPTR_L(*_b.number_);
		longer_number_lsd_ptr = LSDPTR_L(*_a.number_);
		shorter_number_msd_ptr = MSDPTR_L(*_b.number_);
		longer_number_msd_ptr = MSDPTR_L(*_a.number_);
	}
	SETDIGITS_L(result, *(longer_number_lsd_ptr - 1));
	result_ptr = LSDPTR_L(result);
	while (shorter_number_lsd_ptr <= shorter_number_msd_ptr) {
		*result_ptr++ = *shorter_number_lsd_ptr++ ^ *longer_number_lsd_ptr++;
	}
	while (longer_number_lsd_ptr <= longer_number_msd_ptr) {
		*result_ptr++ = *longer_number_lsd_ptr++;
	}
	RMLDZRS_L(result);
	return BasicOp(result);
}

BasicOp operator|(const BasicOp& _a, const BasicOp& _b) {
	if ((vcheck_l(*_a.number_) & vcheck_l(*_b.number_)) == false) {
		throw invalid_argument("the BasicOp object is illegal");
	}
	LINT result;
	lint* shorter_number_lsd_ptr, * shorter_number_msd_ptr, * longer_number_lsd_ptr, * longer_number_msd_ptr, * result_ptr;
	if (DIGITS_L(*_a.number_) < DIGITS_L(*_b.number_)) {
		shorter_number_lsd_ptr = LSDPTR_L(*_a.number_);
		longer_number_lsd_ptr = LSDPTR_L(*_b.number_);
		shorter_number_msd_ptr = MSDPTR_L(*_a.number_);
		longer_number_msd_ptr = MSDPTR_L(*_b.number_);
	}
	else {
		shorter_number_lsd_ptr = LSDPTR_L(*_b.number_);
		longer_number_lsd_ptr = LSDPTR_L(*_a.number_);
		shorter_number_msd_ptr = MSDPTR_L(*_b.number_);
		longer_number_msd_ptr = MSDPTR_L(*_a.number_);
	}
	SETDIGITS_L(result, *(longer_number_lsd_ptr - 1));
	result_ptr = LSDPTR_L(result);
	while (shorter_number_lsd_ptr <= shorter_number_msd_ptr) {
		*result_ptr++ = *shorter_number_lsd_ptr++ | *longer_number_lsd_ptr++;
	}
	while (longer_number_lsd_ptr <= longer_number_msd_ptr) {
		*result_ptr++ = *longer_number_lsd_ptr++;
	}
	RMLDZRS_L(result);
	return BasicOp(result);
}

BasicOp& BasicOp::operator &=(const BasicOp& _a) {
	*this = *this & _a;
	return *this;
}

BasicOp& BasicOp::operator ^=(const BasicOp& _a) {
	*this = *this ^ _a;
	return *this;
}

BasicOp& BasicOp::operator |=(const BasicOp& _a) {
	*this = *this | _a;
	return *this;
}

BasicOp BasicOp::left_shift() const {
	LINT result = *(this->number_);
	RMLDZRS_L(result);
	lint* ap_l, * msdptra_l;
	unsigned long carry = 0;
	msdptra_l = MSDPTR_L(result);
	for (ap_l = LSDPTR_L(result); ap_l <= msdptra_l; ap_l++) {
		*ap_l = (unsigned short)(carry = ((unsigned long)*ap_l << 1) | (carry >> kBITPERDIG));
	}
	if (carry >> kBITPERDIG) {
		if (DIGITS_L(result) < kLINTMAXDIGIT) {
			*ap_l = 1;
			INCDIGITS_L(result);
		}
		else {
			throw runtime_error("the left_shift function's result is overflow");
		}
	}
	RMLDZRS_L(result);
	return BasicOp(result); 
}

BasicOp BasicOp::right_shift() const {
	LINT result = *(this->number_);
	lint* ap_l, * lsdptra_l;
	unsigned short carry = 0;
	unsigned short help;
	lsdptra_l = LSDPTR_L(result);
	if (EQZ_L(result)) {
		return BasicOp(0);
	}
	for (ap_l = MSDPTR_L(result); ap_l >= lsdptra_l; ap_l--) {
		help = (unsigned short)((unsigned short)(*ap_l >> 1) | (unsigned short)(carry << (kBITPERDIG - 1)));
		carry = (unsigned short)(*ap_l & 1);
		*ap_l = help;
	}
	RMLDZRS_L(result);
	return BasicOp(result);

}

BasicOp operator<<(const BasicOp& _a, unsigned int _b) {
	if (vcheck_l(*_a.number_) == false) {
		throw invalid_argument("the BasicOp object is illegal");
	}
	BasicOp result = _a;
	for (size_t i = 0; i < _b; i++) {
		result = result.left_shift();
	}
	return result;
	
	
}

BasicOp operator>>(const BasicOp& _a, unsigned int _b) {
	if (vcheck_l(*_a.number_) == false) {
		throw invalid_argument("the BasicOp object is illegal");
	}
	BasicOp result = _a;
	for (size_t i = 0; i < _b; i++) {
		result = result.right_shift();
	}
	return result;
}

BasicOp& BasicOp::operator <<=(unsigned int _a) {
	*this = *this << _a;
	return *this;
}

BasicOp& BasicOp::operator >>=(unsigned int _a) {
	*this = *this >> _a;
	return *this;
}	


ostream& operator<<(ostream& _os, const BasicOp& _a) {
	_os << LINT2str_l(*_a.number_) << flush;
	return _os;
}


