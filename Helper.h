#pragma once

#include "Blueprint.h"
#include <fmt/format.h>
#include <graphics.h>
// #include <algorithm>
#include "ASCII_KEY.h"
#include "Singleton.h"
#include "Wrapper.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
namespace Helper {

	Singleton *s = Singleton::getInstance();

	// return true when exist id
	template <class T, class U, class S>
	T &getRef(T &input, U &vec, S &statusOut) {
		statusOut = false;
		for (auto &v : vec) {
			if (input.id == v.id) {
				statusOut = true;
				return v;
			}
		}
		fmt::print("OUT\n");
		return input;
	}

	// circle or vertex is the same
	Vertex inCircle(int x, int y) {
		for (auto v : s->store.Vertexs) {
			auto check = ((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y)) <= v.r * v.r;
			if (check == true) {
				fmt::print("+inCircle id:{}\n", v.id);
				return v;
			}
		}
		fmt::print("-inCircle\n");
		Vertex null;
		null.id = -1;
		return null;
	}


	Edge inEdge(int x, int y) {
		for (auto e : s->store.Edges) {
			auto check = ((x - e.center.x) * (x - e.center.x) + (y - e.center.y) * (y - e.center.y)) <= e.radius * e.radius;
			if (check == true) {
				fmt::print("+inLine start:{}|end:{}\n", e.start.id, e.end.id);
				return e;
			}
		}
		fmt::print("-inLine\n");
		Edge null;
		null.id = -1;
		return null;
	}

	void createVectex() {
		auto c = Wrapper::setEventListener(WM_LBUTTONDOWN);
		fmt::print("createVectex: X:{},Y:{}\n", c.x, c.y);
		auto checkInCircle = inCircle(c.x, c.y);

		if (checkInCircle.id != -1) {
			fmt::print("Error inCircle\n");
			return;
		}

		Vertex v = {
			c.x,
			c.y,
			5,										   // radius
			static_cast<int>(s->store.Vertexs.size()), // id
			0										   // degree
		};

		s->store.Vertexs.push_back(v);
		s->reDraw();
	}

	void drawTempEdge(int x, int y) {
		fmt::print("mousemove: {}, {}\n", x, y);
		lineto(x, y);
	}

	std::atomic<bool> flag = true;
	void createTempEdge(Vertex edge1) {
		fmt::print("THREAD\n");
		s->store.tempEdge.status = true;
		s->store.tempEdge.start = edge1;
		while (flag) {
			auto c = Wrapper::setEventListener(WM_MOUSEMOVE, 50);
			s->store.tempEdge.end.x = c.x;
			s->store.tempEdge.end.y = c.y;
			s->reDraw();
			fmt::print("line ");
			//line(edge1.x, edge1.y, c.x, c.y);
		}
		s->store.tempEdge.status = false;
		s->reDraw();
		fmt::print("EXIT THREAD!\n");
		// Axis c;
		// moveto(edge1.x, edge1.y);
		// registermousehandler(WM_MOUSEMOVE, drawTempEdge);

		// clearmouseclick(WM_LBUTTONDOWN);
		// while (ismouseclick(WM_LBUTTONDOWN)) {
		//     delay(200);
		// }
		// getmouseclick(WM_LBUTTONDOWN, c.x, c.y);
		// auto checkInCircle_v1 = inCircle(c.x, c.y);

		// if (checkInCircle_v1.id != -1) {
		//     // not selected vertex
		//     fmt::print("not vertex {} {}\n", c.x, c.y);
		// }
		// fmt::print("exit\n");
	}

	Vertex createDestEdge() {
		auto c = Wrapper::setEventListener(WM_LBUTTONDOWN);
		// fmt::print("x:{} y:{}", c.x, c.y);
		auto edge2 = inCircle(c.x, c.y);
		fmt::print("x:{} y:{} id:{}\n", edge2.x, edge2.y, edge2.id);
		return edge2;
	}

	void testTempEdge(int x, int y) {
		s->store.tempEdge.end.x = x;
		s->store.tempEdge.end.y = y;
		s->reDraw();
		fmt::print("line ");
	}

