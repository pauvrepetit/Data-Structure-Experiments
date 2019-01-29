#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

//定义常量
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

//定义数据类型
typedef int status;		//函数执行状态
typedef struct ElemType {
	int studentID;
	char name[20];
} ElemType;		//结点数据域

typedef struct TreeNode {
	ElemType data;
	struct TreeNode * lchild;
	struct TreeNode * rchild;
} TreeNode;		//二叉树结点

typedef struct TreeHead {
	int exist;	//0 表示 不存在，1 表示 存在
	struct TreeNode * child;
} TreeHead;		//二叉树头结点

typedef struct statusNode {
	status s;
	TreeNode * node;
}statusNode;	//需要返回结点指针的函数返回值类型

int menu(void);		//打印目录

//声明操作二叉树的函数
status InitBiTree(TreeHead *);					//初始化二叉树
status DestroyBiTree(TreeHead *);				//销毁二叉树
status CreateBiTree(TreeNode **, ElemType *, int);	//创建二叉树
status ClearBiTree(TreeNode *);					//清空二叉树
status BiTreeEmpty(TreeHead *);					//判断空二叉树
int BiTreeDepth(TreeNode *);					//求二叉树深度
TreeNode * Root(TreeHead *);					//获得根结点
TreeNode * Value(TreeNode *, int);				//获得结点
status Assign(TreeNode *, int, char *);			//结点赋值
statusNode Parent(TreeNode *, int);				//获得双亲结点
statusNode LeftChild(TreeNode *, int);			//获得左孩子结点
statusNode RightChild(TreeNode *, int);			//获得右孩子结点
statusNode LeftSibling(TreeNode *, int);		//获得左兄弟结点
statusNode RightSibling(TreeNode *, int);		//获得右兄弟结点
status InsertChild(TreeHead *, int , int, TreeHead *);		//插入子树
status DeleteChild(TreeHead *, int , int);					//删除子树
status PreOrderTraverse(TreeNode *, int(*Visit)(TreeNode *));		//前序遍历
status InOrderTraverse(TreeNode *, int(*Visit)(TreeNode *));		//中序遍历
status PostOrderTraverse(TreeNode *, int(*Visit)(TreeNode *));		//后序遍历
status LevelOrderTraverse(TreeNode *, int(*Visit)(TreeNode *));		//按层遍历
status TreeOrderTraverse(TreeNode *, int(*Visit)(TreeNode *), int);		//以树形方式直观显示二叉树，OS的资源管理器
int Visit(TreeNode *);				//遍历时使用的访问函数
int TreeExist(TreeHead *);			//判断二叉树是否存在
int TreeArrayLength(TreeNode *);	//计算二叉树存储为数组时的长度
TreeNode ** LoadToArray(TreeNode * rootNode, TreeNode ** result);		//将树存储到数组中
status LoadToFile(TreeNode *, char *);		//存储到文件
status LoadFromFile(TreeNode **, char *);	//从文件载入

int CreateBiTreeLevel;
int TreeLength;
int LoadToArrayCount;
