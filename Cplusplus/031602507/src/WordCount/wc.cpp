/********************************************************************************
* @File name: wc.cpp
* @Author: ChenYuXin
* @Version: 1.0
* @Date: 2018-09-07
* @Description: Implementing basic functions
********************************************************************************/


#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<regex>
#include<map>
#include<algorithm>
using namespace std;


bool IsLetter(string::iterator it) {
	if ((*it >= 65 && *it <= 90) || (*it >= 97 && *it <= 122)) {
		return true;
	}
	else {
		return false;

	}
}
bool IsDigit(string::iterator it) {
	if (*it >= 48 && *it <= 57) {
		return true;
	}
	else {
		return false;
	}
}



int main(int argc, char *argv[]) {
	int lineCount = 0;     //����
	int characterCount = 0;//�ַ���
	int wordCount = 0;     //������
	map<string, int> wordMap;
	vector<string> lineBuffer;
	string tempStr;
	if (argc == 2) {
		//-------------------------------------------------------------------------
		ifstream rf(argv[1],ios::in);
		if (!rf) {
			cout << "Open File Fail!1" << endl;
			//system("pause");
			return 0;
		}
		else {
			while (rf.get() != EOF) {
				characterCount++;
			}
		}
		//-------------------------------------------------------------------------



		//-------------------------------------------------------------------------
		rf.clear();
		rf.seekg(0, ios::beg);
		if (!rf) {
			cout << "Open File Fail!" << endl;
			//system("pause");
			return 0;
		}
		else {
			while (getline(rf, tempStr)) {
				lineBuffer.push_back(tempStr);
			}
			rf.close();
			for (int i = 0; i != lineBuffer.size(); i++) {
				bool flag = false;
				//��ÿһ������ַ�����
				for (string::iterator it = lineBuffer[i].begin(); it != lineBuffer[i].end(); it++) {
					//�ж��Ƿ�Ϊ����
					if (*it > 32 && flag == false) {
						flag = true;
						lineCount++;
					}
					//�������ַ�����ĸ���ж��Ƿ�Ϊһ�����ʵĿ�ͷ
					if (IsLetter(it)) {
						string  tempWord;
						int tempCharCount = 0;
						for (string::iterator cursor = it; cursor != lineBuffer[i].end(); cursor++) {
							//����ĸδ��4���ҵ�ǰ�ַ�Ϊ��ĸʱ�������ж���һ���ַ���������ַ���ʱ����
							if (tempCharCount < 4 && IsLetter(cursor)) {
								tempCharCount++;
								tempWord += *cursor;
							}
							//����ĸδ��4��ʱ�ҵ�ǰ�ַ�������ĸʱ��˵������ַ���ǰ����ĸ�����ǵ��ʵ�һ����
							else if (tempCharCount < 4 && !IsLetter(cursor)) {
								it = cursor;
								tempWord = "";
								break;
							}
							//����ĸ��4��ʱ�ҵ�ǰ�ַ�����ĸ��������ʱ��˵������ַ���ǰ���ǵ��ʵ�һ���֣���������ַ���
							else if (tempCharCount >= 4 && (IsLetter(cursor) || IsDigit(cursor))) {
								tempCharCount++;
								tempWord += *cursor;
							}
							//����ĸ��4��ʱ�ҵ�ǰ�ַ�������ĸҲ��������ʱ��˵����������Ѿ�����
							else if (tempCharCount >= 4 && !IsLetter(cursor) && !IsDigit(cursor)) {
								it = cursor;
								transform(tempWord.begin(), tempWord.end(), tempWord.begin(), ::tolower); //ת��ΪСд��ĸ
								pair<map<string, int>::iterator, bool> ret = wordMap.insert(make_pair(tempWord, 1));
								if (!ret.second)
									++ret.first->second;
								tempWord = "";
								wordCount++;
								break;
							}
						}
						//��һ�����ʴ�����ĩʱ
						if (tempWord.length() >= 4) {
							transform(tempWord.begin(), tempWord.end(), tempWord.begin(), ::tolower); //ת��ΪСд��ĸ
							pair<map<string, int>::iterator, bool> ret = wordMap.insert(make_pair(tempWord, 1));
							if (!ret.second)
								++ret.first->second;
							tempWord = "";
							wordCount++;
							break;
						}
					}
				}
			}
		}
		//-------------------------------------------------------------------------


		//-------------------------------------------------------------------------
		ofstream wf("result.txt",ios::out);
		wf<< "characters:" << characterCount <<endl << "words: "<< wordCount << endl << "lines:" << lineCount << endl;
		vector<pair<string,int> > wordVector;
		for (map<string, int>::iterator it = wordMap.begin(); it != wordMap.end(); it++) {
			wordVector.push_back(make_pair(it->first, it->second));
		}
		for (int i = 0;i != wordVector.size() && i < 10; i++) {
			int maxFrequency = 0;
			vector<pair<string, int> >::iterator maxFrequencyWord;
			for (vector<pair<string, int> >::iterator it = wordVector.begin(); it != wordVector.end(); it++) {
				if (it->second > maxFrequency) {
					maxFrequency = it->second;
					maxFrequencyWord = it;
				}
			}
			if (i == 0) {
				wf << "<" << maxFrequencyWord->first << ">:" << maxFrequencyWord->second;
			}
			else {
					wf << endl << "<" << maxFrequencyWord->first << ">:" << maxFrequencyWord->second;
			}
			maxFrequencyWord->second = -1;
		}
		cout << "Output Completed" << endl;
		wf.close();
		//-------------------------------------------------------------------------
	}
	else {
		cout << "Wrong Parameter";
		//system("pause");
		return 0;
	}

	//system("pause");
	return 0;
}