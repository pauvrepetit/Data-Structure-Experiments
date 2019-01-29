/* coding: GB2312 */
#define _CRT_SECURE_NO_WARNINGS		//在visual studio中操作时使其允许使用scanf等其认为不安全的函数

//定义常量
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

/*-------线性表的动态分配顺序存储结构--------*/
#define LIST_INIT_SIZE 100	//线性表存储空间的初始分配量

//定义数据元素类型
typedef int status;
typedef int ElemType;

#ifndef __SqList__
#define __SqList__
//定义线性表的结构
typedef struct {	//顺序表(顺序结构)的定义 动态分配
	ElemType * elem;	//存储空间基址
	int length;			//当前长度
	int listsize;		//当前分配的存储容量
}SqList;
#endif // __SqList__

//定义操作线性表的函数
//初始化线性表
status IntiaList(SqList * L) {
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L->elem)
		exit(OVERFLOW);
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
}
//销毁线性表
status DestroyList(SqList * L)
{
	free(L->elem);
	L->elem = NULL;
	return OK;
}
//清空线性表
status ClearList(SqList * L)
{
	L->length = 0;
	return OK;
}
//判断线性表是否为空
status ListEmpty(SqList L)
{
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}
//获取线性表的长度
int ListLength(SqList L)
{
	return L.length;
}
//获取线性表的第i个元素，并将其保存在e中
status GetElem(SqList L, int i, ElemType * e)
{
	if (i < 1 || i > ListLength(L))
		return OVERFLOW;	//i超出线性表中元素的范围，过大或者过小
	*e = L.elem[i - 1];
	return OK;
}
//获取元素值为e在线性表L中的位置
int LocateElem(SqList L, ElemType e)
{
	int i = 0;
	for (i = 0; i < ListLength(L); i++)
	{
		if (e == L.elem[i])		//此处的相等比较如果是浮点数的话应该修改为两者的差的绝对值小于0.000001
			return i + 1;
	}
	return -1;	//不存在该元素的情况
}
//获取线性表中元素内容为cur的前驱，并将其存储在pre_e中
status PriorElem(SqList L, ElemType cur, ElemType * pre_e)
{
	int i = 0;
	if (L.elem[0] == cur)
	{
		return -3;		//cur为线性表中的第一个元素
	}
	else
	{
		for (i = 0; i < ListLength(L); i++)
		{
			if (L.elem[i] == cur)
			{
				*pre_e = L.elem[i - 1];
				return OK;
			}
		}
		return INFEASTABLE;		//cur不在线性表中
	}
}
//获取线性表中元素内容为cur的后继，并将其存储在next_e中
status NextElem(SqList L, ElemType cur, ElemType * next_e)
{
	int i = 0;
	if (L.elem[ListLength(L) - 1] == cur)
	{
		return -3;		//cur为线性表的最后一个元素
	}
	else
	{
		for (i = 0; i < ListLength(L) - 1; i++)
		{
			if (L.elem[i] == cur)
			{
				*next_e = L.elem[i + 1];
				return OK;
			}
		}
		return INFEASTABLE;		//cur不在线性表中
	}
}
//在线性表的第i个位置插入元素e
status ListInsert(SqList * L, int i, ElemType e)
{
	int j = 0;
	if (i < 1 || i > L->length + 1)
		return OVERFLOW;	//i超出可插入的范围
	else if (L->length == L->listsize)
		return -3;			//线性表已满
	L->length++;
	for (j = L->length - 1; j >= i; j--)
	{
		L->elem[j] = L->elem[j - 1];
	}
	L->elem[i - 1] = e;
	return OK;
}
//删除线性表的第i个元素，并将其保存到e中
status ListDelete(SqList * L, int i, ElemType * e)
{
	int j = 0;
	if (i < 1 || i > L->length)
		return OVERFLOW;	//线性表中第i个元素不存在的情况
	*e = L->elem[i - 1];
	L->length--;
	for (j = i - 1; j < L->length; j++)
	{
		L->elem[j] = L->elem[j + 1];
	}
	return OK;
}
//依次打印线性表的每一个元素
status ListTrabverse(SqList L) {
	int i;
	printf("\n-----------all elements -----------------------\n");
	for (i = 0; i < L.length; i++) printf("%d ", L.elem[i]);
	printf("\n------------------ end ------------------------\n");
	return L.length;
}
//将线性表存储到文件
int LoadToFile(SqList L, char * filename)
{
	FILE * fp;
	if ((fp = fopen(filename, "w")) == NULL)
	{
		//文件打开失败
		return 1;
	}
	fwrite(L.elem, sizeof(ElemType), L.length, fp);
	fclose(fp);
	return 0;
}
//从线性表中加载数据
int LoadFromFile(SqList * L, char * filename)
{
	FILE * fp;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		//打开文件失败
		return -1;
	}
	if (L->length != 0)
		return 1;
	while (fread(&L->elem[L->length], sizeof(ElemType), 1, fp))
	{
		L->length++;
	}
	fclose(fp);
	return 0;
}