#include "getToken.c"
#include <stdlib.h>

int cur = 1;

void invalid()
{
    printf("Invalid, %s\n", tokarr[cur].name);
    printf("r = %d, c = %d\n", tokarr[cur].row, tokarr[cur].col);
    exit(0);
}

void valid()
{
    printf("Parsing done successfully\n");
}

void Program();
void declarations();
void data_type();
void identifier_list();
void I1();
void statement_list();
void statement();
void assign_stat();
void decision_stat();
void dprime();
void looping_stat();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

void Program()
{
    if (strcmp(tokarr[cur].name, "main") == 0)
    {
        cur++;
        if (strcmp(tokarr[cur].name, "(") == 0)
        {
            cur++;
            if (strcmp(tokarr[cur].name, ")") == 0)
            {
                cur++;
                if (strcmp(tokarr[cur].name, "{") == 0)
                {
                    cur++;
                    declarations();
                    statement_list();
                    if (strcmp(tokarr[cur].name, "}") == 0)
                    {
                        cur++;
                        return;
                    }
                    else
                        invalid();
                }
                else
                    invalid();
            }
            else
                invalid();
        }
        else
            invalid();
    }
    else
        invalid();
}

void declarations()
{
    if (strcmp(tokarr[cur].name, "int") == 0 || strcmp(tokarr[cur].name, "char") == 0)
    {
        data_type();
        identifier_list();
        if (strcmp(tokarr[cur].name, ";") == 0)
        {
            cur++;
            declarations();
            return;
        }
        else
            invalid();
    }
    else
    {
        return;
    }
}

void data_type()
{
    if (strcmp(tokarr[cur].name, "int") == 0)
    {
        cur++;
        return;
    }
    else if (strcmp(tokarr[cur].name, "char") == 0)
    {
        cur++;
        return;
    }
    else
        invalid();
}

void identifier_list()
{
    if (strcmp(tokarr[cur].type, "id") == 0)
    {
        cur++;
        I1();
    }
    else
        invalid();
}

void I1()
{
    if (strcmp(tokarr[cur].name, ",") == 0)
    {
        cur++;
        identifier_list();
    }
    else if (strcmp(tokarr[cur].name, "[") == 0)
    {
        cur++;
        if (strcmp(tokarr[cur].type, "num") == 0)
        {
            cur++;
            if (strcmp(tokarr[cur].name, "]") == 0)
            {
                cur++;
                if (strcmp(tokarr[cur].name, ",") == 0)
                {
                    cur++;
                    identifier_list();
                }
                else
                {
                    return;
                }
            }
            else
                invalid();
        }
    }
    else
        return;
}

void statement_list()
{
    /* statement_list -> statement statement_list | e
       FIRST(statement) = { id, if, while } */
    if (strcmp(tokarr[cur].type, "id") == 0
        || strcmp(tokarr[cur].name, "if") == 0
        || strcmp(tokarr[cur].name, "while") == 0)
    {
        statement();
        statement_list();
    }
    else
        return;
}

void statement()
{
    /* statement -> assign-stat ; | decision-stat | looping-stat */
    if (strcmp(tokarr[cur].type, "id") == 0)
    {
        assign_stat();
        if (strcmp(tokarr[cur].name, ";") == 0)
            cur++;
        else
            invalid();
    }
    else if (strcmp(tokarr[cur].name, "if") == 0)
    {
        decision_stat();
    }
    else if (strcmp(tokarr[cur].name, "while") == 0)
    {
        looping_stat();
    }
    else
        invalid();
}

void assign_stat()
{
    if (strcmp(tokarr[cur].type, "id") == 0)
    {
        cur++;
        if (strcmp(tokarr[cur].name, "=") == 0)
        {
            cur++;
            expn();
        }
        else
            invalid();
    }
    else
        invalid();
}

/* decision-stat -> if ( expn ) { statement-list } dprime
   dprime        -> else { statement-list } | e            */
