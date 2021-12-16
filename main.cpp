#define FMT_HEADER_ONLY

#include "File.h"
#include "HelpWindow.h"
#include "Helper.h"
#include "Prim.h"
#include "Singleton.h"
#include "Wrapper.h"
#include "processTable.h"
#include <fmt/core.h>
#include <graphics.h>
#include <iostream>
#include <string>

using namespace std;

void getClick(int x, int y) {
	fmt::print("x:{}|y:{}\n", x, y);
}

int main() {

	// string input = "0  2  0  4  6  5  0  0  0  0  0  0    ";
	// string input = "0 2 0 4 6 5 0 0 0 0 0 0    ";
	// fmt::print("x{}x", trim(input));

	Singleton *s1 = Singleton::getInstance();
	Singleton *s2 = Singleton::getInstance();
	std::cout << s1 << '\n';
	std::cout << s2 << '\n';

	// Will not try to call the constructor or do any initializing
	Prim prim;
	// Vertex a;
	// prim = new Prim(a);

	//
	int mainWindow = Wrapper::initWindow(900, 600, "Main");
	processTable pt(mainWindow);
	pt.initWindow();
	//
	HelpWindow hw(mainWindow);
	hw.initWindow();
	//registermousehandler(WM_LBUTTONDOWN, Helper::createVectex);
	//registermousehandler(WM_LBUTTONDBLCLK, Helper::clearViewPort);
	//Wrapper::initWindow(1200, 800, "AASD");
	//

	// style
	settextstyle(4, 4, 1);
	//

	File file;
	// return 0;

	//
	while (true) {
		int cmd = Wrapper::getOneChar();
		fmt::print("cmd:{} - ", cmd);
		switch (cmd) {
		case 8:
			file.init();
			break;
		case '1':
			fmt::print("create Vertex\n");
			//registermousehandler(WM_LBUTTONDOWN, Helper::createVectex);
			Helper::createVectex();
			break;

		case '2':
			fmt::print("create Edge\n");
			//registermousehandler(WM_LBUTTONDOWN, Helper::createEdge);
			Helper::createEdge();
			break;

		case '3':
			fmt::print("add/edit Weight edge\n");
			Helper::editWeight();
			break;

		case '4':
			fmt::print("remove Vertex/Edge\n");
			Helper::removeVertexOrEdge();
			break;
		case '5': {
			fmt::print("select vertex and start\n");
			bool status;
			auto v = Helper::setSelectedEdge(status);
			if (!status) {
				fmt::print("not set selected edge\n");
				break;
			}
			fmt::print("set selected edge\n");
			//
			prim.processTable.clear();
			prim.blacklist.clear();
			s1->store.processTable.clear();
			pt.update();
			s1->reDraw();
			//
			prim.currentVertex = v;
			break;
		}

		case '0':
			fmt::print("next state\n");
			pt.initWindow();
			prim.nextState();
			pt.update();
			break;

		case '/':
			fmt::print("scan\n");
			prim.scan();
			pt.update();
			break;

		case '8':
			fmt::print("clear Viewport\n");
			Wrapper::clearViewPort();
			break;

		case KEY_ESC:
			// clean all
			s1->store.Edges.clear();
			s1->store.Vertexs.clear();
			s1->store.processTable.clear();
			prim.processTable.clear();
			prim.blacklist.clear();
			s1->reDraw();
			pt.update();
			break;
			//
			//
			//
			//

		case '9':
			fmt::print("reDraw\n");
			s1->reDraw();
			break;

		case '.':
			fmt::print("[debug] prim\n");
			fmt::print("current:{}\n", prim.currentVertex.id);
			fmt::print("backlist: ");
			for (auto b : prim.blacklist) {
				fmt::print("{}, ", b.id);
			}
			fmt::print("\n");
			for (auto pt : prim.processTable) {
				fmt::print("sid:{}, did:{}, w:{}, passed:{}\n", pt.source.id, pt.destination.id, pt.weight, pt.passed);
			}
			break;

		case '*':
			fmt::print("[Debug] print Vertex\n");
			for (auto &v : s1->store.Vertexs) {
				fmt::print("id:{}\n", v.id);
			}
			break;

		case '-':
			fmt::print("[Debug] print Edge\n");
			for (auto &e : s1->store.Edges) {
				fmt::print("id:{}, sid:{}, eid:{}, w:{}\n", e.id, e.start.id, e.end.id, e.weight);
			}
			break;

		default:
			fmt::print("default\n");
			break;
		}
		//
		//s1->reDraw();
	}

	while (!kbhit()) {
		delay(300);
	}
}

// int main() {
//     int x = 5;
//     auto y = [&x]() {
//         fmt::print("x1:{}\n", x);
//         x = 10;
//         fmt::print("x2:{}\n", x);
// 		return x;
//     };

//     y();
//     fmt::print("X:{}\n", x);
// }

// int main() {
// 	int mainWindow = Wrapper::initWindow(900, 600, "Main");
// 	registermousehandler(WM_LBUTTONDOWN, getClick);

// 	delay(5000);
// 	fmt::print("W");
// 	registermousehandler(WM_LBUTTONDOWN, [](int x, int y){});
// 	clearmouseclick(WM_LBUTTONDOWN);

// 	while(!kbhit()) {
// 		delay(300);
// 	}

// }
