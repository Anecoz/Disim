#pragma once

#include <GL\glew.h>

class VertexArray
{
public:
	VertexArray(GLfloat* vertices, GLint count, GLint floatPerVertex);
	VertexArray(GLfloat* texCoords, GLfloat* vertices, GLint vertCount, GLint texCount, GLint floatPerVertex);
	virtual ~VertexArray();

	void virtual draw();

	GLint getVAOID() { return _vao; }
	GLint getCount() { return _count; }

protected:
	GLuint _vao, _vbo, _tbo;
	GLint _count;

	void bind();
	void unbind();
};

