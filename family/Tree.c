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
    char Name[20];           // ����
    char Sex;                      // �Ա� ��MŮF
    struct TreeNode * NextNode[20];   //�����ӽڵ㣩 
    struct TreeNode * Parent;         // ���Ƚڵ�
}TreeNode;


//��������
void welcome();											//ϵͳ�������
void progress();										//���̰ٷֱ���ʾ
void MainMenu(TreeNode *Tree);							//��ʼ�������
void showOperation();									//������������

void CreateTreeNode();									//�ڵ㴴������
void CreateTree();										//�ݹ鴴������

TreeNode * FindNode(TreeNode *Tree,char name[],int length);	//�����б�������
void ShowNodeMessage(TreeNode *Tree);					//����ýڵ��Ӧ����Ϣ

int main(){
	
	TreeNode *Tree;
	welcome();
	Tree=(TreeNode *)malloc(sizeof(TreeNode));
	Tree->Parent =NULL;
	strcpy(Tree->Name,"0");
	MainMenu(Tree);
	
	Sleep(1000);				//����֮�����ö��ݵ���ʱ
	printf("\t�밴��������룡");
	while(getchar() == 0);
	system("cls");
	printf("\t��ӭ�������ϵͳ����ѡ�����Ĳ���\n");
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
	fflush(stdout);
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


void MainMenu(TreeNode *Tree){
	char c;								//���ڴ����������ʱ����
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
					printf("\n\t����ͼ�Ķ������δ�������Ƚ�����\n");
					getchar();
					break;
				}
				printf("\n\t��������Ҫ���ҵ��˵�����:\n\t");
				scanf("%s",name);
				ShowNodeMessage(FindNode(Tree,name,20)); break;
			case 'C': printf("����µĳ�Ա"); break;
			case 'D': printf("�������������Ϣ"); break;
			case 'E': printf("�޸�ĳ���˵���Ϣ"); break;
			case 'F': printf("\n\n\t----------------������񵽴˽���-----------------");break;
			default:
			    printf("\n\n\t--------�Բ���!���ѡ���ڷ���Χ֮��!---------");
				printf("\n\t-----------�����ٴ�ѡ������ķ�����!-------------");
				printf("\n\t------------------лл����!----------------------\n\t");
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
	Tree->Parent=NewNode;
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
		return ;

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

void ShowNodeMessage(TreeNode *Tree){
	int i;
	TreeNode *NewNode;
	printf("��Ҫ�ҵ�����Ϣ���£�\n");
	printf("������%s",Tree->Name);

	if(strcmp(Tree->Sex,'G')==0 || strcmp(Tree ->Sex,'g') == 0)
	{
		printf("�Ա�Ů��\n");
	}
	else(strcmp(Tree->Sex , 'B') == 0 || srcmp(Tree ->Sex, 'b')==0)
	{
		printf("�Ա��С�\n");
	}

	if(Tree->NextNode[0] != 0)
	{
		printf("%s����żΪ%s",Tree->Name,Tree->NextNode[0]);
		for(i = 0;i < Tree->Num;i++)
		{
			printf("%s�ĺ���%dΪ%s.",Tree->Name,i,Tree->NextNode[i]->Name);
		}
	}
	else{
		printf("%s����ż,�����޺��ӣ�");
		return ;
	}
}






