#include <iostream>
#include <thread>
#include <string>
#include <vector>

std::vector<size_t> prefix_function(const std::string& text) {

	std::vector<size_t> result(text.length());
	for (size_t i = 1; i < text.length(); ++i)
	{

		// by default, result is filled with zeros
		size_t j = result[i - 1];

		// осуществляем возврат по известным значениям префикс функции
		while (j > 0 && text[i] != text[j])
		{
			j = result[j - 1];

		}
		// увеличиваем значение префикс функции на единицу
		if (text[i] == text[j])
		{
			++j;

		}
		result[i] = j;
	}

	return result;
}

std::vector<size_t> knuth_morris_pratt(const std::string& text, const std::string& pattern) {
	std::vector<size_t> result;
	std::vector<size_t> prefix = prefix_function(pattern + "#" + text);

	for (size_t i = 0; i < text.length(); ++i)
	{
		// найдено вхождение
		if (prefix[pattern.length() + i + 1] == pattern.length())
		{
			// добавляем индекс в выходные данные с учётом сдвига
			result.push_back(i + 1 - pattern.length());
		}
	}

	return result;
}

int main() {
	std::string pattern;
	std::cin >> pattern;

	std::string text;
	std::cin >> text;

	std::vector<size_t> entries = knuth_morris_pratt(text, pattern);

	if (entries.empty())
	{
		std::cout << -1 << std::endl << std::endl;
		return 0;
	}

	for (size_t i = 0; i < entries.size() - 1; ++i)
		std::cout << entries[i] << ',';
	std::cout << entries.back() << std::endl << std::endl;

	return 0;
}