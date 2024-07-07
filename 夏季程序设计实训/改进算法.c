// MyRand.c		产生服从高斯分布（正态分布）和均匀分布的随机数
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include<string.h>
#include "Score.h"
#include "Sorts.h"
#include "MyRand.h"
#pragma warning(disable : 4996)

#define NUM 20
/*
Box-Muller是产生随机数的一种方法。Box-Muller 算法隐含的原理非常深奥，但结果却是相当简单。
如果在(0,1]值域内有两个一致的随机数字u1和u2，则
可以使用以下两个式子中的任一个算出一个正态分布的随机数字z
z = r * cos(θ) 或 z = r * sin(θ)
其中 r = sqrt(-2 * ln(u2)), θ= 2 * π * u1
则z服从N(0, 1)，最后通过线性变换
x = m + (z * σ)服从N(m, σ^2)。
参见https://baike.baidu.com/item/box-muller/4023794?fr=aladdin
*/
double GaussRand(double mean, double variance)	// mena:均值、数学期望，variance方差
{
	static double u, v;
	static int phase = 0;
	double z;

	if(phase == 0)
	{
		u = (rand() + 1.0) / (RAND_MAX + 1.0);	// 避免u或v为0时参与对数log计算
		v = (rand() + 1.0) / (RAND_MAX + 1.0);
		z = sqrt(-2.0 * log(u))* sin(2.0 * M_PI * v);
	}
	else
	{
		z = sqrt(-2.0 * log(u)) * cos(2.0 * M_PI * v);
	}
	phase = 1 - phase;
	return mean + z*sqrt(variance);
}

// 利用rand()产生0~RAND_MAX之间的"均匀"分布的随机整数，进行简单的线性变换
double UniformRand(double a, double b)			// 区间[a, b]上的均匀分布
{
	return a + rand()*(b-a)/RAND_MAX;
}

// Score.c
void GetMemory(Score **data, Score **data0, int n)	// 分配堆内存空间，通过参数"返回"首地址
{													// 隐含约定：指针非空就表示指针"拥有"堆空间资源
	if(*data0!=NULL) free(*data0);					// 先释放原先所"拥有"的堆空间资源
	if(*data !=NULL) free(*data);
	*data0 = (Score*)calloc(n, sizeof(Score));		// 重新申请新的（容量符合要求的）堆空间资源
	*data  = (Score*)calloc(n, sizeof(Score));
}

void FreeMemory(Score **data, Score **data0)		// 释放指针所"拥有"的堆空间资源
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;							// 这一条赋值语句非常重要！保持"隐含约定"
}

void InitScore(struct Score *data, int n)
{
	double mean=72, variance=6*6;
	int i;
	for(i=0; i<n; i++)
	{
		sprintf(data[i].Id, "%08d", i+1);			// 请自学 sprintf 函数。请注意：原始数据中，学号是完全顺序排列的！
		data[i].Total  = data[i].Chinese   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Math      = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].English   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Physics   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Chemistry = (int)(0.5+GaussRand(mean, variance));
	}
}

void ReSet(Score *data, const Score *data0, int n)	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

int Check(const Score *a, int size)					// 未进行完全的正确性检验，仅检验数组元素是否已按降序排列
{
	int i;
	for(i=1; i<size; i++)
		if(a[i-1].Total < a[i].Total)
			return 0;
	return 1;
}

void ShowScore(const Score *data, int size, int m)
{
	int i;
	if(m<=0 || m>=size)
		m = size;							// 所有数据
	printf("\t输出部分数据（即总分前若干名的数据）\n");
	printf("\t学号 \t\t总分\t语文\t数学\t外语\t物理\t化学\n");
	for(i=0; i<m; i++)
		printf("\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", data[i].Id,
			data[i].Total, data[i].Chinese, data[i].Math,
			data[i].English, data[i].Physics, data[i].Chemistry);
}

// 三种基本的优排序算法
// 三种排序算法

