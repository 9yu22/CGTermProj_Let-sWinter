#include "blockMgr.h"

BlockMgr::BlockMgr()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Block newB(-6 + j * 4, -2, 6 + -i * 4);
			this->blockList.push_back(newB);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Block newB(-22 + j * 4, -2, 22 + -i * 4);
			this->blockList.push_back(newB);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Block newB(-6 + j * 4, -2, 44 + -i * 4);
			this->blockList.push_back(newB);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Block newB(22 + j * 4, -2, 22 + -i * 4);
			this->blockList.push_back(newB);
		}
	}
}

void BlockMgr::initList()
{
	for (Block& b : blockList)
	{
		b.initBuffer();
		b.initTexture();
	}
}

void BlockMgr::render(GLuint shaderProgramID)
{
	for (Block& b : blockList)
	{
		b.render(shaderProgramID);
	}
}

void BlockMgr::getInfo()
{
	for (Block& b : blockList)
	{
		//std::cout << "À§Ä¡: (" << b.getPos().x;
	}
}

bool BlockMgr::checkCollision(glm::vec3 characterPos)
{
	for (Block& b : blockList)
	{
		if (characterPos.x >= b.getPos().x - 1.f && characterPos.x <= b.getPos().x + 1.f &&
			characterPos.z >= b.getPos().z - 1.f && characterPos.z <= b.getPos().z + 1.f)
		{
			if (characterPos.y == b.getPos().y + 2.f)
				return true;
		}
	}
	return false;
	
}

void BlockMgr::moveAllBlocks()
{
	for (Block& b : blockList)
	{
		// move
		b.setPos(b.getPos() + b.getVelocity());
		if (b.getPos().y < -2.f || b.getPos().y > 0.f) {
			b.setPos(b.getPos() - b.getVelocity());
			b.setVelocity(glm::vec3(b.getVelocity().x, -b.getVelocity().y, b.getVelocity().z));
		}

		// scale
		b.setScale(b.getScale() + b.getScaleV());
		if (b.getScale().y < 0.5f || b.getScale().y > 1.3f) {
			b.setScale(glm::vec3(b.getScale().x - b.getScaleV(), b.getScale().y - b.getScaleV(), b.getScale().z - b.getScaleV()));
			b.setScaleV(-b.getScaleV());
		}
	}
}

