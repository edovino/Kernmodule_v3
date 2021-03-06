#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ChunkMesh.h"
#include "Texture.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);


class Renderer {
	
private:
	glm::mat4 proj;
	glm::mat4* view;
	Texture terrain;
	Shader sh;


public:
	Renderer(const glm::mat4& proj, glm::mat4* view);
	~Renderer();
	void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, glm::mat4 modelTransform);
	void Draw(const VertexArray& va, Shader& shader, glm::mat4 modelTransform);
	void Draw(const VertexArray & va, Shader& shader, glm::mat4 modelTransform, unsigned int amountOfVerts);
	void Draw(ChunkMesh* chunk);
};