void Bubble(Score *num, int size)
{
    int i, j, k, up, down, flag;
    long long int com, ass;
    Score temp;
    down = size - 1;
    up = 0;
    for(i = size - 1; i > 0; i--)//从前往后排
    {
        for(j = up; j < down; j++)
        {
            if(num[j].Total< num[j+1].Total)
            {
                temp = num[j];
                num[j]= num[j+1];
                num[j+1] = temp;
                ass+=3;
                flag = j;//取出从前往后的下标，在下标之后的数都已经排好序
            }
            com+=1;
        }

            if(flag == -1)
            {
                break;
            }
            down = flag;//取出flag的值
            flag = -1;//重置flag

            for(k = down; k > up; k--)
            {
                if(num[k].Total > num[k-1].Total)
                {
                    temp = num[k];
                    num[k] = num[k-1];
                    num[k-1] = temp;
                    ass+=3;
                    flag = k;//取出从后往前的下标，在下标之前的数都已经排好序
                }
                com+=1;
            }

            if(flag == -1)
            {
                break;
            }
            up = flag;//取出flag的值
            flag = -1;//重置flag
    }
     printf("\tBubble比较次数：%lld     Bubble赋值次数：%lld\n",com,ass);
}






//交换两个数据
void Swap(Score* a, Score* b)
{
    Score temp = *a;
    *a = *b;
    *b = temp;
}

//选择排序
void Select(Score *a, int size)   //优化后的选择排序
{
	int begin = 0;
    int end = size - 1;
    long long int com,ass;
    while (begin < end)
    {
        int max = begin;
        int min = begin;
        int i = 0;
        for (i = begin+1; i <= end; i++)
        {
            if (a[i].Total < a[min].Total)
            {
                min = i;
                ass+=1;
            }
            com+=1;

            if (a[i].Total > a[max].Total)
            {
                max = i;
                ass+=1;
            }
            com+=1;
        }

        Swap(&a[begin], &a[max]);
        if (begin == min)				//修正max
        {
            min = max;
            ass+=1;
        }
        com+=1;
        Swap(&a[end], &a[min]);

        begin++;
        end--;
    }

	 printf("\tSelect比较次数：%lld     Select赋值次数：%lld\n",com,ass);
}

void Qsort(Score* a, int size)
{
    int gap = size;
    long long int com,ass;
    while (gap > 1)
    {
        gap = gap / 3 + 1;	//调整希尔增量
        int i = 0;
        for (i = 0; i < size - gap; i++)	//从0遍历到size-gap-1
        {
            int end = i;
            Score temp = a[end + gap];
            ass+=1;
            while (end >= 0)
            {
                if (a[end].Total < temp.Total)
                {
                    a[end + gap] = a[end];
                    end -= gap;
                }
                else
                {
                    break;
                }
                ass+=2;
                com+=1;

            }
            a[end + gap] = temp;
            ass+=1;	//以 end+gap 作为插入位置
        }
    }
    printf("\txierQsort比较次数：%lld    xierQsort赋值次数：%lld\n",com,ass);
}
// Sorts.c		三种（冒泡、选择、快速）基本排序算法（升序）
double gettime(int restart)					// 参数带默认值，非零表示重新计时
{											// 否则累计计时
	double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t=0;						// 静态局部变量，存储计时起点
	if(restart||t==0) t = clock();			// 根据实参决定是否重新确定计时起点
	return c*(clock()-t);					// 从上一计时点到现在所经历的时间
}

void I_GetMemory(int **data, int **data0, int n)		// 分配堆内存空间，通过参数"返回"首地址
{														// 隐含约定：指针非空就表示指针"拥有"堆空间资源
	if(*data0!=NULL) free(*data0);						// 先释放原先所"拥有"的堆空间资源
	if(*data !=NULL) free(*data);
	*data0 = (int*)calloc(n, sizeof(int));				// 重新申请新的（容量符合要求的）堆空间资源
	*data  = (int*)calloc(n, sizeof(int));
}

void D_GetMemory(double **data, double **data0, int n)	// 分配堆内存空间，通过参数"返回"首地址
{														// 隐含约定：指针非空就表示指针"拥有"堆空间资源
	if(data0!=NULL) free(*data0);						// 先释放原先所"拥有"的堆空间资源
	if(data !=NULL) free(*data);
	*data0 = (double*)calloc(n, sizeof(double));		// 重新申请新的（容量符合要求的）堆空间资源
	*data  = (double*)calloc(n, sizeof(double));
}

void I_FreeMemory(int **data, int **data0)				// 释放指针所"拥有"的堆空间资源
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;								// 这一条赋值语句非常重要！保持"隐含约定"
}

