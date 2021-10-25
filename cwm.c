#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <X11/Xlib.h>
#include "cwm.h"

Display *dpy;
int screen;
int screen_width, screen_height;
int running = 1;
Window root;
Client *first = NULL;
Drw *drw;

void init()
{
    dpy = XOpenDisplay(NULL);

    XSetWindowAttributes wa;

    screen = DefaultScreen(dpy);
    screen_width = DisplayWidth(dpy, screen);
    screen_height = DisplayHeight(dpy, screen);
    root = RootWindow(dpy, screen);

    wa.event_mask = SubstructureRedirectMask | SubstructureNotifyMask | ButtonPressMask | PointerMotionMask | EnterWindowMask | LeaveWindowMask | StructureNotifyMask | PropertyChangeMask;
    XChangeWindowAttributes(dpy, root, CWEventMask, &wa);
    XSelectInput(dpy, root, wa.event_mask);

    drw = drw_create();

    // 设置默认处理函数
    for (int i = 0; i < LASTEvent; i++)
    {
        handlers[i] = default_handler;
    }

    handlers[UnmapNotify] = unmapnotify_handler;
    handlers[MapRequest] = maprequest_handler;
}

void run()
{
    XEvent ev;
    XSync(dpy, False);
    while (running && !XNextEvent(dpy, &ev))
    {
        handler caller = handlers[ev.type];
        if (caller != NULL)
        {
            caller(&ev);
        }
    }
}

void sig_usr1(int signo)
{
    dump();
}

int main()
{
    signal(SIGUSR1, sig_usr1);
    init();
    run();
}