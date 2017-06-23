#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define DELAY_TIME 100;				//定义开始界面刷新间隔时间 

int MARRYIN = -1;
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
void isEmptyTree(TreeNode *Tree);						//判断是否为空树
void SubMenu2(TreeNode *Tree);							//显示二级菜单（添加节点）
void SubMenu1(TreeNode *Tree);							//显示二级菜单（修改节点）


void CreateTreeNode(TreeNode *Tree);					//节点创建方法
void CreateTree(TreeNode *Tree);						//递归创建子树
	
void OutPutAll(TreeNode *Tree);							//递归遍历整个家谱树

TreeNode * FindNode(TreeNode *Tree,char name[],int mark);	//在树中遍历查找
void ShowNodeMessage(TreeNode *Tree);					//输出该节点对应的信息

void addNode(TreeNode *Node,char operation);				//添加节点

void NodeModify(TreeNode *Node,char operation);				//修改节点信息

int main(){
	
	TreeNode *Tree;
	welcome();
	Tree=(TreeNode *)malloc(sizeof(TreeNode));
	Tree->Parent =NULL;
	
	Sleep(1000);				//加载之后设置短暂的延时
	printf("\t请按Enter键进入！");
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
	printf("\t\t\t---------请选择你的操作---------\t\t\t\n");
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
				//isEmptyTree(Tree);
				CreateTreeNode(Tree);
				getchar();
				break;
			case 'B': 
				printf("\n\t请输入你要查找的人的姓名:\n\t");
				scanf("%s",name);
				ShowNodeMessage(FindNode(Tree,name,1));
				printf("\n\n\t--------------%s的信息输出完毕！----------------",Tree->Name);
				printf("\n\n\t--------------请按Enter键继续操作--------------");
				getchar();
				break;
			case 'C': 
				SubMenu2(Tree);
				printf("\n\n\t-------------子女的信息添加成功----------------");
				getchar();
				break;
			case 'D': 
				OutPutAll(Tree);
				getchar();
				printf("\n\t--------------家谱图输出完毕！---------------\n\n");
				printf("\n\n\t--------------请按Enter键继续操作--------------");
				getchar();
				break;
			case 'E':
				SubMenu1(Tree);
				getchar();
				break;
			case 'F': 
				printf("\n\n\t----------------本次服务到此结束-----------------");
				break;
			case '\n': break;
			default:
			    printf("\n\n\t--------对不起!你的选择不在服务范围之内!---------");
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
		return ;

	if (Node->Sex=='G'||Node->Sex=='g')						//根据原结点设置新建节点的配偶属性
		NewNode->Sex='B';
	else 
		NewNode->Sex='G';

	NewNode->Num=0;											//对配偶节点进行属性设置
	NewNode->NextNode[0]=NULL;								//定义配偶节点的孩子节点为空
	Node->NextNode[0]=NewNode;								//将配偶节点与原节点属性绑定
	Node->NextNode[0]->Parent=Node;		 					//将配偶的父节点定义为另一个配偶

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

void isEmptyTree(TreeNode *Tree){
	if(strcmp(Tree->Name,"0")==0)
		{
			printf("\n\t家谱图的多叉树尚未建立请先建立树\n");
			return ;
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
		return ;
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
}

//从树中找出对应节点,length作为一个转换标志判断标志
TreeNode * FindNode(TreeNode *Tree,char name[],int mark)
{
	int i;
	TreeNode *NewNode;
   	if(strcmp(Tree -> Name,name)==0)		//判断是否为本节点
	{
		if(mark == 0)
			MARRYIN = 1;					//对于配偶节点的单独处理，将MARRYIN全局变量置1，如果不是重新还原为0
		else
			MARRYIN = 0;					
		return Tree;
	}
	if(Tree -> NextNode[0] == NULL)
		return NULL;
	/*else {
		if(Tree->NextNode[0] != NULL || strcmp(Tree -> NextNode[0] -> Name,name)==0)		//判断是否为配偶节点
		{
			NewNode = Tree -> NextNode[0];
			printf("---------%s",NewNode -> Name);
			MARRYIN = 1;
			return NewNode;
		}
		if{
			for(i=1;i<Tree->Num;i++)
				NewNode=FindNode(Tree->NextNode[i],name); 
			}
		}*/
	for(i=0;i<=Tree->Num;i++)
	{
		if (i==0)
		  NewNode=FindNode(Tree->NextNode[i],name,0);				//如果是配偶节点，单独处理
		else 
		  NewNode=FindNode(Tree->NextNode[i],name,1);
		if (NewNode!=NULL)
		  return NewNode;	 
	}
	return NULL;
}

//输出要查询节点对应的信息
void ShowNodeMessage(TreeNode *Tree){
	int i;
	TreeNode *NewNode;			//定义为父节点用于判断是否为根节点
	printf("\t您要找的人信息如下：\n");
	printf("\t姓名：%s", Tree -> Name);

	if(Tree->Sex == 'G')
	{
		printf("\t性别：女。\n");
	}
	else
		printf("\t性别：男。\n");
	

	NewNode = Tree -> Parent;

	if(MARRYIN == 1)
	{
		if(Tree -> Sex == 'G')
		{
			printf("\t她是嫁入该家族的。");
			printf("\n\t丈夫 姓名:%s",NewNode->Name);
		}
		else
			{
				printf("\n\n\t他是上门女婿所以父母信息不在家谱内包括");
				printf("\n\t妻子 姓名:%s",NewNode -> Name);
			}
		if ((NewNode -> Num)>0)                                //判断他(她)是否有孩子
			{		
				printf("\n\t的孩子的信息如下:");               //输出他(她)的孩子的信息
				for(i=1;i<=NewNode->Num;i++)
				{
					printf("\n\t姓名:%s  性别:",NewNode->NextNode[i]->Name);
					
					if (NewNode -> NextNode[i] -> Sex == 'G') 
						printf("女");
					else 
						printf("男");
				}
			}
		getchar();
		return ;
		}

	if(Tree->NextNode[0] != 0)
	{
		printf("\t%s的配偶为%s\n",Tree->Name,Tree->NextNode[0] -> Name);
		for(i = 1;i < Tree->Num;i++)								//排除配偶节点
		{
			printf("\t%s的孩子%d为%s.",Tree->Name,i,Tree->NextNode[i]->Name);
		}
	}
	else{
		printf("\t无配偶,并且无孩子！");											
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
				if(NewNode -> NextNode[i])
					printf("\n\t%s姓名:%s  性别:",NewNode->NextNode[i]->Name,NewNode->NextNode[i]->Name);
				
				if (NewNode -> NextNode[i] -> Sex == 'G')
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
		if(Tree -> NextNode[0] -> Sex == 'G')
			printf("\n\t丈夫 姓名:%s",Tree->NextNode[0]->Name);
		else
			printf("\n\t妻子 姓名:%s",Tree->NextNode[0]->Name);

		if (Tree->Num>0)                             //判断他(她)是否有孩子
		{		
			printf("\n\t孩子的信息如下:");       //输出他(她)的孩子的信息
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
	getchar();
}

//输出菜单，增加节点
void SubMenu2(TreeNode *Tree){
	char c;
	int flag = 0;
	char name[20];
	TreeNode *NewNode;
	while(1)
	{
		system("cls");
		printf("\t\t----------请选择你的操作-----------\t\t\n");
		printf("\t---*---*---*---A:添加某个人的子女信息---*---*---*---*---\n");
		printf("\t---*---*---*---B:添加某个人的配偶信息---*---*---*---*---\n");
		printf("\t---*---*---*---C:退出---*---*---*---*---*---*---*---*---\n");
		c = getchar();
		switch(c)
		{
		case 'A': 
			printf("请输入要操作的节点：");
			scanf("%s",name);
			NewNode = FindNode(Tree,name,1);
			addNode(NewNode,'a'); 
			printf("\n\t-------------子女的信息添加成功----------------\n");
			Sleep(500);
			break;
		case 'B': 
			printf("请输入要操作的节点：");
			scanf("%s",name);
			NewNode=FindNode(Tree,name,1);
			addNode(Tree,'b'); 
			printf("\n\t-------------配偶的信息添加成功----------------\n");
			Sleep(500);
			break;
		case 'C': return ; break;
		}
	}
}

//添加节点，operation作为操作方式
void addNode(TreeNode *Node,char operation){
	TreeNode *NewNode;

	if(Node == NULL)
	{
		printf("\n\n\t****该家谱图中没有%s这个人的信息请确认是否输入错误*****\n",Node->Name);
		getchar();
		return ;
	}
	if(operation == 'a')
	{
		NewNode=(TreeNode *)malloc(sizeof(TreeNode));
		printf("\n\n\t请输入子女信息:\n\t");
		scanf("%s",NewNode->Name);
		printf("\n\n\t请输入性别：\n");
		getchar();
		scanf("%c",&NewNode->Sex);																		
		NewNode->NextNode[0]=(TreeNode *)malloc(sizeof(TreeNode));		//对孩子节点的操作
		NewNode->NextNode[0]=NULL;										//初始化...
		NewNode->Num=0;
		NewNode->Parent=Node;
		Node->NextNode[Node -> Num+1]=NewNode;									//父节点对应的改变
		Node->Num = Node -> Num+1;
		return ;
	}
	if(operation == 'b')
	{
		//判断当前节点是否已婚
		if(Node -> Parent != NULL && strcmp(Node -> Name,Node -> Parent -> NextNode[0] -> Name) == 0
			|| Node -> NextNode[0] != NULL)
		{
			printf("\n\n\t已经有了配偶");
			return ;
		}
		if(Node == NULL)
		{
			printf("\n\n\t****该家谱图中没有%s这个人的信息请确认是否输入错误*****\n",Node ->Name);
			return;
		}
		NewNode=(TreeNode *)malloc(sizeof(TreeNode));
		printf("\n\n\t请输入添加配偶的姓名:\n\t");
		scanf("%s",NewNode->Name);
		if(Node ->Sex == 'G')
			NewNode -> Sex = 'B';
		else
			NewNode -> Sex = 'G';
		NewNode->Parent=Node;
		Node->NextNode[0]=NewNode;
		return ;
	}
	//判断的为根节点特殊情况
	if(Node -> Parent == NULL && Node -> NextNode[0] == NULL)
	{
		printf("\n\n\t%s还没有配偶，请添加配偶。",Node->Name);
		return ;
	}
}

//修改信息菜单，修改节点信息
void SubMenu1(TreeNode *Tree)
{
	char c;
	int flag = 0;
	char name[20];
	TreeNode *NewNode;
	while(1)
	{
		system("cls");
		printf("\n\n\t           ---*****---请选择你的操作---****---");
		printf("\n\t---*---*---*---A:修改个人的信息---*---*---*---*---*---*----");
		printf("\n\t---*---*---*---B:修改父母的信息---*---*---*---*---*---*----");
		printf("\n\t---*---*---*---C:修改兄弟姐妹的信息---*---*---*---*---*----");
		printf("\n\t---*---*---*---D:修改子女的信息---*---*---*---*---*---*----");
		printf("\n\t---*---*---*---E:修改配偶的信息---*---*---*---*---*---*----");
		printf("\n\t---*---*---*---F:退出-*---*---*---*---*---*---*---*---*----\n\t");
		c = getchar();
		switch(c)
		{
		case 'A': 
			printf("请输入要操作的节点：");
			scanf("%s",name);
			NewNode = FindNode(Tree,name,1);
			NodeModify(Tree,'a');
			getchar();
			break;
		case 'B': 
			printf("请输入要操作的节点：");
			scanf("%s",name);
			NewNode=FindNode(Tree,name,1);
			NodeModify(Tree,'b');
			getchar();
			break;
		case 'C': 
			printf("请输入要操作的节点：");
			scanf("%s",name);
			NewNode=FindNode(Tree,name,1);
			NodeModify(Tree,'c');
			break;
		case 'D': 
			printf("请输入要操作的节点：");
			scanf("%s",name);
			NewNode=FindNode(Tree,name,1);
			NodeModify(Tree,'d');
			break;
		case 'E': 
			printf("请输入要操作的节点：");
			scanf("%s",name);
			NewNode=FindNode(Tree,name,1);
			NodeModify(Tree,'e');
			break;
		case 'F': 
			return ; 
			break;
		}
	}
}

//修改节点信息
void NodeModify(TreeNode *Tree,char operation){
	int flag =0;
	char name[20];
	//TreeNode *NewNode;
	if(operation == 'a')
	{
		printf("\n\n\t请输入修改的姓名:不需要修改输入‘0’然后按Enter键继续\n\t");
		scanf("%s",name);
		if(strcmp(name,"0")!=0)
			strcpy(Tree->Name,name);							//将节点对应的姓名信息进行修改

		printf("\n\n\t是否要修改性别:需要就输入'1'不需要修改输入'0'然后按Enter键继续\n\t");
	    scanf("%d",&flag);
        if (flag == 1)
		{
			if(Tree -> Sex == 'G')
				Tree -> Sex = 'B';
			else 
				Tree -> Sex = 'G';
		}
		printf("\n\t-------------个人信息修改成功----------------\n");
	}
	if(operation == 'b')
	{
		if(Tree -> Parent)
		{
			printf("该节点是家谱根节点，没有父母信息。");
			return ;
		}
		if (MARRYIN == 1)											 //判断是不是上门女婿或者嫁入该家族的妇女
			{
				if(Tree -> Sex == 'G')
					printf("\n\n\t她是嫁入该家族的所以父母信息不在家谱内包括");
				else
					printf("\n\n\t他是上门女婿所以父母信息不在家谱内包括");
				return ;
			}
		
		printf("\n\t-------------父母信息修改成功----------------\n");
	}
	if(operation == 'c')
	{
		printf("\n\t-------------兄弟姐妹信息修改成功----------------\n");
	}
	if(operation == 'd')
	{
		if(Tree -> Num == 0)
			printf("至今还没有子女！");
		if(Tree -> Num >0)
		{
				
		}
		printf("\n\t-------------子女信息修改成功----------------\n");
	}
	if(operation == 'e')
	{
		printf("\n\t-------------配偶信息修改成功----------------\n");
	}
	return ;
}
