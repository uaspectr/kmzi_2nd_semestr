#include "md5.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ios>
using namespace std;


int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		cout << "Error!\n Usage: ./program_name inputfile"<<endl;
		return 321;
	}


	MD5 md5; //������� ������ ������ MD5
	const char* filePath; //filePath ����� ����������� ���� � �����, �������� �������� ���������� ��������.
	ifstream infile; // ��� ����� ��������� ��������� �� �������� ����
	
	filePath = argv[1];// ����������� ���������� ���� � �����
	infile.open(filePath);// ��������� ���� �� ������
	
	if(infile)// ���� ���� ������ 
	{
		cout << "MD5 digest: ";
		md5.update(infile);// ��������� �������� � ����������� �� �������� �����
		cout << md5.toString() << endl; // ��� ����������� ��� ��������, ���������� � string � ��������� � �������.
	}
	else
	{
		cout << "input file not found" << endl; // ���� �� ������� ������� ����, ������� ��������� �� ����.
		return 123;
	}
	
	return 0;
}
