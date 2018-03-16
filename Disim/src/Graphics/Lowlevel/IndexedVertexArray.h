#pragma once

#include <GL\glew.h>
#include "VertexArray.h"

class IndexedVertexArray : public VertexArray
{
public:
	IndexedVertexArray(GLfloat* vertices, GLuint* indices, GLint numVerts, GLint indicesCount, GLint floatPerVertex);
	IndexedVertexArray(GLfloat* vertices, GLfloat* texCoords, GLuint* indices, GLint numVerts, GLint indicesCount, GLint texCount, GLint floatPerVertex);
	~IndexedVertexArray();
	
	void draw() override;
	
private:
	GLuint _ibo;
};

