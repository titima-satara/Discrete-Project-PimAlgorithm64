#pragma once

#include "Blueprint.h"
#include <fmt/format.h>
#include <graphics.h>
// #include <algorithm>
#include "ASCII_KEY.h"
#include "Singleton.h"
#include <vector>

using namespace std;
namespace Wrapper {

    int initWindow(int width, int heigh, string title, int startLeft = 0, int startTop = 0, bool closeFlag = true) {
        return initwindow(width, heigh, &title[0], startLeft, startTop, false, closeFlag);
    }

    Axis setEventListener(int kind, int _delay = 300) {
        Axis c;
        clearmouseclick(kind);
        while (!ismouseclick(kind)) {
            delay(_delay);
        }
        getmouseclick(kind, c.x, c.y);
        return c;
    }

    void clearViewPort() {
        clearviewport();
    }

    char getOneChar() {
        // https://home.cs.colorado.edu/~main/bgi/doc/getch.html
        char c;
        c = getch();
        if (c != 0)
            return c;

        // special keys
        c = getch();
        return c;
    }

    string getString() {
        vector<char> ch;
        int c;
        while (true) {
            c = getch();
            //fmt::print("ASCII:{}|Char:{}|\n", c, (char)c);

            if (c == KEY_ENTER)
                break;

            if (c == KEY_ESC)
                return "";

            //if (c == KEY_ENTER)

            ch.push_back((char)c);
        }
        //outtextxy(300, 200, (char *)fmt::format("{}", string(ch.begin(), ch.end())).c_str());
        return string(ch.begin(), ch.end());
    }

    void writeText(Axis axis, string text, int color = 15) {
        // 15 = white
        // https://home.cs.colorado.edu/~main/bgi/doc/setcolor.html
        settextstyle(4, 4, 1);
        setcolor(color);

        // string s = "v";
        // s.append(to_string(v.id));
        outtextxy(axis.x, axis.y, &text[0]);
        //
        setcolor(15);
    }

    void drawVertex(Vertex v) {
        // settextstyle(4, 4, 1);
        string s = "v";
        s.append(to_string(v.id));
        outtextxy(v.x, v.y, &s[0]);

        setfillstyle(SOLID_FILL, COLOR(255, 0, 0));
        circle(v.x, v.y, v.r);
        floodfill(v.x, v.y, WHITE);
    }

    void drawEdge(Edge e) {
        line(e.start.x, e.start.y, e.end.x, e.end.y);
        return;

        // for (auto d : Vertexs) {
        //     // std::cout << d.id << " | x:" << d.x << "y: " << d.y << "\n";
        // }
        // fmt::print("\n\n");

        // sort(Vertexs.begin(), Vertexs.end(), [](Vertex v1, Vertex v2) {
        //     return v1.id < v2.id;
        // });
        // for (auto d : Vertexs) {
        //     // cout << d.id << " | x:" << d.x << "y: " << d.y << "\n";
        // }

        // // cout << "\n" << "size: " << Vertexs.size() << "\n";
        // fmt::print("\n");

        // // for (auto l : Lines) {
        // //     // cout << "Edge start: " << l.start << " Edge end: " << l.end << "\n";

        // //     auto v1 = Vertexs[l.start];
        // //     auto v2 = Vertexs[l.end];
        // //     line(v1.x, v1.y, v2.x, v2.y);
        // // }
    }

    void drawEdge(Edge e, int color) {
        setcolor(color);
        drawEdge(e);
        setcolor(15);
    }

    Axis getClick(int _delay) {
        Axis click;
        while (!ismouseclick(WM_LBUTTONDBLCLK))
            delay(_delay);
        getmouseclick(WM_LBUTTONDBLCLK, click.x, click.y);
        return click;
    }

}
