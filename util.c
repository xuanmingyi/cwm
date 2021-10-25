#include <stdio.h>
#include <stdlib.h>
#include "cwm.h"

void add(Client *c)
{
    c->next = first;
    first = c;
}

void rm(Client *c)
{
    Client *tmp = first, *prev = NULL;
    while (tmp)
    {
        if (c == tmp)
        {
            if (prev == NULL)
            {
                // first
                first = tmp->next;
                free(tmp);
            }
            else
            {
                // other
                prev->next = tmp->next;
                free(tmp);
            }
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

Client *find(Client *c)
{
    Client *tmp = first;

    while (tmp)
    {
        if (c == tmp)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

Client *find_by_window_id(Window id)
{
    Client *tmp = first;
    while (tmp)
    {
        if (tmp->win == id)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void dump()
{
    Client *tmp = first;
    int i = 0;
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    printf("%d clients\n", i);
}