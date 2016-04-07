#include "Log.h"


using namespace std;
FILE	*f = fopen("log.txt", "wb"); // открыть 1 раз 
void Log::trace(char* message)
{
	
	//FILE * f = fopen("log.txt", "wb"); // так открывает лог каждый раз файл заного и все стирает - нужен ключ чтобы дописывать а не переписывать (или не открывать сто раз по trace->
	//fwrite(message, sizeof(char), sizeof(message), f); // так только 4 символа
	//fwrite(message, sizeof(message +1 ), sizeof(message), f);
	
	//message = new char[256];
	cout << message << endl;
	//fwrite(message, sizeof(char), strlen(message), f); // а так вроде работает
	
	fwrite(message, strlen(message), 1, f);
	//fwrite("\n", 1, 1, f);
	//cout << message << '\n' << endl;
	
	//fclose(f);
	//delete[] message;
	
}

Log::Log()
{
	//f = fopen("log.txt", "wb");
}


Log::~Log()
{
	fclose(f);
}
