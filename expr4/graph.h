#define _CRT_SECURE_NO_WARNING

//定义常量
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

//定义数据类型
typedef int status;		//函数返回值类型
typedef struct VertexType {
	int ID;
	int value;
} VertexType;	//顶点
typedef int weight;		//弧的权值
typedef struct vexWeightArc {
	int startID;
	int endID;
	weight arcWeight;
} vexWeightArc;
typedef struct GraphNode {
	int endID;		//该弧指向的顶点的ID
	struct GraphNode * nextArc;		//指向下一条弧的指针
	weight arcWeight;		//该弧的权值
} GraphNode;
typedef struct HeadNode {
	VertexType data;	//顶点信息
	GraphNode * firstArc;	//指向第一条依附该顶点的弧的指针
} HeadNode;
typedef struct Graph {
	HeadNode * Vertices;
	int vexNum;		//顶点数
	int arcNum;		//弧数
} Graph;
typedef struct resultNode {
	status s;
	HeadNode * node;
} resultNode;

#define max(a, b) (a > b) ? a : b

//声明函数
int menu(void);		//打印目录

status CreateGraph(Graph * graph, VertexType * setOfVertex, int numOfVertex, vexWeightArc * infoVertexAndArc, int numOfArc);		//创建图
status DestroyGraph(Graph * graph);												//销毁图
HeadNode * LocateVex(Graph * graph, int vertexID);								//查找顶点
VertexType GetVex(Graph * graph, int vertexID);									//获得顶点值
status PutVex(Graph * graph, int vertexID, int vertexNewValue);					//顶点赋值
resultNode FirstAdjVex(Graph * graph, int vertexID);							//获得第一邻接点
resultNode NextAdjVex(Graph * graph, int vertexID, int vertexFirstAdjID);		//获得下一邻接点
status InsertVex(Graph * graph, VertexType newVertex);							//插入顶点
status DeleteVex(Graph * graph, int vertexID);									//删除结点
status InsertArc(Graph * graph, vexWeightArc newArc);							//插入弧
status DeleteArc(Graph * graph, int startID, int endID);						//删除弧
status DFSTraverse(Graph * graph, HeadNode * vertex, int(*Visit)(Graph * graph, int vertexID), int * outputFlag);//深度优先搜索遍历
status BFSTraverse(Graph * graph, HeadNode * vertex, int(*Visit)(Graph * graph, int vertexID), int * outputFlag);//广度优先搜索遍历
status LoadToFile(Graph * graph, char * filename);								//存储到文件
status LoadFromFile(Graph * graph, char * filename);							//从文件载入
status DestroyArc(GraphNode * arc);
GraphNode * FindNode(GraphNode * arc, int vertexID);
status existNode(Graph * graph, int vertexID);
int visit(Graph * graph, int vertexID);
int maxID(Graph * graph);

int sum;