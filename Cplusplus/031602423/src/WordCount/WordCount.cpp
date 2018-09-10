#include<iostream>
#include<string>
#include<map>
#include <fstream>
#include <algorithm>
#include<vector>
using namespace std;

string ff = ".";
int lines=0;
int character(char* path);
int word(string strr);
int isstring(string c);
int splitlen(string f);
string mytolower(string s);
void reorder(map <string, int> m);
int cmp(const pair<string, int>& x, const pair<string, int>& y);
vector<string> splitt(const string &s);
vector<pair<string, int>> tVector;

//�ָ����жϲ��и��ַ���
vector<string> splitt(const string &s) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//�ҵ��ַ������׸������ڷָ�������ĸ��
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			if (isalnum(s[i])==0) {
					++i;
					flag = 0;
					break;
			}
		}

		//�ҵ���һ���ָ������������ָ���֮����ַ���ȡ����
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			if (isalnum(s[j])==0) {//isalnum()�ж���������Ƿ�Ϊ��ĸ��������
					flag = 1;
					break;
			}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}
//�Ƚ�
int cmp(const pair<string, int>& x, const pair<string, int>& y)
{
	if(x.second != y.second)
		return x.second > y.second;
	else {
		return x.first < y.first;//�ֵ���ǰ
	}
}
//����
void reorder(map <string, int> m) {
	//map <string, int>::iterator m1_temp;
	for (map<string, int>::iterator curr = m.begin(); curr != m.end(); curr++)
		tVector.push_back(make_pair(curr->first, curr->second));
	sort(tVector.begin(), tVector.end(), cmp);
}
//�ַ���תСд
string mytolower(string s) {
	int len = s.size();
	//cout << len<<endl;
	for (int i = 0; i<len; i++) {
		if (s[i] >= 'A'&&s[i] <= 'Z') {
			s[i] = tolower(s[i]);
			//s[i]+=32;//+32ת��ΪСд
			//s[i]=s[i]-'A'+'a';
		}
	}
	return s;
}
//�ַ�����
int splitlen(string f) {
	int cc = 0;
	int i = 0;
	while (f[i]!='\0') {
		cc++;
		i++;
	}
	return cc;
}
//�ж��ַ����Ƿ����Ҫ��
int isstring(string c) {
	if (isdigit(c[0]) != NULL || isdigit(c[1]) != NULL || isdigit(c[2]) != NULL || isdigit(c[3]) != NULL)
		return 0;
	else
		return 1;
}
//ͳ���ַ���
int character(char* path) {
	ifstream infile;
	infile.open(path);   //���ļ����������ļ��������� 
	char c;
	int count = 0,i = 0;
	infile >> noskipws;
	while (!infile.eof())
	{
		infile >> c;
		if (c == '\n') {
			if (ff[i] != ' '&&i!=0) {
				//cout << i << endl;
				lines++;
			}
			c = ' ';
		}
		ff += c;
		//cout << ff[i] << endl;
		count++;
		i++;
	}
	ff[i] = '\0';
	infile.close();
	count--;
	lines++;
	return count;
}
//ͳ�ƴ�Ƶ�͵�����
int word(string strr) {
	int i = 0, count = 0;
	map <string, int> m1;
	map <string, int>::iterator m1_Iter;
	vector<string> split = splitt(strr);

	for (vector<string>::size_type i = 0; i != split.size(); ++i){
		//cout << split[i] << endl;
		string key = split[i];
		if (key.size() >= 4 && isstring(key) == 1) {
			cout << "�����������ַ����ǣ�" << key << endl;
			if (m1.count(key) == 0)
			{
				count++;
				m1.insert(pair <string, int>(key, 1));
			}
			else
			{
				m1[key]++;
			}
		}
	}
	reorder(m1);
	/*
	for (m1_Iter = m1.begin(); m1_Iter != m1.end(); m1_Iter++)
	{
		string key = m1_Iter->first;
		int value = m1_Iter->second;
		//cout << "<" << key << ">" << ":" << value << endl;
	}
	*/
	return count;
}

int main(int argc,char* argv[])
{
	char* a = NULL;
	a = argv[1];
	int characters,words;
	characters = character(a);
	//cout << ff<<endl;
	ff=mytolower(ff);
	//cout << ff << endl;
	words = word(ff);
	ofstream fout("result.txt");
	fout << "characters: " << characters << endl;
	fout << "words: " << words << endl;
	fout << "lines: " << lines << endl;
	for (int i = 0; i<tVector.size(); i++)
	{
		if (i == 10)
			break;
		fout << "<" << tVector[i].first << ">" << ": " << tVector[i].second << endl;
	}
	fout.close();
	return 0;
}