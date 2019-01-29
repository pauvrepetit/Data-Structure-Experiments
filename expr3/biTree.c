#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biTree.h"

#define max(a, b) (a > b ? a : b)

extern int CreateBiTreeLevel;
extern int TreeLength;
extern int LoadToArrayCount;

int menu(void)
{
	system("cls");
	printf("\n\n");
	printf("       二叉树的相关操作目录\n");
	printf("-----------------------------------------\n");
	printf("\t1.InitBiTree\t\t\t2.DestroyBiTree\n");
	printf("\t3.CreateBiTree\t\t\t4.ClearBiTree\n");
	printf("\t5.BiTreeEmpty\t\t\t6.BiTreeDepth\n");
	printf("\t7.Root\t\t\t\t8.Value\n");
	printf("\t9.Assign\t\t\t10.Parent\n");
	printf("\t11.LeftChild\t\t\t12.RightChild\n");
	printf("\t13.LeftSibling\t\t\t14.RightSibling\n");
	printf("\t15.InsertChild\t\t\t16.DeleteChild\n");
	printf("\t17.PreOrderTraverse\t\t18.InOrderTraverse\n");
	printf("\t19.PostOrderTraverse\t\t20.LevelOrderTraverse\n");
	printf("\t21.TreeOrderTraverse\t\t22.LoadToFile\n");
	printf("\t23.LoadFromFile\t\t\t0.Exit\n");

	return 0;
}

//定义操作二叉树的函数
//初始化二叉树
status InitBiTree(TreeHead * t)
{
	t->exist = 1;
	t->child = NULL;
	return OK;		//初始化成功
}

//销毁二叉树
status DestroyBiTree(TreeHead * t)
{
	ClearBiTree(t->child);
	t->exist = 0;
	t->child = NULL;
	return OK;
}

//创建二叉树
int CreateBiTree(TreeNode ** rootNode, ElemType * definition, int length)
{
	if (definition[CreateBiTreeLevel].studentID == -1)
	{
		if (CreateBiTreeLevel < length - 1)
			CreateBiTreeLevel++;
		else
			definition[CreateBiTreeLevel].studentID = -1;
		return OK;
	}
	*rootNode = (TreeNode *)malloc(sizeof(TreeNode));
	(*rootNode)->data = definition[CreateBiTreeLevel];
	(*rootNode)->lchild = NULL;
	(*rootNode)->rchild = NULL;
	if (CreateBiTreeLevel < length - 1)
		CreateBiTreeLevel++;
	else
		definition[CreateBiTreeLevel].studentID = -1;
	CreateBiTree(&((*rootNode)->lchild), definition, length);
	CreateBiTree(&((*rootNode)->rchild), definition, length);
	return OK;
}

//清空二叉树
status ClearBiTree(TreeNode * rootNode)
{
	if (rootNode == NULL)
		return OK;
	else
	{
		ClearBiTree(rootNode->lchild);
		ClearBiTree(rootNode->rchild);
		free(rootNode);
		rootNode = NULL;
	}
	return OK;
}

//判断空二叉树
status BiTreeEmpty(TreeHead * t)
{
	if (t->child == NULL)
		return TRUE;	//为空
	else
		return FALSE;	//不为空
}

//求二叉树深度
int BiTreeDepth(TreeNode * rootNode)
{
	if (rootNode == NULL)
		return 0;
	return max(BiTreeDepth(rootNode->lchild), BiTreeDepth(rootNode->rchild)) + 1;
}

//获得根结点
TreeNode * Root(TreeHead * t)
{
	return t->child;	//若为NULL，则为空树
}

//获得结点
TreeNode * Value(TreeNode * node, int e)
{
	int i;
	TreeLength = 0;
	TreeArrayLength(node);
	TreeNode ** treeArray = (TreeNode **)malloc(sizeof(TreeNode) * TreeLength);
	LoadToArrayCount = 0;
	LoadToArray(node, treeArray);

	for (i = 0; i < LoadToArrayCount; i++)
	{
		if (treeArray[i]->data.studentID == e)
		{
			
			TreeNode * result = treeArray[i];
			free(treeArray);
			return result;
		}
	}
	return NULL;
}

//结点赋值
status Assign(TreeNode * node, int e, char * value)
{
	TreeNode * assignNode = Value(node, e);
	if (assignNode == NULL)
		return ERROR;
	strcpy(assignNode->data.name, value);
	return OK;
}

