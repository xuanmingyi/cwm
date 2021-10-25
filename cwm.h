#ifndef CWM_H
#define CWM_H

#include <X11/Xlib.h>

// 画图
typedef struct Drw
{
    Drawable drawable;
    GC gc;

    XftFont *fonts;

} Drw;

Drw *drw_create();
void drw_rect(Drw *drw, int x, int y, unsigned int w, unsigned int h, int filled, int invert);
void drw_map(Drw *drw);

// 类型
typedef void (*handler)(XEvent *);

typedef struct Client
{
    char name[256];
    int x, y, w, h;
    int oldx, oldy, oldw, oldh;
    int oldbw;
    struct Client *next;
    Window win;
} Client;

// 全局变量
extern Display *dpy;
extern int screen;
extern int screen_width, screen_height;
extern Window root;
extern int running;
extern void *handlers[LASTEvent];
extern Client *first;
extern Drw *drw;

// 处理函数
void default_handler(XEvent *);
void unmapnotify_handler(XEvent *);
void maprequest_handler(XEvent *);

// 数据结构
void add(Client *c);
void rm(Client *c);
Client *find(Client *c);
Client *find_by_window_id(Window id);
void dump();

#endif