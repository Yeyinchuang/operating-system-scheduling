#include<iostream>
#include<algorithm>
using namespace std;
const int MAX = 100;
int number;//��Ҫ���ȵĴ�������
void Write(int head, int *task, int count)
{
	cout << "��ʼλ��:" << head << endl;
	cout << "�ߵ�˳��:";
	for (int i = 0; i<number; i++)
		cout << task[i] << " ";
	cout << endl;
	cout << "��ͷ�߹�ƽ������:" << (double)count/ number;
	cout << endl;
}

int FCFS(int head, int *task)//�����ȷ���
{
	int count = abs(head - task[0]);
	for (int i = 1; i<number; i++)
		count += abs(task[i] - task[i - 1]);
	return count;
}

int SSTF(int head, int *task)//���Ѱ��ʱ������
{
	int index,min = 999;//��С�����±��Լ���С����
	int FirstHead = head;//�����ʼֵ

	for (int i = 0; i<number - 1; i++)
	{
		//�ҵ���С���������
		for (int j = i; j<number; j++)
		{
			if (min >= abs(head - task[j]))
			{
				min = abs(head - task[j]);
				index = j;
			}
		}
		int temp = task[i];//����
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

int SCAN(int head, int *task)//�����㷨 ���Ϻ���
{
	int index = 0;//��task�±�
	int *sorttask = new int[number];
	for (int i = 0; i < number; i++) {
		sorttask[i] = task[i];
	}
	sort(sorttask, sorttask +number);//����
	int tag;//�����һ����ʼλ��
	for (int i = 0; i < number; i++) {
		if (sorttask[i] >= head) {
			tag = i;
			break;
		}
	}
	for (int i = tag; i < number; i++) {//������˳��
		task[index++] = sorttask[i];
	}
	for (int i = tag-1; i >= 0; i--) {//������˳��
		task[index++] = sorttask[i];
	}
	int count = abs(head - task[0]);
	for (int i = 1; i<number; i++)
		count += abs(task[i] - task[i - 1]);
	return count;
}

int main()
{
	number = 14;//�������һ��
	int task[MAX] = { 30,50,100,180,20,90,150,70,80,10,160,120,40,110 }, head = 90;//head Ϊͷ
	int *FCFStask = new int[number];
	int *SSTFtask = new int[number];
	int *SCANtask = new int[number];
	for (int i = 0; i < number; i++) {
		FCFStask[i] = task[i];
		SSTFtask[i] = task[i];
		SCANtask[i] = task[i];
	}
	//ȥ��ע�ʹ������㷨��ѡһ������
	int FCFScount = FCFS(head, FCFStask);
	int SSTFcount = SSTF(head, SSTFtask);
	int SCANcount = SCAN(head, SCANtask);
	cout << "�����ȷ���" << endl;
	Write(head, FCFStask, FCFScount);
	cout << endl;
	cout << "���Ѱ��ʱ�����ȣ�" << endl;
	Write(head, SSTFtask, SSTFcount);
	cout << endl;
	cout << "�����㷨(���Ϻ���)��" << endl;
	Write(head, SCANtask, SCANcount);
	return 0;
}