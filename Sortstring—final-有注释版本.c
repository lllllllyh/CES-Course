// SortString.c
/* ˼����
1.	����Ĳ��Ժ����У�
	(1) ����˼��Ȼ����г�����֤sizeof(strA), sizeof(strB), sizeof(strC), sizeof(strD)��Ϊ�����ֽڣ���Щ�ֽ�λ���ڴ�ʲô���򣨴�������ȫ����������ջ��������������
	(2) strA��strB��strC��strD��ϵ��C-�ַ�����������ݴ洢���ڴ��ʲô�������ǵĶ�/д���ԣ��Ƿ�ɶ�����д����Σ�

2.	���BubbleA��BubbleB��������֮ǰ��˼��
	(1) ��αȽ������ַ��������ݣ�
	(2) �洢��ʲô������ַ����ܽ��������ݣ�
	(3) �����ܽ����ַ��������ݣ���������н���ʲô��

3.	GetStringsA��GetStringB�����ĵ�һ����ʽ����Ϊʲô��Ҫ�õ�����ָ�룬������ö���ָ���������
	GetStringsA1����Ӧ�����ʹ�ã�
4.	FreeStrings��������ʽ����Ϊʲô��Ҫ�õ�����ָ�룿����ش��������⣩
	������ö���ָ�루��FreeStrings1���������ܷ��ͷ�������Ķ��ڴ���Դ��FreeStrings������FreeStrings1�����Ĺؼ���ͬ����ʲô��
*/

/*(1) sizeof(strA) ���������� strA ���ܴ�С���� 15 * NUM �ֽڡ���Щ�ֽ�λ��ȫ����������
sizeof(strB) ������ָ������ strB ���ܴ�С���� 15 * sizeof(char*) �ֽڡ���Щ�ֽ�λ��ȫ����������
sizeof(strC) �� sizeof(strD) ��������ָ������Ĵ�С���� sizeof(char**) �ֽڡ���Щ�ֽ�λ��ջ����
(2) strA��strB��strC��strD ��ŵ� C �ַ�����������ݴ洢��ȫ������������Щ����������ǿɶ���д�ġ�

(1) Ҫ�Ƚ������ַ��������ݣ�����ʹ�� strcmp ������ʵ�֡����ᰴ���ֵ�˳����бȽϡ�
(2) �洢��ȫ����������������ַ����ܹ����������ݣ���Ϊȫ���������Ͷ������ڴ��ǿ���ֱ�ӷ��ʺ��޸ĵġ�
(3) ����ַ����洢��ջ�����޷�ֱ�ӽ��������ݡ�����������У����Խ���ָ�������ʵ�ʵ��ַ������ݡ�

GetStringsA �� GetStringsB �����ĵ�һ����ʽ������Ҫʹ������ָ���ԭ������Ҫ�޸Ĵ���ָ���ָ�������ʹ�ö���ָ�룬�޷��������������ڲ��޸�ָ���ֵ�������޷����ط�����ڴ��ĵ�ַ��
GetStringsA1 �������������·�ʽ���ã�
char** strC = GetStringsA1(strA, n1);

FreeStrings ��������ʽ������Ҫʹ������ָ���ԭ����Ϊ���ܹ��������ָ����Ϊ NULL���Է�ֹ��������ָ�롣
ͨ��������ָ��ָ���ָ����Ϊ NULL������ȷ�����ͷ��ڴ�󲻻���ʵ����ͷŵ��ڴ��ĵ�ַ��
���ʹ�ö���ָ�루�� FreeStrings1 �������������ͷ�������Ķ��ڴ���Դ�������ú�����ָ����Ȼָ�����ͷŵ��ڴ�飬���ܵ��º����Ĳ���Ԥ����Ϊ��
�����Ĺؼ���ͬ�������Ƿ�ָ����Ϊ NULL��*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

#define NUM 20

void BubbleA(char(*str)[NUM], int size)
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
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
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
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
	unsigned char* p2 = (unsigned char*)str2;			// ������Ϊ�����޷����ַ��洢ʱ������ȷ���Ƚϵ���ȷ�ԣ������ڽ��бȽ�ʱ���ַ���λ�ĸ��š�����ת����ÿ���ַ���Ϊһ���������޷����������бȽϡ�
	while (*p1 && *p2 && *p1++ == *p2++)					// ˼���⣺����Щ���ʹ��ѭ������
	{														//1.������һ���ַ����Ѿ��ȽϽ�����������һ��ָ��ָ�����ַ��������� '\0'�� 2.����ָ��ָ����ַ������
		p1++;
		p2++;
	}
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

/*�����������Ĺ�������ͬ�ģ��������ڽ��ַ���������ж�̬�ڴ���䣬����Դ�ַ�����������ݸ��Ƶ��µ��ڴ���С����ǵ��������ڴ����������ʽ��ͬ��
GetStringsAʹ��������ָ��char*** dest��Ϊ��һ����ʽ������ͨ�������dest�����޸�ָ���ָ��ʵ����ֱ�ӷ��ط�����ڴ��ĵ�ַ���ں����ڲ���ͨ��(*dest)����������ָ������ݡ�
GetStringsA1ʹ���˶���ָ��char** dest��Ϊ��һ����ʽ�����������ڲ�ͨ��dest����������ָ������ݡ��ں�������ʱ��ֱ�ӷ����˷�����ڴ��ĵ�ַ��
����GetStringsAʱ����Ҫ����ָ������ָ���ָ��ĵ�ַ��Ϊ��һ��������������GetStringsA1ʱ��ֱ�Ӵ������ָ����Ϊ��һ��������
���Ե���GetStringsAʱ��Ҫʹ��&dest������GetStringsA1ʱֱ��ʹ��dest���ɡ�*/

