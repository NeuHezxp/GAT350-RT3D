#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexBuffer.h"
#include "Core/Math/Transform.h"
#include "Renderer/Renderer.h"
#include <vector>

#include "Renderer/Material.h"

namespace nc
{
	class World04 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;

		glm::vec3 m_ambientLight = glm::vec3(0.2f, 0.2f, 0.2f);
		glm::vec3 m_diffuseLight = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 m_lightPosition = glm::vec3(0.0f, 8.0f, 0.0f);

		Transform m_transform;

		
		res_t<Material> m_material;
		res_t<Model> m_model;

		res_t<VertexBuffer> m_vertexBuffer;
	};
}
