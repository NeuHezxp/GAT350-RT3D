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
	struct light_t
	{
		enum eType
		{
			DIRECTIONAL,
			POINT,
			SPOT,
		};

		eType type;
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 color;
		float cutoff;
		
	};

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

		light_t m_light;
		glm::vec3 m_ambientLight = glm::vec3(0.2f, 0.2f, 0.2f);


		Transform m_transform;

		
		res_t<Material> m_material;
		res_t<Model> m_model;
		res_t<VertexBuffer> m_vertexBuffer;
	};
}
