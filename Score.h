// Score.h
#ifndef SCORE_H
#define SCORE_H

typedef struct Score
{
	char Id[9];															// �����8���ַ�
	int Chinese, Math, English, Physics, Chemistry, Total;				// 5�ſγ̳ɼ����ܷ�
} Score;

void GetMemory(Score **data, Score **data0, int n);		// ������ڴ�ռ䣬ͨ������"����"�׵�ַ
void FreeMemory(Score **data, Score **data0);			// �ͷ�ָ����"ӵ��"�Ķѿռ���Դ
void InitScore(struct Score *data, int n);
void ReSet(Score *data, const Score *data0, int n);		// ���ڻָ�"ԭʼ����"���Ա�֤��ͬ�������㷨������ȫ��ͬ������
int  Check(const Score *a, int size);					// ��������Ԫ���Ƿ��Ѱ���������
void ShowScore(const Score *data, int size, int m);		// ��������ǰm��Ԫ��

// ���ֻ����ģ�û���Ż��ģ������㷨
void Bubble(Score *a, int size);						// ð������(���ֽܷ�������)
void Select(Score *a, int size);						// ѡ������(���ֽܷ�������)
void Qsort(Score *a, int size);							// ��������(���ֽܷ�������)

#endif
