#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 110
typedef float float_t ;
const char priority[7][7] = {{'>','>','<','<','<','>','>'},{'>','>','<','<','<','>','>'},{'>','>','>','>','<','>','>'},{'>','>','>','>','<','>','>'},{'<','<','<','<','<','=','0'},{'>','>','>','>','0','>','>'},{'<','<','<','<','<','0','='}};
char Procede(char a,char b)
{
    int i,j ;
    switch (a)
    {
        case '+':
            i = 0 ;
            break ;
        case '-':
            i = 1 ;
            break ;
        case '*':
            i = 2 ;
            break ;
        case '/':
            i = 3 ;
            break ;
        case '(':
            i = 4 ;
            break ;
        case ')':
            i = 5 ;
            break ;
        case '#':
            i = 6 ;
            break ;
    }
    switch (b)
    {
        case '+':
            j = 0 ;
            break ;
        case '-':
            j = 1 ;
            break ;
        case '*':
            j = 2 ;
            break ;
        case '/':
            j = 3 ;
            break ;
        case '(':
            j = 4 ;
            break ;
        case ')':
            j = 5 ;
            break ;
        case '#':
            j = 6 ;
            break ;
    }
    return priority[i][j] ;
}

float_t Operate(float_t m, float_t n, char x)
{
    if (x == '+')
        return m + n ;
    if (x == '-')
        return n - m ;
    if (x == '*')
        return m * n ;
    if (x == '/')
        return n / m ;
    return 0 ;
}
float_t expr(char *i_s)
{
    float_t OPND[maxn];
    int top_OPND = -1;
    char OPTR[maxn];
    int top_OPTR = 0;
    OPTR[top_OPTR] = '#';

    char ss[2] = "#";
    char s[maxn];
    strncpy(s, i_s, maxn);
    strcat(s, ss);

    int k = 0;
    while (s[k] != '#' || OPTR[top_OPTR] != '#')
    {
        if (s[k] >= '0' && s[k] <= '9')
        {
            float_t y = 0;
            int isDecimal = 0;
            float_t decimalPrecision = 0.1;
            while ((s[k] >= '0' && s[k] <= '9') || s[k] == '.')
            {
                if (s[k] == '.')
                {
                    isDecimal = 1;
                }
                else
                {
                    if (isDecimal)
                    {
                        y += (s[k] - '0') * decimalPrecision;
                        decimalPrecision *= 0.1;
                    }
                    else
                    {
                        y = y * 10 + (s[k] - '0');
                    }
                }
                k++;
            }
            OPND[++top_OPND] = y;
        }
        else
        {
            switch (Procede(OPTR[top_OPTR], s[k]))
            {
            case '<':
                OPTR[++top_OPTR] = s[k];
                k++;
                break;
            case '=':
                top_OPTR--;
                k++;
                break;
            case '>':
            {
                char x = OPTR[top_OPTR--];
                float_t m = OPND[top_OPND--];
                float_t n = OPND[top_OPND--];
                OPND[++top_OPND] = Operate(m, n, x);
                break;
            }
            }
        }
    }
    return OPND[top_OPND];
}
int main()
{
    char s[maxn] = "";
    scanf("%s",s);
    float_t res = expr(s);
    printf("%f\n", res);
    return 0 ;
}