void D_FreeMemory(double **data, double **data0)		// 释放指针所"拥有"的堆空间资源
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;								// 这一条赋值语句非常重要！保持"隐含约定"
}

void I_InitData(int *data, int n, int flag)
{
	int i;
	switch(flag)
	{
	case -1: for(i=0; i<n; i++) data[i] = n-1-i;						break;	// 逆序（从大到小）
	case 0:	 for(i=0; i<n; i++) data[i] = i;							break;	// 顺序（从小到大）
	case 1:  for(i=0; i<n; i++) data[i] = (int)(0.5+UniformRand(54,90));break;	// [54,90]上的均匀分布
	default: for(i=0; i<n; i++) data[i] = (int)(0.5+GaussRand(72, 6*6));break;	// 正态分布，均值72，方差36（根方差6）
	}
}

void D_InitData(double *data, int n, int flag)
{
	int i;
	switch(flag)
	{
	case -1: for(i=0; i<n; i++) data[i] = n-1-i;			break;	// 逆序（从大到小）
	case 0:	 for(i=0; i<n; i++) data[i] = i;				break;	// 顺序（从小到大）
	case 1:  for(i=0; i<n; i++) data[i] = UniformRand(54,90);break;	// [54,90]上的均匀分布
	default: for(i=0; i<n; i++) data[i] = GaussRand(72, 6*6);break;	// 正态分布，均值72，方差36（根方差6）
	}
}

void I_ReSet(int *data, const int *data0, int n)		// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

void D_ReSet(double *data, const double *data0, int n)	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

int I_Check(const int *a, int size)						// 检验数组元素是否已按升序排列
{
	int i;
	for(i=1; i<size; i++)
		if(a[i-1] > a[i])
			return 0;
	return 1;
}

int D_Check(const double *a, int size)					// 检验数组元素是否已按升序排列
{
	int i;
	for(i=1; i<size; i++)
		if(a[i-1] > a[i])
			return 0;
	return 1;
}

// 三种基本的优化排序算法
void I_Bubble(int *num, int size)
{
    int i, j, k, up, down, temp, flag;
    up = size - 1;
    down = 0;
    long long int Bubblecom=0,Bubbleass=0;
    for(i = size - 1; i > 0; i--)//从前往后排
    {
        for(j = down; j < up; j++)
        {
            if(num[j] > num[j+1])
            {
                temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                flag = j;//取出从前往后的下标，在下标之后的数都已经排好序
                Bubbleass+=3;
            }
            Bubblecom++;
        }
        if(!Bubbleass)                                 //若一次排序未发生交换，返回函数
			{printf("\tBubble比较次数：%lld     Bubble赋值次数：%lld\n",Bubblecom,Bubbleass);return;}

            if(flag == -1)
            {
                break;
            }
            up = flag;//取出flag的值
            flag = -1;//重置flag

            for(k = up; k > down; k--)
            {
                if(num[k] < num[k-1])
                {
                    temp = num[k];
                    num[k] = num[k-1];
                    num[k-1] = temp;
                    flag = k;//取出从后往前的下标，在下标之前的数都已经排好序
                    Bubbleass+=3;
                }
                Bubblecom++;
            }
            if(!Bubbleass)                                 //若二次排序未发生交换，返回函数
			{printf("\tBubble比较次数：%lld     Bubble赋值次数：%lld\n",Bubblecom,Bubbleass);return;}

            if(flag == -1)
            {
                break;
            }
            down = flag;//取出flag的值
            flag = -1;//重置flag
    }
    printf("\tBubble比较次数：%lld     Bubble赋值次数：%lld\n",Bubblecom,Bubbleass);
}

