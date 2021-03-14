#include<iostream>
#include<algorithm>
using namespace std;
const int MAX = 100;
int number;//需要调度的磁盘数量
void Write(int head, int *task, int count)
{
	cout << "开始位置:" << head << endl;
	cout << "走道顺序:";
	for (int i = 0; i<number; i++)
		cout << task[i] << " ";
	cout << endl;
	cout << "磁头走过平均道数:" << (double)count/ number;
	cout << endl;
}

int FCFS(int head, int *task)//先来先服务
{
	int count = abs(head - task[0]);
	for (int i = 1; i<number; i++)
		count += abs(task[i] - task[i - 1]);
	return count;
}

int SSTF(int head, int *task)//最短寻道时间优先
{
	int index,min = 999;//最小距离下表以及最小距离
	int FirstHead = head;//保存初始值

	for (int i = 0; i<number - 1; i++)
	{
		//找到最小距离的索引
		for (int j = i; j<number; j++)
		{
			if (min >= abs(head - task[j]))
			{
				min = abs(head - task[j]);
				index = j;
			}
		}
		int temp = task[i];//交换
		task[i] = task[index];
		task[index] = temp;
		head = task[i];
		min = 999;
	}
	int count = abs(FirstHead - task[0]);
	for (int i = 0; i<number - 1; i++)
		count += abs(task[i + 1] - task[i]);
	return count;
}

int SCAN(int head, int *task)//电梯算法 先上后下
{
	int index = 0;//做task下标
	int *sorttask = new int[number];
	for (int i = 0; i < number; i++) {
		sorttask[i] = task[i];
	}
	sort(sorttask, sorttask +number);//排序
	int tag;//标记下一个开始位置
	for (int i = 0; i < number; i++) {
		if (sorttask[i] >= head) {
			tag = i;
			break;
		}
	}
	for (int i = tag; i < number; i++) {//计算上顺序
		task[index++] = sorttask[i];
	}
	for (int i = tag-1; i >= 0; i--) {//计算下顺序
		task[index++] = sorttask[i];
	}
	int count = abs(head - task[0]);
	for (int i = 1; i<number; i++)
		count += abs(task[i] - task[i - 1]);
	return count;
}

int main()
{
	number = 14;//设置最多一百
	int task[MAX] = { 30,50,100,180,20,90,150,70,80,10,160,120,40,110 }, head = 90;//head 为头
	int *FCFStask = new int[number];
	int *SSTFtask = new int[number];
	int *SCANtask = new int[number];
	for (int i = 0; i < number; i++) {
		FCFStask[i] = task[i];
		SSTFtask[i] = task[i];
		SCANtask[i] = task[i];
	}
	//去掉注释从三个算法中选一个运行
	int FCFScount = FCFS(head, FCFStask);
	int SSTFcount = SSTF(head, SSTFtask);
	int SCANcount = SCAN(head, SCANtask);
	cout << "先来先服务：" << endl;
	Write(head, FCFStask, FCFScount);
	cout << endl;
	cout << "最短寻道时间优先：" << endl;
	Write(head, SSTFtask, SSTFcount);
	cout << endl;
	cout << "电梯算法(先上后下)：" << endl;
	Write(head, SCANtask, SCANcount);
	return 0;
}