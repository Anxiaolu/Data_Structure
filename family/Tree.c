#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define DELAY_TIME 100;				//���忪ʼ����ˢ�¼��ʱ�� 

int MATEFLAG = 0;
//�ṹ�嶨��
typedef  struct TreeNode 
{  
    int  Num;                     // ������Ŀ
    char Name[20];					// ����
    char Sex;                      // �Ա� ��MŮF
    struct TreeNode * NextNode[20];   //�����ӽڵ㣩 
    struct TreeNode * Parent;         // ���Ƚڵ�
}TreeNode;


//��������
void welcome();											//ϵͳ�������
void progress();										//���̰ٷֱ���ʾ
void MainMenu(TreeNode *Tree);							//��ʼ�������
void showOperation();									//������������

void CreateTreeNode();							//�ڵ㴴������
void CreateTree();								//�ݹ鴴������
	
void OutPutAll();										//�ݹ��������������

TreeNode * FindNode(TreeNode *Tree,char name[],int length);	//�����б�������
void ShowNodeMessage(TreeNode *Tree);					//����ýڵ��Ӧ����Ϣ

int main(){
	
	TreeNode *Tree;
	welcome();
	Tree=(TreeNode *)malloc(sizeof(TreeNode));
	Tree->Parent =NULL;
	
	Sleep(1000);				//����֮�����ö��ݵ���ʱ
	printf("\t�밴��������룡");
	while(getchar() == 0);
	system("cls");
	MainMenu(Tree);
	printf("���˳���ǰϵͳ");
	return 0;

}

void welcome(){
	printf("\n\n\n\n\n\n");
	printf("\t###########################################################\t\n");
	printf("\t##\t\t\t��ӭʹ�ü���ϵͳ\t\t##\t");
	printf("\n\n");
	printf("\t##\t\t\tϵͳ���ڽ�����\t\t\t##\t");
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
	//system("cls");	// ����ϴ�������
	printf("\t##\t\t\t��ǰ����:%d%%\t\t\t##\t\b\b\b\b\b\b\b\b\b\b\b", curPos);
	}
}

//��ǰ̨��ʾ��Ӧ�Ĳ���
void showOperation(){
	printf("\t\t\t---***---��ѡ����Ĳ���---***---\t\t\t\n");
	printf("\t------------A:���������Ϣ���������------------------------\t\n");
	printf("\t------------B:�ڼ����в���ĳ�˲����������������Ӧ��Ϣ----\t\n");
	printf("\t------------C:����µĳ�Ա----------------------------------\t\n");
	printf("\t------------D:�������������Ϣ------------------------------\t\n");
	printf("\t------------E:�޸�ĳ���˵���Ϣ------------------------------\t\n");
	printf("\t------------F:�˳���������----------------------------------\t\n");
}

//���˵�
void MainMenu(TreeNode *Tree){
	char c;	int flag = 1;							//���ڴ����������ʱ����
	char name[20];
	TreeNode *NewNode;
	if(flag){
		printf("\t\t\t��ӭ�������ϵͳ����ѡ�����Ĳ���\t\t\t\n");
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
				printf("\n\t��������Ҫ���ҵ��˵�����:\n\t");
				scanf("%s",name);
				ShowNodeMessage(FindNode(Tree,name,20));
				getchar();
				break;
			case 'C': SubMenu2(); break;
			case 'D': OutPutAll(Tree);getchar(); break;
			case 'E': printf("�޸�ĳ���˵���Ϣ"); break;
			case 'F': printf("\n\n\t----------------������񵽴˽���-----------------");break;
			case '\n': break;
			default:
			    printf("\n\n\t--------�Բ���!���ѡ���ڷ���Χ֮��!---------");
				printf("\n\t-----------�����ٴ�ѡ������ķ�����!-------------");
				printf("\n\t------------------лл����!----------------------\n\t");
				Sleep(500);
				break;
		}
	}
}

