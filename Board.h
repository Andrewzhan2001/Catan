#ifndef BOARD
#define BOARD
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "Tile.h"

class Board {
protected:
	std::vector<std::string> vertex;
	std::vector<std::string> edge;
	std::vector<std::unique_ptr<Tile>> tiles;
	// check whether vertex/road at x is occupied by someone
	bool notOccupied(std::string type, int x);
public:
	virtual ~Board();
	// get the number of tiles
	int getTileNum() const;
	// get the number of roads
	int getRoadNum() const;
	// get the number of vertexs
	int getVertexNum() const;
	// set vertex at index as builder+residence type
	void setVertex(int idx, std::string builder, std::string residence);
	// set vertex at index as builder+"R"
	void setEdge(int idx, std::string builder);
	// set tile x resource and value
	void setTile(int n, std::string resource, int value);
	// return the tile number which has the geese on it
	int getGeese();
	// return whether the tile tilenum has geese
	bool haveGeese(int tilenum);
	// set Geese to tile tilenum
	void setGeeseOnTile(int tilenum);
	// determines whether int x represents a valid vertex
	// A valid vertex must satisfy:
	//   1. The vertex must be in range
	//   2. The vertex has not been occupied
	//   3. The vertex does not have any exsiting residences on its adjacent vertexs 
	// IF INVALID, OUTPUTS "You cannot build here."
	virtual bool validVertex(int x) = 0;
	// determine whether we can build road of edge
	// detail see 2.6 roads
	virtual bool validRoad(int x) = 0;
	// returns vertex indexs that has residence on tile x
	virtual std::vector<int> getNeighbours(int x);
	// find all the tiles that has vertex/edge i
	std::vector<int> findTile(std::string type, int x);
	// determines whether player with color can build a basement/road
	//   at location x.
	// Note: type could only be either "Road" or "Basement"
	virtual bool canBuild(char color, int x, std::string type) = 0;
	// creates a basement/road at location x for player with color
	// Note: type could only be either "road" or "Basement"
	virtual void create(char color, int x, std::string type);
	// determines whether player with color can upgrade residence
	//   at location x.
	virtual bool canUpgrade(char color, int x);
	// upgrades the residence at location x for player with color
	// upgrades to house from basement, upgrades to tower from house
	//   and does nothing if location x is already a tower
	virtual void upgradeLevel(char color, int x);
	// returns a vector of residences that are adjacent to the tiles
	//  with tile value x, the string type represents the kind of resources
	//  will be awarded for this location
	virtual std::vector<std::pair<std::string, int>> getResidences(int x) = 0;
	// print this board to out
	virtual void printBoard(std::ostream& out) = 0;
	// save current board layout to out
	virtual void saveBoard(std::ostream& out) = 0;
};
#endif