void D_Bubble(double *num, int size)
{
    int i, j, k, up, down, flag;
    double temp;
    up = size - 1;
    down = 0;
    long long int Bubblecom=0,Bubbleass=0;
    for(i = size - 1; i > 0; i--)//从前往后排
    {
        for(j = down; j < up; j++)
        {
            if(num[j] > num[j+1])
            {
                temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                flag = j;//取出从前往后的下标，在下标之后的数都已经排好序
                Bubbleass+=3;
            }
            Bubblecom++;
        }
        if(!Bubbleass)                                 //若一次排序未发生交换，返回函数
			{printf("\tBubble比较次数：%lld    Bubble赋值次数：%lld\n",Bubblecom,Bubbleass);return;}

            if(flag == -1)
            {
                break;
            }
            up = flag;//取出flag的值
            flag = -1;//重置flag

            for(k = up; k > down; k--)
            {
                if(num[k] < num[k-1])
                {
                    temp = num[k];
                    num[k] = num[k-1];
                    num[k-1] = temp;
                    flag = k;//取出从后往前的下标，在下标之前的数都已经排好序
                    Bubbleass+=3;
                }
                Bubblecom++;
            }
            if(!Bubbleass)                                 //若二次排序未发生交换，返回函数
			{printf("\tBubble比较次数：%lld     Bubble赋值次数：%lld\n",Bubblecom,Bubbleass);return;}

            if(flag == -1)
            {
                break;
            }
            down = flag;//取出flag的值
            flag = -1;//重置flag
    }
    printf("\tBubble比较次数：%lld    Bubble赋值次数：%lld\n",Bubblecom,Bubbleass);
}


//选择排序的优化(一次将两个元素放在它的最终位置上）
void swap(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
void I_Select(int *array, int size)
{
	//最小值下标
	int minpos = 0;
	//最大值下标
	int maxpos = 0;
	int left = 0;
	int right = size - 1;
	int j = 0;
	long long int selectcom=0,selectass=0;
	//循环size-1次
	while (left < right)
	{
		maxpos = left;
		minpos = left;
		//确定最大值下标以及最小值下标
		for (j = left; j <= right; j++)
		{
			if (array[j]>array[maxpos])
			{
				maxpos = j;
				selectass++;
			}
			if (array[j] < array[minpos])
			{
				minpos = j;
				selectass++;
			}
			selectcom++;
		}
		//将最大值插到最后
		if (maxpos != right)
		{
			swap(&array[maxpos], &array[right]);
			selectass+=3;
		}
		//防止minpos在最大值要插入的位置
		if (minpos == right)
		{
			minpos = maxpos;
			selectass++;
		}
		//将最小值插到最前面
		if (minpos != left)
		{
			swap(&array[minpos], &array[left]);
			selectass+=3;
		}
		selectcom+=2;
		left++;
		right--;
	}
	 printf("\tSelect比较次数：%lld     Select赋值次数：%lld\n",selectcom,selectass);
}


void swap1(double *x, double*y)
{
	double tmp = *x;
	*x = *y;
	*y = tmp;
}
void D_Select(double *array, int size)
{
	//最小值下标
	int minpos = 0;
	//最大值下标
	int maxpos = 0;
	int left = 0;
	int right = size - 1;
	int j = 0;
	long long int selectcom=0,selectass=0;
	//循环size-1次
	while (left < right)
	{
		maxpos = left;
		minpos = left;
		//确定最大值下标以及最小值下标
		for (j = left; j <= right; j++)
		{
			if (array[j]>array[maxpos])
			{
				maxpos = j;
				selectass++;
			}
			if (array[j] < array[minpos])
			{
				minpos = j;
				selectass++;
			}
			selectcom=selectcom+2;
		}
		//将最大值插到最后
		if (maxpos != right)
		{
			swap1(&array[maxpos], &array[right]);
		}
		//防止minpos在最大值要插入的位置
		if (minpos == right)
		{
			minpos = maxpos;
		}
		//将最小值插到最前面
		if (minpos != left)
		{
			swap1(&array[minpos], &array[left]);

		}
		left++;
		right--;
	}
	 printf("\tSelect比较次数：%lld     Select赋值次数：%lld\n",selectcom,selectass);
}
//希尔快排
void I_Qsort(int* arr,int len)
{
    long long int xiercom=0,xierass=0;
    int k,i,j;
	for(k=len/2; k>0; k/=2)
	{
		for(i=k; i<len; i++)
		{   xierass+=2;
			int tmp = arr[i];
			for(j=i-k; j>=0 && tmp<arr[j]; j-=k)
			{
				arr[j+k] = arr[j];
				xiercom++;
				xierass++;
			}
			arr[j+k] = tmp;
		}
	}
	 printf("\txierQsort比较次数：%lld    xierQsort赋值次数：%lld\n",xiercom,xierass);
}

//duoble快排

void D_Qsort(double* arr,int len)
{
    long long int xiercom=0,xierass=0;
    int k,i,j;
	for( k=len/2; k>0; k/=2)
	{
		for( i=k; i<len; i++)
		{
		    xierass+=2;
			double tmp = arr[i];
			for(j=i-k; j>=0 && tmp<arr[j]; j-=k)
			{
				arr[j+k] = arr[j];
				xiercom++;
				xierass++;
			}
			arr[j+k] = tmp;
		}
	}
		 printf("\txierQsort比较次数：%lld    xierQsort赋值次数：%lld\n",xiercom,xierass);
}

void I_Test()
{
	int *data0=NULL, *data=NULL;								// 指针初始化为NULL非常重要！
	char InitConf[][20] = {"完全逆序", "完全顺序", "均匀分布", "正态分布"};	// C-字符串数组（数据分布方式）
	char algo[][20] = {"冒泡排序", "选择排序", "快速排序"};		// C-字符串数组（排序算法名称）
	void (*f[])(int*, int) = {I_Bubble, I_Select, I_Qsort};		// 函数指针数组（元素为一系列函数的入口地址）
	int i, j, n, m = sizeof(f)/sizeof(*f);						// m为函数指针数组f的元素个数（此处有3个函数指针，分别指向3个排序函数的入口地址）
	int flag[20];												// 这里认为：常量20足够大于变量 m。记录不同算法执行的正确性
	double t[20];												// 同上。记录不同算法的执行时间

	for(j=2; j>=-1; j--)										// 数据分布方式
	{
		printf("\n整型数据(%s)\n", InitConf[j+1]);
		for(i=0; i<m; i++)
			printf("\t%s", algo[i]);
		printf("\n");
		for(n=1024; n<=65536; n*=2)
		{
			I_GetMemory(&data, &data0, n);						// 申请分配堆空间
			I_InitData(data0, n, j);							// 设置原始数据
			printf("%d", n);
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					break;
				I_ReSet(data, data0, n);						// 恢复原始数据
				gettime(1);										// 设置计时起点
				f[i](data, n);									// 第 i 种排序算法
				t[i] = gettime(0);								// 返回从计时起点到目前所经历的时间（秒）
				flag[i] = I_Check(data, n);						// 检验排序的正确性
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					printf("\t");
				else
					printf("\t%lf", t[i]);
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					printf("\t快速排序：由于递归层次太深，可能导致栈溢出，故跳过。");
				else
					printf("\t%s: %s", algo[i], (flag[i]?"正确":"错误"));
			}
			printf("\n");
			I_FreeMemory(&data, &data0);						// 释放堆空间资源，并使指针为空
		}
	}
}

