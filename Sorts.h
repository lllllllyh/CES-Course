// Sorts.h		三种（冒泡、选择、快速）基本排序算法（升序）
#ifndef SORTS_H
#define SORTS_H

double gettime(int restart);							// 计时函数（restart非零为设置计时起点，非零时返回从最近设置的计时起点到现在的时间）

void I_GetMemory(int **data, int **data0, int n);		// 分配堆内存空间，通过参数"返回"首地址
void I_FreeMemory(int **data, int **data0);				// 释放指针所"拥有"的堆空间资源
void I_InitData(int *data, int n, int flag);			// 根据flag设置不同分布的"原始数据"
void I_ReSet(int *data, const int *data0, int n);		// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
int  I_Check(const int *a, int size);					// 检验数组元素是否已按升序排列

void D_GetMemory(double **data, double **data0, int n);	// 分配堆内存空间，通过参数"返回"首地址
void D_FreeMemory(double **data, double **data0);		// 释放指针所"拥有"的堆空间资源
void D_InitData(double *data, int n, int flag);			// 根据flag设置不同分布的"原始数据"
void D_ReSet(double *data, const double *data0, int n);	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
int  D_Check(const double *a, int size);				// 检验数组元素是否已按升序排列

// 三种基本的（没有优化的）排序算法
void I_Bubble(int *a, int size);						// 冒泡排序
void I_Select(int *a, int size);						// 选择排序
void I_Qsort(int *a, int size);							// 快速排序

void D_Bubble(double *a, int size);						// 冒泡排序
void D_Select(double *a, int size);						// 选择排序
void D_Qsort(double *a, int size);						// 快速排序

#endif