//char(*source)[NUM]��������ָ������
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

char(*GetStringsA11(char source[][NUM], int n))[NUM]
{
	char(*dest)[NUM] = calloc(n, sizeof(char[NUM]));
	if (dest == NULL) return dest;
	int i;
	for (i = 0; i < n; i++)
	{
		strcpy(dest[i], source[i]);
	}
	return dest;
}

//char* source[]��char** source��һ������,dest=&source
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

/*�����������Ĺ��ܶ����ͷŶ�̬������ַ���������ڴ���Դ��Ȼ�������Ǵ���һЩ�����ȱ�ݡ�
FreeStrings����ʹ��������ָ��char*** strs��Ϊ��һ����ʽ������ͨ�������strs�����޸�ָ���ָ���ں����ڲ���ͨ��(*strs)����������ָ������ݡ�
ͨ���������ͷ�ÿ���ַ����ڴ�������ͷŰ����ַ���ָ����ڴ�顣
FreeStrings1����ʹ���˶���ָ��char** strs��Ϊ��һ����ʽ�����������ڲ�ֱ��ͨ��strs����������ָ������ݡ�
ͨ���������ͷ�ÿ���ַ����ڴ�������ͷ��ַ���ָ��������ڴ�顣
�ڶ�������FreeStrings1��������ͷŶ��ڴ���Դ�����񣬵�����һ��Ǳ�ڵ�ȱ�ݡ��ں�����������Ȼ�ͷ����ַ���ָ��������ڴ�飬��û�н�ָ��strs������ΪNULL��
����ζ���ں����ⲿ��Ȼ���Է��ʵ��Ѿ��ͷŵ��ڴ��ĵ�ַ�����ܻᵼ������ָ������⡣
Ϊ�˽��������⣬������FreeStrings1����������strs = NULL;����ָ�뱾����ΪNULL���Ա�������ָ������⡣*/

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
		strs = NULL;
	}
}

void TestString()
{
	char strA[][NUM] = { "enter", "number", "C/C++�������", "size", "ָ��", "begin", "of", "����", "cat", "case", "program", "certain", "a", "cake", "side" };
	char* strB[] = { "enter", "number", "C/C++�������", "size", "ָ��", "begin", "of", "����", "cat", "case", "program", "certain", "an", "cake", "side" };
	char** strC = NULL, ** strD = NULL; //����ָ��char** strC�൱��char* strC[]
	int n1 = sizeof(strA) / sizeof(*strA), n2 = sizeof(strB) / sizeof(*strB);
	GetStringsA(&strC, strA, n1);			// ������� GetStringsA1 ��������������Ӧ���������ģ�
	//char(*strC1)[NUM] = GetStringsA11(strA, n1);
	GetStringsB(&strD, strB, n2);			// �뻭��strC��strD�Ľṹͼ

	printf("\n\t*** ���ֲ�ͬ�洢��ʽ��C-�ַ������������ ***\n");
	ShowStringsA("\nԭʼ����: ", strA, n1);
	BubbleA(strA, n1);
	ShowStringsA("\n������: ", strA, n1);

	ShowStringsB("\nԭʼ����: ", strB, n2);
	BubbleB(strB, n2);
	ShowStringsB("\n������: ", strB, n2);

	ShowStringsB("\nԭʼ����: ", strC, n1);
	BubbleB(strC, n1);								// �˴��ܷ����BubbleA������strC�����������Ҫ��BubbleA��������Ҫ��GetStringsA���������������޸ģ�
	ShowStringsB("\n������: ", strC, n1);			// �����ԣ�����ʹ���˶�ά�ַ������ָ�� char(*str)[NUM]�������� char** ���͵�ָ�롣���ֲ���һ�����ʣ����Ըú�������ֱ�Ӷ� char** strC ��������
	//BubbleA(strC1, n1);							// ���Ҫ��BubbleA��������Ҫ��GetStringsA�����ĳ�GetStringsA11����ʽ��������һ��strC1���ܣ����������������ʱ����ShowStringsA�������
	//ShowStringsA("\n������: ", strC1, n1);

	ShowStringsB("\nԭʼ����: ", strD, n2);
	BubbleB(strD, n2);						// �˴��ܷ����BubbleA������strD�����������Ҫ��BubbleA��������Ҫ��GetStringsB���������������޸ģ�
	ShowStringsB("\n������: ", strD, n2); // ���ܣ�����ʹ���˶�ά�ַ������ָ�� char(*str)[NUM]�������� char** ���͵�ָ�롣���ֲ���һ�����ʣ����Ըú�������ֱ�Ӷ� char** strC ��������
											// ��������GetStringsA�������޸�����
											
	FreeStrings(&strC, n1);					// ������� FreeStrings1 ��������Ӧ��ִ����Щ��䣿 FreeStrings1(strC, n1);
	FreeStrings(&strD, n2);					// ������� FreeStrings1 ��������Ӧ��ִ����Щ��䣿 FreeStrings1(strD, n2);	
}
