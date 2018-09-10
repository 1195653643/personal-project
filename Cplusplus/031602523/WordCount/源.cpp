#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <regex>
#include <algorithm>
#define MAXLENGTH   101

using namespace std;


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



class Files
{
private:
	char file_name[MAXLENGTH];
	int chars_cnt;
	int words_cnt;
	int lines_cnt;
	string allwords;
public:
	Files()
	{
		file_name[0] = '\0';
		allwords = "";
		chars_cnt = 0;
		words_cnt = 0;
		lines_cnt = 1;
	}
	int get_chrcnt()
	{
		return this->chars_cnt;
	}
	void set_chrcnt(int n)
	{
		this->chars_cnt = n; return;
	}
	int get_wrdcnt()
	{
		return this->words_cnt;
	}
	void set_wrdcnt(int n)
	{
		this->words_cnt = n; return;
	}
	int get_lnecnt()
	{
		return this->lines_cnt;
	}
	void set_lnecnt(int n)
	{
		this->lines_cnt = n; return;
	}
	string get_alstring()
	{
		return this->allwords;
	}
	void set_alstring(string s)
	{
		this->allwords = s;
	}
	string get_filename()
	{
		return this->file_name;
	}
	void set_filename(char * s)
	{
		strcpy(this->file_name, s); return;
	}
};
class Char_counter
{
public:
	int char_count(istream &f, Files &fn);

};

int Char_counter::char_count(istream &f, Files &fn)
{
	char a;
	int cnt = 0;
	string temp = "";
	while (f.get(a))//�ַ���ȡ���ɹ�����ֹ
	{
		if ((a >= 32 && a <= 126) || a == '\n' || a == '\t')
			cnt++;
		temp += a;//��ÿ���ַ�����all_string
	}
	fn.set_alstring(temp);
	return cnt;
}

class Line_counter
{
public:
	int lines_counter(istream &f, Files &fn);
};

int Line_counter::lines_counter(istream &f, Files &fn)
{
	int flag = 0;
	int cnt = 0;
	string temp = fn.get_alstring();
	int len = temp.length();
	for (int i = 0; i < len; i++)
	{
		if (temp[i] >= 33 && temp[i] <= 126)//��ʾ��������Ч��
		{
			flag = 1;
			continue;
		}
		if (temp[i] == 10 && flag == 1)//����������Ч�У����ұ�����1�����з�ʱ��������1
		{
			cnt++;
			flag = 0;
		}
	}
	if (flag == 1)//���һ�����û�л��з���ҲҪ��1
		cnt++;

	return cnt;
}


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

void Word_operater::insert(string w)//�ѵ��ʲ����ϣ��
{
	int hash = ((w[0] - 96)) + ((w[1] - 96) * 26) + ((w[2] - 96) * 26 * 26);//�����ϣֵ
	node *p = new node("", 1);
	node *q = new node("", 1);
	if (this->hash_table[hash]->next == NULL)//�ձ����
	{
		p = this->hash_table[hash];
		this->hash_table[hash] = new node(w, 1);
		this->hash_table[hash]->next = p;
	}
	else//�ǿձ�
	{
		int flag = 0;
		q = p = this->hash_table[hash];
		while (p->next != NULL)//��������
		{
			if (p->name == w)//�ڱ����ҵ��õ��ʣ�����times��1
			{
				p->times++;
				flag = 1;
			}
			q = p;
			p = p->next;
		}
		if (flag == 0)//��������û���ҵ��õ��ʣ���������β�������½��
		{
			node *newnode = new node(w, 1);
			q->next = newnode;
			newnode->next = p;
		}
	}
	return;
}

