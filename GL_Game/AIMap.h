#ifndef H_AI_MAP_H
#define H_AI_MAP_H

#include <cstdlib>
#include <ctime>
#include <glad\glad.h>
#include <glm\glm.hpp>

#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Vector2D.h"

struct Coord {
public:
	Coord() {}
	Coord(size_t r, size_t c) :row(r), col(c), step(0) {}
	size_t row;
	size_t col;
	int step;

};

struct Cell {
public:
	Cell() {}
	Cell(char v) : value(v), step(INT_MAX), prevCol(-1), prevRow(-1) {}
	char value;
	size_t step;
	int prevCol;
	int prevRow;
};

class AIMap
{
public:
	AIMap();
	AIMap(size_t);

	void GenerateMap(double);
	void SetTarget(size_t, size_t);
	Cell Get(int row, int col);
	void Set(int row, int col, Cell b);
	void SetChar(int row, int col, char c);
	bool Solve_Astar(SpriteRenderer *);
	bool Solve_BFS(SpriteRenderer *);
	void Draw(SpriteRenderer *);
	size_t GetStep() { return this->_step; }

	~AIMap();

private:
	Cell * _gridMap;
	GLboolean _solvable;
	size_t _step;
	size_t _rows;
	size_t _cols;
};

#endif