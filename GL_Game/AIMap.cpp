#include "AIMap.h"
#include <queue>
#include <mutex>

#define BLOCKED 'X'
#define NOPASS 'Z'
#define EMPTY '\0'
#define TARGET 'T'
#define PATH 'P'

size_t _targetR;
size_t _targetC;

static double h_distance(Coord coord) {
	double row_diff = (double)coord.row - _targetR;
	double col_diff = (double)coord.col - _targetC;
	//return abs(row_diff) + abs(col_diff) + coord.step;
	return sqrt(row_diff * row_diff + col_diff * col_diff) + coord.step * 0.8;
}


class Compare
{
public:
	bool operator() (Coord a, Coord b)
	{
		return h_distance(a) > h_distance(b);
	}
};



std::mutex mutex_lock;

std::priority_queue<Coord, std::vector<Coord>, Compare> minPQ;


AIMap::AIMap()
{
}

AIMap::AIMap(size_t dimension)
{
	this->_solvable = false;
	this->_rows = this->_cols = dimension;
	this->_gridMap = new Cell[this->_rows * this->_cols];
	for (int i = 0; i < _rows * _cols; i++) {
		_gridMap[i].value = EMPTY;
		_gridMap[i].step = INT32_MAX;
		_gridMap[i].prevCol = -1;
		_gridMap[i].prevRow = -1;
	}
	//memset(_gridMap, 0, sizeof(Cell) * _rows * _cols);
	srand((unsigned)time(nullptr));
}


void AIMap::Set(int row, int col, Cell c)
{
	_gridMap[row * _cols + col] = c;
}
void AIMap::SetChar(int row, int col, char c)
{
	_gridMap[row * _cols + col].value = c;
}
bool AIMap::Solve_Astar(SpriteRenderer * renderer)
{
	minPQ.push(Coord(0, 0));

	while (!minPQ.empty()) {
		Coord current = minPQ.top();
		minPQ.pop();

		if (current.row == _targetR && current.col == _targetC) {
			Cell c = Get(_targetR, _targetC);
			c.step = current.step + 1;
			_step = c.step;
			printf("PREV: %d %d\n", c.prevRow, c.prevCol);
			while (c.prevCol != -1 && c.prevRow != -1) {
				SetChar(c.prevRow, c.prevCol, PATH);
				c = Get(c.prevRow, c.prevCol);
				printf("PREV: %d %d\n", c.prevRow, c.prevCol);
			}
			return true;
		}
		SetChar(current.row, current.col, NOPASS);


		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (!(i == 0 && j == 0) && (i ^ j) & 1) {
					Cell c = Get(current.row + i, current.col + j);
					if (c.value == EMPTY || c.value == TARGET) {
						Coord next = Coord(current.row + i, current.col + j);
						next.step = current.step + 1;
						if (next.step < c.step) {
							c.step = next.step;
							c.prevRow = current.row;
							c.prevCol = current.col;
							Set(current.row + i, current.col + j, c);
							SetChar(current.row + i, current.col + j, NOPASS);
							minPQ.push(next);
						}
						//Set(current.row + i, current.col + j, NOPASS);
					}
				}
			}
		}
		//this->Draw(renderer);
		Sleep(10);
	}
	return false;
}
bool AIMap::Solve_BFS(SpriteRenderer * renderer)
{
	std::queue<Coord> queue;
	queue.push(Coord(0, 0));
	while (!queue.empty()) {
		Coord current = queue.front();
		queue.pop();
		if (current.row == _targetR && current.col == _targetC) {
			Cell c = Get(_targetR, _targetC);
			c.step = current.step + 1;
			_step = c.step;
			printf("PREV: %d %d\n", c.prevRow, c.prevCol);
			while (c.prevCol != -1 && c.prevRow != -1) {
				SetChar(c.prevRow, c.prevCol, PATH);
				c = Get(c.prevRow, c.prevCol);
				printf("PREV: %d %d\n", c.prevRow, c.prevCol);
			}
			return true;
		}
		SetChar(current.row, current.col, NOPASS);
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (!(i == 0 && j == 0) && (i ^ j) & 1) {
					Cell c = Get(current.row + i, current.col + j);
					if (c.value == EMPTY || c.value == TARGET) {
						Coord next = Coord(current.row + i, current.col + j);
						next.step = current.step + 1;
						if (next.step < c.step) {
							c.step = next.step;
							c.prevRow = current.row;
							c.prevCol = current.col;
							Set(current.row + i, current.col + j, c);
							SetChar(current.row + i, current.col + j, NOPASS);
							queue.push(next);
						}
						//Set(current.row + i, current.col + j, NOPASS);
					}
				}
			}
		}
		//this->Draw(renderer);
		//Sleep(1);
	}
	return false;
}
void AIMap::Draw(SpriteRenderer * renderer)
{
	Texture2D tex = ResourceManager::GetTexture("white");
	int s = 9;
	glm::vec2 cell_size = glm::vec2(9, 9);
	for (int row = 0; row < _rows; row++) {
		for (int col = 0; col < _cols; col++) {
			Cell c = Get(row, col);
			if (c.value == EMPTY)
				renderer->DrawSprite(tex, glm::vec2(150.0f + col * s, 50.0f + row * s), cell_size);
			else if(c.value == TARGET)
				renderer->DrawSprite(tex, glm::vec2(150.0f + col * s, 50.0f + row * s), cell_size, 0.0f,
					glm::vec3(1.0f, 1.0f, 0.0f));
			else if (c.value == NOPASS)
				renderer->DrawSprite(tex, glm::vec2(150.0f + col * s, 50.0f + row * s), cell_size, 0.0f,
					glm::vec3(1.0f, 0.5f, 0.5f));
			else if (c.value == BLOCKED)
				renderer->DrawSprite(tex, glm::vec2(150.0f + col * s, 50.0f + row * s), cell_size, 0.0f,
					glm::vec3(0.0f, 0.0f, 0.0f));
			else if (c.value == PATH)
				renderer->DrawSprite(tex, glm::vec2(150.0f + col * s, 50.0f + row * s), cell_size, 0.0f,
					glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}
}
Cell AIMap::Get(int row, int col)
{
	if (row < 0 || row >= _rows || col < 0 || col >= _cols) return BLOCKED;
	return _gridMap[row * _cols + col];
}

void AIMap::GenerateMap(double prob)
{
	for (int row = 0; row < _rows; row++) {
		for (int col = 0; col < _cols; col++) {
			if ((float)rand() / (float)RAND_MAX < prob) SetChar(row, col, BLOCKED);
		}
	}
}

void AIMap::SetTarget(size_t row, size_t col)
{
	SetChar(row, col, TARGET);
	_targetR = row;
	_targetC = col;
}


AIMap::~AIMap()
{
	delete[] _gridMap;
}
