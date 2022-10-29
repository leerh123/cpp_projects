#include"constant.h"
//��n_l_��λ������Ϊa_
inline void SETDIGITS_L(LINT& n_, lint a_) {
	n_[0] = a_;
}
//��ȡn_l_��λ��
inline lint DIGITS_L(const LINT& n_) {
	return n_[0];
}
//��ȡ�����Чλ��ָ��
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
//��ȡ�����Чλ��ָ��
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
//���n_l_�Ƿ���ż��
inline bool ISEVEN_L(const LINT& n_) {
	return (DIGITS_L(n_) == 0) || ((DIGITS_L(n_) > 0) && ((*(LSDPTR_L(n_)) & 1) == 0));
}
//���n_l_�Ƿ�������
inline bool ISODD_L(const LINT& n_) {
	return (DIGITS_L(n_) > 0) && ((*(LSDPTR_L(n_)) & 1) == 1);
}
//λ����һ
inline void DECDIGITS_L(LINT& n_) {
	if (n_[0] == 0)
		return;
	n_[0]--;
}
//λ����һ
inline void INCDIGITS_L(LINT& n_) {
	n_[0]++;
}
//ȥ��ǰ����
inline void RMLDZRS_L(LINT& n_) {
	while ((DIGITS_L(n_) > 0) && (*(MSDPTR_L(n_)) == 0))
		DECDIGITS_L(n_);
}
//ģNmax+1
inline void ANDMAX_L(LINT& n_) {
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
inline bool GE_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) > -1);
}
//�Ƚ�a_>b_
inline bool GT_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) == 1);
}
//�Ƚ�a_<b_
inline bool LT_L(const LINT& a_, const LINT& b_) {
	return (cmp_l(a_, b_) == -1);
}
//�Ƚ�����LINT��������ֵ
inline LINT MAX_L(const LINT& a_, const LINT& b_) {
	return (GT_L(a_, b_) ? a_ : b_);
}
//�Ƚ�����LINT�������Сֵ
inline LINT MIN_L(const LINT& a_, const LINT& b_) {
	return (LT_L(a_, b_) ? a_ : b_);
}
//�Ƚ�a_==0
inline bool EQZ_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 0);
	return (equ_l(a_, tmp));
}
//�Ƚ�a_==1
inline bool EQONE_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 1);
	return (equ_l(a_, tmp));
}
//�Ƚ�a_>0
inline bool GTZ_L(LINT& a_) {
	LINT tmp;
	u2lint_l(tmp, 0);
	return (GT_L(a_, tmp));
}

//��a_��Ϊ0
inline void SETZERO_L(LINT& a_) {
	a_[0] = 0;
}
//��a_��Ϊ1
inline void SETONE_L(LINT& a_) {
	u2lint_l(a_, 1);
}
//��a_��Ϊ2
inline void SETTWO_L(LINT& a_) {
	u2lint_l(a_, 2);
}
//��a_��Ϊul
inline void SET_L(LINT& a_, unsigned long ul) {
	ul2lint_l(a_, ul);
}