int Word_operater::words_counter(ifstream &f, Files &fn)
{
	int flag = 0;
	string thisword = "";
	string temp = fn.get_alstring();
	int len = temp.length();
	int cnt = 0;
	for (int i = 0; i < len; i++)
	{
		if ((temp[i] >= 65 && temp[i] <= 90) || (temp[i] >= 97 && temp[i] <= 122))//�ҵ���һ����ĸ  �ж��ǲ��ǵ���
		{
			flag = 0;
			for (int j = i; j <= i + 3; j++)
			{
				if (temp[j] <= 64 || (temp[j] >= 91 && temp[j] <= 96) || temp[j] >= 123 || len - i < 4)
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)//����ǵ��ʾ���ȡ���ʵ�temp
			{
				thisword = "";
				for (; i < len && ((temp[i] >= 65 && temp[i] <= 90) || (temp[i] >= 97 && temp[i] <= 122) || (temp[i] >= 48 && temp[i] <= 57)); i++)
				{
					if (temp[i] >= 65 && temp[i] <= 90)
						temp[i] += 32;
					thisword += temp[i];
				}
				cnt++;
				insert(thisword);
				//cout << temp << endl;
			}
			else//������ǵ��ʾ�������һ�����ʵĵ�һ����ĸ
			{
				for (; (temp[i] >= 65 && temp[i] <= 90) || (temp[i] >= 97 && temp[i] <= 122) || (temp[i] >= 48 && temp[i] <= 57); i++) {}
			}
		}
		else if (temp[i] >= 48 && temp[i] <= 57)
		{
			for (; (temp[i] >= 65 && temp[i] <= 90) || (temp[i] >= 97 && temp[i] <= 122) || (temp[i] >= 48 && temp[i] <= 57); i++) {}
		}
	}
	fn.set_alstring(temp);
	return cnt;
}

void Word_operater::file_rank(Files &fn)//ͳ�ƴ�Ƶ
{
	int num;
	int flag = 0;//�жϳ��ִ������Ľ���ǲ��Ǳ��� 0���� 1��
	node *max, *q, *p, *front_max;
	front_max = new node("", 0);
	for (int j = 0; j < 10 && j < fn.get_wrdcnt(); j++)//����10�ι�ϣ��
	{
		max = new node("", 0);//��ʼ��max
		for (int i = 0; i <= 18279; i++)
		{
			if (this->hash_table[i]->next == NULL) continue;//�ձ�����
			else//�ǿձ�
			{
				q = p = this->hash_table[i];
				while (p->next != NULL)
				{
					if (p->times > max->times || (p->times == max->times&&p->name < max->name))
					{

						if (p == this->hash_table[i])
						{
							flag = 1;//��ʾ�õ����ڱ�ͷ
							num = i;
						}
						else flag = 0;//��ʾ�õ����ڱ���
						max = p;
						front_max = q;
					}
					q = p;
					p = p->next;
				}
			}
		}
		if (max->times != 0)
		{
			cout << "<" << max->name << ">:" << max->times << endl;//���һ�����
			//*outfile << "<" << max->name << ">:" << max->times << endl;//���һ�����
		}
		else  break;//���maxû�б��滻�����ʱ��ϣ���ǿյģ�����Ҫ���

		if (flag == 1)	this->hash_table[num] = max->next;//���Ƶ�����ĵ����ڱ��ף��滻����ָ��
		else front_max->next = max->next;//���Ƶ�����ĵ����ڱ��У�ɾ�����
	}
	return;
}





int main(int argc, char *argv[])
{
	ifstream f;
	Files file_input;

	Char_counter cc;
	Line_counter lc;
	Word_operater wo;

	file_input.set_filename(argv[1]);
	cout << file_input.get_filename() << endl;

	f.open(file_input.get_filename(), ios::in);
	if (!f.is_open())
	{
		cout << "Warning! can't open this file!" << endl;
	}

	file_input.set_chrcnt(cc.char_count(f, file_input));
	file_input.set_lnecnt(lc.lines_counter(f, file_input));
	file_input.set_wrdcnt(wo.words_counter(f, file_input));
	wo.file_rank(file_input);

	cout << file_input.get_chrcnt() << endl;
	cout << file_input.get_lnecnt() << endl;
	cout << file_input.get_wrdcnt() << endl;

	system("pause");
	return 0;
}