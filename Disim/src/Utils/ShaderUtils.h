#pragma once
#include <GL\glew.h>

#include <string>
#include <vector>

class ShaderUtils {

public:
	static std::string readFile(const char* filePath);
	static GLuint loadShaders(const char *vertex_path, const char *fragment_path);

};