void D_Test()
{
	double *data0=NULL, *data=NULL;								// 指针初始化为NULL非常重要！
	char InitConf[][20] = {"完全逆序", "完全顺序", "均匀分布", "正态分布"};	// C-字符串数组（数据分布方式）
	char algo[][20] = {"冒泡排序", "选择排序", "快速排序"};		// C-字符串数组（排序算法名称）
	void (*f[])(double*, int) = {D_Bubble, D_Select, D_Qsort};	// 函数指针数组（元素为一系列函数的入口地址）
	int i, j, n, m = sizeof(f)/sizeof(*f);						// m为函数指针数组f的元素个数（此处有3个函数指针，分别指向3个排序函数的入口地址）
	int flag[20];												// 这里认为：常量20足够大于变量 m。记录不同算法执行的正确性
	double t[20];												// 同上。记录不同算法的执行时间

	for(j=2; j>=-1; j--)										// 数据分布类型
	{
		printf("\n双精度浮点型数据(%s)\n", InitConf[j+1]);
		for(i=0; i<m; i++)
			printf("\t%s", algo[i]);
		printf("\n");
		for(n=1024; n<=65536; n*=2)
		{
			D_GetMemory(&data, &data0, n);						// 申请分配堆空间
			D_InitData(data0, n, j);							// 设置原始数据
			printf("%d", n);
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					break;
				D_ReSet(data, data0, n);							// 恢复原始数据
				gettime(1);										// 设置计时起点
				f[i](data, n);									// 第 i 种排序算法
				t[i] = gettime(0);								// 返回从计时起点到目前所经历的时间（秒）
				flag[i] = D_Check(data, n);						// 检验排序的正确性
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					printf("\t");
				else
					printf("\t%lf", t[i]);
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(完全顺序、完全逆序)，i==m-1(快速排序，递归算法)
					printf("\t快速排序：由于递归层次太深，可能导致栈溢出，故跳过。");
				else
					printf("\t%s: %s", algo[i], (flag[i]?"正确":"错误"));
			}
			printf("\n");
			D_FreeMemory(&data, &data0);						// 释放堆空间资源，并使指针为空
		}
	}
}

