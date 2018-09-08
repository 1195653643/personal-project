#include<iostream>
#include<fstream>
#include<string>
#include "Ccharacter.h"
using namespace std;

Character::Character(string file)
{
	finname = file;
	number = 0;
	foutname = "result.txt";
}

void Character::count()
{
	ifstream fin;
	fin.open(finname);
	if (!fin.is_open())
	{
		cerr << "Could not open" << finname << endl;
		fin.clear();
	}
	fin >> noskipws;
	char c;
	fin >> c;
	while (!fin.eof())
	{
		cout << c;
		++number;  /////////////��ʱ��ûʵ�����ĵ��޳���������д��/////////////////
		fin >> c;
	}
	fin.close();
}

void Character::show()
{
	cout << "characters:" << number << endl;
}

void Character::fwrite()
{
	ofstream fout;
	fout.open(foutname, ios::out);
	if (!fout.is_open())
	{
		cerr << "Cant't open" << foutname << endl;
		exit(EXIT_FAILURE);
	}
	fout << "characters:" << number << endl;
	fout.close();
}