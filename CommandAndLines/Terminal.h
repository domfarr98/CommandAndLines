#pragma once

#include <string>
#include <iostream>
#include <conio.h>

static void Prompt(std::string text)
{
	std::cout << text << std::endl;
}

template<typename T>
static T PromptWithResponse(std::string text)
{
	std::cout << text << std::endl;
	T response;
	std::cin >> response;
	return response;
}

static bool PromptWithYesNoResponse(std::string text)
{
	std::cout << text << std::endl;
	std::string response;
	std::cin >> response;

	auto boolResponse = false;
	for (auto validResponse = false; !validResponse;)
	{
		if (response == "y" || response == "Y" || response == "yes" || response == "Yes")
		{
			boolResponse = true;
			validResponse = true;
		}
		else if (response == "n" || response == "N" || response == "no" || response == "No")
		{
			validResponse = true;
		}
		else
		{
			std::cout << "Invalid response. Please reply with y/n:" << std::endl;
			std::cin >> response;
		}
	}
	return boolResponse;
}

static void PromptAndWait(std::string text)
{
	std::cout << text << std::endl;
	_getch();
}