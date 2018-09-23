#include "ChunkMeshGenerator.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <iostream>



const float t = 1.0f / 16.0f;

void Addplane(std::vector<float>* vertexBuffer, side s, int x, int y, int z, int texX, int texY) {

	float ux = x;
	float uy = y;
	float uz = z;

	float yMin = (16 - (texY + 1)) * t;
	float yMax = (16 - (texY)) * t;
	float xMin = texX * t;
	float xMax = (texX + 1) * t;

	float right[] = {
		//right							    
		ux + 0.5f,  uy + 0.5f,  uz + 0.5f,  xMin, yMax,
		ux + 0.5f,  uy + 0.5f,  uz - 0.5f,  xMax, yMax,
		ux + 0.5f,  uy - 0.5f,  uz - 0.5f,  xMax, yMin,
		ux + 0.5f,  uy - 0.5f,  uz - 0.5f,  xMax, yMin,
		ux + 0.5f,  uy - 0.5f,  uz + 0.5f,  xMin, yMin,
		ux + 0.5f,  uy + 0.5f,  uz + 0.5f,  xMin, yMax,
	};											 
	float back[] = {							 
		//back									 
		ux - 0.5f, uy - 0.5f, uz - 0.5f,   xMin, yMin,
		ux + 0.5f, uy - 0.5f, uz - 0.5f,   xMax, yMin,
		ux + 0.5f, uy + 0.5f, uz - 0.5f,   xMax, yMax,
		ux + 0.5f, uy + 0.5f, uz - 0.5f,   xMax, yMax,
		ux - 0.5f, uy + 0.5f, uz - 0.5f,   xMin, yMax,
		ux - 0.5f, uy - 0.5f, uz - 0.5f,   xMin, yMin,
	};											 
	float front[] = {							 
		//front									 
		ux - 0.5f, uy - 0.5f,  uz + 0.5f,   xMin, yMin,
		ux + 0.5f, uy - 0.5f,  uz + 0.5f,   xMax, yMin,
		ux + 0.5f, uy + 0.5f,  uz + 0.5f,   xMax, yMax,
		ux + 0.5f, uy + 0.5f,  uz + 0.5f,   xMax, yMax,
		ux - 0.5f, uy + 0.5f,  uz + 0.5f,   xMin, yMax,
		ux - 0.5f, uy - 0.5f,  uz + 0.5f,   xMin, yMin,
	};											 
	float bottom[] = {							 
		//bottom						    	 
		ux - 0.5f, uy - 0.5f,  uz - 0.5f,   xMin, yMax,
		ux + 0.5f, uy - 0.5f,  uz - 0.5f,   xMax, yMax,
		ux + 0.5f, uy - 0.5f,  uz + 0.5f,   xMax, yMin,
		ux + 0.5f, uy - 0.5f,  uz + 0.5f,   xMax, yMin,
		ux - 0.5f, uy - 0.5f,  uz + 0.5f,   xMin, yMin,
		ux - 0.5f, uy - 0.5f,  uz - 0.5f,   xMin, yMax,
	};											 
	float top[] = {								 
		//top							    	 
		ux - 0.5f,  uy + 0.5f,  uz - 0.5f,  xMin, yMax,
		ux + 0.5f,   uy + 0.5f, uz - 0.5f,  xMax, yMax,
		ux + 0.5f,   uy + 0.5f, uz + 0.5f,  xMax, yMin,
		ux + 0.5f,   uy + 0.5f, uz + 0.5f,  xMax, yMin,
		ux - 0.5f,  uy + 0.5f,  uz + 0.5f,  xMin, yMin,
		ux - 0.5f,  uy + 0.5f,  uz - 0.5f,  xMin, yMax
	};											 
	float left[] = {							 
		//left							    	 
		ux - 0.5f,  uy + 0.5f,  uz + 0.5f,  xMin, yMax,
		ux - 0.5f,  uy + 0.5f,  uz - 0.5f,  xMax, yMax,
		ux - 0.5f,  uy - 0.5f,  uz - 0.5f,  xMax, yMin,
		ux - 0.5f,  uy - 0.5f,  uz - 0.5f,  xMax, yMin,
		ux - 0.5f,  uy - 0.5f,  uz + 0.5f,  xMin, yMin,
		ux - 0.5f,  uy + 0.5f,  uz + 0.5f,  xMin, yMax,

	};

	if (s == side::Left) {
		vertexBuffer->insert(vertexBuffer->end(), &left[0], &left[6 * 5]);
	}
	if (s == side::Right) {
		vertexBuffer->insert(vertexBuffer->end(), &right[0], &right[6 * 5]);
	}
	if (s == side::Front) {
		vertexBuffer->insert(vertexBuffer->end(), &front[0], &front[6 * 5]);
	}
	if (s == side::Back) {
		vertexBuffer->insert(vertexBuffer->end(), &back[0], &back[6 * 5]);
	}
	if (s == side::Top) {
		vertexBuffer->insert(vertexBuffer->end(), &top[0], &top[6 * 5]);
	}
	if (s == side::Bottom) {
		vertexBuffer->insert(vertexBuffer->end(), &bottom[0], &bottom[6 * 5]);
	}

}

void AddBlock(std::vector<float>* vertexBuffer, Block b) {
	for (int i = 0; i < 6; i++) {
		BlockPlane bp = b.Planes[(side)i];
		Addplane(vertexBuffer, bp.s, b.getXPos(), b.getYPos(), b.getZPos(), bp.xTex, bp.yTex);
	}
}

ChunkMesh* ChunkMeshGenerator::generateMesh(int x, int y, int z)
{
	float ux = x;
	float uy = y;
	float uz = z;

	ChunkMesh* mesh = new ChunkMesh;

	mesh->va = new VertexArray;

	VertexBufferLayout* layout = new VertexBufferLayout;
	std::vector<float>* vec = new std::vector<float>;
	//vec->assign(cube_vertices, cube_vertices + 36 * 5);
	
	for (int x = 0; x < 50; x++) {
		for (int y = 0; y < 15; y++) {
			for (int z = 0; z < 50; z++) {
				Block b(x, -y, z, blockType::Grass);
				AddBlock(vec, b);
			}
		}
	}



	mesh->buffer = vec;

	std::vector<float>* v = mesh->buffer;



	VertexBuffer* vb = new VertexBuffer(&((*v)[0]), v->size() * sizeof(float));

	layout->Push<float>(3);
	layout->Push<float>(2);
	mesh->va->AddBuffer(*vb, *layout);

	return mesh;
}


