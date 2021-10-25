#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include "cwm.h"

void *handlers[LASTEvent];

void default_handler(XEvent *e)
{
    printf("default handler: e->type = %d\n", e->type);
}

void maprequest_handler(XEvent *e)
{
    XWindowAttributes wa;
    XMapRequestEvent *ev = &e->xmaprequest;
    XWindowChanges wc;
    Client *c = NULL;

    if (!XGetWindowAttributes(dpy, ev->window, &wa))
    {
        return;
    }
    c = malloc(sizeof(Client));
    c->win = ev->window;
    c->x = c->oldx = wa.x = 100;
    c->y = c->oldy = wa.y = 100;
    c->w = c->oldw = wa.width;
    c->h = c->oldh = wa.height;
    c->oldbw = wa.border_width;

    add(c);

    wc.border_width = 10;

    XConfigureWindow(dpy, c->win, CWBorderWidth, &wc);
    XSetWindowBorder(dpy, c->win, 0x3344ff);

    XMoveResizeWindow(dpy, c->win, c->x, c->y, c->w, c->h);

    drw_rect(drw, c->x, c->y - 20, c->w + 2 * 10, 30, 0, 0);
    drw_map(drw);

    XMapWindow(dpy, ev->window);
    printf("map window id : %ld\n", c->win);
    return;
}

void unmapnotify_handler(XEvent *e)
{
    XUnmapEvent *ev = &e->xunmap;

    Client *tmp = find_by_window_id(ev->window);
    if (tmp != NULL)
    {
        rm(tmp);
    }

    printf("unmap window id : %ld\n", ev->window);
    return;
}