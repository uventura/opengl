#pragma once
#include "MainHeader.h"
#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	// Functions
	Model(const char* path)
	{
		loadModel(path);
	}

	void Draw(Shader shader);

	~Model();
private:
	// Model Data
	std::string m_dir;
	std::vector<Mesh> m_meshes;
	std::vector<TextureMesh> textures_loaded;
	// Functions
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<TextureMesh> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};