//双方向リスト
//製作者：トウカイネイ
//2022.10.03

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
#define WORD_SIZE (50)

//クラス定義---------------------------------------
class SCORE_INFO//ノード
{
private:
	SCORE_INFO* prev = nullptr;
	SCORE_INFO* next = nullptr;
	int score;
	string name;
public:
	SCORE_INFO(int _score, string _name) :
		score(_score),
		name(_name)
	{
	};

	void SetPrevNode(SCORE_INFO* _prev) { prev = _prev; };
	void SetNextNode(SCORE_INFO* _next) { next = _next; };
	SCORE_INFO* GetPrevNode() { return prev; };
	SCORE_INFO* GetNextNode() { return next; };

	string GetName() { return name; };
	int GetScore() { return score; };
};

class SCORE_INFO_LIST//リスト(ノード管理用)
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


//main関数-----------------------------------------
int main(void)
{
	//データを格納するための双方向リスト
	SCORE_INFO_LIST scoreList;

	//ファイルを読み込んで、データを取得
	{
		FILE* fp;
		char fileName[] = "Scores.txt";

		int score;
		char name[WORD_SIZE];

		fp = fopen(fileName, "r"); // ファイルを開く、失敗するとNULLを返す。
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

	//読み取ったデータを出力
	{
		scoreList.PrintAllFromHead();
#if 0
		scoreList.PrintAllFromTail();
#endif
	}


	scoreList.Clear();
	(void)getchar();
	return 0;
}


//関数定義-----------------------------------------
void SCORE_INFO_LIST::AddScoreInfo(SCORE_INFO* _scoreInfo)
{
	SCORE_INFO* prevNode = tail;
	SCORE_INFO* nextNode = _scoreInfo;
	if (prevNode == nullptr)
	{
		head = nextNode;
		tail = nextNode;
	}
	else
	{
		prevNode->SetNextNode(nextNode);
		nextNode->SetPrevNode(prevNode);
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
	} while ((node = (SCORE_INFO*)node->GetPrevNode()) != nullptr);
}

void SCORE_INFO_LIST::Clear()
{
	SCORE_INFO* node = head;
	if (node == nullptr)return;

	SCORE_INFO* next = node;
	do {
		node = next;
		next = node->GetNextNode();//削除される前に次のノードを格納
		delete node;
	} while (next != nullptr);
}