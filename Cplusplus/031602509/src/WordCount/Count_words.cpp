#include "work_2.h"
#include "stdafx.h"

int C_words(istream &fl, Words &wn, Wordnode **l)
{
	int count = 0;
	regex pattern("[a-zA-Z]{4}[a-zA-Z0-9]*");		//�趨������ʽģ��
	smatch result;									//smatch����string���
	//cout << regex_search(wn.all_string, result, pattern)<<endl;
	string::const_iterator start = wn.all_string.begin();	//�ַ�����ʼ������
	string::const_iterator end = wn.all_string.end();		//�ַ���ĩβ������
	string temp_str;
	while (regex_search(start, end, result, pattern))		//ѭ������ƥ��ģ��ĵ���
	{
		//cout<<"successfully match";
		temp_str = result[0];
		transform(temp_str.begin(), temp_str.end(), temp_str.begin(), ::tolower);//ת��ΪСд����
		hash_insert(l, temp_str);							//��ϣ�ڵ����
		//cout << temp_str<<" ";
		count++;
		start = result[0].second;							//�����һ����
	}
	//cout << endl;
	return count;
}