#pragma once
#include<utility>
#include<array>
#include<algorithm>

//�������
extern const short kE_LINT_DBZ;//�����
extern const short kE_LINT_OFL;//����
extern const short kE_LINT_UFL;//����
extern const short kE_LINT_MAL;//�ڴ�������
extern const short kE_LINT_NOR;//�Ĵ���������
extern const short kE_LINT_BOR;//�������Ϸ�
extern const short kE_LINT_MOD;//ģ��Ϊż
extern const short kE_LINT_NPT;//����ָ����Ϊ��������
extern const short kE_VCHECK_OFL;//���棺���ֹ���
extern const short kE_VCHECK_LDZ;//���棺ǰ����
extern const short kE_VCHECK_MEM;//��ָ��

//����
extern const unsigned int kBASE;//����B
extern const unsigned int kBASEMINONE;//B - 1
extern const unsigned long kDBASEMINONE;//B^2 - 1
extern const unsigned int kBASEDIV2;//B/2
extern const unsigned int kNOOFREGS;//�Ĵ�����׼���
extern const unsigned int kBITPERDIG;//ÿ��LINT�����а����Ķ�����λ��
extern const unsigned int kLDBITPERDGT;//�Զ�Ϊ��kBITPERDIG�Ķ���
extern const unsigned int kLINTMAXDIGIT;//LINT������BΪ���������λ��
extern const unsigned int kLINTMAXSHORT;//ΪLINT��������USHORT����
extern const unsigned int kLINTMAXBYTE;//ΪLINT���������ֽ���
extern const unsigned int kLINTMAXBIT;//LINT�����������������λ��
extern const double kFLINT_VERSION;//�汾��
extern const std::pair<unsigned int, unsigned int> kLINT_SECURE;//��ȫģʽ��ʶ��

//����
using lint = unsigned short;
using LINT = std::array<lint, 257>;//kLINTMAXDIGIT + 1
using LINTD = std::array<lint, 513>;//(kLINTMAXDIGIT << 1) + 1
using LINTQ = std::array<lint, 1025>;//(kLINTMAXDIGIT << 2) + 1

//����
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
	return &n_[1];
}
inline const lint* LSDPTR_L(const LINT& n_) {
	return &n_[1];
}
//��ȡ�����Чλ��ָ��
inline lint* MSDPTR_L(LINT& n_) {
	return &n_[DIGITS_L(n_)];
}
inline const lint* MSDPTR_L(const LINT& n_) {
	return &n_[DIGITS_L(n_)];
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
//���n_l_�Ƿ���ż��
bool ISEVEN_L(const LINT& n_);
//���n_l_�Ƿ�������
bool ISODD_L(const LINT& n_);
//ģNmax+1
void ANDMAX_L(LINT& n_);
//�Ƚ�����LINT�����Ƿ����
bool equ_l(const LINT& a_, const LINT& b_);
//�Ƚ�����LINT����(a_>b_->1; a_<b_->-1; a_==b_->0)
int cmp_l(const LINT& a_, const LINT& b_);
//����һ��LINT����
void cpy_l(LINT& dest_, const LINT& src_);
//��һ��unsigned long ���͵�����ת��ΪLINT���Ͷ���
void ul2lint_l(LINT& num_, unsigned long ul);
//��һ��unsigned short ���͵�����ת��ΪLINT���Ͷ���
void u2lint_l(LINT& num_, unsigned short u);
//�Ƚ�a_>=b_
bool GE_L(const LINT& a_, const LINT& b_);
//�Ƚ�a_>b_
bool GT_L(const LINT& a_, const LINT& b_);
//�Ƚ�a_<b_
bool LT_L(const LINT& a_, const LINT& b_);
//�Ƚ�����LINT��������ֵ
LINT MAX_L(const LINT& a_, const LINT& b_);
//�Ƚ�����LINT�������Сֵ
LINT MIN_L(const LINT& a_, const LINT& b_);
//�Ƚ�a_==0
bool EQZ_L(LINT& a_);
//�Ƚ�a_==1
bool EQONE_L(LINT& a_);
//�Ƚ�a_>0
bool GTZ_L(LINT& a_);
//��a_��Ϊ0
void SETZERO_L(LINT& a_);
//��a_��Ϊ1
void SETONE_L(LINT& a_);
//��a_��Ϊ2
void SETTWO_L(LINT& a_);
//��a_��Ϊul
void SET_L(LINT& a_, unsigned long ul);
//��a_����ΪNmax
void SETMAX_L(LINT& a_);


