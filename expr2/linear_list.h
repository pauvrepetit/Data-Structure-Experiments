/* coding: GB2312 */
#define _CRT_SECURE_NO_WARNINGS		//在visual studio中操作时使其允许使用scanf等其认为不安全的函数

//定义常量
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

//定义数据类型
typedef int status;
typedef int ElemType;

//定义数据结构
typedef struct LNode {
	ElemType data;
	struct LNode * next;
} LNode;

//定义操作单链表的函数
//初始化单链表
status IntiaList(LNode * L)
{
	L->data = 0;
	L->next = NULL;
	return OK;
}

//销毁单链表
status DestroyList(LNode * L)
{
	L->data = INT_MIN;
	LNode * node1 = L->next;
	if (node1 == NULL)
		return OK;
	else
	{
		LNode * node2 = node1->next;
		while (node2 != NULL)
		{
			free(node1);
			node1 = node2;
			node2 = node2->next;
		}
		free(node1);
		L->next = NULL;
		return OK;
	}
}

//清空单链表
status ClearList(LNode * L)
{
	LNode * node1 = L->next;
	if (node1 == NULL)
		return OK;
	else
	{
		LNode * node2 = node1->next;
		while (node2 != NULL)
		{
			free(node1);
			node1 = node2;
			node2 = node2->next;
		}
		free(node1);
		L->next = NULL;
		return OK;
	}
}

//判断单链表是否为空表
status ListEmpty(LNode * L)
{
	if (L->next == NULL)
		return TRUE;
	else
		return FALSE;
}

//求单链表表长
int ListLength(LNode * L)
{
	int length = 0;
	while (L->next != NULL)
	{
		length++;
		L = L->next;
	}
	return length;
}

//获取单链表的第i个元素，并将其保存在e中
status GetElem(LNode * L, int i, ElemType * e)
{
	int j = 0;
	if (i <= 0)
		return OVERFLOW;
	while (j < i)
	{
		if (L->next == NULL)
			return OVERFLOW;
		L = L->next;
		j++;
	}
	*e = L->data;
	return OK;
}

//获取元素值e在单链表中第一次出现的位置
int LocateElem(LNode * L, ElemType e)
{
	int i;
	for (i = 1; ; i++)
	{
		L = L->next;
		if (L == NULL)
			return -1;
		if (L->data == e)
			return i;
	}
}

//获取单链表中元素内容为cur的前驱，并将其存储在pre_e中
status PriorElem(LNode * L, ElemType cur, ElemType * pre_e)
{
	if (L->next == NULL)
		return INFEASTABLE;
	if (L->next->data == cur)
		return -3;		//cur为单链表的第一个元素
	LNode * node = L->next->next;
	L = L->next;
	while (node != NULL)
	{
		if (node->data == cur)
		{
			*pre_e = L->data;
			return OK;
		}
		L = L->next;
		node = node->next;
	}
	return INFEASTABLE;		//cur不在单链表中
}

//获取单链表中元素内容为cur的后继，并将其存储在next_e中
status NextElem(LNode * L, ElemType cur, ElemType * next_e)
{
	L = L->next;
	if (L == NULL)
		return INFEASTABLE;		//单链表为空
	while (L->next != NULL)
	{
		if (L->data == cur)
		{
			*next_e = L->next->data;
			return OK;
		}
		L = L->next;
	}
	if (L->data == cur)
		return -3;		//cur为单链表的最后一个元素
	else
		return INFEASTABLE;		//cur不在单链表中
}

//在单链表的第i个位置插入元素e
status ListInsert(LNode * L, int i, ElemType e)
{
	int j;
	for (j = 0; j < i - 1; j++)
	{
		if (L->next == NULL)
			return -3;		//i超出可插入的范围
		L = L->next;
	}
	LNode * node = (LNode *)malloc(sizeof(LNode));
	if (node == NULL)
		return OVERFLOW;	//内存不足，无法分配足够的空间来存储待插入的元素
	node->data = e;
	node->next = L->next;
	L->next = node;
	return OK;
}

//删除单链表的第i个元素，并将其保存到e中
status ListDelete(LNode * L, int i, ElemType * e)
{
	int j;
	for (j = 0; j < i - 1; j++)
	{
		if (L->next == NULL)
			return OVERFLOW;	//单链表中不存在第i个元素
		L = L->next;
	}
	if (L->next == NULL)
		return OVERFLOW;
	LNode * node = L->next;
	L->next = node->next;
	*e = node->data;
	free(node);
	return OK;
}

//依次打印单链表的每一个元素
status ListTrabverse(LNode * L)
{
	L = L->next;
	int i = 0;
	while (L != NULL)
	{
		i++;
		printf("%d ", L->data);
		L = L->next;
	}
	putchar('\n');
	return i;
}

//将单链表存储到文件
status LoadToFile(LNode * L, char * filename)
{
	FILE * fp;
	if ((fp = fopen(filename, "w")) == NULL)
		return 1;	//文件打开失败
	L = L->next;
	while (L != NULL)
	{
		fwrite(&L->data, sizeof(ElemType), 1, fp);
		L = L->next;
	}
	fclose(fp);
	return 0;
}

//从单链表中加载数据
status LoadFromFile(LNode * L, char * filename)
{
	int i = 0;
	FILE * fp;
	ElemType add;
	if ((fp = fopen(filename, "r")) == NULL)
		return -1;		//文件打开失败
	if (L->next != NULL)
		return 1;		//单链表当前不为空
	while (1)
	{
		i++;
		if (!fread(&add, sizeof(ElemType), 1, fp))
			break;
		//ListInsert(L, i, add);
		LNode * node = (LNode *)malloc(sizeof(LNode));
		node->data = add;
		node->next = NULL;
		L->next = node;
		L = L->next;
	}
	return 0;
}