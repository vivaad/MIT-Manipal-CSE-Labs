#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    int row;
    int col;
    char name[100];
    char type[20];
} token;

token tokarr[10000];
int tokidx = 0;

int issymbol(char c)
{
    return (strchr(";,:(){}[]", c) != NULL);
}

int iskeyword(char *buf)
{
    char *kw[] = {"auto", "break", "case", "char", "const", "continue", "default",
                  "do", "double", "else", "enum", "extern", "float", "for",
                  "goto", "if", "int", "long", "register", "return", "short",
                  "signed", "sizeof", "static", "struct", "switch", "typedef",
                  "union", "unsigned", "void", "volatile", "while"};
    for (int i = 0; i < 32; i++)
    {
        if (strcmp(buf, kw[i]) == 0)
            return 1;
    }
    return 0;
}

void getNextToken(FILE *fp)
{
    int c;
    char buf[100];
    int i = 0;
    int rowcnt = 1;
    int colcnt = 0;

    while ((c = fgetc(fp)) != EOF)
    {
        colcnt++;
        if (c == '\n')
        {
            rowcnt++;
            colcnt = 0;
            continue;
        }
        if (isspace(c))
        {
            continue;
        }

        int token_row = rowcnt;
        int token_col = colcnt;
        i = 0;
        buf[0] = '\0';

        if (c == '#')
        {
            while ((c = fgetc(fp)) != EOF && c != '\n')
            {
                colcnt++;
            }
            if (c == '\n')
            {
                rowcnt++;
                colcnt = 0;
            }
            continue;
        }

        // Comments
        if (c == '/')
        {
            int next = fgetc(fp);
            colcnt++;
            if (next == '/')
            {
                while ((c = fgetc(fp)) != EOF && c != '\n')
                    colcnt++;
                if (c == '\n')
                {
                    rowcnt++;
                    colcnt = 0;
                }
                continue;
            }
            else if (next == '*')
            {
                int prev = 0;
                while ((c = fgetc(fp)) != EOF)
                {
                    colcnt++;
                    if (c == '\n')
                    {
                        rowcnt++;
                        colcnt = 0;
                    }
                    if (prev == '*' && c == '/')
                    {
                        break;
                    }
                    prev = c;
                }
                continue;
            }
            else
            {
                ungetc(next, fp);
                colcnt--;
            }
        }

        // Assignment & Relational operators: =, ==, >, >=, <, <=, !, !=
        if (c == '=')
        {
            buf[i++] = c;
            int next = fgetc(fp);
            colcnt++;
            if (next == '=')
            {
                buf[i++] = next;
                buf[i] = '\0';
                strcpy(tokarr[tokidx].type, "Relational operator"); // ==
            }
            else
            {
                ungetc(next, fp);
                colcnt--;
                buf[i] = '\0';
                strcpy(tokarr[tokidx].type, "Assignment operator"); // =
            }
            strcpy(tokarr[tokidx].name, buf);
            tokarr[tokidx].row = token_row;
            tokarr[tokidx++].col = token_col;
            continue;
        }

        if (c == '>' || c == '<' || c == '!')
        {
            buf[i++] = c;
            int next = fgetc(fp);
            colcnt++;
            if (next == '=')
                buf[i++] = next;
            else
            {
                ungetc(next, fp);
                colcnt--;
            }
            buf[i] = '\0';
            strcpy(tokarr[tokidx].name, buf);
            strcpy(tokarr[tokidx].type, "Relational operator"); // <, <=, >, >=
            if (c == '!' && next != '=')                        // !=
                strcpy(tokarr[tokidx].type, "Logical operator");
            tokarr[tokidx].row = token_row;
            tokarr[tokidx++].col = token_col;
            continue;
        }

        // Logical operators: &&, ||
        if (c == '&' || c == '|')
        {
            buf[i++] = c;
            int next = fgetc(fp);
            colcnt++;
            if (next == c)
            {
                buf[i++] = next;
            }
            else
            {
                ungetc(next, fp);
                colcnt--;
            }
            buf[i] = '\0';
            strcpy(tokarr[tokidx].name, buf);
            strcpy(tokarr[tokidx].type, "Logical operator");
            tokarr[tokidx].row = token_row;
            tokarr[tokidx++].col = token_col;
            continue;
        }

        // Arithmetic operators: +, -, *, /, ++, --, +=, -=
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            buf[i++] = c;
            int next = fgetc(fp);
            colcnt++;
            if (next == c && (c == '+' || c == '-'))
                buf[i++] = next;
            else if (next == '=')
                buf[i++] = next;
            else
            {
                ungetc(next, fp);
                colcnt--;
            }
            buf[i] = '\0';
            strcpy(tokarr[tokidx].name, buf);
            strcpy(tokarr[tokidx].type, "Arithmetic operator");
            tokarr[tokidx].row = token_row;
            tokarr[tokidx++].col = token_col;
            continue;
        }

        // Special symbols
        if (issymbol(c))
        {
            buf[i++] = c;
            buf[i] = '\0';
            strcpy(tokarr[tokidx].name, buf);
            strcpy(tokarr[tokidx].type, "Special symbol");
            tokarr[tokidx].row = token_row;
            tokarr[tokidx++].col = token_col;
            continue;
        }

        // Numbers
        if (isdigit(c))
        {
            buf[i++] = c;
            while (1)
            {
                int next = fgetc(fp);
                if (next == EOF) break;
                colcnt++;
                if (isdigit(next))
                {
                    buf[i++] = (char)next;
                }
                else
                {
                    ungetc(next, fp);
                    colcnt--;
                    break;
                }
            }
            buf[i] = '\0';
            strcpy(tokarr[tokidx].name, buf);
            strcpy(tokarr[tokidx].type, "num");
            tokarr[tokidx].row = token_row;
            tokarr[tokidx++].col = token_col;
            continue;
        }

        // Identifiers & Keywords
        if (isalpha(c) || c == '_')
        {
            buf[i++] = c;
            while (1)
            {
                int next = fgetc(fp);
                if (next == EOF) break;
                colcnt++;
                if (isalnum(next) || next == '_')
                {
                    buf[i++] = (char)next;
                }
                else
                {
                    ungetc(next, fp);
                    colcnt--;
                    break;
                }
            }
            buf[i] = '\0';
            if (iskeyword(buf))
            {
                strcpy(tokarr[tokidx].name, buf);
                strcpy(tokarr[tokidx].type, "Keyword");
            }
            else
            {
                strcpy(tokarr[tokidx].name, buf);
                strcpy(tokarr[tokidx].type, "id");
            }
            tokarr[tokidx].row = token_row;
            tokarr[tokidx++].col = token_col;
            continue;
        }

        if (c == '"')
        {
            buf[i++] = c;
            while ((c = fgetc(fp)) != EOF)
            {
                colcnt++;
                if (c == '\\')
                {
                    buf[i++] = '\\';
                    c = fgetc(fp);
                    colcnt++;
                    if (c != EOF)
                        buf[i++] = c;
                }
                else if (c == '"')
                {
                    buf[i++] = c;
                    break;
                }
                else
                {
                    buf[i++] = c;
                }
            }
            buf[i] = '\0';
            strcpy(tokarr[tokidx].name, buf);
            strcpy(tokarr[tokidx].type, "Literal");
            tokarr[tokidx].row = token_row;
            tokarr[tokidx++].col = token_col;
            continue;
        }
    }
}

int mainhelp()
{
    FILE *fp = fopen("input.c", "r");
    getNextToken(fp);
    fclose(fp);
    printf(" %-25s | %-20s | %-4s | %-4s\n", "Name", "Type", "Row", "Col");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < tokidx; i++)
    {
        printf(" %-25s | %-20s | %-4d | %-4d\n",
               tokarr[i].name, tokarr[i].type, tokarr[i].row, tokarr[i].col);
    }
    return 0;
}
