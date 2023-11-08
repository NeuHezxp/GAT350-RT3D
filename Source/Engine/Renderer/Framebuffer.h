#pragma once
#include "Framework/Resource/Resource.h"
#include <glm/glm/glm.hpp>
#include <glad/include/glad/glad.h>

namespace nc
{
	class Texture;

	class Framebuffer : public Resource
	{
	public:
		Framebuffer() = default;
		~Framebuffer();

		bool Create(std::string filename, ...) override; //probably wont use this
		bool CreateFramebuffer(res_t<Texture> texture); // 
		bool CreateDepthbuffer(int width, int height);

		void Bind(); // redner to frame buffer bind
		void Unbind();// render to screen

		glm::ivec2 GetSize() const { return m_size; }

		
	protected:
		GLuint m_fbo = 0; 
		res_t<Texture> m_texture;
		glm::ivec2 m_size{ 0 };
	};
}
