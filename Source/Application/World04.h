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

		Transform m_transform;

		
		res_t<Material> m_material;
		res_t<Model> m_model;

		res_t<VertexBuffer> m_vertexBuffer;
	};
}
