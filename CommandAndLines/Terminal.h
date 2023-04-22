#pragma once

#include <string>
#include <iostream>

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
