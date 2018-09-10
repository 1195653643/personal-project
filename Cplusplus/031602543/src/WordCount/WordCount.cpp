#include "stdafx.h"
using namespace std;
string Conventor(int src)//ת��itos
{
	stringstream ss;
	string dst;
	ss.clear();
	ss << src;
	ss >> dst;
	return dst;
}
int Counter::LineCount()//ͳ������
{
	ifstream infile;
	infile.open(sfn);
	string str[1000];
	int line = 0;
	while (infile)//�ļ����� 
	{
		getline(infile, str[line]);//���ж�ȡ
		if (str[line] != "\0")//ͳ�����������������
			line++;
	}
	//cout << "lines: " << line << endl;
	infile.close();
	return line;
}
int Counter::CharCount()
{
	ifstream infile;
	infile.open(sfn);
	string str[1000];
	int ch = 0, line = 0;

	while (infile)//�ļ����� 
	{
		getline(infile, str[line]);//���ж�ȡ
		line++;
	}
	for (int i = 0; i <= line; i++)
	{
		ch += str[i].size();
	}
	ch += line;
	//cout << "characters: " << ch << endl;
	infile.close();
	return ch;
}
int Counter::WordCount()
{
	ifstream infile;
	infile.open(sfn);
	string str[1000], str1[1000];
	int ch = 0, line = 0;
	int words = 0;

	while (infile)//�ļ����� 
		getline(infile, str[line++]);//���ж�ȡ
	line--;
	for (int i = 0; i<line; i++)//������Ŵ���
	{
		int j = 0;
		while (str[i][j] != '\0')
		{
			if (ispunct(str[i][j]))str[i][j] = ' ';//������Ŵ���Ϊ�ո�
			else
			{
				str[i][j] = tolower(str[i][j]);//��ΪСд
			}
			j++;
		}
	}
	int j = 0;

	for (int i = 0; i<line; i++)//���ո������ĵ�ת��Ϊ���� 
	{
		istringstream stream(str[i]);
		while (stream)stream >> str1[j++];
	}
	//for (int k = 0; k < line; k++)cout << str1[k] << endl;

	j -= 1;
	words = 0;
	int k = 0;
	bool isword = true;
	for (int i = 0; i<j - 1; i++)//����ͳ�� 
	{
		isword = true;
		for (k = 0; k<4; k++)//��ȥ���ֿ�ͷ
		{
			if (str1[i][0] == '\0')
			{
				isword = false;
				break;
			}
			if (str1[i][k] == '\0')break;
			else if (!isalpha(str1[i][k])) {
				isword = false;
				break;
			}
		}
		if (isword) {
			words++;
		}
	}
	//for (int k = 0; k < line; k++)cout << str1[k] << endl;
	//cout << "words==" << words << endl;
	//for (int i = 0; i<j - 1; i++)
	//cout << str1[i] << endl;
	//cout << "words: " << words << endl;
	infile.close();
	return words;
}

string Counter::WordFreq()
{
	ifstream infile;
	infile.open(sfn);
	string str[1000], str1[1000], result;
	int ch = 0, line = 0;
	int words = 0;
	bool isword = true;
	while (infile)//�ļ����� 
		getline(infile, str[line++]);//���ж�ȡ
	line--;
	for (int i = 0; i<line; i++)//������Ŵ���
	{
		int j = 0;
		while (str[i][j] != '\0')
		{
			if (ispunct(str[i][j]))str[i][j] = ' ';//������Ŵ���Ϊ�ո�
			else
			{
				str[i][j] = tolower(str[i][j]);//��ΪСд
			}
			j++;
		}
	}

	int j = 0;

	for (int i = 0; i<line; i++)//���ո������ĵ�ת��Ϊ���� 
	{
		istringstream stream(str[i]);
		while (stream)stream >> str1[j++];
	}
	//for (int k = 0; k < line; k++)cout << str1[k] << endl;
	j -= 1;
	words = 0;
	int k = 0;

	for (int i = 0; i<j - 1; i++)//����ɸѡ
	{
		isword = true;
		for (k = 0; k<4; k++)//��ȥ���ֿ�ͷ
		{
			if (str1[i][0] == '\0')
			{
				isword = false;
				break;
			}
			if (str1[i][k] == '\0')break;
			else if (!isalpha(str1[i][k])) {
				isword = false;
				break;
			}
		}
		if (!isword) {
			str1[i] = '\0';
		}
	}

	map<string, int> mymap;
	map<string, int>::iterator it;


	for (int i = 0; i<j - 1; i++)
	{
		//���� �Ƿ���key �еĻ� value++
		//����������key 
		it = mymap.find(str1[i]);
		if (it == mymap.end())
		{
			mymap.insert(map<string, int> ::value_type(str1[i], 1));
		}
		else
		{
			mymap[str1[i]]++;
		}
	}
	it = mymap.begin();
	it++;
	//	for (; it != mymap.end(); it++)
	//	cout << '<'<<it->first << ">: " << it->second << endl;
	it = mymap.begin();
	it++;
	string temps = "\0";
	stringstream ss;
	int i = 0;
	for (i = 0; it != mymap.end(); it++, i++)
	{
		ss.clear();
		temps = "\0";
		str[i] = "\0";
		ss << it->second;
		ss >> temps;
		str[i] = "<" + it->first + "" + ">: " + temps;
	}

	//str[i] = "\0";
	//for (i = 0; str[i] != "\0"; i++)
	//	cout << str[i] << endl;
	for (i = 0; str[i] != "\0"; i++)
	{
		if(str[i][0]=='<')
			result += str[i] + "\n";
		else break;
	}
		infile.close();
	return result;
}
void Counter::Write()
{
	stringstream ss;
	ifstream infile;

	string result, temp;
	int v = 0;

	infile.open(sfn);
	result += "characters: " + Conventor(CharCount()) + "\n";
	result += "words: " + Conventor(WordCount()) + "\n";
	result += "lines: " + Conventor(LineCount()) + "\n";
	result += WordFreq();
	infile.close();

	ofstream outfile;
	outfile.open(dfn);
	outfile << result << endl;
	outfile.close();
}
int main(int argc, char* argv[])
{
	string sfn = argv[1];
	string dfn = "F:\\��\\WordCount\\WordCount\\WordCount\\result.txt";
	Counter Cou(sfn, dfn);

	//Cou.CharCount();
	//Cou.WordCount();
	//Cou.LineCount();
	//Cou.WordFreq();
	//cout << Cou.WordFreq();
	Cou.Write();
	system("pause");
	return 0;
}