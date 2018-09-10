#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <String>
#include <fstream>
#include <assert.h>

using namespace std;

struct WordNode
{
	string word;
	int count;

	WordNode()
	{
		word = "";
		count = 0;
	}
	WordNode(string _word, int _count) :word(_word), count(_count) {}

	// overload < for using map and using sort
	bool operator<(WordNode node_comp)
	{
		if (count == node_comp.count)
			return (word < node_comp.word);
		return count > node_comp.count;
	}

	// overload == for using map
	bool operator==(WordNode node_comp)
	{
		if ((word.compare(node_comp.word) == 0 && count == node_comp.count))
			return true;
		return false;
	}
};

// �ַ��Ƿ�����ĸ
bool CharAlphaJudge(char ch);

// �ַ��Ƿ�����ĸ or ����
bool CharAlphaNumberJudge(char ch);

// ���word�ĺϷ���
bool WordCheck(string word);

// ���һ���Ƿ��п���ʾ���ַ�
bool HaveVisibleChar(string line);

// �õ���Ƶ�ֵ� �������������ͳ���ַ�����
void GetWordCountMap(string file_location);

// �Զ���getline����
bool GetLine(ifstream &instream, string &line);