void decision_stat()
{
    if (strcmp(tokarr[cur].name, "if") == 0)
    {
        cur++;
        if (strcmp(tokarr[cur].name, "(") == 0)
        {
            cur++;
            expn();
            if (strcmp(tokarr[cur].name, ")") == 0)
            {
                cur++;
                if (strcmp(tokarr[cur].name, "{") == 0)
                {
                    cur++;
                    statement_list();
                    if (strcmp(tokarr[cur].name, "}") == 0)
                    {
                        cur++;
                        dprime();
                        return;
                    }
                    else
                        invalid();
                }
                else
                    invalid();
            }
            else
                invalid();
        }
        else
            invalid();
    }
    else
        invalid();
}

void dprime()
{
    /* dprime -> else { statement-list } | e */
    if (strcmp(tokarr[cur].name, "else") == 0)
    {
        cur++;
        if (strcmp(tokarr[cur].name, "{") == 0)
        {
            cur++;
            statement_list();
            if (strcmp(tokarr[cur].name, "}") == 0)
            {
                cur++;
                return;
            }
            else
                invalid();
        }
        else
            invalid();
    }
    else
        return; /* e production */
}

/* looping-stat -> while ( expn ) { statement-list } */
void looping_stat()
{
    if (strcmp(tokarr[cur].name, "while") == 0)
    {
        cur++;
        if (strcmp(tokarr[cur].name, "(") == 0)
        {
            cur++;
            expn();
            if (strcmp(tokarr[cur].name, ")") == 0)
            {
                cur++;
                if (strcmp(tokarr[cur].name, "{") == 0)
                {
                    cur++;
                    statement_list();
                    if (strcmp(tokarr[cur].name, "}") == 0)
                    {
                        cur++;
                        return;
                    }
                    else
                        invalid();
                }
                else
                    invalid();
            }
            else
                invalid();
        }
        else
            invalid();
    }
    else
        invalid();
}

void expn()
{
    simple_expn();
    eprime();
}

void eprime()
{
    if (strcmp(tokarr[cur].name, "==") == 0 || strcmp(tokarr[cur].name, "!=") == 0
        || strcmp(tokarr[cur].name, "<=") == 0 || strcmp(tokarr[cur].name, ">=") == 0
        || strcmp(tokarr[cur].name, ">") == 0  || strcmp(tokarr[cur].name, "<") == 0)
    {
        relop();
        simple_expn();
    }
    else
        return;
}

void simple_expn()
{
    term();
    seprime();
}

void seprime()
{
    if (strcmp(tokarr[cur].name, "+") == 0 || strcmp(tokarr[cur].name, "-") == 0)
    {
        addop();
        term();
        seprime();
    }
    else
        return;
}

void term()
{
    factor();
    tprime();
}

void tprime()
{
    if (strcmp(tokarr[cur].name, "*") == 0 || strcmp(tokarr[cur].name, "/") == 0
        || strcmp(tokarr[cur].name, "%") == 0)
    {
        mulop();
        factor();
        tprime();
    }
    else
        return;
}

void factor()
{
    if (strcmp(tokarr[cur].type, "id") == 0)
        cur++;
    else if (strcmp(tokarr[cur].type, "num") == 0)
        cur++;
    else
        invalid();
}

void relop()
{
    if (strcmp(tokarr[cur].name, "==") == 0)       cur++;
    else if (strcmp(tokarr[cur].name, "!=") == 0)  cur++;
    else if (strcmp(tokarr[cur].name, "<=") == 0)  cur++;
    else if (strcmp(tokarr[cur].name, ">=") == 0)  cur++;
    else if (strcmp(tokarr[cur].name, ">") == 0)   cur++;
    else if (strcmp(tokarr[cur].name, "<") == 0)   cur++;
    else invalid();
}

void addop()
{
    if (strcmp(tokarr[cur].name, "+") == 0)       cur++;
    else if (strcmp(tokarr[cur].name, "-") == 0)  cur++;
    else invalid();
}

void mulop()
{
    if (strcmp(tokarr[cur].name, "*") == 0)       cur++;
    else if (strcmp(tokarr[cur].name, "/") == 0)  cur++;
    else if (strcmp(tokarr[cur].name, "%") == 0)  cur++;
    else invalid();
}

void main()
{
    FILE *fp = fopen("input.c", "r");
    getNextToken(fp);
    fclose(fp);
    Program();
    if (cur == tokidx)
        valid();
    else
        invalid();
}
