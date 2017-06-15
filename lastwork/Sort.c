//第十章-排序
//四个方法,插入排序,冒泡排序,快速排序,希尔排序.
#include <stdio.h>
#include <stdlib.h>

//直接插入排序
void InsertSort(int r[],int n)				//r[0]用作暂存单元和检查哨
{
	int i,j;
	for (i = 2; i <= n; i++)
	{
		r[0] = r[i];				//暂存待插入的记录,设置标记			
		for (j = i-1; r[0] < r[j] ; --j)
		{
			r[j+1] = r[j];			//依次后移
		}
		r[j+1] = r[0];				
	}
}

//冒泡排序
void BubbleSort(int r[], int n)				//r[0]用作交换的临时单元
{
	int j,exchange,bound;
	exchange = n;							//第一次起泡排序的时间是r[1]~r[n]
	while(exchange != 0)					//当上一趟排序有关记录交换时
	{
		bound = exchange;					
		exchange = 0;
		for (j = 0; j < bound; j++)			//一趟起泡排序的区间是r[1]~r[bound]
		{
			if (r[j] > r[j+1])
			{
				r[0] = r[j];
				r[j] = r[j+1];
				r[j+1] =r[0];
				exchange = j;				//记录每一次记录交换的位置
			}
		}
	}				
}

int Partition(int r[], int first, int end)
{
	int i = first,j = end,temp;					//初始化一次分配的区间
	while(i<j)
	{
		while(i < j && r[i] <= r[j]) j--;		//右侧扫描
		if (i<j)
		{
			temp = r[i]; r[i] = r[j];r[j] = temp;	//把较小的记录交换到前面
			i++;
		}
		while(i<j && r[i] <= r[j]) i++;			//左侧扫描
		if (i<j)
		{
			temp = r[i]; r[i] = r[j];r[j] = temp;	//较大的记录交换到后面
			j--;
		}
	}
	return i;										//i为轴值记录的最终未知
}
//快速排序
void QuietSort(int r[], int first, int end)
{
	if (first == end) return;				//区间长度为1,递归结束
	else{
		int pivot = Partition(r,first,end);	//一次划分
		QuietSort(r,first,pivot-1);			//对左侧序列进行快速排序
		QuietSort(r,pivot+1,end);			//对右侧序列进行排序
	}
}


//希尔排序
void ShellSort(int r[],int n)
{
	int d,i,j;
	for (d = n/2; d >= 1; d = d/2)			//以增量为d进行直接插入排序
	{
		for (i = d+1; i <=n ; i++)
		{
			r[0] = r[i];					//暂存待插入记录,然后类似调用直插排序的方式
			for (j = i-d; j > 0 && r[0] < r[j]; j = j-d)
				r[j+d] = r[j];
			r[j+d] = r[0];
		}
	}
}

int main()
{
	int t[7] = {0,15,7,2,33,25,14};
	InsertSort(t,7);
	for (int i = 0; i < 7; i++)
	{
		printf("%d ",t[i]);
	}
	return 0;
}