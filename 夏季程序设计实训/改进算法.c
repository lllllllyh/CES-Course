// MyRand.c		�������Ӹ�˹�ֲ�����̬�ֲ����;��ȷֲ��������
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
Box-Muller�ǲ����������һ�ַ�����Box-Muller �㷨������ԭ��ǳ���£������ȴ���൱�򵥡�
�����(0,1]ֵ����������һ�µ��������u1��u2����
����ʹ����������ʽ���е���һ�����һ����̬�ֲ����������z
z = r * cos(��) �� z = r * sin(��)
���� r = sqrt(-2 * ln(u2)), ��= 2 * �� * u1
��z����N(0, 1)�����ͨ�����Ա任
x = m + (z * ��)����N(m, ��^2)��
�μ�https://baike.baidu.com/item/box-muller/4023794?fr=aladdin
*/
double GaussRand(double mean, double variance)	// mena:��ֵ����ѧ������variance����
{
	static double u, v;
	static int phase = 0;
	double z;

	if(phase == 0)
	{
		u = (rand() + 1.0) / (RAND_MAX + 1.0);	// ����u��vΪ0ʱ�������log����
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

// ����rand()����0~RAND_MAX֮���"����"�ֲ���������������м򵥵����Ա任
double UniformRand(double a, double b)			// ����[a, b]�ϵľ��ȷֲ�
{
	return a + rand()*(b-a)/RAND_MAX;
}

// Score.c
void GetMemory(Score **data, Score **data0, int n)	// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
{													// ����Լ����ָ��ǿվͱ�ʾָ��"ӵ��"�ѿռ���Դ
	if(*data0!=NULL) free(*data0);					// ���ͷ�ԭ����"ӵ��"�Ķѿռ���Դ
	if(*data !=NULL) free(*data);
	*data0 = (Score*)calloc(n, sizeof(Score));		// ���������µģ���������Ҫ��ģ��ѿռ���Դ
	*data  = (Score*)calloc(n, sizeof(Score));
}

void FreeMemory(Score **data, Score **data0)		// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;							// ��һ����ֵ���ǳ���Ҫ������"����Լ��"
}

void InitScore(struct Score *data, int n)
{
	double mean=72, variance=6*6;
	int i;
	for(i=0; i<n; i++)
	{
		sprintf(data[i].Id, "%08d", i+1);			// ����ѧ sprintf ��������ע�⣺ԭʼ�����У�ѧ������ȫ˳�����еģ�
		data[i].Total  = data[i].Chinese   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Math      = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].English   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Physics   = (int)(0.5+GaussRand(mean, variance));
		data[i].Total += data[i].Chemistry = (int)(0.5+GaussRand(mean, variance));
	}
}

void ReSet(Score *data, const Score *data0, int n)	// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

int Check(const Score *a, int size)					// δ������ȫ����ȷ�Լ��飬����������Ԫ���Ƿ��Ѱ���������
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
		m = size;							// ��������
	printf("\t����������ݣ����ܷ�ǰ�����������ݣ�\n");
	printf("\tѧ�� \t\t�ܷ�\t����\t��ѧ\t����\t����\t��ѧ\n");
	for(i=0; i<m; i++)
		printf("\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", data[i].Id,
			data[i].Total, data[i].Chinese, data[i].Math,
			data[i].English, data[i].Physics, data[i].Chemistry);
}

// ���ֻ������������㷨
// ���������㷨

void Bubble(Score *num, int size)
{
    int i, j, k, up, down, flag;
    long long int com, ass;
    Score temp;
    down = size - 1;
    up = 0;
    for(i = size - 1; i > 0; i--)//��ǰ������
    {
        for(j = up; j < down; j++)
        {
            if(num[j].Total< num[j+1].Total)
            {
                temp = num[j];
                num[j]= num[j+1];
                num[j+1] = temp;
                ass+=3;
                flag = j;//ȡ����ǰ������±꣬���±�֮��������Ѿ��ź���
            }
            com+=1;
        }

            if(flag == -1)
            {
                break;
            }
            down = flag;//ȡ��flag��ֵ
            flag = -1;//����flag

            for(k = down; k > up; k--)
            {
                if(num[k].Total > num[k-1].Total)
                {
                    temp = num[k];
                    num[k] = num[k-1];
                    num[k-1] = temp;
                    ass+=3;
                    flag = k;//ȡ���Ӻ���ǰ���±꣬���±�֮ǰ�������Ѿ��ź���
                }
                com+=1;
            }

            if(flag == -1)
            {
                break;
            }
            up = flag;//ȡ��flag��ֵ
            flag = -1;//����flag
    }
     printf("\tBubble�Ƚϴ�����%lld     Bubble��ֵ������%lld\n",com,ass);
}






