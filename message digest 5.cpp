#include "stdafx.h"
#include "MD5.h"
#include <iostream>
#include <Windows.h>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	MD5 md5; //������� ������ ������ MD5
	string filePath; //filePath ����� ����������� ���� � �����, �������� �������� ���������� ��������.
	ifstream infile; // ��� ����� ��������� ��������� �� �������� ����
	
	filePath = "1.txt";// ����������� ���������� ���� � �����
	infile.open(filePath, std::ios_base::in || std::ios_base::binary);// ��������� ���� �� ������
	
	if(infile.is_open())// ���� ���� ������ 
	{
		cout << "MD5 digest: ";
		md5.update(infile);// ��������� �������� � ����������� �� �������� �����
		cout << md5.toString() << endl; // ��� ����������� ��� ��������, ���������� � string � ��������� � �������.
	}
	else
	{
		cout << "input file not found" << endl; // ���� �� ������� ������� ����, ������� ��������� �� ����.
	}
	
	system("pause");
	return 0;
}
