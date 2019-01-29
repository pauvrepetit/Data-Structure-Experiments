#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void)
{
	int numGraph = 0;
	printf("请输入待操作的有向网的数量: ");
	while (scanf("%d", &numGraph) != 1 && (numGraph <= 0))
	{
		printf("输入错误，请重新输入待操作的有向网的数量: ");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');

	Graph * graph;
	Graph * graphList = (Graph *)malloc(sizeof(Graph) * numGraph);

	int op = 1, opGraph = 0, startID;
	int i;
	int numOfVertex, numOfArc, nodeID, nodeValue, nodeNextID;
	VertexType * setOfVertex, vertex;
	vexWeightArc * infoVertexAndArc, newArc;
	HeadNode * node;
	resultNode resNode;
	status res;
	char filename[30];


	for (i = 0; i < numGraph; i++)
	{
		graph = &(graphList[i]);
		graph->arcNum = 0;
		graph->vexNum = 0;
		graph->Vertices = NULL;
	}

	while (op)
	{
		menu();		//print menu

		printf("请输入待操作的有向网的编号[0~%d]: ", numGraph - 1);
		while (scanf("%d", &opGraph) != 1 || (opGraph < 0 || opGraph > numGraph - 1))
		{
			printf("输入错误，请重新输入待操作的有向网的编号[0~%d]: ", numGraph - 1);
			while (getchar() != '\n');
		}
		while (getchar() != '\n');
		graph = &(graphList[opGraph]);
		//select graph

		printf("请选择对有向网的操作[0~15]: ");
		while (scanf("%d", &op) != 1 || (op < 0 || op > 15))
		{
			printf("输入错误，请重新选择对有向网的操作[0~15]: ");
			while (getchar() != '\n');
		}
		while (getchar() != '\n');
		//select operate

		switch (op)
		{
		case 1:
			if (graph->vexNum != 0)
				printf("有向网已存在!\n");
			else
			{
				printf("请输入有向网中顶点的个数: ");
				while (scanf("%d", &numOfVertex) != 1 || (numOfVertex < 1))
				{
					printf("输入错误, 请重新输入有向网的顶点的个数: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				setOfVertex = (VertexType *)malloc(sizeof(VertexType) * numOfVertex);
				for (i = 0; i < numOfVertex; i++)
				{
					printf("请输入第%d个顶点的ID: ", i + 1);
					while (scanf("%d", &(setOfVertex[i].ID)) != 1 || (setOfVertex[i].ID <= 0))
					{
						printf("输入错误, 请重新输入第%d个顶点的ID: ", i + 1);
						while (getchar() != '\n');
					}
					while (getchar() != '\n');

					printf("请输入第%d个顶点的值: ", i + 1);
					while (scanf("%d", &(setOfVertex[i].value)) != 1 || (setOfVertex[i].value <= 0))
					{
						printf("输入错误, 请重新输入第%d个顶点的值: ", i + 1);
						while (getchar() != '\n');
					}
					while (getchar() != '\n');
				}

				printf("请输入有向网中弧的个数: ");
				while (scanf("%d", &numOfArc) != 1 || (numOfArc < 1))
				{
					printf("输入错误, 请重新输入有向网中弧的个数: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');
				infoVertexAndArc = (vexWeightArc *)malloc(sizeof(vexWeightArc) * numOfArc);
				for (i = 0; i < numOfArc; i++)
				{
					printf("请输入第%d条弧的起始顶点ID: ", i + 1);
					while (scanf("%d", &(infoVertexAndArc[i].startID)) != 1 || (infoVertexAndArc[i].startID <= 0))
					{
						printf("输入错误, 请重新输入第%d条弧的起始顶点ID: ", i + 1);
						while (getchar() != '\n');
					}
					while (getchar() != '\n');

					printf("请输入第%d条弧的终止顶点ID: ", i + 1);
					while (scanf("%d", &(infoVertexAndArc[i].endID)) != 1 || (infoVertexAndArc[i].endID <= 0))
					{
						printf("输入错误, 请重新输入第%d条弧的终止顶点ID: ", i + 1);
						while (getchar() != '\n');
					}
					while (getchar() != '\n');

					printf("请输入第%d条弧的权重: ", i + 1);
					while (scanf("%d", &(infoVertexAndArc[i].arcWeight)) != 1 || (infoVertexAndArc[i].arcWeight <= 0))
					{
						printf("输入错误, 请重新输入第%d条弧的权重: ", i + 1);
						while (getchar() != '\n');
					}
					while (getchar() != '\n');
				}
				CreateGraph(graph, setOfVertex, numOfVertex, infoVertexAndArc, numOfArc);
				printf("有向网创建成功!\n");
			}
			getchar();
			break;
		case 2:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				DestroyGraph(graph);
				printf("有向网销毁成功!\n");
			}
			getchar();
			break;
		case 3:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入待查找的顶点的ID: ");
				while (scanf("%d", &nodeID) != 1 || (nodeID <= 0))
				{
					printf("输入错误, 请重新输入待查找的顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				node = LocateVex(graph, nodeID);
				if (node == NULL)
					printf("该顶点不存在!\n");
				else
				{
					printf("该顶点的ID为%d, 值为%d!\n", node->data.ID, node->data.value);
				}
			}
			getchar();
			break;
		case 4:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入待获得顶点值的顶点的ID: ");
				while (scanf("%d", &nodeID) != 1 || (nodeID <= 0))
				{
					printf("输入错误, 请重新输入待获得顶点值的顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				vertex = GetVex(graph, nodeID);
				if (vertex.ID == -1)
					printf("该顶点不存在!\n");
				else
					printf("该顶点的值为%d!\n", vertex.value);
			}
			getchar();
			break;
		case 5:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入待赋值的顶点的ID: ");
				while (scanf("%d", &nodeID) != 1 || (nodeID <= 0))
				{
					printf("输入错误, 请重新输入待赋值的顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				printf("请输入待赋的值: ");
				while (scanf("%d", &nodeValue) != 1 || (nodeValue <= 0))
				{
					printf("输入错误, 请重新输入待赋的值: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				if (PutVex(graph, nodeID, nodeValue) == ERROR)
					printf("该顶点不存在!\n");
				else
					printf("赋值成功!\n");
			}
			getchar();
			break;
		case 6:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入待查找第一邻接点的顶点的ID: ");
				while (scanf("%d", &nodeID) != 1 || (nodeID <= 0))
				{
					printf("输入错误, 请重新输入待查找第一邻接点的顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');
				resNode = FirstAdjVex(graph, nodeID);
				if (resNode.s == OVERFLOW)
					printf("该顶点不存在!\n");
				else if (resNode.s == ERROR)
					printf("该顶点没有邻接点!\n");
				else
					printf("该顶点的第一邻接点的ID为%d, 值为%d!\n", resNode.node->data.ID, resNode.node->data.value);
			}
			getchar();
			break;
		case 7:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入待查找下一邻接点的顶点的ID: ");
				while (scanf("%d", &nodeID) != 1 || (nodeID <= 0))
				{
					printf("输入错误, 请重新输入待查找下一邻接点的顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				printf("请输入待查找下一邻接点的邻接点的ID: ");
				while (scanf("%d", &nodeNextID) != 1 || (nodeNextID <= 0))
				{
					printf("输入错误, 请重新输入待查找下一邻接点的邻接点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				resNode = NextAdjVex(graph, nodeID, nodeNextID);

				if (resNode.s == OVERFLOW)
					printf("该顶点不存在!\n");
				else if (resNode.s == ERROR)
					printf("该顶点没有邻接点!\n");
				else if (resNode.s == -3)
					printf("该邻接点不是该顶点的邻接点!\n");
				else if (resNode.s == -4)
					printf("该邻接点为该顶点的最后一个邻接点!\n");
				else
					printf("该顶点的下一邻接点的ID为%d, 值为%d!\n", resNode.node->data.ID, resNode.node->data.value);
			}
			getchar();
			break;
		case 8:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入待插入的顶点的ID: ");
				while (scanf("%d", &(vertex.ID)) != 1 || (vertex.ID <= 0))
				{
					printf("输入错误, 请重新输入待插入的顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				printf("请输入待插入的顶点的值: ");
				while (scanf("%d", &(vertex.value)) != 1 || (vertex.value <= 0))
				{
					printf("输入错误, 请重新输入待插入的顶点的值: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				res = InsertVex(graph, vertex);
				if (res == OVERFLOW)
					printf("空间不足, 插入失败!\n");
				else if (res == ERROR)
					printf("该顶点已存在!\n");
				else
					printf("插入成功!\n");
			}
			getchar();
			break;
		case 9:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入待删除的顶点的ID: ");
				while (scanf("%d", &nodeID) != 1 || (nodeID <= 0))
				{
					printf("输入错误, 请重新输入待删除的顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				if (DeleteVex(graph, nodeID) == ERROR)
					printf("该顶点不存在!\n");
				else
					printf("删除成功!\n");
			}
			getchar();
			break;
		case 10:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入待插入的弧的起始顶点的ID: ");
				while (scanf("%d", &(newArc.startID)) != 1 || (newArc.startID <= 0))
				{
					printf("输入错误, 请重新输入待插入的弧的起始顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				printf("请输入待插入的弧的终止顶点的ID: ");
				while (scanf("%d", &(newArc.endID)) != 1 || (newArc.endID <= 0))
				{
					printf("输入错误, 请重新输入待插入的弧的终止顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				printf("请输入待插入的弧的权重: ");
				while (scanf("%d", &(newArc.arcWeight)) != 1 || (newArc.arcWeight <= 0))
				{
					printf("输入错误, 请重新输入待插入的弧的权重: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				res = InsertArc(graph, newArc);
				if (res == ERROR)
					printf("起始顶点不存在!\n");
				else if (res == OVERFLOW)
					printf("终止顶点不存在!\n");
				else
					printf("插入成功!\n");
			}
			getchar();
			break;
		case 11:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入待删除的弧的起始顶点的ID: ");
				while (scanf("%d", &(newArc.startID)) != 1 || (newArc.startID <= 0))
				{
					printf("输入错误, 请重新输入待删除的弧的起始顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				printf("请输入待删除的弧的终止顶点的ID: ");
				while (scanf("%d", &(newArc.endID)) != 1 || (newArc.endID <= 0))
				{
					printf("输入错误, 请重新输入待删除的弧的终止顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');
				
				res = DeleteArc(graph, newArc.startID, newArc.endID);
				if (res == 2)
					printf("起始顶点不存在!\n");
				else if (res == 1)
					printf("终止顶点不存在!\n");
				else if (res == 3)
					printf("该弧不存在!\n");
				else
					printf("删除成功!\n");
			}
			getchar();
			break;
		case 12:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入深度优先遍历的起始顶点的ID: ");
				while (scanf("%d", &(startID)) != 1 || (startID <= 0))
				{
					printf("输入错误, 请重新输入深度优先遍历的起始顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				int * outputFlag = (int *)malloc(sizeof(int) * (maxID(graph) + 1));
				for (i = 0; i <= maxID(graph); i++)
					outputFlag[i] = 0;
				sum = 0;
				if (LocateVex(graph, startID) == NULL)
					printf("该顶点不存在!\n");
				else
				{
					printf("深度优先遍历结果如下: \n");
					DFSTraverse(graph, LocateVex(graph, startID), visit, outputFlag);
				}
				free(outputFlag);
			}
			getchar();
			break;
		case 13:
			if(graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入广度优先遍历的起始顶点的ID: ");
				while (scanf("%d", &(startID)) != 1 || (startID <= 0))
				{
					printf("输入错误, 请重新输入广度优先遍历的起始顶点的ID: ");
					while (getchar() != '\n');
				}
				while (getchar() != '\n');

				int * outputFlag = (int *)malloc(sizeof(int) * (maxID(graph) + 1));
				for (i = 0; i <= maxID(graph); i++)
					outputFlag[i] = 0;
				sum = 0;
				if (LocateVex(graph, startID) == NULL)
					printf("该顶点不存在!\n");
				else
				{
					printf("广度优先遍历结果如下: \n");
					BFSTraverse(graph, LocateVex(graph, startID), visit, outputFlag);
				}
				free(outputFlag);
			}
			getchar();
			break;
		case 14:
			if (graph->vexNum == 0)
				printf("有向网不存在!\n");
			else
			{
				printf("请输入存储的文件名: ");
				scanf("%s", filename);
				if (LoadToFile(graph, filename) == ERROR)
					printf("文件打开失败!\n");
				else
					printf("成功输出到文件!\n");
			}
			getchar(); getchar();
			break;
		case 15:
			if (graph->vexNum != 0)
				printf("有向网中已存在内容, 请清空后再从文件载入!\n");
			else
			{
				printf("请输入读取的文件名: ");
				scanf("%s", filename);
				if (LoadFromFile(graph, filename) == ERROR)
					printf("文件打开失败!\n");
				else
					printf("成功载入有向网!\n");
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