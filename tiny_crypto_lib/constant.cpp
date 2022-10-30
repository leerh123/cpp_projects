#include "constant.h"
#include"constant.h"
//错误代码
extern const short kE_LINT_DBZ = -1;//被零除
extern const short kE_LINT_OFL = -2;//上溢
extern const short kE_LINT_UFL = -3;//下溢
extern const short kE_LINT_MAL = -4;//内存分配错误
extern const short kE_LINT_NOR = -5;//寄存器不可用
extern const short kE_LINT_BOR = -6;//基数不合法
extern const short kE_LINT_MOD = -7;//模数为偶
extern const short kE_LINT_NPT = -8;//将空指针作为参数传递
extern const short kE_VCHECK_OFL = 1;//警告：数字过长
extern const short kE_VCHECK_LDZ = 2;//警告：前导零
extern const short kE_VCHECK_MEM = -1;//空指针

//常数
extern const unsigned int kBASE = 0X10000;//基数B
extern const unsigned int kBASEMINONE = 0XFFFFU;//B - 1
extern const unsigned long kDBASEMINONE = 0XFFFFFFFFUL;//B^2 - 1
extern const unsigned int kBASEDIV2 = 0X8000U;//B/2
extern const unsigned int kNOOFREGS = 16U;//寄存器标准编号
extern const unsigned int kBITPERDIG = 16U;//每个LINT数字中包含的二进制位数
extern const unsigned int kLDBITPERDGT = 4U;//以二为底kBITPERDIG的对数
extern const unsigned int kLINTMAXDIGIT = 256U;//LINT对象以B为基数的最大位数
extern const unsigned int kLINTMAXSHORT = kLINTMAXDIGIT + 1;//为LINT对象分配的USHORT个数
extern const unsigned int kLINTMAXBYTE = kLINTMAXSHORT << 1;//为LINT对象分配的字节数
extern const unsigned int kLINTMAXBIT = kLINTMAXDIGIT << 4;//LINT对象包含的最大二进制位数
extern const double kFLINT_VERSION = 0.1;//版本号
extern const std::pair<unsigned int, unsigned int> kLINT_SECURE = { 0X73,0 };//安全模式标识符


//函数

//检查n_l_是否是偶数
bool ISEVEN_L(const LINT& n_) {
	return (DIGITS_L(n_) == 0) || ((DIGITS_L(n_) > 0) && ((*(LSDPTR_L(n_)) & 1) == 0));
}
//检查n_l_是否是奇数
bool ISODD_L(const LINT& n_) {
	return (DIGITS_L(n_) > 0) && (((*(LSDPTR_L(n_))) & 1) == 1);
}
//模Nmax+1
void ANDMAX_L(LINT& n_) {
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
bool GE_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) > -1);
}
//比较a_>b_
bool GT_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) == 1);
}
//比较a_<b_
bool LT_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) == -1);
}
//比较两个LINT对象的最大值
LINT MAX_L(const LINT& a_, const LINT& b_) {
	return (GT_L(a_, b_) ? a_ : b_);
}
//比较两个LINT对象的最小值
LINT MIN_L(const LINT& a_, const LINT& b_) {
	return (LT_L(a_, b_) ? a_ : b_);
}
//比较a_==0
bool EQZ_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 0);
	return (equ_l(a_, tmp));
}
//比较a_==1
bool EQONE_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 1);
	return (equ_l(a_, tmp));
}
//比较a_>0
bool GTZ_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 0);
	return (GT_L(a_, tmp));
}

//将a_设为0
void SETZERO_L(LINT& a_) {
	a_[0] = 0;
}
//将a_设为1
void SETONE_L(LINT& a_) {
	u2lint_l(a_, 1);
}
//将a_设为2
void SETTWO_L(LINT& a_) {
	u2lint_l(a_, 2);
}
//将a_设为ul
void SET_L(LINT& a_, unsigned long ul) {
	ul2lint_l(a_, ul);
}
//将a_设置为Nmax
void SETMAX_L(LINT& a_) {
	SETDIGITS_L(a_, kLINTMAXDIGIT);
	for (auto begin = a_.begin() + 1; begin != a_.end(); begin++) {
		*(begin) = USHRT_MAX;
	}
}