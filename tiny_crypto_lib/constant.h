#pragma once
#include<utility>
#include<array>
#include<algorithm>

//�������
const short kE_LINT_DBZ = -1;//�����
const short kE_LINT_OFL = -2;//����
const short kE_LINT_UFL = -3;//����
const short kE_LINT_MAL = -4;//�ڴ�������
const short kE_LINT_NOR = -5;//�Ĵ���������
const short kE_LINT_BOR = -6;//�������Ϸ�
const short kE_LINT_MOD = -7;//ģ��Ϊż
const short kE_LINT_NPT = -8;//����ָ����Ϊ��������
const short kE_VCHECK_OFL = 1;//���棺���ֹ���
const short kE_VCHECK_LDZ = 2;//���棺ǰ����
const short kE_VCHECK_MEM = -1;//��ָ��

//����
const unsigned int kBASE = 0X10000;//����B
const unsigned int kBASEMINONE = 0XFFFFU;//B - 1
const unsigned long kDBASEMINONE = 0XFFFFFFFFUL;//B^2 - 1
const unsigned int kBASEDIV2 = 0X8000U;//B/2
const unsigned int kNOOFREGS = 16U;//�Ĵ�����׼���
const unsigned int kBITPERDIG = 16U;//ÿ��LINT�����а����Ķ�����λ��
const unsigned int kLDBITPERDGT = 4U;//�Զ�Ϊ��kBITPERDIG�Ķ���
const unsigned int kLINTMAXDIGIT = 256U;//LINT������BΪ���������λ��
const unsigned int kLINTMAXSHORT = kLINTMAXDIGIT + 1;//ΪLINT��������USHORT����
const unsigned int kLINTMAXBYTE = kLINTMAXSHORT << 1;//ΪLINT���������ֽ���
const unsigned int kLINTMAXBIT = kLINTMAXDIGIT << 4;//LINT�����������������λ��
const double kFLINT_VERSION = 0.1;//�汾��
const std::pair<const unsigned int, const unsigned int> kLINT_SECURE = { 0X73,0 };//��ȫģʽ��ʶ��

//����
using lint = unsigned short;
using LINT = std::array<lint, kLINTMAXDIGIT + 1>;
using LINTD = std::array<lint, (kLINTMAXDIGIT << 1) + 1>;
using LINTQ = std::array<lint, (kLINTMAXDIGIT << 2) + 1>;

//����

//��n_l_��λ������Ϊa_
inline void SETDIGITS_L(LINT& n_, lint a_);
// ��ȡn_l_��λ��
inline lint DIGITS_L(const LINT & n_);
//��ȡ�����Чλ��ָ��
inline lint* LSDPTR_L(LINT& n_);
inline const lint* LSDPTR_L(const LINT& n_);
//��ȡ�����Чλ��ָ��
inline lint* MSDPTR_L(LINT& n_);
inline const lint* MSDPTR_L(const LINT& n_);
//���n_l_�Ƿ���ż��
inline bool ISEVEN_L(const LINT& n_);
//���n_l_�Ƿ�������
inline bool ISODD_L(const LINT& n_);
//λ����һ
inline void DECDIGITS_L(LINT& n_);
//λ����һ
inline void INCDIGITS_L(LINT& n_);
// ȥ��ǰ����
inline void RMLDZRS_L(LINT & n_);
//ģNmax+1
inline void ANDMAX_L(LINT& n_);
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
inline bool GE_L(const LINT& a_, const LINT& b_);
//�Ƚ�a_>b_
inline bool GT_L(const LINT& a_, const LINT& b_);
//�Ƚ�a_<b_
inline bool LT_L(const LINT& a_, const LINT& b_);
//�Ƚ�����LINT��������ֵ
inline LINT MAX_L(const LINT& a_, const LINT& b_);
//�Ƚ�����LINT�������Сֵ
inline LINT MIN_L(const LINT& a_, const LINT& b_);
//�Ƚ�a_==0
inline bool EQZ_L(LINT& a_);
//�Ƚ�a_==1
inline bool EQONE_L(LINT& a_);
//�Ƚ�a_>0
inline bool GTZ_L(LINT& a_);
//��a_��Ϊ0
inline void SETZERO_L(LINT& a_);
//��a_��Ϊ1
inline void SETONE_L(LINT& a_);
//��a_��Ϊ2
inline void SETTWO_L(LINT& a_);
//��a_��Ϊul
inline void SET_L(LINT& a_, unsigned long ul);