//������������
void Swap(Score* a, Score* b)
{
    Score temp = *a;
    *a = *b;
    *b = temp;
}

//ѡ������
void Select(Score *a, int size)   //�Ż����ѡ������
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
        if (begin == min)				//����max
        {
            min = max;
            ass+=1;
        }
        com+=1;
        Swap(&a[end], &a[min]);

        begin++;
        end--;
    }

	 printf("\tSelect�Ƚϴ�����%lld     Select��ֵ������%lld\n",com,ass);
}

void Qsort(Score* a, int size)
{
    int gap = size;
    long long int com,ass;
    while (gap > 1)
    {
        gap = gap / 3 + 1;	//����ϣ������
        int i = 0;
        for (i = 0; i < size - gap; i++)	//��0������size-gap-1
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
            ass+=1;	//�� end+gap ��Ϊ����λ��
        }
    }
    printf("\txierQsort�Ƚϴ�����%lld    xierQsort��ֵ������%lld\n",com,ass);
}
// Sorts.c		���֣�ð�ݡ�ѡ�񡢿��٣����������㷨������
double gettime(int restart)					// ������Ĭ��ֵ�������ʾ���¼�ʱ
{											// �����ۼƼ�ʱ
	double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t=0;						// ��̬�ֲ��������洢��ʱ���
	if(restart||t==0) t = clock();			// ����ʵ�ξ����Ƿ�����ȷ����ʱ���
	return c*(clock()-t);					// ����һ��ʱ�㵽������������ʱ��
}

void I_GetMemory(int **data, int **data0, int n)		// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
{														// ����Լ����ָ��ǿվͱ�ʾָ��"ӵ��"�ѿռ���Դ
	if(*data0!=NULL) free(*data0);						// ���ͷ�ԭ����"ӵ��"�Ķѿռ���Դ
	if(*data !=NULL) free(*data);
	*data0 = (int*)calloc(n, sizeof(int));				// ���������µģ���������Ҫ��ģ��ѿռ���Դ
	*data  = (int*)calloc(n, sizeof(int));
}

void D_GetMemory(double **data, double **data0, int n)	// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
{														// ����Լ����ָ��ǿվͱ�ʾָ��"ӵ��"�ѿռ���Դ
	if(data0!=NULL) free(*data0);						// ���ͷ�ԭ����"ӵ��"�Ķѿռ���Դ
	if(data !=NULL) free(*data);
	*data0 = (double*)calloc(n, sizeof(double));		// ���������µģ���������Ҫ��ģ��ѿռ���Դ
	*data  = (double*)calloc(n, sizeof(double));
}

void I_FreeMemory(int **data, int **data0)				// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;								// ��һ����ֵ���ǳ���Ҫ������"����Լ��"
}

void D_FreeMemory(double **data, double **data0)		// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
{
	if(*data0!=NULL) free(*data0);
	if(*data !=NULL) free(*data);
	*data0 = *data = NULL;								// ��һ����ֵ���ǳ���Ҫ������"����Լ��"
}

void I_InitData(int *data, int n, int flag)
{
	int i;
	switch(flag)
	{
	case -1: for(i=0; i<n; i++) data[i] = n-1-i;						break;	// ���򣨴Ӵ�С��
	case 0:	 for(i=0; i<n; i++) data[i] = i;							break;	// ˳�򣨴�С����
	case 1:  for(i=0; i<n; i++) data[i] = (int)(0.5+UniformRand(54,90));break;	// [54,90]�ϵľ��ȷֲ�
	default: for(i=0; i<n; i++) data[i] = (int)(0.5+GaussRand(72, 6*6));break;	// ��̬�ֲ�����ֵ72������36��������6��
	}
}

