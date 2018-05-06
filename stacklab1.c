#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max2 100

int top2 = -1;
char** arr2 = NULL;

void Push2(char* x)
{
    arr2[++top2] = x;
}

void Pop2()
{
    if (top2 == -1)
        return;
    top2 -= 1;
}

char* Top2()
{
    return arr2[top2];
}

int IsEmpty2()
{
    if (top2 == -1)
        return 1;
    else
        return 0;
}

int main()
{
    char a;
    int q = 0, i = 0, flag = 0, popflag = 0, brhrflag = 0, N = 10, closetagflag = 0;
    char br[] = "br", hr[] = "hr";
    char* ar = NULL;
    arr2 = (char**)malloc(max2 * sizeof(char*));

    while ((a = getchar()) != '\n')
    {
        if (a == '<')
        {
            flag = 1;
            ar = (char*)malloc(N * sizeof(char));
            i = 1;
            continue;
        }
        if (a == '/' && flag)
        {
            if (i == 0)
            {
                printf("wrong");
                return 0;
            }
            closetagflag = 1;
            continue;
        }

        if (a == '>')
        {
            flag = 0;
            ar[q] = '\0';
            q = 0;

            if ((strcmp(ar, br)) == 0 || (strcmp(ar, hr)) == 0)
                brhrflag = 1;

            if (!closetagflag && !brhrflag)
            {
                Push2(ar);
            }
            else
            {
                if (closetagflag && (strcmp(Top2(), ar)) != 0)
                {
                    printf("wrong");
                    return 0;
                }
                if (!IsEmpty2() && !brhrflag)
                {
                    if ((strcmp(Top2(), ar)) == 0 && closetagflag)
                    {
                        Pop2();
                        popflag = 1;
                    }
                }
            }

            free(ar);
            popflag = 0;
            brhrflag = 0;
            closetagflag = 0;
            continue;
        }
        if (flag)
        {
            ar[q] = a;
            q++;
        }
    }
    if (IsEmpty2())
        printf("correct");
    else
        printf("wrong");

    free(arr2);

    return 0;
}