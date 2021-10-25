#include <stdlib.h>

#include "cwm.h"

Drw *drw_create()
{
    Drw *drw = malloc(sizeof(Drw));
    drw->drawable = XCreatePixmap(dpy, root, screen_width, screen_height, DefaultDepth(dpy, screen));
    drw->gc = XCreateGC(dpy, root, 0, NULL);
    return drw;
}

// 矩形
void drw_rect(Drw *drw, int x, int y, unsigned int w, unsigned int h, int filled, int invert)
{
    XSetForeground(dpy, drw->gc, 0x003300);
    XFillRectangle(dpy, drw->drawable, drw->gc, x, y, w, h);
}

// 显示drw的数据到win
void drw_map(Drw *drw, Window win, int x, int y, unsigned int w, unsigned int h)
{
    if (!drw)
        return;
    XCopyArea(dpy, drw->drawable, win, drw->gc, x, y, w, h, x, y);
    XSync(dpy, False);
}