#pragma once
#include "Engine/Utility/ModelLoader.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Mesh/StaticMesh.h"
#include "Engine/Utility/Logger.h"
namespace gp1
{
	class ModelLoader
	{
	public:
		static ModelLoader*       Get()
		{
			static ModelLoader I_Loader;
			return &I_Loader;
		}

		gp1::renderer::mesh::StaticMesh* Load(const char* path);
		

	private:
		ModelLoader(): m_logger("Model Loading") {};
		gp1::Logger m_logger;
	};
} // namespace gp1