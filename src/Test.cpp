#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "IOHelper.h"
#include "Test.h"

int sizeX = 0;
int sizeY = 0;

void print(const std::string& lol)
{
	std::cout << lol << "\n";
}

void print(int lol)
{
	std::cout << +lol << "\n";
}

void onExit()
{
	system("stty echo");
	system("stty icanon");

	//std::cout << "\e[?1000l";
}

void setupTerminal()
{
	signal(SIGWINCH, do_resize);

	system("stty -echo");
	system("stty -icanon");
	//system("clear");

	//std::cout << "\e[?1000h";

	std::atexit(onExit);
}

void do_resize(int dummy)
{
	int* dimension = getScreenSize();
	sizeX = dimension[1];
	sizeY = dimension[0];

	drawFrame();

	setCursor(3,4);
	std::cout << "Dimension:";
	setCursor(3,5);
	std::cout << "Y: " << +dimension[0] << "\n";
	setCursor(3,6);
	std::cout << "X: " << +dimension[1] << "\n";
}

void drawFrame()
{
	setCursor(0,0);
	for(int i = 0; i < sizeX; i++)
	{
		std::cout << "#";
	}
	std::cout << "\n";

	for(int i = 0; i < sizeY - 2; i++)
	{
		std::cout << "#";
		for(int j = 0; j < sizeX - 2; j++)
		{
			std::cout << " ";
		}
		std::cout << "#\n";
	}

	for(int i = 0; i < sizeX; i++)
	{
		std::cout << "#";
	}
}

int main()
{
	setupTerminal();
	
	print("Starting.");
	enterScreenBuffer();
	do_resize(0);

	std::string ansiParsingTmp;
	std::string buffer = "";

	char lol = 0;
	while(lol != 4)
	{
		std::cin >> lol;

		//Ignore ANSI in a stupid way.
		if(lol == '\e')
		{
			continue;
		}

		//Print last output
		setCursor(3, 2);
		std::cout << lol << "  - " << +lol;

		//Print way too big buffer.
		setCursor(3, 9);
		buffer += lol;
		std::cout << buffer;
	}

	leaveScreenBuffer();
	//After leaving the mode, go to any valid cursor position
	setCursor(999, 999);
	print(" Ending.");
	return 0;
}
