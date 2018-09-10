#include "stdafx.h"

using namespace std;

class Statistics
{
public :
	int cnum;//�ַ���
	int wnum;//������
	int lnum;//����
	vector<int>a;//������
	map<string, int> word;//��¼���ʼ���Ƶ
	void set(ifstream& in);//ͳ��
	void output(ofstream& out);//���
	int characters(ifstream& in);//ͳ���ַ���
	int	words(ifstream& in);//ͳ�Ƶ�����
	int lines(ifstream& in);//ͳ������
};

bool cmp(int a, int b)
{
	return a > b;
}
int Statistics::words(ifstream& in)//��Ƶͳ�� 
{
	string str;
	string temp;
	int flag = 0;
	int sum = 0;
	int star = 0;
	while (getline(in, str))
	{
		flag = 0;
		for (unsigned i = 0; i < str.length(); i++)//����д��ĸתΪСд��ĸ 
		{
			if (str[i] >= 'A'&&str[i] <= 'Z')
			{
				str[i] = str[i] + 32;
			}
		}
		for (unsigned j = 0; j < str.length(); j++)//��ȡ�Ϸ����ʲ�ͳ�� 
		{
			if (str[j] >= 'a'&&str[j] <= 'z')
			{
				if (flag == 0)
				{
					star = j;
				}
				flag++;
			}
			else
			{
				if (flag >= 4)
				{
					if (str[j] >= '0'&&str[j] <= '9')
					{
						if (j == str.length() - 1)
						{
							flag++;
						}
						else
						{
							flag++;
							continue;
						}
					}
					temp = str.substr(star, flag);//��ȡ�Ϸ����� 
					//cout<<"temp:"<<temp<<endl;
					if (word.count(temp))
					{
						word[temp]++;
					}
					else
					{
						word[temp] = 1;
						sum++;
					}
				}
				flag = 0;
			}
		}
	}
	in.clear();//ָ�����¶�λ���ļ�ͷ�� 
	in.seekg(0, ios::beg);
	return sum;
}
int Statistics::characters(ifstream& in)//ͳ���ַ���
{
	int num = 0;
	char ch;
	while (in.peek() != EOF)
	{
		in.get(ch);
		if (ch >= 0 && ch <= 255)
		{
			num++;
		}
	}
	in.clear();//ָ�����¶�λ���ļ�ͷ�� 
	in.seekg(0, ios::beg);
	return num;
}
int Statistics::lines(ifstream& in)	//ͳ����Ч����
{
	int line = 0;
	string str;
	while (getline(in, str))
	{
		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());//ɾ��һ���еĿո�
		str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());//ɾ��һ���е��Ʊ��
		if (str.length() > 0) //���ɾ���Ʊ���Ϳո�֮���һ�����ݻ��������ַ�������Ч��
		{

			line++;
		}
	}
	in.clear();//ָ�����¶�λ���ļ�ͷ�� 
	in.seekg(0, ios::beg);
	return line;
}
void Statistics::set(ifstream& in)//����ͳ�ƹ���
{
	cnum = characters(in);
	lnum = lines(in);
	wnum = words(in);
}
void Statistics::output(ofstream& out)//����������ָ���ĵ�
{
	out << "characters: " << cnum << endl;
	out << "words: " << wnum << endl;
	out << "lines: " << lnum << endl;
	map<string, int>::iterator it;
	for (it = word.begin(); it != word.end(); it++)
	{
		int m = (*it).second;
		a.push_back(m);
	}
	sort(a.begin(), a.end(), cmp);
	for (int i = 0; i < wnum; i++)
	{
		int m = a[i];
		for (it = word.begin(); it != word.end(); it++)
		{
			if ((*it).second == m)
			{
				out << "<" << (*it).first << "> :" << m << endl;
				(*it).second = 0;
				break;
			}
		}
	}
}
int main(int argc, char *argv[])
{
	ifstream infile;
	ofstream outfile;
	infile.open(argv[1], ios::in);
	if (infile.fail())
	{
		cout << "Open readfile failed!" << endl;
		exit(1);
	}
	outfile.open("result.txt", ios::out);
	if (outfile.fail())
	{
		cout << "Open writefile failed!" << endl;
		exit(1);
	}
	Statistics	s;
	s.set(infile);
	s.output(outfile);
	infile.close();
	outfile.close();
	system("pause");
	return 0;
}