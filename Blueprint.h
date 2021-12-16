#pragma once
#include <vector>

struct Axis {
    int x, y;
};

struct Vertex {
    int x;
    int y;
    int r;
    int id;
    int degree;
};

struct Edge {
    Vertex start, end;
    Axis center;
    int radius;
    int id;
    int weight;
    // why don't use vertex
};

struct TempEdge {
    Vertex start;
    Axis end;
    bool status;
};

struct ProcessTable {
	int weight;
	Vertex source;
	Vertex destination;
	Edge edge;
	bool passed = false;
};

struct storeData {
    std::vector<Vertex> Vertexs;
    std::vector<Edge> Edges;
    TempEdge tempEdge; // for drawing
	std::vector<ProcessTable> processTable;
    int selectedEdgeId;
    //TempWeight
};

