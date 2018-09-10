#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>
#include<cctype>
#include<regex>
#include<io.h>
#include<unordered_map>
#include<iterator>
using namespace std;

/*ȫ�ֱ�������*/
unordered_map<string, int> strMap;
int numCharCount = 0, numLineCount = 0,numWordCount = 0;
bool flag = false;
/*����ַ������ļ�����*/
int CharCount(char* argv[])
{
	ifstream file1;
	file1.open(argv[1]);
	char c;
	int num = 0;
	while (!file1.eof())
	{
		file1 >> c;
		if (c >= 0 && c <= 127)
			num++;
	}
	file1.close();
	return num;

}

/*ͳ������*/
int LineCount(char* argv[])
{
	int num = 0;
	ifstream file1;
	file1.open(argv[1]);
	string str;
	while (!file1.eof())
	{
		getline(file1, str);
		num++;
	}
	file1.close();
	return num;
}

/*ͳ�Ƶ��ʸ���*/
void CountWord(stringstream&ss)
{
	string strTmp;
	while (ss >> strTmp)
	{
		unordered_map<string, int>::iterator it = strMap.find(strTmp);
		if (it == strMap.end())//strMap����������ڵ�ǰ���������һ���¼�ֵ�ԣ�����Ƶ��Ϊ1
		{
			strMap.insert(unordered_map<string, int>::value_type(strTmp, 1));

		}
		else //������������Ƶ�ʼ�1
			strMap[strTmp]++;
	}
	

}

/*������*/
int main(int argc, char* argv[])
{
	//�����ĵ�
	fstream file2;
	string strfile,stmp;
	file2.open(argv[1]);
	while (getline(file2, strfile))
	{
		strfile.append(stmp);
		stmp.clear();



		//ȥ�������
		for (int i = 0; i < strfile.length(); i++)
		{
			if (ispunct(strfile[i]))
			{
				strfile[i] = ' ';
				numWordCount++;
			}
		}

		

		//ͳ���ַ�
		stringstream ss(strfile);

		CountWord(ss);
	}
	if (numWordCount > 0)
		numWordCount++;
	numCharCount = CharCount(argv);
	numLineCount = LineCount(argv);

	

	//Output();
	ofstream OutputFile("result.txt");
	if (OutputFile.is_open())
	{
		unordered_map<string, int>::const_iterator it;

		OutputFile << "characters: " << numCharCount << endl;
		OutputFile << "words: " << numWordCount << endl;
		OutputFile << "lines: " << numLineCount << endl;

		//����
		vector<pair<string, int>>vtMap;
		for (auto it = strMap.begin(); it != strMap.end(); it++)
			vtMap.push_back(make_pair(it->first, it->second));

		sort(vtMap.begin(), vtMap.end(),
			[](const pair<string, int> &x, const pair<string, int> &y) -> int {
			return y.second < x.second; });
		int count = 1;
		for (auto it = vtMap.begin(); it != vtMap.end(); it++)
		{
			if (count > 10)
				break;
			OutputFile << it->first << ':' << it->second << endl;
			count++;
		}

	}
	
	file2.close();

	return 0;
}