void D_InitData(double *data, int n, int flag)
{
	int i;
	switch(flag)
	{
	case -1: for(i=0; i<n; i++) data[i] = n-1-i;			break;	// ���򣨴Ӵ�С��
	case 0:	 for(i=0; i<n; i++) data[i] = i;				break;	// ˳�򣨴�С����
	case 1:  for(i=0; i<n; i++) data[i] = UniformRand(54,90);break;	// [54,90]�ϵľ��ȷֲ�
	default: for(i=0; i<n; i++) data[i] = GaussRand(72, 6*6);break;	// ��̬�ֲ�����ֵ72������36��������6��
	}
}

void I_ReSet(int *data, const int *data0, int n)		// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

void D_ReSet(double *data, const double *data0, int n)	// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
{
	int i;
	for(i=0; i<n; i++)
		data[i] = data0[i];
}

int I_Check(const int *a, int size)						// ��������Ԫ���Ƿ��Ѱ���������
{
	int i;
	for(i=1; i<size; i++)
		if(a[i-1] > a[i])
			return 0;
	return 1;
}

int D_Check(const double *a, int size)					// ��������Ԫ���Ƿ��Ѱ���������
{
	int i;
	for(i=1; i<size; i++)
		if(a[i-1] > a[i])
			return 0;
	return 1;
}

// ���ֻ������Ż������㷨
void I_Bubble(int *num, int size)
{
    int i, j, k, up, down, temp, flag;
    up = size - 1;
    down = 0;
    long long int Bubblecom=0,Bubbleass=0;
    for(i = size - 1; i > 0; i--)//��ǰ������
    {
        for(j = down; j < up; j++)
        {
            if(num[j] > num[j+1])
            {
                temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                flag = j;//ȡ����ǰ������±꣬���±�֮��������Ѿ��ź���
                Bubbleass+=3;
            }
            Bubblecom++;
        }
        if(!Bubbleass)                                 //��һ������δ�������������غ���
			{printf("\tBubble�Ƚϴ�����%lld     Bubble��ֵ������%lld\n",Bubblecom,Bubbleass);return;}

            if(flag == -1)
            {
                break;
            }
            up = flag;//ȡ��flag��ֵ
            flag = -1;//����flag

            for(k = up; k > down; k--)
            {
                if(num[k] < num[k-1])
                {
                    temp = num[k];
                    num[k] = num[k-1];
                    num[k-1] = temp;
                    flag = k;//ȡ���Ӻ���ǰ���±꣬���±�֮ǰ�������Ѿ��ź���
                    Bubbleass+=3;
                }
                Bubblecom++;
            }
            if(!Bubbleass)                                 //����������δ�������������غ���
			{printf("\tBubble�Ƚϴ�����%lld     Bubble��ֵ������%lld\n",Bubblecom,Bubbleass);return;}

            if(flag == -1)
            {
                break;
            }
            down = flag;//ȡ��flag��ֵ
            flag = -1;//����flag
    }
    printf("\tBubble�Ƚϴ�����%lld     Bubble��ֵ������%lld\n",Bubblecom,Bubbleass);
}

void D_Bubble(double *num, int size)
{
    int i, j, k, up, down, flag;
    double temp;
    up = size - 1;
    down = 0;
    long long int Bubblecom=0,Bubbleass=0;
    for(i = size - 1; i > 0; i--)//��ǰ������
    {
        for(j = down; j < up; j++)
        {
            if(num[j] > num[j+1])
            {
                temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                flag = j;//ȡ����ǰ������±꣬���±�֮��������Ѿ��ź���
                Bubbleass+=3;
            }
            Bubblecom++;
        }
        if(!Bubbleass)                                 //��һ������δ�������������غ���
			{printf("\tBubble�Ƚϴ�����%lld    Bubble��ֵ������%lld\n",Bubblecom,Bubbleass);return;}

            if(flag == -1)
            {
                break;
            }
            up = flag;//ȡ��flag��ֵ
            flag = -1;//����flag

            for(k = up; k > down; k--)
            {
                if(num[k] < num[k-1])
                {
                    temp = num[k];
                    num[k] = num[k-1];
                    num[k-1] = temp;
                    flag = k;//ȡ���Ӻ���ǰ���±꣬���±�֮ǰ�������Ѿ��ź���
                    Bubbleass+=3;
                }
                Bubblecom++;
            }
            if(!Bubbleass)                                 //����������δ�������������غ���
			{printf("\tBubble�Ƚϴ�����%lld     Bubble��ֵ������%lld\n",Bubblecom,Bubbleass);return;}

            if(flag == -1)
            {
                break;
            }
            down = flag;//ȡ��flag��ֵ
            flag = -1;//����flag
    }
    printf("\tBubble�Ƚϴ�����%lld    Bubble��ֵ������%lld\n",Bubblecom,Bubbleass);
}


