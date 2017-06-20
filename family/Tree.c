#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define DELAY_TIME 100;				//定义开始界面刷新间隔时间 

int MATEFLAG = 0;
//结构体定义
typedef  struct TreeNode 
{  
    int  Num;                     // 孩子数目
    char Name[20];           // 名字
    char Sex;                      // 性别 男M女F
    struct TreeNode * NextNode[20];   //（孩子节点） 
    struct TreeNode * Parent;         // 祖先节点
}TreeNode;


//函数声明
void welcome();											//系统进入界面
void progress();										//进程百分比显示
void MainMenu(TreeNode *Tree);							//开始界面加载
void showOperation();									//操作界面的输出

void CreateTreeNode();									//节点创建方法
void CreateTree();										//递归创建子树

TreeNode * FindNode(TreeNode *Tree,char name[],int length);	//在树中遍历查找
void ShowNodeMessage(TreeNode *Tree);					//输出该节点对应的信息

int main(){
	
	TreeNode *Tree;
	welcome();
	Tree=(TreeNode *)malloc(sizeof(TreeNode));
	Tree->Parent =NULL;
	strcpy(Tree->Name,"0");
	MainMenu(Tree);
	
	Sleep(1000);				//加载之后设置短暂的延时
	printf("\t请按任意键进入！");
	while(getchar() == 0);
	system("cls");
	printf("\t欢迎进入家谱系统！请选择您的操作\n");
	printf("已退出当前系统");
	return 0;

}

void welcome(){
	printf("\n\n\n\n\n\n");
	printf("\t###########################################################\t\n");
	printf("\t##\t\t\t欢迎使用家谱系统\t\t##\t");
	printf("\n\n");
	printf("\t##\t\t\t系统正在进入中\t\t\t##\t");
	printf("\n\n");
	progress();
	printf("\n");
	printf("\t############################################################\t\n");
}

void progress(){
	int curPos = 0;
	while(curPos<100)
	{
	Sleep(30);
	curPos++;
	//system("cls");	// 清除上次输出结果
	fflush(stdout);
	printf("\t##\t\t\t当前进度:%d%%\t\t\t##\t\b\b\b\b\b\b\b\b\b\b\b", curPos);
	}
}

//向前台显示对应的操作
void showOperation(){
	printf("\t\t\t---***---请选择你的操作---***---\t\t\t\n");
	printf("\t------------A:输入家谱信息建立多叉树------------------------\t\n");
	printf("\t------------B:在家族中查找某人并输出他或（她）的相应信息----\t\n");
	printf("\t------------C:添加新的成员----------------------------------\t\n");
	printf("\t------------D:输出整个家谱信息------------------------------\t\n");
	printf("\t------------E:修改某个人的信息------------------------------\t\n");
	printf("\t------------F:退出整个程序----------------------------------\t\n");
}


void MainMenu(TreeNode *Tree){
	char c;								//用于储存操作的临时变量
	char name[20];
	TreeNode *NewTree;
	while(1)
	{
		system("cls");
		showOperation();

		c = getchar();
		switch(c)
		{
			case 'A': CreateTreeNode();	break;
			case 'B': 
				if(strcmp(Tree ->Name, "0") == 0)
				{
					printf("\n\t家谱图的多叉树尚未建立请先建立树\n");
					getchar();
					break;
				}
				printf("\n\t请输入你要查找的人的姓名:\n\t");
				scanf("%s",name);
				ShowNodeMessage(FindNode(Tree,name,20)); break;
			case 'C': printf("添加新的成员"); break;
			case 'D': printf("输出整个家谱信息"); break;
			case 'E': printf("修改某个人的信息"); break;
			case 'F': printf("\n\n\t----------------本项服务到此结束-----------------");break;
			default:
			    printf("\n\n\t--------对不起!你的选择不在服务范围之内!---------");
				printf("\n\t-----------请您再次选择所需的服务项!-------------");
				printf("\n\t------------------谢谢合作!----------------------\n\t");
				break;
		}
	}
}

