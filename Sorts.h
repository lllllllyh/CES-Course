// Sorts.h		���֣�ð�ݡ�ѡ�񡢿��٣����������㷨������
#ifndef SORTS_H
#define SORTS_H

double gettime(int restart);							// ��ʱ������restart����Ϊ���ü�ʱ��㣬����ʱ���ش�������õļ�ʱ��㵽���ڵ�ʱ�䣩

void I_GetMemory(int **data, int **data0, int n);		// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
void I_FreeMemory(int **data, int **data0);				// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
void I_InitData(int *data, int n, int flag);			// ����flag���ò�ͬ�ֲ���"ԭʼ����"
void I_ReSet(int *data, const int *data0, int n);		// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
int  I_Check(const int *a, int size);					// ��������Ԫ���Ƿ��Ѱ���������

void D_GetMemory(double **data, double **data0, int n);	// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
void D_FreeMemory(double **data, double **data0);		// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
void D_InitData(double *data, int n, int flag);			// ����flag���ò�ͬ�ֲ���"ԭʼ����"
void D_ReSet(double *data, const double *data0, int n);	// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
int  D_Check(const double *a, int size);				// ��������Ԫ���Ƿ��Ѱ���������

// ���ֻ����ģ�û���Ż��ģ������㷨
void I_Bubble(int *a, int size);						// ð������
void I_Select(int *a, int size);						// ѡ������
void I_Qsort(int *a, int size);							// ��������

void D_Bubble(double *a, int size);						// ð������
void D_Select(double *a, int size);						// ѡ������
void D_Qsort(double *a, int size);						// ��������

#endif