void Score_Test()
{
	Score *data0=NULL, *data=NULL;							// 两个指针初始化为NULL非常重要！
	char algo[][20] = {"冒泡排序", "选择排序", "快速排序"};	// C-字符串数组（排序算法名称）
	void (*f[])(Score*, int) = {Bubble, Select, Qsort};		// 函数指针数组（元素为一系列函数的入口地址）
	int i, n, m = sizeof(f)/sizeof(*f);
	int flag;
	double t;

	printf("\n结构体(Score)类型数据 (正态分布)\n");
	for(n=1024; n<=65536; n*=2)
	{
		GetMemory(&data, &data0, n);						// 申请分配堆空间
		InitScore(data0, n);								// 设置原始数据
		for(i=0; i<m; i++)
		{
			ReSet(data, data0, n);							// 恢复原始数据
			gettime(1);										// 设置计时起点
			f[i](data, n);									// 第 i 种排序算法
			t = gettime(0);									// 返回从计时起点到目前所经历的时间（秒）
			flag = Check(data, n);							// 检验排序的正确性
			printf("%d\t%lf\t%s: %s\n", n, t, algo[i], (flag?"正确":"错误"));
			ShowScore(data, n, 10);							// 倒序输出最后10项（由于按升序排列，最高分第一名在最后）
		}
		FreeMemory(&data, &data0);							// 释放堆空间资源，并使指针为空
	}
}
void BubbleA(char(*str)[NUM], int size)
{
	int k,i,j;
	for ( i = 0; i < size - 1; i++) 
	{
		for (j = 0; j < size - i - 1; j++) {
			if (strcmp(str[j], str[j + 1]) > 0) {
				char temp[NUM];
				strcpy(temp, str[j]);
				strcpy(str[j], str[j + 1]);
				strcpy(str[j + 1], temp);
			}
		}
	}
}

void BubbleB(char* str[], int size)
{
	int k,i,j;
	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - i - 1; j++) 
		{
			if (strcmp(str[j], str[j + 1]) > 0) {
				char* temp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = temp;
			}
		}
	}
}

int StrCmp(const char* str1, const char* str2)
{
	unsigned char* p1 = (unsigned char*)str1;			// 思考题：为什么需要进行强制转换成unsigned char*
	unsigned char* p2 = (unsigned char*)str2;
	while (*p1 && *p2 && *p1++ == *p2++)					// 思考题：有哪些情况使本循环结束
		;
	return *p1 > *p2 ? 1 : (*p1 < *p2 ? -1 : 0);
}

void TestStrCmp()
{
	char* str[] = { "abc", "abcd", "上海大学", "", "上海" };
	int n = sizeof(str) / sizeof(*str), i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			printf("strcmp(\"%s\", \"%s\") = %d\nStrCmp(\"%s\", \"%s\") = %d\n\n",
				str[i], str[j], strcmp(str[i], str[j]), str[i], str[j], StrCmp(str[i], str[j]));
}

//void ShowStringsA(const char *prompt, char (* const strs)[NUM], int n)
void ShowStringsA(const char* prompt, char(*strs)[NUM], int n)
{
	int i;
	if (n > 0)
		printf("%s %s", prompt, strs[0]);
	for (i = 1; i < n; i++)
		printf(", %s", strs[i]);
	printf("\n");
}

void ShowStringsB(const char* prompt, char* strs[], int n)
{
	int i;
	if (n > 0)
		printf("%s %s", prompt, strs[0]);
	for (i = 1; i < n; i++)
		printf(", %s", strs[i]);
	printf("\n");
}