//获得双亲结点
//若返回值的s为ERROR，则说明未找到该结点
//若返回值的s为-1，则该结点为根结点
//若返回值的s为OK，则node为双亲结点的指针
statusNode Parent(TreeNode * node, int e)
{
	statusNode result;
	if (node->data.studentID == e)
	{
		result.s = -1;
		result.node = NULL;
		return result;
	}
	LoadToArrayCount = 0;
	TreeLength = 0;
	TreeArrayLength(node);
	TreeNode ** treeArray = (TreeNode **)malloc(sizeof(TreeNode) * TreeLength);
	LoadToArray(node, treeArray);
	for (int i = 0; i < LoadToArrayCount; i++)
	{
		if ((treeArray[i]->data.studentID != -1)
			&& (((treeArray[i]->lchild != NULL) && (treeArray[i]->lchild->data.studentID == e))
			|| ((treeArray[i]->rchild != NULL) && (treeArray[i]->rchild->data.studentID == e))))
		{
			result.s = OK;
			result.node = treeArray[i];
			return result;
		}
	}
	result.s = ERROR;
	result.node = NULL;
	return result;
}

//获得左孩子结点
//若返回值的s为ERROR，则说明结点e不存在
//若返回值的s为OK，则结点e存在，但是左孩子可能为NULL
statusNode LeftChild(TreeNode * node, int e)
{
	statusNode result;
	TreeNode * findChildNode = Value(node, e);
	if (findChildNode == NULL)
	{
		result.s = ERROR;
		result.node = NULL;
		return result;
	}
	result.s = OK;
	result.node = findChildNode->lchild;
	return result;
}

//获得右孩子结点
//若返回值的s为ERROR，则说明结点e不存在
//若返回值的s为OK，则结点e存在，但是右孩子可能为NULL
statusNode RightChild(TreeNode * node, int e)
{
	statusNode result;
	TreeNode * findChildNode = Value(node, e);
	if (findChildNode == NULL)
	{
		result.s = ERROR;
		result.node = NULL;
		return result;
	}
	result.s = OK;
	result.node = findChildNode->rchild;
	return result;
}

//获得左兄弟结点
statusNode LeftSibling(TreeNode * node, int e)
{
	statusNode result;
	statusNode parentNode = Parent(node, e);
	if (parentNode.s == ERROR)
		return parentNode;
	else if (parentNode.s == -1)
		return parentNode;
	else if (parentNode.node->lchild == NULL)
	{
		result.s = -3;
		result.node = NULL;
	}
	else if(parentNode.node->lchild->data.studentID == e)
	{
		result.s = -2;
		result.node = NULL;
	}
	else
	{
		result.s = OK;
		result.node = parentNode.node->lchild;
	}
	return result;
}

//获得右兄弟结点
statusNode RightSibling(TreeNode * node, int e)
{
	statusNode result;
	statusNode parentNode = Parent(node, e);
	if (parentNode.s == ERROR)
		return parentNode;
	else if (parentNode.s == -1)
		return parentNode;
	else if (parentNode.node->rchild == NULL)
	{
		result.s = -3;
		result.node = NULL;
	}
	else if (parentNode.node->rchild->data.studentID == e)
	{
		result.s = -2;
		result.node = NULL;
	}
	else
	{
		result.s = OK;
		result.node = parentNode.node->rchild;
	}
	return result;
}

//插入子树
//返回ERROR表明c的右子树不为空
//返回-1表明ID为e的结点不存在
status InsertChild(TreeHead * t, int e, int LR, TreeHead * c)
{
	TreeNode * child;
	TreeNode * node = Value(t->child, e);
	if (node == NULL)
		return -1;
	if (c->child->rchild != NULL)
		return ERROR;
	if (LR == 0)
	{
		child = node->lchild;
		node->lchild = c->child;
		c->child->rchild = child;
	}
	else
	{
		child = node->rchild;
		node->rchild = c->child;
		c->child->rchild = child;
	}
	//free(c);
	return OK;
}

//删除子树
status DeleteChild(TreeHead * t, int e, int LR)
{
	TreeNode * node = Value(t->child, e);
	if (node == NULL)
		return ERROR;
	if (LR == 0)
	{
		ClearBiTree(node->lchild);
		node->lchild = NULL;
	}
	else
	{
		ClearBiTree(node->rchild);
		node->rchild = NULL;
	}
	return OK;
}

//前序遍历
status PreOrderTraverse(TreeNode * rootNode, int(*Visit)(TreeNode *))
{
	if (rootNode == NULL)
		return OK;
	else
	{
		Visit(rootNode);
		PreOrderTraverse(rootNode->lchild, Visit);
		PreOrderTraverse(rootNode->rchild, Visit);
	}
	return OK;
}

//中序遍历
status InOrderTraverse(TreeNode * rootNode, int(*Visit)(TreeNode *))
{
	if (rootNode == NULL)
		return OK;
	else
	{
		InOrderTraverse(rootNode->lchild, Visit);
		Visit(rootNode);
		InOrderTraverse(rootNode->rchild, Visit);
	}
	return OK;
}

