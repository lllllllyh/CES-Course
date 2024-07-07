// Score.h
#ifndef SCORE_H
#define SCORE_H

typedef struct Score
{
	char Id[9];															// 最多存放8个字符
	int Chinese, Math, English, Physics, Chemistry, Total;				// 5门课程成绩及总分
} Score;

void GetMemory(Score **data, Score **data0, int n);		// 分配堆内存空间，通过参数"返回"首地址
void FreeMemory(Score **data, Score **data0);			// 释放指针所"拥有"的堆空间资源
void InitScore(struct Score *data, int n);
void ReSet(Score *data, const Score *data0, int n);		// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
int  Check(const Score *a, int size);					// 检验数组元素是否已按降序排列
void ShowScore(const Score *data, int size, int m);		// 输出数组的前m个元素

// 三种基本的（没有优化的）排序算法
void Bubble(Score *a, int size);						// 冒泡排序(按总分降序排序)
void Select(Score *a, int size);						// 选择排序(按总分降序排序)
void Qsort(Score *a, int size);							// 快速排序(按总分降序排序)

#endif