//ѡ��������Ż�(һ�ν�����Ԫ�ط�����������λ���ϣ�
void swap(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
void I_Select(int *array, int size)
{
	//��Сֵ�±�
	int minpos = 0;
	//���ֵ�±�
	int maxpos = 0;
	int left = 0;
	int right = size - 1;
	int j = 0;
	long long int selectcom=0,selectass=0;
	//ѭ��size-1��
	while (left < right)
	{
		maxpos = left;
		minpos = left;
		//ȷ�����ֵ�±��Լ���Сֵ�±�
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
		//�����ֵ�嵽���
		if (maxpos != right)
		{
			swap(&array[maxpos], &array[right]);
			selectass+=3;
		}
		//��ֹminpos�����ֵҪ�����λ��
		if (minpos == right)
		{
			minpos = maxpos;
			selectass++;
		}
		//����Сֵ�嵽��ǰ��
		if (minpos != left)
		{
			swap(&array[minpos], &array[left]);
			selectass+=3;
		}
		selectcom+=2;
		left++;
		right--;
	}
	 printf("\tSelect�Ƚϴ�����%lld     Select��ֵ������%lld\n",selectcom,selectass);
}


void swap1(double *x, double*y)
{
	double tmp = *x;
	*x = *y;
	*y = tmp;
}
void D_Select(double *array, int size)
{
	//��Сֵ�±�
	int minpos = 0;
	//���ֵ�±�
	int maxpos = 0;
	int left = 0;
	int right = size - 1;
	int j = 0;
	long long int selectcom=0,selectass=0;
	//ѭ��size-1��
	while (left < right)
	{
		maxpos = left;
		minpos = left;
		//ȷ�����ֵ�±��Լ���Сֵ�±�
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
		//�����ֵ�嵽���
		if (maxpos != right)
		{
			swap1(&array[maxpos], &array[right]);
		}
		//��ֹminpos�����ֵҪ�����λ��
		if (minpos == right)
		{
			minpos = maxpos;
		}
		//����Сֵ�嵽��ǰ��
		if (minpos != left)
		{
			swap1(&array[minpos], &array[left]);

		}
		left++;
		right--;
	}
	 printf("\tSelect�Ƚϴ�����%lld     Select��ֵ������%lld\n",selectcom,selectass);
}
//ϣ������
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
	 printf("\txierQsort�Ƚϴ�����%lld    xierQsort��ֵ������%lld\n",xiercom,xierass);
}

//duoble����

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
		 printf("\txierQsort�Ƚϴ�����%lld    xierQsort��ֵ������%lld\n",xiercom,xierass);
}

void I_Test()
{
	int *data0=NULL, *data=NULL;								// ָ���ʼ��ΪNULL�ǳ���Ҫ��
	char InitConf[][20] = {"��ȫ����", "��ȫ˳��", "���ȷֲ�", "��̬�ֲ�"};	// C-�ַ������飨���ݷֲ���ʽ��
	char algo[][20] = {"ð������", "ѡ������", "��������"};		// C-�ַ������飨�����㷨���ƣ�
	void (*f[])(int*, int) = {I_Bubble, I_Select, I_Qsort};		// ����ָ�����飨Ԫ��Ϊһϵ�к�������ڵ�ַ��
	int i, j, n, m = sizeof(f)/sizeof(*f);						// mΪ����ָ������f��Ԫ�ظ������˴���3������ָ�룬�ֱ�ָ��3������������ڵ�ַ��
	int flag[20];												// ������Ϊ������20�㹻���ڱ��� m����¼��ͬ�㷨ִ�е���ȷ��
	double t[20];												// ͬ�ϡ���¼��ͬ�㷨��ִ��ʱ��

	for(j=2; j>=-1; j--)										// ���ݷֲ���ʽ
	{
		printf("\n��������(%s)\n", InitConf[j+1]);
		for(i=0; i<m; i++)
			printf("\t%s", algo[i]);
		printf("\n");
		for(n=1024; n<=65536; n*=2)
		{
			I_GetMemory(&data, &data0, n);						// �������ѿռ�
			I_InitData(data0, n, j);							// ����ԭʼ����
			printf("%d", n);
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					break;
				I_ReSet(data, data0, n);						// �ָ�ԭʼ����
				gettime(1);										// ���ü�ʱ���
				f[i](data, n);									// �� i �������㷨
				t[i] = gettime(0);								// ���شӼ�ʱ��㵽Ŀǰ��������ʱ�䣨�룩
				flag[i] = I_Check(data, n);						// �����������ȷ��
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					printf("\t");
				else
					printf("\t%lf", t[i]);
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					printf("\t�����������ڵݹ���̫����ܵ���ջ�������������");
				else
					printf("\t%s: %s", algo[i], (flag[i]?"��ȷ":"����"));
			}
			printf("\n");
			I_FreeMemory(&data, &data0);						// �ͷŶѿռ���Դ����ʹָ��Ϊ��
		}
	}
}

