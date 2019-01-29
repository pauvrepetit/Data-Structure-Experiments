#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int menu(void)
{
	system("cls");
	printf("\n\n");
	printf("\t\t有向网的相关操作目录\n");
	printf("\t1.CreateGraph\t\t\t2.DestroyGraph\n");
	printf("\t3.LocateVex\t\t\t4.GetVex\n");
	printf("\t5.PutVex\t\t\t6.FirstAdjVex\n");
	printf("\t7.NextAdjVex\t\t\t8.InsertVex\n");
	printf("\t9.DeleteVex\t\t\t10.InsertArc\n");
	printf("\t11.DeleteArc\t\t\t12.DFSTraverse\n");
	printf("\t13.BFSTraverse\t\t\t14.LoadToFile\n");
	printf("\t15.LoadFromFile\t\t\t0.Exit\n");
	return 0;
}

status CreateGraph(Graph * graph, VertexType * setOfVertex, int numOfVertex, vexWeightArc * infoVertexAndArc, int numOfArc)
{
	int i, j, flag = 0;
	GraphNode * temp;
	graph->vexNum = numOfVertex;
	graph->arcNum = numOfArc;
	graph->Vertices = (HeadNode *)malloc(sizeof(HeadNode) * numOfVertex);
	if (graph->Vertices == NULL)
		return OVERFLOW;	//空间不足
	for (i = 0; i < numOfVertex; i++)
	{
		graph->Vertices[i].data.ID = setOfVertex[i].ID;
		graph->Vertices[i].data.value = setOfVertex[i].value;
		graph->Vertices[i].firstArc = NULL;
	}
	for (i = 0; i < numOfArc; i++)
	{
		flag = 0;
		for (j = 0; j < numOfVertex; j++)
		{
			if (graph->Vertices[j].data.ID == infoVertexAndArc[i].startID)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			continue;
		temp = graph->Vertices[j].firstArc;
		graph->Vertices[j].firstArc = (GraphNode *)malloc(sizeof(GraphNode));
		graph->Vertices[j].firstArc->endID = infoVertexAndArc[i].endID;
		graph->Vertices[j].firstArc->nextArc = temp;
		graph->Vertices[j].firstArc->arcWeight = infoVertexAndArc[i].arcWeight;
	}
	return OK;
}

status DestroyGraph(Graph * graph)
{
	int numOfVertex = graph->vexNum;
	int i;
	for (i = 0; i < numOfVertex; i++)
	{
		DestroyArc(graph->Vertices[i].firstArc);
		graph->Vertices[i].firstArc = NULL;
	}
	free(graph->Vertices);
	graph->arcNum = 0;
	graph->vexNum = 0;
	graph->Vertices = NULL;
	return OK;
}

HeadNode * LocateVex(Graph * graph, int vertexID)
{
	int numOfVertex = graph->vexNum;
	int i;
	for (i = 0; i < numOfVertex; i++)
	{
		if (graph->Vertices[i].data.ID == vertexID)
			return &(graph->Vertices[i]);
	}
	return NULL;
}

VertexType GetVex(Graph * graph, int vertexID)
{
	int numOfVertex = graph->vexNum;
	int i;
	for (i = 0; i < numOfVertex; i++)
	{
		if (graph->Vertices[i].data.ID == vertexID)
			return graph->Vertices[i].data;
	}
	VertexType error;
	error.ID = -1;
	error.value = -1;
	return error;
}

status PutVex(Graph * graph, int vertexID, int vertexNewValue)
{
	HeadNode * vertexLocation = LocateVex(graph, vertexID);
	if (vertexLocation == NULL)
		return ERROR;		//结点不存在
	vertexLocation->data.value = vertexNewValue;
	return OK;
}

resultNode FirstAdjVex(Graph * graph, int vertexID)
{
	resultNode result;
	HeadNode * vertexLocation = LocateVex(graph, vertexID);
	if (vertexLocation == NULL)
	{
		result.s = OVERFLOW;	//顶点不存在
		result.node = NULL;
	}
	else if (vertexLocation->firstArc == NULL)
	{
		result.s = ERROR;	//顶点没有邻接点
		result.node = NULL;
	}
	else
	{
		result.s = OK;
		result.node = LocateVex(graph, vertexLocation->firstArc->endID);
	}
	return result;
}

resultNode NextAdjVex(Graph * graph, int vertexID, int vertexFirstAdjID)
{
	resultNode result;
	GraphNode * findNode;
	HeadNode * vertexLocation = LocateVex(graph, vertexID);
	if (vertexLocation == NULL)
	{
		result.s = OVERFLOW;	//顶点不存在
		result.node = NULL;
	}
	else if (vertexLocation->firstArc == NULL)
	{
		result.s = ERROR;	//顶点没有邻接点
		result.node = NULL;
	}
	else
	{
		findNode = FindNode(vertexLocation->firstArc, vertexFirstAdjID);
		if (findNode == NULL)
		{
			result.s = -3;		//vertexFirstAdjID不是邻接点
			result.node = NULL;
		}
		else if (findNode->nextArc == NULL)
		{
			result.s = -4;		//vertexFirstAdjID是最后一个邻接点
			result.node = NULL;
		}
		else
		{
			result.s = OK;
			result.node = LocateVex(graph, findNode->nextArc->endID);
		}
	}
	return result;
}

status InsertVex(Graph * graph, VertexType newVertex)
{
	if (existNode(graph, newVertex.ID) == TRUE)
		return ERROR;
	int i;
	HeadNode * newVertices = (HeadNode *)malloc(sizeof(HeadNode) * (graph->vexNum + 1));
	HeadNode * temp;
	if (newVertices == NULL)
		return OVERFLOW;
	graph->vexNum++;
	for (i = 0; i < graph->vexNum - 1; i++)
	{
		newVertices[i].data.ID = graph->Vertices[i].data.ID;
		newVertices[i].data.value = graph->Vertices[i].data.value;
		newVertices[i].firstArc = graph->Vertices[i].firstArc;
	}
	temp = graph->Vertices;
	free(temp);
	graph->Vertices = newVertices;
	graph->Vertices[graph->vexNum - 1].data.ID = newVertex.ID;
	graph->Vertices[graph->vexNum - 1].data.value = newVertex.value;
	graph->Vertices[graph->vexNum - 1].firstArc = NULL;
	return OK;
}

status DeleteVex(Graph * graph, int vertexID)
{
	if (existNode(graph, vertexID) == FALSE)
		return ERROR;
	int i = 0;
	int locate = 0;
	GraphNode * node1 = graph->Vertices[i].firstArc;
	GraphNode * node2;
	for (i = 0; i < graph->vexNum; i++)
	{
		node1 = graph->Vertices[i].firstArc;
		if (graph->Vertices[i].data.ID == vertexID)
		{
			locate = i;
			if (node1 != NULL)
			{
				node2 = node1;
				node1 = node2->nextArc;

				while (node1 != NULL)
				{
					node2->nextArc = node1->nextArc;
					free(node1);
					graph->arcNum--;
					node1 = node2->nextArc;
				}
				free(node2);
				graph->arcNum--;
				graph->Vertices[i].firstArc = NULL;
			}
		}
		else
		{
			if (node1 != NULL)
			{
				node2 = node1;
				node1 = node2->nextArc;

				while (1)
				{
					if (node1 == NULL)
						break;
					if (node1->endID == vertexID)
					{
						node2->nextArc = node1->nextArc;
						free(node1);
						graph->arcNum--;
						node1 = node2->nextArc;
						break;
					}
					node2 = node1;
					node1 = node2->nextArc;
				}
			}
		}
	}
	graph->vexNum--;
	for (i = locate; i < graph->vexNum; i++)
	{
		graph->Vertices[i].data.ID = graph->Vertices[i + 1].data.ID;
		graph->Vertices[i].data.value = graph->Vertices[i + 1].data.value;
		graph->Vertices[i].firstArc = graph->Vertices[i + 1].firstArc;
	}
	return OK;
}

status InsertArc(Graph * graph, vexWeightArc newArc)
{
	if (existNode(graph, newArc.endID) == FALSE)
		return OVERFLOW;		//终止结点不存在
	int i = 0;
	for (i = 0; i < graph->vexNum; i++)
	{
		if (graph->Vertices[i].data.ID == newArc.startID)
		{
			GraphNode * node = graph->Vertices[i].firstArc;
			GraphNode * addNode = (GraphNode *)malloc(sizeof(GraphNode));
			addNode->endID = newArc.endID;
			addNode->arcWeight = newArc.arcWeight;
			addNode->nextArc = node;
			graph->Vertices[i].firstArc = addNode;
			graph->arcNum++;
			return OK;
		}
	}
	return ERROR;		//起始结点不存在
}

status DeleteArc(Graph * graph, int startID, int endID)
{
	if (existNode(graph, endID) == FALSE)
		return 1;		//终止结点不存在
	int i = 0;
	for (i = 0; i < graph->vexNum; i++)
	{
		if (graph->Vertices[i].data.ID == startID)
		{
			GraphNode * tempNode;
			GraphNode * node = graph->Vertices[i].firstArc;
			if (node->endID == endID)
			{
				tempNode = node->nextArc;
				free(node);
				graph->Vertices[i].firstArc = tempNode;
				graph->arcNum--;
				return 0;		//success
			}
			else
			{
				tempNode = node;
				if (node != NULL)
					node = tempNode->nextArc;
				while (1)
				{
					if (node == NULL)
						break;
					if (node->endID == endID)
					{
						tempNode->nextArc = node->nextArc;
						free(node);
						node = tempNode->nextArc;
						graph->arcNum--;
						return 0;		//success
					}
					tempNode = node;
					node = node->nextArc;
				}
			}
			return 3;		//该弧不存在
		}
	}
	return 2;		//起始结点不存在
}

status DFSTraverse(Graph * graph, HeadNode * vertex, int(*Visit)(Graph * graph, int vertexID), int * outputFlag)
{
	if (sum == graph->vexNum)
		return OK;
	if (outputFlag[vertex->data.ID] == 0)
	{
		Visit(graph, vertex->data.ID);
		outputFlag[vertex->data.ID] = 1;
		sum++;
	}
	else
		return OK;
	GraphNode * node = vertex->firstArc;
	while (1)
	{
		if (node == NULL)
			break;
		DFSTraverse(graph, LocateVex(graph, node->endID), Visit, outputFlag);
		node = node->nextArc;
	}
	return OK;
}

status BFSTraverse(Graph * graph, HeadNode * vertex, int(*Visit)(Graph *graph, int vertexID), int * outputFlag)
{
	int i, loc = 0, change;
	VertexType * BFSArray = (VertexType *)malloc(sizeof(VertexType) * graph->vexNum);
	GraphNode * node;
	int begin, end;
	begin = 0;
	BFSArray[loc].ID = vertex->data.ID;
	BFSArray[loc].value = vertex->data.value;
	outputFlag[vertex->data.ID] = 1;
	loc++;
	end = loc;
	while (end != graph->vexNum)
	{
		change = loc;
		for (i = begin; i < end; i++)
		{
			node = LocateVex(graph, BFSArray[i].ID)->firstArc;
			while (node != NULL)
			{
				if (outputFlag[node->endID] == 0)
				{
					outputFlag[node->endID] = 1;
					BFSArray[loc].ID = node->endID;
					BFSArray[loc].value = LocateVex(graph, node->endID)->data.value;
					loc++;
				}
				node = node->nextArc;
			}
		}
		begin = end;
		end = loc;
		if (change == loc)
			break;
	}
	for (i = 0; i < end; i++)
		Visit(graph, BFSArray[i].ID);
	return OK;
}

status LoadToFile(Graph * graph, char * filename)
{
	int i;
	int number = -1;
	GraphNode * node;
	FILE * fp = fopen(filename, "w");
	if (fp == NULL)
		return ERROR;		//file open error

	fwrite(&(graph->vexNum), sizeof(int), 1, fp);
	fwrite(&(graph->arcNum), sizeof(int), 1, fp);

	for (i = 0; i < graph->vexNum; i++)
		fwrite(&(graph->Vertices[i].data), sizeof(VertexType), 1, fp);

	for (i = 0; i < graph->vexNum; i++)
	{
		node = graph->Vertices[i].firstArc;
		while (node != NULL)
		{
			fwrite(&(node->endID), sizeof(int), 1, fp);
			fwrite(&(node->arcWeight), sizeof(int), 1, fp);
			node = node->nextArc;
		}
		fwrite(&number, sizeof(int), 1, fp);
		fwrite(&number, sizeof(int), 1, fp);
	}
	fclose(fp);
	return OK;
}

status LoadFromFile(Graph * graph, char * filename)
{
	int i;
	GraphNode * node;
	GraphNode * tempnode;
	FILE * fp = fopen(filename, "r");
	if (fp == NULL)
		return ERROR;		//file open error

	fread(&(graph->vexNum), sizeof(int), 1, fp);
	fread(&(graph->arcNum), sizeof(int), 1, fp);

	graph->Vertices = (HeadNode *)malloc(sizeof(HeadNode) * graph->vexNum);
	for (i = 0; i < graph->vexNum; i++)
		fread(&(graph->Vertices[i].data), sizeof(VertexType), 1, fp);

	for (i = 0; i < graph->vexNum; i++)
	{
		tempnode = (GraphNode *)malloc(sizeof(GraphNode));
		fread(&(tempnode->endID), sizeof(int), 1, fp);
		fread(&(tempnode->arcWeight), sizeof(int), 1, fp);
		if (tempnode->endID == -1)
			graph->Vertices[i].firstArc = NULL;
		else
		{
			graph->Vertices[i].firstArc = tempnode;
			node = tempnode;
			while (1)
			{
				tempnode = (GraphNode *)malloc(sizeof(GraphNode));
				fread(&(tempnode->endID), sizeof(int), 1, fp);
				fread(&(tempnode->arcWeight), sizeof(int), 1, fp);
				if (tempnode->endID == -1)
				{
					node->nextArc = NULL;
					break;
				}
				node->nextArc = tempnode;
				node = node->nextArc;
			}
		}
	}
	fclose(fp);
	return OK;
}

status DestroyArc(GraphNode * arc)
{
	GraphNode * arc2;
	if (arc == NULL)
		return OK;
	arc2 = arc->nextArc;
	while (arc2 != NULL)
	{
		free(arc);
		arc = arc2;
		arc2 = arc2->nextArc;
	}
	free(arc);
	return OK;
}

GraphNode * FindNode(GraphNode * arc, int vertexID)
{
	while (1)
	{
		if (arc == NULL)
			break;
		if (arc->endID == vertexID)
			return arc;
		arc = arc->nextArc;
	}
	return NULL;
}

status existNode(Graph * graph, int vertexID)
{
	int i;
	for (i = 0; i < graph->vexNum; i++)
	{
		if (graph->Vertices[i].data.ID == vertexID)
			return TRUE;		//exist
	}
	return FALSE;		//not exist
}

int visit(Graph * graph, int vertexID)
{
	int i;
	for (i = 0; i < graph->vexNum; i++)
	{
		if (graph->Vertices[i].data.ID == vertexID)
		{
			printf("%d\t%d\n", graph->Vertices[i].data.ID, graph->Vertices[i].data.value);
		}
	}
	return 0;
}

int maxID(Graph * graph)
{
	int maxid = 0;
	int i;
	for (i = 0; i < graph->vexNum; i++)
		maxid = max(graph->Vertices[i].data.ID, maxid);
	return maxid;
}
