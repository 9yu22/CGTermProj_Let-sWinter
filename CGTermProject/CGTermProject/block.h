#pragma once

#include "object.h"

class Block : public Object
{
private:
	glm::vec3 velocity = {};
	float scaleVelocity = 0.f;

	GLint vtSize;
	vector<glm::vec3> vertices;
	vector<glm::vec3> colors;
	vector<glm::vec3> normals;
	vector<glm::vec2> uvs;

	unsigned int texture;

public:
	Block();
	Block(int x, int y, int z, bool random);
	void render(GLuint shaderProgramID) override;
	void initBuffer() override;
	void initTexture() override;

	void setVelocity(glm::vec3 vel);
	void setScaleV(float sv);

	glm::vec3 getVelocity();
	float getScaleV();
};

