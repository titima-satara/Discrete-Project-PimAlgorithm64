#pragma once

#include "Blueprint.h"
#include "Singleton.h"
#include "Wrapper.h"
#include <vector>

using namespace std;

class HelpWindow {
  private:
	int mainWindow;
	int currentWindow;
	int maxLines = 0;
	bool isInitWindow = false;

  private:
	void setMainWindow() {
		setcurrentwindow(mainWindow);
	}

	void setHelpWindow() {
		setcurrentwindow(currentWindow);
	}

  public:
	HelpWindow(int mainWin) {
		mainWindow = mainWin;
		currentWindow = Wrapper::initWindow(800, 600, "Help");
	}

	void initWindow() {
		setHelpWindow();
		int space = 30;
		string texts[] = {
			"", // wtf ?
			"Press 1, Create Vertex",
			"Press 2, Create Edge",
			"Press 3, Edit Weight",
			"Press 4, Remove Vertex or Edge",
			"Press 5, Select Vertex to start",
			"Press 0, Run",
			"Press /, Update(Update Table Only)",
			"Press Esc, Clear all & Redraw",

			"Press Backspace, Load input (test.txt)",
			
		};
		for (int i = 0; i < sizeof(texts) / sizeof(texts[0]); i++) {
			auto text = texts[i];
			int width = textwidth(&text[0]);
			Wrapper::writeText({10 + width, (space * i)}, text);
			fmt::print("i:{} | width:{} | s:{}\n", i, width, text);
		}
		setMainWindow();
	}
};

// ref split
// https://www.quora.com/How-do-I-split-a-string-by-space-into-an-array-in-c++