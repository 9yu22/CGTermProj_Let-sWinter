#include "blockMgr.h"

BlockMgr::BlockMgr()
{
	//Block centerB(0, -2, 0, false);
	//this->blockList.push_back(centerB);

	for (int i = 0; i < 5; ++i)
	{
		Block newB(-6 + i * 4, -2, 10, true, false);
		this->blockList.push_back(newB);
	}

	for (int i = 0; i < 10; ++i)
	{
		Block newB(-10, -2, 10 + i * 4, true, true);
		this->blockList.push_back(newB);
	}

	for (int i = 0; i < 5; ++i)
	{
		Block newB(-6 + i * 4, -2, 50, true, false);
		this->blockList.push_back(newB);
	}

	for (int i = 0; i < 10; ++i)
	{
		Block newB(12, -2, 10 + i * 4, true, true);
		this->blockList.push_back(newB);
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
		//std::cout << "위치: (" << b.getPos().x;
	}
}

Block BlockMgr::checkCollision(glm::vec3 characterPos)
{
	for (Block& b : blockList)
	{
		if (characterPos.x >= b.getPos().x - b.getScale().y && characterPos.x <= b.getPos().x + b.getScale().y &&
			characterPos.z >= b.getPos().z - b.getScale().y && characterPos.z <= b.getPos().z + b.getScale().y)
		{
			//cout << "블록영역" << endl;
			//cout << "내 위치: " << characterPos.x << "," << characterPos.y << "," << characterPos.z << endl;
			//cout << "블록(-x~x / -z~z): " << b.getPos().x - b.getScale().x / 2 << "," << b.getPos().x + b.getScale().x / 2 << endl;
			return b;
		}
	}
	return Block(-10, -10, -10, false, false);
	
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