//后序遍历
status PostOrderTraverse(TreeNode * rootNode, int(*Visit)(TreeNode *))
{
	if (rootNode == NULL)
		return OK;
	else
	{
		PostOrderTraverse(rootNode->lchild, Visit);
		PostOrderTraverse(rootNode->rchild, Visit);
		Visit(rootNode);
	}
	return OK;
}

//按层遍历
status LevelOrderTraverse(TreeNode * rootNode, int(*Visit)(TreeNode *))
{
	LoadToArrayCount = 0;
	TreeLength = 0;
	TreeArrayLength(rootNode);
	TreeNode ** treeArray = (TreeNode **)malloc(sizeof(TreeNode) * TreeLength);
	LoadToArray(rootNode, treeArray);
	int depth = BiTreeDepth(rootNode);
	int i, j;
	int * count = (int *)malloc(sizeof(int) * LoadToArrayCount);
	count[0] = 1;
	for (i = 1; i < LoadToArrayCount; i++)
	{
		statusNode parentstatus = Parent(rootNode, treeArray[i]->data.studentID);
		if (parentstatus.s == OK)
		{
			for (j = 0; j < LoadToArrayCount; j++)
				if (treeArray[j]->data.studentID == parentstatus.node->data.studentID)
					count[i] = count[j] + 1;
		}
		else
			count[i] = -1;
	}
	for (i = 1; i <= depth; i++)
	{
		for (j = 0; j < LoadToArrayCount; j++)
		{
			if (count[j] == i)
				Visit(treeArray[j]);
		}
	}
	return OK;
}

//以树形方式直观显示二叉树，OS的资源管理器
status TreeOrderTraverse(TreeNode * rootNode, int(*Visit)(TreeNode *), int n)
{
	if (rootNode == NULL)
		return OK;
	else
	{
		for (int i = 0; i < n; i++)
			putchar('\t');
		Visit(rootNode);
		TreeOrderTraverse(rootNode->lchild, Visit, n + 1);
		TreeOrderTraverse(rootNode->rchild, Visit, n + 1);
	}
	return OK;
}

status LoadToFile(TreeNode * rootNode, char * filename)
{
	FILE * fp;
	if ((fp = fopen(filename, "w")) == NULL)
		return 1;	//文件打开失败

	LoadToArrayCount = 0;
	TreeLength = 0;
	TreeArrayLength(rootNode);
	TreeNode ** treeArray = (TreeNode **)malloc(sizeof(TreeNode) * TreeLength);
	LoadToArray(rootNode, treeArray);
	for (int i = 0; i < LoadToArrayCount; i++)
	{
		fwrite(&(treeArray[i]->data.studentID), sizeof(int), 1, fp);
		fwrite(treeArray[i]->data.name, sizeof(char) * 20, 1, fp);
	}
	fclose(fp);
	return 0;
}

status LoadFromFile(TreeNode ** rootNode, char * filename)
{
	int i = 0;
	FILE * fp;
	if ((fp = fopen(filename, "r")) == NULL)
		return 1;		//文件打开失败
	ElemType * definition = (ElemType *)malloc(sizeof(ElemType) * 20);
	while (1)
	{
		if (!fread(&(definition[i].studentID), sizeof(int), 1, fp))
			break;
		fread(definition[i].name, sizeof(char) * 20, 1, fp);
		if (i++ >= 19)
			definition = (ElemType *)realloc(definition, sizeof(ElemType) * (i + 20));
	}
	CreateBiTreeLevel = 0;
	CreateBiTree(rootNode, definition, i);
	free(definition);
	return 0;
}

//遍历时使用的访问函数
int Visit(TreeNode * node)
{
	printf("%d %s\n", node->data.studentID, node->data.name);
	return 0;
}

int TreeExist(TreeHead * t)
{
	if (!t->exist)
		printf("二叉树不存在!\n");
	return t->exist;
}

int TreeArrayLength(TreeNode * rootNode)
{
	if (rootNode == NULL)
	{
		TreeLength++;
		return TreeLength;
	}
	TreeLength++;
	TreeArrayLength(rootNode->lchild);
	TreeArrayLength(rootNode->rchild);
	return TreeLength;
}


TreeNode ** LoadToArray(TreeNode * rootNode, TreeNode ** result)
{
	if (rootNode == NULL)
	{
		TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
		t->data.studentID = -1;
		result[LoadToArrayCount++] = t;
		return result;
	}
	result[LoadToArrayCount++] = rootNode;
	LoadToArray(rootNode->lchild, result);
	LoadToArray(rootNode->rchild, result);
	return result;
}
