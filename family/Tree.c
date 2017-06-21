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
    char Name[20];					// 名字
    char Sex;                      // 性别 男M女F
    struct TreeNode * NextNode[20];   //（孩子节点） 
    struct TreeNode * Parent;         // 祖先节点
}TreeNode;


//函数声明
void welcome();											//系统进入界面
void progress();										//进程百分比显示
void MainMenu(TreeNode *Tree);							//开始界面加载
void showOperation();									//操作界面的输出

void CreateTreeNode();							//节点创建方法
void CreateTree();								//递归创建子树
	
void OutPutAll();										//递归遍历整个家谱树

TreeNode * FindNode(TreeNode *Tree,char name[],int length);	//在树中遍历查找
void ShowNodeMessage(TreeNode *Tree);					//输出该节点对应的信息

int main(){
	
	TreeNode *Tree;
	welcome();
	Tree=(TreeNode *)malloc(sizeof(TreeNode));
	Tree->Parent =NULL;
	
	Sleep(1000);				//加载之后设置短暂的延时
	printf("\t请按任意键进入！");
	while(getchar() == 0);
	system("cls");
	MainMenu(Tree);
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

//主菜单
void MainMenu(TreeNode *Tree){
	char c;	int flag = 1;							//用于储存操作的临时变量
	char name[20];
	TreeNode *NewNode;
	if(flag){
		printf("\t\t\t欢迎进入家谱系统！请选择您的操作\t\t\t\n");
		flag = 0;
	}
	while(1)
	{
		system("cls");
		showOperation();
		c = getchar();
		switch(c)
		{
			case 'A': 
				isEmptyTree(Tree);
				CreateTreeNode(Tree);
				break;
			case 'B': 
				printf("\n\t请输入你要查找的人的姓名:\n\t");
				scanf("%s",name);
				ShowNodeMessage(FindNode(Tree,name,20));
				getchar();
				break;
			case 'C': SubMenu2(); break;
			case 'D': OutPutAll(Tree);getchar(); break;
			case 'E': printf("修改某个人的信息"); break;
			case 'F': printf("\n\n\t----------------本项服务到此结束-----------------");break;
			case '\n': break;
			default:
			    printf("\n\n\t--------对不起!你的选择不在服务范围之内!---------");
				printf("\n\t-----------请您再次选择所需的服务项!-------------");
				printf("\n\t------------------谢谢合作!----------------------\n\t");
				Sleep(500);
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
		return 0;

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

int isEmptyTree(TreeNode *Tree){
	if(strcmp(Tree->Name,"0")==0)
		{
			printf("\n\t家谱图的多叉树尚未建立请先建立树\n");
			return 1;
		}
}

//遍历并输出树中的内容
void OutPutAll(TreeNode *Tree)
{
	int i, flag=0;
	printf("\n\t---****---***---***---***---***---***---***---***---***---");
	printf("\n\t姓名:%s 性别:",Tree->Name);
	if (Tree->Sex=='G')
	{
		flag=1;
		printf("女");
	}
	else 
		printf("男");

	if (!(Tree->NextNode[0]))
	{ 
		printf("\n\t至今没有配偶和子女\n");
		return;
	}

    if(flag==1)
		printf("\n\t丈夫 姓名:%s",Tree->NextNode[0]->Name);
	else
		printf("\n\t妻子 姓名:%s",Tree->NextNode[0]->Name);

	for(i=1;i<=Tree->Num;i++)
	{
		printf("\n\t第%d个子女的姓名:%s 性别:",i,Tree->NextNode[i]->Name,Tree->NextNode[i]->Sex);
		if (Tree->NextNode[i]->Sex=='G')
			printf("女");
		else 
			printf("男");
	}

	printf("\n\t");

	for(i=1;i<=Tree->Num;i++)
	{
		OutPutAll(Tree->NextNode[i]);
	}
	printf("\n\t--------------家谱图输出完毕！---------------\n\n");

	printf("\n\n\t--------------请按Enter键继续操作--------------");
	getchar();
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

//输出要查询节点对应的信息
void ShowNodeMessage(TreeNode *Tree){
	int i,flag;				//将flag作为判断男女的标志
	TreeNode *NewNode = Tree -> Parent;			//定义为父节点用于判断是否为根节点
	printf("\t您要找的人信息如下：\n");
	printf("\t姓名：%s", Tree -> Name);

	if(Tree->Sex == 'G')
		printf("\t性别：女。\n");
	else
		printf("\t性别：男。\n");

	if(Tree->NextNode[0] != 0)
	{
		//printf("\t%s的配偶为%s",Tree->Name,Tree->NextNode[0]);
		for(i = 0;i < Tree->Num;i++)
		{
			printf("\t%s的孩子%d为%s.",Tree->Name,i,Tree->NextNode[i]->Name);
		}
	}
	else{
		printf("\t%s无配偶,并且无孩子！");
		return ;
	}

	//判断它是不是根节点如果是的话就没有父母兄弟信息
	if(NewNode==NULL)									
		printf("\n\t是这个家谱图里最顶端的人没有父母和兄弟姐妹信息!",Tree->Name);
	else
	{
		if (NewNode->Sex=='G')      //判断父亲节点是父亲还是母亲
		{												 //输出他（她）的父母亲的信息
			printf("\n\t母亲 姓名:%s",NewNode->Name);
			printf("\n\t父亲 姓名:%s",NewNode->NextNode[0]->Name);
		}
		else 
		{
			printf("\n\t母亲 姓名:%s",NewNode->NextNode[0]->Name);
			printf("\n\t父亲 姓名:%s",NewNode->Name);
		}
		if (NewNode->Num>1)                             //判断他(她)是否有兄弟姐妹
		{												//输出他(她)的兄弟姐妹的信息
			printf("\n\t%s的兄弟姐妹信息如下:",Tree->Name);											
			for(i=1;i<=NewNode->Num;i++)
				{
				if(NewNode->NextNode[i])
					printf("\n\t%s姓名:%s  性别:",NewNode->NextNode[i]->Name,NewNode->NextNode[i]->Name);
				
				if (NewNode->NextNode[i]->Sex=='G')
					printf("女");
				else 
					printf("男");
			}
		}
		else
			printf("\n\t%s没有兄弟姐妹!",Tree->Name);
	}
	
	//如果要查询的有配偶
	if (Tree->NextNode[0] != NULL)
	{
		if(flag==1)
			printf("\n\t丈夫 姓名:%s",Tree->NextNode[0]->Name);
		else
			printf("\n\t妻子 姓名:%s",Tree->NextNode[0]->Name);

		if (Tree->Num>0)                             //判断他(她)是否有孩子
		{		
			printf("\n\t的孩子的信息如下:");       //输出他(她)的孩子的信息
			for(i=1;i<=Tree->Num;i++)
			{
				printf("\n\t姓名:%s  性别:",Tree->NextNode[i]->Name);
				
				if (Tree->NextNode[i]->Sex=='G'||Tree->Sex=='g') 
					printf("女");
				else 
					printf("男");
			}
		}
		else
			printf("\n\t%s至今还没有孩子",Tree->Name);
	}
	else
		printf("\t%s很悲惨啊，到现在还没有对象！", Tree->Name);

	printf("\n\n\t--------------%s的信息输出完毕！----------------",Tree->Name);
	printf("\n\n\t--------------请按Enter键继续操作--------------");
	getchar();
}

void SubMenu2(){
	char c;
	int flag = 0;
	char name[];
	TreeNode *NewNode;
	while(1)
	{
		system("cls");
		printf("\t\t----------请选择你的操作-----------\t\t");
		printf("\t---*---*---*---A:添加某个人的子女信息---*---*---*---*---");
		printf("\t---*---*---*---B:添加某个人的配偶信息---*---*---*---*---");
		printf("\t---*---*---*---C:退出---*---*---*---*---*---*---*---*---");
		c = getchar();
		switch(c)
		{
		case 'A':
		}
	}
}

//添加节点，operation作为操作方式
void addNode(TreeNode *Node,char operation){
	TreeNode *NewTree;
	printf("请输入要做人的姓名。");
	getchar();
	scanf("%s",Node->Name);
	

}



