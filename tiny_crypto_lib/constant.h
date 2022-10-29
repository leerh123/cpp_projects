#pragma once
#include<utility>
#include<array>
#include<algorithm>

//错误代码
const short kE_LINT_DBZ = -1;//被零除
const short kE_LINT_OFL = -2;//上溢
const short kE_LINT_UFL = -3;//下溢
const short kE_LINT_MAL = -4;//内存分配错误
const short kE_LINT_NOR = -5;//寄存器不可用
const short kE_LINT_BOR = -6;//基数不合法
const short kE_LINT_MOD = -7;//模数为偶
const short kE_LINT_NPT = -8;//将空指针作为参数传递
const short kE_VCHECK_OFL = 1;//警告：数字过长
const short kE_VCHECK_LDZ = 2;//警告：前导零
const short kE_VCHECK_MEM = -1;//空指针

//常数
const unsigned int kBASE = 0X10000;//基数B
const unsigned int kBASEMINONE = 0XFFFFU;//B - 1
const unsigned long kDBASEMINONE = 0XFFFFFFFFUL;//B^2 - 1
const unsigned int kBASEDIV2 = 0X8000U;//B/2
const unsigned int kNOOFREGS = 16U;//寄存器标准编号
const unsigned int kBITPERDIG = 16U;//每个LINT数字中包含的二进制位数
const unsigned int kLDBITPERDGT = 4U;//以二为底kBITPERDIG的对数
const unsigned int kLINTMAXDIGIT = 256U;//LINT对象以B为基数的最大位数
const unsigned int kLINTMAXSHORT = kLINTMAXDIGIT + 1;//为LINT对象分配的USHORT个数
const unsigned int kLINTMAXBYTE = kLINTMAXSHORT << 1;//为LINT对象分配的字节数
const unsigned int kLINTMAXBIT = kLINTMAXDIGIT << 4;//LINT对象包含的最大二进制位数
const double kFLINT_VERSION = 0.1;//版本号
const std::pair<const unsigned int, const unsigned int> kLINT_SECURE = { 0X73,0 };//安全模式标识符

//类型
using lint = unsigned short;
using LINT = std::array<lint, kLINTMAXDIGIT + 1>;
using LINTD = std::array<lint, (kLINTMAXDIGIT << 1) + 1>;
using LINTQ = std::array<lint, (kLINTMAXDIGIT << 2) + 1>;

//函数

//将n_l_的位数设置为a_
inline void SETDIGITS_L(LINT& n_, lint a_);
// 获取n_l_的位数
inline lint DIGITS_L(const LINT & n_);
//获取最低有效位的指针
inline lint* LSDPTR_L(LINT& n_);
inline const lint* LSDPTR_L(const LINT& n_);
//获取最高有效位的指针
inline lint* MSDPTR_L(LINT& n_);
inline const lint* MSDPTR_L(const LINT& n_);
//检查n_l_是否是偶数
inline bool ISEVEN_L(const LINT& n_);
//检查n_l_是否是奇数
inline bool ISODD_L(const LINT& n_);
//位数减一
inline void DECDIGITS_L(LINT& n_);
//位数加一
inline void INCDIGITS_L(LINT& n_);
// 去除前导零
inline void RMLDZRS_L(LINT & n_);
//模Nmax+1
inline void ANDMAX_L(LINT& n_);
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
inline bool GE_L(const LINT& a_, const LINT& b_);
//比较a_>b_
inline bool GT_L(const LINT& a_, const LINT& b_);
//比较a_<b_
inline bool LT_L(const LINT& a_, const LINT& b_);
//比较两个LINT对象的最大值
inline LINT MAX_L(const LINT& a_, const LINT& b_);
//比较两个LINT对象的最小值
inline LINT MIN_L(const LINT& a_, const LINT& b_);
//比较a_==0
inline bool EQZ_L(LINT& a_);
//比较a_==1
inline bool EQONE_L(LINT& a_);
//比较a_>0
inline bool GTZ_L(LINT& a_);
//将a_设为0
inline void SETZERO_L(LINT& a_);
//将a_设为1
inline void SETONE_L(LINT& a_);
//将a_设为2
inline void SETTWO_L(LINT& a_);
//将a_设为ul
inline void SET_L(LINT& a_, unsigned long ul);
