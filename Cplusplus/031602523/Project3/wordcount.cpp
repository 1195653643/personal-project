#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <regex>
#include <algorithm>
#define MAXLENGTH   101


//https://blog.csdn.net/nichengwuxiao/article/details/78789225
//https://www.cnblogs.com/batman425/p/3179520.html
//https://www.cnblogs.com/hexiaobao/p/8134829.html

using namespace std;


struct node { //����ṹ��
	string name;//������
	int times;//���ʳ���Ƶ��
	node *next;
	node(string n, int number) //���캯��
	{
		name = n;
		times = number;
		next = NULL;
	}
};



struct files
{
	char file_path[MAXLENGTH];
	char file_name[MAXLENGTH];
	int chars_cnt;
	int words_cnt;
	int lines_cnt;
	node *hash_table[18280];//��ϣ��

	files()
	{
		file_path[0] = '\0';
		file_name[0] = '\0';
		chars_cnt = 0;
		words_cnt = 0;
		lines_cnt = 1;
		for (int i = 0; i <= 18279; i++)//��ʼ�������ṹ��ָ������
		{
			hash_table[i] = new node("", 0);
		}
	}
};

struct words
{
	string allwords;
	int rank_cnt[11];
	string rank_name[11];
	words()
	{
		allwords = "";
		for (int i = 0; i < 11; i++)
		{
			rank_cnt[i] = 0;
			rank_name[i] = "";
		}
	}
};





int chars_counter(istream &f, files &fn, words &wn)
{
	char temp;
	int cnt = 0;
	while (!f.eof())
	{
		f.get(temp);
		if ((temp <= 126 && temp >= 32) || temp == 9 || temp == 10)
		{
			wn.allwords += temp;
			cnt++;
		}
	}

	return cnt;
}

int lines_counter(istream &f, files &fn, words &wn)
{
	int flag = 0;
	int cnt = 0;
	int len = wn.allwords.length();//�ı�����
	for (int i = 0; i < len; i++)
	{
		if (wn.allwords[i] >= 33 && wn.allwords[i] <= 126)//��ʾ��������Ч��
		{
			flag = 1;
			continue;
		}
		if (wn.allwords[i] == 10 && flag == 1)//����������Ч�У����ұ�����1�����з�ʱ��������1
		{
			cnt++;
			flag = 0;
		}
	}
	if (flag == 1)//���һ�����û�л��з���ҲҪ��1
		cnt++;

	return cnt;
}



void insert(files &fn, string w)//�ѵ��ʲ����ϣ��
{
	int hash = ((w[0] - 96)) + ((w[1] - 96) * 26) + ((w[2] - 96) * 26 * 26);//�����ϣֵ
	node *p = new node("", 1);
	node *q = new node("", 1);
	if (fn.hash_table[hash]->next == NULL)//�ձ����
	{
		p = fn.hash_table[hash];
		fn.hash_table[hash] = new node(w, 1);
		fn.hash_table[hash]->next = p;
	}
	else//�ǿձ�
	{
		int flag = 0;
		q = p = fn.hash_table[hash];
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


void file_rank(files &fn)//ͳ�ƴ�Ƶ
{
	int num;
	int flag = 0;//�жϳ��ִ������Ľ���ǲ��Ǳ��� 0���� 1��
	node *max, *q, *p, *front_max;
	front_max = new node("", 0);
	for (int j = 0; j < 10 && j < fn.words_cnt; j++)//����10�ι�ϣ��
	{
		max = new node("", 0);//��ʼ��max
		for (int i = 0; i <= 18279; i++)
		{
			if (fn.hash_table[i]->next == NULL) continue;//�ձ�����
			else//�ǿձ�
			{
				q = p = fn.hash_table[i];
				while (p->next != NULL)
				{
					if (p->times > max->times || (p->times == max->times&&p->name < max->name))
					{

						if (p == fn.hash_table[i])
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

		if (flag == 1)	fn.hash_table[num] = max->next;//���Ƶ�����ĵ����ڱ��ף��滻����ָ��
		else front_max->next = max->next;//���Ƶ�����ĵ����ڱ��У�ɾ�����
	}
	return;
}



int words_counter(ifstream &f, files &fn, words &wn)
{
	int flag = 0;
	string temp = "";
	int len = wn.allwords.length();
	int cnt = 0;
	for (int i = 0; i < len; i++)
	{
		if ((wn.allwords[i] >= 65 && wn.allwords[i] <= 90) || (wn.allwords[i] >= 97 && wn.allwords[i] <= 122))//�ҵ���һ����ĸ  �ж��ǲ��ǵ���
		{
			flag = 0;
			for (int j = i; j <= i + 3; j++)
			{
				if (wn.allwords[j] <= 64 || (wn.allwords[j] >= 91 && wn.allwords[j] <= 96) || wn.allwords[j] >= 123 || len - i < 4)
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)//����ǵ��ʾ���ȡ���ʵ�temp
			{
				temp = "";
				for (; i < len && ((wn.allwords[i] >= 65 && wn.allwords[i] <= 90) || (wn.allwords[i] >= 97 && wn.allwords[i] <= 122) || (wn.allwords[i] >= 48 && wn.allwords[i] <= 57)); i++)
				{
					if (wn.allwords[i] >= 65 && wn.allwords[i] <= 90)
						wn.allwords[i] += 32;
					temp += wn.allwords[i];
				}
				cnt++;
				insert(fn,temp);
				//cout << temp << endl;
			}
			else//������ǵ��ʾ�������һ�����ʵĵ�һ����ĸ
			{
				for (; (wn.allwords[i] >= 65 && wn.allwords[i] <= 90) || (wn.allwords[i] >= 97 && wn.allwords[i] <= 122); i++) {}
			}
		}
		else if (wn.allwords[i] >= 48 && wn.allwords[i] <= 57)
		{
			for (; (wn.allwords[i] >= 65 && wn.allwords[i] <= 90) || (wn.allwords[i] >= 97 && wn.allwords[i] <= 122) || (wn.allwords[i] >= 48 && wn.allwords[i] <= 57); i++) {}
		}
	}

	return cnt;
}





int main(int argc, char *argv[])
{
	ifstream f;
	files file_input;
	words word;
	


		
	strcpy(file_input.file_name, argv[1]);
	cout << file_input.file_name << endl;

	f.open(file_input.file_name, ios::in);
	if (!f.is_open())
	{
		cout << "Warning! can't open this file!" << endl;
	}

	file_input.chars_cnt = chars_counter(f, file_input, word);
	file_input.lines_cnt = lines_counter(f, file_input, word);
	file_input.words_cnt = words_counter(f, file_input, word);
	file_rank(file_input);
	
	cout << file_input.chars_cnt << endl;
	cout << file_input.lines_cnt << endl;
	cout << file_input.words_cnt << endl;

	system("pause");
	return 0;
}
