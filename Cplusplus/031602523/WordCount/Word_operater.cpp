#include "head.h"

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

