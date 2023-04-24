#pragma once

#include <string>
#include <iostream>
#include <format>
#include <conio.h>

static void Prompt(std::string text)
{
	std::cout << text << std::endl;
}

static std::string PromptWithResponse(std::string text)
{
	std::cout << text << std::endl;
	std::string response;
	std::getline(std::cin, response);
	return response;
}

static int PromptWithIntResponse(std::string text)
{
	auto const response = PromptWithResponse(text);
	int intResponse = 0;
	try
	{
		intResponse = std::stoi(response);
	}
	catch (std::invalid_argument)
	{
		Prompt(std::format("{} is not a number!", response));
	}
	return intResponse;
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