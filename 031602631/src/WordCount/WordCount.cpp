/**************��������������WordCount******************/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include"Ccharacter.h" //�����ַ���������Character
#include"Cwords.h" //���㵥�ʸ�������Word ������Ԥ����
#include"Clines.h" //������������Line
#include"Swords.h" //ͳ������10�����ʼ����Ƶ����Wsort ��ֻ��Ҫ����Cword�ٽ�������Ϳ����˰ɣ�
/////////////////////////////////////////////////////////
//int main(int argc, char * argv[])  //����windows IDE
////////////////////////////////////////////////////////
int main()
{
	using namespace std;


	string f = "test.txt";
	for (int i = 0; i < 10000; i++) {
		/******************************************************
		if (argc == 1) //quit if no arguments
		{
			cerr << "Usage:" << argv[0] << "filename[s]\n";
			exit(EXIT_FAILURE);
		}
		if (argc > 2)
		{
			cerr << "Input too many filenames.\n";
			exit(EXIT_FAILURE);
		}

		for (int file = 1; file < argc; file++)  //���ڶ���ļ��Ҳ��ý��ܵ�̬��
		{
			string f = argv[file];
			////////////////////////////////////////////////
		*********************************************************/

		Character Cc(f);
		Word cw(f);
		Line cl(f);
		Wsort sw(f);
		////////////////////////////////////////////////
		Cc.count(); //��������ļ�������
		Cc.show(); //��ʾ���
		Cc.fwrite();
		////////////////////////////////////////////////
		cw.count();
		cw.show();
		cw.fwrite();
		////////////////////////////////////////////////
		cl.count();
		cl.show();
		cl.fwrite();
		////////////////////////////////////////////////
		sw.CS();
		sw.show();
		sw.fwrite();
		//	}
	}
	return 0;
}