	void createEdge() {
		auto c = Wrapper::setEventListener(WM_LBUTTONDOWN);
		auto edge1 = inCircle(c.x, c.y);

		if (edge1.id == -1) {
			// not selected vertex
			fmt::print("not vertex\n");
			return;
		}
		// clear mouse event
		// left button click
		//registermousehandler(WM_LBUTTONDOWN, [](int x, int y) {});
		//
		//ddd();

		//temp edge

		flag = true;
		std::thread t1(createTempEdge, edge1);
		//t1.detach();

		// s->store.tempEdge.status = true;
		// s->store.tempEdge.start = edge1;
		// registermousehandler(WM_MOUSEMOVE, testTempEdge);

		// t1.detach();
		// createTempEdge(edge1);
		//

		auto destEdge = createDestEdge();
		//registermousehandler(WM_MOUSEMOVE, [](int x, int y) {});
		// fmt::print("x:{} y:{}", destEdge.x, destEdge.y);
		if (destEdge.id == -1) {
			// s->store.tempEdge.status = false;
			flag = false;
			t1.join();
			fmt::print("not vertex destEdge\n");
			s->reDraw();
			return;
		} else if (destEdge.id == edge1.id) {
			flag = false;
			t1.join();
			fmt::print("same vertex not allow\n");
			s->reDraw();
			return;
		}

		//flag = false;
		//registermousehandler(WM_MOUSEMOVE, [](int x, int y) {});
		// s->store.tempEdge.status = false;
		flag = false;
		t1.join();

		int center_x = (edge1.x + destEdge.x) / 2;
		int centet_y = (edge1.y + destEdge.y) / 2;

		Edge edge = {
			edge1,									 // start
			destEdge,								 // end
			{center_x, centet_y},					 // center
			15,										 // radius for click
			static_cast<int>(s->store.Edges.size()), // id
			3,										 // weight
		};
		// edge.start = edge1;
		// edge.end = destEdge;
		s->store.Edges.push_back(edge);
		s->reDraw();
		//line(edge1.x, edge1.y, destEdge.x, destEdge.y);

		//createTempEdge(edge1);
	}

	void editWeight() {
		auto c = Wrapper::setEventListener(WM_LBUTTONDOWN);
		auto inedge = inEdge(c.x, c.y);
		if (inedge.id == -1) {
			fmt::print("not edge\n");
			return;
		}
		fmt::print("center x:{} y:{}\n", inedge.center.x, inedge.center.y);
		Wrapper::writeText({inedge.center.x, inedge.center.y}, fmt::format("w:{}", inedge.weight), 4);
		string new_weight_string = Wrapper::getString();
		// inedge.weight = stoi(new_weight);

		int new_weight;
		try {
			new_weight = stoi(new_weight_string);
		} catch (...) {
			fmt::print("new weight error!\n");
			s->reDraw();
			return;
		}

		int index = 0;
		for (auto &e : s->store.Edges) {
			if (e.id == inedge.id) {
				fmt::print("EDIT !\n");
				// e.weight = stoi(new_weight);
				e.weight = new_weight;
				fmt::print("e:{}\n", e.weight);
				break;
			}
			index++;
		}
		s->reDraw();
	}

	void removeVertexOrEdge() {
		auto c = Wrapper::setEventListener(WM_LBUTTONDOWN);
		auto inVertex = inCircle(c.x, c.y);
		if (inVertex.id == -1) {
			fmt::print("[remove] not vertex, next check edge\n");
			auto inedge = inEdge(c.x, c.y);
			if (inedge.id == -1) {
				fmt::print("[remove] not vertex && not edge\n");
				return;
			}
			// then edge
			s->store.Edges.erase(remove_if(
									 s->store.Edges.begin(),
									 s->store.Edges.end(),
									 [&inedge](Edge const &e) {
										 return e.id == inedge.id;
									 }),
								 s->store.Edges.end());
			s->reDraw();

			/*
        bool idExist;
        auto &x = getRef<Edge>(inedge, s->store.Edges, idExist);
		*/

			return;
		}
		// then vertex
		// may be need remove edge before remove vertex
		fmt::print("[remove] vertex\n");
		vector<int> idRemove;
		for (auto e : s->store.Edges) {
			if (e.start.id == inVertex.id || e.end.id == inVertex.id)
				idRemove.push_back(e.id);
		}
		// remove edge
		for (auto i : idRemove) {
			s->store.Edges.erase(remove_if(
									 s->store.Edges.begin(),
									 s->store.Edges.end(),
									 [&i](Edge const &e) {
										 return e.id == i;
									 }),
								 s->store.Edges.end());
		}
		// remove vertex
		s->store.Vertexs.erase(remove_if(
								   s->store.Vertexs.begin(),
								   s->store.Vertexs.end(),
								   [&inVertex](Vertex const &v) {
									   return v.id == inVertex.id;
								   }),
							   s->store.Vertexs.end());
		//
		s->reDraw();
	}

	Vertex setSelectedEdge(bool &statusOut) {
		auto c = Wrapper::setEventListener(WM_LBUTTONDOWN);
		auto vertex = inCircle(c.x, c.y);
		if (vertex.id == -1) {
			fmt::print("not vertex\n");
			statusOut = false;
			return vertex;
		}
		// p = new Prim(vertex);
		s->store.selectedEdgeId = vertex.id;
		statusOut = true;
		return vertex;
	}

	void clearViewPort(int x, int y) {
		Wrapper::clearViewPort();
	}

} // namespace Helper