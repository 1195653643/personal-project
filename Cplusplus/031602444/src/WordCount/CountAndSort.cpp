#include"CountAndSort.h"
using namespace std;

struct SortByValue {
	bool operator()(const pair<string, int> & a, const pair<string, int> & b) {
		if (a.second == b.second) {
			return a.first < b.first;
		}
		else return a.second > b.second;
	}
};

void CountAndSort(char* filemm)//ͳ�ƴ�����Ƶ
{
	map<string, int> mapp;
	string s;
	vector<int> ans;//��ָ���λ��

	ifstream f;

	f.open(filemm, ios::in);

	while (f >> s) //һ�ζ�ȡһ���ַ�������ȡ�ַ������������кͿո���Ʊ��
	{

		ans.clear();

		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] >= 65 && s[i] <= 90)
			{
				s[i] += 32;
			}
			if (s[i] < 48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i]>122)
			{
				ans.push_back(i);
			}
		}

		if (ans.size() == 0)//����ָ����Ŀ����0������ֻ��һ���ַ���
		{
			//����Ӹ÷������ĸ��ַ�������ĸ
			if ((s[0] >= 97 && s[0] <= 122) && (s[1] >= 97 && s[1] <= 122) && (s[2] >= 97 && s[2] <= 122) && (s[3] >= 97 && s[3] <= 122))
			{
				mapp[s]++;
			}
			continue;
		}

		//�������һ�����ϵķָ���
		//���жϵ�һ������Ϊ��һ��û�зָ�������ͷ���
		if ((s[0] >= 97 && s[0] <= 122) && (s[1] >= 97 && s[1] <= 122) && (s[2] >= 97 && s[2] <= 122) && (s[3] >= 97 && s[3] <= 122))
		{
			string temp(s.substr(0, ans[0]));//����ǰ�ĸ��ַ�����ĸ����ȡ
			mapp[temp]++;
		}

		for (int i = 0; i < ans.size(); i++)
		{
			//����ָ������ĸ��ַ�����ĸ
			if ((s[ans[i] + 1] >= 97 && s[ans[i] + 1] <= 122) && (s[ans[i] + 2] >= 97 && s[ans[i] + 2] <= 122) &&
				(s[ans[i] + 3] >= 97 && s[ans[i] + 3] <= 122) && (s[ans[i] + 4] >= 97 && s[ans[i] + 4] <= 122))
			{
				string temp(s.substr(ans[i] + 1, ans[i + 1] - ans[i] - 1));
				mapp[temp]++;
			}
		}
	}


	f.close();



	
	vector<pair<string, int>> v(mapp.begin(), mapp.end());//��Ƶ����
	sort(v.begin(), v.end(), SortByValue());
	
	int vecflag = 0;
		


	for (vector<pair<string, int>>::iterator vec = v.begin(); vec != v.end(); vec++)
	{
		cout << "<" << vec->first << ">: " << vec->second << endl;
		vecflag++;
		if (vecflag == 10) break;
	}

	

}