#include <iostream>

#include "IOHelper.h"

void lol()
{
	std::cout << "lol";
}

void setCursor(int x, int y)
{
	std::cout << "\e[" << y << ";" << x << "H";
}

int* getScreenSize()
{
	int* dimension = (int*) malloc(2);
	char* ret = getCommandFeedbackLine("stty size");

	int num = 0;
	char* c;
	for(c = ret; *c != '\0'; c++)
	{
		if(*c == ' ')
		{
			dimension[0] = num;
			num = 0;
		}
		else
		{
			int tmp = *c - '0';
			num *= 10;
			num += tmp;
		}
	}
	dimension[1] = num;

	return dimension;
}

void enterScreenBuffer()
{
	//Enter screen buffer.
	system("tput smcup");
}

void leaveScreenBuffer()
{
	//Leave screen buffer.
	system("tput rmcup");
}

char* getCommandFeedbackLine(const std::string& command)
{
	FILE *fp;
	int amount = sizeof(char) * 1025;
	char* path = (char*) malloc(amount);

	fp = popen(command.c_str(), "r");

	if(fp == NULL) {
		std::cout << "NOPE\n";
		return NULL;
	}

	while(fgets(path, amount, fp) != NULL)
	{
		//std::cout << ">" << path << "<\n";
		
		char * c;
		for(c = path; *c != '\0'; c++) {
			//std::cout << "\"" << *c << "\" - " << +*c << "\n";
			if(*c == 10)
			{
				*c = '\0';
			}
		}
		pclose(fp);
		return path;
	}

	pclose(fp);
	return NULL;
}