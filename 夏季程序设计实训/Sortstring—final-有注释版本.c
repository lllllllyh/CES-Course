// SortString.c
/* 思考题
1.	下面的测试函数中，
	(1) 请先思考然后进行程序验证sizeof(strA), sizeof(strB), sizeof(strC), sizeof(strD)各为多少字节，这些字节位于内存什么区域（代码区、全局数据区、栈区、堆区）？。
	(2) strA、strB、strC、strD联系的C-字符串数组的内容存储在内存的什么区域？它们的读/写属性（是否可读、可写）如何？

2.	设计BubbleA，BubbleB两个函数之前，思考
	(1) 如何比较两个字符串的内容？
	(2) 存储在什么区域的字符串能交换其内容？
	(3) 若不能交换字符串的内容，排序操作中交换什么？

3.	GetStringsA和GetStringB函数的第一个形式参数为什么需要用到三级指针，如果仅用二级指针会怎样？
	GetStringsA1函数应该如何使用？
4.	FreeStrings函数的形式参数为什么需要用到三级指针？（或回答如下问题）
	如果仅用二级指针（见FreeStrings1函数），能否释放所申请的堆内存资源？FreeStrings函数与FreeStrings1函数的关键不同点是什么？
*/

/*(1) sizeof(strA) 将返回数组 strA 的总大小，即 15 * NUM 字节。这些字节位于全局数据区。
sizeof(strB) 将返回指针数组 strB 的总大小，即 15 * sizeof(char*) 字节。这些字节位于全局数据区。
sizeof(strC) 和 sizeof(strD) 都将返回指针变量的大小，即 sizeof(char**) 字节。这些字节位于栈区。
(2) strA、strB、strC、strD 存放的 C 字符串数组的内容存储在全局数据区。这些数组的内容是可读可写的。

(1) 要比较两个字符串的内容，可以使用 strcmp 函数来实现。它会按照字典顺序进行比较。
(2) 存储在全局数据区或堆区的字符串能够交换其内容，因为全局数据区和堆区的内存是可以直接访问和修改的。
(3) 如果字符串存储在栈区，无法直接交换其内容。在排序操作中，可以交换指针而不是实际的字符串内容。

GetStringsA 和 GetStringsB 函数的第一个形式参数需要使用三级指针的原因是需要修改传入指针的指向。如果仅使用二级指针，无法在这两个函数内部修改指针的值，导致无法返回分配的内存块的地址。
GetStringsA1 函数可以用以下方式调用：
char** strC = GetStringsA1(strA, n1);

FreeStrings 函数的形式参数需要使用三级指针的原因是为了能够将传入的指针置为 NULL，以防止出现悬空指针。
通过将三级指针指向的指针置为 NULL，可以确保在释放内存后不会访问到已释放的内存块的地址。
如果使用二级指针（如 FreeStrings1 函数），可以释放所申请的堆内存资源，但调用函数后指针仍然指向已释放的内存块，可能导致后续的不可预测行为。
函数的关键不同点在于是否将指针置为 NULL。*/

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
	unsigned char* p1 = (unsigned char*)str1;			// 思考题：为什么需要进行强制转换成unsigned char*
	unsigned char* p2 = (unsigned char*)str2;			// 这是因为采用无符号字符存储时，可以确保比较的正确性，避免在进行比较时出现符号位的干扰。这种转换将每个字符视为一个独立的无符号整数进行比较。
	while (*p1 && *p2 && *p1++ == *p2++)					// 思考题：有哪些情况使本循环结束
	{														//1.至少有一个字符串已经比较结束，即其中一个指针指向了字符串结束符 '\0'。 2.两个指针指向的字符不相等
		p1++;
		p2++;
	}
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

/*这两个函数的功能是相同的，都是用于将字符串数组进行动态内存分配，并将源字符串数组的内容复制到新的内存块中。它们的区别在于传入参数的形式不同。
GetStringsA使用了三级指针char*** dest作为第一个形式参数，通过传入的dest参数修改指针的指向，实现了直接返回分配的内存块的地址。在函数内部，通过(*dest)来操作三级指针的内容。
GetStringsA1使用了二级指针char** dest作为第一个形式参数，函数内部通过dest来操作二级指针的内容。在函数返回时，直接返回了分配的内存块的地址。
调用GetStringsA时，需要传入指向三级指针的指针的地址作为第一个参数，而调用GetStringsA1时，直接传入二级指针作为第一个参数。
所以调用GetStringsA时需要使用&dest，调用GetStringsA1时直接使用dest即可。*/

