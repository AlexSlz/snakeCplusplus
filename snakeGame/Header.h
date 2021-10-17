#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "graphics.h"
#include <vector>
#include <iostream>

extern int height, width;

class myObject {
public:
    int x = 0;
    int y = 0;
    int color;
    myObject(int _x, int _y, int _c) {
        x = _x;
        y = _y;
        color = _c;
    }
    void print() {
        setcolor(color);
        rectangle(x, y, x + 10, y + 10);
    }
    bool collide(myObject obj) {
        return ((x - 10 <= obj.x && x + 10 >= obj.x) && (y - 10 <= obj.y && y + 10 >= obj.y));
    }
    void getRandCords() {
        x = 30 + rand() % (((height - 100) + 1) - 30);
        y = 30 + rand() % (((width - 100) + 1) - 30);
    }
};