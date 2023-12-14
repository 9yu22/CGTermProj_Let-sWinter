#pragma once

#include "stdafx.h"
#include "block.h"

class BlockMgr
{
private:
	vector<Block> blockList;

public:
	BlockMgr();
	void initList();
	void render(GLuint shaderProgramID);

	void getInfo();

	Block checkCollision(glm::vec3 characterPos);
	void moveAllBlocks();
};

