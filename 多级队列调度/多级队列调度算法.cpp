#include <stdio.h>
#include<iostream>
#include<fstream>
//#include<sstream>
using namespace std;
typedef struct tag_pcb
{ 
	char name[8];
	int need;//须运行的时间
	int turn;//周转时间
	struct tag_pcb *next;
} PCB;
PCB* RQ1,*RQ2,*Finish1, *Finish2;//带头结点
int clock = 0;//时钟
void initial(PCB* RQ) {
	strcpy(RQ->name, "");
	RQ->need = 0;
	RQ->turn = 0;
	RQ->next =NULL;
}
void readfile(PCB* RQ1, PCB* RQ2) {
	PCB* p;
	p = (PCB*)malloc(sizeof(PCB));
	initial(p);
	p = RQ1;
	ifstream input("进程.txt");
	if (!input) {
		cout << "导入“进程.txt”文件失败" << endl;
		return;
	}
	for (int i = 0; i < 5; i++) {
		PCB *q;
		q = (PCB*)malloc(sizeof(PCB));
		initial(q);
		input >> q->name >> q->need >> q->turn;
		p->next = q;
		p = p->next;
	}
	p = RQ2;
	while (true) {
		PCB *q;
		q = (PCB*)malloc(sizeof(PCB));
		initial(q);
		input >> q->name >> q->need >> q->turn;
		if (input.eof() != 0) break;
		p->next = q;
		p = p->next;
	}
}

void remove(PCB* RQ, PCB* q) {
	PCB* p;
	p = (PCB*)malloc(sizeof(PCB));
	initial(p);
	p = RQ->next;
	if (p == q) {
		RQ->next = RQ->next->next;
		return; 
	}
	while (p->next != q) {
		p = p->next;
	}
	p->next = p->next->next;
}


int main() {
	int piecetime = 7;//片时间
	PCB* p, *q,*s=NULL;//p 移动 q记录尾部 s Finish移动
	RQ1 = (PCB*)malloc(sizeof(PCB));
	RQ2 = (PCB*)malloc(sizeof(PCB));
	Finish1 = (PCB*)malloc(sizeof(PCB));
	Finish2 = (PCB*)malloc(sizeof(PCB));
	p = (PCB*)malloc(sizeof(PCB));
	q = (PCB*)malloc(sizeof(PCB));
	s = (PCB*)malloc(sizeof(PCB));
	initial(p);
	initial(q);
	initial(s);
	initial(RQ1);
	initial(RQ2);
	initial(Finish1);
	initial(Finish2);
	readfile(RQ1, RQ2);
	p = RQ1->next;
	s = Finish1;
	while (p != NULL) {//RQ1调度
		q = p;
		while (q->next != NULL)q = q->next;
		if (p->need <= piecetime) {
			clock += p->need;
			p->turn += clock;
			s->next = p;
			s = s->next;
			p=p->next;
		}
		else {
			clock += piecetime;
			p->need -= piecetime;
			q->next = p;
			p = p->next;
			q->next->next=NULL;
		}
	}
	RQ1 = Finish1;

	Finish2->next = NULL;
	s = Finish2;
	p = RQ2->next;
	q= RQ2->next;
	while (p != NULL) {//RQ2调度

		while (p != NULL) {//找到所需时间最短的进程
			if (p->need < q->need) q= p;
			p = p->next;
		}
		clock += q->need;
		q->turn += clock;
		s->next = q;
		s = s->next;
		remove(RQ2, q);
		p = RQ2->next;
		q = RQ2->next;
	}
	RQ2 = Finish2;

	p = RQ1->next;
	for (int i = 0; i < 5; i++)
	{
		cout << p->name << ":" << p->turn << endl;
		p = p->next;
	}
	cout << endl;
	p = RQ2->next;
	for (int i = 0; i < 5; i++)
	{
		cout << p->name << ":" << p->turn << endl;
		p = p->next;
	}
}