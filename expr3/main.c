#define _CRT_SECURE_NO_WARNINGS		//在visual studio中操作时使其允许使用scanf等其认为不安全的函数

#include <stdio.h>
#include <stdlib.h>
#include "biTree.h"


int main(void)
{
	int numTree = 0;
	printf("请输入待操作的二叉树的数量: ");
	while (scanf("%d", &numTree) != 1 || (numTree <= 0))
	{
		printf("输入错误，请重新输入待操作的二叉树的数量: ");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');

	TreeHead * tree;
	TreeHead * treeList = (TreeHead *)malloc(sizeof(TreeHead) * numTree);
	int op = 1, optree = 0;		//op为操作类型，oplist为待操作树
	int i, res;
	ElemType * definition;
	int definitionLength;
	TreeNode * rootNode, * node;
	int e, LR;
	char value[20], filename[20];
	statusNode result;
	extern int CreateBiTreeLevel;



	for (i = 0; i < numTree; i++)
	{
		tree = &treeList[i];
		tree->exist = 0;
		tree->child = NULL;
	}
	//将二叉树置为不存在

	while (op)
	{
		menu();		//print the menu

		printf("请输入待操作的二叉树编号[0~%d]: ", numTree - 1);
		while (scanf("%d", &optree) != 1 || (optree < 0 || optree > numTree - 1))
		{
			printf("输入错误，请重新输入待操作的二叉树编号[0~%d]: ", numTree - 1);
			while (getchar() != '\n');
		}
		while (getchar() != '\n');
		tree = &treeList[optree];
		//select the tree

		printf("请选择对二叉树的操作[0~23]: ");
		while (scanf("%d", &op) != 1 || (op < 0 || op > 23))
		{
			printf("输入错误，请重新输入对二叉树的操作[0~23]: ");
			while (getchar() != '\n');
		}
		while (getchar() != '\n');
		//select the operate

		switch (op)
		{
		case 1:
			if (!tree->exist)
			{
				InitBiTree(tree);
				printf("二叉树初始化成功!\n");
			}
			else
				printf("二叉树已存在\n");
			getchar();
			break;
		case 2:
			if (TreeExist(tree))
			{
				DestroyBiTree(tree);
				printf("二叉树销毁成功");
			}
			getchar();
			break;
		case 3:
			if (TreeExist(tree))
			{
				printf("请输入待创建的二叉树的结点数量(包含空): ");
				while (scanf("%d", &definitionLength) != 1 || (definitionLength <= 0))
				{
					printf("输入错误，请重新输入待创建的二叉树的结点数量(包含空): ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				definition = (ElemType *)malloc(sizeof(ElemType) * definitionLength);
				for (i = 1; i <= definitionLength; i++)
				{
					printf("请输入第%d个结点的ID(用-1表示空): ", i);
					while (scanf("%d", &(definition[i - 1].studentID)) != 1 || (definition[i - 1].studentID < -1))
					{
						printf("输入错误，请重新输入第%d个结点的ID(用-1表示空): ", i);
						while (getchar() != '\n');
					}
					while (getchar() != '\n');

					if (definition[i - 1].studentID != -1)
					{
						printf("请输入第%d个结点的name: ", i);
						scanf("%s", definition[i - 1].name);
					}
				}
				CreateBiTreeLevel = 0;
				CreateBiTree(&(tree->child), definition, definitionLength);
				printf("二叉树创建成功!\n");
				free(definition);
			}
			getchar();
			break;
		case 4:
			if (TreeExist(tree))
			{
				ClearBiTree(tree->child);
				tree->child = NULL;
				printf("二叉树清空成功!\n");
			}
			getchar();
			break;
		case 5:
			if (TreeExist(tree))
			{
				if (BiTreeEmpty(tree) == TRUE)
					printf("二叉树为空树!\n");
				else
					printf("二叉树不是空树!\n");
			}
			getchar();
			break;
		case 6:
			if (TreeExist(tree))
				printf("二叉树的深度为%d\n", BiTreeDepth(tree->child));
			getchar();
			break;
		case 7:
			if (TreeExist(tree))
			{
				rootNode = Root(tree);
				if (rootNode == NULL)
					printf("二叉树为空树!\n");
				else
					printf("二叉树的根结点的ID为%d, name为%s\n", rootNode->data.studentID, rootNode->data.name);
			}
			getchar();
			break;
		case 8:
			if (TreeExist(tree))
			{
				printf("请输入待查找的结点的ID: ");
				while ((scanf("%d", &e)) != 1)
				{
					printf("输入错误，请重新输入待查找结点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				node = Value(tree->child, e);
				if (node == NULL)
					printf("二叉树中不存在该结点!\n");
				else
					printf("二叉树中ID为%d的结点的name为%s\n", node->data.studentID, node->data.name);
			}
			getchar();
			break;
		case 9:
			if (TreeExist(tree))
			{
				printf("请输入待赋值的结点的ID: ");
				while ((scanf("%d", &e)) != 1)
				{
					printf("输入错误，请重新输入待赋值的结点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				printf("请输入给该结点赋值的内容: ");
				scanf("%s", value);

				if (Value(tree->child, e) == NULL)
					printf("二叉树中不存在该结点!\n");
				else
				{
					Assign(tree->child, e, value);
					printf("给该结点赋值成功!\n");
				}
			}
			getchar();
			getchar();
			break;
		case 10:
			if (TreeExist(tree))
			{
				printf("请输入待查找双亲的结点的ID: ");
				while ((scanf("%d", &e)) != 1)
				{
					printf("输入错误，请重新输入待查找双亲的结点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				result = Parent(tree->child, e);
				if (result.s == ERROR)
					printf("二叉树中不存在该结点!\n");
				else if (result.s == -1)
					printf("该结点为二叉树的根结点!\n");
				else
					printf("该结点的双亲结点的ID为%d, name为%s\n", result.node->data.studentID, result.node->data.name);
			}
			getchar();
			break;
		case 11:
			if (TreeExist(tree))
			{
				printf("请输入待查找左孩子的结点的ID: ");
				while ((scanf("%d", &e)) != 1)
				{
					printf("输入错误，请重新输入待查找左孩子的结点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				result = LeftChild(tree->child, e);
				if (result.s == ERROR)
					printf("二叉树中ID为%d的结点不存在!\n", e);
				else if (result.node == NULL)
					printf("该结点没有左孩子!\n");
				else
					printf("该结点的左孩子的ID为%d, name为%s\n", result.node->data.studentID, result.node->data.name);
			}
			getchar();
			break;
		case 12:
			if (TreeExist(tree))
			{
				printf("请输入待查找右孩子的结点的ID: ");
				while ((scanf("%d", &e)) != 1)
				{
					printf("输入错误，请重新输入待查找右孩子的结点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				result = RightChild(tree->child, e);
				if (result.s == ERROR)
					printf("二叉树中ID为%d的结点不存在!\n", e);
				else if (result.node == NULL)
					printf("该结点没有右孩子!\n");
				else
					printf("该结点的右孩子的ID为%d, name为%s\n", result.node->data.studentID, result.node->data.name);
			}
			getchar();
			break;
		case 13:
			if (TreeExist(tree))
			{
				printf("请输入待查找左兄弟的结点的ID: ");
				while ((scanf("%d", &e)) != 1)
				{
					printf("输入错误，请重新输入待查找左兄弟的结点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				result = LeftSibling(tree->child, e);
				if (result.s == ERROR)
					printf("二叉树中不存在该结点!\n");
				else if (result.s == -1)
					printf("该结点为二叉树的根结点!\n");
				else if (result.s == -2)
					printf("该结点为其双亲结点的左孩子!\n");
				else if (result.s == -3)
					printf("该结点的左兄弟不存在!\n");
				else
					printf("该结点的左兄弟的ID为%d, name为%s\n", result.node->data.studentID, result.node->data.name);
			}
			getchar();
			break;
		case 14:
			if (TreeExist(tree))
			{
				printf("请输入待查找左兄弟的结点的ID: ");
				while ((scanf("%d", &e)) != 1)
				{
					printf("输入错误，请重新输入待查找左兄弟的结点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				result = RightSibling(tree->child, e);
				if (result.s == ERROR)
					printf("二叉树中不存在该结点!\n");
				else if (result.s == -1)
					printf("该结点为二叉树的根结点!\n");
				else if (result.s == -2)
					printf("该结点为其双亲结点的右孩子!\n");
				else if (result.s == -3)
					printf("该结点的右兄弟不存在!\n");
				else
					printf("该结点的右兄弟的ID为%d, name为%s\n", result.node->data.studentID, result.node->data.name);
			}
			getchar();
			break;
		case 15:
			if (TreeExist(tree))
			{
				printf("请输入待插入子树的结点的ID: ");
				while ((scanf("%d", &e)) != 1)
				{
					printf("输入错误，请重新输入待插入子树的结点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				printf("请输入待插入子树的插入位置(左为0, 右为1): ");
				while (((scanf("%d", &LR)) != 1) || (LR != 0 && LR != 1))
				{
					printf("输入错误，请重新输入待插入子树的插入位置(左为0, 右为1): ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				printf("请输入待插入的二叉树的结点数量(包含空): ");
				while (scanf("%d", &definitionLength) != 1 || (definitionLength <= 0))
				{
					printf("输入错误，请重新输入待插入的二叉树的结点数量(包含空): ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				definition = (ElemType *)malloc(sizeof(ElemType) * definitionLength);
				for (i = 1; i <= definitionLength; i++)
				{
					printf("请输入第%d个结点的ID(用-1表示空): ", i);
					while (scanf("%d", &(definition[i - 1].studentID)) != 1 || (definition[i - 1].studentID < -1))
					{
						printf("输入错误，请重新输入第%d个结点的ID(用-1表示空): ", i);
						while (getchar() != '\n');
					}
					while (getchar() != '\n');

					if (definition[i - 1].studentID != -1)
					{
						printf("请输入第%d个结点的name: ", i);
						scanf("%s", definition[i - 1].name);
					}
				}
				TreeHead * newTree = (TreeHead *)malloc(sizeof(TreeHead));
				InitBiTree(newTree);
				CreateBiTreeLevel = 0;
				CreateBiTree(&(newTree->child), definition, definitionLength);
				
				res = InsertChild(tree, e, LR, newTree);
				if (res == OK)
					printf("插入子树成功!\n");
				else if (res == ERROR)
					printf("待插入子树的右子树存在!\n");
				else
					printf("二叉树中不存在ID为%d的结点!\n", e);
				free(definition);
			}
			getchar(); getchar();
			break;
		case 16:
			if (TreeExist(tree))
			{
				printf("请输入待删除子树的结点的ID: ");
				while ((scanf("%d", &e)) != 1)
				{
					printf("输入错误，请重新输入待删除子树的结点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				printf("请输入待删除子树的删除位置(左为0, 右为1): ");
				while (((scanf("%d", &LR)) != 1) || (LR != 0 && LR != 1))
				{
					printf("输入错误，请重新输入待删除子树的删除位置(左为0, 右为1): ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				res = DeleteChild(tree, e, LR);
				if (res == OK)
					printf("删除子树成功!\n");
				else
					printf("二叉树中不存在ID为%d的结点!\n", e);
			}
			getchar();
			break;
		case 17:
			if (TreeExist(tree))
			{
				if (BiTreeEmpty(tree) == TRUE)
					printf("二叉树为空!\n");
				else
				{
					printf("二叉树的前序遍历结果为: \n");
					PreOrderTraverse(tree->child, Visit);
				}
			}
			getchar();
			break;
		case 18:
			if (TreeExist(tree))
			{
				if (BiTreeEmpty(tree) == TRUE)
					printf("二叉树为空!\n");
				else
				{
					printf("二叉树的中序遍历结果为: \n");
					InOrderTraverse(tree->child, Visit);
				}
			}
			getchar();
			break;
		case 19:
			if (TreeExist(tree))
			{
				if (BiTreeEmpty(tree) == TRUE)
					printf("二叉树为空!\n");
				else
				{
					printf("二叉树的后序遍历结果为: \n");
					PostOrderTraverse(tree->child, Visit);
				}
			}
			getchar();
			break;
		case 20:
			if (TreeExist(tree))
			{
				if (BiTreeEmpty(tree) == TRUE)
					printf("二叉树为空!\n");
				else
				{
					printf("二叉树的按层遍历结果为: \n");
					LevelOrderTraverse(tree->child, Visit);
				}
			}
			getchar();
			break;
		case 21:
			if (TreeExist(tree))
			{
				if (BiTreeEmpty(tree) == TRUE)
					printf("二叉树为空!\n");
				else
				{
					printf("二叉树的树形遍历结果为: \n");
					TreeOrderTraverse(tree->child, Visit, 0);
				}
			}
			getchar();
			break;
		case 22:
			if (TreeExist(tree))
			{
				printf("请输入文件名: ");
				scanf("%s", filename);
				if (LoadToFile(tree->child, filename))
					printf("文件打开失败!\n");
				else
					printf("输出到文件成功!\n");
			}
			getchar(); getchar();
			break;
		case 23:
			if (TreeExist(tree))
			{
				if (!BiTreeEmpty(tree))
					printf("二叉树不为空，请清空后再从文件载入!\n");
				else
				{
					printf("请输入文件名: ");
					scanf("%s", filename);
					if (LoadFromFile(&(tree->child), filename))
						printf("文件打开失败!\n");
					else
						printf("成功载入到二叉树!\n");
				}
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