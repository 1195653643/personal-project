#pragma once
#include <fstream>
#include <string> 
#include <unordered_map>
#include <vector>

using namespace std;

#define ORDER_WORD vector<pair<string, int>>

class FileRead
{
public:
	FileRead(string filePath);
	~FileRead();
	int getLineNum();
	int getWordNum();
	int getCrtNum();
	vector<pair<string, int>> getOrderWord();//���ش�ź�����ĵ��ʼ�����ִ���������
private:
	int lineNum;
	int wordNum;
	int crtNum;
	ifstream readFile;
	unordered_map<string, int> wordMap;//����ļ��з���Ҫ��ĵ���
	unordered_map<string, int>::iterator itor;
	vector<pair<string, int>> orderWord;//�����ŵ��ʵ�����
	void wordCount();//���ļ�������������ļ��е���
	void crtCount();//���ļ��ַ���������
	void wordPair();//���ļ��е��ʰ�Ҫ������
	/*wordPair��������ȽϺ���*/
	static bool wordPair_cmp(pair<string, int> a, pair<string, int> b);
};