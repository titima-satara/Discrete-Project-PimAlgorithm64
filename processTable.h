#pragma once
#include "Blueprint.h"
#include "Wrapper.h"
#include <fmt/format.h>
#include <iostream>
#include <vector>
// #include <graphics.h>

using namespace std;

class processTable {
  private:
	int mainWindow;
	int currentWindow;
	int maxLines = 0;
	bool isInitWindow = false;
	//
	int space = 10;
	int headerHeight = 40;
	int lineHeight = 30;
	//
	Singleton *s = Singleton::getInstance();

  private:
	void setMainWindow() {
		setcurrentwindow(mainWindow);
	}

	void setProcessTableWindow() {
		setcurrentwindow(currentWindow);
	}

	void drawFrameTable() {
		setProcessTableWindow();

		rectangle(space, space, getmaxx() - space, getmaxy() - space);
		//

		line(space, space + headerHeight, getmaxx() - space, space + headerHeight);
		//
		int col_splits[] = {195, 390};
		for (auto const &col : col_splits) {
			line(space + col, space, space + col, getmaxy() - space);
		}
		int col_texts_axis[] = {
			150,
			340,
			530,
		};
		string col_texts[] = {
			"v Source",
			"v Dest",
			"Weight",
		};
		for (int i = 0; i < sizeof(col_texts_axis) / sizeof(col_texts_axis[0]); i++) {
			Wrapper::writeText({space + col_texts_axis[i], space + (headerHeight / 2) + 10}, col_texts[i]);
		}
		//

		int lines = 1;
		while (true) {
			int height = space + headerHeight + (lineHeight * lines);
			if (height > getmaxy() - space)
				break;
			line(space, height, getmaxx() - space, height);
			lines++;
		}
		maxLines = lines;
		//
		fmt::print("lines:{}\n", lines);
		setMainWindow();
	}

	void writeLine(int y, string msg1, string msg2, string msg3, int color = 15) {
		int col_texts_axis[] = {
			120,
			310,
			500,
		};
		Wrapper::writeText({space + col_texts_axis[0], y}, msg1, color);
		Wrapper::writeText({space + col_texts_axis[1], y}, msg2, color);
		Wrapper::writeText({space + col_texts_axis[2], y}, msg3, color);
	}

  public:
	processTable(int mainWin) {
		mainWindow = mainWin;
	}

	void update() {
		// if (line < 0) {
		// 	fmt::print("line must > 0");
		// 	return;
		// }
		// if (line > maxLines) {
		// 	fmt::print("line > maxLines: {} > {}", line, maxLines);
		// 	return;
		// }
		// setProcessTableWindow();
		// int col_texts_axis[] = {
		// 	120,
		// 	310,
		// 	500,
		// };
		// for (int i = 1; i <= maxLines; i++) {
		// 	int height = space + headerHeight + (i * lineHeight) - 3;
		// 	for (auto const &col : col_texts_axis) {
		// 		Wrapper::writeText({space + col, height}, fmt::format("v{}", i));
		// 	}
		// }
		setProcessTableWindow();
		Wrapper::clearViewPort();
		drawFrameTable();
		setProcessTableWindow();
		bool debug = false;
		if (debug) {
			for (int i = 1; i <= maxLines; i++) {
				int height = space + headerHeight + (i * lineHeight) - 3;
				writeLine(height, "v1", "v2", "v3");
			}
		} else {
			for (int i = 1; i <= s->store.processTable.size(); i++) {
				int height = space + headerHeight + (i * lineHeight) - 3;
				auto index = s->store.processTable[i - 1];
				writeLine(
					height,
					fmt::format("v{}", index.source.id),
					fmt::format("v{}", index.destination.id),
					fmt::format("{}", index.weight),
					(index.passed == true) ? COLOR(255, 0, 0) : 15);
			}
		}

		setMainWindow();
	}

	void
	initWindow() {
		if (isInitWindow) {
			return;
		}
		isInitWindow = true;
		currentWindow = Wrapper::initWindow(600, 900, "Table");
		drawFrameTable();
		update();
		setMainWindow();
	}
};