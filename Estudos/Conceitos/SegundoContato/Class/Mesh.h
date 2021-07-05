#pragma once
#include "MainHeader.h"
#include "Shader.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct TextureMesh
{
	unsigned int id;
	std::string type;
	aiString path;
};

class Mesh
{
public:
	// Mesh Data
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<TextureMesh> m_textures;
	// Functions
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureMesh> textures);
	void Draw(Shader shader);

private:
	unsigned int nDiffuses, nSpeculars;
	// Render Data
	unsigned int m_VAO, m_VBO, m_EBO;
	// Functions
	void setupMesh();
};