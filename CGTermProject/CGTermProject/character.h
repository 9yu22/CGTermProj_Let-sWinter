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

	float moveLeftRight = 0.f;
	float moveBackForth = 0.f;
	float moveUpDown = 0.f;
	float rotationAngle = 0.f;

public:
	character();
	void render(GLuint shaderProgramID) override;
	void initBuffer() override;
	void initTexture() override;
};