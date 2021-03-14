#include<iostream>
#include<fstream>
using namespace std;
const int n = 5;//���̸���
const int m = 3;//��Դ����
int Available[m];//��ʣ����Դ
int Alloc[n][m];//��������Դ
int Need[n][m];//�滹��Ҫ��Դ
int request[m];//������
int tag;//����ĸ���������
int num=0;//��־���󼸴�
//int count = 4;//�ܹ��������
void input() {
	ifstream input("��Դ�ļ�.txt");
	if (!input) {
		cout << "�޷��򿪡���Դ�ļ�.txt����" << endl;
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
	ifstream input("�����ļ�.txt");
	if (!input) {
		cout << "�޷��򿪡������ļ�.txt����" << endl;
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
	int work[m];//Ϊ�˱��浱ǰ����
	memset(Finish, false, n);
	for (int i = 0; i < m; i++)
		work[i] = Available[i];
	for (int i = 0; i < n; i++) {
		if (Finish[i]) continue;
		else {
			if (compare(work, Need[i])) {
				Finish[i] = true;
				cout << "P" << i + 1 << "��ȫ" << endl;
				for (int j = 0; j < m; j++)work[j] += Alloc[i][j];
				i = -1;//���ô�ͷ��ʼ
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (!Finish[i]) {
			cout << "P" << i + 1 << "����ȫ" << endl;
			return false;
		}
	}
	return true;
}

int main() {
	input();
	while (true) {
		read_req();
		if (num > 4)break;//�ܹ��Ĵ�
		cout << endl;
		cout << "��" << num << "������" << endl;
		if (!compare(Need[tag], request)) {
			cout << "����Ƿ�" << endl;
			continue;
		}
		if (!compare(Available,request)) {
			cout << "P" << tag + 1 << "����" << endl;
			continue;
		}
		for (int i = 0; i < m; i++) {//��̽����
			Available[i] -= request[i];
			Alloc[tag][i] += request[i];
			Need[tag][i]-= request[i];
		}
		if (safe()) {
			int flag=0;//�Ƿ��㹻
			for(int i=0;i<m;i++)
				if (Need[tag][i] != 0) { flag = 1; break; }
			if (flag == 0) {
				for (int i = 0; i < m; i++)
					Available[i] += Alloc[tag][i];
			}
			continue;
		}
		else {
			cout << "���󲻰�ȫ" << endl;
			for (int i = 0; i < m; i++) {//��̽����
				Available[i] += request[i];
				Alloc[tag][i] -= request[i];
				Need[tag][i] += request[i];
			}
			continue;
		}
	}
	return 0;
}