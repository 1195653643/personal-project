#include<iostream>
#include<string>
#include <fstream>
using namespace std;
int main(int argc,char* argv[])
{
	char* a = NULL;
	a = argv[1];
	//cout << a;
	ifstream infile;
	infile.open(a);   //���ļ����������ļ��������� 
	//assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

	string s;
	while (getline(infile, s))
	{
		cout << s << endl;
	}
	infile.close();
	
	return 0;
}