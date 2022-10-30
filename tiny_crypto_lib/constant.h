#pragma once
#include<utility>
#include<array>
#include<algorithm>

//错误代码
extern const short kE_LINT_DBZ;//被零除
extern const short kE_LINT_OFL;//上溢
extern const short kE_LINT_UFL;//下溢
extern const short kE_LINT_MAL;//内存分配错误
extern const short kE_LINT_NOR;//寄存器不可用
extern const short kE_LINT_BOR;//基数不合法
extern const short kE_LINT_MOD;//模数为偶
extern const short kE_LINT_NPT;//将空指针作为参数传递
extern const short kE_VCHECK_OFL;//警告：数字过长
extern const short kE_VCHECK_LDZ;//警告：前导零
extern const short kE_VCHECK_MEM;//空指针

//常数
extern const unsigned int kBASE;//基数B
extern const unsigned int kBASEMINONE;//B - 1
extern const unsigned long kDBASEMINONE;//B^2 - 1
extern const unsigned int kBASEDIV2;//B/2
extern const unsigned int kNOOFREGS;//寄存器标准编号
extern const unsigned int kBITPERDIG;//每个LINT数字中包含的二进制位数
extern const unsigned int kLDBITPERDGT;//以二为底kBITPERDIG的对数
extern const unsigned int kLINTMAXDIGIT;//LINT对象以B为基数的最大位数
extern const unsigned int kLINTMAXSHORT;//为LINT对象分配的USHORT个数
extern const unsigned int kLINTMAXBYTE;//为LINT对象分配的字节数
extern const unsigned int kLINTMAXBIT;//LINT对象包含的最大二进制位数
extern const double kFLINT_VERSION;//版本号
extern const std::pair<unsigned int, unsigned int> kLINT_SECURE;//安全模式标识符

//类型
using lint = unsigned short;
using LINT = std::array<lint, 257>;//kLINTMAXDIGIT + 1
using LINTD = std::array<lint, 513>;//(kLINTMAXDIGIT << 1) + 1
using LINTQ = std::array<lint, 1025>;//(kLINTMAXDIGIT << 2) + 1

//函数
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
	return &n_[1];
}
inline const lint* LSDPTR_L(const LINT& n_) {
	return &n_[1];
}
//获取最高有效位的指针
inline lint* MSDPTR_L(LINT& n_) {
	return &n_[DIGITS_L(n_)];
}
inline const lint* MSDPTR_L(const LINT& n_) {
	return &n_[DIGITS_L(n_)];
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
//检查n_l_是否是偶数
bool ISEVEN_L(const LINT& n_);
//检查n_l_是否是奇数
bool ISODD_L(const LINT& n_);
//模Nmax+1
void ANDMAX_L(LINT& n_);
//比较两个LINT对象是否相等
bool equ_l(const LINT& a_, const LINT& b_);
//比较两个LINT对象(a_>b_->1; a_<b_->-1; a_==b_->0)
int cmp_l(const LINT& a_, const LINT& b_);
//复制一个LINT对象
void cpy_l(LINT& dest_, const LINT& src_);
//将一个unsigned long 类型的数字转换为LINT类型对象
void ul2lint_l(LINT& num_, unsigned long ul);
//将一个unsigned short 类型的数字转换为LINT类型对象
void u2lint_l(LINT& num_, unsigned short u);
//比较a_>=b_
bool GE_L(const LINT& a_, const LINT& b_);
//比较a_>b_
bool GT_L(const LINT& a_, const LINT& b_);
//比较a_<b_
bool LT_L(const LINT& a_, const LINT& b_);
//比较两个LINT对象的最大值
LINT MAX_L(const LINT& a_, const LINT& b_);
//比较两个LINT对象的最小值
LINT MIN_L(const LINT& a_, const LINT& b_);
//比较a_==0
bool EQZ_L(LINT& a_);
//比较a_==1
bool EQONE_L(LINT& a_);
//比较a_>0
bool GTZ_L(LINT& a_);
//将a_设为0
void SETZERO_L(LINT& a_);
//将a_设为1
void SETONE_L(LINT& a_);
//将a_设为2
void SETTWO_L(LINT& a_);
//将a_设为ul
void SET_L(LINT& a_, unsigned long ul);
//将a_设置为Nmax
void SETMAX_L(LINT& a_);


