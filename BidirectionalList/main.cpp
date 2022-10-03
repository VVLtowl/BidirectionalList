//�o�������X�g
//����ҁF�g�E�J�C�l�C
//2022.10.03

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define WORD_SIZE (50)



//class DOUBLE_LINKED_LIST_NODE
//{
//private:
//	DOUBLE_LINKED_LIST_NODE* pre;
//	DOUBLE_LINKED_LIST_NODE* next;
//public:
//	void SetPreNode(DOUBLE_LINKED_LIST_NODE* _pre) { pre = _pre; };
//	void SetNextNode(DOUBLE_LINKED_LIST_NODE* _next) { next = _next; };
//	DOUBLE_LINKED_LIST_NODE* GetPreNode() { return pre; };
//	DOUBLE_LINKED_LIST_NODE* GetNextNode() { return next; };
//};


//class DOUBLE_LINKED_LIST
//{
//protected:
//	DOUBLE_LINKED_LIST_NODE* head;
//	DOUBLE_LINKED_LIST_NODE* tail;
//
//public:
//	void Add(DOUBLE_LINKED_LIST_NODE* _node);
//	void Remove(DOUBLE_LINKED_LIST_NODE* _node);
//	void Clear();
//	DOUBLE_LINKED_LIST_NODE* GetHead() { return head; };
//	DOUBLE_LINKED_LIST_NODE* GetTail() { return tail; };
//};
//


class SCORE_INFO //: public DOUBLE_LINKED_LIST_NODE
{
private:
	SCORE_INFO* pre;
	SCORE_INFO* next;
	int score;
	string name;
public:
	SCORE_INFO() {};
	SCORE_INFO(int _score, string _name) :
		score(_score),
		name(_name)
	{
	};

	void SetPreNode(SCORE_INFO* _pre) { pre = _pre; };
	void SetNextNode(SCORE_INFO* _next) { next = _next; };
	SCORE_INFO* GetPreNode() { return pre; };
	SCORE_INFO* GetNextNode() { return next; };

	string GetName() { return name; };
	int GetScore() { return score; };
};

class SCORE_INFO_LIST
{
private:
	SCORE_INFO* head = nullptr;
	SCORE_INFO* tail = nullptr;
public:
	void AddScoreInfo(SCORE_INFO* _scoreInfo);
	void PrintAllFromHead();
	void PrintAllFromTail();
	void Clear();

	SCORE_INFO* GetHead() { return head; };
	SCORE_INFO* GetTail() { return tail; };
};


int main(void)
{
	//�f�[�^��ۑ����邽�߂̑o�������X�g
	SCORE_INFO_LIST scoreList;

	//�t�@�C����ǂݍ���ŁA�f�[�^���擾
	{
		FILE* fp;
		char fileName[] = "Scores.txt";

		int score;
		char name[WORD_SIZE];

		fp = fopen(fileName, "r"); // �t�@�C�����J���A���s�����NULL��Ԃ��B
		if (fp == NULL) {
			cout << fileName << "file open error!" << endl;
			return -1;
		}
		else {
			cout << fileName << "file opened!" << endl;
		}
		
		while (fscanf(fp, "%d\t%s", &score, name) != EOF) {

#if _DEBUG
			cout << name << ":" << score<<endl;//test
#endif
			SCORE_INFO* scoreInfo=new SCORE_INFO(score, name);
			scoreList.AddScoreInfo(scoreInfo);
		}

		fclose(fp);
	}

	//�ǂݎ�����f�[�^���o��
	{
		scoreList.PrintAllFromHead();
		scoreList.PrintAllFromTail();
	}


	scoreList.Clear();
	(void)getchar();
	return 0;
}


//�֐���`-----------------------------------------
void SCORE_INFO_LIST::AddScoreInfo(SCORE_INFO* _scoreInfo)
{
	SCORE_INFO* preNode = tail;
	SCORE_INFO* nextNode = _scoreInfo;
	if (preNode == nullptr)
	{
		head = nextNode;
		tail = nextNode;
	}
	else
	{
		preNode->SetNextNode(nextNode);
		nextNode->SetPreNode(preNode);
		tail = nextNode;
	}
}

void SCORE_INFO_LIST::PrintAllFromHead()
{
	SCORE_INFO* node = head;
	if (node == nullptr)return;

	do{
		cout << node->GetName() << (node->GetName().size()<8? "\t\t:":"\t:")<< node->GetScore() << endl;
	} while ((node = (SCORE_INFO*)node->GetNextNode()) != nullptr);
}

void SCORE_INFO_LIST::PrintAllFromTail()
{
	SCORE_INFO* node = tail;
	if (node == nullptr)return;

	do {
		cout << node->GetName() << (node->GetName().size() < 8 ? "\t\t:" : "\t:") << node->GetScore() << endl;
	} while ((node = (SCORE_INFO*)node->GetPreNode()) != nullptr);
}

void SCORE_INFO_LIST::Clear()
{
	SCORE_INFO* node = head;
	if (node == nullptr)return;

	SCORE_INFO* next = node;
	do {
		node = next;
		next = next->GetNextNode();
		delete node;
	} while (next != nullptr);
}