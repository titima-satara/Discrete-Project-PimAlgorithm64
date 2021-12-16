#pragma once
#include "Blueprint.h"
#include "Wrapper.h"
#include <iostream>
#include <vector>
// CR: https://www.tutorialspoint.com/Explain-Cplusplus-Singleton-design-pattern
class Singleton {
  private:
    static Singleton *instance;

    // Private constructor so that no objects can be created.
    Singleton() {
    }

  public:
    storeData store;
    static Singleton *getInstance() {
        if (!instance)
            instance = new Singleton;
        return instance;
    }

    //
    void reDraw() {
        Wrapper::clearViewPort();
        // delay(1500);
        for (auto v : store.Vertexs) {
            Wrapper::drawVertex(v);
            // delay(500);
        }
        //
        for (auto e : store.Edges) {
            Wrapper::writeText(e.center, fmt::format("w:{}", e.weight));
            Wrapper::drawEdge(e);
        }
        //
        //

        //
        if (store.tempEdge.status) {
            Vertex end = {
                store.tempEdge.end.x,
                store.tempEdge.end.y};
            Edge edge = {
                store.tempEdge.start,
                end};
            // store.tempEdge.
            Wrapper::drawEdge(edge);
        }
        // draw processTable
        for (auto pl : store.processTable) {
            if (pl.passed)
                Wrapper::drawEdge(pl.edge, RGB(0, 0, 255));
        }
    }
    //
};

Singleton *Singleton::instance = 0;