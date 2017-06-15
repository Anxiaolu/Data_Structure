//第7章
#include <stdio.h>			
#include <stdlib.h>
#define Maxsize 10						//定义图中最多顶点个数
typedef char Datatype;						//定义图中顶点数据类型,这里假设为char型
int visited[Maxsize] = {0};					//定义已经遍历的顶点集合
typedef struct 
{
	Datatype vertex[Maxsize];				//存放顶点的一维数组
	int edge[Maxsize] [Maxsize];				//存放个顶点关系的二维数组
	int vertexNum,edgeNum;					//定义图的顶点数和边数
}MGraph;

//图的初始化
void CreateGraph(MGraph *G,Datatype a[],int n,int e){	
	int i,j,k;
	G -> vertexNum = n;
	G -> edgeNum = e;
	for (i = 0; i < G-> vertexNum; ++i)
	{
		G -> vertex[i] = a[i];				//储存顶点信息
	}
	for (i = 0; i < G -> vertexNum; i++)			//初始化邻接矩阵
		for (int j = 0; j < G ->vertexNum; j++)
			G -> edge[i][j] = 0;
	printf("输入边关系:\n");
	for (k = 0; k < G -> edgeNum; k++)			//依次输入每一条边
	{	
		scanf("%d%d",&i,&j);				//输入边依附的顶点编号
		G -> edge[i][j] = 1;				//置有边标志
		G -> edge[j][i] = 1;
	}
}

//深度优先搜索
void DFSTraverse(MGraph *G, int v){
	printf("%c\n", G -> vertex [v]);
	visited[v] = 1;
	for (int j = 0; j < G -> vertexNum; j++)
	{
		if (G -> edge[v][j] == 1 && visited[j] == 0)
		{
			DFSTraverse(G,j);			//
		}
	}
}

//广度优先遍历
void BFSTraverse(MGraph *G,int v){				//全局数组变量visited[n]已初始化为0
	int i,j,Q[Maxsize];					//采用顺序队列,存储顶点编号
	int front = -1, rear = -1;				//初始化顺序队列
	printf("%c\n", G -> vertex[v]);
	visited[v] = 1;
	Q[++rear] = v;
	while(front != rear)					//当队列非空的时候
	{
		i = Q[++front];					//当队头元素出队列送到v中
		for (int i = 0; i < G -> vertexNum; i++)
		{
			if (G -> edge[i][j] == 1 && visited[j] == 0)
			{
				printf("%c\n", G -> vertex[j]);
				visited[j] = 1;
				Q[++rear] = j;
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int i;
	char ch[] = {'A','B','C','D'};
	MGraph MG;
	CreateGraph(&MG,ch,4,5);				//建立具有5个节点,6条边的无向图
	for (int i = 0; i < Maxsize; i++)
	{
		visited[i] = 0;
	}
	printf("shen:\n");
	DFSTraverse(&MG,0);					//从顶点0出发进行深度优先遍历
	for (int i = 0; i < Maxsize; i++)	
	{
		visited[i] = 0;
	}
	printf("guang:\n");
	BFSTraverse(&MG,0);					//从顶点0出发进行广度优先遍历
	return 0;
}
