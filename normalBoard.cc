#include "normalBoard.h"
#include "Board.h"
#include "Tile.h"
#include <iostream>
using namespace std;

normalBoard::~normalBoard() = default;

normalBoard::normalBoard() : Board{} {
	// initialize the vertex/edge as their index
	for (int i = 0; i <= 53; i++) {
		if (i < 10) {
			string space = " " + to_string(i);
			vertex.push_back(space);
		}
		else {
			vertex.push_back(to_string(i));
		}
	}

	for (int i = 0; i <= 71; i++) {
		if (i < 10) {
			string space = " " + to_string(i);
			edge.push_back(space);
		}
		else {
			edge.push_back(to_string(i));
		}
	}
	for (int i = 0; i < 42; i++) {
		temp.push_back("");
		temp[i].assign(60, ' ');
	}
	for (int i = 0; i < 19; i++) {
		tiles.emplace_back(std::make_unique<Tile>(i));
	}
}

bool normalBoard::validVertex(int x) {
	if ((x >= 0) && (x <= 53)) { // the last vertex is 53
	  // can't be built on a vertex that is adjacent to a vertex with
	  // an existing residence
	  // find all adjacent vertex
		std::vector<int> adjV;
		for (const auto& it : findTile("vertex", x)) {
			std::vector<int> vv = tiles[it]->vertexAdjacentVertex(x);
			adjV.insert(adjV.end(), vv.begin(), vv.end());
		}
		// make sure all adjacent vertex is not occupied
		for (const auto& it : adjV) {
			if (!notOccupied("vertex", it)) {
				return false;
			}
		}
		// check the chosen vertex is not occupied
		if (notOccupied("vertex", x)) {
			return true;
		}
	}
	return false;
}

bool normalBoard::validRoad(int x) {
	if ((x >= 0) && (x <= 71)) { // the last edge is 71
		if (notOccupied("edge", x)) {
			return true;
		}
	}
	return false;
}

bool normalBoard::canBuild(char color, int x, std::string type) {
  bool meet = false;
  int emptyVertex = 0;
  bool oneEmptyVertex = false;
  const std::vector<int> all_tile =
      findTile("edge", x); // all tiles that have edge x
  if ((type == "Road") && (validRoad(x))) {
    // find all adjacent vertex: at most two adjacent vertexs for one edge
    std::vector<int> adjV = (tiles[all_tile[0]])->getAdjacentVertex(x);
    // condition 1: check if an adjacent residence is built by the same builder
    for (auto i : adjV) {
      if (!notOccupied("vertex", i)) { // if adjacent vertex is occupied
        // true if it's occupied by the same builder
        meet = (vertex[i][0] == color);
        oneEmptyVertex = true;
      } else {
        emptyVertex = i;
      }
    }
    if (meet) {
      return true;
    } else {
      // condition 2: an adjacent road is built by the same builder
      // if only one adjacent vertex is empty, check the adjacent edges of that
      // one
      if (oneEmptyVertex) {
        std::vector<int> adE;
        for (auto &it : findTile("vertex", emptyVertex)) {
          std::vector<int> be = tiles[it]->getAdjacentEdge(emptyVertex);
          adE.insert(adE.end(), be.begin(), be.end());
        }
        for (auto i : adE) {
          // if find any one of the adjacent edges is occupied by the same owner
          if (!notOccupied("edge", i) && (edge[i][0] == color)) {
            return true;
          }
        }
      } else {
        // if two vertex are empty find all adjacent edges
        std::vector<int> adjEE;
        for (auto &it : all_tile) {
          std::vector<int> ee = tiles[it]->edgeAdjacentEdge(x);
          adjEE.insert(adjEE.end(), ee.begin(), ee.end());
        }
        for (auto i : adjEE) {
          // if find any one of the adjacent edges is occupied by the same owner
          if (!notOccupied("edge", i) && (edge[i][0] == color)) {
            return true;
          }
        }
      }
    }
  } else if ((type == "Basement") && validVertex(x)) {
    // condition 1 already met since it's vaildvertex
    // condition 2: has an adjacent road that is built by the same builder
    // find all adjacent edges
    std::vector<int> adjE;
    for (auto &it : findTile("vertex", x)) {
      std::vector<int> be = tiles[it]->getAdjacentEdge(x);
      adjE.insert(adjE.end(), be.begin(), be.end());
    }
    for (auto i : adjE) {
      // if find any one of the adjacent edges is occupied by the same owner
      if (!notOccupied("edge", i) && (edge[i][0] == color)) {
        return true;
      }
    }
  }
  // if not satisfied any condition
  return false;
}

std::vector<std::pair<std::string, int>> normalBoard::getResidences(int x) {
	// find all tiles that has value x
	std::vector<int> tilesV;
	int n = 0;
	for (auto& i : tiles) {
		if (i->getValue() == x) {
			tilesV.push_back(n);
		}
		n++;
	}
	// find all residences of tileV
	std::vector<std::pair<std::string, int>> result;
	for (auto& it : tilesV) {
		std::vector<int> neighbours = getNeighbours(it);
		for (auto& i : neighbours) {
			result.push_back(std::make_pair(tiles[it]->getResource(), i));
		}
	}
	return result;
}



void normalBoard::resettemp() {
	for (int i = 0; i < 41; i++) {
		temp[i].assign(60, ' ');
	}
}

void normalBoard::OutputTile(int x, int y, vector<string> tilegraph) {
	for (auto&& i : tilegraph) {
		temp[x].replace(y, i.length(), i);
		++x;
	}
}

void normalBoard::printBoard(std::ostream& out) {
	int x = 0;
	int y = 26;
	for (auto&& i : tiles) {
		const vector<string> tilegraph = i->printTile(vertex, edge);
		OutputTile(x, y, tilegraph);
		if (x == 0 && y == 26) {
			x = 4;
			y = 16;
		}
		else if (x == 28 && y == 36) {
			x += 4;
			y = 26;
		}
		else if (y == 36) {
			x += 4;
			y = 6;
		}
		else if (y == 46) {
			x += 4;
			y = 16;
		}
		else {
			y += 20;
		}
	}
	for (auto&& i : temp) {
		out << i << endl;
	}
}

void normalBoard::saveBoard(std::ostream& out) {
	for (size_t i = 0; i < tiles.size(); ++i) {
		Tile* t = tiles[i].get();
		std::string r = t->getResource();
		if (r == "BRICK") {
			out << "0";
		}
		else if (r == "ENERGY") {
			out << "1";
		}
		else if (r == "GLASS") {
			out << "2";
		}
		else if (r == "HEAT") {
			out << "3";
		}
		else if (r == "WIFI") {
			out << "4";
		}
		else if (r == "PARK") {
			out << "5";
		}
		out << " ";
		out << t->getValue();
		if (i != tiles.size() - 1) {
			out << " ";
		}
	}
}