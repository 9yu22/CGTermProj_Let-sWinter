#pragma once

#include "object.h"

class character : public Object
{
private:
	GLint vtSize;
	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> uvs;

	unsigned int texture;

public:
	character();
	void render(GLuint shaderProgramID) override;
	void initBuffer() override;
	void initTexture() override;
};