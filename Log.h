#pragma once
#include <iostream>
#include <stdio.h>
class Log
{
public:
	//static void trace(wchar_t * message); // � ��� ���������
	static void trace(char * message); // ��� ������ 4 �������
	
	Log();
	~Log();
};

