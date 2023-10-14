#pragma once
#include <vector>
#include <glad/glad.h>

#include "Framework/World.h"
#include "Renderer/Renderer.h"

namespace nc
{
	class World03 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;

		float m_uvOffsetX = 0.0f;
		float m_uvOffsetY = 0.0f;
		float m_uvtilesetX = 0.0f;
		float m_uvtilesetY = 0.0f;

		Transform m_transform;

		res_t<Program> m_program;
		res_t<Texture> m_texture;
		res_t<VertexBuffer> m_vertexBuffer;
	};
}