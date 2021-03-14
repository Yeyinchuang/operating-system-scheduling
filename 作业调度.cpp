#include<iostream>
#include<string>
using namespace std;
//#define MAXWORK 2//���ͬʱ��������
const int MAXWORK = 2;
int *finish = new int[MAXWORK];  // ��¼���ʱ��ı仯
class Job {
public:
	string jobName; // ��ҵ��
	int arriveTime; // ����ʱ��
	int needTime; // ����ʱ��
	Job(string jobName, int arriveTime, int needTime) {
		this->jobName = jobName;
		this->arriveTime = arriveTime;
		this->needTime = needTime;
	}
	string toString() {
		return "Job [jobName=" + jobName + ", arriveTime=" + to_string(arriveTime)
			+ ", needTime=" + to_string(needTime) + "]";
	}

};
// ð������
void Bubble(Job job[], int length) {//����ʱ��ð������
	Job temp("", 0, 0); // ��ʱ����
	bool flag = false; // ��ʶ��������ʾ�Ƿ���й�����
	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - 1 - i; j++) {
			// ���ǰ������Ⱥ���������򽻻�
			if (job[j].arriveTime > job[j + 1].arriveTime) {
				flag = true;
				temp = job[j];
				job[j] = job[j + 1];
				job[j + 1] = temp;
			}
		}
		if (!flag) { // ��һ�������У�һ�ν�����û�з�����
			break;
		}
		else {
			flag = false; // ����flag, �����´��ж�
		}
	}
}

// �����ȷ����㷨
void FCFS(Job job[], int length) {
	int minfinish = 999;//������ɵ�
	int mintag;//�ڼ���
	double T = 0; // ƽ����תʱ��
	double W = 0; // ƽ����Ȩ��תʱ��
	double t = 0; // ��תʱ��
	double w = 0; // ��Ȩ��תʱ��
	memset(finish, 0, sizeof(finish)*MAXWORK);
	cout << "�����ȷ����㷨��" << endl;
	cout << "��ҵ����˳��" << endl;
	for (int c = 0; c < length; c++) {
		// ��¼���ʱ��ı仯
		minfinish = 999;
		for (int i = 0; i < MAXWORK; i++) {//�ҵ�Ŀǰ��Ӧ��ʹ�õĹ�����
			if (finish[i] < minfinish) {
				minfinish = finish[i];
				mintag = i;
			}
		}
		if (finish[mintag] >= job[c].arriveTime) {//�����Ѿ�����
			finish[mintag] = finish[mintag] + job[c].needTime;
		}
		else {//����δ����
			finish[mintag] = job[c].arriveTime + job[c].needTime;
		}
		// ������תʱ��
		t = finish[mintag] - job[c].arriveTime;
		// �����Ȩ��תʱ��
		w = t / job[c].needTime;
		// ��¼��תʱ���ܺ�
		T += t;
		// ��¼��Ȩ��תʱ���ܺ�
		W += w;
		cout << job[c].jobName;
	}
	cout << endl;
	cout << "ƽ����תʱ��Ϊ��" << T / length << endl;
	cout << "ƽ����Ȩ��תʱ��Ϊ��" << W / length << endl;
	cout << "=========================" << endl;
}

// ����ҵ�����㷨
void SJF(Job job[], int length) {
	int minfinish = 999;//������ɵ�
	int mintag;//�ڼ���
	double T = 0; // ƽ����תʱ��
	double W = 0; // ƽ����Ȩ��תʱ��
	double t = 0; // ��תʱ��
	double w = 0; // ��Ȩ��תʱ��
	memset(finish, 0, sizeof(finish)*MAXWORK);
	int decide = -1;// ��¼��ǰѡ�񵽵���ҵ����
	int minneedtime = 999;// ��¼��С����ʱ��
	int arr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // ��¼��ҵ��ѡ�������1Ϊѡ�У�0Ϊδѡ��
	cout << "����ҵ�����㷨��" << endl;
	cout << "��ҵ����˳��" << endl;
	for (int e = 0; e < length; e++) {
		minfinish = 999;
		for (int i = 0; i < MAXWORK; i++) {//�ҵ�Ŀǰ��Ӧ��ʹ�õĹ�����
			if (finish[i] < minfinish) {
				minfinish = finish[i];
				mintag = i;
			}
		}
		decide = -1;
		minneedtime = 999;
		for (int c = 0; c <length; c++) {
			/**
			* ��Ҫ�жϣ�����ҵ����һ����ҵ���ʱ���Ƿ��Ѿ����� ����ҵ�Ƿ��Ѿ�ִ����� ����ҵ�ķ���ʱ���Ƿ�Ϊ��С
			* */
			if (job[c].arriveTime <= finish[mintag] && arr[c] == 0
				&& job[c].needTime < minneedtime) {
				// �����������
				decide = c; // ��ʱ��¼��ǰ��ҵ���±�
				minneedtime = job[c].needTime; // ��ʱ��¼����ҵ�ķ���ʱ��Ϊ��С
			}
		}
		if (decide == -1) {//Ŀǰ���е���ҵ��δ��
			for (int c = 0; c < length; c++) {
				if (arr[c] == 0) {
					decide = c;//ѡ�����絽��
					break;
				}
			}
			finish[mintag] = job[decide].arriveTime + job[decide].needTime;
		}
		else finish[mintag] = finish[mintag] + job[decide].needTime;
		arr[decide] = 1; // ��ҵ�ѱ����ȣ�����Ϊ1
						 // ������תʱ��
		t = finish[mintag] - job[decide].arriveTime;
		// �����Ȩ��תʱ��
		w = t / job[decide].needTime;
		// ��¼��תʱ���ܺ�
		T += t;
		// ��¼��Ȩ��תʱ���ܺ�
		W += w;
		cout << job[decide].jobName;
	}
	cout << endl;
	cout << "ƽ����תʱ��Ϊ��" << T / length << endl;
	cout << "ƽ����Ȩ��תʱ��Ϊ��" << W / length << endl;
	cout << "=========================" << endl;
}

