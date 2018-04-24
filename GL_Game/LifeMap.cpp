#include "LifeMap.h"

GLboolean _get(GLboolean * array, int width, int height, int row, int col) {
	if (row < 0)
		row += height;
	else if (row >= height)
		row -= height;
	if (col < 0)
		col += width;
	else if (col >= width)
		col -= width;
	
	return array[row * width + col];
}

int _getNumliveNeighbor(GLboolean * array, int width, int height, int row, int col) {
	int count = 0;
	for (int r = -1; r <= 1; r++) {
		for (int c = -1; c <= 1; c++) {
			if (r == 0 && c == 0) continue;
			if (_get(array, width, height, row + r, col + c))
				count++;
		}
	}
	return count;
}

void _set(GLboolean * array, int row, int col, int width, GLboolean b) {
	array[row * width + col] = b;
}

LifeMap::LifeMap()
{
}

LifeMap::LifeMap(int size)
{
	this->_width = this->_height = size;
	_gridMap = new GLboolean[size * size];
	_buffer = new GLboolean[size * size];
	memset(_gridMap, 0, sizeof(GLboolean) * size * size);
	
	srand((unsigned)time);
}


LifeMap::~LifeMap()
{
	delete[] _gridMap;
	delete[] _buffer;
}

GLboolean LifeMap::Get(int row, int col)
{
	return _gridMap[row * _width + col];
}

void LifeMap::Set(int row, int col, GLboolean b)
{
	_gridMap[row * _width + col] = b;
}

void LifeMap::Generate(float prob)
{
	for (int row = 0; row < _height; row++) {
		for (int col = 0; col < _width; col++) {

			float n = (float)rand() / (float)RAND_MAX;
			if (n < prob)
				Set(row, col, true);
		}
	}
}

void LifeMap::Draw(SpriteRenderer * renderer)
{
	Texture2D tex = ResourceManager::GetTexture("white");
	for (int row = 0; row < _height; row++) {
		for (int col = 0; col < _width; col++) {
			if(Get(row, col))
				renderer->DrawSprite(tex, glm::vec2(150.0f + col * 5, 50.0f + row * 5), glm::vec2(3, 3));
		}
	}
}

void LifeMap::Update()
{
	memcpy(_buffer, _gridMap, _width * _height);

	for (int row = 0; row < _height; row++) {
		for (int col = 0; col < _width; col++) {
			int count = _getNumliveNeighbor(_buffer, _width, _height, row, col);
			if (_get(_buffer, _width, _height, row, col)) {
				if (count < 2 || count > 3)
					Set(row, col, false);
			}
			else {
				if(count == 3)
					Set(row, col, true);
			}
		}
	}
	
	
}
