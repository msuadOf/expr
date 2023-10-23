/**
 * @file expr.c
 * @author Nsuad 
 * @brief article: https://blog.csdn.net/qq_41317652/article/details/82958188
 * @version 0.1
 * @date 2023-10-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 110

const char priority[7][7] = {
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'<', '<', '<', '<', '<', '=', '0'},
    {'>', '>', '>', '>', '0', '>', '>'},
    {'<', '<', '<', '<', '<', '0', '='}
};

char Procede(char a, char b)
{
    int i, j;
    switch (a)
    {
        case '+':
            i = 0;
            break;
        case '-':
            i = 1;
            break;
        case '*':
            i = 2;
            break;
        case '/':
            i = 3;
            break;
        case '(':
            i = 4;
            break;
        case ')':
            i = 5;
            break;
        case '#':
            i = 6;
            break;
    }
    switch (b)
    {
        case '+':
            j = 0;
            break;
        case '-':
            j = 1;
            break;
        case '*':
            j = 2;
            break;
        case '/':
            j = 3;
            break;
        case '(':
            j = 4;
            break;
        case ')':
            j = 5;
            break;
        case '#':
            j = 6;
            break;
    }
    return priority[i][j];
}

int Operate(int m, int n, char x)
{
    if (x == '+')
        return m + n;
    if (x == '-')
        return n - m;
    if (x == '*')
        return m * n;
    if (x == '/')
        return n / m;
    return 0;
}

int expr(char* i_s)
{
    int OPND[maxn];
    int top_OPND = -1;
    char OPTR[maxn];
    int top_OPTR = 0;

    OPTR[top_OPTR] = '#';

    char ss[2] = "#";
    char s[maxn];
    strcpy(s,i_s);
    //scanf("%s", s);
    strcat(s, ss);
    char c = s[0];
    int k = 1;
    while (c != '#' || OPTR[top_OPTR] != '#')
    {
        int y = 0;
        if (c >= '0' && c <= '9')
        {
            while (c >= '0' && c <= '9')
            {
                y = y * 10 + (c - '0');
                c = s[k++];
            }
            OPND[++top_OPND] = y;
        }
        else
        {
            switch (Procede(OPTR[top_OPTR], c))
            {
                case '<':
                    OPTR[++top_OPTR] = c;
                    c = s[k++];
                    break;
                case '=':
                    top_OPTR--;
                    c = s[k++];
                    break;
                case '>':
                {
                    char x = OPTR[top_OPTR--];
                    int m = OPND[top_OPND--];
                    int n = OPND[top_OPND--];
                    OPND[++top_OPND] = Operate(m, n, x);
                    break;
                }
            }
        }
    }

    return  OPND[top_OPND];
}
int main(){
    char s[100];
    scanf("%s",s);
    int res=expr(s);
    printf("%d\n",res);
    return 0;
}