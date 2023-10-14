#include "World03.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#define INTERLEAVE

namespace nc
{
	bool World03::Initialize()
	{
		m_program = GET_RESOURCE(Program, "Shaders/unlit_texture.prog");
		m_program->Use();

		m_texture = GET_RESOURCE(Texture, "Textures/llama.jpg");
		m_texture->Bind();
		m_texture->SetActive(GL_TEXTURE0);

		// Vertex Data
		float vertexData[] = {
			// Position         // Color        // Texcoords
			-0.8f, -0.8f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			-0.8f,  0.8f, 0.0f, 1.0f, 1.0f, 0.5f, 0.0f, 1.0f,
			 0.8f, -0.8f, 0.0f, 0.8f, 0.5f,-1.0f, 1.0f, 0.0f,
			 0.8f,  0.8f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};

		// Create and set up vertex buffer
		m_vertexBuffer = GET_RESOURCE(VertexBuffer, "vb");
		m_vertexBuffer->CreateVertexBuffer(sizeof(vertexData), 4, vertexData);
		m_vertexBuffer->SetAttribute(0, 3, 8 * sizeof(GLfloat), 0);                  // position
		m_vertexBuffer->SetAttribute(1, 3, 8 * sizeof(GLfloat), 3 * sizeof(float));  // color
		m_vertexBuffer->SetAttribute(2, 2, 8 * sizeof(GLfloat), 6 * sizeof(float));  // texcoord

		return true;
	}

	void World03::Shutdown()
	{
	}

	void World03::Update(float dt)
	{
		ENGINE.GetSystem<Gui>()->BeginFrame();
		ImGui::Begin("Transform");
		ImGui::DragFloat3("Position", &m_transform.position[0]);
		ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
		ImGui::DragFloat3("Scale", &m_transform.scale[0]);
		ImGui::DragFloat2("UV offset ", &m_uvOffsetX, 0.01f, 1.0f, 10.0f);
		ImGui::DragFloat2("UV Tile ", &m_uvtilesetX, 0.01f, 1.0f, 10.0f);


		ImGui::End();


		//added movement
		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * dt : 0;
		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
		m_transform.position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_Q) ? m_speed * -dt : 0;
		m_transform.position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_E) ? m_speed * dt : 0;
		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * dt : 0;
		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * -dt : 0;
		m_time += dt;
		m_program->SetUniform("offset", glm::vec2{ m_uvOffsetX + m_time, m_uvOffsetY });
		m_program->SetUniform("tiling", glm::vec2{ m_uvtilesetX, m_uvtilesetY });
		///model matrix
		///
	//	glm::mat4 position = glm::translate(glm::mat4{ 1 }, m_position); //if the parentheses are confusing, make em brackets
	//	glm::mat4 rotation = glm::rotate(glm::mat4{ 1 }, glm::radians(m_angle), glm::vec3{ 0, 0, 1 });
	//	glm::mat4 model = position * rotation; //make model = position, which was the PREVIOUS mat4 model
		m_program->SetUniform("model", m_transform.GetMatrix());

		///view matrix
		glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }); //make the -5 a 5 or else itll be weird!!!
		m_program->SetUniform("view", view);

		///projection
		glm::mat4 projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.01f, 100.0f);
		m_program->SetUniform("projection", projection);
		ENGINE.GetSystem<Gui>()->EndFrame();
	}

	void World03::Draw(Renderer& renderer)
	{
		// pre-render
		renderer.BeginFrame();

		/// render
		m_vertexBuffer->Draw(GL_TRIANGLE_STRIP);
		ENGINE.GetSystem<Gui>()->Draw();
		// post-render
		renderer.EndFrame();
	}
}