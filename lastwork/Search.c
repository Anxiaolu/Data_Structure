//第九章
//静态查找,折半查找(地柜/非递归)
#include <stdio.h>
#include <stdlib.h>
//顺序查找:r[]为待查数据集合,n为集合长度,k为待查值
int SeqSearch(int r[],int n,int k)						//待查集合存储在数组r[1]~r[n+1]
{
	int i = n;											//倒序比较
	r[0] = k;
	while(r[i] != k)
		i--;
	return 0;
}

//折半查找非递归
int BinSeache1(int r[], int n, int k)					//待查集合存储在数组r[1]~r[n]
{
	int mid,low =1,hight = n;							//初始查找区间为[1,n]
	while(low <=hight)
	{
		mid  = (low + hight)/2;
		if (k < r[mid]) hight = mid -1;
		else if (k > r[mid]) low = mid+1;
			else return mid;							//查找成功,反悔元素序号
	}
	return 0;											//查找失败,返回0
}

//折半查找地柜
int BinSeache2(int r[], int low,int hight, int k)
{
	int mid;
	if (low > hight) return 0;							//设置递归边界
	else{
		mid = (low + hight)/2;
		if (k < r[mid]) return BinSeache2(r,low,mid-1,k);
		else if (k> r[mid]) return BinSeache2(r,mid+1,hight,k);
			else return mid;							//查找成功返回序号
	}
}


int main()
{
	int t[7]={0},i,j;
	printf("请输入数据:");
	for (int i = 0; i < 7; ++i)
	{
		scanf("%d ",t[i]);
	}
	printf("要查询的数是:%d",&i);
	printf("查找结果:\n");
	printf("%d\n",SeqSearch(t,7,i));
	return 0;
}	