//��������Ľڵ㣬�������ڵ�
void CreateTreeNode(TreeNode *Tree){
	TreeNode * NewNode;
	NewNode=(TreeNode *)malloc(sizeof(TreeNode));
	printf("\n\t����������:\n\t");
	scanf("%s",Tree->Name);
	printf("\n\t�������Ա�ŮG��B:\n\t");
	getchar();
	scanf("%c",&(Tree->Sex));
	Tree->Parent=NULL;
	CreateTree(Tree);
	printf("\n\t--------------����ͼ�Ѿ������ɹ�---------------\n\n");

	printf("\n\n\t--------------�밴Enter����������--------------");
	getchar();
}

//�ݹ鴴������
void CreateTree(TreeNode *Node)
{
	int i;
	TreeNode *NewNode;
	NewNode = (TreeNode *)malloc(sizeof(TreeNode));
    Node->NextNode[0]=NewNode;
	Node->NextNode[0]=NULL;

	printf("\n\t������%s����Ů����Ŀ:\n\t",Node->Name);
    scanf("%d",&(Node->Num));

	printf("\n\t������%s����ż������:\n\t",Node->Name);
	scanf("%s",NewNode->Name);
	if((Node->Num)==0&&strcmp(NewNode->Name,"0")==0)		//�����Ƚڵ�û����żʱ���˳�
		return 0;

	if (Node->Sex=='G'||Node->Sex=='g')						//����ԭ��������½��ڵ����ż����
		NewNode->Sex='B';
	else 
		NewNode->Sex='G';

	NewNode->Num=0;											//����ż�ڵ������������
	NewNode->NextNode[0]=NULL;								//������ż�ڵ�ĺ��ӽڵ�Ϊ��
	Node->NextNode[0]=NewNode;								//����ż�ڵ���ԭ�ڵ����԰�
	Node->NextNode[0]->Parent=Node;							//����ż�ĸ��ڵ㶨��Ϊ��һ����ż

	for(i=1;i<=Node->Num;i++)
	{
		NewNode=(TreeNode *)malloc(sizeof(TreeNode));
		printf("\n\t������%s�ĵ�%d��Ů������\n\t",Node->Name,i);
		scanf("%s",NewNode->Name);
		printf("\n\t������%s�ĵ�%d��Ů���Ա�ŮG��B:\n\t",Node->Name,i);
		getchar();
		scanf("%c",&NewNode->Sex);
		NewNode->Num=0;
		NewNode->Parent=Node;								//�븸�ڵ��
		Node->NextNode[i]=NewNode;							
		CreateTree(Node->NextNode[i]);						//�ݹ鴴���μ���
	}
}

int isEmptyTree(TreeNode *Tree){
	if(strcmp(Tree->Name,"0")==0)
		{
			printf("\n\t����ͼ�Ķ������δ�������Ƚ�����\n");
			return 1;
		}
}

//������������е�����
void OutPutAll(TreeNode *Tree)
{
	int i, flag=0;
	printf("\n\t---****---***---***---***---***---***---***---***---***---");
	printf("\n\t����:%s �Ա�:",Tree->Name);
	if (Tree->Sex=='G')
	{
		flag=1;
		printf("Ů");
	}
	else 
		printf("��");

	if (!(Tree->NextNode[0]))
	{ 
		printf("\n\t����û����ż����Ů\n");
		return;
	}

    if(flag==1)
		printf("\n\t�ɷ� ����:%s",Tree->NextNode[0]->Name);
	else
		printf("\n\t���� ����:%s",Tree->NextNode[0]->Name);

	for(i=1;i<=Tree->Num;i++)
	{
		printf("\n\t��%d����Ů������:%s �Ա�:",i,Tree->NextNode[i]->Name,Tree->NextNode[i]->Sex);
		if (Tree->NextNode[i]->Sex=='G')
			printf("Ů");
		else 
			printf("��");
	}

	printf("\n\t");

	for(i=1;i<=Tree->Num;i++)
	{
		OutPutAll(Tree->NextNode[i]);
	}
	printf("\n\t--------------����ͼ�����ϣ�---------------\n\n");

	printf("\n\n\t--------------�밴Enter����������--------------");
	getchar();
}

//�������ҳ���Ӧ�ڵ�
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

