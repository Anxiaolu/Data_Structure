//第6章
#include "stdlib.h"
#include <stdio.h>
typedef char Element;
struct Tree
{
    Element data;
    struct Tree *left;
    struct Tree *right;
};
void CreateBinSortTree(struct Tree **t);  //这个函数的形参是前面定义过的tree形式的指针的指针,意义是创建新的树
void destroytree(struct Tree *t)
{
  if(t)
   {
    destroytree(t->left);
    destroytree(t->right);
    free (t);
}
}
void SearchNode2Tree(struct Tree *t,struct Tree **rtree,struct Tree **ltree)  //在现有的二叉树中找到某个具体的元素的位置
{
   Element ch;
   *rtree=NULL;
   *ltree=t;
   printf("请输入想要搜索的元素\n");
   scanf("%c",&ch);
   if(ch=='#')
   return;
   else
   while(*ltree)
  {
     if(ch!=(*ltree)->data && ch!=(*rtree)->data)
     {
       *rtree=*ltree;
       *ltree=(*rtree)->left;
       *rtree=(*rtree)->right;
     }
     else
    {
     printf("find!");
     break;
    }
  }
}
void CreateBinSortTree(struct Tree **t)
{
    char ch;
    scanf("%c",&ch);
    getchar();
    if (ch == '#')
    {
        *t = NULL;
        return ;   //输入#表示创建空树,退出此函数
    }
    *t = (struct Tree *)malloc(sizeof(struct Tree));  //为新创建的树分配内存空间,此时*t表示函数指针
    (*t)->data = ch;
    CreateBinSortTree( &((*t)->left));   //创建左子树
    CreateBinSortTree( &((*t)->right));  //创建右子树
}
void PrintTree(struct Tree *r, int order)   //二叉树的遍历,有三种情况,前序中序和后序遍历
{
    if (r == NULL)
    {
        return ;
    }
    switch(order)
    {
    
    case 1:  //先序遍历,顺序是先根,然后左子树,然后右子树
        printf("%c ",r->data);
        PrintTree(r->left,order);
        PrintTree(r->right,order);
        break;
    case 2:  //中序遍历,先遍历左子树.然后是根,最后右子树
        PrintTree(r->left,order);
        printf("%c ",r->data);
        PrintTree(r->right,order);
        break;
    case 3: //后序遍历,先遍历左子树,然后右子树,最后根
        PrintTree(r->left,order);
        PrintTree(r->right,order);
        printf("%c ",r->data);
        break;
    }
    
}
void main()
{
    struct Tree *rtree;
    struct Tree *ltree;
    printf("请输入一组字母(#表示子树为空)\n");
    struct Tree *t=NULL;
    CreateBinSortTree(&t);
    
    printf("\n根左右:");
    PrintTree(t,1);
    printf("\n左根右:");
    PrintTree(t,2);
    printf("\n左右根:");
    PrintTree(t,3);
    printf("\n");
    SearchNode2Tree(t, &rtree, &ltree);
    destroytree(t);
}
