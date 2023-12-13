#pragma once

#include "object.h"

class Block : public Object
{
private:
	GLint vtSize;
	vector<glm::vec3> vertices;
	vector<glm::vec3> colors;
	vector<glm::vec3> normals;
	vector<glm::vec2> uvs;

	unsigned int texture;

public:
	Block();
	void render(GLuint shaderProgramID) override;
	void initBuffer() override;
	void initTexture() override;
};

