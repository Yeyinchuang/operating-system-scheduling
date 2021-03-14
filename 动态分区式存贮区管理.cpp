#include<iostream>
#include<vector>
#include<string>
using namespace std;
int maxsize=513;//���
class rd {//�����ڵ�
public:
	bool flagfree;//�Ƿ���б�־ true���� false������
	int size;
	rd *next;
	rd(bool flag, int size, rd *next):flagfree(flag), size(size), next(next){}
};

class Progress//����
{
public:
	string name;
	int begin;
	int size;
	Progress(string name, int begin,int size) :name(name), begin(begin),size(size){}

};

class Management//����
{
private:
	rd* first; //ָ���������ĵ�һ���ڵ�
	rd* RD;//�ָ��
	vector<Progress> work; //�洢�����Ѿ�����ɹ��Ľ���
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
	cout << "����������ֺʹ�С:"<<endl;
	int address=0;
	string name;
	int size;
	cin >> name >> size;
	size += 1;
	RD=first->next;//�ָ��
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
		cout << "����ɹ�" << endl;
	}
	else cout << "�ڴ治���������޷����" << endl;
}

void Management::BestWay()
{
	cout << "����������ֺʹ�С:" << endl;
	int address = 0;
	string name;
	int size;
	cin >> name >> size;
	int min = maxsize;
	size += 1;
	RD = first->next;//�ָ��
	rd *rd0 = NULL;//����¼
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
		cout << "����ɹ�" << endl;
	}
	else cout << "�ڴ治���������޷����" << endl;
}

void Management::WorstWay()
{
	cout << "����������ֺʹ�С:" << endl;
	int address = 0;
	string name;
	int size;
	cin >> name >> size;
	int max = 0;
	size += 1;
	RD = first->next;//�ָ��
	rd *rd0 = NULL;//����¼
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
		cout << "����ɹ�" << endl;
	}
	else cout << "�ڴ治���������޷����" << endl;
}

void Management::show()
{
	cout << endl;
	int i = 1;
	RD = first->next;
	while (RD) {
		if(RD->flagfree)cout<< "��" << i << "���������"<<'\t';
		else cout << "��" << i << "�����������" << '\t';
		cout << "������" << RD->size << "��" << endl;
		i++;
		RD = RD->next;
	}
	cout << "�������еĽ���" << endl;
	auto iter = begin(work);
	while (iter != end(work)) {
		cout << "����" << iter->name << "�ĵ�ַ��" << iter->begin << endl;
		cout << "��СΪ" << iter->size <<"��"<< endl;
		iter++;
	}
	cout << endl;
}

void Management::Release()
{
	cout << "�����ͷŽ��̵�����";
	int address = 0;
	string name;
	cin >> name;
	auto iter = begin(work);
	for (; iter != end(work); iter++) {//�ҵ�����
		if (iter->name == name) break;
	}
	if (iter == end(work)) {
		cout << "û�д˽���" << endl;
		return;
	}
	RD = first;
	while (RD) {
		if (iter->begin == address) break;
		address += RD->next->size;
		RD = RD->next;
	}
	RD->flagfree = true;
	if (RD->next->next != NULL) {//�����������
		if (RD->next->next->flagfree) {//�����������
			RD->next->size += RD->next->next->size;
			rd *p = RD->next->next;
			RD->next->next = RD->next->next->next;
			delete p;
		}
	}
	if (RD->flagfree) {//ǰ��������ñ�ϲ�
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
	int tag;//��ѡ����
	while (true) {
		m.show();
		cout << "��ѡ����" << endl;
		cout << "1.�������" << endl;
		cout << "2.�ͷŽ���" << endl;
		cout << "0.�˳�" << endl;
		cin >> tag;
		switch (tag) {
		case 1:
			cout << "������������̷�ʽ" << endl;
			cout << "1.�״�����" << endl;
			cout << "2.�������" << endl;
			cout << "3.�����" << endl;
			cout << "0.ȡ��" << endl;
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
