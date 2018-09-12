#include"CountWords.h"
#include"Sort.h"


int CountWords(string filename)
{
	const char *k;
	int i, sign = 0, mm = 0;
	ifstream file(filename.c_str());      //�ַ���ȡ�ļ� 
	string  temp;
	unordered_map<string, int> ttmap;   //ʹ��unordered_map��Ϊ��Ч����ײ�Ϊhash����map�Ǻ������Ч�ʶ�����Ȼ��ǰ�߸���~

	while (file >> temp)
	{
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);  //���ȣ����ļ�����תΪСд���Ӷ�������ĿҪ��Ҳ�����������							
		k = temp.c_str();
		sign = 0;
		if (temp.length() >= 4)
		{
			for (i = 0; i < 4; i++)
			{
				if (k[i] <= 'z'&&k[i] >= 'a')
					sign += 1;

			}
			if (sign == 4)                      //���������Ϊ���ʵ�������sign=4������ʾ��ǰ�ĸ��ַ�Ϊ��ĸ��
			{
				if (ttmap[temp] == 0)
					mm++;
				ttmap[temp]++;                //ͨ��Keyֵ���˴�Ϊstring�������ġ�hash��������value�����ۼ���ĸ��Ŀ��+1��
			}
		}
	}
	return mm;
}