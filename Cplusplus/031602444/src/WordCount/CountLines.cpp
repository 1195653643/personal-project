#include"CountLines.h"

using namespace std;

int CountLines(char* filemm)//ͳ����Ч����
{
	int lines = 0;
	char c;
	char lastline = '\0';
	
	ifstream f;

	f.open(filemm, ios::in);

	while (f.get(c))
	{
		
		if (lastline != '\n'&&c == '\n')
		{
			lines++;
		}
		if (lastline == '\n' && (c == '\t' || c == ' '))
		{
			lastline = '\n';
		}
		else
		{
			lastline = c;
		}
	}


	f.close();

	if ((c == '\t' || c == ' ') && (lastline == '\t' || lastline == ' '))
	{
		lastline = c;
	}
	//����ı����һ���ַ��ǻ��з�����ǰһ���ַ��ǻ��з���ǰ�ַ��ǿո�Ҫ��ȥһ��
	else if (c == '\n' || (lastline = '\n' && (c == '\t' || c == ' ')))
	{
		lines--;
	}

	lines++;


	return lines;

}