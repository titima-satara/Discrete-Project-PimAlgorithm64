#pragma once

#include "Blueprint.h"
#include "Singleton.h"
#include <vector>

using namespace std;

class Prim {
  public:
    vector<ProcessTable> processTable;
    Singleton *s = Singleton::getInstance();
    Vertex currentVertex;
    vector<Vertex> blacklist;

  private:
    void findWay() {
        for (auto e : s->store.Edges) {
            if (e.start.id == currentVertex.id || e.end.id == currentVertex.id) {
                auto dest = currentVertex.id != e.start.id ? e.start : e.end;
                updateTable(e.weight, currentVertex, dest, e);
            }
        }
		s->store.processTable = processTable;
    }
    //
    void updateTable(int weight, Vertex source, Vertex dest, Edge edge) {
        // check blacklist
        for (auto &b : blacklist) {
            if (b.id == dest.id) {
                fmt::print("BLACKLIST !:{}\n", b.id);
                return;
            }
        }
        //
        for (auto &pt : processTable) {
            if (pt.destination.id == dest.id && pt.weight >= weight) {
                pt.weight = weight;
                pt.source = source;
                pt.edge = edge;
                return;
            } 
			if (pt.destination.id == dest.id && pt.weight < weight) {
				// if new weight more table, nothing to do;
				return;
			}
        }
        // not found or not ...
        ProcessTable pt = {
            weight,
            source,
            dest,
            edge};
        processTable.push_back(pt);
    }
    //
    ProcessTable &getMinWeight() {
        int min = INT_MAX;
        ProcessTable *p = nullptr;
        for (auto &pt : processTable) {
            fmt::print("pass:{}\n", pt.passed);
            if (pt.weight < min && pt.passed == false)
                min = pt.weight;
        }
        fmt::print("min:{}\n", min);
        for (auto &pt : processTable) {
            if (pt.weight == min && pt.passed == false) {
                p = &pt;
                break; // return first value
                // return pt;
            }
        }
        // return null;
        fmt::print("p:{}\n", fmt::ptr(p));
        return *p;
    }
    void walk() {
        // loop iterator, need remove value
        /*
		vector<ProcessTable>::iterator i;
		int checkValue = INT_MAX;
		for (auto it = processTable.begin(); it != processTable.end(); it++) {
			if (checkValue > it->weight) {
				checkValue = it->weight;
				i = it;
			}
		}
		*/


		if (blacklist.size() == s->store.Vertexs.size() - 1) {
			fmt::print("fin !\n");
			return;
		}

        auto &minWeight = getMinWeight();
        // fmt::print("passed:{}", minWeight.passed);
        //fmt::print("s:{}, d:{}\n", minWeight.source.id, minWeight.destination.id);
        blacklist.push_back(currentVertex);
        currentVertex = minWeight.destination;
        minWeight.passed = true;
    }

  public:
    Prim() {
    }
    // Prim(Vertex startVertex) {
    //     currentVertex = startVertex;
    // 	findWay();
    // }
    void scan() {
        findWay(); // and update table
    }
    void nextState() {
        findWay();
        for (auto const &pt : processTable) {
            fmt::print("sid:{}, did:{}, w:{}, passed:{}\n", pt.source.id, pt.destination.id, pt.weight, pt.passed);
        }
        walk();
		s->store.processTable = processTable;
		s->reDraw();
    }
};