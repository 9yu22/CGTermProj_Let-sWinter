#pragma once
#include "stdafx.h"

int makeVertexShader(const char* path);
int makeFragmentShader(const char* path);
GLuint initShader(const char* vertPath, const char* fragPath);
