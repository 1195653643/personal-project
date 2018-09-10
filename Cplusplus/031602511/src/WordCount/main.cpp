#include "FileRead.h"
#include <vector>
#include <iostream>

using namespace std;

#define READING_FILE "input.txt"
#define WRITING_FILE "result.txt"
#define ORDER_WORD vector<pair<string, int>>

int main() {
	int i = 0;
	FileRead fileRead(READING_FILE);
	ofstream fileWrite(WRITING_FILE, ios::out | ios::trunc);
	int crtNum = fileRead.getCrtNum();
	int lineNum = fileRead.getLineNum();
	int wordNum = fileRead.getWordNum();
	ORDER_WORD orderWord = fileRead.getOrderWord();
	ORDER_WORD::iterator outItor;
	if (!fileWrite) {
		cerr << WRITING_FILE << "�ļ���ʧ��!" << endl;
		exit(1);
	}
	fileWrite << "characters: " << crtNum << endl;
	fileWrite << "words: " << wordNum << endl;
	fileWrite << "lines: " << lineNum << endl;
	outItor = orderWord.begin();
	for (i = 0; i < 10 && outItor != orderWord.end(); i++, outItor++) {
		fileWrite << "<" << outItor->first << ">" << ": " << outItor->second << endl;
	}
	if (crtNum == 0) cout << READING_FILE << "�ļ��в����ڷǿհ��ַ���" << endl;
	else if (wordNum == 0) cout << READING_FILE << "�ļ��в����ڷ���Ҫ��ĵ���!" << endl;
	return 0;
}