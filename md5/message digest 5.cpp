#include "stdafx.h"
#include "MD5.h"
#include <iostream>
#include <Windows.h>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	MD5 md5; //создаем объект класса MD5
	string filePath; //filePath будем присваивать путь к файлу, дайджест которого необходимо получить.
	ifstream infile; // тут будет храниться указатель на открытый файл
	
	filePath = "1.txt";// присваиваем переменной путь к файлу
	infile.open(filePath, std::ios_base::in || std::ios_base::binary);// открываем файл на чтение
	
	if(infile.is_open())// если файл открыт 
	{
		cout << "MD5 digest: ";
		md5.update(infile);// обновляем контекст в зависимости от входного файла
		cout << md5.toString() << endl; // тут вычисляется сам дайджест, приводится к string и выводится в консоль.
	}
	else
	{
		cout << "input file not found" << endl; // если не удалось открыть файл, выводим сообщение об этом.
	}
	
	system("pause");
	return 0;
}
