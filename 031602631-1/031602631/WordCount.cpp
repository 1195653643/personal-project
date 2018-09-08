/**************��������������WordCount******************/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include"Ccharacter.h" //�����ַ���������Character
#include"Cwords.h" //���㵥�ʸ�������Word ������Ԥ����
#include"Clines.h" //������������Line
#include"Swords.h" //ͳ������10�����ʼ����Ƶ����Wsort ��ֻ��Ҫ����Cword�ٽ�������Ϳ����˰ɣ�
int main(int argc, char * argv[])  //����windows IDE
{
	using namespace std;
	if (argc == 1) //quit if no arguments
	{
		cerr << "Usage:" << argv[0] << "filename[s]\n";
		exit(EXIT_FAILURE);
	}
	ifstream fin;
	for (int file = 1; file < argc; file++) //Ӧ��һ��ֻ��һ���ļ��ɡ�����
	{
		string f = argv[file];
		////////////////////////////////////////////////
		Character Cc(f);
		Word cw(f);
		Line cl(f);
		Wsort sw(f);
		cout << "sword success" << endl;
		////////////////////////////////////////////////
		Cc.count(); //��������ļ�������
		Cc.show(); //��ʾ���
		Cc.fwrite();
		cout << "character success" << endl;
		////////////////////////////////////////////////
		cw.count();
		cw.show();
		cw.fwrite();
		cout << "word success" << endl;
		////////////////////////////////////////////////
		cl.count();
		cl.show();
		cl.fwrite();
		cout << "line success" << endl;
		////////////////////////////////////////////////
		sw.CS();
		sw.show();
		sw.fwrite();
		cout << "sword success" << endl;
	}
	return 0;
}