void D_Test()
{
	double *data0=NULL, *data=NULL;								// ָ���ʼ��ΪNULL�ǳ���Ҫ��
	char InitConf[][20] = {"��ȫ����", "��ȫ˳��", "���ȷֲ�", "��̬�ֲ�"};	// C-�ַ������飨���ݷֲ���ʽ��
	char algo[][20] = {"ð������", "ѡ������", "��������"};		// C-�ַ������飨�����㷨���ƣ�
	void (*f[])(double*, int) = {D_Bubble, D_Select, D_Qsort};	// ����ָ�����飨Ԫ��Ϊһϵ�к�������ڵ�ַ��
	int i, j, n, m = sizeof(f)/sizeof(*f);						// mΪ����ָ������f��Ԫ�ظ������˴���3������ָ�룬�ֱ�ָ��3������������ڵ�ַ��
	int flag[20];												// ������Ϊ������20�㹻���ڱ��� m����¼��ͬ�㷨ִ�е���ȷ��
	double t[20];												// ͬ�ϡ���¼��ͬ�㷨��ִ��ʱ��

	for(j=2; j>=-1; j--)										// ���ݷֲ�����
	{
		printf("\n˫���ȸ���������(%s)\n", InitConf[j+1]);
		for(i=0; i<m; i++)
			printf("\t%s", algo[i]);
		printf("\n");
		for(n=1024; n<=65536; n*=2)
		{
			D_GetMemory(&data, &data0, n);						// �������ѿռ�
			D_InitData(data0, n, j);							// ����ԭʼ����
			printf("%d", n);
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					break;
				D_ReSet(data, data0, n);							// �ָ�ԭʼ����
				gettime(1);										// ���ü�ʱ���
				f[i](data, n);									// �� i �������㷨
				t[i] = gettime(0);								// ���شӼ�ʱ��㵽Ŀǰ��������ʱ�䣨�룩
				flag[i] = D_Check(data, n);						// �����������ȷ��
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					printf("\t");
				else
					printf("\t%lf", t[i]);
			}
			for(i=0; i<m; i++)
			{
				if(n==65536 && j<=0 && i==m-1)					// j<=0(��ȫ˳����ȫ����)��i==m-1(�������򣬵ݹ��㷨)
					printf("\t�����������ڵݹ���̫����ܵ���ջ�������������");
				else
					printf("\t%s: %s", algo[i], (flag[i]?"��ȷ":"����"));
			}
			printf("\n");
			D_FreeMemory(&data, &data0);						// �ͷŶѿռ���Դ����ʹָ��Ϊ��
		}
	}
}

