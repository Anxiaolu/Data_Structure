//邻接表实现图的创建,销毁,DFS,BFS算法
#include <stdio.h>			
#include <stdlib.h>
#include <malloc.h>
#define MaxSize 10				/*图的最大定点数*/
typedef char Datatype;				/*定义图中定点的数据类型,假设为char型*/
int visited[MaxSize] = {0};			/*已经遍历的图的节点集合*/
//定义边表节点
typedef struct 
{
	int adjvex;
	struct EdgeNode *next;
}EdgeNode;

//定义定点表节点
typedef struct 
{
	Datatype vertex;
	EdgeNode * first;
}vertexNode;

//定义邻接表储存结构
typedef struct 
{
	vertexNode adjlist[MaxSize];		/*存放顶点表的数组*/
	int vertexNum,edgeNum;			/*图的定点数和边数*/	
}ALGraph;

/**
 * @param a[]顶点的数据信息
 * @param n 顶点个数
 * @param e 边的个数
 * return 图的邻接表
 */
void CreatGraph(ALGraph *G,Datatype a[],int n,int e){
	int i,j,k;
	EdgeNode *s = NULL;
	G->vertexNum = n;
	G->edgeNum = e;
	for (int i = 0; i < G->vertexNum; i++)
	{
		G->adjlist[i].vertex = a[i];		/*存储顶点信息*/
		G->adjlist[i].first = NULL;		/*初始化表的头指针*/
	}
	for (int i = 0; i < G->edgeNum; i++)
	{
		scanf("%d%d",&i,&j);			/*输入边所依附的顶点编号*/
		s = (EdgeNode *)malloc(sizeof(EdgeNode));
		s->adjvex = j;
		s->next = G-> adjlist[i].first;		/*将s插入到第i个边表的表头*/
		G-> adjlist[i].first = s;
	}
}

/**
 * 图的销毁
 *
 */
void DestoryGraph(ALGraph *G){
	EdgeNode *p = NULL,*q = NULL;
	for (int i = 0; i < G->vertexNum; i++)
	{
		p = q = G-> adjlist[i].first;
		while(p != NULL)
		{
			p = p->next;
			free(q);
			q = p;
		}
	}
}

/**
 * 深度优先遍历
 *
 */
void DFSTraverse(ALGraph *G ,int v){
	EdgeNode * p = NULL;
	int j;
	printf("%c",G->adjlist[v].vertex);
	visited[v] = 1;
	p = G-> adjlist[v].first;		/*工作指针p指向顶点v的边表*/
	while(p != NULL)			/*依次搜索顶点v的邻接点j*/
	{
		j = p->adjvex;
		if(visited[j] == 0) 
			DFSTraverse(G,j);
		p = p->next;
	}
}

/**
 * 广度优先遍历
 *
 */
void BFSTraverse(ALGraph *G,int v){
	EdgeNode *p = NULL;
	int Q[MaxSize],front = -1,rear = -1,j;	/*队列采用顺序储存*/
	printf("%c",G->adjlist[v].vertex);
	visited[v]=1;
	Q[++rear] = v;
	while(front != rear)			/*当队列非空时*/
	{
		v = Q[++front];
		p = G->adjlist[v].first;	/*工作指针p指向顶点v的边表*/
		while(p != NULL)
		{
			j = p->adjvex;		/*j为顶点v的邻接点*/
			if(visited[j] == 0)
			{
				printf("%c",G->adjlist[j].vertex); 
				visited[j] = 1; 
				Q[++rear] =j;
			}
			p = p->next;
		}
	}
}	


int main(int argc, char const *argv[])
{
	char ch[] = {'A','B','C','D','E'};
	int i;
	ALGraph ALG;
	CreatGraph(&ALG,ch,5,6);		/*创建一个具有5个顶点,6条边的有向图*/
	for (int i = 0; i < MaxSize; i++)
	{
		visited[i] = 0;
	}
	printf("深度优先遍历序列是:");
	DFSTraverse(&ALG,0);			/*从顶点0开始进行深度优先遍历*/
	for (int i = 0; i < MaxSize; i++)
	{
		visited[i] = 0;
	}
	printf("广度优先遍历序列是:");
	BFSTraverse(&ALG,4);			/*从顶点0开始进行广度优先遍历*/
	DestoryGraph(&ALG);
	return 0;
}








