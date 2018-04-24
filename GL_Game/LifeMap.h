/*
	用来储存地图数据的类
*/

#ifndef H_LIFE_MAP_H
#define H_LIFE_MAP_H

#include <cstdlib>
#include <ctime>
#include <glad\glad.h>
#include <glm\glm.hpp>

#include "SpriteRenderer.h"
#include "ResourceManager.h"


class LifeMap
{
public:

	LifeMap();
	LifeMap(int size);
	~LifeMap();

	GLboolean Get(int row, int col);
	void LifeMap::Set(int row, int col, GLboolean b);

	// 随机放置点，根据prob这个随机几率（0.0 - 1.0）
	void Generate(float prob);

	// 游戏逻辑
	void Draw(SpriteRenderer * renderer);
	void Update();

private:
	GLboolean * _gridMap;
	GLboolean * _buffer;
	int _width;
	int _height;
};

#endif // !H_LIFE_MAP_H


