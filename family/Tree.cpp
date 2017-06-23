#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define DELAY_TIME 100;				//���忪ʼ����ˢ�¼��ʱ�� 

int MARRYIN = -1;
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
void isEmptyTree(TreeNode *Tree);						//�ж��Ƿ�Ϊ����
void SubMenu2(TreeNode *Tree);							//��ʾ�����˵�����ӽڵ㣩
void SubMenu1(TreeNode *Tree);							//��ʾ�����˵����޸Ľڵ㣩


void CreateTreeNode(TreeNode *Tree);					//�ڵ㴴������
void CreateTree(TreeNode *Tree);						//�ݹ鴴������
	
void OutPutAll(TreeNode *Tree);							//�ݹ��������������

TreeNode * FindNode(TreeNode *Tree,char name[],int mark);	//�����б�������
void ShowNodeMessage(TreeNode *Tree);					//����ýڵ��Ӧ����Ϣ

void addNode(TreeNode *Node,char operation);				//��ӽڵ�

void NodeModify(TreeNode *Node,char operation);				//�޸Ľڵ���Ϣ

int main(){
	
	TreeNode *Tree;
	welcome();
	Tree=(TreeNode *)malloc(sizeof(TreeNode));
	Tree->Parent =NULL;
	
	Sleep(1000);				//����֮�����ö��ݵ���ʱ
	printf("\t�밴Enter�����룡");
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
	printf("\t\t\t---------��ѡ����Ĳ���---------\t\t\t\n");
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
				//isEmptyTree(Tree);
				CreateTreeNode(Tree);
				getchar();
				break;
			case 'B': 
				printf("\n\t��������Ҫ���ҵ��˵�����:\n\t");
				scanf("%s",name);
				ShowNodeMessage(FindNode(Tree,name,1));
				printf("\n\n\t--------------%s����Ϣ�����ϣ�----------------",Tree->Name);
				printf("\n\n\t--------------�밴Enter����������--------------");
				getchar();
				break;
			case 'C': 
				SubMenu2(Tree);
				printf("\n\n\t-------------��Ů����Ϣ��ӳɹ�----------------");
				getchar();
				break;
			case 'D': 
				OutPutAll(Tree);
				getchar();
				printf("\n\t--------------����ͼ�����ϣ�---------------\n\n");
				printf("\n\n\t--------------�밴Enter����������--------------");
				getchar();
				break;
			case 'E':
				SubMenu1(Tree);
				getchar();
				break;
			case 'F': 
				printf("\n\n\t----------------���η��񵽴˽���-----------------");
				break;
			case '\n': break;
			default:
			    printf("\n\n\t--------�Բ���!���ѡ���ڷ���Χ֮��!---------");
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
		return ;

	if (Node->Sex=='G'||Node->Sex=='g')						//����ԭ��������½��ڵ����ż����
		NewNode->Sex='B';
	else 
		NewNode->Sex='G';

	NewNode->Num=0;											//����ż�ڵ������������
	NewNode->NextNode[0]=NULL;								//������ż�ڵ�ĺ��ӽڵ�Ϊ��
	Node->NextNode[0]=NewNode;								//����ż�ڵ���ԭ�ڵ����԰�
	Node->NextNode[0]->Parent=Node;		 					//����ż�ĸ��ڵ㶨��Ϊ��һ����ż

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

void isEmptyTree(TreeNode *Tree){
	if(strcmp(Tree->Name,"0")==0)
		{
			printf("\n\t����ͼ�Ķ������δ�������Ƚ�����\n");
			return ;
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
		return ;
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
}

//�������ҳ���Ӧ�ڵ�,length��Ϊһ��ת����־�жϱ�־
TreeNode * FindNode(TreeNode *Tree,char name[],int mark)
{
	int i;
	TreeNode *NewNode;
   	if(strcmp(Tree -> Name,name)==0)		//�ж��Ƿ�Ϊ���ڵ�
	{
		if(mark == 0)
			MARRYIN = 1;					//������ż�ڵ�ĵ���������MARRYINȫ�ֱ�����1������������»�ԭΪ0
		else
			MARRYIN = 0;					
		return Tree;
	}
	if(Tree -> NextNode[0] == NULL)
		return NULL;
	/*else {
		if(Tree->NextNode[0] != NULL || strcmp(Tree -> NextNode[0] -> Name,name)==0)		//�ж��Ƿ�Ϊ��ż�ڵ�
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
		  NewNode=FindNode(Tree->NextNode[i],name,0);				//�������ż�ڵ㣬��������
		else 
		  NewNode=FindNode(Tree->NextNode[i],name,1);
		if (NewNode!=NULL)
		  return NewNode;	 
	}
	return NULL;
}

//���Ҫ��ѯ�ڵ��Ӧ����Ϣ
void ShowNodeMessage(TreeNode *Tree){
	int i;
	TreeNode *NewNode;			//����Ϊ���ڵ������ж��Ƿ�Ϊ���ڵ�
	printf("\t��Ҫ�ҵ�����Ϣ���£�\n");
	printf("\t������%s", Tree -> Name);

	if(Tree->Sex == 'G')
	{
		printf("\t�Ա�Ů��\n");
	}
	else
		printf("\t�Ա��С�\n");
	

	NewNode = Tree -> Parent;

	if(MARRYIN == 1)
	{
		if(Tree -> Sex == 'G')
		{
			printf("\t���Ǽ���ü���ġ�");
			printf("\n\t�ɷ� ����:%s",NewNode->Name);
		}
		else
			{
				printf("\n\n\t��������Ů�����Ը�ĸ��Ϣ���ڼ����ڰ���");
				printf("\n\t���� ����:%s",NewNode -> Name);
			}
		if ((NewNode -> Num)>0)                                //�ж���(��)�Ƿ��к���
			{		
				printf("\n\t�ĺ��ӵ���Ϣ����:");               //�����(��)�ĺ��ӵ���Ϣ
				for(i=1;i<=NewNode->Num;i++)
				{
					printf("\n\t����:%s  �Ա�:",NewNode->NextNode[i]->Name);
					
					if (NewNode -> NextNode[i] -> Sex == 'G') 
						printf("Ů");
					else 
						printf("��");
				}
			}
		getchar();
		return ;
		}

	if(Tree->NextNode[0] != 0)
	{
		printf("\t%s����żΪ%s\n",Tree->Name,Tree->NextNode[0] -> Name);
		for(i = 1;i < Tree->Num;i++)								//�ų���ż�ڵ�
		{
			printf("\t%s�ĺ���%dΪ%s.",Tree->Name,i,Tree->NextNode[i]->Name);
		}
	}
	else{
		printf("\t����ż,�����޺��ӣ�");											
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
				if(NewNode -> NextNode[i])
					printf("\n\t%s����:%s  �Ա�:",NewNode->NextNode[i]->Name,NewNode->NextNode[i]->Name);
				
				if (NewNode -> NextNode[i] -> Sex == 'G')
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
		if(Tree -> NextNode[0] -> Sex == 'G')
			printf("\n\t�ɷ� ����:%s",Tree->NextNode[0]->Name);
		else
			printf("\n\t���� ����:%s",Tree->NextNode[0]->Name);

		if (Tree->Num>0)                             //�ж���(��)�Ƿ��к���
		{		
			printf("\n\t���ӵ���Ϣ����:");       //�����(��)�ĺ��ӵ���Ϣ
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
	getchar();
}

//����˵������ӽڵ�
void SubMenu2(TreeNode *Tree){
	char c;
	int flag = 0;
	char name[20];
	TreeNode *NewNode;
	while(1)
	{
		system("cls");
		printf("\t\t----------��ѡ����Ĳ���-----------\t\t\n");
		printf("\t---*---*---*---A:���ĳ���˵���Ů��Ϣ---*---*---*---*---\n");
		printf("\t---*---*---*---B:���ĳ���˵���ż��Ϣ---*---*---*---*---\n");
		printf("\t---*---*---*---C:�˳�---*---*---*---*---*---*---*---*---\n");
		c = getchar();
		switch(c)
		{
		case 'A': 
			printf("������Ҫ�����Ľڵ㣺");
			scanf("%s",name);
			NewNode = FindNode(Tree,name,1);
			addNode(NewNode,'a'); 
			printf("\n\t-------------��Ů����Ϣ��ӳɹ�----------------\n");
			Sleep(500);
			break;
		case 'B': 
			printf("������Ҫ�����Ľڵ㣺");
			scanf("%s",name);
			NewNode=FindNode(Tree,name,1);
			addNode(Tree,'b'); 
			printf("\n\t-------------��ż����Ϣ��ӳɹ�----------------\n");
			Sleep(500);
			break;
		case 'C': return ; break;
		}
	}
}

//��ӽڵ㣬operation��Ϊ������ʽ
void addNode(TreeNode *Node,char operation){
	TreeNode *NewNode;

	if(Node == NULL)
	{
		printf("\n\n\t****�ü���ͼ��û��%s����˵���Ϣ��ȷ���Ƿ��������*****\n",Node->Name);
		getchar();
		return ;
	}
	if(operation == 'a')
	{
		NewNode=(TreeNode *)malloc(sizeof(TreeNode));
		printf("\n\n\t��������Ů��Ϣ:\n\t");
		scanf("%s",NewNode->Name);
		printf("\n\n\t�������Ա�\n");
		getchar();
		scanf("%c",&NewNode->Sex);																		
		NewNode->NextNode[0]=(TreeNode *)malloc(sizeof(TreeNode));		//�Ժ��ӽڵ�Ĳ���
		NewNode->NextNode[0]=NULL;										//��ʼ��...
		NewNode->Num=0;
		NewNode->Parent=Node;
		Node->NextNode[Node -> Num+1]=NewNode;									//���ڵ��Ӧ�ĸı�
		Node->Num = Node -> Num+1;
		return ;
	}
	if(operation == 'b')
	{
		//�жϵ�ǰ�ڵ��Ƿ��ѻ�
		if(Node -> Parent != NULL && strcmp(Node -> Name,Node -> Parent -> NextNode[0] -> Name) == 0
			|| Node -> NextNode[0] != NULL)
		{
			printf("\n\n\t�Ѿ�������ż");
			return ;
		}
		if(Node == NULL)
		{
			printf("\n\n\t****�ü���ͼ��û��%s����˵���Ϣ��ȷ���Ƿ��������*****\n",Node ->Name);
			return;
		}
		NewNode=(TreeNode *)malloc(sizeof(TreeNode));
		printf("\n\n\t�����������ż������:\n\t");
		scanf("%s",NewNode->Name);
		if(Node ->Sex == 'G')
			NewNode -> Sex = 'B';
		else
			NewNode -> Sex = 'G';
		NewNode->Parent=Node;
		Node->NextNode[0]=NewNode;
		return ;
	}
	//�жϵ�Ϊ���ڵ��������
	if(Node -> Parent == NULL && Node -> NextNode[0] == NULL)
	{
		printf("\n\n\t%s��û����ż���������ż��",Node->Name);
		return ;
	}
}

//�޸���Ϣ�˵����޸Ľڵ���Ϣ
void SubMenu1(TreeNode *Tree)
{
	char c;
	int flag = 0;
	char name[20];
	TreeNode *NewNode;
	while(1)
	{
		system("cls");
		printf("\n\n\t           ---*****---��ѡ����Ĳ���---****---");
		printf("\n\t---*---*---*---A:�޸ĸ��˵���Ϣ---*---*---*---*---*---*----");
		printf("\n\t---*---*---*---B:�޸ĸ�ĸ����Ϣ---*---*---*---*---*---*----");
		printf("\n\t---*---*---*---C:�޸��ֵܽ��õ���Ϣ---*---*---*---*---*----");
		printf("\n\t---*---*---*---D:�޸���Ů����Ϣ---*---*---*---*---*---*----");
		printf("\n\t---*---*---*---E:�޸���ż����Ϣ---*---*---*---*---*---*----");
		printf("\n\t---*---*---*---F:�˳�-*---*---*---*---*---*---*---*---*----\n\t");
		c = getchar();
		switch(c)
		{
		case 'A': 
			printf("������Ҫ�����Ľڵ㣺");
			scanf("%s",name);
			NewNode = FindNode(Tree,name,1);
			NodeModify(Tree,'a');
			getchar();
			break;
		case 'B': 
			printf("������Ҫ�����Ľڵ㣺");
			scanf("%s",name);
			NewNode=FindNode(Tree,name,1);
			NodeModify(Tree,'b');
			getchar();
			break;
		case 'C': 
			printf("������Ҫ�����Ľڵ㣺");
			scanf("%s",name);
			NewNode=FindNode(Tree,name,1);
			NodeModify(Tree,'c');
			break;
		case 'D': 
			printf("������Ҫ�����Ľڵ㣺");
			scanf("%s",name);
			NewNode=FindNode(Tree,name,1);
			NodeModify(Tree,'d');
			break;
		case 'E': 
			printf("������Ҫ�����Ľڵ㣺");
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

//�޸Ľڵ���Ϣ
void NodeModify(TreeNode *Tree,char operation){
	int flag =0;
	char name[20];
	//TreeNode *NewNode;
	if(operation == 'a')
	{
		printf("\n\n\t�������޸ĵ�����:����Ҫ�޸����롮0��Ȼ��Enter������\n\t");
		scanf("%s",name);
		if(strcmp(name,"0")!=0)
			strcpy(Tree->Name,name);							//���ڵ��Ӧ��������Ϣ�����޸�

		printf("\n\n\t�Ƿ�Ҫ�޸��Ա�:��Ҫ������'1'����Ҫ�޸�����'0'Ȼ��Enter������\n\t");
	    scanf("%d",&flag);
        if (flag == 1)
		{
			if(Tree -> Sex == 'G')
				Tree -> Sex = 'B';
			else 
				Tree -> Sex = 'G';
		}
		printf("\n\t-------------������Ϣ�޸ĳɹ�----------------\n");
	}
	if(operation == 'b')
	{
		if(Tree -> Parent)
		{
			printf("�ýڵ��Ǽ��׸��ڵ㣬û�и�ĸ��Ϣ��");
			return ;
		}
		if (MARRYIN == 1)											 //�ж��ǲ�������Ů�����߼���ü���ĸ�Ů
			{
				if(Tree -> Sex == 'G')
					printf("\n\n\t���Ǽ���ü�������Ը�ĸ��Ϣ���ڼ����ڰ���");
				else
					printf("\n\n\t��������Ů�����Ը�ĸ��Ϣ���ڼ����ڰ���");
				return ;
			}
		
		printf("\n\t-------------��ĸ��Ϣ�޸ĳɹ�----------------\n");
	}
	if(operation == 'c')
	{
		printf("\n\t-------------�ֵܽ�����Ϣ�޸ĳɹ�----------------\n");
	}
	if(operation == 'd')
	{
		if(Tree -> Num == 0)
			printf("����û����Ů��");
		if(Tree -> Num >0)
		{
				
		}
		printf("\n\t-------------��Ů��Ϣ�޸ĳɹ�----------------\n");
	}
	if(operation == 'e')
	{
		printf("\n\t-------------��ż��Ϣ�޸ĳɹ�----------------\n");
	}
	return ;
}
