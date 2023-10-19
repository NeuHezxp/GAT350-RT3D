#include "World04.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>

namespace nc
{
	bool World04::Initialize()
	{
		auto material = GET_RESOURCE(Material, "materials/grid.mtrl");
		m_model = std::make_shared<Model>();
		m_model->SetMaterial(material);
		m_model->Load("models/squirrel.glb"); // The object for the model // Go to grid.mtrl for texture

		return true;
	}

	void World04::Shutdown()
	{
	}

	void World04::Update(float dt)
	{
		ENGINE.GetSystem<Gui>()->BeginFrame();

		ImGui::Begin("Transform");
		ImGui::DragFloat3("Position", &m_transform.position[0], 0.1f);
		ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
		ImGui::DragFloat3("Scale", &m_transform.scale[0], .01f);
		ImGui::End();

		ImGui::Begin("Light");
		ImGui::SliderFloat3("Ambient Light", &m_ambientLight[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse Light", &m_diffuseLight[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("Light Position", &m_lightPosition[0], -10.0f, 10.0f);
		ImGui::End();

		//m_transform.rotation.z += 180 * dt;

		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * +dt : 0;
		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * +dt : 0;

		m_time += dt;

		auto material = m_model->GetMaterial();

		material->ProcessGui();
		material->Bind();

		// model matrix
		material->GetProgram()->SetUniform("model", m_transform.GetMatrix());

		// view matrix
		glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
		material->GetProgram()->SetUniform("view", view);

		// projectioon matrix
		glm::mat4 projection = glm::perspective(glm::radians(70.0f), ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), 0.01f, 100.0f); //zNear is clipping for how close // zFar is anything far away is gone
		material->GetProgram()->SetUniform("projection", projection);

		//matrix for light
		// Update light uniforms
		material->GetProgram()->SetUniform("ambientLight", m_ambientLight);
		material->GetProgram()->SetUniform("light.color", m_diffuseLight);
		material->GetProgram()->SetUniform("light.position", m_lightPosition);

		ENGINE.GetSystem<Gui>()->EndFrame();
	}

	void World04::Draw(Renderer& renderer)
	{
		// pre-render
		renderer.BeginFrame();
		// render
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		m_model->Draw();
		ENGINE.GetSystem<Gui>()->Draw();
		// post-render
		renderer.EndFrame();
	}
}