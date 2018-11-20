#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "IOHelper.h"
#include "Test.h"

//### Variables ###
//Last measured size of the terminal.
int sizeX = 0;
int sizeY = 0;

//Input buffer:
std::string buffer = "";

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

	//Print last output:
	setCursor(3, 2);
	std::cout << "Control + D to exit.";

	//Print dimension:
	setCursor(3,4);
	std::cout << "Dimension:";
	setCursor(3,5);
	std::cout << "X: " << +sizeX << "\n";
	setCursor(3,6);
	std::cout << "Y: " << +sizeY << "\n";
	
	//Print buffer (scrollable):
	int pointer = 8;
	for(int i = buffer.length() - 1; i >= 0; i--)
	{
		setCursor(3, pointer);
		std::cout << buffer.c_str()[i] << "  - " << +buffer.c_str()[i];

		if(++pointer > sizeY - 2)
		{
			break;
		}
	}
}

int main()
{
	setupTerminal();
	
	print("Starting.");
	enterScreenBuffer();
	do_resize(0);

	std::string ansiParsingTmp;

	char lastInput = 0;
	while(lastInput != 4)
	{
		std::cin >> lastInput;

		/*
		//Ignore ANSI in a stupid way.
		if(lol == '\e')
		{
			continue;
		}
		*/

		buffer += lastInput;
		drawFrame();
	}

	leaveScreenBuffer();
	//After leaving the mode, go to any valid cursor position
	setCursor(999, 999);
	print(" Ending.");
	return 0;
}
