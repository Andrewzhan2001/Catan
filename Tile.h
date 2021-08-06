#ifndef TILE
#define TILE
#include <string>
#include <vector>
class Board;

class Tile {
	int tileNum;
	std::string resource;
	int value;
	bool geese; // indicate whether there is a geese on this tile
	std::vector<int> vertex; // the index of the vertex of this tile
	std::vector<int> edge;  // the index of the edge of this tile

public:
	Tile(int tileNum);
	int getTileNum() const;
	int getValue() const;
	std::string getResource() const;
	std::vector<int> getVertex();
	void setGeese(bool has);
	void setResourceValue(std::string r, int v);
	// return all adjacent edge of vertex i
	std::vector<int> getAdjacentEdge(int vertexIndex);
	// return all adjacent vertex of edge i
	std::vector<int> getAdjacentVertex(int edgeIndex);
	// return all adjacent vertex of vertex i
	std::vector<int> vertexAdjacentVertex(int vertexIndex);
	// return all adjacent edge of edge i
	std::vector<int> edgeAdjacentEdge(int edgeIndex);
	// check whether the tile has type at index
	// if type is vertex/edge, check if it has vertex/edge index
	bool has(const std::string& type, int index);

	std::vector<std::string> printTile(const std::vector<std::string>& vertexs,
	                                   std::vector<std::string> edges);

	friend class Board;
};
#endif
