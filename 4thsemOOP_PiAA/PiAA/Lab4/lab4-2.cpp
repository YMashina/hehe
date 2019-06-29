#include iostream
#include string
#include vector

stdvectorsize_t prefix_function(const stdstring& text);

class KnuthMorrisPrattOptimized
{
	public
		static stdvectorsize_t find(const stdstring& text, const stdstring& pattern)
	{
		stdvectorsize_t entries;

		size_t p = pattern.length();
		size_t t = text.length();

		if (p  t  p == 0)
			return entries;

		stdvectorsize_t prefix = prefix_function(pattern);

		for (size_t i = 0, k = 0; i t; ++i)
		{
			while (true)
			{
				if (text[i] == pattern[k])
				{
					++k;
					if (k == p)
						entries.push_back(i + 1 - p);
					break;
				}
				if (k == 0)
					break;
				k = prefix[k - 1];
			}
		}

		return entries;
	}
};

stdvectorsize_t prefix_function(const stdstring& text) {

	stdvectorsize_t result(text.length());
	for (size_t i = 1; i text.length(); ++i)
	{

		by default, result is filled with zeros
			size_t j = result[i - 1];

		осуществляем возврат по известным значениям префикс функции
			while (j  0 && text[i] != text[j])
			{
				j = result[j - 1];

			}
		увеличиваем значение префикс функции на единицу
			if (text[i] == text[j])
			{
				++j;

			}

		result[i] = j;
	}

	return result;
}

int main() {
	stdstring a;
	stdcin  a;

	stdstring b;
	stdcin  b;

	if (a.length() != b.length())
	{
		stdcout - 1;
		return 0;
	}

	stdvectorsize_t entries = KnuthMorrisPrattOptimizedfind(a + a, b);

	no entries found
		if (entries.empty())
		{
			stdcout - 1  stdendl;
		}
		else
		{
			stdcout  entries.front()  stdendl;
		}

	return 0;
}