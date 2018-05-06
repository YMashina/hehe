#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

typedef struct stack { 
char** arr[max]; 
int top; 
}stack; 

void initStack(struct stack* stack) { 
stack->top=0; 
} 

char* pop(struct stack* stack) { 
stack->top-=1; 
return stack->arr[stack->top]; 
} 

void push(struct stack* stack, char* x) { 
stack->arr[stack->top]=x; 
stack->top+=1; 
} 

char* top(struct stack* stack) { 
return stack->arr[stack->top-1]; 
} 

int isEmpty(struct stack* stack) { 
    if(stack->top==0) 
        return 1;
    else
        return 0;
} 

int main()
{
    stack stk;
    initStack(&stk);
    char a;
    int q = 0, i = 0, flag = 0, popflag = 0, brhrflag = 0, N = 10, closetagflag = 0;
    char br[] = "br", hr[] = "hr";
    char* ar = NULL;

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
                push(&stk, ar);
            }
            else
            {
                if (closetagflag && (strcmp(top(&stk), ar)) != 0)
                {
                    printf("wrong");
                    return 0;
                }
                if (!isEmpty(&stk) && !brhrflag)
                {
                    if ((strcmp(top(&stk), ar)) == 0 && closetagflag)
                    {
                        pop(&stk);
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
    if (isEmpty(&stk))
        printf("correct");
    else
        printf("wrong");
    
    return 0;
}