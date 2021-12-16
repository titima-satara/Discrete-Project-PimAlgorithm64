#pragma once

#include "Blueprint.h"
#include "Helper.h"
#include "Singleton.h"
#include "Wrapper.h"
#include <bits/stdc++.h>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class File {
  private:
	Singleton *s = Singleton::getInstance();
	vector<string> lines;
	int maxVertex;

  public:
	// File() {

	// }

	void init() {
		readFile();
		findMaxVertex();

		clear();

		createVertex();
		addEdge();
		s->reDraw();
	}

  private:
	void clear() {
		s->store.Vertexs.clear();
		s->store.Edges.clear();
		s->store.processTable.clear();
		s->reDraw();
	}

	void readFile() {
		lines.clear();
		string str;
		ifstream myFile("test.txt");
		while (getline(myFile, str)) {
			// auto re = regex_replace(str, regex("\\s+"), " ");
			// fmt::print("x{}x\n", re);
			// lines.push_back(re);
			lines.push_back(str);
		}
		myFile.close();
	}

	void findMaxVertex() {
		for (int row = 0; row < lines.size() - 1; row++) {
			// auto currentRow = lines[row];
			istringstream iss(lines[row]);
			vector<string> currentRow{
				istream_iterator<string>(iss),
				{},
			};

			for (int col = 1 + row; col < currentRow.size(); col++) {
				maxVertex = col + 1; // read from col + 1 // start from 1
			}
			break; // best performance ?
		}
	}

	void createVertex() {
		int height = 50;

		int width = (getmaxy() / 2);

		while (s->store.Vertexs.size() < maxVertex) {
			string text = fmt::format("Click to create vertex: {}", maxVertex - s->store.Vertexs.size());
			int textWidth = textwidth(&text[0]);
			Wrapper::writeText({width + textWidth, height}, text);
			fmt::print("current vertex:{} | need:{}", s->store.Vertexs.size(), maxVertex);
			Helper::createVectex();
		}
		fmt::print("success\n");
	}

	void addEdge() {
		for (int row = 0; row < lines.size() - 1; row++) {
			// auto currentRow = lines[row];
			istringstream iss(lines[row]);
			vector<string> currentRow{
				istream_iterator<string>(iss),
				{},
			};

			// for (int col = 0; col < currentRow.size(); col++) {
			// 	auto const currentChar = currentRow[col];
			// 	if (  col < row   ) {
			// 		fmt::print("* ");
			// 		continue;
			// 	}
			// 	fmt::print("{} ", currentChar);
			// }

			for (int col = 1 + row; col < currentRow.size(); col++) {
				auto const strWeight = currentRow[col];
				fmt::print("{} ", strWeight);
				// TODO:
				// need create vertex first
				// bc edge mapping with vertex (start and end)
				// may be load file and show need how many vertex and then add edge
				// can use remove char button for binding event
				//

				// Edge edge;
				// edge.start = s->store.Vertexs[row];
				// edge.end = s->store.Vertexs[col];
				// edge.
				int weight;
				try {
					weight = stoi(strWeight);
					if (weight == 0) {
						continue;
					}
				} catch (...) {
					fmt::print("new weight error!\n");
					s->reDraw();
					return;
				}
				//
				const auto edge1 = s->store.Vertexs[row];
				const auto destEdge = s->store.Vertexs[col];
				int center_x = (edge1.x + destEdge.x) / 2;
				int centet_y = (edge1.y + destEdge.y) / 2;
				Edge edge = {
					edge1,									 // start
					destEdge,								 // end
					{center_x, centet_y},					 // center
					15,										 // radius for click
					static_cast<int>(s->store.Edges.size()), // id
					weight,									 // weight
				};
				s->store.Edges.push_back(edge);
			}

			fmt::print("\n");
		}
		fmt::print("*****\n");
		//
	}
};