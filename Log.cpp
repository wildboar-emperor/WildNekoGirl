#include "Log.h"


using namespace std;
FILE	*f = fopen("log.txt", "wb"); // ������� 1 ��� 
void Log::trace(char* message)
{
	
	//FILE * f = fopen("log.txt", "wb"); // ��� ��������� ��� ������ ��� ���� ������ � ��� ������� - ����� ���� ����� ���������� � �� ������������ (��� �� ��������� ��� ��� �� trace->
	//fwrite(message, sizeof(char), sizeof(message), f); // ��� ������ 4 �������
	//fwrite(message, sizeof(message +1 ), sizeof(message), f);
	
	//message = new char[256];
	cout << message << endl;
	//fwrite(message, sizeof(char), strlen(message), f); // � ��� ����� ��������
	
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
