#include "stdafx.h"
#include "work_2.h"
using namespace std;



int main(int argc, char *argv[])
{
	File fnew;                 //�����ļ�ģ��
	Words wnew;                //���Ƶ���ģ��
	Wordnode *log[HASH_LENGTH] = { NULL };  //��ϣɢ��ָ������
	int i;
	if (argc == 1)               //�����Ϸ��Լ��
	{
		cout << "Wrong parameters!" << endl;
		system("pause");
		return 0;
	}
	strcpy_s(fnew.file_name, argv[1]);      //��ȡ�ļ���
	//cout << fnew.file_name << endl;
	ifstream f;
	f.open(fnew.file_name, ios::in);		//���ļ�
	if (!f.is_open())						//����ļ��Ƿ����
	{
		cout << "can't open this file!" << endl;
	}
	fnew.count_chars = C_chars(f, fnew, wnew);	//�����ַ���(����)
	fnew.count_words = C_words(f, wnew, log);	//���㵥����(�����ϣ�ڵ�)

	//cout << "chars = " << fnew.count_chars << "," << "lines = " << fnew.count_lines<<","<<"words = "<<fnew.count_words<<endl;
	rank_word(log, wnew);						//��Ƶ����

	ofstream fo;
	fo.open("result.txt", ios::out);			//����ļ�
	if (!fo.is_open())							//����ļ��Ϸ��Լ��
	{
		cout << "can't output the file!" << endl;
	}
	fo << "characters: " << fnew.count_chars << "\n";	//����������
	fo << "words: " << fnew.count_words << "\n";
	fo << "lines: " << fnew.count_lines << "\n";
	for (i = 1; i < 11; i++)
	{
		if (wnew.count_rank[i] != 0)			
		{
			fo << "<" << wnew.word_rank[i] << ">: " << wnew.count_rank[i] << "\n";
		}
		else
			break;
	}
	f.close();
	fo.close();								//�ر��ļ�
	cout << "WordCount complete!" << endl;
	system("pause");
	return 0;
}