//双方向リスト
//製作者：トウカイネイ
//2022.10.03

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include <string>
#include <iostream>

using namespace std;

#define WORD_SIZE (50)



class DOUBLE_LINKED_LIST_NODE
{
private:
	DOUBLE_LINKED_LIST_NODE* pre;
	DOUBLE_LINKED_LIST_NODE* next;
public:
	void SetPreNode(DOUBLE_LINKED_LIST_NODE* _pre) { pre = _pre; };
	void SetNextNode(DOUBLE_LINKED_LIST_NODE* _next) { next = _next; };
	DOUBLE_LINKED_LIST_NODE* GetPreNode() { return pre; };
	DOUBLE_LINKED_LIST_NODE* GetNextNode() { return next; };
};


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
		pre = new SCORE_INFO();
		next = new SCORE_INFO();
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
	void PrintAll();

	SCORE_INFO* GetHead() { return head; };
	SCORE_INFO* GetTail() { return tail; };
};


int main(void)
{
	//データを保存するための
	SCORE_INFO_LIST scoreList;


	//ファイルを読み込んで、データを取得
	{
		FILE* fp;
		char fileName[] = "Scores.txt";
		//int chr;

		int score;
		char name[WORD_SIZE];
		//char word[WORD_SIZE];



		fp = fopen(fileName, "r"); // ファイルを開く。失敗するとNULLを返す。
		if (fp == NULL) {
			printf("[%s] file open error!\n", fileName);
			return -1;
		}
		else {
			printf("[%s] file opened!\n", fileName);
		}

		
		while (fscanf(fp, "%d\t%s", &score, name) != EOF) {
			cout << name << ":" << score<<endl;//test
			SCORE_INFO* scoreInfo=new SCORE_INFO(score, name);
			scoreList.AddScoreInfo(scoreInfo);
		}

		fclose(fp);
	
		scoreList.PrintAll();
	}

	return 0;
}


//関数定義-----------------------------------------

void SCORE_INFO_LIST::AddScoreInfo(SCORE_INFO* _scoreInfo)
{
	SCORE_INFO* preNode = tail;
	SCORE_INFO* nextNode = _scoreInfo;
	if (preNode == nullptr)
	{
		head = nextNode;
	}
	else
	{
		preNode->SetNextNode(nextNode);
		nextNode->SetPreNode(preNode);
		head = nextNode;
	}
}

void SCORE_INFO_LIST::PrintAll()
{
	SCORE_INFO* node = head;
	if (node == nullptr)return;

	do{
		cout << node->GetName() << "\t:" << node->GetScore() << endl;
	} while ((node = (SCORE_INFO*)node->GetNextNode()) != nullptr);
}