#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPalindrome(char str[], int start, int end)
{
    // when 1 character
    if (start == end)
    return 1;

    // If first != last
    if (str[start] != str[end])
    return 0;

    // If more than 2, middle substring for palindrome.
    if (start < end + 1)
    return isPalindrome(str, start + 1, end - 1);

    return 1;
}

int main()
{
    char* str = (char*)malloc(50*sizeof(char));
    scanf("%s",str);
    int n = strlen(str);

	if (n == 0) //empty=palindrome
    printf("YES");

    if (isPalindrome(str, 0, n - 1))
    printf("YES");
    else
    printf("NO");

    return 0;
}
