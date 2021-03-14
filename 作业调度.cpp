#include<iostream>
#include<string>
using namespace std;
//#define MAXWORK 2//最多同时工作数量
const int MAXWORK = 2;
int *finish = new int[MAXWORK];  // 记录完成时间的变化
class Job {
public:
	string jobName; // 作业名
	int arriveTime; // 到达时间
	int needTime; // 服务时间
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
// 冒泡排序
void Bubble(Job job[], int length) {//到达时间冒泡排序
	Job temp("", 0, 0); // 临时变量
	bool flag = false; // 标识变量，表示是否进行过交换
	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - 1 - i; j++) {
			// 如果前面的数比后面的数大，则交换
			if (job[j].arriveTime > job[j + 1].arriveTime) {
				flag = true;
				temp = job[j];
				job[j] = job[j + 1];
				job[j + 1] = temp;
			}
		}
		if (!flag) { // 在一趟排序中，一次交换都没有发生过
			break;
		}
		else {
			flag = false; // 重置flag, 进行下次判断
		}
	}
}

// 先来先服务算法
void FCFS(Job job[], int length) {
	int minfinish = 999;//最早完成的
	int mintag;//第几个
	double T = 0; // 平均周转时间
	double W = 0; // 平均带权周转时间
	double t = 0; // 周转时间
	double w = 0; // 带权周转时间
	memset(finish, 0, sizeof(finish)*MAXWORK);
	cout << "先来先服务算法：" << endl;
	cout << "作业调度顺序：" << endl;
	for (int c = 0; c < length; c++) {
		// 记录完成时间的变化
		minfinish = 999;
		for (int i = 0; i < MAXWORK; i++) {//找到目前最应该使用的工作器
			if (finish[i] < minfinish) {
				minfinish = finish[i];
				mintag = i;
			}
		}
		if (finish[mintag] >= job[c].arriveTime) {//任务已经到达
			finish[mintag] = finish[mintag] + job[c].needTime;
		}
		else {//任务未到达
			finish[mintag] = job[c].arriveTime + job[c].needTime;
		}
		// 计算周转时间
		t = finish[mintag] - job[c].arriveTime;
		// 计算带权周转时间
		w = t / job[c].needTime;
		// 记录周转时间总和
		T += t;
		// 记录带权周转时间总和
		W += w;
		cout << job[c].jobName;
	}
	cout << endl;
	cout << "平均周转时间为：" << T / length << endl;
	cout << "平均带权周转时间为：" << W / length << endl;
	cout << "=========================" << endl;
}

// 短作业优先算法
void SJF(Job job[], int length) {
	int minfinish = 999;//最早完成的
	int mintag;//第几个
	double T = 0; // 平均周转时间
	double W = 0; // 平均带权周转时间
	double t = 0; // 周转时间
	double w = 0; // 带权周转时间
	memset(finish, 0, sizeof(finish)*MAXWORK);
	int decide = -1;// 记录当前选择到的作业号码
	int minneedtime = 999;// 记录最小服务时间
	int arr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 记录作业的选择情况：1为选中，0为未选中
	cout << "短作业优先算法：" << endl;
	cout << "作业调度顺序：" << endl;
	for (int e = 0; e < length; e++) {
		minfinish = 999;
		for (int i = 0; i < MAXWORK; i++) {//找到目前最应该使用的工作器
			if (finish[i] < minfinish) {
				minfinish = finish[i];
				mintag = i;
			}
		}
		decide = -1;
		minneedtime = 999;
		for (int c = 0; c <length; c++) {
			/**
			* 需要判断：该作业在上一个作业完成时，是否已经到达 该作业是否已经执行完毕 该作业的服务时间是否为最小
			* */
			if (job[c].arriveTime <= finish[mintag] && arr[c] == 0
				&& job[c].needTime < minneedtime) {
				// 如果满足条件
				decide = c; // 暂时记录当前作业的下标
				minneedtime = job[c].needTime; // 暂时记录该作业的服务时间为最小
			}
		}
		if (decide == -1) {//目前所有的作业都未到
			for (int c = 0; c < length; c++) {
				if (arr[c] == 0) {
					decide = c;//选择最早到的
					break;
				}
			}
			finish[mintag] = job[decide].arriveTime + job[decide].needTime;
		}
		else finish[mintag] = finish[mintag] + job[decide].needTime;
		arr[decide] = 1; // 作业已被调度，设置为1
						 // 计算周转时间
		t = finish[mintag] - job[decide].arriveTime;
		// 计算带权周转时间
		w = t / job[decide].needTime;
		// 记录周转时间总和
		T += t;
		// 记录带权周转时间总和
		W += w;
		cout << job[decide].jobName;
	}
	cout << endl;
	cout << "平均周转时间为：" << T / length << endl;
	cout << "平均带权周转时间为：" << W / length << endl;
	cout << "=========================" << endl;
}

// 响应比高者优先算法
void HRRN(Job job[], int length) {
	int minfinish = 999;//最早完成的
	int mintag;//第几个
	double T = 0; // 平均周转时间
	double W = 0; // 平均带权周转时间
	double t = 0; // 周转时间
	double w = 0; // 带权周转时间
//	int *finish = new int[MAXWORK];  // 记录完成时间的变化
	memset(finish, 0, sizeof(finish)*MAXWORK);
	int decide = -1;// 记录当前选择到的作业号码
	double maxresponse = 0;// 记录最大响应比
	int arr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 记录作业的选择情况：1为选中，0为未选中

	cout << "响应比高者优先算法：" << endl;
	cout << "作业调度顺序：" << endl;
	for (int e = 0; e < length; e++) {
		minfinish = 999;
		for (int i = 0; i < MAXWORK; i++) {//找到目前最应该使用的工作器
			if (finish[i] < minfinish) {
				minfinish = finish[i];
				mintag = i;
			}
		}
		decide = -1;
		maxresponse = 0;
		for (int c = 0; c <length; c++) {
			/**
			* 需要判断：该作业在上一个作业完成时，是否已经到达 该作业是否已经执行完毕 该作业的服务时间是否为最小
			* */
			if (job[c].arriveTime <= finish[mintag] && arr[c] == 0) {
				double response = double(finish[mintag] - job[c].arriveTime + job[c].needTime) / job[c].needTime;//如果到达则求响应比
				if (response > maxresponse) {
					// 如果满足条件
					decide = c; // 暂时记录当前作业的下标
					maxresponse = response; // 暂时记录该作业的响应比为最小
				}
			}
		}
		if (decide == -1) {//目前所有的作业都未到
			for (int c = 0; c < length; c++) {
				if (arr[c] == 0) {
					decide = c;//选择最早到的
					break;
				}
			}
			finish[mintag] = job[decide].arriveTime + job[decide].needTime;
		}
		else finish[mintag] = finish[mintag] + job[decide].needTime;
		arr[decide] = 1; // 作业已被调度，设置为1
						 // 计算周转时间
		t = finish[mintag] - job[decide].arriveTime;
		// 计算带权周转时间
		w = t / job[decide].needTime;
		// 记录周转时间总和
		T += t;
		// 记录带权周转时间总和
		W += w;
		cout << job[decide].jobName;
	}
	cout << endl;
	cout << "平均周转时间为：" << T / length << endl;
	cout << "平均带权周转时间为：" << W / length << endl;
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
	// 先用冒泡排序，将它们按到达时间排序
	int length = sizeof(job) / sizeof(Job);
	Bubble(job, length);
	// 先来先服务
	FCFS(job, length);
	// 短作业优先
	SJF(job, length);
	// 高响应者优先
	HRRN(job, length);
	return 0;
}