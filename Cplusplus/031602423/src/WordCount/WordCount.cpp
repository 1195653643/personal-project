#include "stdafx.h"

int main(int args,char* argv[])

{
	char* a = NULL;
	//char* a = "input.txt";
	
	a = argv[1];
	if (argv[1] == NULL)
	{
		cout << "û�������ı�·����" << endl;
		return 1;
	}
	else if (argv[2] != NULL)
	{
		cout << "����������࣡" << endl;
		return 2;
	}
	string filename = argv[1];
	ifstream input;
	input.open(filename);
	if (input.fail())
	{
		cout << "�ļ������ڣ�" << endl;
		return 3;
	}
	input.close();
	
	int characters,words;
	//ͳ���ַ���
	ofstream fout("characters.txt");
	characters = character(a);
	fout << "characters: " << characters << endl;
	fout.close();
	//ͳ�Ƶ�����
	ofstream foutt("words.txt");
	words = word(a);
	foutt << "words: " << words << endl;
	foutt.close();
	//ͳ��ǰʮ��Ƶ
	WordsFrequency(a);
	return 0;
}