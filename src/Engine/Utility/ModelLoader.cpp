//
//	Created by Matty2048 on 19. May. 2021
//

#include "Engine/Utility/ModelLoader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "../third_party/tinyobjloader/tiny_obj_loader.h"
gp1::renderer::mesh::StaticMesh* gp1::ModelLoader::Load(const char* path) //returns a pointer to a static mesh
{
	using namespace gp1::renderer::mesh;
	StaticMesh*  mesh = new StaticMesh();
	tinyobj::attrib_t                attrib;
	std::vector<tinyobj::shape_t>    shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;
	bool        ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path);

	if (!warn.empty())
	{
		m_logger.LogWarning(warn.c_str());
	}
	if (!err.empty())
	{
		m_logger.LogError(err.c_str());
	}
	
	if (!ret)
	{
		m_logger.LogWarning("Failed to parse model ", path);
		return nullptr; 
	}
	
	//
	//This segment copies the vertex data of the mesh
	mesh->m_Vertices.reserve(attrib.vertices.size()/3); //preallocates size
	for (unsigned int i = 0; i < attrib.vertices.size(); i += 3)
	{
		StaticMeshVertex v { {attrib.vertices[i], attrib.vertices[i + 1], attrib.vertices[i + 2] },
			                 {0.f,0.f,0.f},
			                 {0.f,0.f} };

		mesh->m_Vertices.emplace_back(v);
	}

	for (auto s: shapes)
	{
		for (auto i: s.mesh.indices)
		{
			mesh->m_Indices.push_back(i.vertex_index);
		}
	}
	



}