//根据输入的节点，创建根节点
void CreateTreeNode(TreeNode *Tree){
	TreeNode * NewNode;
	NewNode=(TreeNode *)malloc(sizeof(TreeNode));
	printf("\n\t请输入姓名:\n\t");
	scanf("%s",Tree->Name);
	printf("\n\t请输入性别女G男B:\n\t");
	getchar();
	scanf("%c",&(Tree->Sex));
	Tree->Parent=NewNode;
	Tree->Parent=NULL;
	CreateTree(Tree);
	printf("\n\t--------------家谱图已经建立成功---------------\n\n");

	printf("\n\n\t--------------请按Enter键继续操作--------------");
	getchar();
}

//递归创建子树
void CreateTree(TreeNode *Node)
{
	int i;
	TreeNode *NewNode;
	NewNode = (TreeNode *)malloc(sizeof(TreeNode));
    Node->NextNode[0]=NewNode;
	Node->NextNode[0]=NULL;

	printf("\n\t请输入%s的子女的数目:\n\t",Node->Name);
    scanf("%d",&(Node->Num));

	printf("\n\t请输入%s的配偶的姓名:\n\t",Node->Name);
	scanf("%s",NewNode->Name);
	if((Node->Num)==0&&strcmp(NewNode->Name,"0")==0)		//当祖先节点没有配偶时，退出
		return ;

	if (Node->Sex=='G'||Node->Sex=='g')						//根据原结点设置新建节点的配偶属性
		NewNode->Sex='B';
	else 
		NewNode->Sex='G';

	NewNode->Num=0;											//对配偶节点进行属性设置
	NewNode->NextNode[0]=NULL;								//定义配偶节点的孩子节点为空
	Node->NextNode[0]=NewNode;								//将配偶节点与原节点属性绑定
	Node->NextNode[0]->Parent=Node;							//将配偶的父节点定义为另一个配偶

	for(i=1;i<=Node->Num;i++)
	{
		NewNode=(TreeNode *)malloc(sizeof(TreeNode));
		printf("\n\t请输入%s的第%d子女的名字\n\t",Node->Name,i);
		scanf("%s",NewNode->Name);
		printf("\n\t请输入%s的第%d子女的性别女G男B:\n\t",Node->Name,i);
		getchar();
		scanf("%c",&NewNode->Sex);
		NewNode->Num=0;
		NewNode->Parent=Node;								//与父节点绑定
		Node->NextNode[i]=NewNode;							
		CreateTree(Node->NextNode[i]);						//递归创建次级树
	}
}



//从树中找出对应节点
TreeNode * FindNode(TreeNode *Tree,char name[],int length)
{
	int i;
	TreeNode *NewNode;
   	if(strcmp(Tree -> Name,name)==0)
	{
		if(length==0)
	     	MATEFLAG=1;
		else 
			MATEFLAG=0;
		return Tree;
	}
	if(Tree->NextNode[0]==NULL)
		return NULL;
	for(i=0;i<Tree->Num;i++)
	{
		if (i==0)
		  NewNode=FindNode(Tree->NextNode[i],name,0);
		else 
		  NewNode=FindNode(Tree->NextNode[i],name,20);
		if (NewNode!=NULL)
		  return NewNode;	 
	}	
	return NULL;
	
}

void ShowNodeMessage(TreeNode *Tree){
	int i;
	TreeNode *NewNode;
	printf("您要找的人信息如下：\n");
	printf("姓名：%s",Tree->Name);

	if(strcmp(Tree->Sex,'G')==0 || strcmp(Tree ->Sex,'g') == 0)
	{
		printf("性别：女。\n");
	}
	else(strcmp(Tree->Sex , 'B') == 0 || srcmp(Tree ->Sex, 'b')==0)
	{
		printf("性别：男。\n");
	}

	if(Tree->NextNode[0] != 0)
	{
		printf("%s的配偶为%s",Tree->Name,Tree->NextNode[0]);
		for(i = 0;i < Tree->Num;i++)
		{
			printf("%s的孩子%d为%s.",Tree->Name,i,Tree->NextNode[i]->Name);
		}
	}
	else{
		printf("%s无配偶,并且无孩子！");
		return ;
	}
}






