#pragma once

#include <string>
#include <iostream>
#include <conio.h>

void Prompt(std::string text)
{
	std::cout << text << std::endl;
}

template<typename T>
T PromptWithResponse(std::string text)
{
	std::cout << text << std::endl;
	T response;
	std::cin >> response;
	return response;
}

void PromptAndWait(std::string text)
{
	std::cout << text << std::endl;
	getch();
}