//���Ҫ��ѯ�ڵ��Ӧ����Ϣ
void ShowNodeMessage(TreeNode *Tree){
	int i,flag;				//��flag��Ϊ�ж���Ů�ı�־
	TreeNode *NewNode = Tree -> Parent;			//����Ϊ���ڵ������ж��Ƿ�Ϊ���ڵ�
	printf("\t��Ҫ�ҵ�����Ϣ���£�\n");
	printf("\t������%s", Tree -> Name);

	if(Tree->Sex == 'G')
		printf("\t�Ա�Ů��\n");
	else
		printf("\t�Ա��С�\n");

	if(Tree->NextNode[0] != 0)
	{
		//printf("\t%s����żΪ%s",Tree->Name,Tree->NextNode[0]);
		for(i = 0;i < Tree->Num;i++)
		{
			printf("\t%s�ĺ���%dΪ%s.",Tree->Name,i,Tree->NextNode[i]->Name);
		}
	}
	else{
		printf("\t%s����ż,�����޺��ӣ�");
		return ;
	}

	//�ж����ǲ��Ǹ��ڵ�����ǵĻ���û�и�ĸ�ֵ���Ϣ
	if(NewNode==NULL)									
		printf("\n\t���������ͼ����˵���û�и�ĸ���ֵܽ�����Ϣ!",Tree->Name);
	else
	{
		if (NewNode->Sex=='G')      //�жϸ��׽ڵ��Ǹ��׻���ĸ��
		{												 //������������ĸ�ĸ�׵���Ϣ
			printf("\n\tĸ�� ����:%s",NewNode->Name);
			printf("\n\t���� ����:%s",NewNode->NextNode[0]->Name);
		}
		else 
		{
			printf("\n\tĸ�� ����:%s",NewNode->NextNode[0]->Name);
			printf("\n\t���� ����:%s",NewNode->Name);
		}
		if (NewNode->Num>1)                             //�ж���(��)�Ƿ����ֵܽ���
		{												//�����(��)���ֵܽ��õ���Ϣ
			printf("\n\t%s���ֵܽ�����Ϣ����:",Tree->Name);											
			for(i=1;i<=NewNode->Num;i++)
				{
				if(NewNode->NextNode[i])
					printf("\n\t%s����:%s  �Ա�:",NewNode->NextNode[i]->Name,NewNode->NextNode[i]->Name);
				
				if (NewNode->NextNode[i]->Sex=='G')
					printf("Ů");
				else 
					printf("��");
			}
		}
		else
			printf("\n\t%sû���ֵܽ���!",Tree->Name);
	}
	
	//���Ҫ��ѯ������ż
	if (Tree->NextNode[0] != NULL)
	{
		if(flag==1)
			printf("\n\t�ɷ� ����:%s",Tree->NextNode[0]->Name);
		else
			printf("\n\t���� ����:%s",Tree->NextNode[0]->Name);

		if (Tree->Num>0)                             //�ж���(��)�Ƿ��к���
		{		
			printf("\n\t�ĺ��ӵ���Ϣ����:");       //�����(��)�ĺ��ӵ���Ϣ
			for(i=1;i<=Tree->Num;i++)
			{
				printf("\n\t����:%s  �Ա�:",Tree->NextNode[i]->Name);
				
				if (Tree->NextNode[i]->Sex=='G'||Tree->Sex=='g') 
					printf("Ů");
				else 
					printf("��");
			}
		}
		else
			printf("\n\t%s����û�к���",Tree->Name);
	}
	else
		printf("\t%s�ܱ��Ұ��������ڻ�û�ж���", Tree->Name);

	printf("\n\n\t--------------%s����Ϣ�����ϣ�----------------",Tree->Name);
	printf("\n\n\t--------------�밴Enter����������--------------");
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
		printf("\t\t----------��ѡ����Ĳ���-----------\t\t");
		printf("\t---*---*---*---A:���ĳ���˵���Ů��Ϣ---*---*---*---*---");
		printf("\t---*---*---*---B:���ĳ���˵���ż��Ϣ---*---*---*---*---");
		printf("\t---*---*---*---C:�˳�---*---*---*---*---*---*---*---*---");
		c = getchar();
		switch(c)
		{
		case 'A':
		}
	}
}

//��ӽڵ㣬operation��Ϊ������ʽ
void addNode(TreeNode *Node,char operation){
	TreeNode *NewTree;
	printf("������Ҫ���˵�������");
	getchar();
	scanf("%s",Node->Name);
	

}



