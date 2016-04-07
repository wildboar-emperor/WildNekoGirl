#pragma once
#include <iostream>
#include <stdio.h>
class Log
{
public:
	//static void trace(wchar_t * message); // а так билеберда
	static void trace(char * message); // так только 4 символа
	
	Log();
	~Log();
};