//char(*source)[NUM]本质上是指针数组
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

//char* source[]跟char** source是一个性质,dest=&source
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

/*这两个函数的功能都是释放动态分配的字符串数组的内存资源。然而，它们存在一些区别和缺陷。
FreeStrings函数使用了三级指针char*** strs作为第一个形式参数，通过传入的strs参数修改指针的指向。在函数内部，通过(*strs)来操作三级指针的内容。
通过遍历和释放每个字符串内存块后，最后释放包含字符串指针的内存块。
FreeStrings1函数使用了二级指针char** strs作为第一个形式参数，函数内部直接通过strs来操作二级指针的内容。
通过遍历和释放每个字符串内存块后，最后释放字符串指针数组的内存块。
第二个函数FreeStrings1可以完成释放堆内存资源的任务，但存在一个潜在的缺陷。在函数结束后，虽然释放了字符串指针数组的内存块，但没有将指针strs本身置为NULL。
这意味着在函数外部仍然可以访问到已经释放的内存块的地址，可能会导致悬垂指针的问题。
为了解决这个问题，可以在FreeStrings1函数最后添加strs = NULL;来将指针本身置为NULL，以避免悬垂指针的问题。*/

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
		strs = NULL;
	}
}

void TestString()
{
	char strA[][NUM] = { "enter", "number", "C/C++程序设计", "size", "指针", "begin", "of", "函数", "cat", "case", "program", "certain", "a", "cake", "side" };
	char* strB[] = { "enter", "number", "C/C++程序设计", "size", "指针", "begin", "of", "函数", "cat", "case", "program", "certain", "an", "cake", "side" };
	char** strC = NULL, ** strD = NULL; //二重指针char** strC相当于char* strC[]
	int n1 = sizeof(strA) / sizeof(*strA), n2 = sizeof(strB) / sizeof(*strB);
	GetStringsA(&strC, strA, n1);			// 如果换成 GetStringsA1 函数，则调用语句应该是怎样的？
	//char(*strC1)[NUM] = GetStringsA11(strA, n1);
	GetStringsB(&strD, strB, n2);			// 请画出strC或strD的结构图

	printf("\n\t*** 多种不同存储方式的C-字符串数组的排序 ***\n");
	ShowStringsA("\n原始数据: ", strA, n1);
	BubbleA(strA, n1);
	ShowStringsA("\n排序结果: ", strA, n1);

	ShowStringsB("\n原始数据: ", strB, n2);
	BubbleB(strB, n2);
	ShowStringsB("\n排序结果: ", strB, n2);

	ShowStringsB("\n原始数据: ", strC, n1);
	BubbleB(strC, n1);								// 此处能否调用BubbleA函数对strC进行排序？如果要用BubbleA函数，需要对GetStringsA函数进行怎样的修改？
	ShowStringsB("\n排序结果: ", strC, n1);			// 不可以，声明使用了二维字符数组的指针 char(*str)[NUM]，而不是 char** 类型的指针。两种不是一个性质，所以该函数不能直接对 char** strC 进行排序。
	//BubbleA(strC1, n1);							// 如果要用BubbleA函数，需要将GetStringsA函数改成GetStringsA11的形式，并动用一个strC1接受，并在输出排序结果的时候，用ShowStringsA进行输出
	//ShowStringsA("\n排序结果: ", strC1, n1);

	ShowStringsB("\n原始数据: ", strD, n2);
	BubbleB(strD, n2);						// 此处能否调用BubbleA函数对strD进行排序？如果要用BubbleA函数，需要对GetStringsB函数进行怎样的修改？
	ShowStringsB("\n排序结果: ", strD, n2); // 不能，声明使用了二维字符数组的指针 char(*str)[NUM]，而不是 char** 类型的指针。两种不是一个性质，所以该函数不能直接对 char** strC 进行排序。
											// 处理结果与GetStringsA函数的修改类似
											
	FreeStrings(&strC, n1);					// 如果调用 FreeStrings1 函数，则应该执行哪些语句？ FreeStrings1(strC, n1);
	FreeStrings(&strD, n2);					// 如果调用 FreeStrings1 函数，则应该执行哪些语句？ FreeStrings1(strD, n2);	
}
