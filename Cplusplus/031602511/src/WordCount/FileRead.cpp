#include "FileRead.h"
#include <iostream>
#include <algorithm>

/*ʹ�ļ�����Ŀ���ļ���������*/
FileRead::FileRead(string filePath) {
	readFile.open(filePath, ios::in);
	if (!readFile) {
		cerr << filePath << "�ļ������ڣ�" << endl;
		exit(1);
	}
	lineNum = 0;
	wordNum = 0;
	crtNum = 0;
}

FileRead::~FileRead() {
	readFile.close();
}

/*�����ļ��е��������ַ���������*/
void FileRead::crtCount() {
	readFile.clear(ios::goodbit);
	readFile.seekg(ios::beg);//ÿ�δ�ͷ��ȡ�ļ�
	char c;
	int _lineNum = 0;
	int _crtNum = 0;
	int flag = 0;
	readFile >> noskipws;//�����Կո�
	while (readFile.get(c)) {
		_crtNum++;
		if (c != '\n' && c != ' ' && flag == 0) flag++;
		else if (c == '\n' && flag != 0) {
			_lineNum++;
			flag = 0;
		}
	}
	if (flag != 0) _lineNum++;

	/*��������ַ������������浽��Ӧ������*/
	crtNum = _crtNum;
	lineNum = _lineNum;
}

/*�����ļ����������ĵ��������������ʼ�����ִ������浽unorder_map���͵�������*/
void FileRead::wordCount() {
	readFile.clear(ios::goodbit);
	readFile.seekg(0, ios::beg);//ÿ�δ�ͷ��ȡ�ļ�
	int _wordNum = 0;
	int alpLength = 0;
	int start = 0;//���ڷָ��
	char str[100];
	string word;//��ʱ�洢����

	char c;
	readFile >> noskipws;
	while (readFile.get(c)) {
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
			if ((c >= '0' && c <= '9') && (alpLength < 4)) {
				alpLength = 0;
				start = 0;
				continue;
			}
			else if (!(c >= '0' && c <= '9')) {
				if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
				alpLength++;
			}
			str[start++] = c;
		}
		else if (start > 3) {//�����ָ����ҵ������ĸ�������ĸ��ͷʱ��������
			_wordNum++;			
			//cout << alpLength << ", " << start << "   ";		
			alpLength = 0;
			str[start] = 0;
			start = 0;
			word = str;
			itor = wordMap.find(word);
			if (itor != wordMap.end()) {
				(itor->second)++;
			}
			else {
				wordMap[word] = 1;
			}
			//---------------------------------------------------------------------------
			//cout << word << endl;
		}
		else {
			alpLength = 0;
			start = 0;
		}
	}
	if (start > 3) {//�ļ�ĩβ�ĵ����޷�����֮ǰ��whileѭ����Ҫ�����ж�
		_wordNum++;
		str[start] = 0;
		start = 0;
		word = str;
		itor = wordMap.find(word);
		if (itor != wordMap.end()) {
			(itor->second)++;
		}
		else {
			wordMap[word] = 1;
		}
	}

	wordNum = _wordNum;
}

/*�����ʰ�Ҫ������󱣴浽orderWord������*/
void FileRead::wordPair() {
	/*ͨ����������map�е�pair���ݸ��Ƶ�vector��*/
	for (itor = wordMap.begin(); itor != wordMap.end(); itor++) {
		orderWord.push_back(make_pair(itor->first, itor->second));
	}
	/*ͨ��sort������vector�еĵ��ʰ���ĿҪ������*/
	sort(orderWord.begin(), orderWord.end(), &wordPair_cmp);
}

int FileRead::getCrtNum() {
	if (crtNum == 0 && lineNum == 0) crtCount();
	return crtNum;
}

int FileRead::getLineNum() {
	if (crtNum == 0 && lineNum == 0) crtCount();
	return lineNum;
}

int FileRead::getWordNum() {
	if (wordMap.empty()) wordCount();
	return wordNum;
}

/*���ش�ź�����ĵ��ʼ�����ִ���������*/
vector<pair<string, int>> FileRead::getOrderWord() {
	if (wordMap.empty()) wordCount();
	if (orderWord.empty()) wordPair();
	return orderWord;
}