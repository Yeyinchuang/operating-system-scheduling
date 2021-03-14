#include<iostream>
#include<fstream>
using namespace std;
const int n = 5;//进程个数
const int m = 3;//资源种类
int Available[m];//存剩余资源
int Alloc[n][m];//存已有资源
int Need[n][m];//存还需要资源
int request[m];//请求量
int tag;//标记哪个进程请求
int num=0;//标志请求几次
//int count = 4;//总共请求次数
void input() {
	ifstream input("资源文件.txt");
	if (!input) {
		cout << "无法打开“资源文件.txt“！" << endl;
		return;
	}
	for (int i = 0; i < m; i++)
		input >> Available[i];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			input >> Alloc[i][j];
		for (int j = 0; j < m; j++)
			input >> Need[i][j];
	}
}

void read_req() {
	ifstream input("请求文件.txt");
	if (!input) {
		cout << "无法打开“请求文件.txt“！" << endl;
		return;
	}
	for (int k = 0; k < num; k++) {
		input >> tag;
		for (int i = 0; i < m; i++)
			input >> request[i];
	}
	if (input.eof() != 0) return;
	input >> tag;
	for (int i = 0; i < m; i++)
		input >> request[i];
	num++;
}
bool compare(int Available[],int request[]) {
	for (int i = 0; i < m; i++)
		if(Available[i] < request[i])return false;
	return true;
}

bool safe() {
	bool Finish[n];
	int work[m];//为了保存当前变量
	memset(Finish, false, n);
	for (int i = 0; i < m; i++)
		work[i] = Available[i];
	for (int i = 0; i < n; i++) {
		if (Finish[i]) continue;
		else {
			if (compare(work, Need[i])) {
				Finish[i] = true;
				cout << "P" << i + 1 << "安全" << endl;
				for (int j = 0; j < m; j++)work[j] += Alloc[i][j];
				i = -1;//重置从头开始
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (!Finish[i]) {
			cout << "P" << i + 1 << "不安全" << endl;
			return false;
		}
	}
	return true;
}

int main() {
	input();
	while (true) {
		read_req();
		if (num > 4)break;//总共四次
		cout << endl;
		cout << "第" << num << "次请求" << endl;
		if (!compare(Need[tag], request)) {
			cout << "请求非法" << endl;
			continue;
		}
		if (!compare(Available,request)) {
			cout << "P" << tag + 1 << "阻塞" << endl;
			continue;
		}
		for (int i = 0; i < m; i++) {//试探分配
			Available[i] -= request[i];
			Alloc[tag][i] += request[i];
			Need[tag][i]-= request[i];
		}
		if (safe()) {
			int flag=0;//是否足够
			for(int i=0;i<m;i++)
				if (Need[tag][i] != 0) { flag = 1; break; }
			if (flag == 0) {
				for (int i = 0; i < m; i++)
					Available[i] += Alloc[tag][i];
			}
			continue;
		}
		else {
			cout << "请求不安全" << endl;
			for (int i = 0; i < m; i++) {//试探分配
				Available[i] += request[i];
				Alloc[tag][i] -= request[i];
				Need[tag][i] += request[i];
			}
			continue;
		}
	}
	return 0;
}