void GetStringsA(char*** dest, char(*source)[NUM], int n)
{
	*dest = (char**)calloc(sizeof(char*), n);
	if (*dest == NULL) return;
	int i, len;
	for (i = 0; i < n; i++)
	{
		len = strlen(source[i]);
		(*dest)[i] = (char*)calloc(sizeof(char), len + 1);
		strcpy((*dest)[i], source[i]);
	}
}

char** GetStringsA1(char(*source)[NUM], int n)		// 思考题：本函数与上面的GetStringSA函数的功能是否相同？调用本函数时，应该用何种表达式？
{
	char** dest;
	dest = (char**)calloc(sizeof(char*), n);
	if (dest == NULL) return dest;
	int i, len;
	for (i = 0; i < n; i++)
	{
		len = strlen(source[i]);
		dest[i] = (char*)calloc(sizeof(char), len + 1);
		strcpy(dest[i], source[i]);
	}
	return dest;
}

void GetStringsB(char*** dest, char* source[], int n)
{
	*dest = (char**)calloc(sizeof(char*), n);
	if (*dest == NULL) return;
	int i, len;
	for (i = 0; i < n; i++)
	{
		len = strlen(source[i]);
		(*dest)[i] = (char*)calloc(sizeof(char), len + 1);
		strcpy((*dest)[i], source[i]);
	}
}

void FreeStrings(char*** strs, int n)
{
	int i;
	if (*strs != NULL)
	{
		for (i = 0; i < n; i++)
			if ((*strs)[i] != NULL)
				free((*strs)[i]);
		free(*strs);
		*strs = NULL;
	}
}

void FreeStrings1(char** strs, int n)		// 思考题：本函数能否完成释放堆内存资源的任务？有何缺陷？
{
	int i;
	if (strs != NULL)
	{
		for (i = 0; i < n; i++)
			if (strs[i] != NULL)
				free(strs[i]);
		free(strs);
	}
}

void TestString()
{
	char strA[][NUM] = { "enter", "number", "C/C++程序设计", "size", "指针", "begin", "of", "函数", "cat", "case", "program", "certain", "a", "cake", "side" };
	char* strB[] = { "enter", "number", "C/C++程序设计", "size", "指针", "begin", "of", "函数", "cat", "case", "program", "certain", "an", "cake", "side" };
	char** strC = NULL, ** strD = NULL;
	int n1 = sizeof(strA) / sizeof(*strA), n2 = sizeof(strB) / sizeof(*strB);
	GetStringsA(&strC, strA, n1);			// 如果换成 GetStringsA1 函数，则调用语句应该是怎样的？
	GetStringsB(&strD, strB, n2);			// 请画出strC或strD的结构图

	printf("\n\t*** 多种不同存储方式的C-字符串数组的排序 ***\n");
	ShowStringsA("\n原始数据: ", strA, n1);
	BubbleA(strA, n1);
	ShowStringsA("\n排序结果: ", strA, n1);

	ShowStringsB("\n原始数据: ", strB, n2);
	BubbleB(strB, n2);
	ShowStringsB("\n排序结果: ", strB, n2);

	ShowStringsB("\n原始数据: ", strC, n1);
	BubbleB(strC, n1);						// 此处能否调用BubbleA函数对strC进行排序？如果要用BubbleA函数，需要对GetStringsA函数进行怎样的修改？
	ShowStringsB("\n排序结果: ", strC, n1);

	ShowStringsB("\n原始数据: ", strD, n2);
	BubbleB(strD, n2);						// 此处能否调用BubbleA函数对strD进行排序？如果要用BubbleA函数，需要对GetStringsB函数进行怎样的修改？
	ShowStringsB("\n排序结果: ", strD, n2);

	FreeStrings(&strC, n1);					// 如果调用 FreeStrings1 函数，则应该执行哪些语句？
	FreeStrings(&strD, n2);					// 如果调用 FreeStrings1 函数，则应该执行哪些语句？
}
int main()					// 主函数
{
//	void TestStrCmp();	TestStrCmp();	return 0;

	srand(time(NULL));		// 设置随机数发生器的种子
	
	I_Test();				// 测试int类型数据
	D_Test();				// 测试double类型数据
	Score_Test();			// 测试Score类型数据

                        	// 调式下面的函数时，建议将上面的3行语句注释起来，以节省时间
	//void TestString();		// 函数原型，用于函数声明
	//TestString();			// 函数调用

	return 0;
}