// ��Ӧ�ȸ��������㷨
void HRRN(Job job[], int length) {
	int minfinish = 999;//������ɵ�
	int mintag;//�ڼ���
	double T = 0; // ƽ����תʱ��
	double W = 0; // ƽ����Ȩ��תʱ��
	double t = 0; // ��תʱ��
	double w = 0; // ��Ȩ��תʱ��
//	int *finish = new int[MAXWORK];  // ��¼���ʱ��ı仯
	memset(finish, 0, sizeof(finish)*MAXWORK);
	int decide = -1;// ��¼��ǰѡ�񵽵���ҵ����
	double maxresponse = 0;// ��¼�����Ӧ��
	int arr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // ��¼��ҵ��ѡ�������1Ϊѡ�У�0Ϊδѡ��

	cout << "��Ӧ�ȸ��������㷨��" << endl;
	cout << "��ҵ����˳��" << endl;
	for (int e = 0; e < length; e++) {
		minfinish = 999;
		for (int i = 0; i < MAXWORK; i++) {//�ҵ�Ŀǰ��Ӧ��ʹ�õĹ�����
			if (finish[i] < minfinish) {
				minfinish = finish[i];
				mintag = i;
			}
		}
		decide = -1;
		maxresponse = 0;
		for (int c = 0; c <length; c++) {
			/**
			* ��Ҫ�жϣ�����ҵ����һ����ҵ���ʱ���Ƿ��Ѿ����� ����ҵ�Ƿ��Ѿ�ִ����� ����ҵ�ķ���ʱ���Ƿ�Ϊ��С
			* */
			if (job[c].arriveTime <= finish[mintag] && arr[c] == 0) {
				double response = double(finish[mintag] - job[c].arriveTime + job[c].needTime) / job[c].needTime;//�������������Ӧ��
				if (response > maxresponse) {
					// �����������
					decide = c; // ��ʱ��¼��ǰ��ҵ���±�
					maxresponse = response; // ��ʱ��¼����ҵ����Ӧ��Ϊ��С
				}
			}
		}
		if (decide == -1) {//Ŀǰ���е���ҵ��δ��
			for (int c = 0; c < length; c++) {
				if (arr[c] == 0) {
					decide = c;//ѡ�����絽��
					break;
				}
			}
			finish[mintag] = job[decide].arriveTime + job[decide].needTime;
		}
		else finish[mintag] = finish[mintag] + job[decide].needTime;
		arr[decide] = 1; // ��ҵ�ѱ����ȣ�����Ϊ1
						 // ������תʱ��
		t = finish[mintag] - job[decide].arriveTime;
		// �����Ȩ��תʱ��
		w = t / job[decide].needTime;
		// ��¼��תʱ���ܺ�
		T += t;
		// ��¼��Ȩ��תʱ���ܺ�
		W += w;
		cout << job[decide].jobName;
	}
	cout << endl;
	cout << "ƽ����תʱ��Ϊ��" << T / length << endl;
	cout << "ƽ����Ȩ��תʱ��Ϊ��" << W / length << endl;
	cout << "=========================" << endl;
}

int main() {
	Job jobA("A", 0, 7);
	Job jobB("B", 2, 10);
	Job jobC("C", 5, 20);
	Job jobD("D", 7, 30);
	Job jobE("E", 12, 40);
	Job jobF("F", 15, 8);
	Job jobG("G", 4, 8);
	Job jobH("H", 6, 20);
	Job jobI("I", 8, 10);
	Job jobJ("J", 10, 12);
	Job job[] = { jobA, jobB, jobC, jobD, jobE, jobF, jobG, jobH, jobI, jobJ};
	// ����ð�����򣬽����ǰ�����ʱ������
	int length = sizeof(job) / sizeof(Job);
	Bubble(job, length);
	// �����ȷ���
	FCFS(job, length);
	// ����ҵ����
	SJF(job, length);
	// ����Ӧ������
	HRRN(job, length);
	return 0;
}