#include "VertexArray.h"
#include "Shader.h"

VertexArray::VertexArray(GLfloat* vertices, GLint count, GLint floatPerVertex) {
  _tbo = 0;
  _count = count;

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, floatPerVertex * count * sizeof GLfloat, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(Shader::VERTEX_ATTRIB_LOC, floatPerVertex, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Shader::VERTEX_ATTRIB_LOC);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

VertexArray::VertexArray(GLfloat* texCoords, GLfloat* vertices, GLint numVerts, GLint numTex, GLint floatPerVertex) {
  _count = numVerts;

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, floatPerVertex * numVerts * sizeof GLfloat, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(Shader::VERTEX_ATTRIB_LOC, floatPerVertex, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Shader::VERTEX_ATTRIB_LOC);

	glGenBuffers(1, &_tbo);
	glBindBuffer(GL_ARRAY_BUFFER, _tbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * numTex * sizeof GLfloat, texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(Shader::TEX_ATTRIB_LOC, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Shader::TEX_ATTRIB_LOC);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VertexArray::bind() {
	glBindVertexArray(_vao);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}

void VertexArray::draw() {
	bind();
	glDrawArrays(GL_TRIANGLES, 0, _count);
	unbind();
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	if (_tbo != 0)
		glDeleteBuffers(1, &_tbo);
}
