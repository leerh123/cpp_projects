#include "constant.h"
#include"constant.h"
//�������
extern const short kE_LINT_DBZ = -1;//�����
extern const short kE_LINT_OFL = -2;//����
extern const short kE_LINT_UFL = -3;//����
extern const short kE_LINT_MAL = -4;//�ڴ�������
extern const short kE_LINT_NOR = -5;//�Ĵ���������
extern const short kE_LINT_BOR = -6;//�������Ϸ�
extern const short kE_LINT_MOD = -7;//ģ��Ϊż
extern const short kE_LINT_NPT = -8;//����ָ����Ϊ��������
extern const short kE_VCHECK_OFL = 1;//���棺���ֹ���
extern const short kE_VCHECK_LDZ = 2;//���棺ǰ����
extern const short kE_VCHECK_MEM = -1;//��ָ��

//����
extern const unsigned int kBASE = 0X10000;//����B
extern const unsigned int kBASEMINONE = 0XFFFFU;//B - 1
extern const unsigned long kDBASEMINONE = 0XFFFFFFFFUL;//B^2 - 1
extern const unsigned int kBASEDIV2 = 0X8000U;//B/2
extern const unsigned int kNOOFREGS = 16U;//�Ĵ�����׼���
extern const unsigned int kBITPERDIG = 16U;//ÿ��LINT�����а����Ķ�����λ��
extern const unsigned int kLDBITPERDGT = 4U;//�Զ�Ϊ��kBITPERDIG�Ķ���
extern const unsigned int kLINTMAXDIGIT = 256U;//LINT������BΪ���������λ��
extern const unsigned int kLINTMAXSHORT = kLINTMAXDIGIT + 1;//ΪLINT��������USHORT����
extern const unsigned int kLINTMAXBYTE = kLINTMAXSHORT << 1;//ΪLINT���������ֽ���
extern const unsigned int kLINTMAXBIT = kLINTMAXDIGIT << 4;//LINT�����������������λ��
extern const double kFLINT_VERSION = 0.1;//�汾��
extern const std::pair<unsigned int, unsigned int> kLINT_SECURE = { 0X73,0 };//��ȫģʽ��ʶ��


//����

//���n_l_�Ƿ���ż��
bool ISEVEN_L(const LINT& n_) {
	return (DIGITS_L(n_) == 0) || ((DIGITS_L(n_) > 0) && ((*(LSDPTR_L(n_)) & 1) == 0));
}
//���n_l_�Ƿ�������
bool ISODD_L(const LINT& n_) {
	return (DIGITS_L(n_) > 0) && (((*(LSDPTR_L(n_))) & 1) == 1);
}
//ģNmax+1
void ANDMAX_L(LINT& n_) {
	SETDIGITS_L(n_, std::min(DIGITS_L(n_), (lint)kLINTMAXDIGIT));
	RMLDZRS_L(n_);
}
//�Ƚ�����LINT�����Ƿ����
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
//�Ƚ�����LINT����(a_>b_->1; a_<b_->-1; a_==b_->0)
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
//����һ��LINT����
void cpy_l(LINT& dest_, const LINT& src_) {
	dest_ = src_;
	RMLDZRS_L(dest_);
}
//��һ��unsigned long ���͵�����ת��ΪLINT���Ͷ���
void ul2lint_l(LINT& num_, unsigned long ul) {
	*LSDPTR_L(num_) = (lint)(ul & 0xffff);
	*(LSDPTR_L(num_) + 1) = (lint)((ul >> 16) & 0xffff);
	SETDIGITS_L(num_, 2);
	RMLDZRS_L(num_);
}
//��һ��unsigned short ���͵�����ת��ΪLINT���Ͷ���
void u2lint_l(LINT& num_, unsigned short u) {
	num_[1] = u;
	SETDIGITS_L(num_, 1);
	RMLDZRS_L(num_);
}
//�Ƚ�a_>=b_
bool GE_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) > -1);
}
//�Ƚ�a_>b_
bool GT_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) == 1);
}
//�Ƚ�a_<b_
bool LT_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) == -1);
}
//�Ƚ�����LINT��������ֵ
LINT MAX_L(const LINT& a_, const LINT& b_) {
	return (GT_L(a_, b_) ? a_ : b_);
}
//�Ƚ�����LINT�������Сֵ
LINT MIN_L(const LINT& a_, const LINT& b_) {
	return (LT_L(a_, b_) ? a_ : b_);
}
//�Ƚ�a_==0
bool EQZ_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 0);
	return (equ_l(a_, tmp));
}
//�Ƚ�a_==1
bool EQONE_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 1);
	return (equ_l(a_, tmp));
}
//�Ƚ�a_>0
bool GTZ_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 0);
	return (GT_L(a_, tmp));
}

//��a_��Ϊ0
void SETZERO_L(LINT& a_) {
	a_[0] = 0;
}
//��a_��Ϊ1
void SETONE_L(LINT& a_) {
	u2lint_l(a_, 1);
}
//��a_��Ϊ2
void SETTWO_L(LINT& a_) {
	u2lint_l(a_, 2);
}
//��a_��Ϊul
void SET_L(LINT& a_, unsigned long ul) {
	ul2lint_l(a_, ul);
}
//��a_����ΪNmax
void SETMAX_L(LINT& a_) {
	SETDIGITS_L(a_, kLINTMAXDIGIT);
	for (auto begin = a_.begin() + 1; begin != a_.end(); begin++) {
		*(begin) = USHRT_MAX;
	}
}