void Score_Test()
{
	Score *data0=NULL, *data=NULL;							// ����ָ���ʼ��ΪNULL�ǳ���Ҫ��
	char algo[][20] = {"ð������", "ѡ������", "��������"};	// C-�ַ������飨�����㷨���ƣ�
	void (*f[])(Score*, int) = {Bubble, Select, Qsort};		// ����ָ�����飨Ԫ��Ϊһϵ�к�������ڵ�ַ��
	int i, n, m = sizeof(f)/sizeof(*f);
	int flag;
	double t;

	printf("\n�ṹ��(Score)�������� (��̬�ֲ�)\n");
	for(n=1024; n<=65536; n*=2)
	{
		GetMemory(&data, &data0, n);						// �������ѿռ�
		InitScore(data0, n);								// ����ԭʼ����
		for(i=0; i<m; i++)
		{
			ReSet(data, data0, n);							// �ָ�ԭʼ����
			gettime(1);										// ���ü�ʱ���
			f[i](data, n);									// �� i �������㷨
			t = gettime(0);									// ���شӼ�ʱ��㵽Ŀǰ��������ʱ�䣨�룩
			flag = Check(data, n);							// �����������ȷ��
			printf("%d\t%lf\t%s: %s\n", n, t, algo[i], (flag?"��ȷ":"����"));
			ShowScore(data, n, 10);							// ����������10����ڰ��������У���߷ֵ�һ�������
		}
		FreeMemory(&data, &data0);							// �ͷŶѿռ���Դ����ʹָ��Ϊ��
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
	unsigned char* p1 = (unsigned char*)str1;			// ˼���⣺Ϊʲô��Ҫ����ǿ��ת����unsigned char*
	unsigned char* p2 = (unsigned char*)str2;
	while (*p1 && *p2 && *p1++ == *p2++)					// ˼���⣺����Щ���ʹ��ѭ������
		;
	return *p1 > *p2 ? 1 : (*p1 < *p2 ? -1 : 0);
}

void TestStrCmp()
{
	char* str[] = { "abc", "abcd", "�Ϻ���ѧ", "", "�Ϻ�" };
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

char** GetStringsA1(char(*source)[NUM], int n)		// ˼���⣺�������������GetStringSA�����Ĺ����Ƿ���ͬ�����ñ�����ʱ��Ӧ���ú��ֱ��ʽ��
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

void FreeStrings1(char** strs, int n)		// ˼���⣺�������ܷ�����ͷŶ��ڴ���Դ�������к�ȱ�ݣ�
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
	char strA[][NUM] = { "enter", "number", "C/C++�������", "size", "ָ��", "begin", "of", "����", "cat", "case", "program", "certain", "a", "cake", "side" };
	char* strB[] = { "enter", "number", "C/C++�������", "size", "ָ��", "begin", "of", "����", "cat", "case", "program", "certain", "an", "cake", "side" };
	char** strC = NULL, ** strD = NULL;
	int n1 = sizeof(strA) / sizeof(*strA), n2 = sizeof(strB) / sizeof(*strB);
	GetStringsA(&strC, strA, n1);			// ������� GetStringsA1 ��������������Ӧ���������ģ�
	GetStringsB(&strD, strB, n2);			// �뻭��strC��strD�Ľṹͼ

	printf("\n\t*** ���ֲ�ͬ�洢��ʽ��C-�ַ������������ ***\n");
	ShowStringsA("\nԭʼ����: ", strA, n1);
	BubbleA(strA, n1);
	ShowStringsA("\n������: ", strA, n1);

	ShowStringsB("\nԭʼ����: ", strB, n2);
	BubbleB(strB, n2);
	ShowStringsB("\n������: ", strB, n2);

	ShowStringsB("\nԭʼ����: ", strC, n1);
	BubbleB(strC, n1);						// �˴��ܷ����BubbleA������strC�����������Ҫ��BubbleA��������Ҫ��GetStringsA���������������޸ģ�
	ShowStringsB("\n������: ", strC, n1);

	ShowStringsB("\nԭʼ����: ", strD, n2);
	BubbleB(strD, n2);						// �˴��ܷ����BubbleA������strD�����������Ҫ��BubbleA��������Ҫ��GetStringsB���������������޸ģ�
	ShowStringsB("\n������: ", strD, n2);

	FreeStrings(&strC, n1);					// ������� FreeStrings1 ��������Ӧ��ִ����Щ��䣿
	FreeStrings(&strD, n2);					// ������� FreeStrings1 ��������Ӧ��ִ����Щ��䣿
}
int main()					// ������
{
//	void TestStrCmp();	TestStrCmp();	return 0;

	srand(time(NULL));		// ���������������������
	
	I_Test();				// ����int��������
	D_Test();				// ����double��������
	Score_Test();			// ����Score��������

                        	// ��ʽ����ĺ���ʱ�����齫�����3�����ע���������Խ�ʡʱ��
	//void TestString();		// ����ԭ�ͣ����ں�������
	//TestString();			// ��������

	return 0;
}

