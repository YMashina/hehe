#include "pch.h"
#include <iostream>
#include <thread>
#include <string>
#include <vector>

class KnuthMorrisPrattOptimized
{
public:
	static std::vector<size_t> find(const std::string& text, const std::string& pattern);
};

std::vector<size_t> prefix_function(const std::string& text) {

	std::cout << "--calculation of prefix function--" << std::endl;
	std::cout << "prefix function value for the 1st character: '" << text.front() << "' = 0" << std::endl;

	std::vector<size_t> result(text.length());
	for (size_t i = 1; i < text.length(); ++i)
	{

		std::cout << "current character: '" << text[i] << "' (index i = " << i << ")" << std::endl;

		// by default, result is filled with zeros
		size_t j = result[i - 1];

		std::cout << "last known prefix-function value j: " << j << std::endl;

		// осуществляем возврат по известным значениям префикс функции
		while (j > 0 && text[i] != text[j])
		{
			std::cout << "j="<<j<<" is larger than 0, and ";
			std::cout << "s[i=" << i << "]" << " = '" << text[i] << "' isn't equal to s[j=" << j << "] = '" << text[j] << "', therefore j is decremented: j = ";

			j = result[j - 1];
			std::cout << j << std::endl;
		}
		// увеличиваем значение префикс функции на единицу
		if (text[i] == text[j])
		{
			++j;

			std::cout <<"text[i="<<i<<"]"<< " = '"<< text[i] <<"' is equal to "<<"text[j="<<j-1<<"] = '"<<text[j-1]<<"', therefore j is incremented: j = " << j << std::endl;

		}

		std::cout << "prefix-function value found: " << j << std::endl << std::endl;

		result[i] = j;
	}
	
	std::cout << "--calculation of prefix-function complete--" << std::endl;

	return result;
}

std::vector<size_t> KnuthMorrisPrattOptimized::find(const std::string& text, const std::string& pattern)
{
	std::vector<size_t> entries;

	size_t p = pattern.length();
	size_t t = text.length();

	if (p > t || p == 0)
		return entries;

	std::vector<size_t> prefix = prefix_function(pattern);

	std::cout << "prefix-function values: " << std::endl;
	for (size_t i = 0; i < pattern.length(); ++i)
		std::cout << pattern[i] << " ";
	std::cout << std::endl;
	for (size_t i = 0; i < prefix.size(); ++i)
		std::cout << prefix[i] << " ";
	std::cout << std::endl;


	for (size_t i = 0, q = 0; i < t; ++i)
	{
		while (true)
		{
			if (text[i] == pattern[q])
			{
				++q;
				if (q == p)
					entries.push_back(i + 1 - p);
				break;
			}
			if (q == 0) //so that pattern's siterator wouldn't be incremented unless a potential entry is present
				break;
			q = prefix[q - 1];
		}
	}

	return entries;
}

int main() {
	std::string pattern;
	std::cin >> pattern;

	std::string text;
	std::cin >> text;

	std::vector<size_t> entries = KnuthMorrisPrattOptimized::find(text, pattern);

	// no entries found
	if (entries.empty())
	{
		std::cout << -1 << std::endl << std::endl;
		return 0;
	}
	std::cout << "\nEntries of '"<<pattern<< "' start on the following indexes of '" << text << "':"<< std::endl;
	for (size_t i = 0; i < entries.size() - 1; ++i)
		std::cout << entries[i] << ',';
	std::cout << entries.back() << std::endl << std::endl;

	return 0;
}