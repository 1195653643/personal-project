#pragma once
#include "pre.h"
#include "file.h"

struct node {
	string name;//��
	int times;//����Ƶ��
	node *next;
	node(string n, int number)
	{
		name = n;
		times = number;
		next = NULL;
	}
};

class Word_operater
{
private:
	node *hash_table[18280];//��ϣ��
public:
	Word_operater()
	{
		for (int i = 0; i <= 18279; i++)//��ʼ�������ṹ��ָ������
		{
			hash_table[i] = new node("", 0);
		}
	}
	void insert(string w);
	int words_counter(ifstream &f, Files &fn);
	void file_rank(Files &fn);
};