#include<bits/stdc++.h>
using namespace std;

map<string, int> M;

bool cmp(pair<string, int> a, pair<string, int> b)
{
	return a.second > b.second;
	return a.first > b.first;
}

int CountChar(char *filename)//ͳ���ַ��� 
{
	int sum = 0;
	ifstream file;
	file.open(filename);
	char ch;
	while ((ch=file.get())!=EOF )
	{
		sum++;
	}
	file.close();
	return sum;
}

int CountLines(char *filename)//ͳ������ 
{
	ifstream file;
	file.open(filename);
	string s;
	int sum = 0;
	while (getline(file, s)) 
	{
		if(s!="\0")//������������ 
		sum++;
	}	
	file.close();

	return sum;
}

int CountWords(char *filename)//ͳ�Ƶ����� 
{
	ifstream file;
	file.open(filename);
	string s;
	int sum = 0;
	regex r("\\b[a-zA-Z]{4}[a-zA-Z0-9]*", regex::icase);
	while (file>>s) {
		smatch m;		
		while (regex_search(s, m, r)) {//ƥ�����������ʽ�ĵ��� 
			sum++;
			s = m.suffix().str();
		}
		}
	file.close();

	return sum;
}

void topten(char *filename)//Ƶ����ߵ�ʮ������ 
{
	ifstream file;
	file.open(filename);
	string s;
	regex r("\\b[a-zA-Z]{4}[a-zA-Z0-9]*", regex::icase);
	while (file>>s) {
		for(int i=0;i<s.size();i++)
		{
			if(s[i]<='Z'&&s[i]>='A') s[i]=s[i]+32;//�ɴཫ���е���ĸת����Сд 
		}
		smatch m;		
		while (regex_search(s, m, r)) {
		M[m[0]]++;
		s = m.suffix().str();
		}
	}
	file.close();
}


int main()
{	
	ofstream fileOutput;
	char filename[105];
	cout << "input the filename: ";
	//cin >> filename;
	filename="test.txt" ;
	fileOutput.open("result.txt",ios::app);
  	fileOutput<<"characters: " << CountChar(filename) << endl;
  	fileOutput<<"lines: " << CountLines(filename) << endl;
  	fileOutput<<"words: "<<CountWords(filename)<<endl;
	topten(filename);
	int count=10;
	vector<pair<string, int> > ans;
	for(auto u : M) {
		ans.push_back(u);
	}
	sort(ans.begin(),ans.end(),cmp);
	for(auto u : ans)
	{
		if(count)  fileOutput<< u.first << " " << u.second << endl;
		else break;
	}
	return 0;
}
