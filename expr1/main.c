/* coding: GB-2312 */
#define _CRT_SECURE_NO_WARNINGS		//在visual studio中操作时使其允许使用scanf等其认为不安全的函数

/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "linear_list.h"

int main(void) {
	int numList = 0;
	printf("请输入想要处理的线性表的数量: ");
	while (scanf("%d", &numList) != 1)
	{
		printf("输入错误，请重新输入想要处理的线性表数量: ");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');

	SqList * L;
	SqList * LList = (SqList *)malloc(sizeof(SqList) * numList);
	int op = 1, oplist = 0;
	int i;
	char filename[30];
	status res;
	ElemType e_6, e_7, cur, e_10, e_11, pre_e, next_e;

	for (i = 0; i < numList; i++)
	{
		L = &LList[i];
		L->elem = NULL;
		L->length = -1;
		L->listsize = -1;
	}
	while (op) {
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
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

		printf("请选择你想要操作的线性表[0~%d]: ", numList - 1);
		while (scanf("%d", &oplist) != 1 || (oplist < 0 || oplist > numList - 1))
		{
			printf("输入错误，请重新输入你想要操作的线性表[0~%d]: ", numList - 1);	//确定输入的正确性
			while (getchar() != '\n');
		}
		while (getchar() != '\n');	//读取输入的多余的元素
		L = &LList[oplist];

		printf("    请选择你的操作[0~14]:");
		while (scanf("%d", &op) != 1 || (op < 0 || op > 14))
		{
			printf("输入错误，请重新选择你的操作[0~14]: ");	//确定输入的正确性
			while (getchar() != '\n');
		}
		while (getchar() != '\n');	//读取输入的多余的元素

		switch (op) {
		case 1:
			//printf("\n----IntiaList功能待实现！\n");
			if (L->elem)	//线性表不存在的情况
				printf("线性表已存在!\n");
			else
			{
				if (IntiaList(L) == OK)
					printf("线性表创建成功！\n");
				else
					printf("线性表创建失败！\n");
			}
			getchar();
			break;
		case 2:
			//printf("\n----DestroyList功能待实现！\n");
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				DestroyList(L);
				printf("线性表删除成功!\n");
			}
			getchar();
			break;
		case 3:
			//printf("\n----ClearList功能待实现！\n");
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				ClearList(L);
				printf("线性表清空成功!\n");
			}
			getchar();
			break;
		case 4:
			//printf("\n----ListEmpty功能待实现！\n");
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				res = ListEmpty(*L);
				if (res == TRUE)
					printf("线性表为空!\n");
				else
					printf("线性表不为空!\n");
			}
			getchar();
			break;
		case 5:
			//printf("\n----ListLength功能待实现！\n");
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
				printf("线性表的长度为%d\n", ListLength(*L));
			getchar();
			break;
		case 6:
			//printf("\n----GetElem功能待实现！\n");
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				printf("请输入待查找的数据元素的位置: ");
				while (scanf("%d", &i) != 1)
				{
					printf("输入错误，请重新输入待查找的数据元素的位置: ");	//确认输入的正确性
					while (getchar() != '\n');
				}
				while (getchar() != '\n');	//读取输入的多余的元素

				res = GetElem(*L, i, &e_6);
				if (res == OVERFLOW)
					printf("溢出，查找元素不存在!\n");
				else
					printf("线性表第%d个数据元素的值为%d!\n", i, e_6);		//第二个%d处的输出取决于ElemType的类型
			}
			getchar();
			break;
		case 7:
			//printf("\n----LocateElem功能待实现！\n");
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				printf("请输入待查找的元素: ");
				while (scanf("%d", &e_7) != 1)		//此处%d与ElemType有关
				{
					printf("输入错误，请重新输入待查找的元素: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');	//读取输入的多余的元素

				res = LocateElem(*L, e_7);
				if (res == -1)
					printf("线性表中不存在该元素!\n");
				else
					printf("该元素在线性表中第一次出现的位置为第%d个位置!\n", res);
			}
			getchar();
			break;
		case 8:
			//printf("\n----PriorElem功能待实现！\n");
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				printf("输入待查找前驱的元素: ");
				while (scanf("%d", &cur) != 1)
				{
					printf("输入错误，请重新输入待查找前驱的元素: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');	//读取输入的多余的元素

				res = PriorElem(*L, cur, &pre_e);
				if (res == INFEASTABLE)
					printf("操作失败，%d不在线性表中!\n", cur);
				else if (res == -3)
					printf("操作失败，%d为线性表的第一个元素!\n", cur);
				else
					printf("线性表中元素%d的前驱为%d!\n", cur, pre_e);
			}
			getchar();
			break;
		case 9:
			//printf("\n----NextElem功能待实现！\n");
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				printf("输入待查找后继的元素: ");
				while (scanf("%d", &cur) != 1)
				{
					printf("输入错误，请重新输入待查找后继的元素: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');	//读取输入的多余的元素

				res = NextElem(*L, cur, &next_e);
				if (res == INFEASTABLE)
					printf("操作失败，%d不在线性表中!\n", cur);
				else if (res == -3)
					printf("操作失败，%d为线性表的最后一个元素!\n", cur);
				else
					printf("线性表中元素%d的后继为%d!\n", cur, next_e);
			}
			getchar();
			break;
		case 10:
			//printf("\n----ListInsert功能待实现！\n");
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				printf("请输入插入元素的位置: ");
				while (scanf("%d", &i) != 1)
				{
					printf("输入错误，请重新输入插入元素的位置: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');	//读取输入的多余的元素
				printf("请输入插入元素的值: ");
				while (scanf("%d", &e_10) != 1)
				{
					printf("输入错误，请重新输入插入元素的值: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');	//读取输入的多余的元素

				res = ListInsert(L, i, e_10);
				if (res == OVERFLOW)
					printf("第%d个位置超出线性表可插入范围\n", i);
				else if (res == -3)
					printf("线性表已满，不能够插入元素\n");
				else
					printf("插入成功!\n");
			}
			getchar();
			break;
		case 11:
			//printf("\n----ListDelete功能待实现！\n");
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				printf("请输入待删除的元素的位置: ");
				while (scanf("%d", &i) != 1)
				{
					printf("输入错误，请重新输入待删除的元素的位置: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');	//读取输入的多余的元素

				res = ListDelete(L, i, &e_11);
				if (res == OVERFLOW)
					printf("溢出!\n");
				else
					printf("删除成功!删除的元素为%d\n", e_11);
			}
			getchar();
			break;
		case 12:
			//printf("\n----ListTrabverse功能待实现！\n");
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				res = ListTrabverse(*L);
				if (!res)
					printf("线性表是空表!\n");
			}
			getchar();
			break;
		case 13:
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				printf("input file name: ");
				scanf("%s", filename);
				res = LoadToFile(*L, filename);
				if (res == 0)
					printf("成功输出到文件!\n");
				else
					printf("文件打开失败!\n");
			}
			getchar(); getchar();
			break;
		case 14:
			if (!L->elem)	//线性表不存在的情况
				printf("线性表不存在!\n");
			else
			{
				printf("input file name: ");
				scanf("%s", filename);
				res = LoadFromFile(L, filename);
				if (res == 1)
					printf("线性表中已存在元素，请清空后再从文件载入!\n");
				else if (res == -1)
					printf("文件打开失败!\n");
				else
					printf("载入成功!\n");
			}
			getchar(); getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统!\n");
	getchar();
	return 0;
}//end of main()
