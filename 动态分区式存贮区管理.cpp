#include<iostream>
#include<vector>
#include<string>
using namespace std;
int maxsize=513;//最大
class rd {//分区节点
public:
	bool flagfree;//是否空闲标志 true空闲 false不空闲
	int size;
	rd *next;
	rd(bool flag, int size, rd *next):flagfree(flag), size(size), next(next){}
};

class Progress//进程
{
public:
	string name;
	int begin;
	int size;
	Progress(string name, int begin,int size) :name(name), begin(begin),size(size){}

};

class Management//管理
{
private:
	rd* first; //指向分区链表的第一个节点
	rd* RD;//活动指针
	vector<Progress> work; //存储所有已经申请成功的进程
public:
	Management(rd* next) { first=new rd(true,0, next);}
	void FirstWay();
	void BestWay();
	void WorstWay();
	void show();
	void Release();
};
void Management::FirstWay()
{
	cout << "输入进程名字和大小:"<<endl;
	int address=0;
	string name;
	int size;
	cin >> name >> size;
	size += 1;
	RD=first->next;//活动指针
	while (RD) {
		address += RD->size;
		if (RD->flagfree)
		{
			if (RD->size == size)
			{
				RD->flagfree = false;
				address -= size;
				break;
			}
			else if (RD->size > size)
			{
				address -= size;
				RD->size -= size;
				rd *newrd=new rd(false,size, RD->next);
				RD->next = newrd;
				break;
			}
		}
		RD = RD->next;
	}
	if (RD != NULL) {
		Progress progress(name, address,size);
		work.push_back(progress);
		cout << "申请成功" << endl;
	}
	else cout << "内存不够，任务无法完成" << endl;
}

void Management::BestWay()
{
	cout << "输入进程名字和大小:" << endl;
	int address = 0;
	string name;
	int size;
	cin >> name >> size;
	int min = maxsize;
	size += 1;
	RD = first->next;//活动指针
	rd *rd0 = NULL;//做记录
	while (RD) {
		if (RD->flagfree)
		{
			if (RD->size == size)
			{
				RD->flagfree = false;
				return;
			}
			else if (RD->size > size)
			{
				if (RD->size < min)
					rd0 = RD;
			}
		}
		RD = RD->next;
	}
	if (rd0 != NULL) {
		RD = first->next;
		while (RD != rd0) {
			address += RD->size;
			RD = RD->next;
		}
		if (rd0->size == size) {
			Progress progress(name, address, size);
			work.push_back(progress);
		}
		else {

			RD->size -= size;
			rd *newrd = new rd(false, size, RD->next);
			RD->next = newrd;
			address += RD->size;
			Progress progress(name, address, size);
			work.push_back(progress);
		}
		cout << "申请成功" << endl;
	}
	else cout << "内存不够，任务无法完成" << endl;
}

void Management::WorstWay()
{
	cout << "输入进程名字和大小:" << endl;
	int address = 0;
	string name;
	int size;
	cin >> name >> size;
	int max = 0;
	size += 1;
	RD = first->next;//活动指针
	rd *rd0 = NULL;//做记录
	while (RD) {
		if (RD->flagfree)
		{
			if (RD->size >= size)
			{
				if (RD->size > max)
					rd0 = RD;
			}
		}
		RD = RD->next;
	}
	if (rd0 != NULL) {
		RD = first->next;
		while (RD != rd0) {
			address += RD->size;
			RD = RD->next;
		}
		if(rd0->size==size){
			RD->flagfree = false;
			Progress progress(name, address, size);
			work.push_back(progress);
		}
		else {
			RD->size -= size;
			rd *newrd = new rd(false, size, RD->next);
			RD->next = newrd;
			address += RD->size;
			Progress progress(name, address, size);
			work.push_back(progress);
		}
		cout << "申请成功" << endl;
	}
	else cout << "内存不够，任务无法完成" << endl;
}

void Management::show()
{
	cout << endl;
	int i = 1;
	RD = first->next;
	while (RD) {
		if(RD->flagfree)cout<< "第" << i << "块分区可用"<<'\t';
		else cout << "第" << i << "块分区不可用" << '\t';
		cout << "容量是" << RD->size << "节" << endl;
		i++;
		RD = RD->next;
	}
	cout << "正在运行的进程" << endl;
	auto iter = begin(work);
	while (iter != end(work)) {
		cout << "进程" << iter->name << "的地址在" << iter->begin << endl;
		cout << "大小为" << iter->size <<"节"<< endl;
		iter++;
	}
	cout << endl;
}

void Management::Release()
{
	cout << "输入释放进程的名称";
	int address = 0;
	string name;
	cin >> name;
	auto iter = begin(work);
	for (; iter != end(work); iter++) {//找到进程
		if (iter->name == name) break;
	}
	if (iter == end(work)) {
		cout << "没有此进程" << endl;
		return;
	}
	RD = first;
	while (RD) {
		if (iter->begin == address) break;
		address += RD->next->size;
		RD = RD->next;
	}
	RD->flagfree = true;
	if (RD->next->next != NULL) {//后面分区存在
		if (RD->next->next->flagfree) {//后面分区可用
			RD->next->size += RD->next->next->size;
			rd *p = RD->next->next;
			RD->next->next = RD->next->next->next;
			delete p;
		}
	}
	if (RD->flagfree) {//前面分区可用便合并
		RD->size += RD->next->size;
		rd *p = RD->next;
		RD->next = RD->next->next;
		delete p;
	}
	work.erase(iter);
}

int main() {
	rd *next = new rd(true,512,NULL);
	Management m(next);
	int tag;//做选择标记
	while (true) {
		m.show();
		cout << "请选择功能" << endl;
		cout << "1.申请进程" << endl;
		cout << "2.释放进程" << endl;
		cout << "0.退出" << endl;
		cin >> tag;
		switch (tag) {
		case 1:
			cout << "请输入申请进程方式" << endl;
			cout << "1.首次申请" << endl;
			cout << "2.最好申请" << endl;
			cout << "3.最坏申请" << endl;
			cout << "0.取消" << endl;
			cin >> tag;
			switch (tag) {
			case 1:
				m.FirstWay();
				break;
			case 2:
				m.BestWay();
				break;
			case 3:
				m.WorstWay();
				break;
			default:
				break;
			}
			break;
		case 2:
			m.Release();
			break;
		default:
			return 0;
		}
	}
	return 0;
}
