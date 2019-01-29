/* coding: GB2312 */
#define _CRT_SECURE_NO_WARNINGS		//在visual studio中操作时使其允许使用scanf等其认为不安全的函数

#include <stdio.h>
#include <stdlib.h>
#include "linear_list.h"

int main(void)
{
	int numList = 0;
	printf("请输入想要处理的单链表的数量：");
	while (scanf("%d", &numList) != 1)
	{
		printf("输入错误，请重新输入想要处理的单链表的数量：");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');

	//定义变量
	LNode * L;
	LNode * LList = (LNode *)malloc(sizeof(LNode) * numList);
	int op = 1, oplist = 0;	//op为操作类型数，oplist为操作单链表数
	int i, res;
	char filename[30];
	ElemType e_6, e_7, cur, e_10, e_11, pre_e, next_e;


	for (i = 0; i < numList; i++)
	{
		L = &LList[i];
		L->data = INT_MIN;
		L->next = NULL;
	}

	while (op)
	{
		system("cls");
		printf("\n\n");
		printf("      基于链式存储结构的线性表的相关操作目录      \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. IntiaList       7. LocateElem\n");
		printf("    	  2. DestroyList     8. PriorElem\n");
		printf("    	  3. ClearList       9. NextElem \n");
		printf("    	  4. ListEmpty     10. ListInsert\n");
		printf("    	  5. ListLength     11. ListDelete\n");
		printf("    	  6. GetElem       12. ListTrabverse\n");
		printf("    	  13. LoadToFile   14. LoadFromFile\n");
		printf("          0. Exit\n");
		printf("-------------------------------------------------\n");
		
		//选择待操作的单链表
		printf("请选择你想要操作的单链表[0~%d]:", numList - 1);
		while (scanf("%d", &oplist) != 1 || (oplist < 0 || oplist > numList - 1))
		{
			printf("输入错误，请重新输入你想要操作的单链表[0~%d]:", numList - 1);
			while (getchar() != '\n');
		}
		while (getchar() != '\n');
		L = &LList[oplist];

		//选择对单链表的操作
		printf("请选择你的操作[0~14]:");
		while (scanf("%d", &op) != 1 || (op < 0 || op > 14))
		{
			printf("输入错误，请重新选择你的操作[0~14]:");
			while (getchar() != '\n');
		}
		while (getchar() != '\n');

		//对单链表进行操作
		switch (op)
		{
		case 1:
			if (L->data == 0)
				printf("单链表已存在!\n");
			else
			{
				IntiaList(L);
				printf("单链表创建成功!\n");
			}
			getchar();
			break;
		case 2:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				DestroyList(L);
				printf("单链表删除成功!\n");
			}
			getchar();
			break;
		case 3:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				ClearList(L);
				printf("单链表清空成功!\n");
			}
			getchar();
			break;
		case 4:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				if (ListEmpty(L) == TRUE)
					printf("单链表为空!\n");
				else
					printf("单链表不为空!\n");
			}
			getchar();
			break;
		case 5:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
				printf("单链表的长度为%d\n", ListLength(L));
			getchar();
			break;
		case 6:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				printf("请输入待查找元素的位置:");
				while (scanf("%d", &i) != 1)
				{
					printf("输入错误，请重新输入待查找元素的位置:");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				if (GetElem(L, i, &e_6) == OVERFLOW)
					printf("查找元素不存在!\n");
				else
					printf("单链表中第%d个元素的值为%d\n", i, e_6);
			}
			getchar();
			break;
		case 7:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				printf("请输入待查找的元素:");
				while (scanf("%d", &e_7) != 1)
				{
					printf("输入错误，请重新输入待查找的元素:");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				res = LocateElem(L, e_7);
				if (res == -1)
					printf("单链表中不存在该元素!\n");
				else
					printf("该元素在单链表中第一次出现的位置为第%d个位置!\n", res);
			}
			getchar();
			break;
		case 8:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				printf("请输入待查找前驱的元素:");
				while (scanf("%d", &cur) != 1)
				{
					printf("输入错误，请重新输入待查找前驱的元素: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				res = PriorElem(L, cur, &pre_e);
				if (res == INFEASTABLE)
					printf("操作失败，%d不在单链表中!\n", cur);
				else if (res == -3)
					printf("操作失败，%d为单链表的第一个元素!\n", cur);
				else
					printf("单链表中元素%d的前驱为%d\n", cur, pre_e);
			}
			getchar();
			break;
		case 9:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				printf("输入待查找后继的元素: ");
				while (scanf("%d", &cur) != 1)
				{
					printf("输入错误，请重新输入待查找后继的元素: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				res = NextElem(L, cur, &next_e);
				if (res == INFEASTABLE)
					printf("操作失败，%d不在单链表中!\n", cur);
				else if (res == -3)
					printf("操作失败，%d为单链表的最后一个元素!\n", cur);
				else
					printf("单链表中元素%d的后继为%d\n", cur, next_e);
			}
			getchar();
			break;
		case 10:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				printf("请输入插入元素的位置: ");
				while (scanf("%d", &i) != 1)
				{
					printf("输入错误，请重新输入插入元素的位置: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				printf("请输入插入元素的值: ");
				while (scanf("%d", &e_10) != 1)
				{
					printf("输入错误，请重新输入插入元素的值: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				res = ListInsert(L, i, e_10);
				if (res == OVERFLOW)
					printf("插入失败，空间不足!\n");
				else if (res == -3)
					printf("第%d个元素超出单链表范围!\n", i);
				else
					printf("插入成功!\n");
			}
			getchar();
			break;
		case 11:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				printf("请输入待删除的元素的位置: ");
				while (scanf("%d", &i) != 1)
				{
					printf("输入错误，请重新输入待删除的元素的位置: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				res = ListDelete(L, i, &e_11);
				if (res == OVERFLOW)
					printf("第%d个元素不在单链表中!\n", i);
				else
					printf("删除成功，删除的元素为%d!\n", e_11);
			}
			getchar();
			break;
		case 12:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				if (!ListTrabverse(L))
					printf("单链表为空表!\n");
			}
			getchar();
			break;
		case 13:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				printf("input file name: ");
				scanf("%s", filename);
				res = LoadToFile(L, filename);
				if (res == 0)
					printf("成功输出到文件!\n");
				else
					printf("文件打开失败!\n");
			}
			getchar(); getchar();
			break;
		case 14:
			if (L->data != 0)
				printf("单链表不存在!\n");
			else
			{
				printf("input file name: ");
				scanf("%s", filename);
				res = LoadFromFile(L, filename);
				if (res == 1)
					printf("单链表中已存在元素，请清空后再从文件载入!\n");
				else if (res == -1)
					printf("文件打开失败!\n");
				else
					printf("载入成功!\n");
			}
			getchar(); getchar();
			break;
		case 0:
			break;
		}
	}
	printf("欢迎再次使用本系统!\n");
	getchar();

	return 0;
}