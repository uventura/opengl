#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureMesh> textures)
: m_vertices(vertices), m_indices(indices), m_textures(textures)
{
	setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));
	// Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, TexCoords)));

	glBindVertexArray(0);
}

void Mesh::Draw(Shader shader)
{
	bool activeTex = false;

	if(activeTex){
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for(unsigned int i = 0; i < m_textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			
			std::stringstream ss;
			std::string number;
			std::string name = m_textures[i].type;

			if(diffuseNr > 3 || specularNr > 2)
				continue;

			if(name == "texture_diffuse")
				ss << diffuseNr++;
			else if(name == "texture_specular")
				ss << specularNr++;

			number = ss.str();

			glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
			shader.uniform1iv(("material." + name + number).c_str(), i);
		}

		glActiveTexture(GL_TEXTURE0);
	}

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}