#include"constant.h"
//将n_l_的位数设置为a_
inline void SETDIGITS_L(LINT& n_, lint a_) {
	n_[0] = a_;
}
//获取n_l_的位数
inline lint DIGITS_L(const LINT& n_) {
	return n_[0];
}
//获取最低有效位的指针
inline lint* LSDPTR_L(LINT& n_) {
	if (DIGITS_L(n_) == 0) {
		return nullptr;
	}
	return &n_[1];
}
inline const lint* LSDPTR_L(const LINT& n_) {
	if (DIGITS_L(n_) == 0) {
		return nullptr;
	}
	return &n_[1];
}
//获取最高有效位的指针
inline lint* MSDPTR_L(LINT& n_) {
	if (DIGITS_L(n_) == 0) {
		return nullptr;
	}
	return &n_[DIGITS_L(n_)];
}
inline const lint* MSDPTR_L(const LINT& n_) {
	if (DIGITS_L(n_) == 0) {
		return nullptr;
	}
	return &n_[DIGITS_L(n_)];
}
//检查n_l_是否是偶数
inline bool ISEVEN_L(const LINT& n_) {
	return (DIGITS_L(n_) == 0) || ((DIGITS_L(n_) > 0) && ((*(LSDPTR_L(n_)) & 1) == 0));
}
//检查n_l_是否是奇数
inline bool ISODD_L(const LINT& n_) {
	return (DIGITS_L(n_) > 0) && ((*(LSDPTR_L(n_)) & 1) == 1);
}
//位数减一
inline void DECDIGITS_L(LINT& n_) {
	if (n_[0] == 0)
		return;
	n_[0]--;
}
//位数加一
inline void INCDIGITS_L(LINT& n_) {
	n_[0]++;
}
//去除前导零
inline void RMLDZRS_L(LINT& n_) {
	while ((DIGITS_L(n_) > 0) && (*(MSDPTR_L(n_)) == 0))
		DECDIGITS_L(n_);
}
//模Nmax+1
inline void ANDMAX_L(LINT& n_) {
	SETDIGITS_L(n_, std::min(DIGITS_L(n_), (lint)kLINTMAXDIGIT));
	RMLDZRS_L(n_);
}
//比较两个LINT对象是否相等
bool equ_l(const LINT& a_, const LINT& b_) {
	const lint* msdptr_a, * msdptr_b;
	lint la = DIGITS_L(a_);
	lint lb = DIGITS_L(b_);
	if (la == 0 && lb == 0)
		return true;
	while (a_[la] == 0 && la > 0) {
		la--;
	}
	while (b_[lb] == 0 && lb > 0) {
		lb--;
	}
	if (la != lb)
		return false;
	if (la == 0 && lb == 0)
		return true;
	msdptr_a = &a_[la];
	msdptr_b = &b_[lb];
	while ((*msdptr_a == *msdptr_b) && (msdptr_b > &a_[0])) {
		msdptr_a--;
		msdptr_b--;
	}
	return (msdptr_a > &a_[0] ? false : true);
}
//比较两个LINT对象(a_>b_->1; a_<b_->-1; a_==b_->0)
int cmp_l(const LINT& a_, const LINT& b_) {
	const lint* msdptr_a, * msdptr_b;
	lint la = DIGITS_L(a_);
	lint lb = DIGITS_L(b_);
	if (la == 0 && lb == 0)
		return 0;
	while (a_[la] == 0 && la > 0) {
		la--;
	}
	while (b_[lb] == 0 && lb > 0) {
		lb--;
	}
	if (la > lb)
		return 1;
	if (la < lb)
		return -1;
	if (la == 0 && lb == 0)
		return 0;


	msdptr_a = &a_[la];
	msdptr_b = &b_[lb];
	while ((*msdptr_a == *msdptr_b) && (msdptr_b > &a_[0])) {
		msdptr_a--;
		msdptr_b--;
	}
	if (msdptr_a == &a_[0])
		return 0;
	if (*msdptr_a > *msdptr_b)
		return 1;
	return -1;
}
//复制一个LINT对象
void cpy_l(LINT& dest_, const LINT& src_) {
	dest_ = src_;
	RMLDZRS_L(dest_);
}
//将一个unsigned long 类型的数字转换为LINT类型对象
void ul2lint_l(LINT& num_, unsigned long ul) {
	*LSDPTR_L(num_) = (lint)(ul & 0xffff);
	*(LSDPTR_L(num_) + 1) = (lint)((ul >> 16) & 0xffff);
	SETDIGITS_L(num_, 2);
	RMLDZRS_L(num_);
}
//将一个unsigned short 类型的数字转换为LINT类型对象
void u2lint_l(LINT& num_, unsigned short u) {
	num_[1] = u;
	SETDIGITS_L(num_, 1);
	RMLDZRS_L(num_);
}
//比较a_>=b_
inline bool GE_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) > -1);
}
//比较a_>b_
inline bool GT_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) == 1);
}
//比较a_<b_
inline bool LT_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) == -1);
}
//比较两个LINT对象的最大值
inline LINT MAX_L(const LINT& a_, const LINT& b_) {
	return (GT_L(a_, b_) ? a_ : b_);
}
//比较两个LINT对象的最小值
inline LINT MIN_L(const LINT& a_, const LINT& b_) {
	return (LT_L(a_, b_) ? a_ : b_);
}
//比较a_==0
inline bool EQZ_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 0);
	return (equ_l(a_, tmp));
}
//比较a_==1
inline bool EQONE_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 1);
	return (equ_l(a_, tmp));
}
//比较a_>0
inline bool GTZ_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 0);
	return (GT_L(a_, tmp));
}

//将a_设为0
inline void SETZERO_L(LINT& a_) {
	a_[0] = 0;
}
//将a_设为1
inline void SETONE_L(LINT& a_) {
	u2lint_l(a_, 1);
}
//将a_设为2
inline void SETTWO_L(LINT& a_) {
	u2lint_l(a_, 2);
}
//将a_设为ul
inline void SET_L(LINT& a_, unsigned long ul) {
	ul2lint_l(a_, ul);
}
